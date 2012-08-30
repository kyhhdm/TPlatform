/** 
 * @file TestLockTable.hpp
 * .
 * 
 * @author Chen rishan
 * @date 2007-08-31
 */
#ifndef _TESTLOCKTABLE_HPP
#define _TESTLOCKTABLE_HPP 1

#include <cxxtest/TestSuite.h>
#include "fsdirectory/LockTable.hpp"

using namespace std;
using namespace tfs;

class TestLockTable: public CxxTest::TestSuite
{
public:
    void testInvalidParameter()
    {
        LockTable lockTable;
        LockType lockType;

        //setup 
        string filename1("/root/dd/file1.dat");
        string filename2("/root/dd/file2.dat");
        string filename3("/root/dd/file3.dat");

        string holder1("tsunami");
        string holder2("pb");

        lockType = ReadLock;

        //delete empty table
        TS_ASSERT( false == lockTable.deleteItem(filename1, holder1));
        TS_ASSERT( 0 == lockTable.deleteItem(holder1));

        //add null filename or holder
        TS_ASSERT( false == lockTable.addItem("", holder1, lockType));
        TS_ASSERT( false == lockTable.addItem(filename1, "", lockType));
        TS_ASSERT( false == lockTable.addItem("", "", lockType));

        //normal setup
        TS_ASSERT( true == lockTable.addItem(filename1, holder1, lockType));
        TS_ASSERT( true == lockTable.addItem(filename2, holder1, lockType));
        TS_ASSERT( true == lockTable.addItem(filename1, holder1, lockType));
        TS_ASSERT( true == lockTable.addItem(filename1, holder2, lockType));

        //delete item test
        TS_ASSERT( false == lockTable.deleteItem("", holder1));
        TS_ASSERT( false == lockTable.deleteItem(filename1, ""));

        TS_ASSERT( false == lockTable.deleteItem(""));
    }

    void testNormalReadLock(void)
    {   
        LockTable lockTable;
        LockType lockType;

        //delete first
        string filename1("/root/dd/file1.dat");
        string filename2("/root/dd/file2.dat");
        string filename3("/root/dd/file3.dat");
        string filename4("/root/dd/file4.dat");

        string holder1("tsunami");
        string holder2("pb");
        string holder3("yzf");

        lockType = ReadLock;

        //normal setup
        TS_ASSERT( true == lockTable.addItem(filename1, holder1, lockType));
        TS_ASSERT( true == lockTable.addItem(filename2, holder1, lockType));
        TS_ASSERT( true == lockTable.addItem(filename1, holder1, lockType));
        TS_ASSERT( true == lockTable.addItem(filename1, holder2, lockType));
        TS_ASSERT( true == lockTable.addItem(filename3, holder2, lockType));
        TS_ASSERT( true == lockTable.addItem(filename3, holder2, lockType));
        TS_ASSERT( true == lockTable.addItem(filename3, holder2, lockType));
        TS_ASSERT( true == lockTable.addItem(filename4, holder3, lockType));

        //delete
        TS_ASSERT(true == lockTable.deleteItem(filename1, holder1));
        TS_ASSERT(true == lockTable.deleteItem(filename1, holder1));
        TS_ASSERT(true == lockTable.deleteItem(filename2, holder1));
        TS_ASSERT(true == lockTable.deleteItem(filename3, holder2));
        TS_ASSERT(true == lockTable.deleteItem(filename1, holder2));

        //client dead
        TS_ASSERT( 0 == lockTable.deleteItem(holder1));
        TS_ASSERT( 2 == lockTable.deleteItem(holder2));
        TS_ASSERT( 1 == lockTable.deleteItem(holder3));

    }

    //--------------------------------
    void testWriteLock(void)
    {
        LockTable lockTable;
        LockType lockType;

        //delete first
        string filename1("/root/dd/file1.dat");
        string filename2("/root/dd/file2.dat");
        string filename3("/root/dd/file3.dat");
        string filename4("/root/dd/file4.dat");

        string holder1("tsunami");
        string holder2("pb");

        lockType = ReadLock;

        //normal setup
        TS_ASSERT( true == lockTable.addItem(filename1, holder1, lockType));
        TS_ASSERT( true == lockTable.addItem(filename2, holder1, lockType));
        TS_ASSERT( true == lockTable.addItem(filename1, holder1, lockType));
        TS_ASSERT( true == lockTable.addItem(filename1, holder2, lockType));
        TS_ASSERT( true == lockTable.addItem(filename3, holder2, lockType));
        TS_ASSERT( true == lockTable.addItem(filename3, holder2, lockType));
        TS_ASSERT( true == lockTable.addItem(filename3, holder2, lockType));


        //add WriteLock on opened file
        TS_ASSERT( false == lockTable.addItem(filename1, holder1, WriteLock));
        TS_ASSERT( false == lockTable.addItem(filename1, holder2, WriteLock));
        TS_ASSERT( false == lockTable.addItem(filename3, holder1, WriteLock));

        //
        TS_ASSERT( true == lockTable.addItem(filename4, holder1, WriteLock));
        TS_ASSERT( false == lockTable.addItem(filename4, holder1, ReadLock));
        TS_ASSERT( false == lockTable.addItem(filename4, holder2, ReadLock));

        //delete
        TS_ASSERT( 4 == lockTable.deleteItem(holder1));
        TS_ASSERT( true == lockTable.deleteItem(filename1, holder2));
        TS_ASSERT( false == lockTable.deleteItem(filename1, holder2));
        TS_ASSERT( true == lockTable.addItem(filename4, holder2, WriteLock));
        TS_ASSERT( true == lockTable.deleteItem(filename3, holder2));
        TS_ASSERT( 3 == lockTable.deleteItem(holder2));

    }
        
};


#endif /* _TESTLOCKTABLE_HPP */
