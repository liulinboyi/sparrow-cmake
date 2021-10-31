//
// Created by xiaoliu on 2021/10/30.
//

#ifndef SPR_DEBUGSERVER_H
#define SPR_DEBUGSERVER_H


struct DArray {
    int capcity;
    int n;
    int arr[];//还可以写成这样 int arr[0];
//    int *arr;//替换柔性数组
};

void process(char *buffer);

void hello();

int server();

struct Array *getCmd(char *buffer);


#endif //SPR_DEBUGSERVER_H
