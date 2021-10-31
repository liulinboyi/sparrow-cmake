#include "../object/obj_fn.h"
#include "../object/class.h"
#include "../vm/vm.h"
#include <string.h>

//新建模块
ObjModule *newObjModule(VM *vm, const char *modName /*模块名称*/)
{
   ObjModule *objModule = ALLOCATE(vm, ObjModule); // 为新模块分配内存
   if (objModule == NULL)
   {
      MEM_ERROR("allocate ObjModule failed!");
   }

   //ObjModule是元信息对象,不属于任何一个类
   initObjHeader(vm, &objModule->objHeader, OT_MODULE, NULL /*此处传值null表示ObjModule不属于任何一个类*/); // 初始化对象头

   pushTmpRoot(vm, (ObjHeader *)objModule);
   StringBufferInit(&objModule->moduleVarName); // 初始化moduleVarName
   ValueBufferInit(&objModule->moduleVarValue); // 初始化moduleVarValue

   objModule->name = NULL; //核心模块名为NULL 类型是ObjString*
   if (modName != NULL)
   { // modName不为null说明不是核心模块
      objModule->name = newObjString(vm, modName, strlen(modName));
   }
   popTmpRoot(vm);

   return objModule;
}

// class结构体是存储类的方法的结构
// ObjInstance是存储对象域的结构
//创建类class的实例 创建参数class的实例对象
ObjInstance *newObjInstance(VM *vm, Classes *classes)
{
   //参数class主要作用是提供类中field的数目 通用数据要放在模板即class中
   ObjInstance *objInstance = ALLOCATE_EXTRA(vm,
                                             ObjInstance, sizeof(Value) * classes->fieldNum);

   //在此关联对象的类为参数class
   initObjHeader(vm, &objInstance->objHeader, OT_INSTANCE, classes/*创建的对象所属的类是此class，在这里将对象和类作了绑定*/); // 初始化对象头

   //初始化field为NULL 初始化数组fields中元素的值为null
   uint32_t idx = 0;
   while (idx < classes->fieldNum)
   {
      objInstance->fields[idx++] = VT_TO_VALUE(VT_NULL);
   }
   return objInstance;
}
