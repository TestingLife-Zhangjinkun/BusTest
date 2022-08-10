#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include "BusTestInterface.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // "Pin to top" button slot function
    void TopMost_Clicked();
    // "About" button slot function
    void About_Clicked();
    // Toolbar trigger slot function
    void actionTriggered(QAction *action);

private:
    // Use JSON file to configure global parameters
    void InitGlobalParams();
    // Load plugin
    quint8 LoadPlugins();
    void AddToolBar(BusTestInterface* ti);


    Ui::MainWindow *ui;
    // Grid layout manager, interface plugin widget occupies 4 rows and 1 column,
    // statistics widget occupies 1 row and 1 column
    QGridLayout* gridLayout = nullptr;
    // The button that the app always displays at the top.
    QPushButton *topMost = nullptr;
    // Top flag, default false
    bool isTopMost = false;
    // Number of UDP unicast communication forms
    quint16 udpUnicastTabNum = 1;
    // Bus Test Interface List
    QList<BusTestInterface*> tiList;
    // Record the currently displayed test plugin
    BusTestInterface* curTi = nullptr;

};
#endif // MAINWINDOW_H
