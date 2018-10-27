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
    void write_changes(const char *command);

private slots:
    void on_horizontalSlider_sliderMoved(int position);
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();


private:
    Ui::MainWindow *ui;
    std::string path;

};

#endif // MAINWINDOW_H
