#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <iostream>
#include <string>

std::string exec(const std::string& cmd);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setReadOnly(true);
    ui->horizontalSlider->setMinimum(10);
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

    // Remove the new line
    path.pop_back();

    // Add file
    path += "/sensitivity";

    // Get current sensitivity
    value = std::stoi(exec("cat " + path));

    ui->lineEdit->setText(QString::number(value));
    ui->horizontalSlider->setValue(value);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    // Update text box
    ui->lineEdit->setText(QString::number(position));
}

void MainWindow::on_save_button_clicked()
{
    // Write value to device file
    exec("echo " + std::to_string(ui->horizontalSlider->value()) + " > " + path);
}

void MainWindow::on_exit_button_clicked()
{
    qApp->exit();
}
