#ifndef PAINTCHANGE_H
#define PAINTCHANGE_H

#include <QWidget>
#include "pathadvisor.h"
#include "QCloseEvent"

namespace Ui {
class paintchange;
}

class paintchange : public QWidget
{
    Q_OBJECT

public:
    explicit paintchange(QWidget *parent = 0);
    ~paintchange();

    void findedge();

    void resetweight();

    PathAdvisor m_pathadvisor;

    int x,y;

protected:
    void closeEvent(QCloseEvent *e) override;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::paintchange *ui;
};

#endif // PAINTCHANGE_H
