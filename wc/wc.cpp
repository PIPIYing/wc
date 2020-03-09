#include <stdio.h>
#include <string.h>
#include <io.h>
#define N 100

//统计字符数
int countChar(char file[N])
{
    FILE* fp = NULL;
    errno_t err;
    //英文字符计数器和中文字符计数器
    int n = 0, nC = 0;
    int c[N];
    int i = 0;

    err = fopen_s(&fp, file, "r");
    if (fp == NULL)
    {
        printf("该文件不存在。\n");
        return -1;
    }
    else {
        //统计字符数（包括字母、数字、英文符号、空格、换行、中文字符）
        for (i = 0; i < N; i++) {
            c[i] = fgetc(fp);
            if (feof(fp))  break;
            else {
                if (c[i] > 127) {
                    //每个中文字和中文符号各占3个字符位
                    c[i + 1] = fgetc(fp);
                    c[i + 2] = fgetc(fp);
                    i += 3;
                    nC++;
                }
                else if (c[i] < 0)  
                    break;
                else  n++;
            }
        }
        printf("字符数：%d\t中文字：%d\n", n,nC);
    }

    fclose(fp);
    return 1;
}

//统计单词数
int countWord(char file[N]) {
    FILE* fp = NULL;
    errno_t err;
    int c;
    //计数器
    int n = 0;  

    err = fopen_s(&fp, file, "r");
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

    return 1;
}

//统计行数
int countLine(char file[N]) {
    FILE* fp = NULL;
    errno_t err;
    char b[N];
    //计数器
    int n = 0;  

    err = fopen_s(&fp, file, "r");
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

    return 1;
}

//递归查找符合条件的文件
int searchFile(char path[N],char mode[N]) {
    //文件句柄
    long Handle;
    //文件存储信息结构体
    struct _finddata_t fileInfo;
    //现在的查找路径
    char nowPath[N] = { 0 };
    strcpy_s(nowPath, path);
    strcat_s(nowPath, mode);

    if ((Handle = _findfirst(nowPath, &fileInfo)) == -1L)
        printf("没有找到这种类型的文件。\n");
    else {
        printf("文件名：%s\n", fileInfo.name);
        while (_findnext(Handle, &fileInfo) == 0)
            printf("文件名：%s\n", fileInfo.name);
        _findclose(Handle);
    }
    return 0;
};

////递归查找符合条件的文件
//int searchFile(char path[N],char mode[N]) {
//    //文件句柄
//    long Handle;
//    //文件存储信息结构体
//    struct _finddata_t fileInfo;
//    //现在的查找路径
//    char nowPath[N] = { 0 };
//    strcpy_s(nowPath, path);
//    strcat_s(nowPath, mode);
//
//    Handle = _findfirst(nowPath, &fileInfo);
//   
//    if ((Handle) == -1L)
//        printf("没有找到这种类型的文件。\n");
//    else {
//        do {
//            //判断是否为"."当前目录，".."上一层目录，查找子目录的文件
//            if ((strcmp(fileInfo.name, ".") != 0) && (strcmp(fileInfo.name, "..") != 0))
//            {
//                strcat_s(nowPath, "\\");
//                strcat_s(nowPath, fileInfo.name);
//                searchFile(nowPath, mode);
//            }
//            else  printf("文件名：%s\n", fileInfo.name);
//        } while (_findnext(Handle, &fileInfo) == 0);
//
//        _findclose(Handle);
//    }
//    return 1;
//};

//统计代码行、空行和注释行（可简化该函数）
int countElse(char file[N]) {
    FILE* fp = NULL;
    errno_t err;
    char b[N];
    //记录代码行数，记录空行数，记录注释行，记录数组长度，记录字符长度，记录两种注释行数（//和/* */）
    int codeLine = 0, blankLine = 0, commentLine = 0, length = 0, count_char = 0, countC1 = 0, countC2 = 0;
    int i,j;
    //tag是查找/* */注释符号的前半部分的标记，查找成功记为1，查找失败记为0
    int tag=0;

    err = fopen_s(&fp, file, "r");
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
                if (b[i] == '/' && b[i + 1]  == '*'&& tag == 0){
                    countC2++;
                    tag = 1;
                    /* 第二种注释情况，读入的一行为注释行，同行查找结束符号 */
                    for (j = i + 2; j < length-2; j++) {
                        if (b[j] == '*' && b[j+1] == '/') {
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

    printf("代码行：%d\t", codeLine);
    printf("空白行：%d\t", blankLine);
    printf("注释行：%d\n", commentLine);

    return 1;
}

int main(int argc, char* argv[]) {
    char path[N] = { "E:\\vs project\\wc\\wc" };
    char mode[N] = { "\\*.txt" };
    //char file[N] = { "file.txt" };

    /*
    if (strcmp(argv[1], "-c") == 0)
        countChar(argv[2]);
    else if (strcmp(argv[1], "-w") == 0)
        countWord(argv[2]);
    else if (strcmp(argv[1], "-l") == 0)
        countLine(argv[2]);
    else if (strcmp(argv[1], "-a") == 0)
        countElse(argv[2]);
    */

    //countElse(file);
    searchFile(path,mode);

    return 0;
}

