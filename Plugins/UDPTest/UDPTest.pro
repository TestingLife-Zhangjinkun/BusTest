QT += widgets axcontainer

TEMPLATE = lib
DEFINES += UDPTEST_LIBRARY

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#包含接口文件路径
INCLUDEPATH    += ../../framework
#指定编译生成的dll文件目录
DESTDIR     = ../Plugin

SOURCES += \
    datacheckform.cpp \
    numberconvertform.cpp \
    typeconvert.cpp \
    udpform.cpp \
    udptest.cpp \
    unicastform.cpp

HEADERS += \
    UDPTest_global.h \
    datacheckform.h \
    numberconvertform.h \
    typeconvert.h \
    udpform.h \
    udptest.h \
    unicastform.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

FORMS += \
    datacheckform.ui \
    numberconvertform.ui \
    udpform.ui \
    unicastform.ui
