#include "widget.h"
#include <QApplication>
#include <QListWidget>
#include <QListWidgetItem>
#include <QString>
#include <QDir>
#include <QFile>
#include <QStringList>
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    return a.exec();
}
