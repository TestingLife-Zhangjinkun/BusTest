#include "datacheckform.h"
#include "ui_datacheckform.h"
#include <QDebug>

DataCheckForm::DataCheckForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataCheckForm)
{
    ui->setupUi(this);

    ui->lineEdit_Float1_MemVal->setFocusPolicy(Qt::NoFocus);
    ui->checkBox_LittleEndian->setChecked(true);
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
    const char* ch = (char*)(&f);
    QByteArray ba = QByteArray(ch, 4);
    // Big end mode, reversed
    if(!ui->checkBox_LittleEndian->isChecked())
        std::reverse(ba.begin(), ba.end());
    QString str = ba.toHex(' ').toUpper();
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

    qInfo().noquote() << f;
    QString strFloat = QString("%1").arg(f);
    ui->lineEdit_Float2->setText(strFloat);

}











// 显示在内存值表示浮点数的实际值
void DataCheckForm::on_lineEdit_Float1_editingFinished()
{
    QString strFloat = ui->lineEdit_Float1->text();
    float f = strFloat.toFloat();
    qInfo().noquote() << QString::number(f, 'f', 6);
    ui->lineEdit_Float1_MemVal->setText(QString::number(f, 'f', 6));
}

