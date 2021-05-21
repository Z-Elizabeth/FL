#include "text.h"
#include <QGraphicsTextItem>

text::text(QGraphicsItem *parent)
    : QGraphicsTextItem(parent)
{
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
}

QVariant text::itemChange(GraphicsItemChange change,
                     const QVariant &value)
{
    //if (change == QGraphicsItem::ItemSelectedHasChanged)
        //emit selectedChange(this);
    return value;
}

QString text::getTextString() {
    return textString;
}

void text::setTextString(const QString &textStr) {
    textString = textStr;
}

QColor text::getTextColor() {
    return textColor;
}

void text::setTextColor(const QColor &color) {
    textColor = color;
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
}

