#ifndef _FUNCS_H_
#define _FUNCS_H_

#include <iostream>
#include <string>

//�ߵĽṹ�嶨��
struct vex
{
	int i;
	int j;
	int weigh;
};

//���վ��
void addPlace();

//��ӱ�
void addLink();

//Ѱ�ҵ����ڵļ��ϣ�������һ���Ӧ�Ĺ�ϵ���ϵ�һά�����±�
int findUnion(int point);

//KrusKal�㷨����
void Kruskal();

#endif