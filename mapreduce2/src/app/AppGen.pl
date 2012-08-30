#!/usr/bin/perl
use strict;
use warnings;

if ($#ARGV != 0){
    print "Usage: $0 <project_name>\n";
    exit 0;
}
my $project_name = $ARGV[0];
print "project name: $project_name\n";

my ($sec, $min, $hour, $mday, $mon, $year, $wday, $yday, $isdst);
($sec,$min,$hour,$mday,$mon,$year,$wday,$yday,$isdst) = localtime();
$year += 1900;
$mon ++;
my $date = sprintf("%04d-%02d-%02d", $year, $mon, $mday);
print "date: $date\n";

print "create dir $project_name\n";
mkdir $project_name;
chdir $project_name;

print "create file ${project_name}Mapper.hpp\n";
open OUTFILE, ">${project_name}Mapper.hpp"; 
print OUTFILE "
/**
 * \@file ${project_name}Mapper.hpp
 * \@description
 *
 * \@author
 * \@date ${date}
 *
 * */
#ifndef ${project_name}Mapper_HPP
#define ${project_name}Mapper_HPP

#include \"Mapper.hpp\"
namespace mapreduce{

    class ${project_name}Mapper: public Mapper{
    public:
        ${project_name}Mapper();
        ~${project_name}Mapper();
        bool map(const void* key, const void* value, Collector& collector) const;
    private:

    };

}

#endif /* ${project_name}Mapper_HPP */
";

close OUTFILE;

print "create file ${project_name}Mapper.cpp\n";

open OUTFILE, ">${project_name}Mapper.cpp"; 
print OUTFILE "
/**
 * \@file ${project_name}Mapper.cpp
 *
 * */
#include \"${project_name}Mapper.hpp\"
#include \"Collector.hpp\"
#include <iostream>

using namespace std;
using namespace mapreduce;


${project_name}Mapper::${project_name}Mapper()
{
}

${project_name}Mapper::~${project_name}Mapper()
{
}

bool ${project_name}Mapper::map(const void* key, const void* value, Collector& collector) const
{
    // >> change the following code
    collector.collect( key, value);

    return true;
}
";

close OUTFILE;

print "create file ${project_name}Reducer.hpp\n";

open OUTFILE, ">${project_name}Reducer.hpp"; 
print OUTFILE "
/**
 * \@file ${project_name}Reducer.hpp
 * \@description
 *
 * \@author
 * \@date ${date}
 *
 * */
#ifndef ${project_name}Reducer_HPP
#define ${project_name}Reducer_HPP

#include \"Reducer.hpp\"

namespace mapreduce{

    class ${project_name}Reducer : public Reducer{
    public:
        ${project_name}Reducer();
        ~${project_name}Reducer();
    	bool reduce(const void* key, KeyValueIterator& values, Collector& collector) const;
    };

}

#endif /* ${project_name}Reducer_HPP */
";

close OUTFILE;

print "create file ${project_name}Reducer.cpp\n";

open OUTFILE, ">${project_name}Reducer.cpp"; 
print OUTFILE "
/**
 * \@file ${project_name}Reducer.cpp
 * 
 **/
#include \"${project_name}Reducer.hpp\"
#include \"KeyValueIterator.hpp\"
#include \"Collector.hpp\"

using namespace std;
using namespace mapreduce;

${project_name}Reducer::${project_name}Reducer()
{
}

${project_name}Reducer::~${project_name}Reducer()
{
}

bool ${project_name}Reducer::reduce(const void* key, KeyValueIterator& values, Collector& collector) const
{
    // >> change the following code
    while(values.hasMore()){
        void* value = values.next();
        collector.collect( key, value);
    }
    return true;
}

";

close OUTFILE;

print "create file ${project_name}KeyValue.hpp\n";

open OUTFILE, ">${project_name}KeyValue.hpp"; 
print OUTFILE "
/**
 * \@file ${project_name}Key.hpp
 * \@description
 *
 * \@author
 * \@date ${date}
 *
 * */
#ifndef ${project_name}Key_HPP
#define ${project_name}Key_HPP

#include \"HashableComparable.hpp\"


namespace mapreduce{

    class Archive;

    class ${project_name}Key{
    public:

        friend class Archive;
    };

    class ${project_name}Value{
    public:

        friend class Archive;
    };

    class ${project_name}KeyHelper: public HashableComparable{
    public:
        friend class ${project_name}Key;

        virtual bool operator()(const void* key1, const void* key2) const;
        virtual bool equal(const void* key1, const void* key2) const;
        virtual unsigned int hash(const void* key, int partitionNumber) const;
    };

    Archive& operator>>(Archive& ar, ${project_name}Key*& data);
    Archive& operator<<(Archive& ar, ${project_name}Key& data);

    Archive& operator>>(Archive& ar, ${project_name}Value*& data);
    Archive& operator<<(Archive& ar, ${project_name}Value& data);
}

#endif /* ${project_name}KeyValue_HPP */
";

close OUTFILE;

print "create file ${project_name}KeyValue.cpp\n";

open OUTFILE, ">${project_name}KeyValue.cpp"; 
print OUTFILE "
/**
 * \@file ${project_name}KeyValue.cpp
 *
 * \@author
 * \@date ${date}
 *
 **/
#include \"${project_name}KeyValue.hpp\"
#include \"Archive.hpp\"
#include \"ArchiveBuffer.hpp\"
#include <cstdio>
#include <iostream>

using namespace std;
using namespace mapreduce;


bool ${project_name}KeyHelper::operator()(const void* key1, const void* key2) const
{

}

bool ${project_name}KeyHelper::equal(const void* key1, const void* key2) const
{

}

unsigned int ${project_name}KeyHelper::hash(const void* key, int partitionNumber) const
{

}

namespace mapreduce{

Archive& operator>>(Archive& ar, ${project_name}Key*& data)
{
    return ar;
}

Archive& operator<<(Archive& ar, ${project_name}Key& data)
{
    return ar;
}

Archive& operator>>(Archive& ar, ${project_name}Value*& data)
{
    return ar;
}

Archive& operator<<(Archive& ar, ${project_name}Value& data)
{
    return ar;
}

}
";

close OUTFILE;

print "create file ${project_name}.cpp\n";

open OUTFILE, ">${project_name}.cpp"; 
print OUTFILE "
/**
 * \@file ${project_name}.cpp
 * \@description 
 *
 * \@author
 * \@date ${date}
 *
 **/

#include \"${project_name}Mapper.hpp\"
#include \"${project_name}Reducer.hpp\"
#include \"${project_name}KeyValue.hpp\"
#include \"Mapper.hpp\"
#include \"Collector.hpp\"
#include \"Reducer.hpp\"
#include \"KeyValueIterator.hpp\"
#include \"TKeyValueFeeder.hpp\"
#include \"TKeyValueWriter.hpp\"
#include \"TStringHashableComparable.hpp\"
#include \"ClassLoader.hpp\"
#include \"TextFileWriter.hpp\"
#include <string>
#include <vector>
#include <iostream>
#include <typeinfo>

using namespace std;
using namespace mapreduce;

REGISTER_CLASS_BEGIN();
REGISTER_CLASS(${project_name}Mapper);
REGISTER_CLASS(${project_name}Reducer);
REGISTER_CLASS(${project_name}KeyHelper);
REGISTER_FEEDER_CLASS(${project_name}Key,${project_name}Value);
REGISTER_WRITER_CLASS(${project_name}Key,${project_name}Value);
REGISTER_CLASS_END(); 

";

close OUTFILE;

print "create file ${project_name}Job.ini\n";

open OUTFILE, ">${project_name}Job.ini"; 
print OUTFILE "
[job]
#change the following configurations
input_file=
output_file=
so_file=/homeX/tfs/lib/gcc-3.4/lib${project_name}.so
reduce_task_num=
do_local_combine=no
mapper_class=${project_name}Mapper
reducer_class=${project_name}Reducer
mapper_in_key_class=${project_name}Key
mapper_in_value_class=${project_name}Value
mapper_out_key_class=${project_name}Key
mapper_out_value_class=${project_name}Value
reducer_out_key_class=${project_name}Key
reducer_out_value_class=${project_name}Value
";

close OUTFILE;

print "create file ${project_name}Main.cpp\n";

open OUTFILE, ">${project_name}Main.cpp"; 
print OUTFILE "
/**
 * \@file ${project_name}Main.cpp
 * \@description 
 *
 * \@author
 * \@date ${date}
 *
 **/
#include \"mapreduce.h\"
#include <iostream>
#include <string>
using namespace std;
using namespace mapreduce::api;

#ifdef ${project_name}_MAIN

    int setJobSpec(MapReduceJob &jobSpec){
	jobSpec.mapperClass = \"${project_name}Mapper\";
	jobSpec.reducerClass = \"${project_name}Reducer\";
	jobSpec.mapperOutKeyClass = \"${project_name}Key\";
	jobSpec.mapperOutValueClass = \"${project_name}Value\";
	//set up mapper reader class
	jobSpec.mapperInKeyClass = = \"${project_name}Key\";
	jobSpec.mapperInValueClass= \"${project_name}Value\";
	//jobSpec.mapperRecordReaderClass= \"${project_name}KeyValueFeeder\";
	//set up reducer writer class
	jobSpec.reducerOutKeyClass= \"${project_name}Key\";
	jobSpec.reducerOutValueClass= \"${project_name}Value\";
	//jobSpec.reducerRecordWriterClass= \"${project_name}KeyValueWriter\";
	return 0;
    }

int main(int argc, char** argv){

    MapReduceJob jobSpec;
    jobSpec.reduceTaskNum = 10;
    jobSpec.inputFile = \"\";
    jobSpec.outputFile = \"\";
    jobSpec.soFile = \"lib${project_name}.so\";
    setJobSpec(jobSpec);
    cout << jobSpec << endl;

    string masterHost = \"127.0.0.1\";
    int masterPort = 20000;
    bool bDetach = true;
    MapReduceService service(masterHost, masterPort);
    int jobId = service.create(jobSpec);
    cout << \"Job ID: \" << jobId << endl;

    if (jobId < 0){
        return -1;
    }
    
    if (bDetach){
        service.detach(jobId);
    }
    else{
        int ret = service.wait(jobId);
        if (ret == 0){
            cout << \"Job successfully done.\" << endl;
        }
        else if (ret == 1){
            cout << \"Job was abandoned. \" << endl;
        }
        else{
            cout << \"Job done with unkonw errors \" << endl;
        }
        
    }

    return 0;
}
#endif
";

close OUTFILE;


