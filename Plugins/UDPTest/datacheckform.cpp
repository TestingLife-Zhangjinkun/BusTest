#include "datacheckform.h"
#include "ui_datacheckform.h"
#include <QDebug>

DataCheckForm::DataCheckForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataCheckForm)
{
    ui->setupUi(this);
}

DataCheckForm::~DataCheckForm()
{
    delete ui;
}

/***
 * 浮点数转换思路：由于强制转换会造成数据丢失，所以直接操作内存。将float/double的指针转换成其它类型的指针，再解引用。
 * double：8字节；float：4字节
 * qulonglong：8字节；qint32、quint32：4字节
 ***/

// Floating point to hexadecimal conversion
void DataCheckForm::on_pushButton_Convert1_clicked()
{
    QString strFloat = ui->lineEdit_Float1->text();
    float f = strFloat.toFloat();
    QByteArray ba;
    const quint8* ch = (quint8*)(&f);
    ba.resize(4);
    for(auto i=0; i<4; ++i)
        ba[i] = *((quint8*)(ch+i));
    QString str = tcInstance.ByteArrayToHexString(ba);
    ui->lineEdit_Hex1->setText(str);
}

void DataCheckForm::on_pushButton_Convert2_clicked()
{
    QString strHex = ui->lineEdit_Hex2->text().trimmed();
    QByteArray ba = tcInstance.HexStringToByteArray(strHex);
    float f;
    quint8* ch = (quint8*)(&f);
    for(auto i=0; i<4; ++i)
        *(ch+i) = ba[i];

    QString strFloat = QString("%1").arg(f);
    ui->lineEdit_Float2->setText(strFloat);

}











