#include "../object/meta_obj.h"
#include "../object/class.h"
#include "../vm/vm.h"

//创建一个空函数
ObjFn* newObjFn(VM* vm, ObjModule* objModule/*函数所属的模块*/, uint32_t slotNum/*函数需要的栈的大小*/) {
   ObjFn* objFn = ALLOCATE(vm, ObjFn); 
   if (objFn == NULL) {
      MEM_ERROR("allocate ObjFn failed!"); 
   }
   initObjHeader(vm, &objFn->objHeader, OT_FUNCTION, vm->fnClass);
   ByteBufferInit(&objFn->instrStream);
   ValueBufferInit(&objFn->constants);
   objFn->module = objModule;
   objFn->maxStackSlotUsedNum = slotNum;
   objFn->upvalueNum = objFn->argNum = 0;
#ifdef DEBUG
   objFn->debug = ALLOCATE(vm, FnDebug);
   objFn->debug->fnName = NULL;
   IntBufferInit(&objFn->debug->lineNo);
#endif
   return objFn;
}

//以函数fn创建一个闭包
ObjClosure* newObjClosure(VM* vm, ObjFn* objFn) {
   ObjClosure* objClosure = ALLOCATE_EXTRA(vm, 
	 ObjClosure, sizeof(ObjUpvalue*) * objFn->upvalueNum);
   initObjHeader(vm, &objClosure->objHeader, OT_CLOSURE, vm->fnClass/*vm中新增的类的挂载点*/);
   objClosure->fn = objFn;
   
   //清除upvalue数组做 以避免在填充upvalue数组之前触发GC
   uint32_t idx = 0;
   while (idx < objFn->upvalueNum) {
      objClosure->upvalues[idx] = NULL; // 未初始化的元素是未知的，GC会误处理为upvalue从而造成严重错误
      // 所以要显示的置为null
      idx++;
   }

   return objClosure;
}

//创建upvalue对象
ObjUpvalue* newObjUpvalue(VM* vm, Value* localVarPtr/*局部变量在栈中的地址*/) {
   ObjUpvalue* objUpvalue = ALLOCATE(vm, ObjUpvalue);
   initObjHeader(vm, &objUpvalue->objHeader, OT_UPVALUE, NULL);
   objUpvalue->localVarPtr = localVarPtr; // 赋值
   objUpvalue->closedUpvalue = VT_TO_VALUE(VT_NULL);
   objUpvalue->next = NULL;
   return objUpvalue;
}
