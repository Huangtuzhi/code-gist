// 手工需要这些头文件
// #include "./business_logic/business_a.h"
// #include "./business_logic/business_b.h"

// 反射只需要这个头文件
#include "base_module.h"

int main() {
	// 使用 ModuleA 处理
 //    BaseModule * module_a = new BusinessModuleA();
 //    cout << module_a->GetData() << endl;

 //    // 使用 ModuleB 处理
 //    BaseModule * module_b = new BusinessModuleB();
	// cout << module_b->GetData() << endl;


    // 使用反射获取 ModuleA 实例
    BaseModule* business_a = GET_MODULE("BusinessModuleA");
    cout << business_a->GetData() << endl;

    // 使用反射获取 ModuleB 实例
    BaseModule* business_b = GET_MODULE("BusinessModuleB");
    cout << business_b->GetData() << endl;
}