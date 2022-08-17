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

private:
    Ui::DataCheckForm *ui;
    // Variables for TypeConvert
    TypeConvert tcInstance = TypeConvert::getTCInstance();

};

#endif // DATACHECKFORM_H
