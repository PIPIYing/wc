#include <stdio.h>
#include <string.h>
#include <io.h>
#define N 100

//统计字符数
int countChar(char file[N])
{
    FILE* fp = NULL;
    errno_t err;
    int c;
    //计数器
    int n = 0;  
    //int c[N];
    //int i = 0;

    err = fopen_s(&fp, file, "r");
    if (fp == NULL)
    {
        printf("该文件不存在。\n");
        return -1;
    }
    else {
        //统计字符数（包括字母、数字、英文符号、空格、换行、中文字符）
        //for (i = 0; i < N; i++) {
        //    c[i] = fgetc(fp);
        //    if (feof(fp))  break;
        //    else {
        //        if (c[i] > 127) {
        //            //每个中文字和中文符号各占3个字符位
        //            c[i + 1] = fgetc(fp);
        //            c[i + 2] = fgetc(fp);
        //            i += 3;
        //            n++;
        //        }
        //        else if (c[i] < 0)  
        //            break;
        //        else  n++;
        //    }
        //}

       //统计字符数（包括字母、数字、英文符号、空格、换行，不包括中文字符）
        do
        {
            c = fgetc(fp);
            if (feof(fp))  break;
            if (c > 127) {
                //每个中文字和中文符号各占3个字符位，需跳过三位再计算
                c = fgetc(fp);
                c = fgetc(fp);
            }
            else  n++;
        } while (1);

    }

    fclose(fp);
    return n;
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

    return n;
}

//统计行数
int countLine(char file[N]) {
    FILE* fp = NULL;
    errno_t err;
    char b[N];
    //计数器
    int n = 0;  

    err = fopen_s(&fp, "file.txt", "r");
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

    return n;
}

//递归查找符合条件的文件
int searchFile() {
    //文件句柄
    long Handle;
    //文件存储信息结构体
    struct _finddata_t fileInfo;

    if ((Handle = _findfirst("E:\\vs project\\wc\\wc\\*.c", &fileInfo)) == -1L)
        printf("没有找到这种类型的文件。\n");
    else {
        printf("文件名：%s\n", fileInfo.name);
        while (_findnext(Handle, &fileInfo) == 0)
            printf("文件名：%s\n", fileInfo.name);
        _findclose(Handle);
    }
    return 0;
};

int main(int argc, char* argv[]) {
    int count1, count2, count3;

    //-1返回文件不存在的结果
    /*if (strcmp(argv[1], "-c") == 0)
    {
        count1 = countChar(argv[2]);
        if (count1 != -1)  printf("该文件中有%d个字符。\n", count1);
    }
    else if (strcmp(argv[1], "-w") == 0)
    {
        count2 = countWord(argv[2]);
        if (count2 != -1)  printf("该文件中有%d个单词。\n", count2);
    }
    else if (strcmp(argv[1], "-l") == 0)
    {
        count3 = countLine(argv[2]);
        if (count3 != -1)  printf("该文件中有%d行。\n", count3);
    }*/

    searchFile();

    return 0;
}

