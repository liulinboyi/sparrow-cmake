#include "cli.h"
#include <stdio.h>
#include <string.h>
#include "../parser/parser.h"
#include "../vm/vm.h"
#include "../vm/core.h"

void VOS_FREE(void *pData);

void VOS_FREE(void *pData)
{
   if (NULL != pData)
   {
      free(pData);
      pData = NULL;
   }
   return;
}

//执行脚本文件
static void runFile(const char *path /*路径*/)
{
   // 设置rootDir，是脚本文件所在的根目录
   const char *lastSlash = strrchr(path, '/'); // 最后一次出现/字符的位置
   if (lastSlash != NULL)
   {
      // char a[] = {*lastSlash};
      // printf("lastSlash: %ld\n",sizeof(a));
      // printf("lastSlash: %ld\n", strlen(lastSlash));
      // printf("path: %ld\n", strlen(path));
      // printf("%s\n", lastSlash);
      // printf("%s\n", path);
      // printf("lastSlash - path: %ld\n", lastSlash - path);
      // printf("lastSlash - path + 2: %ld\n", lastSlash - path + 2);
      char *root = (char *)malloc(lastSlash - path + 2);
      memcpy(root, path, lastSlash - path + 1);
      root[lastSlash - path + 1] = '\0';
      rootDir = root;
   }

   VM *vm = newVM();
   const char *sourceCode = readFile(path);
   // executeModule(vm, OBJ_TO_VALUE(newObjString(vm, path, strlen(path))), sourceCode);
   // freeVM(vm);

   // 测试parser
   struct parser parser;
   initParser(vm, &parser, path, sourceCode,NULL);

   #include "../parser/token.list"
   while (parser.curToken.type != TOKEN_EOF)
   {
      getNextToken(&parser);
      printf("%dL: %s [", parser.curToken.lineNo, tokenArray[parser.curToken.type]);
      uint32_t idx = 0;
      while (idx < parser.curToken.length)
      {
         printf("%c", *(parser.curToken.start + idx++));
      }
      printf("]\n");
   }
   // 测试parser
}

//运行命令行
static void runCli(void)
{
   VM *vm = newVM();
   char sourceLine[MAX_LINE_LEN];
   printf("maque Version: %s %s\n", VERSION, OSBIT);
   while (true)
   {
      printf(">>> ");

      //若读取失败或者键入quit就退出循环
      if (!fgets(sourceLine, MAX_LINE_LEN, stdin) ||
          memcmp(sourceLine, "quit", 4) == 0)
      {
         break;
      }
      executeModule(vm, OBJ_TO_VALUE(newObjString(vm, "cli", 3)), sourceLine);
   }
   freeVM(vm);
}

int main(int argc, const char **argv)
{
   if (argc == 1)
   {
      runCli();
   }
   else
   {
      runFile(argv[1]);
   }
   return 0;
}
