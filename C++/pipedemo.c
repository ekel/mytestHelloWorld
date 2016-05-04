/*
 * pipedemo.c
 *
 *  Created on: 2016��5��4��
 *      Author: zhiteng.he
 */

#include <unistd.h>
#include <string.h>
#include <stdio.h>

//int pipe(int filedes[2]);
//filedes[0]:read
//filedes[1]:write
//������fork()�е���pipe()�������ӽ��̲���̳��ļ�������
//�������̲��������Ƚ��̣��Ͳ���ʹ��pipe�����ǿ���ʹ�������ܵ�
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


