#ifndef UDPTEST_H
#define UDPTEST_H

#include "UDPTest_global.h"
#include <QWidget>
#include <BusTestInterface.h>

class UDPTEST_EXPORT UDPTest
        :public QWidget
        ,public BusTestInterface
{
public:
    UDPTest();
};

#endif // UDPTEST_H
