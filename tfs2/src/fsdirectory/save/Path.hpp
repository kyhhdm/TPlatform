/** @file Path.hpp
 * Path Class implements path name parser interface.
 *
 * @author PengBo
 * @date 2 8 2007
 *
 * Notes: it should be move to util module someday.
 *
 *
 */
#ifndef _TFS_PATH_HPP
#define _TFS_PATH_HPP 

// use boost filesystem ver 1.34.1
#include <boost/filesystem/path.hpp>

namespace tfs {

    class Path {
    

    public:
        typedef boost::filesystem::path PathType;
        typedef boost::filesystem::path::iterator PathIterator;

        static const std::string RootString;
        static const std::string CurDirString;
        static const std::string ParentDirString;
        
        /** Construct
         * @param [in] name : 
         * @throws
         */    
        Path(const std::string name);

        Path();
        ~Path();

        /** Check if the path name contains filename part
         */
        bool isPureDir() const;

        /** Get full path name
         */
        std::string getFullPathName() const;

        /** Get pure directory name
         */
        const std::string& getDirName() const;

        /** Get file name
         */
        const std::string& getFileName() const;

        /** iterator through directory nodes
         */
        PathIterator begin();
        PathIterator end();

    private:
        //stores dir only, filename deprecated in PathType object
        PathType m_path;
        std::string m_dir;
        std::string m_filename;
    };

    // inline implementation =================================
    inline Path::Path() {
    }

    inline Path::~Path() {
    }

    inline bool Path::isPureDir() const {
        return ( (m_dir.size() != 0) && (m_filename.size() == 0) );
    }

    inline const std::string& Path::getDirName() const {
        return m_dir;  
    }

    inline const std::string& Path::getFileName() const {
        return m_filename;  
    }

    inline std::string Path::getFullPathName() const {
        return m_dir + m_filename;
    }

    inline Path::PathIterator Path::begin() {
        return m_path.begin();
    }
    inline Path::PathIterator Path::end() {
        return m_path.end();
    }

}

#endif /* _TFS_PATH_HPP */
