#include "numberconvertform.h"
#include "ui_numberconvertform.h"
#include <QFile>
#include <QDebug>
#include <QAxObject>
#include <QDir>
#include <QScrollBar>

NumberConvertForm::NumberConvertForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NumberConvertForm)
{
    ui->setupUi(this);

//    ui->tableWidget->clear();
//    // 只设置列数，行数动态增加
//    ui->tableWidget->setColumnCount(6);
    // 设置整行选中的方式
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    // 设置不可编辑
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    // 设置可以选中单行
    ui->tableWidget->setSelectionMode(QAbstractItemView::/*ExtendedSelection*/SingleSelection);
    //设置无边框
//    ui->tableWidget->setFrameShape(QFrame::NoFrame);
    //设置不显示格子线
//    ui->tableWidget->setShowGrid(false);
    //设置行号列,true为显示
//    ui->tableWidget->verticalHeader()->setVisible(false);
    // 设置表头高度
    ui->tableWidget->horizontalHeader()->setFixedHeight(30);
    // 设置选中行背景色
//    ui->tableWidget->setStyleSheet("selection-background-color:blue");
    // 设置表头 背景色
//    ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:red;}");

    //设置水平、垂直滚动条样式,添加头文件 #include <QScrollBar>
    ui->tableWidget->horizontalScrollBar()->setStyleSheet("QScrollBar{background:transparent; height:10px;}"
                                                          "QScrollBar::handle{background:lightgray;"
                                                          "border:2px solid transparent; border-radius:5px;}"
                                                          "QScrollBar::handle:hover{background:gray;}"
                                                          "QScrollBar::sub-line{background:transparent;}"
                                                          "QScrollBar::add-line{background:transparent;}");
    ui->tableWidget->verticalScrollBar()->setStyleSheet("QScrollBar{background:transparent; width: 10px;}"
                                                        "QScrollBar::handle{background:lightgray;"
                                                        "border:2px solid transparent; border-radius:5px;}"
                                                        "QScrollBar::handle:hover{background:gray;}"
                                                        "QScrollBar::sub-line{background:transparent;}"
                                                        "QScrollBar::add-line{background:transparent;}");


}

NumberConvertForm::~NumberConvertForm()
{
    delete ui;
}

// 显示CRC校验算法参数配置列表 20221103
void NumberConvertForm::on_pushButton_ShowCRCParams_clicked()
{
    QString fileName = tr("%1/config/data/CRC.xlsx").arg(QDir::currentPath());
    QFile file(fileName);
    if(!file.exists())
    {
        qInfo().noquote() << fileName << "文件不存在！";
        return;
    }

    // Excel应用程序
    QAxObject *excel = new QAxObject("Excel.Application");
    // true：操作文件时可见，false：操作文件时不可见
    excel->dynamicCall("SetVisible(bool)", false);
    // 所有Excel文件
    QAxObject *workBooks = excel->querySubObject("WorkBooks");
    // 按照路径获取文件
    QAxObject *workBook = workBooks->querySubObject("Open(QString&）", fileName);
    // 获取文件的所有Sheet页
    QAxObject *sheets = workBook->querySubObject("WorkSheets");
    // 获取文件Sheet页
    QAxObject *sheet = sheets->querySubObject("Item(QString)", "CRC16");
    if(nullptr == sheet)
    {
        qInfo().noquote() << "校验配置Sheet页不存在";
        return;
    }
    // 有数据的矩形区域
    QAxObject *usedRange = sheet->querySubObject("UsedRange");

    // 获取行数
    QAxObject *rows = usedRange->querySubObject("Rows");
    int nRows = rows->property("Count").toUInt();
    if(nRows <= 1)
    {
        qInfo() << "无数据，跳过该文件！";
        return;
    }

    // 获取列数
    QAxObject *columns = usedRange->querySubObject("Columns");
    int nColumns = columns->property("Count").toUInt();

    // 获取所有数据
    QVector<QVector<QString>> vecDatas;

    ui->tableWidget->clear();
    // 调整内容大小
//    ui->tableWidget->resizeRowsToContents();
    // 标题头的大小
    ui->tableWidget->horizontalHeader()->setDefaultSectionSize(200);
    // 横向先自适应宽度
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    //设置标题头的字体样式
    QFont font = ui->tableWidget->horizontalHeader()->font();
    font.setBold(true);
    ui->tableWidget->horizontalHeader()->setFont(font);
    //设置充满表宽度
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    //设置行距
//    ui->tableWidget->verticalHeader()->setDefaultSectionSize(10);

    // 只设置列数，行数动态增加
    ui->tableWidget->setColumnCount(nColumns-1);
    quint16 rowNo = 0;
    QVariant var = usedRange->dynamicCall("Value");
    bool headerFlag = true;
    foreach(QVariant varRow, var.toList())
    {
        QVector<QString> vecDataRow;
        quint16 columnNo = 0;

        QStringList header;
        // 设置表头标识
        foreach(QVariant var, varRow.toList())
        {
            // 读取文件首行作为表头
            if(headerFlag)
            {
                //设置标题头的文字
                if(header.size() < 6)
                {
                    header<< var.toString();
                    continue;
                }
                else
                {
                    ui->tableWidget->setHorizontalHeaderLabels(header);
                    headerFlag = false;
                    break;
                }
            }
            else
            { // 从第2行开始插入表格内容
                // 处理行首元素时插入新行
                if(columnNo == 0)
                    ui->tableWidget->insertRow(rowNo);
                ui->tableWidget->setItem(rowNo, columnNo, new QTableWidgetItem(var.toString()));
                if(columnNo > 0)
                    //内容水平垂直居中 Note:要先设置内容，该属性才有效
                    ui->tableWidget->item(rowNo, columnNo)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
                ++columnNo;
                vecDataRow.push_back(var.toString());
                if(vecDataRow.size() == 6)
                { // 当前行处理完毕，行号+1
                    ++rowNo;
                    break;
                }
            }
        }
        vecDatas.push_back(vecDataRow);
    }
    // 然后设置要根据内容适应宽度的列。Note：需要在表格添加内容之后再设置
//    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    //清除表格数据区的内容，但不清除表头
//    ui->tableWidget->clearContents();

    // 关闭文件
    workBook->dynamicCall("Close()");
    excel->dynamicCall("Quit()");
    if(excel)
    {
        delete excel;
        excel = nullptr;
    }
}
















