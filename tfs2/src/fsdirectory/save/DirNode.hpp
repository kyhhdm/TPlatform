/** @file DirNode.hpp
 * DirNode is the directory tree node type.
 *
 * @author PengBo
 * @date 18 7 2007
 *
 *   <br>
 * design notes: <br>
 *   1.use vector to store files and subdir nodes, it's simple but not efficient  <br>
 *     it's slow in find an item and erase item operation in vector.               <br>  
 *     use set<> maybe better, especially for m_children.
 *   2.there are memeory preserving in vector implementation, usally 2K each vector <br>
 *     which means high level of memeory wastes.  <br>
 *   <br>
 *   3. 20070808,pb, should not use vector<INode> but vector<INode*> is better <br>
 *     because items in vector maybe moved when container increases, which make objects in vector <br>
 *     copied around, terrible there. <br>
 *     Although shared_ptr<INode> are recommended by textbook, here without memeory managment problem <br> 
 *     <INode*> is just ok.  <br>
 *
 */
#ifndef _TFSMASTER_DIRNODE_HPP
#define _TFSMASTER_DIRNODE_HPP 

#include "INode.hpp"
#include "common/IceGenerated.hpp"
#include "common/Types.hpp"
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/vector.hpp>

namespace tfs {
    
    class DirNode;

    typedef std::vector<INode*>::iterator  INodeIterator;
    typedef std::vector<DirNode*>::iterator DirNodeIterator;

    class DirNode {
        //internal data structure
        INode*    m_inode;
        DirNode*  m_parent;
        int       m_lockCount;
        std::vector<INode*>     m_files;
        std::vector<DirNode*>   m_children;
        
        
        friend class boost::serialization::access;
        template<class Archive>
        void save(Archive & ar, const unsigned int version) const;
        template<class Archive>
        void load(Archive & ar, const unsigned int version);

        BOOST_SERIALIZATION_SPLIT_MEMBER();

    public:
        enum OperationHint{
            OpDefault,
            FreeNodeInDelete,
            ReserveNodeInDelete
        };

        //1.constructors
        /** Constructor.
         */    
        DirNode();
        DirNode(const std::string& name, DirNode* parent);
        ~DirNode();

        //2. read only accessors
        /** Get inode id of this node
         */
        INode* getINode() ;

        /** Get name of this node
         */
        const std::string& getName();

        /** Get parent node 
         */
        DirNode* getParent() const ;

        /** Get lock count 
         */
        int getLockCount() const ;


         /** Get inodes iterator begin of the files in this directory
         *
         */    
        INodeIterator getFilesBegin();

         /** Get inodes iterator end of the files in this directory
         *
         */    
        INodeIterator getFilesEnd();

         /** Find a file according to it's name
         *
         * @return : NULL if not found, otherwise return the found INode pointer
         */    
        INode* findFile(const std::string& name) ;


         /** Get children iterator begin
         *
         */    
        DirNodeIterator getChildrenBegin();

         /** Get children iterator end
         *
         */    
        DirNodeIterator getChildrenEnd();

         /** Find a child according to it's name
         *
         * @return : NULL if not found, otherwise return the found DirNode pointer
         */    
        DirNode* findChild(const std::string& name);


        //3. mutable accessors
        /** Set inode id of this node
         */
        //void setINode(const INode& inode);

        /** Increment lock count
         */
        void incLock();

        /** Decrement lock count
         */
        void decLock();

        /** Add file in this node
         */
        void addFile(const INode& inode);
        void addFile(INode* pINode);

        /** Delete a file in this node
         */
        void deleteFile(const std::string& filename, OperationHint hint = FreeNodeInDelete);

        /** Add child under this node
         */
        void addChild(DirNode* node);

        /** Delete a child under this node
         */
        void deleteChild(DirNode* node,  OperationHint hint = FreeNodeInDelete);

        /** Set parent
         */
        void setParent(DirNode* parent);

        //4.helper function
        void makeFilesInfo(FilesInfo& filesInfo);

    };

    // inline implementation =================================
    inline  DirNode::DirNode() {
        //
        //! default constructor can't allocate memeory, otherwise serialize 
        //  process will leak memeory for it call default constructor and 
        //  reset the pointers.
        m_inode = NULL;
        m_parent = NULL;
        m_lockCount = 0;
    }

    inline  DirNode::~DirNode() {
        if (m_inode) delete m_inode;

        for ( INodeIterator iter = m_files.begin(); iter != m_files.end(); ++iter){
            delete *iter;
        }

        for ( DirNodeIterator iter = m_children.begin(); iter != m_children.end(); ++iter){
            delete *iter;
        }
    }   

    inline  DirNode::DirNode(const std::string& name, DirNode* parent){
        m_inode = new INode(name, 0, 0, FileModeTypeDir);
        m_parent = parent;
        m_lockCount = 0;
    }

    inline  INode* DirNode::getINode() { return m_inode; }
    inline  const std::string& DirNode::getName() { return m_inode->getName(); }
    inline  DirNode* DirNode::getParent() const { return m_parent; }
    inline  int DirNode::getLockCount() const { return m_lockCount; }

    inline  INodeIterator DirNode::getFilesBegin() { return m_files.begin(); }
    inline  INodeIterator DirNode::getFilesEnd() { return m_files.end(); }
    inline  DirNodeIterator DirNode::getChildrenBegin() { return m_children.begin(); }
    inline  DirNodeIterator DirNode::getChildrenEnd() { return m_children.end(); }

    //inline  void DirNode::setINode(const INode& inode) { m_inode = inode; }

    inline  void DirNode::setParent(DirNode* parent) { m_parent = parent; }
    inline  void DirNode::addFile(const INode& inode) { 
        //!DirNode is the owner of file inode, so we allocate new inode here
        INode* pNewINode = new INode(inode);
        m_files.push_back(pNewINode); 
    }
    inline  void DirNode::addFile(INode* pINode) {
        //take care, we take ownership of this object now.
        m_files.push_back(pINode);
    }

    inline  void DirNode::deleteFile(const std::string& filename, OperationHint hint) { 
        for ( INodeIterator iter = m_files.begin(); iter != m_files.end(); ++iter){
            if ( (*iter)->getName() == filename ) {
                //delete INode of file, I'm the owner of this INode.
                if( hint == FreeNodeInDelete) delete *iter;
                //erase item from container
                m_files.erase(iter);
                return;
            }
        }
    }

    inline  void DirNode::addChild(DirNode* node) { 
        m_children.push_back(node); 
        node->setParent(this);
    }
    inline  void DirNode::deleteChild(DirNode* node, OperationHint hint) { 
        for ( DirNodeIterator iter = m_children.begin(); iter != m_children.end(); ++iter){
            if ( *iter == node ) {
                //
                //#child DirNode object may not be deleted here! Be careful who is in charge!
                //
                if( hint == FreeNodeInDelete) delete *iter;

                m_children.erase(iter);
                return;
            }
        }
    }
    inline  void DirNode::incLock() { m_lockCount++; }
    inline  void DirNode::decLock() { m_lockCount--; }

    inline  INode* DirNode::findFile(const std::string& name) {
        for ( INodeIterator iter = m_files.begin(); iter != m_files.end(); ++iter){
            if ( (*iter)->getName() == name ) {
                return *iter;
            }
        }
        return NULL;
    }

    inline  DirNode* DirNode::findChild(const std::string& name) {
        for ( DirNodeIterator iter = m_children.begin(); iter != m_children.end(); ++iter){
            if ( (*iter)->getName() == name ) {
                return *iter;
            }
        }
        return NULL;
    }

    template<class Archive>
    void DirNode::save(Archive & ar, const unsigned int version) const {
        UNUSED(version);
        ar & m_inode;
        ar & m_files;
        ar & m_children;
    } 

    template<class Archive>
    void DirNode::load(Archive & ar, const unsigned int version) {
        UNUSED(version);
        ar & m_inode;
        ar & m_files;
        ar & m_children;

        //setup the children when load up
        for ( DirNodeIterator iter = m_children.begin(); iter != m_children.end(); ++iter){
            (*iter)->setParent(this);
        }
        m_lockCount = 0;
    } 


}

#endif /* _TFSMASTER_DIRNODE_HPP */
