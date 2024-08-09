#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setWindowIcon(QIcon(":/resources/art/chessAppLogo.ico"));

    MainWindow w;

    w.setWindowTitle("Ethan's Incredible Chess App");
    w.resize(600, 400);
    w.show();
    return a.exec();
}
