/** 
 * @file MapReduceJob.ice
 * 
 * @author YangZhifeng
 * @date 28 11月 2007
 */
#ifndef _MAPREDUCEJOB_ICE
#define _MAPREDUCEJOB_ICE 1

module mapreduce
{
    module slice
    {
        struct MapReduceJob
        {
            /// TFS file as input
            string inputFile;
            /// TFS file as output
            string outputFile;
            /// replication of the output files
            int outputReplication;
            /// shared object file
            string soFile;
            /// the number of map tasks, ingored, use the number of chunks
            int mapTaskNum;
            /// the number of reduce tasks, ignored, use the number of workers
            int reduceTaskNum;
            /// whether do the local combine after map
            bool doLocalCombine;
            /// whether do the group by sort
            bool doGroupBySort;
            /// whether concat output files into one file when the whole job done
            bool doConcatOutputs;
            // mapreduce core settings
            string mapperClass;
            string reducerClass;
            string mapperOutKeyClass;
            string mapperOutValueClass;
            // following group are optional
            string mapperInKeyClass;
            string mapperInValueClass;
            string mapperRecordReaderClass;
            string reducerOutKeyClass;
            string reducerOutValueClass;
            string reducerRecordWriterClass;
 
        };
    };
};


#endif /* _MAPREDUCEJOB_ICE */

// Local Variables: ***
// mode:c++ ***
// End: ***
