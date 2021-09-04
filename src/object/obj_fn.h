#ifndef _OBJECT_FN_H
#define _OBJECT_FN_H
#include "../include/utils.h"
#include "../object/meta_obj.h"

typedef struct {
   char* fnName;     //函数名
   IntBuffer lineNo; //行号
} FnDebug;   //在函数中的调试结构 在语义分析生成指令时会用上此结构

typedef struct {	
   ObjHeader objHeader;
   ByteBuffer instrStream;  //函数编译后的指令流
   ValueBuffer constants;   // 函数中的常量表，用于存储函数中的变量 模块作为最大的指令流单元，
   // 位于模块中的模块变量类的类名都会作为常量存储到模块的常量表中
  
   ObjModule* module;    //本函数所属的模块

   uint32_t maxStackSlotUsedNum; //本函数最多需要的栈空间,是栈使用空间的峰值，是在编译时统计的
   uint32_t upvalueNum;	  //本函数所涵盖的upvalue数量 位于本函数直接或间接外层函数中的局部变量即自由变量
   uint8_t argNum;   //函数期望的参数个数
#if DEBUG
   FnDebug* debug;
#endif
} ObjFn;   //函数对象

typedef struct upvalue {
   ObjHeader objHeader;

   //栈是个Value类型的数组,localVarPtr指向upvalue所关联的局部变量
   Value* localVarPtr; // 用于指向所关联的upvalue 我们的栈是由Value数组实现的

   //已被关闭的upvalue
   Value closedUpvalue;

   struct upvalue* next;   //用以链接openUpvalue链表
} ObjUpvalue;   //upvalue对象

typedef struct {
   ObjHeader objHeader;
   ObjFn* fn;   //闭包中所要引用的函数 “函数”

   ObjUpvalue* upvalues[0]; //用于存储此函数的 "close upvalue" “函数依赖的环境”
} ObjClosure;	  //闭包对象

typedef struct {
   uint8_t* ip;    //程序计数器 指向下一个将被执行的指令

   //在本frame中执行的闭包函数
   ObjClosure* closure;
   
   //frame是共享therad.stack
   //此项用于指向本frame所在thread运行时栈的起始地址
   Value* stackStart;
} Frame;  //调用框架 是函数的一套运行环境

#define INITIAL_FRAME_NUM 4 // 线程中初始化的Frame数量

ObjUpvalue* newObjUpvalue(VM* vm, Value* localVarPtr);
ObjClosure* newObjClosure(VM* vm, ObjFn* objFn);
ObjFn* newObjFn(VM* vm, ObjModule* objModule, uint32_t maxStackSlotUsedNum);
#endif
