#ifndef _INCLUDE_UTILS_H
#define _INCLUDE_UTILS_H
#include "../include/common.h"

void *memManager(VM *vm, void *ptr, uint32_t oldSize, uint32_t newSize);
// 分配类型为type的内存块
#define ALLOCATE(vmPtr, type) \
   (type *)memManager(vmPtr, NULL, 0, sizeof(type))
// 除了mainType之外，还需要分配extraSize大小的内存，用于实现柔性数组的功能
#define ALLOCATE_EXTRA(vmPtr, mainType, extraSize) \
   (mainType *)memManager(vmPtr, NULL, 0, sizeof(mainType) + extraSize)
// 用于分配数组内存
#define ALLOCATE_ARRAY(vmPtr, type, count) \
   (type *)memManager(vmPtr, NULL, 0, sizeof(type) * count)
// 用于释放数组占用的内存
#define DEALLOCATE_ARRAY(vmPtr, arrayPtr, count) \
   memManager(vmPtr, arrayPtr, sizeof(arrayPtr[0]) * count, 0)
// 用于释放内存
#define DEALLOCATE(vmPtr, memPtr) memManager(vmPtr, memPtr, 0, 0)

uint32_t ceilToPowerOf2(uint32_t v);

typedef struct
{
   char *str;
   uint32_t length;
} String; // 用于存储字符串,为后面定义String类型缓冲区做准备

typedef struct
{
   uint32_t length; //除结束'\0'之外的字符个数 长度由length控制,
   char start[0];   //类似c99中的柔性数组 字符串长度不定,使用柔性数组
} CharValue;        //字符串缓冲区 用于存储字符串对象(ObjectString)中的字符串

//声明buffer类型 整个语言的核心存储结构:type#Buffer结构体,其中##是预处理提供的字符串连接符,若type为String则生成的结构体名称StringBuffer
#define DECLARE_BUFFER_TYPE(type)                                                \
   typedef struct                                                                \
   {                                                                             \
      /* 数据缓冲区 */                                                      \
      type *datas;                                                               \
      /*缓冲区中已使用的元素个数*/                                   \
      uint32_t count;                                                            \
      /*缓冲区容量用*/                                                     \
      uint32_t capacity;                                                         \
   } type##Buffer;                                                               \
   void type##BufferInit(type##Buffer *buf);                                     \
   void type##BufferFillWrite(VM *vm,                                            \
                              type##Buffer *buf, type data, uint32_t fillCount); \
   void type##BufferAdd(VM *vm, type##Buffer *buf, type data);                   \
   void type##BufferClear(VM *vm, type##Buffer *buf);

//定义buffer方法
#define DEFINE_BUFFER_METHOD(type)                                              \
   void type##BufferInit(type##Buffer *buf) /*初始化缓冲区*/                                     \
   {                                                                            \
      buf->datas = NULL;                                                        \
      buf->count = buf->capacity = 0;                                           \
   }                                                                            \
                                                                                \
   void type##BufferFillWrite(VM *vm,                                           \
                              type##Buffer *buf, type data, uint32_t fillCount) \
   {                                                                            \
      uint32_t newCounts = buf->count + fillCount; /*已使用加上添加的为新的已使用*/                              \
      if (newCounts > buf->capacity) /*新的已使用大于总容量->需要扩容*/                                            \
      {                                                                         \
         size_t oldSize = buf->capacity * sizeof(type);/*数量乘以大小*/                         \
         buf->capacity = ceilToPowerOf2(newCounts); /*计算新的容*/                             \
         size_t newSize = buf->capacity * sizeof(type);/*数量乘以大小*/                         \
         ASSERT(newSize > oldSize, "faint...memory allocate!");                 \
         buf->datas = (type *)memManager(vm, buf->datas, oldSize, newSize);     \
      }                                                                         \
      uint32_t cnt = 0;/*扩容之后写入data*/                                                         \
      while (cnt < fillCount)                                                   \
      {                                                                         \
         buf->datas[buf->count++] = data;                                       \
         cnt++;                                                                 \
      }                                                                         \
   }                                                                            \
                                                                                \
   void type##BufferAdd(VM *vm, type##Buffer *buf, type data)                   \
   {                                                                            \
      type##BufferFillWrite(vm, buf, data, 1);                                  \
   }                                                                            \
                                                                                \
   void type##BufferClear(VM *vm, type##Buffer *buf)                            \
   {                                                                            \
      size_t oldSize = buf->capacity * sizeof(buf->datas[0]);                   \
      memManager(vm, buf->datas, oldSize, 0);                                   \
      type##BufferInit(buf);                                                    \
   }

DECLARE_BUFFER_TYPE(String)
#define SymbolTable StringBuffer
typedef uint8_t Byte;
typedef char Char;
typedef int Int;
DECLARE_BUFFER_TYPE(Int)
DECLARE_BUFFER_TYPE(Char)
DECLARE_BUFFER_TYPE(Byte)

typedef enum
{
   ERROR_IO,
   ERROR_MEM,
   ERROR_LEX,
   ERROR_COMPILE,
   ERROR_RUNTIME
} ErrorType;

void errorReport(void *parser,
                 ErrorType errorType, const char *fmt, ...);

void symbolTableClear(VM *, SymbolTable *buffer);

#define IO_ERROR(...) \
   errorReport(NULL, ERROR_IO, __VA_ARGS__)

#define MEM_ERROR(...) \
   errorReport(NULL, ERROR_MEM, __VA_ARGS__)

#define LEX_ERROR(parser, ...) \
   errorReport(parser, ERROR_LEX, __VA_ARGS__)

#define COMPILE_ERROR(parser, ...) \
   errorReport(parser, ERROR_COMPILE, __VA_ARGS__)

#define RUN_ERROR(...) \
   errorReport(NULL, ERROR_RUNTIME, __VA_ARGS__)

#define DEFAULT_BUfFER_SIZE 512

#endif
