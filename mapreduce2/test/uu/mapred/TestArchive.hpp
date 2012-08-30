/** 
 * @file TestArchive.hpp
 * .
 * 
 * @author Peng Bo
 * @date 2008-04-07
 */
#ifndef _TEST_MAPREDUCE_ARCHIVE_HPP
#define _TEST_MAPREDUCE_ARCHIVE_HPP

//#define TEST_TFS

#include <cxxtest/TestSuite.h>
#include <cxxtest/GlobalFixture.h>
#include "FileStreamLocal.hpp"
#include "ArchiveBuffer.hpp"
#include "Archive.hpp"

#ifdef TEST_TFS 
#include "FileStreamTfs.hpp"
#endif

#include "MapReduceException.hpp"
#include "util/Logger.hpp"
#include <time.h>
#include <string>
#include <iostream>
#include "boost/filesystem.hpp"

using namespace std;
using namespace mapreduce;
using namespace boost::filesystem;
  
class ArchiveFixture : public CxxTest::GlobalFixture{
    public:    
    bool setUpWorld() { 

        return true; 
    }

    bool tearDownWorld() { 
        return true; 
    }

    bool setUp() { 
        return true; 
    }    
    bool tearDown() { 
        return true; 
    }
};


static ArchiveFixture ArchiveFixture;


//=====================================================
class UserType{
public:
    int id;
    float weight;
    string name;
    char* message;  
    
    UserType(int _id, float _weight, char* _name, char* _message):
        id(_id),weight(_weight),name(_name),message(_message)
    {
    }

    bool operator==(UserType& other){
        return ((id == other.id) && (weight==other.weight) && 
            !strcmp(message, other.message) && (name == other.name));
    }
};

Archive& operator>>(Archive& ar, UserType*& data)
{
    int *pId;
    float *pWeight;
    char* *pMessage = &data->message; 
    string* pName = &data->name;

    ar >> pId;
    ar >> pWeight;
    //ar >> (&data->name);
    ar >> pName;
    ar >> pMessage;
    
    data->id = *pId;
    data->weight = *pWeight;
    return ar;
}

Archive& operator<<(Archive& ar, UserType& data){
    ar << data.id << data.weight << data.name << data.message;
    return ar;

}
//=====================================================

class TestArchive: public CxxTest::TestSuite
{

    //==========helper functions=================
    FileStream* createFileStream(bool local, string& filename, FileStream::OpenMode openMode, bool openOnDemand)
    {
#ifdef TEST_TFS 
        if(local){
            return new FileStreamLocal(filename, openMode, openOnDemand);
        }
        else{
            return new FileStreamTfs(filename, openMode, openOnDemand);
        }
#else
            return new FileStreamLocal(filename, openMode, openOnDemand);
#endif

    }

    void doTestNormalArchiving(bool streamType, const char* rootDirectory)
    {
        FileStream* readStream;
        FileStream* writeStream;
        Archive* archive;

        remove_all(rootDirectory);
        create_directory( rootDirectory );
        string filename = string(rootDirectory) + "/TestArchive.dat";

        //write a file
        TS_ASSERT_THROWS_NOTHING( writeStream = createFileStream(streamType,filename, FileStream::Append, false) );

        //test a short non-auto clear buffer
        archive = new Archive(0, false);

        TS_ASSERT_THROWS_NOTHING(archive->open(writeStream));

        //prepare data
        int key = 0;
        char *data[]={
            "123456789abcdef",
            "23456789abcdef1",
            "3456789abcdef12",
            "456789abcdef123",
            "56789abcdef1234",
            "6789abcdef12345",
            "789abcdef123456",
            "89abcdef1234567XXX"
        };

        for(key = 0 ; key < sizeof(data)/sizeof(char*); key++){
            *archive << key << data[key];
            archive->getBuffer()->commitAppendRecord();
        }

        TS_ASSERT_THROWS_NOTHING( archive->close()); 

        //read and check
        TS_ASSERT_THROWS_NOTHING( readStream = createFileStream(streamType, filename, FileStream::ReadOnly, false) );
        char buffer[64], i;
        for(i = 0 ; i < sizeof(data)/sizeof(char*); i++){
            TS_ASSERT(sizeof(key) == readStream->read((char*)&key, sizeof(key)));
            TS_ASSERT(strlen(data[i])+1 == readStream->read((char*)buffer, strlen(data[i])+1));
            TS_ASSERT_SAME_DATA(buffer, data[i] , strlen(data[i])+1);
        }
        TS_ASSERT(0 == readStream->read((char*)buffer, 20));

        TS_ASSERT_THROWS_NOTHING( readStream->close()); 

        
        //test read archive
        delete archive;
        archive = new Archive(35, false);
        TS_ASSERT_THROWS_NOTHING( readStream->open()); 

        TS_ASSERT_THROWS_NOTHING(archive->open(readStream));

        char* value;
        char** pValue = &value;
        int* pKey;
        for(i = 0 ; i < sizeof(data)/sizeof(char*); i++){
            //(*archive) >> (&key) >> value;
            *archive >> pKey >> pValue;
            TS_ASSERT( *pKey == i);
            TS_ASSERT_SAME_DATA(value, data[i] , strlen(data[i])+1);
        }

        TS_ASSERT_THROWS_NOTHING( archive->close()); 
        delete archive;
    }

    void doTestStringArchiving(bool streamType, const char* rootDirectory)
    {
        FileStream* readStream;
        FileStream* writeStream;
        Archive* archive;

        remove_all(rootDirectory);
        create_directory( rootDirectory );
        string filename = string(rootDirectory) + "/TestArchive.dat";

        //write a file
        TS_ASSERT_THROWS_NOTHING( writeStream = createFileStream(streamType,filename, FileStream::Append, false) );

        //test a short non-auto clear buffer
        archive = new Archive(0, false);

        TS_ASSERT_THROWS_NOTHING(archive->open(writeStream));

        //prepare data
        int key = 0;
        char *data[]={
            "123456789abcdef",
            "23456789abcdef1",
            "3456789abcdef12",
            "456789abcdef123",
            "56789abcdef1234",
            "6789abcdef12345",
            "789abcdef123456",
            "89abcdef1234567XXX"
        };

        for(key = 0 ; key < sizeof(data)/sizeof(char*); key++){
            *archive << key << data[key];
            archive->getBuffer()->commitAppendRecord();
        }

        TS_ASSERT_THROWS_NOTHING( archive->close()); 

        //read and check
        TS_ASSERT_THROWS_NOTHING( readStream = createFileStream(streamType, filename, FileStream::ReadOnly, false) );
        char buffer[64], i;
        for(i = 0 ; i < sizeof(data)/sizeof(char*); i++){
            TS_ASSERT(sizeof(key) == readStream->read((char*)&key, sizeof(key)));
            TS_ASSERT(strlen(data[i])+1 == readStream->read((char*)buffer, strlen(data[i])+1));
            TS_ASSERT_SAME_DATA(buffer, data[i] , strlen(data[i])+1);
        }
        TS_ASSERT(0 == readStream->read((char*)buffer, 20));

        TS_ASSERT_THROWS_NOTHING( readStream->close()); 


        //test read archive
        delete archive;
        archive = new Archive(35, false);
        TS_ASSERT_THROWS_NOTHING( readStream->open()); 

        TS_ASSERT_THROWS_NOTHING(archive->open(readStream));

        string value;
        string* pValue = &value;
        int* pKey;
        for(i = 0 ; i < sizeof(data)/sizeof(char*); i++){
            *archive >> pKey >> pValue;
            TS_ASSERT( *pKey == i);
            TS_ASSERT_SAME_DATA(pValue->c_str(), data[i] , strlen(data[i])+1);
        }

        TS_ASSERT_THROWS_NOTHING( archive->close()); 
        delete archive;
    }

    void doTestUserTypeArchiving(bool streamType, const char* rootDirectory)
    {
        FileStream* readStream;
        FileStream* writeStream;
        Archive* archive;

        remove_all(rootDirectory);
        create_directory( rootDirectory );
        string filename = string(rootDirectory) + "/TestArchive.dat";

        //write a file
        TS_ASSERT_THROWS_NOTHING( writeStream = createFileStream(streamType,filename, FileStream::Append, false) );

        //test a short non-auto clear buffer
        archive = new Archive(0, false);

        TS_ASSERT_THROWS_NOTHING(archive->open(writeStream));

        //prepare data
        int key = 0;
        //UserType data[]={
        //    {0, 1., "0", "123456789abcdef"},
        //    {1, 1.1, "1", "23456789abcdef1"},
        //    {2, 1.2, "2", "3456789abcdef12"},
        //    {3, 1.3, "3", "456789abcdef123"},
        //    {4, 1.4, "4", "56789abcdef1234"},
        //    {5, 1.5, "5", "6789abcdef12345"},
        //    {6, 1.6, "6", "789abcdef123456"},
        //    {7, 1.7, "7", "89abcdef1234567XXX"}
        //};

        UserType* data[8];
        
        data[0]= new UserType(0, 1., "0", "123456789abcdef");
        data[1]= new UserType(1, 1.1, "1", "23456789abcdef1");
        data[2]= new UserType(2, 1.2, "2", "3456789abcdef12");
        data[3]= new UserType(3, 1.3, "3", "456789abcdef123");
        data[4]= new UserType(4, 1.4, "4", "56789abcdef1234");
        data[5]= new UserType(5, 1.5, "5", "6789abcdef12345");
        data[6]= new UserType(6, 1.6, "6", "789abcdef123456");
        data[7]= new UserType(7, 1.7, "7", "89abcdef1234567XXX");

        for(key = 0 ; key < sizeof(data)/sizeof(char*); key++){
            *archive << key << *data[key];
            archive->getBuffer()->commitAppendRecord();
        }

        TS_ASSERT_THROWS_NOTHING( archive->close()); 

        //read and check
        TS_ASSERT_THROWS_NOTHING( readStream = createFileStream(streamType, filename, FileStream::ReadOnly, false) );
        //char buffer[64], i;
        //for(i = 0 ; i < sizeof(data)/sizeof(char*); i++){
        //    TS_ASSERT(sizeof(key) == readStream->read((char*)&key, sizeof(key)));
        //    TS_ASSERT(strlen(data[i])+1 == readStream->read((char*)buffer, strlen(data[i])+1));
        //    TS_ASSERT_SAME_DATA(buffer, data[i] , strlen(data[i])+1);
        //}
        //TS_ASSERT(0 == readStream->read((char*)buffer, 20));

        //TS_ASSERT_THROWS_NOTHING( readStream->close()); 


        //test read archive
        delete archive;
        archive = new Archive(64, false);
        TS_ASSERT_THROWS_NOTHING( readStream->open()); 

        TS_ASSERT_THROWS_NOTHING(archive->open(readStream));

        UserType value(0,0,"","");
        UserType* pValue = &value;
        int* pKey, i;
        for(i = 0 ; i < sizeof(data)/sizeof(char*); i++){
            *archive >> pKey >> pValue;
            TS_ASSERT( *pKey == i);
            TS_ASSERT(*data[i] == *pValue);
        }

        TS_ASSERT_THROWS_NOTHING( archive->close()); 
        delete archive;
    }


public:

    //==============test goes here =====================

    void testLocal1(void)	{
        doTestNormalArchiving( true, "foo");
    }

    void testLocal2(void)	{
        doTestStringArchiving( true, "foo");
    }
    
    void testLocal3(void){
        doTestUserTypeArchiving( true, "foo");
    }

    void testLocal4(void){
    }

    void testLocal5(void){
    }

    //#TODO
    // test openStream/closeStream multiple time
    // test PString 

};


#endif /* _TEST_TFSMASTER_ARCHIVE_HPP */

