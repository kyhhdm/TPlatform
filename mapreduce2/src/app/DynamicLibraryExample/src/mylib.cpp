#include "mylib.hpp"

#include <iostream>

using namespace std;

const char * const SimpleFactory::ID = "SimpleFactory";
const char * const ISimple::ID = "ISimple";

extern "C" {
	IClassFactory * GetClassObject()
	{
		IClassFactory * ret;
		ret = new SimpleFactory();
		ret->AddRef();
		return ret;
	}
}

HRESULT SimpleFactory::QueryInterface( IN CLSID clsid, OUT void ** ppv )
{
	HRESULT ret;
	if(clsid == SimpleFactory::ID) {
		*ppv = (void*)this;
		AddRef();
		ret = E_NOERR;
	} else {
		ret = IClassFactory::QueryInterface(clsid, ppv);
	}


	return ret;
}

HRESULT SimpleFactory::CreateInstance( IN CLSID clsid, OUT void ** ppv )
{
	HRESULT ret;
	IUnknown * obj;

	if(clsid == ISimple::ID) {
		obj = new MySimple();
		obj->AddRef();
		*ppv = obj;
		ret = E_NOERR;
	} else {
		ret = E_NOINTERFACE;
	}

	return ret;
}

HRESULT ISimple::QueryInterface( IN CLSID clsid, OUT void ** ppv )
{
	HRESULT ret;

	if(clsid == ISimple::ID) {
		AddRef();
		*ppv = (void*)this;
		ret = E_NOERR;
	} else {
		ret = IUnknown::QueryInterface(clsid, ppv);
	}

	return ret;
}

int MySimple::getMagicNumber() const
{
	cout << "returning magic number" << endl;
	return 52;
}

