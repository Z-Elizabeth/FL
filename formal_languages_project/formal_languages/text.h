#pragma once
#include <QGraphicsTextItem>


class text : public QGraphicsTextItem
{
    Q_OBJECT
public:
    text(QGraphicsItem *parent = nullptr);
    std::vector<std::pair<QPoint, QString>> listArrowTexts;
    std::vector<std::pair<QPoint, QString>> listCircleTexts;
    void clearTexts();
    QString getTextString();
    void setTextString(const QString &textStr);
    void setArrowTextColor(const QColor &color);
    void setCircleTextColor(const QColor &color);
    QColor getArrowTextColor();
    QColor getCircleTextColor();

protected:
    QString textString;
    QColor textArrowColor;
    QColor textCircleColor;
};
