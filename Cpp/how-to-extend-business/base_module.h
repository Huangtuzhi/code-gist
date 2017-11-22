#include <iostream>
#include <string>
#include "./reflection/class_register.h"
using namespace std;

#ifndef __BASEMODULE__
#define __BASEMODULE__

class BaseModule
{
public:
	virtual ~BaseModule(); 

	virtual string GetData();
};

CLASS_REGISTER_DEFINE_REGISTRY(ModuleRegister, BaseModule);

#define REGISTER_MODULE(class_name, entryName) \
	CLASS_REGISTER_OBJECT_CREATOR(            \
		ModuleRegister, BaseModule, class_name, entryName);

#define GET_MODULE(entryName) \
	CLASS_REGISTER_CREATE_OBJECT(ModuleRegister, entryName);

#endif