#include "mainwindow.h"
#include "network.h"
#include <QDir>
#include <QDebug>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QString pathUser = QCoreApplication::applicationDirPath() + "/../../../users.txt";
    //QString pathPost = QCoreApplication::applicationDirPath() + "/../../../posts.txt";
    Network network;
    network.readUsers("users.txt");
    network.readPosts("posts.txt");
    //qDebug() << QDir::currentPath();
    MainWindow w(&network);
    w.show();
    return a.exec();
}
