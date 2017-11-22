#include "class_register_test_helper.h"
#include <iostream>

int main() {
	Banker* a = CREATE_BANKER("ABanker");
	if(a!= NULL) {
		std::cout<<a->GetBankerName()<<std::endl;
	}
	else {
		std::cout<<"a is NULL!" << std::endl;
	}

	Banker* b = CREATE_BANKER("BBanker");
	if(b!=NULL) {
		std::cout<<b->GetBankerName()<<std::endl;
	}
	else {
		std::cout<<"b is NULL" << std::endl;
	}

	return 0;	
}
