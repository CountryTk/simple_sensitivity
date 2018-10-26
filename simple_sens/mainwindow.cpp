#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <unistd.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {

    ui->setupUi(this);
    ui->lineEdit->setReadOnly(true);
    ui->lineEdit->setText("0");

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_horizontalSlider_sliderMoved(int position) {

    ui->lineEdit->setText(QString::number((position + 1) * 2));
}


void MainWindow::on_pushButton_2_clicked() {

    qApp->exit();
}

void MainWindow::on_pushButton_clicked() {

    QString value = ui->lineEdit->text();

    if (value != "0") {
        QString command = "pkexec su && echo '" + value + "'" + " > /sys/devices/platform/i8042/serio1/serio2/sensitivity";
        qDebug() << command;
        QByteArray ba = command.toLocal8Bit();
        const char *c_str2 = ba.data();
        write_changes(c_str2);

    }  else {
        qDebug() << "Please select a value";

    }
}

void MainWindow::write_changes(const char *command) {

    int return_code = system("pkexec su");
    qDebug() << return_code;
}
