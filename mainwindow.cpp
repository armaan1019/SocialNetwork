#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>
#include <QDebug>
#include <QDir>
#include <QSettings>

MainWindow::MainWindow(Network* network_, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), network(network_)
{
    ui->setupUi(this);

    QSettings settings("MyCompany", "SocialNetwork");
    postPrivacy = settings.value("postPrivacy", 2).toInt();
    commentPrivacy = settings.value("commentPrivacy", 2).toInt();

    ui->postsPrivacy->setCurrentIndex(postPrivacy);
    ui->commentPrivacy->setCurrentIndex(commentPrivacy);

    connect(ui->postsPrivacy, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=](int index) {
        postPrivacy = index;
        QSettings settings("MyCompany", "SocialNetwork");
        settings.setValue("postPrivacy", index);
    });

    connect(ui->commentPrivacy, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=](int index) {
        commentPrivacy = index;
        QSettings settings("MyCompany", "SocialNetwork");
        settings.setValue("commentPrivacy", index);
    });


    ui->errorLabel->hide();
    ui->profileLabel->hide();
    ui->friendsTable->hide();
    ui->postsLabel->hide();
    ui->backButton->hide();
    ui->addFriendButton->hide();
    ui->addPostButton->hide();
    ui->suggestTable->hide();
    ui->addPost->hide();
    ui->enterPost->hide();
    ui->notFriendLabel->hide();
    ui->settingsButton->hide();
    ui->profilePrivacy->hide();
    ui->profilePrivacyLabel->hide();
    ui->commentPrivacy->hide();
    ui->commentPrivacyLabel->hide();
    ui->postsPrivacy->hide();
    ui->postsPrivacyLabel->hide();
    ui->settingsSaveButton->hide();

    connect(ui->loginButton, &QPushButton::clicked, this, &MainWindow::handleLogin);
    connect(ui->friendsTable, &QTableWidget::cellClicked, this, &MainWindow::switchProfile);
    connect(ui->backButton, &QPushButton::clicked, this, &MainWindow::back);
    connect(ui->suggestTable, &QTableWidget::cellClicked, this, &MainWindow::addSuggest);
    connect(ui->addFriendButton, &QPushButton::clicked, this, &MainWindow::addFriend);
    connect(ui->addPostButton, &QPushButton::clicked, this, &MainWindow::addPost);
    connect(ui->addPost, &QPushButton::clicked, this, &MainWindow::add);
    connect(ui->settingsButton, &QPushButton::clicked, this, &MainWindow::settingsButton);
    connect(ui->settingsSaveButton, &QPushButton::clicked, this, &MainWindow::settingsSave);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleLogin() {
    QString name = ui->inputName->toPlainText();
    //qDebug() << network->numUsers();

    user = network->getUser(network->getId(name.toStdString()));
    if(user != nullptr) {
        ui->loginButton->hide();
        ui->inputName->hide();
        ui->errorLabel->hide();

        ui->profileLabel->setText("My Profile");
        ui->profileLabel->show();
        ui->addPostButton->show();
        ui->friendsTable->setColumnCount(1);
        int row = 0;
        ui->friendsTable->setRowCount(user->getFriends().size());
        ui->friendsTable->setHorizontalHeaderLabels(QStringList() << "Friends");
        for(auto friendId: user->getFriends()) {
            User* userf = network->getUser(friendId);
            QString friendName = QString::fromStdString(userf->getName());
            QTableWidgetItem *item = new QTableWidgetItem(friendName);

            ui->friendsTable->setItem(row, 0, item);
            row++;
        }
        ui->friendsTable->resizeColumnsToContents();
        ui->friendsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->friendsTable->show();

        int someScore = 2;
        int& score = someScore;
        std::vector<int> suggestions = network->suggestFriends(user->getId(), score);
        ui->suggestTable->setRowCount(suggestions.size());
        ui->suggestTable->setColumnCount(1);
        int suggestRow = 0;
        for(auto buddy: suggestions) {
            User* userSuggestion = network->getUser(buddy);
            QString friendName = QString::fromStdString(userSuggestion->getName());
            QTableWidgetItem *item = new QTableWidgetItem(friendName);

            ui->suggestTable->setItem(suggestRow, 0, item);
            suggestRow++;
        }
        ui->suggestTable->resizeColumnsToContents();
        ui->suggestTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->suggestTable->show();

        QString postsText = QString::fromStdString(user->getPostsString(5, false));
        ui->postsLabel->setText(postsText);
        ui->postsLabel->setWordWrap(true);
        ui->postsLabel->show();
        ui->settingsButton->show();
    } else {
        ui->errorLabel->show();
    }
}

void MainWindow::switchProfile(int row, int col) {
    ui->backButton->show();
    ui->suggestTable->hide();
    ui->addFriendButton->show();
    QTableWidgetItem *item = ui->friendsTable->item(row, col);
    if(!item) {
        return;
    }

    display = network->getUser(network->getId(item->text().toStdString()));
    int privacy = display->getPrivacy();
    bool isFriend = false;
    bool isfoff = false;
    for(int x: display->getFriends()) {
        if(user->getId() == x) {
            isFriend = true;
            break;
        }
    }
    if(!isFriend) {
        for(int x: display->getFriends()) {
            User* newUser = network->getUser(x);
            for(int y: newUser->getFriends()) {
                if(user->getId() == y) {
                    isfoff = true;
                }
            }
        }
    }
    QString profileString = QString::fromStdString(display->getName());

    ui->profileLabel->setText(profileString + "'s Profile");
    if(privacy == 2 || isFriend || (privacy == 1 && isfoff)) {
        ui->friendsTable->setRowCount(display->getFriends().size());
        int newRow = 0;
        for(auto buddy: display->getFriends()) {
            User* userFriend = network->getUser(buddy);
            QTableWidgetItem *item = new QTableWidgetItem(QString::fromStdString(userFriend->getName()));
            ui->friendsTable->setItem(newRow, 0, item);
            newRow++;
        }
    } else {
        ui->notFriendLabel->show();
        ui->friendsTable->hide();
    }

    QString postsText = QString::fromStdString(network->getPostsString(display->getId(), 5, user));
    ui->postsLabel->setText(postsText);
    ui->postsLabel->setWordWrap(true);
    ui->postsLabel->show();
}

void MainWindow::back() {
    //ui->friendsTable->setEnabled(true);
    ui->notFriendLabel->hide();
    MainWindow::handleLogin();
}

void MainWindow::addSuggest(int row, int col) {
    ui->backButton->show();
    ui->addFriendButton->show();
    ui->suggestTable->hide();
    QTableWidgetItem *item = ui->suggestTable->item(row, col);
    if(!item) {
        return;
    }

    display = network->getUser(network->getId(item->text().toStdString()));
    QString profileString = QString::fromStdString(display->getName());

    int privacy = display->getPrivacy();
    bool isFriend = false;
    bool isfoff = false;
    for(int x: display->getFriends()) {
        if(user->getId() == x) {
            isFriend = true;
            break;
        }
    }
    if(!isFriend) {
        for(int x: display->getFriends()) {
            User* newUser = network->getUser(x);
            for(int y: newUser->getFriends()) {
                if(user->getId() == y) {
                    isfoff = true;
                }
            }
        }
    }
    ui->profileLabel->setText(profileString + "'s Profile");
    if(privacy == 2 || isFriend || (privacy == 1 && isfoff)) {
        ui->friendsTable->setRowCount(display->getFriends().size());
        int newRow = 0;
        for(auto buddy: display->getFriends()) {
            User* userFriend = network->getUser(buddy);
            QTableWidgetItem *item = new QTableWidgetItem(QString::fromStdString(userFriend->getName()));
            ui->friendsTable->setItem(newRow, 0, item);
            newRow++;
        }
        //ui->friendsTable->setEnabled(false);
    } else {
        ui->notFriendLabel->show();
        ui->friendsTable->hide();
    }

    QString postsText = QString::fromStdString(network->getPostsString(display->getId(), 5, user));
    ui->postsLabel->setText(postsText);
    ui->postsLabel->setWordWrap(true);
    ui->postsLabel->show();
}

void MainWindow::addFriend() {
    QString text = ui->profileLabel->text();
    QStringList parts = text.split("'s Profile");
    QString userName = parts[0];
    display = network->getUser(network->getId(userName.toStdString()));
    QString mainUserName = ui->inputName->toPlainText();
    user = network->getUser(network->getId(mainUserName.toStdString()));

    //qDebug() << user->getName() << " " << mainUser->getName();
    //QString currentDir = QDir::currentPath();
    //qDebug() << "Current working directory:" << currentDir;

    network->addConnection(user->getName(), display->getName());
    ui->friendsTable->setRowCount(display->getFriends().size());
    int newRow = 0;
    for(auto buddy: display->getFriends()) {
        User* userFriend = network->getUser(buddy);
        QTableWidgetItem *item = new QTableWidgetItem(QString::fromStdString(userFriend->getName()));
        ui->friendsTable->setItem(newRow, 0, item);
        newRow++;
    }
    network->writeUsers("users2.txt");
}

void MainWindow::addPost() {
    ui->enterPost->show();
    ui->addPost->show();
}

void MainWindow::add() {
    QString text = ui->profileLabel->text();
    QStringList parts = text.split("'s Profile");
    if(parts.size() > 1) {
        QString userName = parts[0];
        display = network->getUser(network->getId(userName.toStdString()));
        QString post = ui->enterPost->toPlainText();
        int numPosts = 0;
        for(int i = 0; i < network->numUsers(); i++) {
            numPosts += network->getUser(i)->getPosts().size();
        }
        Post* p = new IncomingPost(numPosts, display->getId(), post.toStdString(), 0, commentPrivacy, user->getName());
        display->addPost(p);
        network->writePosts("posts2.txt");
        QString postsText = QString::fromStdString(display->getPostsString(5, false));
        ui->postsLabel->setText(postsText);
        ui->postsLabel->setWordWrap(true);
    } else {
        QString post = ui->enterPost->toPlainText();
        int numPosts = 0;
        for(int i = 0; i < network->numUsers(); i++) {
            numPosts += network->getUser(i)->getPosts().size();
        }
        Post* p = new Post(numPosts, user->getId(), post.toStdString(), 0, postPrivacy);
        user->addPost(p);
        network->writePosts("posts2.txt");
        QString postsText = QString::fromStdString(user->getPostsString(5, false));
        ui->postsLabel->setText(postsText);
        ui->postsLabel->setWordWrap(true);
    }

    ui->enterPost->clear();
    ui->addPost->hide();
    ui->enterPost->hide();
}

void MainWindow::settingsButton() {
    ui->profilePrivacy->setCurrentIndex(user->getPrivacy());
    ui->postsPrivacy->setCurrentIndex(postPrivacy);
    ui->commentPrivacy->setCurrentIndex(commentPrivacy);
    ui->settingsSaveButton->show();
    ui->friendsTable->hide();
    ui->suggestTable->hide();
    ui->postsLabel->hide();
    ui->addPostButton->hide();
    ui->profileLabel->setText("Your Settings");

    ui->profilePrivacy->show();
    ui->profilePrivacyLabel->show();
    ui->commentPrivacy->show();
    ui->commentPrivacyLabel->show();
    ui->postsPrivacy->show();
    ui->postsPrivacyLabel->show();
}

void MainWindow::settingsSave() {
    user->setPrivacy(ui->profilePrivacy->currentIndex());
    network->writeUsers("users2.txt");
    postPrivacy = ui->postsPrivacy->currentIndex();
    commentPrivacy = ui->commentPrivacy->currentIndex();

    ui->settingsSaveButton->hide();
    ui->profilePrivacy->hide();
    ui->profilePrivacyLabel->hide();
    ui->commentPrivacy->hide();
    ui->commentPrivacyLabel->hide();
    ui->postsPrivacy->hide();
    ui->postsPrivacyLabel->hide();

    MainWindow::back();
}
