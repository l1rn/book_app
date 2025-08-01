
#include "SpecialButton.h"

SpecialButton::SpecialButton(QWidget *parent)
    : QPushButton(parent) {
    setObjectName("specialButton");
    setMinimumHeight(20);

    setStyleSheet(
        "SpecialButton {"
        "    background-color: #1976D2;"
        "    color: white;"
        "    border-radius: 8px;"
        "    padding: 6px 12px;"
        "    font-weight: bold;"
        "}"
        "SpecialButton:hover {"
        "    background-color: #1565C0;"
        "}"
    );
}