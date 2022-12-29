#include "paintwidget.h"
#include "ui_paintwidget.h"
#include "QMessageBox"
#include "QDebug"
#include "QTime"
#include "extre.h"
#define MI_PI 3.14

bool flag=false;
bool open=false;
PaintWidget::PaintWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PaintWidget)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/new/prefix1/AppIcon.png"));
}


void PaintWidget::paintEvent(QPaintEvent* event)
{

    static int __radius__ = 5.0f;
    // Do all painting-related stuffs inside this function body.

    auto painter=new QPainter(this);

    painter->setBrush(Qt::white);
    painter->setRenderHint(QPainter::Antialiasing);
    // Render all nodes seperately.
    painter->setBrush(QBrush(QColor(255,255,255)));
    painter->drawRect(this->rect());

    QPen penEdge(QColor(50.0f, 100.0f, 150.0f));
    penEdge.setWidth(5.0f);

    QPen pen(QColor(178,178,178));  // outlines.
    painter->setFont(QFont("Times New Roman",20,3));
    pen.setWidth(5.0f);
    painter->setPen(pen);
 // color inside (fulling-out).

    QPen penTtf(QColor(0.0f,0.0f,0.0f));
    penTtf.setWidth(5.0f);
    for(int i=0; i< m_pathAdvisor.m_nodes.size(); ++i)
    {
        auto curNode = m_pathAdvisor.m_nodes[i];

        for(int k=0; k<curNode.neighbors.size(); k++)
        {
            int neighboringIndex = curNode.neighbors[k].first;  // QPair<QString, float>, == STL::Tuple<> the same use.
            auto neighboringNode = m_pathAdvisor.m_nodes[neighboringIndex];
            painter->setRenderHint(QPainter::Antialiasing,true);
            qreal arrowSize=20;
            painter->setPen(penEdge);
            QLine line(neighboringNode.x,neighboringNode.y,curNode.x,curNode.y);
            double angle =std::atan2(-line.dy(),line.dx());
            QPointF arrowP1=line.p1()+QPointF(sin(angle+MI_PI/3)*arrowSize,cos(angle+MI_PI/3)*arrowSize);
            QPointF arrowP2=line.p1()+QPointF(sin(angle+2*MI_PI/3)*arrowSize,cos(angle+2*MI_PI/3)*arrowSize);

            QPolygonF arrowHead;
            arrowHead.clear();
            arrowHead<<line.p1()<<arrowP1<<arrowP2;
            painter->drawLine(line);
            painter->setBrush(QBrush(QColor(50.0f, 100.0f, 150.0f)));
            painter->drawPolygon(arrowHead);

            painter->setPen(penTtf);
            QPointF mid_edge_point(0.5f*(curNode.x + neighboringNode.x), 0.5f*(curNode.y + neighboringNode.y));
            painter->drawText(mid_edge_point, QString::number(curNode.neighbors[k].second));
        }
    }

    if(flag)
    {
        QPen penEdge(QColor(255.0f, 0, 0));
        penEdge.setWidth(5.0f);
        for(int i=0;i<m_pathAdvisor.res_nodes.size();++i)
        {
            auto curNode1 = m_pathAdvisor.res_nodes[i];
            for(int j=0;j<curNode1.neighbors.size();j++)
            {
                int neighboringIndex1 = curNode1.neighbors[j].first;
                auto neighboringNode1 = m_pathAdvisor.res_nodes[neighboringIndex1];
                painter->setRenderHint(QPainter::Antialiasing,true);
                qreal arrowSize=20;
                painter->setPen(penEdge);
                QLine line(neighboringNode1.x,neighboringNode1.y,curNode1.x,curNode1.y);
                double angle =std::atan2(-line.dy(),line.dx());
                QPointF arrowP1=line.p1()+QPointF(sin(angle+MI_PI/3)*arrowSize,cos(angle+MI_PI/3)*arrowSize);
                QPointF arrowP2=line.p1()+QPointF(sin(angle+2*MI_PI/3)*arrowSize,cos(angle+2*MI_PI/3)*arrowSize);

                QPolygonF arrowHead;
                arrowHead.clear();
                arrowHead<<line.p1()<<arrowP1<<arrowP2;
                painter->drawLine(line);
                painter->setBrush(QBrush(QColor(50.0f, 100.0f, 150.0f)));
                painter->drawPolygon(arrowHead);

            }
        }
    }
    for(int i=0; i< m_pathAdvisor.m_nodes.size(); ++i)
    {
        auto curNode = m_pathAdvisor.m_nodes[i];

        painter->setPen(pen);
        painter->drawEllipse(QPointF(curNode.x, curNode.y), __radius__, __radius__);
        painter->setBrush(QBrush(QColor(178,178,178)));
        painter->setPen(penTtf);
        painter->drawText(QPointF(curNode.x, curNode.y), curNode.label);
    }

    delete painter;
}


void PaintWidget::mousePressEvent(QMouseEvent* event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        m_clickedPos = event->pos();
        res_clickedPos = event->pos();

        float minDis = INT_MAX;
        for(int i=0; i<m_pathAdvisor.m_nodes.size(); ++i)
        {

            auto distance = (m_clickedPos - m_pathAdvisor.m_nodes[i].toQPoint()).manhattanLength(); // |dx| + |dy|
            if(distance < minDis)
            {
                minDis = distance;
                this->m_selectedNode = &(m_pathAdvisor.m_nodes[i]);
                this->res_selectedNode = &(m_pathAdvisor.res_nodes[i]);
            }
        }
    }
}

void PaintWidget::mouseMoveEvent(QMouseEvent* event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        if(!m_selectedNode)
            return;

        m_clickedPos = event->pos();
        res_clickedPos = event->pos();

        this->m_selectedNode->x = m_clickedPos.x();
        this->m_selectedNode->y = m_clickedPos.y();
        this->res_selectedNode->x = res_clickedPos.x();
        this->res_selectedNode->y = res_clickedPos.y();
        ui->lineEdit->setText(QString::number(m_clickedPos.x(),10));
        ui->lineEdit_2->setText(QString::number(m_clickedPos.y(),10));

        this->update();
    }
}

void PaintWidget::mouseReleaseEvent(QMouseEvent* event)
{
    if(event->buttons() & Qt::LeftButton)
    {
       this->m_selectedNode = nullptr;
    }
}

PaintWidget::~PaintWidget()
{
    delete ui;
}

void PaintWidget::readnum()
{
    m_pathAdvisor.ReadNode();
    flag=false;
    open=true;
    this->update();
}

void PaintWidget::on_pushButton_clicked()
{
    QFile file;
    f = QFileDialog::getOpenFileName(this,QString("选择文件"),QString("/"),QString("MAP(*.map)"));
    file.setFileName(f);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QByteArray t;
        while (!file.atEnd()) {
            t+=file.readLine();
        }
        if(t==NULL)
        {
            QMessageBox::warning(NULL,"警告","文件内无内容",QMessageBox::Yes);
            file.close();
        }
        else
        {
            this->close();
            PaintWidget *p=new PaintWidget;
            p->setWindowTitle("图的关键路径");
            p->show();
            p->readnum();
            p->ui->textEdit->setText(f);
        }
    }
}


void PaintWidget::on_pushButton_2_pressed()
{
    m_pathAdvisor.CriticalPath();
    flag=true;
    this->update();
}

void PaintWidget::on_pushButton_3_clicked()
{
    if(open)
    {
        this->m_paintcahnge=new paintchange;
        m_paintcahnge->resize(400,300);
        m_paintcahnge->setAttribute(Qt::WA_DeleteOnClose);
        m_paintcahnge->setWindowTitle("权值修改");
        m_paintcahnge->show();
    }
    else
    {
        QMessageBox::warning(NULL,"警告","没有加载文件",QMessageBox::Yes);
    }
}

void PaintWidget::on_pushButton_4_clicked()
{
    if(flagw)
    {
        this->close();
        PaintWidget *p=new PaintWidget;
        p->setWindowTitle("图的关键路径");
        p->show();
        p->readnum();
        p->ui->textEdit->setText(f);
    }
    else
    {
        QMessageBox::warning(NULL,"警告","没有修改权值无需刷新",QMessageBox::Yes);
    }
}
