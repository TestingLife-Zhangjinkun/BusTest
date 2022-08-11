#ifndef UNICASTFORM_H
#define UNICASTFORM_H

#include <QWidget>

namespace Ui {
class UnicastForm;
}

class UnicastForm : public QWidget
{
    Q_OBJECT

public:
    explicit UnicastForm(QWidget *parent = nullptr);
    ~UnicastForm();

private:
    Ui::UnicastForm *ui;
};

#endif // UNICASTFORM_H
