#pragma once
#include "Graph.h"

// 读入顶点、路径文件
void LoadVex();
void LoadPath();

// 读取文件，创建景点图
void CreateGraph();

// 查询指定景点信息，显示到相邻景点的距离
void GetSpotInfo();

// 旅游景点导航功能，显示导航路线
void TravelPath();

// 查询两景点间的最短路径与距离
void FindShortPath();

// 轻轨建设规划
void DesignPath();
