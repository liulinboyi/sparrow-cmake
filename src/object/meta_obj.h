#ifndef _OBJECT_METAOBJ_H
#define _OBJECT_METAOBJ_H
#include "../object/obj_string.h"

/*
元信息
包括
模块对象
实例对象
仅供内部使用，用户看不到
*/

// 模块变量 -> 在模块中定义的全局变量
typedef struct {
   ObjHeader  objHeader;
   SymbolTable moduleVarName;   //模块中的模块变量名
   ValueBuffer moduleVarValue;  //模块中的模块变量值
   ObjString*  name;   //模块名
} ObjModule;   //模块对象 模块就是在独立作用域中，定义的代码的集合 在模块对象中只保存在模块中定义的全局变量

typedef struct {
   ObjHeader objHeader;
   //具体的字段
   Value fields[0]; // 柔性数组
} ObjInstance;	//对象实例

ObjModule* newObjModule(VM* vm, const char* modName);
ObjInstance* newObjInstance(VM* vm, Class* class);
#endif
