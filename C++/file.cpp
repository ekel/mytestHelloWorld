/*------
��Ҫ�Ǵ����ini�ļ� ���ж�ȡÿ������  Ȼ�����ȡ�����ַ���


--------------*/
#include <fstream>
#include <stdio>

int parseIni()
{
    char str[255] = {0};
    FILE * pFile;
    char *pch;
    int n = 0;
    pFile = fopen ("demo.ini","r");
    if (pFile != NULL)
    {
        while ( fgets (str, 100, pFile) != NULL )
        {
            if ((pch = strtok (str, "//")) == NULL)
            continue;
            
            n = strlen(pch);
            pch[n-1] = '\0';
            if ((pch = strtok (pch, "//")) == NULL)
                continue;
            
            if (strstr(pch, "ip") != NULL || strstr(pch, "IP") != NULL)
            {
                strcpy(g_szDrtpIP, pch+3);
            }
            if (strstr(pch, "port") != NULL || strstr(pch, "PORT") != NULL)
            {
                g_iDrtpPort = atoi(pch+5);
            }
            if (strstr(pch, "operator") != NULL || strstr(pch, "OPERATOR") != NULL)
            {
                strcpy(g_szOper, pch+9);
            }
        }

        fclose (pFile);
    }
}