/** @file Exceptions.ice
 * Exceptions which may be thrown by these Ice defined interface 
 * @author YangZhifeng
 * @date 13  3  2007
 */
#ifndef _EXCEPTIONS_ICE
#define _EXCEPTIONS_ICE 1

module tfs
{
    module slice
    {
        /// root of all our exceptions
        exception GenericException
        {
            /// specific reason why you throw this exception
            string reason;
        };

        exception NoSuchFileOrDir extends GenericException
        {
        };

        /// local filesystem i/o error
        exception IOError extends GenericException
        {
        };

        exception LockFail extends GenericException
        {
        };
           
        exception OffsetOutOfRange extends GenericException
        {
        };
            
        exception NoChunkAllocated extends GenericException
        {
        };

        exception NoSuchChunk extends GenericException
        {
        };
        exception FileOrDirAlreadyExists extends GenericException
        {
        };
        exception UnknownChunkServer extends GenericException
        {
        };
        exception ReplicationOutOfRange extends GenericException
        {
        };
        exception ChunkSizeOutOfRange extends GenericException
        {
        };
        
        exception InvalidFileOrDirName extends GenericException
        {
        };
        exception JournalException extends GenericException
        {
        };
        
    };
};

#endif /* _EXCEPTIONS_ICE */

// Local Variables: ***
// mode:c++ ***
// End: ***
