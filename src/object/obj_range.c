#include "../object/obj_range.h"
#include "../include/utils.h"
#include "../object/class.h"
#include "../vm/vm.h"

//新建range对象
ObjRange* newObjRange(VM* vm, int from, int to) {
   ObjRange* objRange = ALLOCATE(vm, ObjRange); // 分配内存
   initObjHeader(vm, &objRange->objHeader, OT_RANGE, vm->rangeClass); // 初始化对象头
   objRange->from = from; // 初始化对象的from
   objRange->to = to; // 初始化对象的to
   return objRange; // 最后返回
}
