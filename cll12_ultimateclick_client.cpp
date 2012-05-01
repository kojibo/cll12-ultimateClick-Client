#include "cll12_ultimateclick_client.h"
#include "ui_cll12_ultimateclick_client.h"

cll12_ultimateClick_client::cll12_ultimateClick_client(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::cll12_ultimateClick_client)
{
    ui->setupUi(this);
}

cll12_ultimateClick_client::~cll12_ultimateClick_client()
{
    delete ui;
}
