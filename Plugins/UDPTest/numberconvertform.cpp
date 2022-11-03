#include "numberconvertform.h"
#include "ui_numberconvertform.h"

NumberConvertForm::NumberConvertForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NumberConvertForm)
{
    ui->setupUi(this);
}

NumberConvertForm::~NumberConvertForm()
{
    delete ui;
}
