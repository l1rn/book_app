#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override = default;
private:
    QFont mainFont;

    QWidget *central;
    QWidget *headerWidget;
    QWidget *contentWidget;

    QLineEdit *searchInput;

    QPushButton *profileButton;
    QPushButton *searchButton;

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