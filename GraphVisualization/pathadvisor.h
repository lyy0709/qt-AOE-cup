#ifndef PATHADVISOR_H
#define PATHADVISOR_H

#include <QVector>
#include <QPointF>
#include <QDebug>


struct Node{

    QString label;
    float x, y;   // 绘制用的。

    QVector<QPair<int, int>> neighbors;

    Node(float x=0.0f, float y=0.0f, QString l = "n"): label(l), x(x), y(y){}

    QPointF toQPoint(){ return QPointF(x, y);}
};

// 只需要改这里
class PathAdvisor
{
public:
    PathAdvisor();

    QVector<Node> m_nodes;  // Feed into this data structure.

    QVector<Node> res_nodes;

    void ConstructPath();//构建邻接矩阵

    void ReadNode();//读入图的数据

    bool ToPosort(int *topo);//进行拓扑排序
    
    void CriticalPath();//求解关键路径

};


#endif // PATHADVISOR_H
