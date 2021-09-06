#include "utils.h"
#include "../vm/vm.h"
#include "../parser/parser.h"
#include <stdlib.h>
#include <stdarg.h>
#include "../gc/gc.h"

//内存管理三种功能:
//   1 申请内存
//   2 修改空间大小
//   3 释放内存
void *memManager(VM *vm, void *ptr, uint32_t oldSize, uint32_t newSize)
{
   //累计系统分配的总内存
   vm->allocatedBytes += newSize - oldSize;

   //避免realloc(NULL, 0)定义的新地址,此地址不能被释放
   if (newSize == 0)
   {
      free(ptr);
      return NULL;
   }

   //在分配内存时若达到了GC触发的阀值则启动垃圾回收
   if (newSize > 0 && vm->allocatedBytes > vm->config.nextGC)
   {
      startGC(vm); // gc时会停止整个解析器，即垃圾回收时，整个程序不得不先暂停
   }

   return realloc(ptr, newSize);
}

// 找出大于等于v最近的2次幂
uint32_t ceilToPowerOf2(uint32_t v)
{
   v += (v == 0); //修复当v等于0时结果为0的边界情况
   v--;
   v |= v >> 1; // 位或赋值运算符
   v |= v >> 2;
   v |= v >> 4;
   v |= v >> 8;
   v |= v >> 16;
   v++;
   return v;
}

DEFINE_BUFFER_METHOD(String)
DEFINE_BUFFER_METHOD(Int)
DEFINE_BUFFER_METHOD(Char)
DEFINE_BUFFER_METHOD(Byte)

void symbolTableClear(VM *vm, SymbolTable *buffer)
{
   uint32_t idx = 0;
   while (idx < buffer->count)
   {
      memManager(vm, buffer->datas[idx++].str, 0, 0);
   }
   StringBufferClear(vm, buffer);
}

//通用报错函数
void errorReport(void *parser,
                 ErrorType errorType, const char *fmt, ...)
{
   char buffer[DEFAULT_BUfFER_SIZE] = {'\0'};
   va_list ap;
   va_start(ap, fmt);
   vsnprintf(buffer, DEFAULT_BUfFER_SIZE, fmt, ap);
   va_end(ap);

   switch (errorType)
   {
   case ERROR_IO:  // 文件io报错
   case ERROR_MEM: // 内存分配错误
      fprintf(stderr, "%s:%d In function %s():%s\n",
              __FILE__, __LINE__, __func__, buffer);
      break;
   case ERROR_LEX:     // 词法分析错误
   case ERROR_COMPILE: // 编译错误
      ASSERT(parser != NULL, "parser is null!");
      Parser *p = (Parser *)parser;
      fprintf(stderr, "%s:%d \"%s\"\n", p->file,
              p->preToken.lineNo, buffer);
      break;
   case ERROR_RUNTIME: // 虚拟机运行时阶段报错
      fprintf(stderr, "%s\n", buffer);
      break;
   default:
      NOT_REACHED();
   }
   exit(1);
}
