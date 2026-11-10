#include "ui/MainWindow.h"
#include <QApplication>
#include <QFile>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    app.setApplicationName("SPIDE Studio");
    app.setOrganizationName("SPIDE");
    app.setApplicationVersion("0.1.0");

    QFile themeFile(":/styles/dark_theme.qss");
    if (themeFile.open(QFile::ReadOnly | QFile::Text)) {
        app.setStyleSheet(QString::fromUtf8(themeFile.readAll()));
        themeFile.close();
    }

    Spide::UI::MainWindow window;
    window.show();

    return app.exec();
}
