#ifndef _OBJECT_LIST_H
#define _OBJECT_LIST_H
#include "../object/class.h"
#include "../vm/vm.h"

typedef struct {
   ObjHeader objHeader;
   ValueBuffer elements;  //list中的元素 元素也是值统一类型为Value
} ObjList;  //list对象

ObjList* newObjList(VM* vm, uint32_t elementNum);
Value removeElement(VM* vm, ObjList* objList, uint32_t index);
void insertElement(VM* vm, ObjList* objList, int32_t index, Value value);
#endif
