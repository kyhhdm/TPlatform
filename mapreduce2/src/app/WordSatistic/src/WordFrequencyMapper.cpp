/**
 * @file WordFrequencyMapper.cpp
 *
 * @author Chen Rishan
 * @date 2007-12-11
 * */
#include "WordFrequencyMapper.hpp"
#include "Buffer.hpp"
#include "KeyValue.hpp"
#include <SimpleParser/parser.h>
#include <iostream>

using namespace std;
using namespace mapreduce;
using namespace boost;

IMPLEMENT_FACTORY(IMapper, WordFrequencyMapper);

WordFrequencyMapper::WordFrequencyMapper()
{
    m_parser = new CParser(0);
}

WordFrequencyMapper::~WordFrequencyMapper()
{
    delete m_parser;
}

int WordFrequencyMapper::map(const KeyValue& inKeyValue, std::vector<boost::shared_ptr<KeyValue> >& outKeyValues) const
{
    Buffer key, value;
    
    
    //do parsing
    string strPage;
    inKeyValue.getValue(0, value);
    value.getStr(strPage);
    m_parser->init_page((char*)strPage.c_str());
    m_parser->convert_charset("skip");
    m_parser->delete_tags();
    m_parser->cut_words(1);
    m_parser->end_page();

    //processing with the keywords list
    char *p = m_parser->get_keywords();
	p=strtok(p," ");
	
    value.clear();
    value.appendInt(1);
	while(p){
		switch(*p){
		case	DELI_WEIGHT:
		case	DELI_LOC:
		case	DELI_PARA:
			//skip these tokens
			break;
		default:
            {
                key.appendStr(p ,strlen(p));
                KeyValue* outKeyValue = new KeyValue(1);
                outKeyValue->setKey(key);
                outKeyValue->setValue(0,value);
                key.clear();

                shared_ptr<KeyValue> pKeyValue(outKeyValue);
                outKeyValues.push_back(pKeyValue);
            }
		}
		p=strtok(NULL," ");
	}

    return 1;
}

