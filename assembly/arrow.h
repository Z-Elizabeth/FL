#ifndef ARROW_H
#define ARROW_H
#include <QApplication>
#include <QWidget>


class arrow : public QObject
{
    Q_OBJECT
public:
    arrow(QObject *parent = 0);

    void setArrowPenColor(const QColor &newColor);
    void setArrowLastPoint(const QPoint &newPoint);
    void setArrowFirstPoint(const QPoint &newPoint);
    void setArrowPenWidth(const int &newWidth);
    void clearArrows();
    void deleteArrow();
    void addBeginPointArrow();
    void addEndPointArrow(const QPoint &endPoint);

    QColor getArrowPenColor();
    QPoint getArrowLastPoint();
    QPoint getArrowFirstPoint();
    int getArrowPenWidth();

    int numCurArrow;
    bool ifArrow;
    bool ifMarkArrow();
    std::vector<std::pair<QPoint,QPoint>> listArrows;

private:
    QColor ArrowPenColor;
    QPoint ArrowLastPoint;
    QPoint ArrowFirstPoint;
    int ArrowPenWidth;

};

#endif // ARROW_H
