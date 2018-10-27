#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_horizontalSlider_sliderMoved(int position);
    void on_save_button_clicked();
    void on_exit_button_clicked();

private:
    Ui::MainWindow *ui;
    std::string path;
    int value;
};

#endif // MAINWINDOW_H
