/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTextEdit *inputName;
    QPushButton *loginButton;
    QLabel *errorLabel;
    QLabel *profileLabel;
    QTableWidget *friendsTable;
    QLabel *postsLabel;
    QPushButton *backButton;
    QTableWidget *suggestTable;
    QPushButton *addPostButton;
    QPushButton *addFriendButton;
    QTextEdit *enterPost;
    QPushButton *addPost;
    QLabel *notFriendLabel;
    QPushButton *settingsButton;
    QComboBox *profilePrivacy;
    QComboBox *postsPrivacy;
    QComboBox *commentPrivacy;
    QLabel *profilePrivacyLabel;
    QLabel *postsPrivacyLabel;
    QLabel *commentPrivacyLabel;
    QPushButton *settingsSaveButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        inputName = new QTextEdit(centralwidget);
        inputName->setObjectName("inputName");
        inputName->setGeometry(QRect(250, 90, 151, 31));
        loginButton = new QPushButton(centralwidget);
        loginButton->setObjectName("loginButton");
        loginButton->setGeometry(QRect(270, 160, 101, 32));
        errorLabel = new QLabel(centralwidget);
        errorLabel->setObjectName("errorLabel");
        errorLabel->setGeometry(QRect(250, 130, 151, 16));
        profileLabel = new QLabel(centralwidget);
        profileLabel->setObjectName("profileLabel");
        profileLabel->setGeometry(QRect(200, 20, 261, 41));
        friendsTable = new QTableWidget(centralwidget);
        friendsTable->setObjectName("friendsTable");
        friendsTable->setGeometry(QRect(20, 60, 256, 192));
        postsLabel = new QLabel(centralwidget);
        postsLabel->setObjectName("postsLabel");
        postsLabel->setGeometry(QRect(440, 70, 251, 271));
        backButton = new QPushButton(centralwidget);
        backButton->setObjectName("backButton");
        backButton->setGeometry(QRect(510, 10, 111, 32));
        suggestTable = new QTableWidget(centralwidget);
        suggestTable->setObjectName("suggestTable");
        suggestTable->setGeometry(QRect(20, 320, 256, 192));
        addPostButton = new QPushButton(centralwidget);
        addPostButton->setObjectName("addPostButton");
        addPostButton->setGeometry(QRect(390, 10, 101, 32));
        addFriendButton = new QPushButton(centralwidget);
        addFriendButton->setObjectName("addFriendButton");
        addFriendButton->setGeometry(QRect(20, 10, 101, 32));
        enterPost = new QTextEdit(centralwidget);
        enterPost->setObjectName("enterPost");
        enterPost->setGeometry(QRect(420, 380, 301, 101));
        addPost = new QPushButton(centralwidget);
        addPost->setObjectName("addPost");
        addPost->setGeometry(QRect(520, 500, 101, 32));
        notFriendLabel = new QLabel(centralwidget);
        notFriendLabel->setObjectName("notFriendLabel");
        notFriendLabel->setGeometry(QRect(50, 270, 201, 16));
        settingsButton = new QPushButton(centralwidget);
        settingsButton->setObjectName("settingsButton");
        settingsButton->setGeometry(QRect(640, 10, 101, 32));
        profilePrivacy = new QComboBox(centralwidget);
        profilePrivacy->addItem(QString());
        profilePrivacy->addItem(QString());
        profilePrivacy->addItem(QString());
        profilePrivacy->setObjectName("profilePrivacy");
        profilePrivacy->setGeometry(QRect(320, 210, 103, 32));
        postsPrivacy = new QComboBox(centralwidget);
        postsPrivacy->addItem(QString());
        postsPrivacy->addItem(QString());
        postsPrivacy->addItem(QString());
        postsPrivacy->setObjectName("postsPrivacy");
        postsPrivacy->setGeometry(QRect(320, 270, 103, 32));
        commentPrivacy = new QComboBox(centralwidget);
        commentPrivacy->addItem(QString());
        commentPrivacy->addItem(QString());
        commentPrivacy->addItem(QString());
        commentPrivacy->setObjectName("commentPrivacy");
        commentPrivacy->setGeometry(QRect(320, 330, 103, 32));
        profilePrivacyLabel = new QLabel(centralwidget);
        profilePrivacyLabel->setObjectName("profilePrivacyLabel");
        profilePrivacyLabel->setGeometry(QRect(210, 210, 101, 16));
        postsPrivacyLabel = new QLabel(centralwidget);
        postsPrivacyLabel->setObjectName("postsPrivacyLabel");
        postsPrivacyLabel->setGeometry(QRect(210, 270, 111, 16));
        commentPrivacyLabel = new QLabel(centralwidget);
        commentPrivacyLabel->setObjectName("commentPrivacyLabel");
        commentPrivacyLabel->setGeometry(QRect(180, 330, 131, 16));
        settingsSaveButton = new QPushButton(centralwidget);
        settingsSaveButton->setObjectName("settingsSaveButton");
        settingsSaveButton->setGeometry(QRect(320, 420, 101, 32));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 24));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        inputName->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'.AppleSystemUIFont'; font-size:13pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        loginButton->setText(QCoreApplication::translate("MainWindow", "Login", nullptr));
        errorLabel->setText(QCoreApplication::translate("MainWindow", "No such user. Try again", nullptr));
        profileLabel->setText(QCoreApplication::translate("MainWindow", "nameLabel", nullptr));
        postsLabel->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        backButton->setText(QCoreApplication::translate("MainWindow", "Back to Profile", nullptr));
        addPostButton->setText(QCoreApplication::translate("MainWindow", "Add Post", nullptr));
        addFriendButton->setText(QCoreApplication::translate("MainWindow", "Add Friend", nullptr));
        addPost->setText(QCoreApplication::translate("MainWindow", "Add", nullptr));
        notFriendLabel->setText(QCoreApplication::translate("MainWindow", "Become a friend to view friends", nullptr));
        settingsButton->setText(QCoreApplication::translate("MainWindow", "Settings", nullptr));
        profilePrivacy->setItemText(0, QCoreApplication::translate("MainWindow", "Private", nullptr));
        profilePrivacy->setItemText(1, QCoreApplication::translate("MainWindow", "Semi-private", nullptr));
        profilePrivacy->setItemText(2, QCoreApplication::translate("MainWindow", "Public", nullptr));

        postsPrivacy->setItemText(0, QCoreApplication::translate("MainWindow", "Private", nullptr));
        postsPrivacy->setItemText(1, QCoreApplication::translate("MainWindow", "Semi-private", nullptr));
        postsPrivacy->setItemText(2, QCoreApplication::translate("MainWindow", "Public", nullptr));

        commentPrivacy->setItemText(0, QCoreApplication::translate("MainWindow", "Private", nullptr));
        commentPrivacy->setItemText(1, QCoreApplication::translate("MainWindow", "Semi-private", nullptr));
        commentPrivacy->setItemText(2, QCoreApplication::translate("MainWindow", "Public", nullptr));

        profilePrivacyLabel->setText(QCoreApplication::translate("MainWindow", "Profile Privacy:", nullptr));
        postsPrivacyLabel->setText(QCoreApplication::translate("MainWindow", "Posts Privacy:", nullptr));
        commentPrivacyLabel->setText(QCoreApplication::translate("MainWindow", "Comments Privacy:", nullptr));
        settingsSaveButton->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
