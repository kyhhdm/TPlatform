/***************************************************************************
 ***************************************************************************

    Creator: Tom Barclay MSR

    Date: 1/17/96

    Copyright (c) 1995, 1996, 1998 Microsoft Corporation, All Right Reserved

****************************************************************************
****************************************************************************/

/*
    SortGen.EXE :  Sort Benchmark data generator

    This is a console application.
    It generates 100 byte records.
        The first 10 bytes is a random key of 10 printable characters.
        The next 10 bytes is the record number,0,1,... with leading blanks.
         The remaining bytes contain varying fields of
            "AAAAAAAAAA", "BBBBBBBBBB", ... "ZZZZZZZZZZ".
            The series repeats until it fills the record.
            The next record picks up where we left off on the previous record.

    This is the command syntax:

        SortGen.exe NumberOfRecordsToGenerate  OutputFileName

    Example generating 100mb

        SortGen.exe 1000000 sort100mb.dat

    Modification History:
    JNG         04/29/98    Modified Barclay's code to use stdio.h.
    Peng Liu    12/07/02    Modified Barclay's code to generate 100-bytes records instead of 101-bytes records.
    JNG         01/19/04    Modified Peng Liu code to use long long (64bit int) to handle more than 2 billion records. 

    historical note: LIMITATIONS:  Program works up to 2^31 records (about 200GB), before 31 bit record counter overflows.
					  We hope this will be a problem someday.
    This was a problem in 2004, and the problem was removed by using long-long datatype.
*/

// 20080503, port to linux, yzf

//
//  INCLUDE FILES
//
//#include "stdafx.h"

#include <stdlib.h>
#include <stdio.h>
#define  VERSION    "V1.1-4"

// larger than 2G
#define _FILE_OFFSET_BITS 64

/*************************************************************************
`* format of record: 10 bytes of key,	                                 *								
 *                   10 bytes of serial number,                          *
 *                   80 bytes of data                                    *
 *************************************************************************/
struct record
{ 
    char    sortkey[10] ;
    char    recnum[10];
    char    txtfld[80];
};
//
// GLOBALS
//
const	int	RecordSize          = (sizeof(struct record));  // 100 bytes
const	int	RecordsPerBuffer    = 1<<16;					// 64 K records per buffer
const	int	BufferSize          = 100 * (1<<16);			// about 512KB of IO at a time.

long long	MaxRecord			=   1;						// # records to generate
char		*OutFileName		=   "c:\\temp.dat";			// Name of file to create
 
/*************************************************************************
 *                                                                       *
 * My random number generator (I trust it).                              *
 *                                                                       *
 *************************************************************************/
unsigned my_rand(void)
    {
    static unsigned      rand;
    return (rand = rand * 3141592621 + 663896637);
    }

/*************************************************************************
 *                                                                       *
 * Generate a random key of 10 printable characters                      *
 *                                                                       *
 *************************************************************************/
void rand_key(char key[10])
{
    unsigned    temp;

    // generate a random key consisting of 95 ascii values, ' ' to '~'
    temp = my_rand();
    temp /= 52;                             // filter out lower order bits
    key[3] = ' ' + (temp % 95);
    temp /= 95;
    key[2] = ' ' + (temp % 95);       
    temp /= 95;
    key[1] = ' ' + (temp % 95);
    temp /= 95;
    key[0] = ' ' + (temp % 95);
    
    temp = my_rand();
    temp /= 52;                             // filter out lower order bits 
    key[7] = ' ' + (temp % 95);
    temp /= 95;
    key[6] = ' ' + (temp % 95);
    temp /= 95;
    key[5] = ' ' + (temp % 95);
    temp /= 95;
    key[4] = ' ' + (temp % 95);
    
    temp = my_rand();
    temp /= 52 * 95 * 95;                   // filter out lower order bits 
    key[9] = ' ' + (temp % 95);
    temp /= 95;
    key[8] = ' ' + (temp % 95);
}

/*************************************************************************
 *                                                                       *
 * Generate a random record.                                             *
 *                                                                       *
 *************************************************************************/
void gen_rec(struct record *rp)
{
    static  int    current;
    char        *sptr;
    static char nxtchar = 'A';
    int         i, j;
    
    rand_key(rp->sortkey) ;                 // Get 10 byte sort key     
    sprintf(rp->recnum, "%10d", current++);
    sptr = rp->txtfld ;
    for( i=0; i < 8; i++)
        {
        for( j=0; j < 10; j++ )
            *sptr++ = nxtchar ;
        nxtchar++;
        if( nxtchar > 'Z' ) nxtchar = 'A';
        }
    sptr[-2] = '\r';
    sptr[-1] = '\n';
}

/*************************************************************************
 *                                                                       *
 * Fill the output buffer with records                                   *
 * Buffer holds an integer number of whole records                       *
 *  (buffer size is a multiple of record size)                           *
 *                                                                       *
 *************************************************************************/
int FillBuffer(char *Buffer, int BufferSize, long long Record, long long MaxRecord)
    {   
    int RecordCount = 0;
    do  {
        gen_rec((struct record *) &Buffer[RecordCount*RecordSize]);
        Record++;
        RecordCount++;
        }while ((RecordCount < RecordsPerBuffer) && (Record < MaxRecord));

    return (RecordCount);
}
 
/*************************************************************************
 *                                                                       *
 * Online manual                                                         *
 *                                                                       *
 *************************************************************************/
void usage()
{
    fprintf(stderr,"Usage: \n\tSortGen <#rows> <filename> \n");
}

/*************************************************************************
 *                                                                       *
 * Main routine of data generator                                        *
 *                                                                       *
 *************************************************************************/
 
main (int argc, char * argv[])
{
    long long   GeneratedRecords = 0;       // Records generated so far
    long long   DesiredRecords   = 0;       // Target number of records
    long        BufferRecords    = 0;       // Records in buffer
    char        *Buffer  ;                  // output buffer    
    long        WriteCount       = 0;       // bytes written by this IO  
    long        error            = 0;       // error flag
	FILE        * OutFile		 ;			// Output file
    
    /*********************************************************************
     *                                                                   *
     * Decode parameters (record count and file name)                    *
     *                                                                   *
     *********************************************************************/ 
    if (argc < 2)
        { usage(); return(1); }
    argc--;									// Don't count program name  
    argv++;
    if (argc > 0)
        {
        DesiredRecords = atoll(argv[0]);
        argc--;
        argv++;
        }
    if (argc > 0)
        {
        OutFileName = argv[0];
        argc--;
        argv++;
        }
    /************************************************************************
     *                                                                      *
     * Put out greeting                                                     *
     *                                                                      *
     ************************************************************************/
    fprintf(stderr,"SortGen - Sort Data Generator version %s\n", VERSION);
    fprintf(stderr,"\tGenerating %lld sort test data records to file %s \n",
                                                DesiredRecords, OutFileName);

    /************************************************************************
    /*                                                                      *
    /*      Open Output File and allocate output buffer                     *
    /*                                                                      *
    /************************************************************************/
    Buffer = (char *)malloc( BufferSize ) ;
    if( Buffer  == NULL  )
        {
        fprintf(stderr,"? Couldn't allocate the I/O buffer\n");
        error = 1;  goto common_exit;
        }

    OutFile = fopen( OutFileName, "w+b");
    if( OutFile == NULL )
        {
        fprintf(stderr,"? Error creating file %s\n", OutFileName) ;
        error = 1;  goto common_exit;
        }

    /************************************************************************
    /*                                                                      *
    /*      Main Loop                                                       *
    /*      Fill the buffer write it out                                    *
    /*                                                                      *
    /************************************************************************/
    while( GeneratedRecords < DesiredRecords)
        {
        BufferRecords = FillBuffer(Buffer, BufferSize, GeneratedRecords, DesiredRecords);
        WriteCount = (long) fwrite( Buffer, 1, (BufferRecords * RecordSize), OutFile);
        if( WriteCount != (BufferRecords * RecordSize))
            {fprintf(stderr,"? Error %d on write to outfile.\n",ferror(OutFile));
            error = 1; goto common_exit;
            }
        GeneratedRecords += BufferRecords ;
        }

    /************************************************************************
    /*                                                                      *
    /*      All Done                                                        *
    /*      close output file; and exit                                     *
    /*                                                                      *
    /************************************************************************/
common_exit:
    fprintf(stderr, "\nCompleted writing %lld Records to file %s\n",
                                                DesiredRecords,   OutFileName) ;
    fclose(OutFile) ;                   // close output file         
    free(Buffer);                       // free record buffer
    if (error)                          // delete output file on error
        remove( OutFileName);           //
    return(error);                      // return status code
}                                       // End of SortGen.c
