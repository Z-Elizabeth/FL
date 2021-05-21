#include "circle.h"
#include "text.h"
#include <QApplication>
#include <QtWidgets>

circle::circle(QObject *parent)
    : QObject(parent)
{
    CirclePenColor= Qt::black;
    CircleBrushColor = Qt::white;
    numCurCircle=-1;
    CirclePenWidth = 1;
    std::vector<int> circleParametrs;
    ifCircle = false;
}

extern text Text;

QColor circle::getCirclePenColor() {
    return CirclePenColor;
}

QColor circle::getCircleBrushColor() {
    return CircleBrushColor;
}

QPoint circle::getCircleLastPoint() {
    return CircleLastPoint;
}

int circle::getCirclePenWidth() {
    return CirclePenWidth;
}

void circle::setCirclePenColor(const QColor &newColor)
{
    CirclePenColor = newColor;
}

void circle::setCircleBrushColor(const QColor &newColor)
{
    CircleBrushColor = newColor;
}

void circle::setCircleLastPoint(const QPoint &newPoint)
{
    CircleLastPoint = newPoint;
}

void circle::setCirclePenWidth(const int &newWidth) {
    CirclePenWidth = newWidth;
}

void circle::clearCircles() {
    int size = listCircles.size();
    for(int i=size-1; i>=0; i--) {
        listCircles.erase(listCircles.begin()+i);
    }
    size = listRect.size();
    if (size>0) {
       listRect.erase(listRect.begin());
    }
    numCurCircle = -1;
}

void circle::drawNewCircle(const QPoint &endPoint) {
    int radius = 25;
    std::pair<QPoint,int> oneMore(endPoint,radius);
    listCircles.push_back(oneMore);
    QPoint text_location;
    text_location.rx() = int(endPoint.x() - 10);
    text_location.ry() = int(endPoint.y() - 5);
    Text.listCircleTexts.push_back({text_location, Text.getTextString()});
}

void circle::markCircle(const std::vector<int> &parametrs){
    int radius = parametrs[3];
    QPoint point;
    point.setX(parametrs[1]-radius);
    point.setY(parametrs[2]-radius);
    listRect.push_back({point,2*radius});
    //modified = true;
    //redraw();
}

bool circle::ifMarkCircle(){
    if (listRect.size() == 0) return false;
    else return true;
}

void circle::disMarkCircle(){
    listRect.erase(listRect.begin());
    numCurCircle=0;
}

std::pair<QPoint, int> circle::checkNearCircle(const QPoint &point) {
    std::pair<QPoint, int> result = {point, 0};
    for (auto elem : listCircles) {
        if ((point.x() >= elem.first.x() - elem.second) && (point.x() <= elem.first.x() + elem.second)
             && (point.y() >= elem.first.y() - elem.second) && (point.y() <= elem.first.y() + elem.second)) {
            result = elem;
        }
    }
    return result;
}

void circle::mousePressEventCircle() {
    circleParametrs = ifEmptyCircle(getCircleLastPoint());

    if(circleParametrs[0]==0 && !ifMarkCircle()) drawNewCircle(getCircleLastPoint());
    else if(!ifMarkCircle()) markCircle(circleParametrs);
    else if(circleParametrs[0]==0) disMarkCircle();
}

void circle::changeSizeCircle(const QPoint &endPoint){
    int a = getCircleLastPoint().x()-endPoint.x();
    int b = getCircleLastPoint().y()-endPoint.y();
    int radius = a*a + b*b;
    radius = sqrt(radius);
    listCircles[numCurCircle].second=radius;
    QPoint point;
    point.setX(listCircles[numCurCircle].first.x()-listCircles[numCurCircle].second);
    point.setY(listCircles[numCurCircle].first.y()-listCircles[numCurCircle].second);
    listRect[0].first = point;
    listRect[0].second = 2*listCircles[numCurCircle].second;
    //redraw();
}

std::vector<int> circle::ifEmptyCircle(const QPoint &endPoint){
    int size = listCircles.size();
    std::vector<int> parametrs={0,0,0,0};
    if(size==0) return {0,0,0,0};
    for(int i=0; i<size; i++){
        int a = endPoint.x()-listCircles[i].first.x();
        int b = endPoint.y()-listCircles[i].first.y();
        int res = a*a + b*b - listCircles[i].second*listCircles[i].second;
        numCurCircle= i;
        if(res < 0) return {1,listCircles[i].first.x(),listCircles[i].first.y(),listCircles[i].second};
    }
    return parametrs;
}

void circle::changePosCircle(const QPoint &endPoint){
    listCircles[numCurCircle].first.setX(listCircles[numCurCircle].first.x() + (endPoint.x()-getCircleLastPoint().x()));
    listCircles[numCurCircle].first.setY(listCircles[numCurCircle].first.y() + (endPoint.y()-getCircleLastPoint().y()));
    QPoint point;
    point.setX(listCircles[numCurCircle].first.x()-listCircles[numCurCircle].second);
    point.setY(listCircles[numCurCircle].first.y()-listCircles[numCurCircle].second);
    listRect[0].first = point;
    setCircleLastPoint(endPoint);
    Text.listCircleTexts[numCurCircle].first.rx() = endPoint.x() - 10;
    Text.listCircleTexts[numCurCircle].first.ry() = endPoint.y() - 5;
}

