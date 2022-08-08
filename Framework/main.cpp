#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    // Adaptive Processing Approaches for High Resolution Displays。
#if (QT_VERSION > QT_VERSION_CHECK(5, 6, 0))
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#endif

    QApplication a(argc, argv);
    MainWindow w;
    // set title name
    w.setWindowTitle("Bus Interface Test Tool");

    w.show();
    return a.exec();
}
