#include "../object/header_obj.h"
#include "../object/class.h"
#include "../vm/vm.h"

DEFINE_BUFFER_METHOD(Value) // 生成ValueBUffer对应的操作方法

//初始化对象头 初始化ObjectHeader指向的对象头 objType对象类型 class类
void initObjHeader(VM* vm, ObjHeader* objHeader, ObjType objType, Classes* classes) {
   objHeader->type = objType;
   objHeader->isDark = false; // 默认位false，其终值由垃圾回收机制设置
   objHeader->classes = classes;    //设置meta类
   objHeader->next = vm->allObjects; // vm->allObjects初始化值是null，当创建第一个对象头时，objHeader->next指向null
   vm->allObjects = objHeader; // 第一个对象头赋值给vm->allObjects，当第二个对象头初始化时，objHeader->next指向第一个对象头，以此类推
   // 第n个对象头next指向第n-1个对象头，第n-1个对象头next指向第n-2个对象头，...，第2个对象头next指向第1个对象头,第1个对象头next指向null
}
