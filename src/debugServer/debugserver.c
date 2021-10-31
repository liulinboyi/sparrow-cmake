//
// Created by xiaoliu on 2021/10/30.
//

//#include "debugserver.h"
#include <stdio.h>

#include <sys/stat.h>
#include <fcntl.h>

#if WIN32
#include <winsock2.h>
#include <windows.h>
#include<ws2tcpip.h>

#pragma comment(lib, "wsock32.lib")

#endif

#include <errno.h>
#include<stdlib.h>
#include<string.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>

#define SERVER_PORT 13337


#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

struct DArray {
    int capcity;
    int n;
    int arr[];//还可以写成这样 int arr[0];
//    int *arr;//替换柔性数组
};

//message
struct Message {
    int length;
    int content[];
};


struct DArray *getCmd(char *buffer, char split) {
    int capcity = 3;
    struct DArray *ps = (struct DArray *) malloc(sizeof(struct DArray) + capcity * sizeof(int));
    ps->capcity = capcity;
    ps->n = 0;

    int tempIndex = 0;
    char *tempBuffer = buffer;
    char cur = *buffer;
    char *aa = malloc(strlen(buffer));
    char *aaTemp = aa;
    while (cur != '\0') {
        cur = *tempBuffer;
        *aa = cur;
        if (cur == split) {
            if (ps->capcity - 1 < tempIndex) {
                int tempCapcity = ps->capcity * 2;
                struct DArray *ptr = (struct DArray *) realloc(ps,
                                                               sizeof(struct DArray) + tempCapcity * sizeof(int));
                ptr->capcity = tempCapcity;
                ps = ptr;
            }
            *aa = '\0';
            ps->arr[tempIndex] = aaTemp;
            ps->n++;
            aa = malloc(strlen(buffer));
            aaTemp = aa;
            tempIndex++;

            tempBuffer++;
        } else {
            aa++;
            tempBuffer++;
        }
    }
    if (ps->capcity - 1 < tempIndex) {
        int tempCapcity = ps->capcity * 2;
        struct DArray *ptr = (struct DArray *) realloc(ps,
                                                       sizeof(struct DArray) + tempCapcity * sizeof(int));
        ptr->capcity = tempCapcity;
        ps = ptr;
    }
    ps->arr[tempIndex] = aaTemp;
    ps->n++;
    return ps;
}

void join(struct Message *buffer, char *allContent) {
    int ii = 0;
    for (int j = 0; j < buffer->length; j++) {
        int len = strlen(buffer->content[j]);
        for (int k = 0; k < len; k++) {
            char temp = *((char *) buffer->content[j] + k);
//            char *aa = " ";
//            if (temp == '\xa0') {
//                // Remove these two lines for quality time debugging in case the user has special
//                // spaces with code 160. See https://en.wikipedia.org/wiki/Non-breaking_space
//                allContent[ii] = aa[0];
//            } else {
//                allContent[ii] = temp;
//            }
            allContent[ii] = temp;
            ii++;
        }
        allContent[ii] = '\n';
        ii++;
    }
    allContent[ii] = '\0';
    printf("%s", allContent);
}

struct Action {
    char *file;
    char *next;
    char *setbp;
    char *bye;
};

struct Action action = {
        "file",
        "next",
        "setbp",
        "bye",
};

struct stat sb;
struct Message *FIlebuffer;

void process(char *buffer, int client, int serverSocket) {
    struct DArray *res = getCmd(buffer, '\n');
    int line = 0;
    if (FIlebuffer == NULL) {
        FIlebuffer = (struct Message *) malloc(sizeof(struct Message) + sb.st_size * sizeof(int));
    }
    for (int i = 0; i < res->n; i++) {
        char *aa = (char *) res->arr[i];
        printf("%s\n", aa);
        struct DArray *temp = getCmd(aa, '|');
        char *ac = (char *) temp->arr[0];

        if (*ac == *action.file) {
//            printf("file");
            char *filename = (char *) temp->arr[1];
            FILE *in_file = fopen(filename, "r");

            stat(filename, &sb);

            char *file_contents = malloc(sb.st_size);

            int index = 0;
            FIlebuffer->length = 0;

            while (fscanf(in_file, "%[^\n] ", file_contents) != EOF) {
                printf("> %s\n", file_contents);
                char *tempContent = malloc(strlen(file_contents) + 1);
                memcpy(tempContent, file_contents, strlen(file_contents) + 1);
                FIlebuffer->content[index] = (char *) tempContent;
                FIlebuffer->length++;
                index++;
            }

            int Allsize = 0;
            for (int j = 0; j < FIlebuffer->length; j++) {
                printf("%s\n", FIlebuffer->content[j]);
                Allsize += strlen(FIlebuffer->content[j]);
            }

            fclose(in_file);

            char *allContent = malloc(Allsize + FIlebuffer->length + 1);
            join(FIlebuffer, allContent);
            printf("%s\n", allContent);
//            char *na = "N/A";
            char *na = "";
            char *tempRes = malloc(strlen(na) + strlen(ac) + 2);
            memccpy(tempRes, ac, 0, strlen(ac));
            tempRes[strlen(ac)] = '\n';
            memccpy(tempRes + strlen(ac) + 1, na, 0, strlen(na));
            tempRes[strlen(ac) + strlen(na) + 1] = '\0';
            printf("%s\n", tempRes);
            send(client, tempRes, strlen(tempRes), 0); //服务端也向客户端发送消息

        } else if (*ac == *action.setbp) {

        } else if (*ac == *action.next) {
            int contentLength = strlen((char *) FIlebuffer->content[line]);
//            int filePathLength = strlen((char *) res->arr[1]);
//            char *content = malloc(strlen(action.next) + filePathLength + 3);
//            memccpy(content, action.next, 0, strlen(action.next));
//
//            content[strlen(action.next)] = '\n';
//            memccpy(content + strlen(action.next) + 1, (char *) res->arr[1], 0, filePathLength);
//
//            content[strlen(action.next) + filePathLength + 1] = '\0';
//            send(client, content, strlen(content), 0); //服务端也向客户端发送消息

//            send(client, (char *) FIlebuffer->content[line], contentLength, 0); //服务端也向客户端发送消息
//mock
            char *res = "next\n"
                        "/home/xiaoliu/spr/test-2.cscs\n"
                        "1\n"
                        "1\n"
                        "\n"
                        "2\n"
                        "this:1:array:[]\n"
                        "a:1:number:5\n"
                        "1\n"
                        "/home/xiaoliu/spr/test-2.cscs\n"
                        "b = 200;";
            send(client, res, strlen(res), 0);
        } else if (*ac == *action.bye) {
            close(serverSocket);
            exit(1);
        }
    }
}

void hello() {
    printf("hello");
};

/*
监听后，一直处于accept阻塞状态，
直到有客户端连接，
当客户端如数quit后，断开与客户端的连接
*/
int server() {

    //调用socket函数返回的文件描述符
    int serverSocket;

    //声明两个套接字sockaddr_in结构体变量，分别表示客户端和服务器
    struct sockaddr_in server_addr;
    struct sockaddr_in clientAddr;

    int addr_len = sizeof(clientAddr);
    int client;
    struct Message *buffer = (struct Message *) malloc(sizeof(struct Message) + 500 * sizeof(int));
//    char *buffer[200]; //存储 发送和接收的信息
    int iDataNum;

#if WIN32
    //必须先初始化
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
        printf("require version fail!");
        return -1;
    }
#endif

    //socket函数，失败返回-1
    //int socket(int domain, int type, int protocol);
    //第一个参数表示使用的地址类型，一般都是ipv4，AF_INET
    //第二个参数表示套接字类型：tcp：面向连接的稳定数据传输SOCK_STREAM
    //第三个参数设置为0
    //建立socket
    if ((serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        perror("socket");
        return 1;
    }
//    如何解决程序退出重启后不能绑定端口的问题？
//https://blog.csdn.net/persistvonyao/article/details/18601623
    int opt = 1;
    int len = sizeof(opt);
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, len);

    //初始化 server_addr
    memset(&server_addr, 0, sizeof(server_addr));

    //初始化服务器端的套接字，并用htons和htonl将端口和地址转成网络字节序
//    server_addr.sin_family = AF_INET;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);

    //ip可是是本服务器的ip，也可以用宏INADDR_ANY代替，代表0.0.0.0，表明所有地址
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
//    char *address = "127.0.0.1";
//    server_addr.sin_addr.s_addr = inet_addr(address);
    //对于bind，accept之类的函数，里面套接字参数都是需要强制转换成(struct sockaddr *)
    //bind三个参数：服务器端的套接字的文件描述符，
    if (bind(serverSocket, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        perror("connect");
        return 1;
    }

    //设置服务器上的socket为监听状态
    if (listen(serverSocket, 5) < 0) {
        perror("listen");
        return 1;
    }

    //循环 接收消息、发送消息

    printf("监听端口: %d\n", SERVER_PORT);

    //调用accept函数后，会进入阻塞状态
    //accept返回一个套接字的文件描述符，这样服务器端便有两个套接字的文件描述符，
    //serverSocket和client。
    //serverSocket仍然继续在监听状态，client则负责接收和发送数据
    //clientAddr是一个传出参数，accept返回时，传出客户端的地址和端口号
    //addr_len是一个传入-传出参数，传入的是调用者提供的缓冲区的clientAddr的长度，以避免缓冲区溢出。
    //传出的是客户端地址结构体的实际长度。
    //出错返回-1

    client = accept(serverSocket, (struct sockaddr *) &clientAddr, (socklen_t *) &addr_len);

    if (client < 0) {
        perror("accept");
//            continue;
    }

    printf("等待消息...\n");

    //inet_ntoa ip地址转换函数，将网络字节序IP转换为点分十进制IP
    //表达式：char *inet_ntoa (struct in_addr);
    printf("IP is %s\n", inet_ntoa(clientAddr.sin_addr)); //把来访问的客户端的IP地址打出来
    printf("Port is %d\n", htons(clientAddr.sin_port));

    while (1) {

//        read(client, buffer->content, 4096);
        sleep(1.5);
        recv(client, buffer->content, 4096, 0);
        printf("收到消息: %s\n", buffer->content);
        process(buffer->content, client, serverSocket);
    }
//    close(serverSocket);
//
//    return 0;

}