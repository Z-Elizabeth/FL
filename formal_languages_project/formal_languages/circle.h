#pragma once

#include <QApplication>
#include <QtWidgets>
#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>
#include <vector>
#include <utility>

class circle : public QObject
{
    Q_OBJECT
public:
    circle(QObject *parent = 0);

    void clearCircles();
    void mousePressEventCircle();
    void changeSizeCircle(const QPoint &endPoint);
    void changePosCircle(const QPoint &endPoint);
    void setCirclePenColor(const QColor &newColor);
    void setCircleBrushColor(const QColor &newColor);
    void setCircleLastPoint(const QPoint &newPoint);
    void setCirclePenWidth(const int &newWidth);

    std::pair<QPoint, int> checkNearCircle(const QPoint &point);
    QColor getCirclePenColor();
    QColor getCircleBrushColor();
    QPoint getCircleLastPoint();
    int getCirclePenWidth();

    std::vector<std::pair<QPoint, std::pair<int, bool>>> listCircles;
    int numCurCircle;
    std::vector<std::pair<QPoint,int>> listRect;
    bool ifCircle;
    bool ifMarkCircle();

private:
    void drawNewCircle(const QPoint &endPoint);
    void markCircle(const std::vector<int> &parametrs);
    void disMarkCircle();

    QColor CirclePenColor;
    QColor CircleBrushColor;
    QPoint CircleLastPoint;
    int CirclePenWidth;
    std::vector<int> ifEmptyCircle(const QPoint &endPoint);
    std::vector<int> circleParametrs;

};
