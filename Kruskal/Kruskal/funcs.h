#ifndef _FUNCS_H_
#define _FUNCS_H_

#include <iostream>
#include <string>

//边的结构体定义
struct vex
{
	int i;
	int j;
	int weigh;
};

//添加站点
void addPlace();

//添加边
void addLink();

//寻找点所在的集合，返回这一点对应的关系集合的一维数组下标
int findUnion(int point);

//KrusKal算法本体
void Kruskal();

#endif