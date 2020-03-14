#include <stdio.h>
#include <string.h>
#include <io.h>
#include<iostream>
#include <windows.h>
#include "wc.h"
#define N 100
#define M 100000

//统计字符数
int countChar(char path[N], char file[N])
{
    FILE* fp = NULL;
    errno_t err;
    //英文字符计数器和中文字符计数器
    int n = 0, nC = 0;
    int c[M];
    int i = 0;
    char filePath[N] = { 0 };

    strcpy_s(filePath, path);
    strcat_s(filePath, file);

    err = fopen_s(&fp, filePath, "r");
    if (fp == NULL)
    {
        printf("该文件不存在。\n");
        return -1;
    }
    else {
        //统计字符数（包括字母、数字、英文符号、空格、换行、中文字符）
        for (i = 0; i < M; i++) {
            c[i] = fgetc(fp);
            if (feof(fp))  break;
            else {
                if (c[i] > 127) {
                    //每个中文字和中文符号各占2个字符位
                    c[i + 1] = fgetc(fp);
                    i += 2;
                    nC++;
                }
                else if (c[i] < 0)  
                    break;
                else  n++;
            }
        }
        n -= 1;
        printf("字符数：%d\t中文字：%d\n", n,nC);
    }

    fclose(fp);
    return n;
}

//统计单词数
int countWord(char path[N], char file[N]) {
    FILE* fp = NULL;
    errno_t err;
    int c;
    //计数器
    int n = 0; 
    char filePath[N] = { 0 };

    strcpy_s(filePath, path);
    strcat_s(filePath, file);

    err = fopen_s(&fp, filePath, "r");
    if (fp == NULL)
    {
        printf("该文件不存在。\n");
        return -1;
    }
    do
    {
        c = fgetc(fp);
        if (feof(fp))  break;
        //else if(c == ' ' || c == ',' || c == '.' || c == '!' || c == ':' || c == ';' || c == '?')  n++;
        //通过空格来统计单词数
        else if (c == ' ')  n++;
    } while (1);

    printf("单词数：%d\n", n);

    return n;
}

//统计行数
int countLine(char path[N], char file[N]) {
    FILE* fp = NULL;
    errno_t err;
    char b[N];
    //计数器
    int n = 0;  
    char filePath[N] = { 0 };

    strcpy_s(filePath, path);
    strcat_s(filePath, file);

    err = fopen_s(&fp, filePath, "r");
    if (fp == NULL)
    {
        printf("该文件不存在。\n");
        return -1;
    }
    do {
        //fgets()函数按行读取字符，每读一次为一行，以此计数
        if (fgets(b, N, fp))  n++;
        else break;
    } while (1);

    printf("行数：%d\n", n);

    return n;
}

//统计代码行、空行和注释行
int countElse(char path[N], char file[N]) {
    FILE* fp = NULL;
    errno_t err;
    char b[N];
    //记录代码行数，记录空行数，记录注释行，记录数组长度，记录字符长度，记录两种注释行数（//和/* */），记录三种行的总数
    int codeLine = 0, blankLine = 0, commentLine = 0, length = 0, count_char = 0, countC1 = 0, countC2 = 0, sum = 0;
    int i, j;
    //tag是查找/* */注释符号的前半部分的标记，查找成功记为1，查找失败记为0
    int tag = 0;
    char filePath[N] = { 0 };

    strcpy_s(filePath, path);
    strcat_s(filePath, file);

    err = fopen_s(&fp, filePath, "r");
    if (fp == NULL)
    {
        printf("该文件不存在。\n");
        return -1;
    }
    do {
        //fgets()函数按行读取字符
        if (fgets(b, N, fp)) {
            length = strlen(b);
            for (i = 0, count_char = 0; i < length; i++) {
                if (b[i] != ' ' && b[i] != '\n' && b[i] != '\t')
                    //在一行中，除去空格、换行、\t之外都计入字符数
                    count_char++;
                if (b[i] == '/' && b[i + 1] == '/') {
                    //第一种注释情况，读入的一行为注释行，跳出循环
                    countC1++;
                    //注释行不属于代码行
                    if (count_char > 1)  codeLine--;
                    //注释行不属于空行
                    else  blankLine--;
                    break;
                }
                if (tag == 1) {
                    countC2++;
                    //在该行查找注释的结束符号
                    for (j = i; j < length; j++) {
                        if (b[j] == '*' && b[j + 1] == '/') {
                            /* 查找结束符号成功，该行为注释行 */
                            //注释行不属于代码行
                            if (count_char > 1)  codeLine--;
                            //注释行不属于空行
                            else  blankLine--;
                            //现查找注释行前半部分失败
                            tag = 0;
                            break;
                        }
                    }
                    //tag=0说明该行是完整的注释行，同行查找结束符号成功
                    if (tag == 0)  break;
                    //否则同行查找结束符号失败，把tag置为1
                    else {
                        //注释行不属于代码行
                        if (count_char > 1)  codeLine--;
                        //注释行不属于空行
                        else  blankLine--;
                        break;
                    }
                }
                if (b[i] == '/' && b[i + 1] == '*' && tag == 0) {
                    countC2++;
                    tag = 1;
                    /* 第二种注释情况，读入的一行为注释行，同行查找结束符号 */
                    for (j = i + 2; j < length - 2; j++) {
                        if (b[j] == '*' && b[j + 1] == '/') {
                            /* 查找结束符号成功，该行为注释行 */
                            countC2++;
                            //注释行不属于代码行
                            if (count_char > 1)  codeLine--;
                            //注释行不属于空行
                            else  blankLine--;
                            //现查找注释行前半部分失败
                            tag = 0;
                            break;
                        }
                    }
                    //tag=0说明该行是完整的注释行，同行查找结束符号成功
                    if (tag == 0)  break;
                    //否则同行查找结束符号失败，把tag置为1
                    else {
                        //注释行不属于代码行
                        if (count_char > 1)  codeLine--;
                        //注释行不属于空行
                        else  blankLine--;
                        break;
                    }
                }
            }
            //字符数大于1为代码行，否则为空行
            if (count_char > 1)  codeLine++;
            else  blankLine++;
        }
        else break;
    } while (1);

    commentLine = countC1 + countC2;
    sum = codeLine + blankLine + commentLine;

    printf("代码行：%d\t", codeLine);
    printf("空白行：%d\t", blankLine);
    printf("注释行：%d\n", commentLine);

    //返回注释行
    return commentLine;
}

//递归查找符合条件的文件
int searchFile(char path[N],char mode[N],int tag) {
    //文件句柄
    intptr_t Handle1;
    intptr_t Handle2;
    //文件结构体
    struct _finddata_t fileInfo1;
    struct _finddata_t fileInfo2;
    //.c文件查找路径、所有文件的查找路径、递归路径
    char nowPath_file[N] = { 0 };
    char nowPath_folder[N] = { 0 };
    char nowPath_re[N] = { 0 };
    //查找文件和文件夹的通识符
    char mode_N[N] = { "*.*" };
    int i, num = 0;
    //标记文件夹
    int mark = 0;

    //基本路径
    strcpy_s(nowPath_file, path);
    strcpy_s(nowPath_folder, path);
    strcpy_s(nowPath_re, path);
    //拼接.c文件和所有文件的查找路径
    strcat_s(nowPath_file, mode);
    strcat_s(nowPath_folder, mode_N);

    //根目录的文件句柄
    Handle1 = _findfirst(nowPath_folder, &fileInfo1);
    //.c类型文件的文件句柄
    Handle2 = _findfirst(nowPath_file, &fileInfo2);

    if ((Handle2 = _findfirst(nowPath_file, &fileInfo2)) == -1L)
        printf("该目录中没有找到这种类型的文件。\n");
    else {
        //查找文件后缀名.
        for (i = 0; i < strlen(fileInfo2.name); i++) {
            if (fileInfo2.name[i] == '.') {
                mark = 1;
                break;
            }
        }
        //不打印文件夹名
        if (mark == 1 && strcmp(fileInfo2.name, ".") != 0 && strcmp(fileInfo2.name, "..") != 0) {
            printf("文件名：%s\n", fileInfo2.name);
            num = num + 1;
            //处理文件的相关内容
            if (tag == 1) {
                countChar(nowPath_re, fileInfo2.name);
            }
            else if (tag == 2) {
                countWord(nowPath_re, fileInfo2.name);
            }
            else if (tag == 3) {
                countLine(nowPath_re, fileInfo2.name);
            }
            else if (tag == 4) {
                countElse(nowPath_re, fileInfo2.name);
            }
            else;
            mark = 0;
        }
        //_findnext是以_findfirst为开始接着查找以下符合H2（.c）的文件并打印
        while (_findnext(Handle2, &fileInfo2) == 0) {
            //查找文件后缀名.
            for (i = 0; i < strlen(fileInfo2.name); i++) {
                if (fileInfo2.name[i] == '.') {
                    mark = 1;
                    break;
                }
            }
            //不打印文件夹名
            if (mark == 1 && strcmp(fileInfo2.name, ".") != 0 && strcmp(fileInfo2.name, "..") != 0) {
                printf("文件名：%s\n", fileInfo2.name);
                num = num + 1;
                //处理文件的相关内容
                if (tag == 1) {
                    countChar(nowPath_re, fileInfo2.name);
                }
                else if (tag == 2) {
                    countWord(nowPath_re, fileInfo2.name);
                }
                else if (tag == 3) {
                    countLine(nowPath_re, fileInfo2.name);
                }
                else if (tag == 4) {
                    countElse(nowPath_re, fileInfo2.name);
                }
                else;
            }
            mark = 0;
        }
        _findclose(Handle2);
    }

    if ((Handle1 = _findfirst(nowPath_folder, &fileInfo1)) == -1L)
        printf("该目录中没有文件。\n");
    else {
        do {
            if (fileInfo1.attrib & _A_SUBDIR) {
                //判断是否为"."当前目录，".."上一层目录，查找子目录的文件
                if ((strcmp(fileInfo1.name, ".") != 0) && (strcmp(fileInfo1.name, "..") != 0))
                {
                    printf("\n%s文件夹\n", fileInfo1.name);
                    //拼接子目录的路径，进行递归查找
                    strcat_s(nowPath_re, fileInfo1.name);
                    strcat_s(nowPath_re, "\\");
                    num += searchFile(nowPath_re, mode, tag);
                }
            }
        } while (_findnext(Handle1, &fileInfo1) == 0);  //循环该目录中所有文件
        _findclose(Handle1);
    }    
    return num;
}

//拆分输入的路径
int splitPath(char path[N],char mode[N]) {
    int i, j, k, len;
    //1表示到符合输入要求的路径
    int mark = 0;
    len = strlen(path);

    for (i = len; i >= 0; i--) {
        if (path[i] == '\\') {
            for (j = i; j < len; j++) {
                //是文件/通配符的标志
                if (path[j] == '.' || path[j] == '*') {
                    for (k = 0; i < len; i++, k++) {
                        mode[k] = path[i + 1];
                        path[i + 1] = '\0';
                    }
                    mark = 1;
                }
                if (mark == 1)  break;
            }
            if (mark == 1)  break;
        }
    }
    if (mark == 1)  return 1;
    else  printf("输入文件路径有误，请重新输入!\n例：E:\\test\\file.c\n");
    return -1;
}

int main(int argc, char* argv[]) {
    //char path[N] = { "E:\\vs project\\wcTest\\" };
    //char mode[N] = { "*.*" };
    //char file[N] = { "test.c" };
    char path[N] = { "E:\\test" };
    char mode[N] = { 0 };
    //1是-c，2是-w，3是-l，4是-a
    int tag = 0;

    //统计
    if (strcmp(argv[1], "-c") == 0) {
        strcpy_s(path, argv[2]);
        if (splitPath(path, mode) == 1)  countChar(path, mode);
    }
    else if (strcmp(argv[1], "-w") == 0) {
        strcpy_s(path, argv[2]);
        if (splitPath(path, mode) == 1)  countWord(path, mode);
    }
    else if (strcmp(argv[1], "-l") == 0) {
        strcpy_s(path, argv[2]);
        if (splitPath(path, mode) == 1)  countLine(path, mode);
    }
    else if (strcmp(argv[1], "-a") == 0) {
        strcpy_s(path, argv[2]);
        if (splitPath(path, mode) == 1)  countElse(path, mode);
    }
    //拓展功能
    else if (strcmp(argv[1], "-s") == 0 && strcmp(argv[2], "-c") == 0) {
        tag = 1;
        strcpy_s(path, argv[3]);
        if (splitPath(path, mode) == 1)  searchFile(path, mode, tag);
    }
    else if (strcmp(argv[1], "-s") == 0 && strcmp(argv[2], "-w") == 0) {
        tag = 2;
        strcpy_s(path, argv[3]);
        if (splitPath(path, mode) == 1)  searchFile(path, mode, tag);
    }
    else if (strcmp(argv[1], "-s") == 0 && strcmp(argv[2], "-l") == 0) {
        tag = 3;
        strcpy_s(path, argv[3]);
        if (splitPath(path, mode) == 1)  searchFile(path, mode, tag);
    }
    else if (strcmp(argv[1], "-s") == 0 && strcmp(argv[2], "-a") == 0) {
        tag = 4;
        strcpy_s(path, argv[3]);
        if (splitPath(path, mode) == 1)  searchFile(path, mode, tag);
    }
    //批处理同类型文件
    else if (strcmp(argv[1], "-s") == 0) {
        strcpy_s(path, argv[2]);
        if (splitPath(path, mode) == 1)  searchFile(path, mode, tag);
    }
    else printf("指令有误，请重新输入！\n");

    system("pause");

    return 0;
}