#ifndef DATACHECKFORM_H
#define DATACHECKFORM_H

#include <QWidget>
#include "typeconvert.h"

namespace Ui {
class DataCheckForm;
}

class DataCheckForm : public QWidget
{
    Q_OBJECT

public:

    enum CRC8_Mode
    {
        CRC8_ITU = 0,
        CRC8_ROHC,
        CRC8_MAXIM,
    };
    enum CRC16_Mode
    {
        CRC16_CCITT_True = 0,
        CRC16_CCITT_FALSE,
        CRC16_XMODEM,
        CRC16_X25,
        CRC16_MODBUS,
        CRC16_IBM,
        CRC16_MAXIM,
        Crc16_USB,
        CRC16_DNP,
    };
    enum CRC32_Mode
    {
        CRC32_WinRAR = 0,
        CRC32_MPEG
    };
    Q_ENUM(CRC8_Mode)
    Q_ENUM(CRC16_Mode)
    Q_ENUM(CRC32_Mode)

    explicit DataCheckForm(QWidget *parent = nullptr);
    ~DataCheckForm();

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

private:
    Ui::DataCheckForm *ui;
    // Variables for TypeConvert
    TypeConvert tcInstance = TypeConvert::getTCInstance();

};

#endif // DATACHECKFORM_H
