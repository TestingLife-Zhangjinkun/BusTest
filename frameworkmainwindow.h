#ifndef FRAMEWORKMAINWINDOW_H
#define FRAMEWORKMAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class FrameworkMainWindow; }
QT_END_NAMESPACE

class FrameworkMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    FrameworkMainWindow(QWidget *parent = nullptr);
    ~FrameworkMainWindow();

private:
    Ui::FrameworkMainWindow *ui;
};
#endif // FRAMEWORKMAINWINDOW_H
