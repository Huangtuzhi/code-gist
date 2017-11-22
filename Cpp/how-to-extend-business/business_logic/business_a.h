#include <iostream>
#include <string>
#include "../base_module.h"
using namespace std;

class BusinessModuleA: public BaseModule
{
public:
	virtual string GetData();
};