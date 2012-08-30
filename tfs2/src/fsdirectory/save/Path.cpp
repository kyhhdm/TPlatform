/** @file Path.cpp
 *
 * @author PengBo
 * @date 20070802
 *
 *
 */

#include "fsdirectory/Path.hpp"
#include <vector>

const std::string tfs::Path::RootString ="/";
const std::string tfs::Path::CurDirString =".";
const std::string tfs::Path::ParentDirString = "..";

using namespace tfs;
using namespace std;

Path::Path(const std::string name):m_path(name) 
{
    //#BUGFIX item#6, report by tsunami
    // ROOT path problem
    // [1].boost::path works strange for path start not with "/" 
    //     "//home/tfs//hah.doc" ==> "//home" "/" "tfs" hah.doc"
    // => deprecate all redundant "/" prefix
    // [2].root path string like "/" "//" will be treated as leaves in boost
    //     so we check if the leaf start with "/", then it should be Root
    // =>
    // [3].last / with be treat as .
    //     "/home/tfs/subdir/"  ==> "/ home tfs subdir ."
    //
    int startRootPos = 0;
    while (startRootPos < name.size() && ('/' == name[startRootPos])) {
        ++startRootPos;
    }

    if(startRootPos > 0 ){
        m_path = PathType(std::string(name, startRootPos - 1));
    }

    m_filename = m_path.leaf();
    if ( 0 == m_filename.find(RootString)) {
        m_filename = "";
        m_dir = RootString;
        m_path = PathType(RootString);
    }
    else{
        if ( m_filename == CurDirString ) {
            m_filename = "";
        }
            
        //call remove_leaf() will destory m_filename, so it must be called early
        PathType pureDir = m_path.remove_leaf();
        m_dir = pureDir.directory_string();
    
        //do normalize, deal with "." and ".." inside m_dir
        vector<string> normalizedPath;

        PathIterator iter;
        for( iter = pureDir.begin(); iter != pureDir.end(); ++iter){
            if(*iter == ParentDirString) {
                if( normalizedPath.size() > 1 ) normalizedPath.pop_back();
            }
            else if(*iter == CurDirString){
                // do nothing
            }
            else{
                normalizedPath.push_back(*iter);
            }
        }
        
        m_dir = "";
        for ( int i = 0; i < normalizedPath.size() ; i++){
            m_dir += normalizedPath[i];
            if(i > 0) m_dir += "/";
        }
        //m_dir += m_filename;
    
        //m_path = PathType(m_dir + m_filename );
        m_path = PathType(m_dir);
    }
    
}


