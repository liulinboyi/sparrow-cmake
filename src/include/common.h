/*
通用工具类的代码
*/
#ifndef _INCLUDE_COMMON_H
#define _INCLUDE_COMMON_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct vm VM;
typedef struct parser Parser;
typedef struct class Class;

#define bool char
#define true 1
#define false 0
#define UNUSED __attribute__((unused)) // 有些函数不需要函数全部实参，使用gcc内部属性__attribute__((unused))，让gcc不要报警

#ifdef DEBUG
// 调试阶段，出现断言
#define ASSERT(condition, errMsg)                                       \
   do                                                                   \
   {                                                                    \
      if (!(condition))                                                 \
      {                                                                 \
         fprintf(stderr, "ASSERT failed! %s:%d In function %s(): %s\n", \
                 __FILE__, __LINE__, __func__, errMsg);                 \
         abort();                                                       \
      }                                                                 \
   } while (0);
#else
#define ASSERT(condition, errMsg) ((void)0)
#endif

// 不能达到：有些程序分支是不能达到的，如果执行到说明执行错误了，为了检测这些情况，定义了这个宏
#define NOT_REACHED()                                          \
   do                                                          \
   {                                                           \
      fprintf(stderr, "NOT_REACHED: %s:%d In function %s()\n", \
              __FILE__, __LINE__, __func__);                   \
      while (1)                                                \
         ;                                                     \
   } while (0);

#endif
