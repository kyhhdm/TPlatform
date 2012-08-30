// hello.hpp
#include <fuse-2.7.1/fusexx.hpp>

#include <string>

class TfsHello : public fusexx::fuse<TfsHello> {
        public:
                TfsHello (); // Constructor

                // Overload the fuse methods
                static int getattr (const char *, struct stat *);
                static int readdir (const char *, void *, fuse_fill_dir_t, off_t, struct fuse_file_info *);
                static int open (const char *, struct fuse_file_info *);
                static int read (const char *, char *, size_t, off_t, struct fuse_file_info *);
       
        private:
                // Private variables
                // Notice that they aren't static, i.e. they belong to an instantiated object
                std::string m_strHelloWorld;
                std::string m_strPath;
};
