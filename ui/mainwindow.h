#include "QMainWindow"
#include "QPushButton"

#ifndef MAINWINDOW_H
#define MAINWINDOW_H



class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void onButtonClicked();

private:
    QPushButton *button{};
};


#endif //MAINWINDOW_H
