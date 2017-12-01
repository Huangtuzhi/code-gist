## 目录结构

```
.
└──how-to-extend-business
    ├── entrance.cpp    # 相当于系统框架的 main 函数入口
    ├── base_module.cpp # 相当于系统框架的基类
    ├── base_module.h
    ├── business_logic  # 扩展的业务逻辑目录
    │   ├── business_a.cpp
    │   ├── business_a.h
    │   ├── business_b.cpp
    │   └── business_b.h
    ├── make.sh         # 编译脚本
    └── reflection      # 反射宏
        ├── class_register.h
        ├── class_register_test.cc
        ├── class_register_test_helper.cc
        └── class_register_test_helper.h
```

## 原理

[用继承和反射机制实现业务扩展](http://fuzhii.com/2017/11/22/how-to-extend-business/)
