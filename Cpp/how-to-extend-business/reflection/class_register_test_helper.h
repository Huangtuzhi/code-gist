#include "class_register.h"

class Banker{
public:
	Banker(){}
	virtual ~Banker(){}
	virtual std::string GetBankerName() const = 0;
};

CLASS_REGISTER_DEFINE_REGISTRY(banker_register, Banker);


#define REGISTER_BANKER(class_name,entryName)								\
	CLASS_REGISTER_OBJECT_CREATOR(banker_register, Banker, class_name,entryName);

#define CREATE_BANKER(entryName)											\
	CLASS_REGISTER_CREATE_OBJECT(banker_register, entryName);
