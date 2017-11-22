#include <iostream>
#include <string>
#include "../base_module.h"
using namespace std;

class BusinessModuleB: public BaseModule
{
public:
	virtual string GetData();
};