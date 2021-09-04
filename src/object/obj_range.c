#include "../object/obj_range.h"
#include "../include/utils.h"
#include "../object/class.h"
#include "../vm/vm.h"

//新建range对象
ObjRange* newObjRange(VM* vm, int from, int to) {
   ObjRange* objRange = ALLOCATE(vm, ObjRange);
   initObjHeader(vm, &objRange->objHeader, OT_RANGE, vm->rangeClass);
   objRange->from = from;
   objRange->to = to;
   return objRange;
}
