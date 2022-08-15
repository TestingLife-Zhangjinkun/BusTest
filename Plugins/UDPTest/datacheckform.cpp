#include "datacheckform.h"
#include "ui_datacheckform.h"
#include <QDebug>
#include <QMessageBox>

DataCheckForm::DataCheckForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataCheckForm)
{
    ui->setupUi(this);

    ui->lineEdit_Float1_MemVal->setFocusPolicy(Qt::NoFocus);
    // Pause control to emit signals
    ui->checkBox_LittleEndian->blockSignals(true);
    ui->checkBox_LittleEndian->setChecked(true);
    ui->checkBox_LittleEndian->setDisabled(true);
    ui->checkBox_LittleEndian->blockSignals(false);
    ui->checkBox_Separator1->setChecked(true);
    ui->lineEdit_Hex1->setReadOnly(true);
    // Input rules: Only floating point numbers are accepted, and a maximum of 6 digits after the decimal point are entered.
    QRegExpValidator* floatRegExp = new QRegExpValidator(QRegExp("^(-?\\d+)(\\.\\d{0,6})?$"));
    ui->lineEdit_Float1->setValidator(floatRegExp);
    // Input rules: Only hexadecimal characters and space characters are accepted.
    QRegExpValidator* hexRegExp = new QRegExpValidator(QRegExp("([a-fA-F0-9]{2}\\s?){3}[a-fA-F0-9]{2}"));
    ui->lineEdit_Hex2->setValidator(hexRegExp);

    ui->checkBox_LittleEndian2->setChecked(true);
    QStringList list = {"0", "1", "2", "3", "4", "5", "6"};
    ui->comboBox_Float2_ReservedBits->addItems(list);
    ui->comboBox_Float2_ReservedBits->setCurrentIndex(2);
    ui->lineEdit_Float2->setReadOnly(true);
    ui->lineEdit_Float2_MemVal->setFocusPolicy(Qt::NoFocus);

    ui->checkBox_LittleEndian3->setChecked(true);
    ui->checkBox_LittleEndian3->setDisabled(true);
    ui->checkBox_Separator3->setChecked(true);
    ui->lineEdit_Hex3->setReadOnly(true);

    ui->checkBox_LittleEndian4->setChecked(true);
    QStringList list1 = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
                         "10", "11", "12", "13"};
    ui->comboBox_Double2_ReservedBits->addItems(list1);
    ui->comboBox_Double2_ReservedBits->setCurrentIndex(2);
    ui->lineEdit_Double2->setReadOnly(true);
    ui->lineEdit_Double2_MemVal->setFocusPolicy(Qt::NoFocus);

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
    if(ui->lineEdit_Float1->text().trimmed().isEmpty())
    {
        QMessageBox::information(this, "信息提示", "请输入单精度浮点数！");
        return;
    }

    QString strFloat = ui->lineEdit_Float1->text();
    float f = strFloat.toFloat();
    const char* ch = (char*)(&f);
    QByteArray ba = QByteArray(ch, 4);
    // Big end mode, reversed
    if(!ui->checkBox_LittleEndian->isChecked())
        std::reverse(ba.begin(), ba.end());
    QString str = "";
    if(ui->checkBox_Separator1->isChecked())
        str = ba.toHex(' ').toUpper();
    else
        str = ba.toHex().toUpper();
    ui->lineEdit_Hex1->setText(str);
}

void DataCheckForm::on_pushButton_Convert2_clicked()
{
    QString strHex = ui->lineEdit_Hex2->text().trimmed();
    if(strHex.remove(' ').length() < 8)
    {
        QMessageBox::information(this, "信息提示", "请输入8个十六进制字符！");
        return;
    }
    QByteArray ba = QByteArray::fromHex(strHex.toLatin1());
    float f;
    char* ch = (char*)(&f);
    if(!ui->checkBox_LittleEndian2->isChecked())
        std::reverse(ba.begin(), ba.end());
    for(auto i=0; i<4; ++i)
        *(ch+i) = ba[i];

    QString strFloat = QString::number(f, 'f', ui->comboBox_Float2_ReservedBits->currentIndex());
    ui->lineEdit_Float2->setText(strFloat);
    ui->lineEdit_Float2_MemVal->setText(QString::number(f, 'f', 6));
}

// 显示在内存值表示浮点数的实际值
void DataCheckForm::on_lineEdit_Float1_editingFinished()
{
    QString strFloat = ui->lineEdit_Float1->text();
    float f = strFloat.toFloat();
    qInfo().noquote() << QString::number(f, 'f', 6);
    ui->lineEdit_Float1_MemVal->setText(QString::number(f, 'f', 6));
}

// 更改浮点数在内存中的存储模式
void DataCheckForm::on_pushButton_ChangeMemMode1_clicked()
{
    if(ui->checkBox_LittleEndian->isChecked())
    { // little endian mode
        ui->checkBox_LittleEndian->setChecked(false);
        ui->checkBox_LittleEndian->setText("大端模式");
    }
    else
    {
        ui->checkBox_LittleEndian->setChecked(true);
        ui->checkBox_LittleEndian->setText("小端模式");
    }
}

void DataCheckForm::on_checkBox_Separator1_stateChanged(int arg1)
{
    if(arg1 == 2)
        ui->lineEdit_Hex1->setText(tcInstance.StringNoNullToNull(ui->lineEdit_Hex1->text()));
    else
        ui->lineEdit_Hex1->setText(ui->lineEdit_Hex1->text().remove(' '));
}

void DataCheckForm::on_checkBox_LittleEndian2_stateChanged(int arg1)
{
    if(arg1 == 2)
        ui->checkBox_LittleEndian2->setText("小端模式");
    else
        ui->checkBox_LittleEndian2->setText("大端模式");
}


void DataCheckForm::on_lineEdit_Hex2_textChanged(const QString &arg1)
{
    ui->lineEdit_Hex2->setText(tcInstance.StringNoNullToNull(arg1));
}

// 双精度浮点数到十六进制的转换
void DataCheckForm::on_pushButton_Convert3_clicked()
{
    if(ui->lineEdit_Double1->text().trimmed().isEmpty())
    {
        QMessageBox::information(this, "信息提示", "请输入双精度浮点数！");
        return;
    }

    QString strDouble = ui->lineEdit_Double1->text();
    double d = strDouble.toDouble();
    const char* ch = (char*)(&d);
    QByteArray ba = QByteArray(ch, 8);
    // Big end mode, reversed
    if(!ui->checkBox_LittleEndian3->isChecked())
        std::reverse(ba.begin(), ba.end());
    QString str = "";
    if(ui->checkBox_Separator3->isChecked())
        str = ba.toHex(' ').toUpper();
    else
        str = ba.toHex().toUpper();
    ui->lineEdit_Hex3->setText(str);
}

void DataCheckForm::on_lineEdit_Double1_editingFinished()
{
    QString strDouble = ui->lineEdit_Double1->text();
    double d = strDouble.toDouble();
    qInfo().noquote() << QString::number(d, 'f', 13);
    ui->lineEdit_Double1_MemVal->setText(QString::number(d, 'f', 13));
}

void DataCheckForm::on_pushButton_Convert4_clicked()
{
    QString strHex = ui->lineEdit_Hex4->text().trimmed();
    if(strHex.remove(' ').length() < 16)
    {
        QMessageBox::information(this, "信息提示", "请输入16个十六进制字符！");
        return;
    }
    QByteArray ba = QByteArray::fromHex(strHex.toLatin1());
    double d;
    char* ch = (char*)(&d);
    if(!ui->checkBox_LittleEndian4->isChecked())
        std::reverse(ba.begin(), ba.end());
    for(auto i=0; i<8; ++i)
        *(ch+i) = ba[i];

    QString strDouble = QString::number(d, 'f', ui->comboBox_Double2_ReservedBits->currentIndex());
    ui->lineEdit_Double2->setText(strDouble);
    ui->lineEdit_Double2_MemVal->setText(QString::number(d, 'f', 13));

}

void DataCheckForm::on_pushButton_ChangeMemMode3_clicked()
{
    if(ui->checkBox_LittleEndian3->isChecked())
    { // little endian mode
        ui->checkBox_LittleEndian3->setChecked(false);
        ui->checkBox_LittleEndian3->setText("大端模式");
    }
    else
    {
        ui->checkBox_LittleEndian3->setChecked(true);
        ui->checkBox_LittleEndian3->setText("小端模式");
    }
}

void DataCheckForm::on_checkBox_LittleEndian4_stateChanged(int arg1)
{
    if(arg1 == 2)
        ui->checkBox_LittleEndian4->setText("小端模式");
    else
        ui->checkBox_LittleEndian4->setText("大端模式");
}