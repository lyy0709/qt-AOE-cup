#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H
#include "QCloseEvent"
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include "QFile"
#include "QList"
#include "QFileDialog"
#include "paintchange.h"
#include "pathadvisor.h"

namespace Ui {
class PaintWidget;
}

class PaintWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PaintWidget(QWidget *parent = 0);
    ~PaintWidget();

    void readnum();

    paintchange *m_paintcahnge = nullptr;

    PathAdvisor m_pathAdvisor;

protected:
    void paintEvent(QPaintEvent *event) override;//重写QPainterevent实现绘画
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_pressed();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::PaintWidget *ui;

    QPoint m_clickedPos;
    QPoint res_clickedPos;
    Node* m_selectedNode = nullptr;
    Node* res_selectedNode = nullptr;
};

#endif // PAINTWIDGET_H
