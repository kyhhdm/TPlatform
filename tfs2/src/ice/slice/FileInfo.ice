/* 
 * @(#)FileInfo.ice
 * AUTHOR: YangZhifeng
 * CREATE DATE: 21 5 2007
 * DESCRIPTION: 
 */
/** @file
 * 
 * @author YangZhifeng
 * @date 21  5 2007
 */
#ifndef _FILEINFO_ICE
#define _FILEINFO_ICE 1

module tfs
{
    module slice
        {
            const short FileModeTypeDir = 01000;
            const short FileModeOwnerRead = 0400;
            const short FileModeOwnerWrite = 0200;
            const short FileModeOwnerExec = 0100;
            const short FileModeGroupRead = 0040;
            const short FileModeGroupWrite = 0020;
            const short FileModeGroupExec = 0010;
            const short FileModeOtherRead = 0004;
            const short FileModeOtherWrite = 0002;
            const short FileModeOtherExec = 0001;

            /**
             * struct to store the information about a file.
             * 
             */
            struct FileInfo
            {
                /// the value of `flag' must `bit or' of the above constants
                short flag;
                /// the name of the file or dir
                string name;
                /// create time of the file or dir
                int createTime;
                /// size of the file, invalid if it is a dir
                long size;
                /// replication of the file, invalid if it is a dir
                short replication;
                /// max chunk size of the file, invalid if it is a dir
                long chunkSize;
            };
            
            sequence<FileInfo> FilesInfo;
        };

};


#endif /* _FILEINFO_ICE */

// Local Variables: ***
// mode:c++ ***
// End: ***
