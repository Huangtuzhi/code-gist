#include "class_register_test_helper.h"

CLASS_REGISTER_IMPLEMENT_REGISTRY(banker_register, Banker);

class ABanker: public Banker{
public:
	ABanker(){}
	virtual ~ABanker(){}
	virtual std::string GetBankerName() const {
		return "I am A Banker";
	}
};
REGISTER_BANKER(ABanker, "ABanker");


class BBanker: public Banker {
public:
	BBanker(){}
	virtual ~BBanker(){}
	virtual std::string GetBankerName() const {
		return "I am B Banker";
	}
};

REGISTER_BANKER(BBanker, "BBanker");
