#ifndef NUMBERCONVERTFORM_H
#define NUMBERCONVERTFORM_H

#include <QWidget>

namespace Ui {
class NumberConvertForm;
}

class NumberConvertForm : public QWidget
{
    Q_OBJECT

public:
    explicit NumberConvertForm(QWidget *parent = nullptr);
    ~NumberConvertForm();

private slots:
    void on_pushButton_ShowCRCParams_clicked();

private:
    Ui::NumberConvertForm *ui;
};

#endif // NUMBERCONVERTFORM_H
