#ifndef UDPFORM_H
#define UDPFORM_H

#include <QWidget>

namespace Ui {
class UDPForm;
}

class UDPForm : public QWidget
{
    Q_OBJECT

public:
    explicit UDPForm(QWidget *parent = nullptr);
    ~UDPForm();

private:
    Ui::UDPForm *ui;
};

#endif // UDPFORM_H
