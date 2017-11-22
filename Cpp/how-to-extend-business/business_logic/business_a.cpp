#include "business_a.h"

string BusinessModuleA::GetData()
{
    return "Module A";
}

REGISTER_MODULE(BusinessModuleA, "BusinessModuleA");