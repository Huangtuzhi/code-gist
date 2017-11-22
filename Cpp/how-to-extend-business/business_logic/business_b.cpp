#include "business_b.h"

string BusinessModuleB::GetData()
{
    return "Module B";
}

REGISTER_MODULE(BusinessModuleB, "BusinessModuleB");