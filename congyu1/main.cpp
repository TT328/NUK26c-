#include <QApplication>
#include <QResource>
#include <QDir>
#include <QDebug>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Q_INIT_RESOURCE(resources);

    qDebug() << "root =" << QDir(":/").entryList(QDir::AllEntries);
    qDebug() << "res =" << QDir(":/res").entryList(QDir::AllEntries);
    qDebug() << "cards =" << QDir(":/res/cards").entryList(QDir::AllEntries);

    MainWindow w;
    w.show();

    return a.exec();
}
