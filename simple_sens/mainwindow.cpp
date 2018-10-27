#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFile>
#include <QList>
#include <iostream>

std::string exec(const char* cmd);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setReadOnly(true);
    ui->lineEdit->setText("0");
    ui->horizontalSlider->setMaximum(220);

    // Find device path of trackpoint
    path = exec("find /sys/devices/platform/i8042"
                " -name name | xargs grep -Fl TrackPoint"
                " | sed 's/\\/input\\/input[0-9]*\\/name$//'");

    // Chech if path was found
    if (path == "")
    {
        std::cerr << "Error: Trackpoint device path not found." << std::endl;
        exit(-1);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{

    double t = double(position);
    double selected = t / 100.0;
    ui->lineEdit->setText(QString::number(selected));
}


void MainWindow::on_pushButton_2_clicked()
{

    qApp->exit();
}

void MainWindow::on_pushButton_clicked()
{

    QString value = ui->lineEdit->text();

    if (value != "0")
    {

        int id = 0;

        if (id != -1)
        {
            QString command = "xinput --set-prop " + QString::number(id) + " 'libinput Accel Speed' " + value;
            QByteArray ba = command.toLocal8Bit();
            const char *c_str2 = ba.data();
            write_changes(c_str2);

        }
        else
        {
            qDebug() << "Oops, something went south";
        }

    }
    else
    {
        qDebug() << "Please select a value";

    }
}

void MainWindow::write_changes(const char *command)
{

    int return_code = system(command);
}
