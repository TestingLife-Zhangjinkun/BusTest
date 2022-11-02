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

quint16 DataCheckForm::CRC16_IBM(char *data, quint16 dataLen)
{
    quint16 initValue = 0x0000;
    quint16 poly = 0x8005;

    //    InvertUint16(&poly, &poly);
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
    QStringList byteLengthList = {"1子节", "2子节", "4子节"};
    ui->comboBox_ChecksumLength->blockSignals(true);
    ui->comboBox_ChecksumLength->addItems(byteLengthList);
    ui->comboBox_ChecksumLength->blockSignals(false);
    ui->comboBox_ChecksumLength->setCurrentIndex(1);

    //zjk 20221102
    // 初始化字节序单选按钮分组
    sendModeGroup = new QButtonGroup(this);
    sendModeGroup->addButton(ui->radioButton_SmallStorage, 0);
    sendModeGroup->addButton(ui->radioButton_BigStorage, 1);
    // 初始设置小端存储
    ui->radioButton_SmallStorage->setChecked(true);
    // 绑定信号与槽
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
    //    qInfo().noquote() << QString::number(d, 'f', 13);
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

void DataCheckForm::on_lineEdit_Hex4_textChanged(const QString &arg1)
{
    ui->lineEdit_Hex4->setText(tcInstance.StringNoNullToNull(arg1));
}

// 整数与十六进制的转换
void DataCheckForm::on_pushButton_Convert5_clicked()
{
    if(ui->lineEdit_Int1->text().trimmed().isEmpty())
    {
        QMessageBox::information(this, "信息提示", "请输入整数！");
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
            QMessageBox::information(this, "信息提示", "Int8类型整数范围：-128~127");
            return;
        }
        ba = QByteArray(ch, 1);
        break;
    case 1:
        i = strInt.toInt(&ok, base);
        if(i<0 || i > 255)
        {
            QMessageBox::information(this, "信息提示", "UInt8类型整数范围：0~255");
            return;
        }
        ba = QByteArray(ch, 1);
        break;
    case 2:
        i = strInt.toShort(&ok, base);
        if(!ok)
        {
            QMessageBox::information(this, "信息提示", "Int16类型整数范围：-32768~32767");
            return;
        }
        ba = QByteArray(ch, 2);
        break;
    case 3:
        i = strInt.toUShort(&ok, base);
        if(!ok)
        {
            QMessageBox::information(this, "信息提示", "Int16类型整数范围：0~65535");
            return;
        }
        ba = QByteArray(ch, 2);
        break;
    case 4:
        i = strInt.toInt(&ok, base);
        if(!ok)
        {
            QMessageBox::information(this, "信息提示", "Int32类型整数范围：-2147483648~2147483647");
            return;
        }
        ba = QByteArray(ch, 4);
        break;
    case 5:
        i = strInt.toUInt(&ok, base);
        if(!ok)
        {
            QMessageBox::information(this, "信息提示", "UInt32类型整数范围：0~4294967295");
            return;
        }
        ba = QByteArray(ch, 4);
        break;
    case 6:
        i = strInt.toLongLong(&ok, base);
        if(!ok)
        {
            QMessageBox::information(this, "信息提示", "输入的Int64类型整数超出有效范围！");
            return;
        }
        ba = QByteArray(ch, 8);
        break;
    case 7:
        i = strInt.toULongLong(&ok, base);
        if(!ok)
        {
            QMessageBox::information(this, "信息提示", "输入的UInt64类型整数超出有效范围！");
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
        ui->checkBox_LittleEndian5->setText("大端模式");
    }
    else
    {
        ui->checkBox_LittleEndian5->setChecked(true);
        ui->checkBox_LittleEndian5->setText("小端模式");
    }
}

// 十六进制字符串转换为整数
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
        QMessageBox::information(this, "信息提示", "输入的十六进制字节的长度与类型不匹配！");
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

// 初始化校验算法下拉列表框
void DataCheckForm::on_comboBox_ChecksumLength_currentIndexChanged(int index)
{
    ui->comboBox_CheckAlgorithm->clear();
    QMetaEnum me;
    switch (index)
    {
    case 0:
        // 获得枚举类型的元数据对象
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

// 产生校验码函数  20221102
void DataCheckForm::on_pushButton_Generate_Checkcode_clicked()
{
    QString hexStr = ui->textEdit_ByteString->toPlainText();
    QByteArray ba = tcInstance.HexStringToByteArray(hexStr);
    DataCheckForm& pCRC = DataCheckForm::getDCFInstance();
    char* pCrcCheckSum = ba.data();    // QByteArray转char*
    quint8 ret8 = 0;
    quint16 ret16 = 0;
    quint32 ret32 = 0;
    QString methodName = ui->comboBox_CheckAlgorithm->currentText().toUpper();
    bool callResult = false;
    switch (ui->comboBox_ChecksumLength->currentIndex())
    {
    case 0: // 处理1字节校验码
        callResult = QMetaObject::invokeMethod(&pCRC, methodName.toLatin1().data(), Qt :: AutoConnection,
                                               Q_RETURN_ARG(quint8, ret8),
                                               Q_ARG(char*, pCrcCheckSum), Q_ARG(quint16, ba.size()));
        break;
    case 1: // 处理2字节校验码
        // Note：被调用QMetaObject::invokeMethod的参数类型必须严格一致。Q_ARG()宏不识别quint8类型，需要使用char
        callResult = QMetaObject::invokeMethod(&pCRC, methodName.toLatin1().data(), Qt :: AutoConnection,
                                               Q_RETURN_ARG(quint16, ret16),
                                               Q_ARG(char*, pCrcCheckSum), Q_ARG(quint16, ba.size()));
        break;
    case 2: // 处理4字节校验码
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
        ui->lineEdit_Checkcode->setText("调用校验函数失败！");
        return;
    }
    // 根据字节长度返回校验码
    QString checkcode = "";
    switch (ui->comboBox_ChecksumLength->currentIndex())
    {
    case 0:
        qDebug().noquote() << "十进制校验码：" << ret8;
        checkcode = tcInstance.DecToHexString(ret8, 1, !crcByteOrder);
        qDebug().noquote() << "十六进制校验码：" << checkcode;
        ui->lineEdit_Checkcode_Dec->setText(QString::number(ret8));
        break;
    case 1:
        qDebug().noquote() << "十进制校验码：" << ret16;
        checkcode = tcInstance.DecToHexString(ret16, 2, !crcByteOrder);
        qDebug().noquote() << "十六进制校验码：" << checkcode;
        ui->lineEdit_Checkcode_Dec->setText(QString::number(ret16));
        break;
    case 2:
        qDebug().noquote() << "十进制校验码：" << ret32;
        checkcode = tcInstance.DecToHexString(ret32, 4, !crcByteOrder);
        qDebug().noquote() << "十六进制校验码：" << checkcode;
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
    // 通过ID来获取选中的radioButton的方法
    int idNumber = sendModeGroup->checkedId();
    switch (idNumber)
    {
    case 0: // 小端字节序存储：低在前高在后
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

// 把quint16数（十六bit）颠倒过来，算法同InvertUint8
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
* Note: 把字节颠倒过来，如0x12变成0x48
*       0x12: 0001 0010
*       0x48: 0100 1000
*****************************************************************************/
void DataCheckForm::InvertUint8(quint8 *destUch, quint8 *srcUch)
{
    quint8 uCh = 0;  // 临时变量，暂存翻转后的值

    for(auto i = 0; i < 8; i++)
    {
        if(*srcUch & (1 << i))
        {   // 判断srcUch的第i位，若为1，则翻转后的第7-i位置1
            uCh |= 1 << (7-i);   // 将ch的第7-i位置1
        }
    }

    *destUch = uCh;
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
    QTextCursor cursor = ui->textEdit_ByteString->textCursor();   // 光标
    quint16 lineNum = cursor.blockNumber(); // 行号
    quint16 posInBlock = cursor.positionInBlock(); // 光标所在行的位置，从左边开始计算
    QString lineText = ui->textEdit_ByteString->document()->findBlockByLineNumber(lineNum).text();

    /* 按回车会新开一行，如果判断光标在行首位置且行号大于0则认为新开一行，把光标向下移动一行*/
    if(posInBlock == 0 && lineNum > 0)
    {
        cursor.movePosition(QTextCursor::Down);
        ui->textEdit_ByteString->setTextCursor(cursor);
        return;
    }
    char ch = ' ';
    // 光标所在行的位置大于等于1，才取前一个字符，这是为了预防按下Backspace键回退到一行开始处的位置，会导致lineText.at(posInBlock-1)访问越界
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
