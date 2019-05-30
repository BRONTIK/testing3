#include "widget.h"
#include "ui_widget.h"
#include <QString>
#include <QStringList>
#include <QFile>
#include <QDir>
#include <QFileDialog>
#include <QTextStream>
#include <iostream>
#include <QListWidget>
#include <QListWidgetItem>
#include <QMenuBar>
#include <QAction>
#include <cstring>
#include <fstream>
#include <QListWidgetItem>
#include <QFrame>

using namespace std;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    comboBox_filling();

    list_filling("");

    //ui->lineEdit->setText("co");
}

Widget::~Widget()
{
    delete ui;
}

void Widget::comboBox_filling()
{
    QFile file("C:/Users/123456/Desktop/untitled/dataBase/cI2.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);

    while (!in.atEnd()) {
        QString line = in.readLine();
        ui->comboBox->addItem(line);
    }

    file.close();
}

void Widget::textBrowser_filling(QString name)
{


    QDir dir("C:/Users/123456/Desktop/untitled/img");
    QFile file("C:/Users/123456/Desktop/untitled/dataBase/fff_1.txt");
    QFile file2("C:/Users/123456/Desktop/untitled/dataBase/compositions/" + name + ".txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QFileInfoList list = dir.entryInfoList();
    for (int i = 0; i < list.size(); ++i)
    {
        QFileInfo fileInfo = list.at(i);

        if (fileInfo.baseName() == name)
            ui->textBrowser->setHtml(
                QString("<img src=\"")
                + fileInfo.filePath()
                + "\" width=\"700\""
                + " height=\"400\">"
            );
    }

    ui->textBrowser->setStyleSheet
           (
            "font-family: Arial;"
            "font-size: 15px;"
            "font-style: italic;"
            "font-weight: 100;"
                );

    /* Счётчик пробелов */
    int spaces_counter = 0;

    /* Выбранная категория */
    QString item;

    QTextStream in(&file);

    while (!in.atEnd()) {
        QString line = in.readLine();

        if (line == "")
            spaces_counter++;

        if (spaces_counter%3 == 1 && line != "")
            item = line;

        if (spaces_counter%3 == 2 && line != "" && item == name)
            ui->textBrowser->append(line[0].toUpper()
                    + line.mid(1, line.size () - 1));

    }
       file.close();

    ui->textBrowser->append("");

    if (file2.open(QIODevice::ReadOnly | QIODevice::Text)) {

    QTextStream in2(&file2);

    while (!in2.atEnd()) {
        QString line = in2.readLine();

//        if(line == "Состав:" || line == "Приготовление:") {
//                        ui->textBrowser->setStyleSheet("font-weight: 900;");
//                        ui->textBrowser->append(line);
//                        ui->textBrowser->setStyleSheet("");
//        }
//        else
            ui->textBrowser->append(line);
    }

    file2.close();
    }

}

void Widget::list_filling(const QString &substring)
{
    //ui->lineEdit->setText("Поиск");
    QFile file("C:/Users/123456/Desktop/untitled/dataBase/fff_1.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QListWidgetItem item_list;

    /* Счётчик пробелов */
    int spaces_counter = 0;

    /* Выбранная категория */
    QString category;

    QTextStream in(&file);
    //QTextStream out(&file2);

    while (!in.atEnd()) {
        QString line = in.readLine();

        if (line == "")
            spaces_counter++;

        if (spaces_counter%3 == 0 && line != "")
            category = line;

        if (spaces_counter%3 == 1 && line != "" && category == ui->comboBox->currentText()){
            if (substring == ""){
                ui->List->addItem(line [0].toUpper()
                        + line.mid(1, line.size () - 1).toLower ());
            }
            else {
                if (line.toUpper().startsWith(substring.toUpper()))
                    ui->List->addItem(line [0].toUpper()
                            + line.mid(1, line.size () - 1).toLower ());
            }
        }
    }

    file.close();

}


void Widget::on_comboBox_activated()
{
    ui->List->clear();
    list_filling(ui->lineEdit->text());
}

void Widget::on_lineEdit_textChanged(const QString &arg1)
{
    ui->List->clear();
    list_filling(arg1);
}

void Widget::on_List_itemActivated(QListWidgetItem *item)
{
    ui->textBrowser->clear();
    ui->textBrowser->setStyleSheet("");

    if (ui->comboBox->currentText() == "Cocktails")
        textBrowser_filling(item->text().toUpper());
    else
        textBrowser_filling(item->text());
}

/*void Widget::on_lineEdit_selectionChanged()
{
    ui->lineEdit->clear();
}*/
