/*
 * pipedemo.c
 *
 *  Created on: 2016年5月4日
 *      Author: zhiteng.he
 */

#include <unistd.h>
#include <string.h>
#include <stdio.h>

//int pipe(int filedes[2]);
//filedes[0]:read
//filedes[1]:write
//必须在fork()中调用pipe()，否则子进程不会继承文件描述符
//两个进程不共享祖先进程，就不能使用pipe。但是可以使用命名管道
int main()
{
    int result = -1;
    int fd[2], nbytes;
    pid_t pid;
    char str[] = "my name is kingstar, now it's FIS!";
    char readbuffer[100];
    result = pipe(fd);
    if (result == -1)
    {
        printf("failed to pipe!\n");
        return -1;
    }

    pid = fork();

    if (pid == -1)
    {
        printf("failed to fork!\n");
        return -1;
    }

    if (pid == 0)   // son
    {
        close(fd[0]);
        result = write(fd[1], str, strlen(str));
        return 0;
    }
    else
    {
        close(fd[1]);
        nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
        printf("the parent receive %d bytes data:%s\n", nbytes, readbuffer);

    }
    return 0;
}

// 发生阻塞的例子
#define K 1024
#define WRITELEN (128*K)
int main()
{
    int fd[2] = {0};
    int nbytes = 0;
    char readbuffer[10 * K] = {0};
    pid_t pid;

    char str[WRITELEN] = "my name is kingstar, now it's FIS!\n ok, 阻塞开始了... ...";
    int result = -1;
    result = pipe(fd);
    if (result == -1)
    {
        printf("failed to pipe!\n");
        return -1;
    }

    pid = fork();
    if (pid == -1)
    {
        printf("failed to fork!\n");
        return -1;
    }

    if (pid == 0)   // son
    {
        close(fd[0]);

        int size = WRITELEN;
        while (size >= 0)	// =0的目的是为了让write执行两次
        {
            result = write(fd[1], str, WRITELEN);
			printf("result=%d size=%d\n", result, size);
            if (result > 0)
            {
			
                size -= result;
                printf("the son write %d bytes data, the rest is %d bytes\n", result, size);
            }
            else
            {
                sleep(10);
            }
        }
        printf("son is over\n");
        return 0;
    }
    else    // parent
    {
        close(fd[1]);
        while (1)
        {
            nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
            if (nbytes <= 0)
            {
                printf("no data had writen \n");
                break;
            }
            printf("recieve %d bytes data:%s \n", nbytes, readbuffer);
        }
    }
    return 0;
}
