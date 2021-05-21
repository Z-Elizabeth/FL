#ifndef TEXT_H
#define TEXT_H
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
    void setTextColor(const QColor &color);
    QColor getTextColor();

signals:

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    QString textString;
    QColor textColor;
};

#endif // TEXT_H
