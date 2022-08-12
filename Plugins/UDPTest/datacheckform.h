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

private:
    Ui::DataCheckForm *ui;
    // Variables for TypeConvert
    TypeConvert tcInstance = TypeConvert::getTCInstance();

};

#endif // DATACHECKFORM_H
