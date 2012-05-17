#include "threadcercle.h"
#include <QtGui>
#include <QTcpSocket>
#include <QIODevice>
#include <QThread>

threadCercle::threadCercle()
{
}

void threadCercle::run()
{
    QByteArray baReception;
    sockClient.connectToHost(m_IPServeur, 55415);
    int posX, posY, rayon;
    m_bEtat=true;
    if (sockClient.waitForConnected(5000))
    {
        emit(siConnecte("Cliquez!"));
        while (m_bEtat)
        {
            sockClient.waitForReadyRead(100);
            if(sockClient.bytesAvailable() > 0)
            {
                baReception.append(sockClient.read(sockClient.bytesAvailable()));
            }
            else
            {
                m_bEtat = false;
            }
            if(baReception[0] ==1)
            {
                posX = (baReception[1] << 8) + uchar(baReception[2]);
                posY = (baReception[3] << 8) + uchar(baReception[4]);
                rayon= uchar(baReception[5]);
                emit (siNouvCercle(posX,posY,rayon));
            }
            else
            {
                if(baReception[0]==2)
                {
                    emit(siConnecte("Vous avez gagné!"));
                }
                else
                {
                    if(baReception[0]==3)
                    {
                        emit(siConnecte("Vous avez perdu..."));
                    }
                }
            }
            baReception.clear();
            sockClient.write("#");
        }
        emit(siConnecte("Fin."));
    }
    else
    {
        emit(siConnecte("Une erreur s'est produite."));
    }

    sockClient.disconnectFromHost();
    sockClient.close();
}

void threadCercle::slReussit()
{
    QByteArray baEnvoyer;
    baEnvoyer.append((char)1);
    sockClient.write(baEnvoyer);
    emit(siPoint());
}
