#ifndef THREADCERCLE_H
#define THREADCERCLE_H
#include <QTcpSocket>
#include <QThread>

class threadCercle : public QThread
{
    Q_OBJECT
public:
    threadCercle();
    bool m_bEtat;
    QString m_IPServeur;
protected:
    void run();
    QTcpSocket sockClient;
signals:
    void siNouvCercle(int, int, int);
    void siConnecte(QString);
    void siPoint();
public slots:
    void slReussit();
    
};

#endif // THREADCERCLE_H
