#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "user.h"
#include "network.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Network* network_, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleLogin();
    void switchProfile(int row, int col);
    void back();
    void addSuggest(int row, int col);
    void addFriend();
    void addPost();
    void add();
    void settingsButton();
    void settingsSave();

private:
    Ui::MainWindow *ui;
    Network* network;
    User* user;
    User* display;
    int postPrivacy;
    int commentPrivacy;
};
#endif // MAINWINDOW_H
