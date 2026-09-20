#include "MainWindow.h"

#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QApplication::setApplicationName("SPIDE Studio");
    QApplication::setApplicationVersion("0.1.0");
    QApplication::setOrganizationName("SPIDE");
    QApplication::setStyle(QStyleFactory::create("Fusion"));

    MainWindow window;
    window.show();
    return app.exec();
}