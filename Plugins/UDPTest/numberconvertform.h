#ifndef NUMBERCONVERTFORM_H
#define NUMBERCONVERTFORM_H

#include <QWidget>
#include <QButtonGroup>
#include "typeconvert.h"
#include <QTextEdit>

namespace Ui {
class NumberConvertForm;
}

class NumberConvertForm : public QWidget
{
    Q_OBJECT

public:
    /***** Singleton pattern class definition *******/
    static NumberConvertForm& getDCFInstance()
    {
        static NumberConvertForm instance;
        return instance;
    }

    explicit NumberConvertForm(QWidget *parent = nullptr);
    ~NumberConvertForm();

    enum CRC8_Mode
    {
        Crc8 = 0,
        Crc8_ITU,
        Crc8_ROHC,
        Crc8_MAXIM,
        CheckSum_8,
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
    enum Hash_Mode
    {
        md5 = 0
    };

    enum CHECKSUM_Mode
    {
        Checksum_8 = 0,
        Checksum_8_REVERSE,
        Checksum_16,
        Checksum_16_REVERSE,
        SumCheck_8,
        Xor_8,
    };

    Q_ENUM(CRC8_Mode)
    Q_ENUM(CRC16_Mode)
    Q_ENUM(CRC32_Mode)
    Q_ENUM(Hash_Mode)
    Q_ENUM(CHECKSUM_Mode)

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

    // MD5加密算法
    Q_INVOKABLE QByteArray MD5(const QByteArray &data);

    // 校验和系列算法
    Q_INVOKABLE quint8 CHECKSUM_8(char *data, quint16 dataLen);
    Q_INVOKABLE quint8 CHECKSUM_8_REVERSE(char *data, quint16 dataLen);
    Q_INVOKABLE quint16 CHECKSUM_16(char *data, quint16 dataLen);
    Q_INVOKABLE quint16 CHECKSUM_16_REVERSE(char *data, quint16 dataLen);
    Q_INVOKABLE quint8 SUMCHECK_8(char *data, quint16 dataLen);
    Q_INVOKABLE quint8 XOR_8(char *data, quint16 dataLen);


private slots:
    void on_pushButton_UpdateCRCParams_clicked();

    void on_comboBox_ChecksumLength_currentIndexChanged(int index);

    void on_pushButton_Generate_Checkcode_clicked();

    // 选择CRC校验码字节序的多个QRadioButton控件的槽函数
    void onRadioClickSelecByteOrder();

    void on_checkBox_FormatData_stateChanged(int arg1);

    void on_textEdit_CRCInput_textChanged();

    void on_pushButton_Generate_MD5_clicked();

    void on_pushButton_Select_File_clicked();

    // 选择MD5校验码输入数据类型的两个QRadioButton控件的槽函数
    void onRadioClickSelecDataType();

    void on_checkBox_ByteOrder_stateChanged(int arg1);

    void on_checkBox_FormatData_2_stateChanged(int arg1);

    void on_pushButton_Generate_Checksum_clicked();

    void on_checkBox_Checksum_ByteOrder_stateChanged(int arg1);

    void on_checkBox_Checksum_FormatData_stateChanged(int arg1);

    void on_pushButton_Clear_Checksum_clicked();

    void on_textEdit_ChecksumInput_textChanged();

    void on_pushButton_Clear_Checkcode_clicked();

    void on_comboBox_CheckAlgorithm_activated(int index);

    void on_pushButton_Clear_MD5_clicked();

    void on_textEdit_MD5Input_textChanged();

private:
    void InvertUint16(quint16 *destUShort, quint16 *srcUShort);
    void InvertUint8(quint8 *destUch, quint8 *srcUch);
    void InvertUint32(quint32 *destUInt, quint32 *srcUInt);
    // 显示CRC8校验配置列表
    void DisPlay_CRC8_Configation_List();
    void DisPlay_CRC16_Configation_List();
    void DisPlay_CRC32_Configation_List();
    // 只接受十六进制字符输入
    void HexCharInput(QTextEdit* textEdit);
    // 初始化CRC校验配置参数
    void Init_CRC_Config_Params();

    Ui::NumberConvertForm *ui;

    // CRC16 Sheet配置数据
    QVector<QVector<QString>> crc16Data;
    QVector<QVector<QString>> crc8Data;
    QVector<QVector<QString>> crc32Data;

    TypeConvert tcInstance = TypeConvert::getTCInstance();
    // false：小端存储；true：大端存储。缺省为小端存储
    bool  crcByteOrder = false;
    QButtonGroup *sendModeGroup = nullptr;
    // false：ASCII；true：Hex。缺省为Hex
    bool  md5DataType = true;
    QButtonGroup *dataTypeGroup = nullptr;

    // false：小端存储；true：大端存储。缺省为大端存储
    bool  checksumByteOrder = true;

    // MD5输入文件大小，小于loadSize，一次性读取所有内容计算MD5值；大于则分段读取文件内容，计算MD5值
    const qint64 loadSize = 1024*10;


};

#endif // NUMBERCONVERTFORM_H
