#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFile>
#include <QList>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {

    ui->setupUi(this);
    ui->lineEdit->setReadOnly(true);
    ui->lineEdit->setText("0");
    ui->horizontalSlider->setMaximum(100);

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_horizontalSlider_sliderMoved(int position) {

    double value = 100.000;
    double t = double(position);
    double selected = t / value;
    ui->lineEdit->setText(QString::number(selected));
}


void MainWindow::on_pushButton_2_clicked() {

    qApp->exit();
}

void MainWindow::on_pushButton_clicked() {

    QString value = ui->lineEdit->text();

    if (value != "0") {

        int id = get_input_id();

        if (id != -1) {
            QString command = "xinput --set-prop " + QString::number(id) + " 'libinput Accel Speed' " + value;
            QByteArray ba = command.toLocal8Bit();
            const char *c_str2 = ba.data();
            write_changes(c_str2);

        } else {
            qDebug() << "Oops, something went south";
        }

    }  else {
        qDebug() << "Please select a value";

    }
}

void MainWindow::write_changes(const char *command) {

    int return_code = system(command);

}

int MainWindow::get_input_id() {

    int return_code = system("xinput list > list.txt");
    system("python3 parse.py list.txt");

    if (return_code == 0) {
        QFile file("value.txt");
        file.open(QIODevice::ReadOnly);
        QString our_value;
        our_value.append(file.readAll());
        int code = our_value.toInt();
        return code;


    } else {
        qDebug() << "Error";

        return -1;
    }

}
