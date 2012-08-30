/**
 * @file WordFrequencyMain.cpp
 *
 * @author PengBo
 * @date 2007-12-18
 * */

#include "WordFrequencyMain.hpp"
#include <iostream>
#include <fstream>

using namespace std;
using namespace boost;
using namespace mapreduce;
using namespace classloader;


WordFrequencyMain::WordFrequencyMain(string basename)
{
    //============================
    string feederLibName = basename + "Feeder.so";
    string mapperLibName = basename + "Mapper.so";
    string hasherLibName = basename + "KeyHasher.so";
    string reducerLibName = basename + "Reducer.so";
    string comparisonLibName = basename + "KeyComparison.so";

    //=============================
    HRESULT res;
    m_loader = new ClassLoader();
    m_loader->AddRef();
    //dynamicly load feeder
    res = m_loader->GetClassObject(feederLibName.c_str(), &m_factory);
	if(res != E_NOERR) {
		if(res == E_DLLOPEN) {
			cerr << "you must make "<< feederLibName << " available to dlopen by either putting it's directory in ld.so.conf or in LD_LIBRARY_PATH or by installing it to the system library dir" << endl;
			//return -1;
            throw std::exception();
		}
	}
	assert(res == E_NOERR);
	res = m_factory->CreateInstance(CLSID("IFeeder"), (void**)&m_feeder);
	assert(res == E_NOERR);

    //dynamicly load mapper
    res = m_loader->GetClassObject(mapperLibName.c_str(), &m_factory);
	if(res != E_NOERR) {
		if(res == E_DLLOPEN) {
			cerr << "you must make "<< mapperLibName << " available to dlopen by either putting it's directory in ld.so.conf or in LD_LIBRARY_PATH or by installing it to the system library dir" << endl;
			//return -1;
            throw std::exception();
		}
	}
	assert(res == E_NOERR);
	res = m_factory->CreateInstance(CLSID("IMapper"), (void**)&m_mapper);
	assert(res == E_NOERR);

    //dynamicly load hasher
    res = m_loader->GetClassObject(hasherLibName.c_str(), &m_factory);
	if(res != E_NOERR) {
		if(res == E_DLLOPEN) {
			cerr << "you must make "<< hasherLibName << " available to dlopen by either putting it's directory in ld.so.conf or in LD_LIBRARY_PATH or by installing it to the system library dir" << endl;
            throw std::exception();
			//return -1;
		}
	}
	assert(res == E_NOERR);
	res = m_factory->CreateInstance(CLSID("IKeyHasher"), (void**)&m_hasher);
	assert(res == E_NOERR);

    //dynamicly load reducer
    res = m_loader->GetClassObject(reducerLibName.c_str(), &m_factory);
	if(res != E_NOERR) {
		if(res == E_DLLOPEN) {
			cerr << "you must make "<< reducerLibName << " available to dlopen by either putting it's directory in ld.so.conf or in LD_LIBRARY_PATH or by installing it to the system library dir" << endl;
            throw std::exception();
			//return -1;
		}
	}
	assert(res == E_NOERR);
	res = m_factory->CreateInstance(CLSID("IReducer"), (void**)&m_reducer);
	assert(res == E_NOERR);

    //dynamicly load comparisoner
    res = m_loader->GetClassObject(comparisonLibName.c_str(), &m_factory);
	if(res != E_NOERR) {
		if(res == E_DLLOPEN) {
			cerr << "you must make "<< comparisonLibName << " available to dlopen by either putting it's directory in ld.so.conf or in LD_LIBRARY_PATH or by installing it to the system library dir" << endl;
            throw std::exception();
			//return -1;
		}
	}
	assert(res == E_NOERR);
	res = m_factory->CreateInstance(CLSID("IKeyComparison"), (void**)&m_comparison);
	assert(res == E_NOERR);

}

WordFrequencyMain::~WordFrequencyMain()
{
	m_mapper->Release();
    m_reducer->Release();
    m_feeder->Release();
    m_hasher->Release();
	m_comparison->Release();
    m_loader->Release();
    
}

void WordFrequencyMain::run(string& inFilePath)
{
    {
        //do map
        if(m_feeder->open(inFilePath) == -1){
            cerr << "SetMapper::map(): wrapper " << inFilePath << " open error!" << endl;
            return ;
        }

        shared_ptr<KeyValue> inKeyValue;
        vector<shared_ptr<KeyValue> > outKeyValues;
        ofstream tmpf("wf.tmp");

        int count = 0;
        inKeyValue = m_feeder->next();


        while(inKeyValue.get() != NULL){
            
            KeyValueField keyUrl;
            inKeyValue->getKey(keyUrl);
            string url;
            keyUrl.getStr(url);
            cout << "read : " << url << endl;
            //cout << '.' ;
            cout.flush();
            
            //map the keyvalue to a set of keyvalues
            m_mapper->map(*inKeyValue, outKeyValues);
            
            cout << "mapper: " << outKeyValues.size() << endl;
            
            for(int i = 0 ; i < outKeyValues.size() ; i ++){
                shared_ptr<KeyValue> pKeyValue = outKeyValues[i];
                KeyValueField keyTerm, valueTerm;
                pKeyValue->getKey(keyTerm);
                pKeyValue->getValue(0,valueTerm);
                
                string term;
                int freq = 0;
                keyTerm.getStr(term);
                valueTerm.getInt(freq);
                tmpf << term << " " << freq << endl;
                
            }
            inKeyValue = m_feeder->next();
            count ++;
        }
        m_feeder->close();
        tmpf.close();
    }

    //do sort
    cout << "sorting..." << endl;
    
    system("sort -n wf.tmp > wfin.tmp");

    cout << "reduce..." << endl;

    {
        //do reduce
        ifstream inf("wfin.tmp" );
        ofstream outf("wfout.tmp" );
        string term;
        int freq;
        vector<shared_ptr<KeyValue> > keyValues;
        KeyValueField prevKey, currKey, key, value;

        
        inf >> term >> freq;
            
        key.appendStr(term);
        value.appendInt(freq);

        KeyValue* inKeyValue = new KeyValue(1);
        inKeyValue->setKey(key);
        inKeyValue->setValue(0,value);
        
        shared_ptr<KeyValue> currKeyValue(inKeyValue);
        keyValues.push_back(currKeyValue);
        //currKeyValue->getKey(prevKey);
        
        prevKey = key;

        while(!inf.eof()){
            //read in new record
            inf >> term >> freq;
            
            key.clear();
            value.clear();    
            key.appendStr(term);
            value.appendInt(freq);

            KeyValue* inKeyValue = new KeyValue(1);
            inKeyValue->setKey(key);
            inKeyValue->setValue(0,value);
            
            shared_ptr<KeyValue> currKeyValue(inKeyValue);

            //for each keyvalue
            //currKeyValue->getKey(currKey);

            currKey = key;

            if(m_comparison->compare(currKey, prevKey) == 0){
                //if current key is same as previsou key, add to waiting list
                keyValues.push_back(currKeyValue);
                //crazy, that prevKey.getStr() will mutate it's internal state. 
                prevKey.reset();
            }
            else{
                //if current key is different from previsou key, reduce current waiting list, and restart the process
                vector<shared_ptr<KeyValue> > newKeyValues;
                m_reducer->reduce(keyValues, newKeyValues);
                
                //write out put
                KeyValueField keyNew, valueNew;
                newKeyValues[0]->getKey(keyNew);
                newKeyValues[0]->getValue(0,valueNew);
                string term;
                int freq;
                keyNew.getStr(term);
                valueNew.getInt(freq);
                outf << term << " " << freq << endl;

                keyValues.clear();
                //currKeyValue->getKey(prevKey);
                prevKey = key;

                keyValues.push_back(currKeyValue);
            }
            
        }
    }
}


//=======================
int main(int argc, char* argv[])
{
    if(argc!=3) {
        cout << "usage : " << argv[0] << " <app basename> <inputFileName>" << endl;
        return -1;
    }

    WordFrequencyMain* app = new WordFrequencyMain(argv[1]);

    string inputFile(argv[2]);
    app->run(inputFile);

    return 0;
}

