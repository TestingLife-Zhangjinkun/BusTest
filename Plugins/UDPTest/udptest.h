#ifndef UDPTEST_H
#define UDPTEST_H

#include "UDPTest_global.h"
#include <QWidget>
#include <BusTestInterface.h>
#include "ui_udpform.h"
#include "unicastform.h"

class UDPTEST_EXPORT UDPTest
        :public QWidget
        ,public BusTestInterface
{
    Q_OBJECT
    // Metadata describing test plugins
    Q_PLUGIN_METADATA(IID BusTestInterface_iid)
    // Tell Qt which interface the class implements
    Q_INTERFACES(BusTestInterface);

public:
    UDPTest(QWidget* parent = Q_NULLPTR);

    virtual QString PluginName() override;
    virtual QIcon PluginIcon() override;
    virtual QWidget* PluginWidget() override;
    virtual QString PluginTooltip() override;
    virtual void SetTabNum(quint16) override;

private:
    // Initialize UDP widget
    void InitUDPWidget();

    // Manually associate UI
    Ui::UDPForm* ui;
    // The number of unicast communication forms
    quint16 unicastFormNum = 1;
    // Unicast Communication Form
    UnicastForm *unicastForm = nullptr;


};

#endif // UDPTEST_H
