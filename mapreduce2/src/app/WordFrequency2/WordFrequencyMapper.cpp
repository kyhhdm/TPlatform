/**
 * @file WordFrequencyMapper.cpp
 *
 * */
#include "WordFrequencyMapper.hpp"
#include "Collector.hpp"
#include <stdio.h>
#include <SimpleParser/parser.h>
#include <iostream>

using namespace std;
using namespace mapreduce;


WordFrequencyMapper::WordFrequencyMapper()
{
    m_parser = new CParser(0);
}

WordFrequencyMapper::~WordFrequencyMapper()
{
    delete m_parser;
}

bool WordFrequencyMapper::map(const void* key, const void* value, Collector& collector) const
{
    //<char*, char*> as mapper intput
    //<char*, int> as mapper output

    int outValue = 1;
    int outputCnt = 0;
    int bodyLen = strlen(*(char**)value);

    //do parsing
    m_parser->init_page(*(char**)value);
    m_parser->convert_charset("skip");
    m_parser->delete_tags();
    m_parser->cut_words(1);
    m_parser->end_page();

    //processing with the keywords list
    char *p = m_parser->get_keywords();

    //cout << p << endl;
	p=strtok(p," ");
	
	while(p){
		switch(*p){
		case	DELI_WEIGHT:
		case	DELI_LOC:
		case	DELI_PARA:
			//skip these tokens
			break;
        case    '\0':
            cout << "+";
		default:{
            char** pData = &p;
            collector.collect( pData, &outValue);
            outputCnt ++;
            }
		}
		p=strtok(NULL," ");
	}

    //cout << *(char**)key << " : " << bodyLen << " : " << outputCnt << endl;

    return true;
}

