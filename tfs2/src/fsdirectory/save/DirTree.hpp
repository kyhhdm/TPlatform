/** @file DirectoryTree.hpp
 * DirectoryTree implements the filesystem hierachy by tree structure.
 *
 * @author PengBo
 * @date 18 7 2007
 *
 *
 */
#ifndef _TFSMASTER_DIRECTORYTREE_HPP
#define _TFSMASTER_DIRECTORYTREE_HPP 

#include "common/IceGenerated.hpp"
#include "common/Types.hpp"
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

namespace tfs {

    class DirNode;
    class INode;

    class DirTree {

    public:
        //1.constructors
        /** Construct from image file.
         * @param [in] imageFileName : 
         * @throws IOException (image files open/load failure)
         */    
        DirTree(const std::string imageFileName);

        /** Construct from root dirnode.
         *
         * @param [in] DirNode* : pointer to the root node, 
         *  create default Root Node if pDirNode == NULL
         */    
        DirTree(DirNode *pDirNode);

        /** Construct a null tree.
         */    
        DirTree();

        ~DirTree();

        /** Find the given directory node by full path name
         * it's a basic operation in name space managment
         * 
         * @param [in] pathName 
         * @throws
         * @return DirNode* or NULL for false
         */
        DirNode* findDirNode(const std::string &pathName) const;

        /** Find the given inode by full path name, either Directory or File
         * it's a basic operation in name space managment
         * 
         * @param [in] name 
         * @throws
         * @return INode* or NULL for false
         */
        INode* findINode(const std::string &name) const;


        /** Create a serail of dirctory nodes by full path name
         * create all midlle nodes if necessary
         * 
         * @param [in] dirname: treat all name before last "/" as directory name
         * @throws
         * @return DirNode* for the last new cretaed node or NULL for false 
         */    
        DirNode* createDirNodes(const std::string& PathName);

        /** Mode a directory node from source place to destination place by name.
         *
         * @param [in] src: source 
         * @param [in] dst: destination
         * @throws
         * @return : 
         */    
        bool moveDirNode(const DirNode* src, const DirNode* dst);

        /** Delete a directory node.
         * 
         * @param [in] DirNode* node 
         * @throws
         * @return : 
         */    
        bool deleteDirNode(DirNode* node);

        /** Add read lock on the dir nodes in the path.
         *
         * @param [in] PathName 
         * @throws
         * @return : 
         */    
        bool lockPath(const std::string& PathName);

        /** Remove read lock on the dir nodes in the path.
         *
         * @param [in] PathName 
         * @throws
         * @return : 
         */    
        bool unlockPath(const std::string& PathName);                 

        /** Accessors
         */
        DirNode* getRoot() const;
        void setRoot(DirNode* pRootNode);

    private:
        DirNode*    m_pRoot;

        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive & ar, const unsigned int version);


    };

    // inline implementation =================================
    template<class Archive>
    inline void DirTree::serialize(Archive & ar, const unsigned int version) {
        UNUSED(version);
        ar & m_pRoot;
    }        

    inline DirNode* DirTree::getRoot() const {
        return m_pRoot;
    }

    inline void DirTree::setRoot(DirNode* pRootNode) {
        m_pRoot = pRootNode;
    }




}

#endif /* _TFSMASTER_DIRECTORYTREE_HPP */
