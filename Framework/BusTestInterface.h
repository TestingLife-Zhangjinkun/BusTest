#ifndef BUSTESTINTERFACE_H
#define BUSTESTINTERFACE_H

#include <QString>
#include <QWidget>
#include <QIcon>

// define interface
class BusTestInterface
{
public:
    // plugin name
    virtual QString PluginName() = 0;
    // plugin icon
    virtual QIcon PluginIcon() = 0;
    // Plugin Widget, one for each bus interface, and then use TabWidget to subdivide multiple forms
    virtual QWidget* PluginWidget() = 0;
    // plugin tooltip
    virtual QString PluginTooltip() = 0;
    // Set the number of forms
    virtual void SetTabNum(quint16) = 0;
};

// declare interface
#define BusTestInterface_iid "Com.Interface.BusTestInterface"
Q_DECLARE_INTERFACE(BusTestInterface, BusTestInterface_iid)

#endif // BUSTESTINTERFACE_H
