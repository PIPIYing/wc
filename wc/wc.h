#pragma once
#ifndef _WC_H
#define _WC_H
#define N 100

//ͳ���ַ���
int countChar(char path[N], char file[N]);
//ͳ�Ƶ�����
int countWord(char path[N], char file[N]);
//ͳ������
int countLine(char path[N], char file[N]);
//ͳ�ƴ����С����к�ע���У��ɼ򻯸ú�����
int countElse(char path[N], char file[N]);
//�ݹ���ҷ����������ļ�
int searchFile(char path[N], char mode[N], int tag);
//�����cmd�����������·��
int splitPath(char path[N], char mode[N]);

#endif