#ifndef _OBJECT_HEADER_H
#define _OBJECT_HEADER_H
#include "../include/utils.h"
typedef enum {
   OT_CLASS,   //此项是class类型,类 以下都是object类型
   OT_LIST, // list类型 列表
   OT_MAP, // map类型 散列数组
   OT_MODULE, // module类型 模块作用域
   OT_RANGE, // range类型 表示步进为1的数字范围
   OT_STRING, // string类型 即字符串
   OT_UPVALUE, // upvalue(上值)类型 自由变量，闭包中的概念
   OT_FUNCTION, // function类型 函数
   OT_CLOSURE, // closure类型 闭包
   OT_INSTANCE, // instance 即实例，对象实例
   OT_THREAD // thread类型 线程实例
} ObjType;  //对象类型

typedef struct objHeader {
   ObjType type;
   bool isDark;	   //对象是否可达
   Classes* classes;   //指向对象本身所属的类 其类型是Class
   struct objHeader* next;   //用于链接所有已分配对象 指向下一个创建的对象 所有对象的链接形成已分配对象链表
} ObjHeader;	  //对象头,用于记录元信息和垃圾回收

typedef enum {
   VT_UNDEFINED, // 未定义
   VT_NULL, // 空值
   VT_FALSE, // 布尔假
   VT_TRUE, // 布尔真
   VT_NUM, // 数字类型
   VT_OBJ   //值为对象,指向对象头
} ValueType;     //value类型 值类型 脚本语言对用户是弱类型，我们要在背后区分数据类型以分别对待

typedef struct {
   ValueType type; // 此值类型
   // 共用体是一种特殊的数据类型，允许您在相同的内存位置存储不同的数据类型。
   // 您可以定义一个带有多成员的共用体，但是任何时候只能有一个成员带有值。
   // 共用体提供了一种使用相同的内存位置的有效方式。
   union { // 表示数值，包括数字和对象两种
      double num;
      ObjHeader* objHeader; // object指向具体对象的header
   };
} Value;   //通用的值结构

DECLARE_BUFFER_TYPE(Value) // 生成valueBuffer定义，以及相应的方法

void initObjHeader(VM* vm, ObjHeader* objHeader, ObjType objType, Classes* classes);
#endif
