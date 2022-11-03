#ifndef DATACHECKFORM_H
#define DATACHECKFORM_H

#include <QWidget>
#include "typeconvert.h"
#include <QButtonGroup>

namespace Ui {
class DataCheckForm;
}

class DataCheckForm : public QWidget
{
    Q_OBJECT

public:

    /***** Singleton pattern class definition *******/
    static DataCheckForm& getDCFInstance()
    {
        static DataCheckForm instance;
        return instance;
    }

    explicit DataCheckForm(QWidget *parent = nullptr);
    ~DataCheckForm();

    enum CRC8_Mode
    {
        Crc8 = 0,
        Crc8_ITU,
        Crc8_ROHC,
        Crc8_MAXIM,
    };
    enum CRC16_Mode
    {
        Crc16_CCITT_True = 0,
        Crc16_CCITT_False,
        Crc16_XMODEM,
        Crc16_X25,
        Crc16_MODBUS,
        Crc16_IBM,
        Crc16_MAXIM,
        Crc16_USB,
        Crc16_DNP,
    };
    enum CRC32_Mode
    {
        Crc32_WinRAR = 0,
        Crc32_MPEG
    };
    Q_ENUM(CRC8_Mode)
    Q_ENUM(CRC16_Mode)
    Q_ENUM(CRC32_Mode)

    // Qt反射：就是运行时把字符串映射为类，函数声明时必须使用Q_INVOKABLE
    Q_INVOKABLE quint8 CRC8(char *data, quint16 dataLen);
    Q_INVOKABLE quint8 CRC8_MAXIM(char *data, quint16 dataLen);
    Q_INVOKABLE quint8 CRC8_ITU(char *data, quint16 dataLen);
    Q_INVOKABLE quint8 CRC8_ROHC(char *data, quint16 dataLen);

    Q_INVOKABLE quint16 CRC16_CCITT_TRUE(char *data, quint16 dataLen);
    Q_INVOKABLE quint16 CRC16_CCITT_FALSE(char *data, quint16 dataLen);
    Q_INVOKABLE quint16 CRC16_XMODEM(char *data, quint16 dataLen);
    Q_INVOKABLE quint16 CRC16_X25(char *data, quint16 dataLen);
    Q_INVOKABLE quint16 CRC16_MODBUS(char *data, quint16 dataLen);
    Q_INVOKABLE quint16 CRC16_IBM(char* data, quint16 dataLen);
    Q_INVOKABLE quint16 CRC16_MAXIM(char *data, quint16 dataLen);
    Q_INVOKABLE quint16 CRC16_USB(char* data, quint16 dataLen);
    Q_INVOKABLE quint16 CRC16_DNP(char *data, quint16 dataLen);

    Q_INVOKABLE quint32 CRC32_WINRAR(char *data, quint16 dataLen);         // WinRar使用该校验算法
    Q_INVOKABLE quint32 CRC32_MPEG(char *data, quint16 dataLen);    // MPEG使用该校验算法

private slots:
    void on_pushButton_Convert1_clicked();

    void on_pushButton_Convert2_clicked();

    void on_lineEdit_Float1_editingFinished();

    void on_pushButton_ChangeMemMode1_clicked();

    void on_checkBox_Separator1_stateChanged(int arg1);

    void on_checkBox_LittleEndian2_stateChanged(int arg1);


    void on_lineEdit_Hex2_textChanged(const QString &arg1);

    void on_pushButton_Convert3_clicked();

    void on_lineEdit_Double1_editingFinished();

    void on_pushButton_Convert4_clicked();

    void on_pushButton_ChangeMemMode3_clicked();

    void on_checkBox_LittleEndian4_stateChanged(int arg1);

    void on_lineEdit_Hex4_textChanged(const QString &arg1);

    void on_pushButton_Convert5_clicked();

    void on_pushButton_ChangeMemMode5_clicked();

    void on_pushButton_Convert6_clicked();

    void on_lineEdit_Hex6_textChanged(const QString &arg1);

    void on_comboBox_ChecksumLength_currentIndexChanged(int index);

    void on_pushButton_Generate_Checkcode_clicked();

    // 选择CRC校验码字节序的多个QRadioButton控件的槽函数
    void onRadioClickSelecByteOrder();

    void on_checkBox_FormatData_stateChanged(int arg1);

    void on_textEdit_ByteString_textChanged();

private:
    void InvertUint16(quint16 *destUShort, quint16 *srcUShort);
    void InvertUint8(quint8 *destUch, quint8 *srcUch);
    void InvertUint32(quint32 *destUInt, quint32 *srcUInt);

    Ui::DataCheckForm *ui;
    // Variables for TypeConvert
    TypeConvert tcInstance = TypeConvert::getTCInstance();
    // false：小端存储；true：大端存储。缺省为小端存储
    bool  crcByteOrder = false;
    QButtonGroup *sendModeGroup = nullptr;

};

#endif // DATACHECKFORM_H
