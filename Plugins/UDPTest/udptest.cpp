#include "udptest.h"
#include <QTabBar>

UDPTest::UDPTest(QWidget *parent)
    :QWidget(parent)
    , ui(new Ui::UDPForm)
{
    ui->setupUi(this);
}

QString UDPTest::PluginName()
{
    return "UDP";
}

QIcon UDPTest::PluginIcon()
{
    // Note: When using the plugin, the current directory is the directory where the framework is located.
    return QIcon(QPixmap("res/png/UDPPlugin/title.png"));
}

QWidget *UDPTest::PluginWidget()
{
    return this;
}

QString UDPTest::PluginTooltip()
{
    return "UDP interface plugin";
}

void UDPTest::SetTabNum(quint16 num)
{
    unicastFormNum = num;
    InitUDPWidget();
}

void UDPTest::InitUDPWidget()
{
    ui->tabWidget->clear();

    // The number of unicast communication forms, up to 4 are displayed.
    if(unicastFormNum > 1)
    {
        if(unicastFormNum > 4)
            unicastFormNum = 4;
        for (auto i = 1; i <= unicastFormNum; i++)
        {
            ui->tabWidget->addTab(new UnicastForm(), QIcon("res/png/UDPPlugin/unicast.jpg")
                              , "Unicast " + QString::number(i));
        }
    }
    else
        ui->tabWidget->addTab(new UnicastForm(), QIcon("res/png/UDPPlugin/unicast.jpg"), "Unicast");
//    ui->tabWidget->addTab(new MulticastForm(), QIcon(QPixmap("../Plugins/UDPTest/res/png/multicast.jpeg")), "组播和广播通信");
//    ui->tabWidget->addTab(new FileSendForm(), QIcon(QPixmap("../Plugins/UDPTest/res/png/DataSend.jpg")), "文件发送");
    ui->tabWidget->addTab(new DataCheckForm(), QIcon(QPixmap("res/png/UDPPlugin/DataSend.jpg")), "Data Check");

    ui->tabWidget->tabBar()->setDocumentMode(true);
    ui->tabWidget->tabBar()->setExpanding(true);

    // Displays the unicast communication form by default
    ui->tabWidget->setCurrentIndex(0);
}
