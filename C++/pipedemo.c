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

// ��������������
#define K 1024
#define WRITELEN (128*K)
int main()
{
    int fd[2] = {0};
    int nbytes = 0;
    char readbuffer[10 * K] = {0};
    pid_t pid;

    char str[WRITELEN] = "my name is kingstar, now it's FIS!\n ok, ������ʼ��... ...";
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
        while (size >= 0)	// =0��Ŀ����Ϊ����writeִ������
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
