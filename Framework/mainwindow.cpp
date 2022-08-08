#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    gridLayout = new QGridLayout();
    // Set the left, top, right and bottom margins
    gridLayout->setContentsMargins(5, 5, 5, 5);
    ui->centralwidget->setLayout(gridLayout);

    gridLayout->addWidget(ui->label, 0, 0, 5, 1);
    ui->label->setText("Welcome to the Bus Interface Test Tool!");
    ui->label->setAlignment(Qt::AlignCenter);
    ui->label->setFrameStyle(QFrame::Box);

}

MainWindow::~MainWindow()
{
    delete ui;
}

