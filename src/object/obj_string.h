#ifndef _OBJECT_STRING_H
#define _OBJECT_STRING_H
#include "../object/header_obj.h"

typedef struct {
   ObjHeader objHeader; // 对象都有自己的objHeader
   uint32_t hashCode;  //字符串的哈希值
   CharValue value; // 值，不同对象的值有不同的含义，对于字符串对象来说，值就是字符串
} ObjString; // 字符串对象

uint32_t hashString(char* str, uint32_t length); // 计算以str为起始，长度为length的字符串的哈希值，采用的算法是fnv-la
// fnv-la算法的特点是，哈希速度快，结果高度分散，因此碰撞率较低
void hashObjString(ObjString* objString); // 用于计算objString的哈希值，并将结果存入到objString->hashCode中
ObjString* newObjString(VM* vm, const char* str, uint32_t length); // 用字符串str创建字符串对象
#endif
