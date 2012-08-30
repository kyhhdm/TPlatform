#include "app/include/simple_lib.hpp"
#include <classloader/ClassLoader.h>
#include <classloader/IClassFactory.h>
#include <assert.h>
#include <iostream>

using namespace std;
using namespace classloader;

int main(int argc, char ** argv)
{
	ClassLoader * loader;
	IClassFactory * factory;
	HRESULT res;

    if(argc != 2){
        cout << "USAGE: simple_client <shared_LIB>" << endl;
    }

	loader = new ClassLoader();
	loader->AddRef();
	res = loader->GetClassObject(argv[1], &factory);
	if(res != E_NOERR) {
		if(res == E_DLLOPEN) {
			cerr << "you must make simple_lib.so available to dlopen by either putting it's directory in ld.so.conf or in LD_LIBRARY_PATH or by installing it to the system library dir" << endl;
			return -1;
		}
	}
	assert(res == E_NOERR);

	ISimple * simple;
	res = factory->CreateInstance(CLSID("ISimple"), (void**)&simple);
	assert(res == E_NOERR);

	cout << "magic number is " << simple->getMagicNumber() << endl;

	simple->Release();
	loader->Release();

	return 0;
}
