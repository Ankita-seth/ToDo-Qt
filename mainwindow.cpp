#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QStandardPaths>
#include <QMessageBox>
#include <QTime>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QFile file(Path);
    qDebug() << QTime::currentTime().toString() << "Main window called"<< file.fileName();
    if(!file.open(QIODevice::ReadWrite))
    {
        QMessageBox::information(0, "error", file.errorString());
    }

    QTextStream in(&file);

    while(!in.atEnd())
    {
        QListWidgetItem* item = new QListWidgetItem(in.readLine(), ui->listWidget);
        ui->listWidget->addItem(item);
        item->setFlags(item->flags() | Qt::ItemIsEditable);
    }

    file.close();
}

MainWindow::~MainWindow()
{
    delete ui;

    QFile file(Path);

    if(!file.open(QIODevice::ReadWrite))
    {
        QMessageBox::information(0, "error", file.errorString());
    }

    QTextStream out(&file);

    for(int i = 0; i <ui->listWidget->count() ; ++i)
    {
        out <<ui->listWidget->item(i)->text()<<"\n";
    }

    file.close();
}


void MainWindow::on_btnAdd_clicked()
{
    QListWidgetItem *item = new QListWidgetItem(ui->txtTask->text(),ui->listWidget);
    ui->listWidget->addItem(item);
    item->setFlags(item->flags() | Qt::ItemIsEditable);

    ui->txtTask->clear();
    ui->txtTask->setFocus();
}


void MainWindow::on_btnRemove_clicked()
{
    QListWidgetItem* item = ui->listWidget->takeItem(ui->listWidget->currentRow());


    delete item;
}


void MainWindow::on_btnRemoveAll_clicked()
{
    ui->listWidget->clear();
}

