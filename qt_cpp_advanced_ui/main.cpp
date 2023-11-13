#include "mainwindow.h"

#include <QApplication>
#include "settings.h"

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    MainWindow w;
    w.resize(Settings::kWindowWidth, Settings::kWindowHeight);
    w.show();

    return a.exec();
}
