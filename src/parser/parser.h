#ifndef _PARSER_PARSER_H
#define _PARSER_PARSER_H
#include "../include/common.h"
#include "../vm/vm.h"
#include "../object/class.h"
#include "../compiler/compiler.h"

typedef enum {
   TOKEN_UNKNOWN,
   // 数据类型
   TOKEN_NUM,		   //数字
   TOKEN_STRING,     	   //字符串
   TOKEN_ID,	     	   //变量名 
   TOKEN_INTERPOLATION,     //内嵌表达式

   // 关键字(系统保留字)
   TOKEN_VAR,		   //'var'
   TOKEN_FUN,		   //'fun'
   TOKEN_IF,		   //'if'
   TOKEN_ELSE,	     	   //'else'	
   TOKEN_TRUE,	     	   //'true'
   TOKEN_FALSE,	     	   //'false'
   TOKEN_WHILE,	     	   //'while'
   TOKEN_FOR,	     	   //'for'
   TOKEN_BREAK,	     	   //'break'
   TOKEN_CONTINUE,         //'continue'
   TOKEN_RETURN,     	   //'return'
   TOKEN_NULL,	     	   //'null'

   //以下是关于类和模块导入的token
   TOKEN_CLASS,	     	   //'class'
   TOKEN_THIS,	     	   //'this'
   TOKEN_STATIC,     	   //'static'
   TOKEN_IS,		   // 'is'
   TOKEN_SUPER,	     	   //'super'
   TOKEN_IMPORT,     	   //'import'

   //分隔符
   TOKEN_COMMA,		   //','
   TOKEN_COLON,		   //':'
   TOKEN_LEFT_PAREN,	   //'('
   TOKEN_RIGHT_PAREN,	   //')'
   TOKEN_LEFT_BRACKET,	   //'['
   TOKEN_RIGHT_BRACKET,	   //']'
   TOKEN_LEFT_BRACE,	   //'{'
   TOKEN_RIGHT_BRACE,	   //'}'
   TOKEN_DOT,		   //'.'
   TOKEN_DOT_DOT,	   //'..'
   
   //简单双目运算符
   TOKEN_ADD,		   //'+'
   TOKEN_SUB,		   //'-'
   TOKEN_MUL,		   //'*' 
   TOKEN_DIV,		   //'/' 
   TOKEN_MOD,		   //'%'

   //赋值运算符
   TOKEN_ASSIGN,	   //'='

   // 位运算符
   TOKEN_BIT_AND,	   //'&'
   TOKEN_BIT_OR,	   //'|'
   TOKEN_BIT_NOT,	   //'~'
   TOKEN_BIT_SHIFT_RIGHT,  //'>>'
   TOKEN_BIT_SHIFT_LEFT,   //'<<'

   // 逻辑运算符
   TOKEN_LOGIC_AND,	   //'&&'
   TOKEN_LOGIC_OR,	   //'||'
   TOKEN_LOGIC_NOT,	   //'!'

   //关系操作符
   TOKEN_EQUAL,		   //'=='
   TOKEN_NOT_EQUAL,	   //'!='
   TOKEN_GREATE,	   //'>'
   TOKEN_GREATE_EQUAL,	   //'>='
   TOKEN_LESS,		   //'<'
   TOKEN_LESS_EQUAL,	   //'<='

   TOKEN_QUESTION,	   //'?'

   //文件结束标记,仅词法分析时使用
   TOKEN_EOF		   //'EOF'
} TokenType;

typedef struct {
   TokenType type;
   const char* start; // 源码串的起始地址
   uint32_t length; // 此单词长度
   uint32_t lineNo; // 在源码中的行号
   Value value; // 存储单词的值
} Token;

// 词法分析器结构
struct parser {
   const char* file; // 通常指向源码文件名 由此知道当前在编译那个文件 编译的源码也可能不在文件中，是内部用源码定义的数据
   const char* sourceCode; // 指向源码串 将源码读取到缓冲区，然后用sourceCode指向缓冲区
   const char* nextCharPtr; // 指向sourceCode下一个字符
   const char* curCharPtr; // 指向sourceCode当前字符串
   char curChar; // 识别到的当前字符
   Token curToken; // 当前token
   Token preToken; // 前一个token，有时需要前一个token
   ObjModule* curModule;    // 当前正在编译的模块
   CompileUnit* curCompileUnit;   // 当前编译单元

   //处于内嵌表达式之中时,期望的右括号数量.
   //用于跟踪小括号对儿的嵌套
   int interpolationExpectRightParenNum;
   struct parser* parent;  //指向父parser
   VM* vm; // 表示parser隶属于那个vm
};

#define PEEK_TOKEN(parserPtr) parserPtr->curToken.type

char lookAheadChar(Parser* parser);
void getNextToken(Parser* parser);
bool matchToken(Parser* parser, TokenType expected);
void consumeCurToken(Parser* parser, TokenType expected, const char* errMsg);
void consumeNextToken(Parser* parser, TokenType expected, const char* errMsg);
uint32_t getByteNumOfEncodeUtf8(int value);
uint8_t encodeUtf8(uint8_t* buf, int value);
void initParser(VM* vm, Parser* parser, const char* file, const char* sourceCode, ObjModule* objModule);
#endif
