#include "pathadvisor.h"
#include "paintwidget.h"
#include "QFile"
#include "QDebug"
#include "QStack"
#include "QMessageBox"
#include "extre.h"

int m=0,flag1=2;
QString a,b,c,x,y;
QStringList list;
PathAdvisor::PathAdvisor()
{

}

void PathAdvisor::ConstructPath()
{
    if(flag1==1)
    {
         m_nodes.append(Node(x.toFloat(),y.toFloat(),a));
         res_nodes.append(Node(x.toFloat(),y.toFloat(),a));
    }
    else
    {
        m_nodes[a.toInt()].neighbors.append(QPair<int,int>(b.toInt(),c.toInt()));
    }
}

void PathAdvisor::ReadNode()
{

    int n=0;
    QString line;
    QFile file;
    file.setFileName(f);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        while (!file.atEnd()) {
            if(n==0)
            {
                line = file.readLine();
                m=line.toInt();
                n++;
                continue;
            }
            else if(n<=m)
            {
                flag1=1;
                line = file.readLine();
                list=line.split(' ');
                x=list.at(0);
                y=list.at(1);
                a=list.at(2);
                ConstructPath();
                n++;
            }
            else
            {
                flag1=0;
                line=file.readLine();
                list = line.split(' ');
                a=list.at(0);
                b=list.at(1);
                c=list.at(2);
                ConstructPath();
            }
        }
    }
}

bool PathAdvisor::ToPosort(int *topo)
{
    int *indegree=(int *)malloc(m*sizeof(int));
    memset(indegree,0,sizeof(int )*m);
    QStack<int> st;
    for(int i=0;i<m;i++)
    {
        auto arcnode=m_nodes[i];
        for(int j=0;j<arcnode.neighbors.size();j++)
        {
            indegree[arcnode.neighbors[j].first]++;
        }
    }
    for(int i=0;i<m;i++)
    {
        if(indegree[i]==0)
        {
            st.push(i);
        }
    }
    int size =0;
    int topo_i=0;
    while(!st.empty())
    {
        int i=st.top();
        st.pop();
        topo[topo_i++]=i;
        size++;
        auto arc=m_nodes[i];
        for(int j=0;j<arc.neighbors.size();j++)
        {
            --indegree[arc.neighbors[j].first];
            if(indegree[arc.neighbors[j].first]==0)
            {
                st.push(arc.neighbors[j].first);
            }
        }
    }
    if(size==m) return true;
    else return false;
}

void PathAdvisor::CriticalPath()
{
    int* topo =(int *)malloc(m*sizeof(int));
    if(!ToPosort(topo))
    {
        QMessageBox::warning(NULL,"警告","非AOE网！",QMessageBox::Yes);
        return;
    }
    int *etv=(int *)malloc(m*sizeof(int));
    int *ltv=(int *)malloc(m*sizeof(int));
    memset(etv,0,sizeof(int)*m);
    for(int i=0;i<m;i++)
    {
        auto arc=m_nodes[i];
        for(int j=0;j<arc.neighbors.size();++j)
        {
            if(etv[arc.neighbors[j].first]<etv[i]+arc.neighbors[j].second)
            {
                etv[arc.neighbors[j].first]=etv[i]+arc.neighbors[j].second;

            }
        }
    }
    for(int i=0;i<m;++i)
    {
        ltv[i]=etv[m-1];
    }
    for(int i=m-2;i>0;i--)
    {
        auto arcnode=m_nodes[i];
        for(int j=0;j<arcnode.neighbors.size();++j)
        {
            if(ltv[i]>ltv[arcnode.neighbors[j].first]-arcnode.neighbors[j].second)
            {
                ltv[i]=ltv[arcnode.neighbors[j].first]-arcnode.neighbors[j].second;
            }
        }
    }
    for(int i=0;i<m;i++)
    {
        auto arcn=m_nodes[i];
        for(int j=0;j<arcn.neighbors.size();++j)
        {
            if(i==m-1) arcn.neighbors.size()-1;
            if(ltv[arcn.neighbors[j].first]==etv[i]+arcn.neighbors[j].second)
            {
                res_nodes[i].neighbors.append(QPair<int,int>(arcn.neighbors[j].first,arcn.neighbors[j].second));
            }
        }
    }
}
