#ifndef SIMPLEFACTORY_H
#define SIMPLEFACTORY_H

#include <classloader/IClassFactory.h>

using namespace classloader;

int foo(int);

extern "C" {
	IClassFactory * GetClassObject();
}

class SimpleFactory : public IClassFactory
{
public:
	static const char * const ID;
	HRESULT QueryInterface( IN CLSID clsid, OUT void ** ppv );
	HRESULT CreateInstance( IN CLSID clsid, OUT void ** ppv );
};

class ISimple : public IUnknown
{
public:
	static const char * const ID;

	HRESULT QueryInterface( IN CLSID clsid, OUT void ** ppv );

	virtual int getMagicNumber() const = 0;
};

class Simple : public ISimple
{
public:
	/* ISimple interface */
	int getMagicNumber() const;
};

#endif /* SIMPLEFACTORY_H */
