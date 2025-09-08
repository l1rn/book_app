#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override = default;
private:
    QWidget *central;
    QWidget *headerWidget;
    QWidget *contentWidget;

    QPushButton *profile_button;

    QVBoxLayout *mainLayout;
    QVBoxLayout *contentLayout;
    QHBoxLayout *headerLayout;

    // layout properties
    void setupUI();
    void setupHeader();
    void setupContent();

    // button properties
    void setupProfileButton();
    void handleButton();
};

#endif