#include "arrow.h"
#include "text.h"
#include <cmath>
#include <QApplication>


arrow::arrow(QObject *parent)
    : QObject(parent)
{
    ArrowPenColor = Qt::black;
    ifArrow = false;
    numCurArrow=-1;
    ArrowPenWidth = 1;
}

extern text Text;

QColor arrow::getArrowPenColor() {
    return ArrowPenColor;
}

QPoint arrow::getArrowLastPoint() {
    return ArrowLastPoint;
}

int arrow::getArrowPenWidth() {
    return ArrowPenWidth;
}

QPoint arrow::getArrowFirstPoint() {
    return ArrowFirstPoint;
}

void arrow::setArrowPenColor(const QColor &newColor)
{
    ArrowPenColor = newColor;
}

void arrow::setArrowLastPoint(const QPoint &newPoint)
{
    ArrowLastPoint = newPoint;
}

void arrow::setArrowFirstPoint(const QPoint &newPoint)
{
    ArrowFirstPoint = newPoint;
}

void arrow::setArrowPenWidth(const int &newWidth) {
    ArrowPenWidth = newWidth;
}

void arrow::clearArrows() {
    int size = listArrows.size();
    for(int i=size-1; i>=0; i--) {
        listArrows.erase(listArrows.begin()+i);
        listHeads.erase(listHeads.begin()+i);
    }
    numCurArrow = -1;
}

void arrow::deleteArrow(std::vector<int> &arrowToDelete) {
    int size = arrowToDelete.size();
    for (int i = 0; i < size; i++) {
        listArrows.erase(listArrows.begin() + arrowToDelete[i] - i);
        listHeads.erase(listHeads.begin() + arrowToDelete[i] - i);
        Text.listArrowTexts.erase(Text.listArrowTexts.begin() + arrowToDelete[i] - i);
    }
}

void arrow::addBeginPointArrow(const QPoint &beginPoint) {
    QPoint point;
    point.setX(0);
    point.setY(0);
    listArrows.push_back({beginPoint, point});
    numCurArrow = listArrows.size()-1;
}

void arrow::addEndPointArrow(const QPoint &endPoint) {
    QPoint point;
    point.setX(0);
    point.setY(0);
    if (listArrows[numCurArrow].first != endPoint && listArrows[numCurArrow].second == point) {
        listArrows[numCurArrow].second = endPoint;
    }
    // Find text location
    float k = (1.0*listArrows[numCurArrow].first.y() - 1.0*listArrows[numCurArrow].second.y())/
                    (1.0*listArrows[numCurArrow].first.x() - 1.0*listArrows[numCurArrow].second.x());
    float k_1 = -1/k;
    float b = 1.0*listArrows[numCurArrow].first.y() - k*listArrows[numCurArrow].first.x();
    int x_0 = int(0.5*(listArrows[numCurArrow].first.rx() + listArrows[numCurArrow].second.rx()));
    int y_0 = int(0.5*(listArrows[numCurArrow].first.ry() + listArrows[numCurArrow].second.ry()));
    float b_1 = k * x_0 + b - k_1 * x_0;

    //Distance equation: y = ax^2 + cx + e
    float a = k_1 * k_1 + 1;
    float c = 2 * (k_1 * (b_1 - y_0) - x_0);
    float e = - 300 - 2 * b_1 * y_0 + b_1 * b_1 + y_0 * y_0 + x_0 * x_0;
    float D = c * c - 4 * a * e;
    int x = int((- c + pow(D, 0.5)) / (2 * a));
    int y = int(k_1 * x + b_1);

    QPoint textLocation;
    textLocation.rx() = x;
    textLocation.ry() = y;
    Text.listArrowTexts.push_back({textLocation, Text.getTextString()});
}

void arrow::checkNearArrow(std::vector<std::pair<QPoint,int>> &rect) {
    int size = listArrows.size();
    std::vector<int> arrowToDelete;
    if(size > 0){
        for(int i = 0; i < size; i++){
            if (((listArrows[i].first.x() >= rect[0].first.x()) && (listArrows[i].first.x() <= rect[0].first.x() + rect[0].second)
                 && (listArrows[i].first.y() >= rect[0].first.y()) && (listArrows[i].first.y() <= rect[0].first.y() + rect[0].second))
                    || ((listArrows[i].second.x() >= rect[0].first.x()) && (listArrows[i].second.x() <= rect[0].first.x() + rect[0].second)
                        && (listArrows[i].second.y() >= rect[0].first.y()) && (listArrows[i].second.y() <= rect[0].first.y() + rect[0].second))) {
                arrowToDelete.push_back(i);
            }
        }
    }
    deleteArrow(arrowToDelete);
}
