#pragma once
#ifndef _WC_H
#define _WC_H
#define N 100

//统计字符数
int countChar(char path[N], char file[N]);
//统计单词数
int countWord(char path[N], char file[N]);
//统计行数
int countLine(char path[N], char file[N]);
//统计代码行、空行和注释行（可简化该函数）
int countElse(char path[N], char file[N]);
//递归查找符合条件的文件
int searchFile(char path[N], char mode[N], int tag);
//拆分在cmd下输入的完整路径
int splitPath(char path[N], char mode[N]);

#endif