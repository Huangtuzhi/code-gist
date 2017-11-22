#include "base_module.h"

BaseModule::~BaseModule()
{
}

string BaseModule::GetData()
{
    return "haha";
}

CLASS_REGISTER_IMPLEMENT_REGISTRY(ModuleRegister, BaseModule);