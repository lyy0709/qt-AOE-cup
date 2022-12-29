#include "paintchange.h"
#include "ui_paintchange.h"
#include "QDebug"
#include "QMessageBox"
#include "paintwidget.h"
#include "extre.h"

bool flagedge=false;
bool flagfind=false;
paintchange::paintchange(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::paintchange)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/new/prefix1/AppIcon.png"));
    this->m_pathadvisor.ReadNode();
}

paintchange::~paintchange()
{
    delete ui;
}

void paintchange::findedge()
{
    QString a=ui->textEdit->document()->toPlainText();
    QString b=ui->textEdit_2->document()->toPlainText();
    int w;
//    char *a1,*b1;
//    QByteArray a2=a.toLatin1();
//    QByteArray b2=b.toLatin1();
//    a1=a2.data();b1=b2.data();
//    int w;
//    x=a1[0]-'A';
//    y=b1[0]-'A';
    x=a.at(0).toLatin1()-'A';
    y=b.at(0).toLatin1()-'A';
    auto curNode=m_pathadvisor.m_nodes[x];
    for(int i=0;i<curNode.neighbors.size();++i)
    {
        int neighboringIndex = curNode.neighbors[i].first;
        if(y==neighboringIndex)
        {
            w=curNode.neighbors[i].second;
            ui->textEdit_3->setText(QString::number(w,10));
            flagedge=true;
            flagfind=true;
        }
    }
    if(!flagedge)
    {
        QMessageBox::warning(NULL,"警告","两点之间没有边",QMessageBox::Yes);
    }
}

void paintchange::resetweight()
{
    int w;
    QString a=ui->textEdit_3->document()->toPlainText();
    w=a.toInt();
    QFile file;
    file.setFileName(f);
    if(file.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        QTextStream stream(&file);
        stream<<m_pathadvisor.m_nodes.size()<<"\n";
        for(int i=0;i<m_pathadvisor.m_nodes.size();++i)
        {
            stream<<m_pathadvisor.m_nodes[i].x<<" "<<m_pathadvisor.m_nodes[i].y<<" "<<m_pathadvisor.m_nodes[i].label;
        }
        for(int i=0;i<m_pathadvisor.m_nodes.size();++i)
        {
            auto curNode=m_pathadvisor.m_nodes[i];
            for(int j=0;j<curNode.neighbors.size();++j)
            {
                auto neighboringInde=curNode.neighbors[j];
                if(x==i&&curNode.neighbors[j].first==y)
                {
                    stream<<i<<" "<<neighboringInde.first<<" "<<w<<"\n";
                    continue;
                }
                if(i==m_pathadvisor.m_nodes.size()-1&&j==curNode.neighbors.size()-1)
                {
                    stream<<i<<" "<<neighboringInde.first<<" "<<neighboringInde.second;
                }
                else
                {
                    stream<<i<<" "<<neighboringInde.first<<" "<<neighboringInde.second<<"\n";
                }
            }
        }
    }
}

void paintchange::closeEvent(QCloseEvent *e)
{
    this->close();
    flagw=true;
//    if(this->close())
//    {
//        PaintWidget *painwidget=new PaintWidget;
//        painwidget->show();
//        painwidget->readnum();
//    }
}

void paintchange::on_pushButton_clicked()
{
    findedge();
    flagedge=false;
}

void paintchange::on_pushButton_2_clicked()
{
    if(flagfind)
    {
         resetweight();
         QMessageBox::information(NULL,"提示","权值修改成功！",QMessageBox::Yes);
    }
    else
    {
        QMessageBox::warning(NULL,"警告","需要查询之后才能修改",QMessageBox::Yes);
    }

}
