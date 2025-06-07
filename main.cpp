#include "mainwindow.h"
#include "network.h"
#include <QDir>
#include <QDebug>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QString pathUser = QCoreApplication::applicationDirPath() + "/../../../users.txt";
    //QString pathPost = QCoreApplication::applicationDirPath() + "/../../../posts2.txt";
    Network network;
    network.readUsers("users2.txt");
    network.readPosts("posts2.txt");
    qDebug() << QDir::currentPath();
    MainWindow w(&network);
    w.show();
    return a.exec();
}
