#include "datacheckform.h"
#include "ui_datacheckform.h"
#include <QDebug>
#include <QMessageBox>
#include <QMetaEnum>
#include <QTextBlock>

quint16 DataCheckForm::CRC16_USB(char *data, quint16 dataLen)
{
    quint16 initValue = 0xFFFF;
    quint16 poly = 0x8005;

    InvertUint16(&poly, &poly);
    while (dataLen--)
    {
        initValue ^= *(data++);
        for(auto i = 0; i < 8; i++)
        {
            if(initValue & 0x01)
            {
                initValue = (initValue >> 1) ^ poly;
            }
            else
            {
                initValue = initValue >> 1;
            }
        }
    }
    return (initValue ^ 0xFFFF);

}

quint16 DataCheckForm::CRC16_DNP(char *data, quint16 dataLen)
{
    quint16 initValue = 0x0000;
    quint16 poly = 0x3D65;

    InvertUint16(&poly, &poly);
    while (dataLen--)
    {
        initValue ^= *(data++);
        for(int i = 0;i < 8;i++)
        {
            if(initValue & 0x01)
            {
                initValue = (initValue >> 1) ^ poly;
            }
            else
            {
                initValue = (initValue >> 1);
            }
        }
    }

    return (initValue ^ 0xFFFF);
}

quint32 DataCheckForm::CRC32_WINRAR(char *data, quint16 dataLen)
{
    quint32 initValue = 0xFFFFFFFF;
    quint32 poly = 0x04C11DB7;

    InvertUint32(&poly, &poly);
    while (dataLen--)
    {
        initValue ^= *(data++);
        for(int i = 0;i < 8;i++)
        {
            if(initValue & 0x01)
            {
                initValue = (initValue >> 1) ^ poly;
            }
            else
            {
                initValue = initValue >> 1;
            }
        }
    }

    return (initValue ^ 0xFFFFFFFF) ;
}

quint16 DataCheckForm::CRC16_IBM(char *data, quint16 dataLen)
{
    quint16 initValue = 0x0000;
    quint16 poly = 0x8005;

    InvertUint16(&poly, &poly);
    while (dataLen--)
    {
        initValue ^= *(data++);
        for(int i = 0;i < 8;i++)
        {
            if(initValue & 0x01)
                initValue = (initValue >> 1) ^ poly;
            else
                initValue = initValue >> 1;
        }
    }
    return initValue;
}

quint16 DataCheckForm::CRC16_MAXIM(char *data, quint16 dataLen)
{
    quint16 initValue = 0x0000;
    quint16 poly = 0x8005;

    InvertUint16(&poly, &poly);
    while (dataLen--)
    {
        initValue ^= *(data++);
        for(auto i = 0; i < 8; i++)
        {
            if(initValue & 0x01)
            {
                initValue = (initValue >> 1) ^ poly;
            }
            else
            {
                initValue = initValue >> 1;
            }
        }
    }

    return (initValue ^ 0xFFFF);
}

/****************************Info**********************************************
* Name:    CRC-32/MPEG-2  x32+x26+x23+x22+x16+x12+x11+x10+x8+x7+x5+x4+x2+x+1
* Width:	32
* Poly:    0x4C11DB7
* Init:    0xFFFFFFF
* Refin:   False
* Refout:  False
* Xorout:  0x0000000
* Note:
*****************************************************************************/
quint32 DataCheckForm::CRC32_MPEG(char *data, quint16 dataLen)
{
    quint32 initValue = 0xFFFFFFFF;
    quint32 poly = 0x04C11DB7;
    quint8 uCh = 0;

    while (dataLen--)
    {
        uCh = *(data++);
        initValue ^= (uCh << 24);
        for(auto i = 0; i < 8; i++)
        {
            if(initValue & 0x80000000)
            {
                initValue = (initValue << 1) ^ poly;
            }
            else
            {
                initValue = initValue << 1;
            }
        }
    }

    return initValue;
}

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

    ui->lineEdit_Double1_MemVal->setFocusPolicy(Qt::NoFocus);
    ui->checkBox_LittleEndian3->setChecked(true);
    ui->checkBox_LittleEndian3->setDisabled(true);
    ui->checkBox_Separator3->setChecked(true);
    ui->lineEdit_Hex3->setReadOnly(true);

    QRegExpValidator* doubleRegExp = new QRegExpValidator(QRegExp("^(-?\\d+)(\\.\\d{0,13})?$"));
    ui->lineEdit_Double1->setValidator(doubleRegExp);

    ui->checkBox_LittleEndian4->setChecked(true);
    QStringList list1 = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
                         "10", "11", "12", "13"};
    ui->comboBox_Double2_ReservedBits->addItems(list1);
    ui->comboBox_Double2_ReservedBits->setCurrentIndex(2);
    ui->lineEdit_Double2->setReadOnly(true);
    ui->lineEdit_Double2_MemVal->setFocusPolicy(Qt::NoFocus);

    QRegExpValidator* hexRegExp1 = new QRegExpValidator(QRegExp("([a-fA-F0-9]{2}\\s?){7}[a-fA-F0-9]{2}"));
    ui->lineEdit_Hex4->setValidator(hexRegExp1);

    ui->checkBox_LittleEndian5->setChecked(true);
    ui->checkBox_LittleEndian5->setDisabled(true);
    ui->checkBox_Separator5->setChecked(true);
    ui->checkBox_LittleEndian2->setChecked(true);
    QStringList list2 = {"Int8", "UInt8", "Int16", "UInt16", "Int32", "UInt32", "Int64", "UInt64"};
    ui->comboBox_IntType1->addItems(list2);
    ui->comboBox_IntType1->setCurrentIndex(4);
    ui->lineEdit_Hex5->setReadOnly(true);

    QRegExpValidator* intRegExp = new QRegExpValidator(QRegExp("^-?\\d+$"));
    ui->lineEdit_Int1->setValidator(intRegExp);

    ui->comboBox_IntType2->addItems(list2);
    ui->comboBox_IntType2->setCurrentIndex(4);
    ui->checkBox_LittleEndian6->setChecked(true);

    ui->lineEdit_Hex6->setValidator(hexRegExp1);

    //******************************//
    QStringList byteLengthList = {"1??????", "2??????", "4??????"};
    ui->comboBox_ChecksumLength->blockSignals(true);
    ui->comboBox_ChecksumLength->addItems(byteLengthList);
    ui->comboBox_ChecksumLength->blockSignals(false);
    ui->comboBox_ChecksumLength->setCurrentIndex(1);

    //zjk 20221102
    // ????????????????????????????????????
    sendModeGroup = new QButtonGroup(this);
    sendModeGroup->addButton(ui->radioButton_SmallStorage, 0);
    sendModeGroup->addButton(ui->radioButton_BigStorage, 1);
    // ????????????????????????
    ui->radioButton_SmallStorage->setChecked(true);
    // ??????????????????
    connect(ui->radioButton_SmallStorage, SIGNAL(clicked()), this, SLOT(onRadioClickSelecByteOrder()));
    connect(ui->radioButton_BigStorage, SIGNAL(clicked()), this, SLOT(onRadioClickSelecByteOrder()));
}

DataCheckForm::~DataCheckForm()
{
    delete ui;
}

quint8 DataCheckForm::CRC8(char *data, quint16 dataLen)
{
    quint8 initValue = 0x00;
    quint8 poly = 0x07;

    while (dataLen--)
    {
        initValue ^= *(data++);
        for(auto i = 0; i < 8; i++)
        {
            if(initValue & 0x80)
            {
                initValue = (initValue << 1) ^ poly;
            }
            else
            {
                initValue = initValue << 1;
            }
        }
    }

    return initValue;
}

quint8 DataCheckForm::CRC8_MAXIM(char *data, quint16 dataLen)
{
    quint8 initValue = 0x00;
    quint8 poly = 0x31;

    InvertUint8(&poly, &poly);
    while (dataLen--)
    {
        initValue ^= *(data++);
        for(auto i = 0; i < 8; i++)
        {
            if(initValue & 0x01)
            {
                initValue = (initValue >> 1) ^ poly;
            }
            else
            {
                initValue = initValue >> 1;
            }
        }
    }

    return initValue;
}

/****************************Info**********************************************
* Name:    CRC-8/ITU           x8+x2+x+1
* Width:	8
* Poly:    0x07
* Init:    0x00
* Refin:   False
* Refout:  False
* Xorout:  0x55
* Alias:   CRC-8/ATM
*****************************************************************************/
quint8 DataCheckForm::CRC8_ITU(char *data, quint16 dataLen)
{
    quint8 initValue = 0x00;
    quint8 poly = 0x07;

    while (dataLen--)
    {
        initValue ^= *(data++);
        for(auto i = 0;i < 8;i++)
        {
            if(initValue & 0x80)
            {
                initValue = (initValue << 1) ^ poly;
            }
            else
            {
                initValue = initValue << 1;
            }
        }
    }

    return (initValue ^ 0x55);
}

/****************************Info**********************************************
* Name:    CRC-8/ROHC          x8+x2+x+1
* Width:	8
* Poly:    0x07
* Init:    0xFF
* Refin:   True
* Refout:  True
* Xorout:  0x00
* Note:
*****************************************************************************/
quint8 DataCheckForm::CRC8_ROHC(char *data, quint16 dataLen)
{
    quint8 initValue = 0xFF;
    quint8 poly = 0x07;

    InvertUint8(&poly, &poly);
    while (dataLen--)
    {
        initValue ^= *(data++);
        for(auto i = 0; i < 8; i++)
        {
            if(initValue & 0x01)
            {
                initValue = (initValue >> 1) ^ poly;
            }
            else
            {
                initValue = initValue >> 1;
            }
        }
    }

    return initValue;
}

//?????????????????????????????????????????????Refin???refout???true?????????????????????????????????
//????????????poly???????????????????????????????????????????????????
quint16 DataCheckForm::CRC16_CCITT_TRUE(char *data, quint16 dataLen)
{
    quint16 initValue = 0x0000;     // ?????????
    quint16 poly = 0x1021;          // ?????????

    InvertUint16(&poly, &poly);
    while (dataLen--)
    {
        initValue ^= *(data++);
        for(int i = 0;i < 8;i++)
        {
            if(initValue & 0x01)
            {
                initValue = (initValue >> 1) ^ poly;
            }
            else
            {
                initValue = initValue >> 1;
            }
        }
    }

    return initValue;
}

/****************************Info**********************************************
* Name:    CRC-16/CCITT-FALSE   x16+x12+x5+1
* Width:	16
* Poly:    0x1021
* Init:    0xFFFF
* Refin:   False
* Refout:  False
* Xorout:  0x0000
* Note:
*****************************************************************************/
quint16 DataCheckForm::CRC16_CCITT_FALSE(char *data, quint16 dataLen)
{
    quint16 initValue = 0xFFFF;
    quint16 poly = 0x1021;

    while (dataLen--)
    {
        initValue ^= *(data++) << 8;
        for(int i = 0;i < 8; i++)
        {
            if(initValue & 0x8000)
            {
                initValue = (initValue << 1) ^ poly;
            }
            else
            {
                initValue = initValue << 1;
            }
        }
    }

    return initValue;
}

/****************************Info**********************************************
* Name:    CRC-16/XMODEM       x16+x12+x5+1
* Width:	16
* Poly:    0x1021
* Init:    0x0000
* Refin:   False
* Refout:  False
* Xorout:  0x0000
* Alias:   CRC-16/ZMODEM,CRC-16/ACORN
*****************************************************************************/
quint16 DataCheckForm::CRC16_XMODEM(char *data, quint16 dataLen)
{
    quint16 initValue = 0x0000;
    quint16 poly = 0x1021;

    while (dataLen--)
    {
        initValue ^= (*(data++) << 8);
        for(int i = 0; i < 8; i++)
        {
            if(initValue & 0x8000)
            {
                initValue = (initValue << 1) ^ poly;
            }
            else
            {
                initValue = initValue << 1;
            }
        }
    }

    return initValue;
}

quint16 DataCheckForm::CRC16_X25(char *data, quint16 dataLen)
{
    quint16 initValue = 0xFFFF;
    quint16 poly = 0x1021;

    InvertUint16(&poly, &poly);
    while (dataLen--)
    {
        initValue ^= *(data++);
        for(auto i = 0; i < 8; i++)
        {
            if(initValue & 0x01)
            {
                initValue = (initValue >> 1) ^ poly;
            }
            else
            {
                initValue = initValue >> 1;
            }
        }
    }

    return (initValue ^ 0xFFFF);
}

quint16 DataCheckForm::CRC16_MODBUS(char *data, quint16 dataLen)
{
    quint16 initValue = 0xFFFF;
    quint16 poly = 0x8005;

    InvertUint16(&poly, &poly);
    while (dataLen--)
    {
        initValue ^= *(data++);
        for(int i = 0;i < 8;i++)
        {
            if(initValue & 0x01)
            {
                initValue = (initValue >> 1) ^ poly;
            }
            else
            {
                initValue = initValue >> 1;
            }
        }
    }

    return initValue;
}

/***
 * ????????????????????????????????????????????????????????????????????????????????????????????????float/double?????????????????????????????????????????????????????????
 * double???8?????????float???4??????
 * qulonglong???8?????????qint32???quint32???4??????
 ***/

// Floating point to hexadecimal conversion
void DataCheckForm::on_pushButton_Convert1_clicked()
{
    if(ui->lineEdit_Float1->text().trimmed().isEmpty())
    {
        QMessageBox::information(this, "????????????", "??????????????????????????????");
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
        QMessageBox::information(this, "????????????", "?????????8????????????????????????");
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

// ?????????????????????????????????????????????
void DataCheckForm::on_lineEdit_Float1_editingFinished()
{
    QString strFloat = ui->lineEdit_Float1->text();
    float f = strFloat.toFloat();
    qInfo().noquote() << QString::number(f, 'f', 6);
    ui->lineEdit_Float1_MemVal->setText(QString::number(f, 'f', 6));
}

// ??????????????????????????????????????????
void DataCheckForm::on_pushButton_ChangeMemMode1_clicked()
{
    if(ui->checkBox_LittleEndian->isChecked())
    { // little endian mode
        ui->checkBox_LittleEndian->setChecked(false);
        ui->checkBox_LittleEndian->setText("????????????");
    }
    else
    {
        ui->checkBox_LittleEndian->setChecked(true);
        ui->checkBox_LittleEndian->setText("????????????");
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
        ui->checkBox_LittleEndian2->setText("????????????");
    else
        ui->checkBox_LittleEndian2->setText("????????????");
}


void DataCheckForm::on_lineEdit_Hex2_textChanged(const QString &arg1)
{
    ui->lineEdit_Hex2->setText(tcInstance.StringNoNullToNull(arg1));
}

// ??????????????????????????????????????????
void DataCheckForm::on_pushButton_Convert3_clicked()
{
    if(ui->lineEdit_Double1->text().trimmed().isEmpty())
    {
        QMessageBox::information(this, "????????????", "??????????????????????????????");
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
    //    qInfo().noquote() << QString::number(d, 'f', 13);
    ui->lineEdit_Double1_MemVal->setText(QString::number(d, 'f', 13));
}

void DataCheckForm::on_pushButton_Convert4_clicked()
{
    QString strHex = ui->lineEdit_Hex4->text().trimmed();
    if(strHex.remove(' ').length() < 16)
    {
        QMessageBox::information(this, "????????????", "?????????16????????????????????????");
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
        ui->checkBox_LittleEndian3->setText("????????????");
    }
    else
    {
        ui->checkBox_LittleEndian3->setChecked(true);
        ui->checkBox_LittleEndian3->setText("????????????");
    }
}

void DataCheckForm::on_checkBox_LittleEndian4_stateChanged(int arg1)
{
    if(arg1 == 2)
        ui->checkBox_LittleEndian4->setText("????????????");
    else
        ui->checkBox_LittleEndian4->setText("????????????");
}

void DataCheckForm::on_lineEdit_Hex4_textChanged(const QString &arg1)
{
    ui->lineEdit_Hex4->setText(tcInstance.StringNoNullToNull(arg1));
}

// ??????????????????????????????
void DataCheckForm::on_pushButton_Convert5_clicked()
{
    if(ui->lineEdit_Int1->text().trimmed().isEmpty())
    {
        QMessageBox::information(this, "????????????", "??????????????????");
        return;
    }

    QString strInt = ui->lineEdit_Int1->text();
    QVariant i;
    const char* ch = (char*)(&i);
    bool ok;
    int base = 10;
    QByteArray ba;
    switch (ui->comboBox_IntType1->currentIndex())
    {
    case 0:
        i = strInt.toInt(&ok, base);
        if(i<-128 || i > 127)
        {
            QMessageBox::information(this, "????????????", "Int8?????????????????????-128~127");
            return;
        }
        ba = QByteArray(ch, 1);
        break;
    case 1:
        i = strInt.toInt(&ok, base);
        if(i<0 || i > 255)
        {
            QMessageBox::information(this, "????????????", "UInt8?????????????????????0~255");
            return;
        }
        ba = QByteArray(ch, 1);
        break;
    case 2:
        i = strInt.toShort(&ok, base);
        if(!ok)
        {
            QMessageBox::information(this, "????????????", "Int16?????????????????????-32768~32767");
            return;
        }
        ba = QByteArray(ch, 2);
        break;
    case 3:
        i = strInt.toUShort(&ok, base);
        if(!ok)
        {
            QMessageBox::information(this, "????????????", "Int16?????????????????????0~65535");
            return;
        }
        ba = QByteArray(ch, 2);
        break;
    case 4:
        i = strInt.toInt(&ok, base);
        if(!ok)
        {
            QMessageBox::information(this, "????????????", "Int32?????????????????????-2147483648~2147483647");
            return;
        }
        ba = QByteArray(ch, 4);
        break;
    case 5:
        i = strInt.toUInt(&ok, base);
        if(!ok)
        {
            QMessageBox::information(this, "????????????", "UInt32?????????????????????0~4294967295");
            return;
        }
        ba = QByteArray(ch, 4);
        break;
    case 6:
        i = strInt.toLongLong(&ok, base);
        if(!ok)
        {
            QMessageBox::information(this, "????????????", "?????????Int64?????????????????????????????????");
            return;
        }
        ba = QByteArray(ch, 8);
        break;
    case 7:
        i = strInt.toULongLong(&ok, base);
        if(!ok)
        {
            QMessageBox::information(this, "????????????", "?????????UInt64?????????????????????????????????");
            return;
        }
        ba = QByteArray(ch, 8);
        break;
    default:
        break;
    }
    // Big end mode, reversed
    if((ui->comboBox_IntType1->currentIndex() > 1) && (!ui->checkBox_LittleEndian5->isChecked()))
        std::reverse(ba.begin(), ba.end());
    QString str = "";
    if(ui->checkBox_Separator5->isChecked())
        str = ba.toHex(' ').toUpper();
    else
        str = ba.toHex().toUpper();
    ui->lineEdit_Hex5->setText(str);

}

void DataCheckForm::on_pushButton_ChangeMemMode5_clicked()
{
    if(ui->checkBox_LittleEndian5->isChecked())
    { // little endian mode
        ui->checkBox_LittleEndian5->setChecked(false);
        ui->checkBox_LittleEndian5->setText("????????????");
    }
    else
    {
        ui->checkBox_LittleEndian5->setChecked(true);
        ui->checkBox_LittleEndian5->setText("????????????");
    }
}

// ????????????????????????????????????
void DataCheckForm::on_pushButton_Convert6_clicked()
{
    QString strHex = ui->lineEdit_Hex6->text().trimmed();
    QByteArray ba = QByteArray::fromHex(strHex.toLatin1());
    quint16 byteLen = 0;
    QVariant i;
    switch (ui->comboBox_IntType2->currentIndex())
    {
    case 0:
        i = (qint8)0;
        byteLen = 1;
        break;
    case 1:
        i = (quint8)0;
        byteLen = 1;
        break;
    case 2:
        i = (qint16)0;
        byteLen = 2;
        break;
    case 3:
        i = (quint16)0;
        byteLen = 2;
        break;
    case 4:
        i = (qint32)0;
        byteLen = 4;
        break;
    case 5:
        i = (quint32)0;
        byteLen = 4;
        break;
    case 6:
        i = (qint64)0;
        byteLen = 8;
        break;
    case 7:
        i = (quint64)0;
        byteLen = 8;
        break;
    default:
        break;
    }
    if(ba.size() != byteLen)
    {
        QMessageBox::information(this, "????????????", "?????????????????????????????????????????????????????????");
        return;
    }
    char* ch = (char*)(&i);
    if(!ui->checkBox_LittleEndian6->isChecked())
        std::reverse(ba.begin(), ba.end());
    for(auto index=0; index<byteLen; ++index)
        *(ch+index) = ba[index];

    QString strInt = "";
    bool ok;
    switch (ui->comboBox_IntType2->currentIndex())
    {
    case 0:
        // handle negative numbers
        if(i.toInt(&ok) & 0x80)
            strInt = QString::number(i.toInt(&ok) - 0xFF - 1);
        else
            strInt = QString::number(i.toInt(&ok));
        break;
    case 1:
        strInt = QString::number(i.toUInt());
        break;
    case 2:
        // handle negative numbers
        if(i.toInt(&ok) & 0x8000)
            strInt = QString::number(i.toInt(&ok) - 0xFFFF - 1);
        else
            strInt = QString::number(i.toInt(&ok));
        break;
    case 3:
        strInt = QString::number(i.toUInt());
        break;
    case 4:
        strInt = QString::number(i.toInt());
        break;
    case 5:
        strInt = QString::number(i.toUInt());
        break;
    case 6:
        strInt = QString::number(i.toLongLong());
        break;
    case 7:
        strInt = QString::number(i.toULongLong());
        break;
    default:
        break;
    }
    ui->lineEdit_Int2->setText(strInt);
}

void DataCheckForm::on_lineEdit_Hex6_textChanged(const QString &arg1)
{
    ui->lineEdit_Hex6->setText(tcInstance.StringNoNullToNull(arg1));
}

// ????????????????????????????????????
void DataCheckForm::on_comboBox_ChecksumLength_currentIndexChanged(int index)
{
    ui->comboBox_CheckAlgorithm->clear();
    QMetaEnum me;
    switch (index)
    {
    case 0:
        // ????????????????????????????????????
        me = QMetaEnum::fromType<DataCheckForm::CRC8_Mode>();
        for(auto i = 0; i < me.keyCount(); ++i)
            ui->comboBox_CheckAlgorithm->addItem(me.key(i));
        break;
    case 1:
        me = QMetaEnum::fromType<DataCheckForm::CRC16_Mode>();
        for(auto i = 0; i < me.keyCount(); ++i)
            ui->comboBox_CheckAlgorithm->addItem(me.key(i));
        break;
    case 2:
        me = QMetaEnum::fromType<DataCheckForm::CRC32_Mode>();
        for(auto i = 0; i < me.keyCount(); ++i)
            ui->comboBox_CheckAlgorithm->addItem(me.key(i));
        break;
    default:
        break;
    }
}

// ?????????????????????  20221102
void DataCheckForm::on_pushButton_Generate_Checkcode_clicked()
{
    QString hexStr = ui->textEdit_ByteString->toPlainText();
    QByteArray ba = tcInstance.HexStringToByteArray(hexStr);
    DataCheckForm& pCRC = DataCheckForm::getDCFInstance();
    char* pCrcCheckSum = ba.data();    // QByteArray???char*
    quint8 ret8 = 0;
    quint16 ret16 = 0;
    quint32 ret32 = 0;
    QString methodName = ui->comboBox_CheckAlgorithm->currentText().toUpper();
    bool callResult = false;
    switch (ui->comboBox_ChecksumLength->currentIndex())
    {
    case 0: // ??????1???????????????
        callResult = QMetaObject::invokeMethod(&pCRC, methodName.toLatin1().data(), Qt :: AutoConnection,
                                               Q_RETURN_ARG(quint8, ret8),
                                               Q_ARG(char*, pCrcCheckSum), Q_ARG(quint16, ba.size()));
        break;
    case 1: // ??????2???????????????
        // Note????????????QMetaObject::invokeMethod????????????????????????????????????Q_ARG()????????????quint8?????????????????????char
        callResult = QMetaObject::invokeMethod(&pCRC, methodName.toLatin1().data(), Qt :: AutoConnection,
                                               Q_RETURN_ARG(quint16, ret16),
                                               Q_ARG(char*, pCrcCheckSum), Q_ARG(quint16, ba.size()));
        break;
    case 2: // ??????4???????????????
        qRegisterMetaType<quint32>("quint32");
        callResult = QMetaObject::invokeMethod(&pCRC, methodName.toLatin1().data(), Qt :: AutoConnection,
                                               Q_RETURN_ARG(quint32, ret32),
                                               Q_ARG(char*, pCrcCheckSum), Q_ARG(quint16, ba.size()));
        break;
    default:
        ;
    }
    if(!callResult)
    {
        ui->lineEdit_Checkcode->setText("???????????????????????????");
        return;
    }
    // ?????????????????????????????????
    QString checkcode = "";
    switch (ui->comboBox_ChecksumLength->currentIndex())
    {
    case 0:
        qDebug().noquote() << "?????????????????????" << ret8;
        checkcode = tcInstance.DecToHexString(ret8, 1, !crcByteOrder);
        qDebug().noquote() << "????????????????????????" << checkcode;
        ui->lineEdit_Checkcode_Dec->setText(QString::number(ret8));
        break;
    case 1:
        qDebug().noquote() << "?????????????????????" << ret16;
        checkcode = tcInstance.DecToHexString(ret16, 2, !crcByteOrder);
        qDebug().noquote() << "????????????????????????" << checkcode;
        ui->lineEdit_Checkcode_Dec->setText(QString::number(ret16));
        break;
    case 2:
        qDebug().noquote() << "?????????????????????" << ret32;
        checkcode = tcInstance.DecToHexString(ret32, 4, !crcByteOrder);
        qDebug().noquote() << "????????????????????????" << checkcode;
        ui->lineEdit_Checkcode_Dec->setText(QString::number(ret32));
        break;
    default:
        ;
    }
    ui->lineEdit_Checkcode->setText(checkcode);
    ui->textEdit_ByteString->setText(tcInstance.StringNoNullToNull(hexStr+checkcode));

}

void DataCheckForm::onRadioClickSelecByteOrder()
{
    // ??????ID??????????????????radioButton?????????
    int idNumber = sendModeGroup->checkedId();
    switch (idNumber)
    {
    case 0: // ??????????????????????????????????????????
        crcByteOrder = false;
        break;
    case 1:
        crcByteOrder = true;
        break;
    default:
        crcByteOrder = false;
        break;
    }
}

// ???quint16????????????bit???????????????????????????InvertUint8
void DataCheckForm::InvertUint16(quint16 *destUShort, quint16 *srcUShort)
{
    quint16 uShort = 0;

    for(auto i = 0; i < 16; i++)
    {
        if(*srcUShort & (1 << i))
        {
            uShort |= 1 << (15 - i);
        }
    }

    *destUShort = uShort;
}

/****************************Info**********************************************
* Name: InvertUint8
* Note: ???????????????????????????0x12??????0x48
*       0x12: 0001 0010
*       0x48: 0100 1000
*****************************************************************************/
void DataCheckForm::InvertUint8(quint8 *destUch, quint8 *srcUch)
{
    quint8 uCh = 0;  // ????????????????????????????????????

    for(auto i = 0; i < 8; i++)
    {
        if(*srcUch & (1 << i))
        {   // ??????srcUch??????i????????????1?????????????????????7-i??????1
            uCh |= 1 << (7-i);   // ???ch??????7-i??????1
        }
    }

    *destUch = uCh;
}

void DataCheckForm::InvertUint32(quint32 *destUInt, quint32 *srcUInt)
{
    quint32 uInt = 0;

    for(auto i=0; i< 32; i++)
    {
        if(*srcUInt & (1 << i))
            uInt |= 1 << (31 - i);
    }

    *destUInt = uInt;
}

void DataCheckForm::on_checkBox_FormatData_stateChanged(int arg1)
{
    QString sendStr = ui->textEdit_ByteString->toPlainText();
    if(arg1 == 2)
    {
        QByteArray ba = tcInstance.HexStringToByteArray(sendStr);
        sendStr = ba.toHex(' ').data();
    }
    else if(arg1 == 0)
    {
        sendStr = sendStr.remove(" ");
    }
    ui->textEdit_ByteString->setText(sendStr.toUpper());
}

void DataCheckForm::on_textEdit_ByteString_textChanged()
{
    QTextCursor cursor = ui->textEdit_ByteString->textCursor();   // ??????
    quint16 lineNum = cursor.blockNumber(); // ??????
    quint16 posInBlock = cursor.positionInBlock(); // ????????????????????????????????????????????????
    QString lineText = ui->textEdit_ByteString->document()->findBlockByLineNumber(lineNum).text();

    /* ???????????????????????????????????????????????????????????????????????????0???????????????????????????????????????????????????*/
    if(posInBlock == 0 && lineNum > 0)
    {
        cursor.movePosition(QTextCursor::Down);
        ui->textEdit_ByteString->setTextCursor(cursor);
        return;
    }
    char ch = ' ';
    // ????????????????????????????????????1???????????????????????????????????????????????????Backspace????????????????????????????????????????????????lineText.at(posInBlock-1)????????????
    if(posInBlock >= 1)
    {
        ch = lineText.at(posInBlock-1).toLatin1();
    }
    if((ch == ' ') || (ch >= '0' && ch <='9') || (ch >='a' && ch <= 'f') || (ch >='A' && ch <= 'F'))
    {
        return;
    }
    else
    {
        cursor.deletePreviousChar();
        ui->textEdit_ByteString->setTextCursor(ui->textEdit_ByteString->textCursor());
    }
}
