#ifndef _CLI_CLI_H
#define _CLI_CLI_H

// #ifdef _WIN32
// #define VERSION "0.1.1" + _WIN64 ? "64bit" : "32bit"
// #else
// #define VERSION "0.1.1" + __WORDSIZE == 32 ? "32bit" : "64bit"
// #endif
#define VERSION "0.1"
#define OSBIT sizeof(char *) == 4 ? "32bit" : "64bit"

#define MAX_LINE_LEN 1024

#endif
