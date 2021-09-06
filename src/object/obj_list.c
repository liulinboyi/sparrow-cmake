#include "../object/obj_list.h"

// list增删改操作在这里
//新建list对象,元素个数为elementNum
ObjList* newObjList(VM* vm, uint32_t elementNum) {
   //存储list元素的缓冲区
   Value* elementArray = NULL;

   //先分配内存,后调用initObjHeader, 先分配内存有好处，避免gc无谓的遍历
   // 垃圾回收会在memManager（内存分配函数）函数中添加爱代码
   if (elementNum > 0) { // 如果elementNum为0，则不会进入此代码块
      elementArray = ALLOCATE_ARRAY(vm, Value, elementNum);
   }
   ObjList* objList = ALLOCATE(vm, ObjList); 

   objList->elements.datas = elementArray; // XXXBuffer中用于存储数据的是其中的datas指向的缓冲区
   objList->elements.capacity = objList->elements.count = elementNum;
   initObjHeader(vm, &objList->objHeader, OT_LIST, vm->listClass);
   return objList;
}

//在objlist中索引为index处插入value, 类似于list[index] = value
// 只支持一个元素的插入，在插入新元素之前，需要将index后面的元素后移一位 primListInsert函数内部使用
void insertElement(VM* vm, ObjList* objList, int32_t index, Value value) {
   // 如果index为负数，但是使用uint32_t，则index会变成无符号数，会扭曲语义
   if (index < 0 || index > (int32_t)(objList->elements.count - 1)) { // 暂时先这么改，索引为负数时报错
      RUN_ERROR("index out bounded: " + index);
   }

   if (VALUE_IS_OBJ(value)) {
      pushTmpRoot(vm, VALUE_TO_OBJ(value));
   }
   //准备一个Value的空间以容纳新元素产生的空间波动
   //即最后一个元素要后移1个空间
   ValueBufferAdd(vm, &objList->elements, VT_TO_VALUE(VT_NULL));
   if (VALUE_IS_OBJ(value)) {
      popTmpRoot(vm);
   }
   
   //下面使index后面的元素整体后移一位
   uint32_t idx = objList->elements.count - 1;
   while ((int32_t)idx > index) {
      objList->elements.datas[idx] = objList->elements.datas[idx - 1];
      idx--;
   }

   //在index处插入数值
   objList->elements.datas[index] = value;
}

//调整list容量 容量即最大可容纳元素数量 调整容量到对应内存大小
static void shrinkList(VM* vm, ObjList* objList, uint32_t newCapacity) {
   uint32_t oldSize = objList->elements.capacity * sizeof(Value);
   uint32_t newSize = newCapacity * sizeof(Value);
   memManager(vm, objList->elements.datas, oldSize, newSize);
   objList->elements.capacity = newCapacity;
}

//删除list中索引为index处的元素,即删除list[index]
Value removeElement(VM* vm, ObjList* objList, uint32_t index) {
   Value valueRemoved = objList->elements.datas[index];

   if (VALUE_IS_OBJ(valueRemoved)) {
      pushTmpRoot(vm, VALUE_TO_OBJ(valueRemoved));
   }
   //使index后面的元素前移一位,覆盖index处的元素
   uint32_t idx = index;
   while (idx < objList->elements.count) {
      objList->elements.datas[idx] = objList->elements.datas[idx + 1];
      idx++;
   }

   //若容量利用率过低就减小容量
   uint32_t _capacity = objList->elements.capacity / CAPACITY_GROW_FACTOR;
   if (_capacity > objList->elements.count) { // 小于列表容量的1/4，调整空间
      shrinkList(vm, objList, _capacity);
   }
   if (VALUE_IS_OBJ(valueRemoved)) {
      popTmpRoot(vm);
   }

   objList->elements.count--; // 减少一个元素
   return valueRemoved;
}
