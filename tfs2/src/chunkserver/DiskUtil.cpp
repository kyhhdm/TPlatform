
#include <sys/vfs.h>
#include <error.h>
#include "DiskUtil.hpp"
#include <string>
#include <vector>

using namespace std;

long long DiskUtil::getAvailSpace(const string & path,const std::string& flag)
{

    long long bavail;
    struct statfs fs;
    if(statfs(path.c_str(),&fs)<0)
    {
        //        perror("statfs");
        return -1;
    }

//     blocks = fs.f_blocks;
//     bfree=fs.f_bfree;
    bavail = fs.f_bavail;

    long long result_byte =  (bavail)*(fs.f_bsize);
    
    //  if(fs.f_type==EXT2_SUPER_MAGIC)
//     {
//         printf("Total size of / is %f G\n",blocks*fs.f_bsize/Gsize);
//         printf("Free size of / is %f G\n",bfree*fs.f_bsize/Gsize);
//         printf("Avail size of / is %f G\n",(bavail)*(fs.f_bsize)/Gsize);

//     }
    
    if (flag == "M"){
        return result_byte/(1024*1024);
    }else if (flag == "G"){
        return result_byte/(1024*1024*1024);
    }else if (flag == "K"){
        return result_byte/(1024);
    }else if (flag == "B"){
        return result_byte/(1024*1024);
    }
    
    return -1;
}
