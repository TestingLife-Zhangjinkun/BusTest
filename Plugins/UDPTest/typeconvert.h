#ifndef TYPECONVERT_H
#define TYPECONVERT_H

#include <QObject>
#include <QDebug>

class TypeConvert : public QObject
{
    Q_OBJECT
public:
    /***** Singleton pattern class definition *******/
    static TypeConvert& getTCInstance()
    {
        static TypeConvert instance;
        return instance;
    }

    TypeConvert(QObject *parent = nullptr): QObject(parent)
    {
    }

    TypeConvert(const TypeConvert&, QObject *parent = nullptr): QObject(parent)
    {
    }

    /***** Function definition *******/
    // 十六进制字符串转QByteArray
    QByteArray HexStringToByteArray(const QString &hexStr);
    // 无空格的十六进制字符串转有空格的十六进制字符串
    QString StringNoNullToNull(const QString &hexStr);
    // QByteArray转十六进制字符串
    QString ByteArrayToHexString(QByteArray baData);
    // 缺省转换为4Bytes长度
    const QString DecToHexString(quint32, quint16 len = 4, const bool isLittleEndian = false);
    // 十进制转十六进制
    void DecToHex(int dec, quint8 *hex, int len);

};

#endif // TYPECONVERT_H
