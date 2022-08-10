#include "udptest.h"

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
    return QIcon();
}

QWidget *UDPTest::PluginWidget()
{
    return this;
}

QString UDPTest::PluginTooltip()
{
    return "";
}

void UDPTest::SetTabNum(quint16)
{

}
