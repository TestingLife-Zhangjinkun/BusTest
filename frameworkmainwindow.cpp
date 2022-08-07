#include "frameworkmainwindow.h"
#include "ui_frameworkmainwindow.h"

FrameworkMainWindow::FrameworkMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FrameworkMainWindow)
{
    ui->setupUi(this);
}

FrameworkMainWindow::~FrameworkMainWindow()
{
    delete ui;
}

