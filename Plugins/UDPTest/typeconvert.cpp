#include "typeconvert.h"

/*********************************************************************************
** 函数名称：       HexStringToByteArray
** 函数描述：       十六进制字符串转QByteArray
** 函数输入参数：    hexStr：十六进制字符串
** 函数输出参数：    无
** 函数返回值：      QByteArray
** 作者：           zjk
** 日期：          ‎2020‎年‎3‎月9‎日 19:19
**********************************************************************************/
QByteArray TypeConvert::HexStringToByteArray(const QString &hexStr)
{
    bool ok;
    QString str = hexStr;   // 先转换为函数内局部变量，再使用
    QByteArray ret; // 定义返回变量

    str = str.remove(" ");  // 去除开始和结尾的空格
//    str = str.simplified(); // 去除开始和结尾的空格，并且将内部空格变成单个空格，也包括去除ASCII码字符
    str = StringNoNullToNull(str);  // 无空格的十六进制字符串转为有空格的字符串，如12 AD EE，即在字节间插入空格
    QStringList list = str.split(" ");  // 通过空格" "分隔字符串

    foreach(QString s, list)
    {
        if(!s.isEmpty())
        {
            char ch = s.toInt(&ok, 16) & 0xFF;
            if(ok)
            {
                ret.append(ch);
            }
            else
            {
                qDebug() << "非法的十六进制字符：" << s;
            }
        }
    }

    return ret;
}

/*********************************************************************************
** 函数名称：       StringNoNullToNull
** 函数描述：       无空格的十六进制字符串转有空格的十六进制字符串
** 函数输入参数：    hexStr：无空格的十六进制字符串
** 函数输出参数：    无
** 函数返回值：      十六进制字符串，以空格分隔字节，如“12 AD FF 4E”
** 作者：           zjk
** 日期：          ‎2020‎年‎3‎月9‎日 21:44
**********************************************************************************/
QString TypeConvert::StringNoNullToNull(const QString &hexStr)
{
    QString ret = hexStr;
    auto len = 0;
    ret = ret.remove(' ');  // 删除空格符，没有也无影响
    if(ret.length() % 2 == 0)
    {
        len = ret.length()/2;
    }
    else if(ret.length() % 2 == 1)
    {   // 处理字符串长度为奇数
        len = ret.length() / 2 + 1;
    }
    for(auto i = 1; i < len; i++)
    {
       ret.insert(3*i - 1, " ");
    }

    return ret.toUpper();
}

/*********************************************************************************
** 函数名称：       ByteArrayToHexString
** 函数描述：       QByteArray转十六进制字符串
** 函数输入参数：    baData：字节数组
** 函数输出参数：    无
** 函数返回值：      十六进制字符串，以空格分隔字节，如“12 AD FF 4E”
** 作者：           zjk
** 日期：          ‎2020‎年‎3‎月9‎日 21:28
**********************************************************************************/
QString TypeConvert::ByteArrayToHexString(QByteArray baData)
{
    QString ret(baData.toHex().toUpper());
    int len = ret.length()/2;
    for(auto i = 1; i < len; i++)
    {
        ret.insert(3*i-1, " ");
    }

    return ret;
}

// 整数转换为十六进制字符串，缺省高字节在前、低字节在后 zjk--20210415
const QString TypeConvert::DecToHexString(quint32 dec, quint16 len, const bool isLittleEndian)
{
    QString ret = ""; //  替换字符串
    quint8 hexArray[len];
    DecToHex(dec, hexArray, len);
    QByteArray ba = QByteArray((char*)hexArray, len);
    if(isLittleEndian)
    {   // 小端模式，需要高低字节转换
        char ch = ' ';
        for (auto i = 0; i < ba.size()/2; i++)
        {
            ch = ba.at(i);
            ba[i] = ba.at(ba.size()-i-1);
            ba[ba.size()-i-1] = ch;
        }
    }
    ret = ByteArrayToHexString(ba);

    return ret;
}

/*********************************************************************************
** 函数名称：       DecToHex
** 函数描述：       十进制转十六进制
** 函数输入参数：    dec：待转换的十进制数据，quint8 *hex：转换后存放十六进制数据的指针地址，len：十进制数据长度。
** 约束：调用该函数时，需保证len与dec所有的数值范围对应，即0～65535对应len=2字节；65536～4294967295对应len=4字节。
** 设计：数据在计算机中按照字节（八位）存储，十六进制数的每个字符（八位）所表示的十进制数的范围是
**      0～255，进制为256，即2的8次方。十进制转十六进制，相当于右移8位，即除以256，用取模%运算
** 函数输出参数：    quint8 *hex：转换后存放十六进制数据的指针地址，修改的是指针所指向的地址的内容，且按字节修改，之后按qint32（即4字节）读取即可
** 函数返回值：      无
** 作者：           zjk
** 日期：          ‎2020‎年‎3‎月12‎日 8:17
**********************************************************************************/
void TypeConvert::DecToHex(int dec, quint8 *hex, int len)
{
    qint32 i;
    for(i = len - 1; i >= 0; i--)
    {
        hex[i] = (dec % 256) & 0xFF; // 传递的是quint8*，修改的是指针所指向的地址的内容，且按字节修改，之后按qint32（即4字节）读取即可
        dec /= 256;
    }
}
