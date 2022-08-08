#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    // Grid layout manager, interface plugin widget occupies 4 rows and 1 column,
    // statistics widget occupies 1 row and 1 column
    QGridLayout* gridLayout = nullptr;

};
#endif // MAINWINDOW_H
