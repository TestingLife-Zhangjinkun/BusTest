#include "udpform.h"
#include "ui_udpform.h"

UDPForm::UDPForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UDPForm)
{
    ui->setupUi(this);
}

UDPForm::~UDPForm()
{
    delete ui;
}
