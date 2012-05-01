#ifndef CLL12_ULTIMATECLICK_CLIENT_H
#define CLL12_ULTIMATECLICK_CLIENT_H

#include <QMainWindow>

namespace Ui {
class cll12_ultimateClick_client;
}

class cll12_ultimateClick_client : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit cll12_ultimateClick_client(QWidget *parent = 0);
    ~cll12_ultimateClick_client();
    
private:
    Ui::cll12_ultimateClick_client *ui;
};

#endif // CLL12_ULTIMATECLICK_CLIENT_H
