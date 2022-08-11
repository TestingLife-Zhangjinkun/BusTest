#include "unicastform.h"
#include "ui_unicastform.h"

UnicastForm::UnicastForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UnicastForm)
{
    ui->setupUi(this);
}

UnicastForm::~UnicastForm()
{
    delete ui;
}
