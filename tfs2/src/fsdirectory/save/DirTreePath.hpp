/** @file DirTreePath.hpp
 * DirTreePath implements the iteration support on Directory Tree.
 *
 * @author PengBo
 * @date 20070803
 *
 *
 */
#ifndef _TFSMASTER_TREEPATH_HPP
#define _TFSMASTER_TREEPATH_HPP 

#include "Path.hpp"
#include "common/IceGenerated.hpp"
#include "common/Types.hpp"

namespace tfs {

    class DirNode;
    class DirTree;

    /** Iterator supporting algorithms of tree walk by according given path name,
     */  
    class DirTreePath{
        DirTree*    m_pTree; 
        Path     m_path;
    public:
        class iterator{
            friend class DirTreePath;

            DirNode*    m_pDirNode;
            Path::PathIterator m_pathIter;
            bool    m_matchFlag;

        public:
            iterator(DirNode* dirNode, Path::PathIterator iter);
            iterator();
            ~iterator();

            DirNode* operator*();

            iterator& operator++();

            bool operator!=(const iterator& right);

            //accessors
            /** Get the path name Iterator object 
             *
             * @return PathIterator
             */    
            Path::PathIterator getPathIterator() const;

            /** Get path node name in current path iterator
             *
             * @return node name
             */    
            const std::string& getNodeName() const;

            /** Setup a DirNode object presenting for current path node in the tree
             *
             * @param [in] pDirNode : DirNode object for current node
             */    
            void setDirNode(DirNode* pDirNode);

            /** Match to check if this node match search path node
             *  
             */    
            bool match();

            /** Clear match state , prepareing to continue iteration
             *
             */               
            void clear();

        };

        /** Constructor 
         *
         * @param [in] dirTree  : the tree object
         * @param [in] pathName : the given path that will be iterated
         * @throws
         */    
        DirTreePath(const DirTree* pDirTree, const std::string& pathName);

        ~DirTreePath();
        
        /** Get the start pointer of iteration
         *
         * @param [in]
         * @throws
         * @return start iterator 
         */    
        iterator begin();

        /** Get the end pointer of iteration
         *
         * @param [in]
         * @throws
         * @return end iterator 
         */    
        iterator end();
    };

    // inline implementation =================================
    inline DirTreePath::iterator::iterator() {
        m_matchFlag = true;
    }

    inline DirTreePath::iterator::~iterator() { }

    inline DirTreePath::iterator::iterator(DirNode* dirNode, Path::PathIterator iter){
        m_pDirNode = dirNode;
        m_pathIter = iter;
        m_matchFlag = true;
    }

    inline DirNode* DirTreePath::iterator::operator*() {
        return m_pDirNode;
    }

    inline DirTreePath::iterator& DirTreePath::iterator::operator++() {
        DirNode* pDirNode = NULL;
        //
        // Notes: path stores pure directory nodes and access from iterator
        //  /tfs/home/dir/          => / tfs home dir .
        //  /tfs/home/dir/file.dat  => / tfs home dir .
        //  /tfs/home/dir           => / tfs home .
        //
        
        ++m_pathIter;

        //if ( *m_pathIter == Path::RootString ) {
        //    pNode = this->m_root;
        //}
        if ( *m_pathIter == Path::CurDirString ) {
            return *this;
        }
        else if ( *m_pathIter == Path::ParentDirString ) {
            pDirNode = m_pDirNode->getParent();
        }
        else {
            pDirNode =  m_pDirNode->findChild(*m_pathIter);
        }

        if(pDirNode) {
            m_matchFlag = true;
            m_pDirNode = pDirNode;
        }
        else{
            m_matchFlag = false;
        }

        return *this;        
    }

    inline bool DirTreePath::iterator::operator!=(const DirTreePath::iterator& right) {
        return ( right.getPathIterator() != m_pathIter);
    }

    inline bool DirTreePath::iterator::match() {
        //if ( *m_pathIter == Path::ParentDirString || *m_pathIter == Path::CurDirString) return true;
        //else return (m_pDirNode->getName() == *m_pathIter);
        return m_matchFlag;
    }

    inline Path::PathIterator DirTreePath::iterator::getPathIterator() const { return m_pathIter;}
    inline const std::string& DirTreePath::iterator::getNodeName() const { return *m_pathIter;}
    inline void DirTreePath::iterator::setDirNode(DirNode* pDirNode) { m_pDirNode = pDirNode; }

    inline void DirTreePath::iterator::clear() { m_matchFlag = true;}
}

#endif /* _TFSMASTER_TREEPATH_HPP */
