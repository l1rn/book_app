#pragma once
#include <QPushButton>

class SpecialButton : public QPushButton {
    Q_OBJECT
public:
    explicit SpecialButton(QWidget *parent = nullptr);
};