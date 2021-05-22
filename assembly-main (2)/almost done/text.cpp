#include "text.h"
#include <QGraphicsTextItem>

text::text(QGraphicsItem *parent)
    : QGraphicsTextItem(parent)
{}

QString text::getTextString() {
    return textString;
}

void text::setTextString(const QString &textStr) {
    textString = textStr;
}

QColor text::getArrowTextColor() {
    return textArrowColor;
}

QColor text::getCircleTextColor() {
    return textCircleColor;
}

void text::setCircleTextColor(const QColor &color) {
    textCircleColor = color;
}

void text::setArrowTextColor(const QColor &color) {
    textArrowColor = color;
}

void text::clearTexts() {
    int size = listArrowTexts.size();
    for(int i=size-1; i>=0; i--) {
        listArrowTexts.erase(listArrowTexts.begin()+i);
    }
    size = listCircleTexts.size();
    for(int i=size-1; i>=0; i--) {
       listCircleTexts.erase(listCircleTexts.begin()+i);
    }
    textString = "";
}

