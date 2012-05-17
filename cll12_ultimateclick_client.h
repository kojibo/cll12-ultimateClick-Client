#ifndef CLL12_ULTIMATECLICK_CLIENT_H
#define CLL12_ULTIMATECLICK_CLIENT_H

#include <QMainWindow>
#include <QtGui>
#include "threadcercle.h"

namespace Ui {
class cll12_ultimateClick_client;
}

class cll12_ultimateClick_client : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit cll12_ultimateClick_client(QWidget *parent = 0);
    ~cll12_ultimateClick_client();
signals:
    void siReussit();
private slots:
    void on_btnOuvrir_clicked();
    void slNouvCercle(int posX, int posY, int rayon);
    void mousePressEvent(QMouseEvent * e);
    void paintEvent(QPaintEvent *event);
    void slConnecte(QString);
    void slPoint();
    void m_timer_tick();
private:
    Ui::cll12_ultimateClick_client *ui;
    threadCercle * m_threadCercle;
    QTimer *m_timer;
    int PosX, PosY, Rayon, Temps;
    bool Commence;
};

#endif // CLL12_ULTIMATECLICK_CLIENT_H
