#include "cll12_ultimateclick_client.h"
#include "ui_cll12_ultimateclick_client.h"
#include <QtGui>
#include <QMainWindow>
#include <QMouseEvent>
#include <QtCore/qmath.h>

cll12_ultimateClick_client::cll12_ultimateClick_client(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::cll12_ultimateClick_client)
{
    ui->setupUi(this);
    m_threadCercle = new threadCercle();
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(m_timer_tick()));
    m_timer->setInterval(1000);
    connect(m_threadCercle, SIGNAL(siNouvCercle(int, int, int)), this, SLOT(slNouvCercle(int, int, int)));
    connect(this, SIGNAL(siReussit()),m_threadCercle,SLOT(slReussit()));
    connect(m_threadCercle, SIGNAL(siConnecte(QString)), this, SLOT(slConnecte(QString)));
    connect(m_threadCercle, SIGNAL(siPoint()),this,SLOT(slPoint()));
    PosX = 0;
    PosY = 0;
    Rayon = 0;
    Commence=false;
    ui->lblMessage->setText("Utilisez le bouton droit de la souris.");
    Temps = 0;
    bPremier = true;
}

cll12_ultimateClick_client::~cll12_ultimateClick_client()
{
    delete ui;
}

void cll12_ultimateClick_client::paintEvent(QPaintEvent *event)
{
    QPainter PanJeu(this);
    PanJeu.setBrush(Qt::white);
    PanJeu.drawRect(55,75,602,302);
    PanJeu.setBrush(Qt::red);
    PanJeu.setPen(Qt::darkRed);
    if(Commence==true&&Rayon>0)
    {
        PanJeu.drawEllipse(QPoint(55+PosX,75+PosY),Rayon, Rayon);
        Commence=false;
        if(bPremier == true)
        {
            m_timer->start();
            bPremier = false;
        }
    }
}

void cll12_ultimateClick_client::mousePressEvent(QMouseEvent * e)
{
    if(e->button() == Qt::RightButton)
    {
        int X = e->x()-55;
        int Y = e->y()-75;
        if((X >= 0 && Y >= 0) &&(X<=600&&Y<=300))
        {
            if(qPow(PosX - X, 2) + qPow(PosY - Y, 2) <= qPow(Rayon, 2))
            {
                emit(siReussit());
            }
            ui->label_2->setText(QString("%1").arg(X));
            ui->label_3->setText(QString("%1").arg(Y));
        }
    }
}

void cll12_ultimateClick_client::slNouvCercle(int X, int Y, int r)
{
    PosX = X;
    PosY = Y;
    Rayon = r;
    Commence = true;
    ui->lblMessage->setVisible(false);
    repaint();
    ui->label_4->setText(QString("%1").arg(X));
    if(bPremier == true)
    {
        m_timer->start();
        bPremier = false;
    }
}

void cll12_ultimateClick_client::on_btnOuvrir_clicked()
{
    ui->lblMessage->setText("Cliquez!");
    m_threadCercle->m_bEtat = true;
    m_threadCercle->m_IPServeur = ui->txtIPServeur->text();
    m_threadCercle->start();
}
void cll12_ultimateClick_client::slConnecte(QString mess)
{
   ui->lblMessage->setVisible(true);
   if(mess!="Fin.")
       ui->lblMessage->setText(mess);
   if(mess=="Une erreur s'est produite."|| mess=="Fin." || mess=="Vous avez gagné!" || mess=="Vous avez perdu...")
   {
       m_threadCercle->exit();
       m_timer->stop();
       PosX = 0;
       PosY = 0;
       Rayon = 0;
       ui->btnOuvrir->setEnabled(true);
       ui->txtIPServeur->setEnabled(true);
       repaint();
       Temps = 0;
       ui->lblTemps->setText("00:00:00:00");
       bPremier = true;
   }
   else
   {
       ui->btnOuvrir->setEnabled(false);
       ui->txtIPServeur->setEnabled(false);
   }
}
void cll12_ultimateClick_client::slPoint()
{
    int nbPoints;
    nbPoints = ui->lblPoints->text().toInt();
    ui->lblPoints->setText(QString("%1").arg(nbPoints + (4-Rayon/8)));
}

void cll12_ultimateClick_client::m_timer_tick()
{
    Temps = Temps +1;
    int jour, heure, minute, seconde;
    jour = Temps / 86400;
    heure = (Temps - jour*86400) / 3600;
    minute = (Temps - (jour*86400 + heure*3600))/ 60;
    seconde = Temps - (jour*86400 + heure*3600 + minute * 60);

    ui->lblTemps->setText(QString("%00:%01:%02:%03").arg(jour,2,10,QChar('0')).arg(heure,2,10,QChar('0')).arg(minute,2,10,QChar('0')).arg(seconde,2,10,QChar('0')));
}
