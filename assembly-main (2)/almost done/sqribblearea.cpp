#include <QtWidgets>
#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#if QT_CONFIG(printdialog)
#include <QPrinter>
#include <QPrintDialog>
#endif
#endif

#include <iostream>
#include <QFile>

#include "scribblearea.h"
#include "circle.h"
#include "arrow.h"
#include "windows.h"
#include "text.h"



ScribbleArea::ScribbleArea(QWidget *parent)
    : QWidget(parent)
{
    // Roots the widget to the top left even if resized
    setAttribute(Qt::WA_StaticContents);

    // Set defaults for the monitored variables
    modified = false;
    scribbling = false;
}

circle Circle;
arrow Arrow;
text Text;

bool ScribbleArea::saveImage(const QString &fileName)
{
    // Created to hold the image
    QImage visibleImage = image;
    resizeImage(&visibleImage, size());

    if (visibleImage.save(fileName)) {
        modified = false;
        return true;
    } else {
        return false;
    }
}


void ScribbleArea::clearImage()
{
    image.fill(qRgb(255, 255, 255));
    modified = false;
    update();
}

void ScribbleArea::clearScreen()
{
    clearImage();

    Arrow.clearArrows();

    Circle.clearCircles();

    Text.clearTexts();

     //QFile file(QDir::currentPath()+"/text.txt");
     QFile file("../../../text.txt");
     file.open(QIODevice::WriteOnly);
     file.close();
}

std::pair<QPoint, std::pair<QPoint, QPoint>> ScribbleArea::findIntersection(const QPoint &beginPoint, const QPoint &endPoint, int radius) {
    QPoint resultPoint = endPoint;
    QPoint firstHead = endPoint;
    QPoint secondHead = endPoint;

    //Line equation: y = k * x + b
    float k = (1.0*endPoint.y() - 1.0*beginPoint.y())/(1.0*endPoint.x() - 1.0*beginPoint.x());
    float b = 1.0*beginPoint.y() - k*beginPoint.x();
    float x = 0;

    //Intersection equation: y = ax^2 + cx + e
    float a = k * k + 1;
    float c = 2 * (k * (b - endPoint.y()) - endPoint.x());
    float e = - radius * radius - 2 * b * endPoint.y() + b * b + endPoint.y() * endPoint.y() + endPoint.x() * endPoint.x();
    float D = c * c - 4 * a * e;
    x = (- c + pow(D, 0.5)) / (2 * a);
    if (x < std::min(beginPoint.x(), endPoint.x()) || x > std::max(beginPoint.x(), endPoint.x())) {
           x = (- c - pow(D, 0.5)) / (2 * a);
    }
    resultPoint.setX(int(x));
    resultPoint.setY(int(k * x + b));

    float k_1 = tan(atan(k) + 0.6);
    float b_1 = 1.0 * resultPoint.y() - k_1 * resultPoint.x();

    float k_2 = tan(atan(k) - 0.6 + 3.14);
    float b_2 = 1.0 * resultPoint.y() - k_2 * resultPoint.x();

    float x_2 = 0;
    float x_1 = 0;

    if ((beginPoint.x() - resultPoint.x() > 0) ){

        x_2 = ((-20 * sin(0.6) * sqrt(1 + pow(k, 2)) - (b_2 - b)) /(k_2 - k));
        x_1 = ((20 * sin(0.6) * sqrt(1 + pow(k, 2)) - (b_1 - b)) /(k_1 - k));
    }

    else{
        x_2 = ((20 * sin(0.6) * sqrt(1 + pow(k, 2)) - (b_2 - b)) /(k_2 - k));
        x_1 = ((-20 * sin(0.6) * sqrt(1 + pow(k, 2)) - (b_1 - b)) /(k_1 - k));

    }
    float y_2 = k_2 * x_2 + b_2;
    float y_1 = k_1 * x_1 + b_1;

    firstHead.setX(int(x_1));
    firstHead.setY(int(y_1));
    secondHead.setX(int(x_2));
    secondHead.setY(int(y_2));

    //resultPoint.setX(0);
    //resultPoint.setY(0);
    return {resultPoint, {firstHead, secondHead}};
}


void ScribbleArea::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        Circle.setCircleLastPoint(event->pos());
        //QPoint beginArrow;
        //beginArrow = findIntersection(event->pos());
        //Arrow.setArrowFirstPoint(event->pos());
        scribbling = true;
        if(Circle.ifCircle) {
            Circle.mousePressEventCircle();
            //Sleep(500);
        }
        if(Arrow.ifArrow) {
            QPoint beginArrow = Circle.checkNearCircle(event->pos()).first;
            Arrow.addBeginPointArrow(beginArrow);
            //Arrow.mousePressEventArrow();
        }
    }
}

void ScribbleArea::mouseMoveEvent(QMouseEvent *event)
{
    if(Circle.ifCircle && Circle.ifMarkCircle() ) {

        if(event->buttons() & Qt::LeftButton){
            Circle.changeSizeCircle(event->pos());
        }

        if(event->buttons() & Qt::RightButton){
            Circle.changePosCircle(event->pos());
        }
    }
}

void ScribbleArea::mouseReleaseEvent(QMouseEvent *event)
{
    if ((event->button() == Qt::LeftButton && scribbling) && Arrow.ifArrow) {
        std::pair<QPoint, int> endArrowCircle = Circle.checkNearCircle(event->pos());
        Arrow.addEndPointArrow(findIntersection(Arrow.listArrows[Arrow.numCurArrow].first,
                               endArrowCircle.first, endArrowCircle.second).first);
        Arrow.listHeads.push_back(findIntersection(Arrow.listArrows[Arrow.numCurArrow].first,
                endArrowCircle.first, endArrowCircle.second).second);
        scribbling = false;
    }
    redraw();
}

void ScribbleArea::mouseDoubleClickEvent(QMouseEvent *event) {
/*    if (event->button() == Qt::LeftButton && Circle.ifCircle) {
        QPainter painter(this);
        painter.setBrush(Qt::white);
        painter.drawEllipse(event->pos(), 10, 10);
    }
    paintEvent();
*/
}

void ScribbleArea::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    QRect dirtyRect = event->rect();
    painter.drawImage(dirtyRect, image, dirtyRect);
}

void ScribbleArea::resizeEvent(QResizeEvent *event)
{
    if (width() > image.width() || height() > image.height()) {
        int newWidth = qMax(width() + 128, image.width());
        int newHeight = qMax(height() + 128, image.height());
        resizeImage(&image, QSize(newWidth, newHeight));
        update();
    }
    QWidget::resizeEvent(event);
}

void ScribbleArea::drawLineTo(const QPoint &endPoint)
{
    QPainter painter(&image);

    painter.setPen(QPen(Arrow.getArrowPenColor(), Arrow.getArrowPenWidth(), Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));

    painter.drawLine(Arrow.getArrowLastPoint(), endPoint);

    //modified = true;

    Arrow.setArrowLastPoint(endPoint);
}

void ScribbleArea::resizeImage(QImage *image, const QSize &newSize)
{
    if (image->size() == newSize)
        return;

    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(255, 255, 255));

    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}

void ScribbleArea::clickedCircleButton(){
    if(Circle.ifCircle) {Circle.ifCircle = false;}
    else { Circle.ifCircle = true; Arrow.ifArrow = false; }
}

void ScribbleArea::clickedArrowButton(){
    if(Arrow.ifArrow) {Arrow.ifArrow = false;}
    else { Arrow.ifArrow = true; Circle.ifCircle = false; }

}

void ScribbleArea::clickedDeleteButton()
{
/*    circle->setAutoExclusive(false);
    circle->setChecked(false);
    circle->setAutoExclusive(true);
    arrow->setAutoExclusive(false);
    arrow->setChecked(false);
    arrow->setAutoExclusive(true);
*/

    //Circle.deleteCircle();
    if (Circle.ifMarkCircle()) {
        Circle.listCircles.erase(Circle.listCircles.begin() + Circle.numCurCircle);
        Text.listCircleTexts.erase(Text.listCircleTexts.begin() + Circle.numCurCircle);
        Arrow.checkNearArrow(Circle.listRect);
        Circle.listRect.erase(Circle.listRect.begin());
        modified = true;
    }
    redraw();

}

void ScribbleArea::redraw(){
    clearImage();
    QPainter painter(&image);

    //Draw arrows
    painter.setPen(QPen(Arrow.getArrowPenColor(), Arrow.getArrowPenWidth()+1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.setRenderHint(QPainter::Antialiasing, true);
    int size = Arrow.listArrows.size();
    for(int i=0;i<size;i++){
        painter.drawLine(Arrow.listArrows[i].first, Arrow.listArrows[i].second);
        painter.drawLine(Arrow.listArrows[i].second, Arrow.listHeads[i].first);
        painter.drawLine(Arrow.listArrows[i].second, Arrow.listHeads[i].second);
    }

    //Draw circles
    painter.setPen(QPen(Circle.getCirclePenColor(), Circle.getCirclePenWidth()+1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.setBrush(Circle.getCircleBrushColor());
    size = Circle.listCircles.size();
    for(int i=0; i<size; i++){
        painter.drawEllipse(Circle.listCircles[i].first, Circle.listCircles[i].second, Circle.listCircles[i].second);
    }

    //Draw rectangle which marks a circle
    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.setBrush(QBrush (Qt::transparent));
    size = Circle.listRect.size();
    if(size != 0) {
        painter.drawRect(Circle.listRect[0].first.x(), Circle.listRect[0].first.y(), Circle.listRect[0].second, Circle.listRect[0].second);
    }

    //Draw texts
    painter.setPen(QPen(Text.getArrowTextColor(), 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    size = Text.listArrowTexts.size();
    for(int i = 0; i < size; i++) {
       painter.drawText(Text.listArrowTexts[i].first, Text.listArrowTexts[i].second);
    }

    painter.setPen(QPen(Text.getCircleTextColor(), 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    size = Text.listCircleTexts.size();
    for(int i = 0; i < size; i++) {
        painter.drawText(Text.listCircleTexts[i].first, Text.listCircleTexts[i].second);
    }

    //Rewrite text file
    //QFile file(QDir::currentPath()+"/text.txt");
    QFile file("../../../text.txt");
    if (file.open(QIODevice::WriteOnly))
    {
        //circle pen color, arrow color, circle brush color, circle width, arrow width
        QString str = Circle.getCirclePenColor().name()+"|"+Circle.getCircleBrushColor().name()+"|"
                +QString::number(Circle.getCirclePenWidth())+"|"+Arrow.getArrowPenColor().name()+"|"
                +QString::number(Arrow.getArrowPenWidth())+ "|" + Text.getCircleTextColor().name() + "|"
                + Text.getArrowTextColor().name() + "\n";
        file.write(str.toUtf8());

        int size = Arrow.listArrows.size();
        for(int i=0; i<size; i++){
            //if arrow length is not 0
           if (Arrow.listArrows[i].first.x() != Arrow.listArrows[i].second.x() or Arrow.listArrows[i].first.y() != Arrow.listArrows[i].second.y()) {
                QString str = "0|" + Text.listArrowTexts[i].second + "|" + QString::number(Arrow.listArrows[i].first.x())+"|"
                    + QString::number(Arrow.listArrows[i].first.y()) + "|"
                    + QString::number(Arrow.listArrows[i].second.x())+"|"
                    + QString::number(Arrow.listArrows[i].second.y()) + "|"
                    + QString::number(Arrow.listHeads[i].first.x()) + "|"
                    + QString::number(Arrow.listHeads[i].first.y()) + "|"
                    + QString::number(Arrow.listHeads[i].second.x()) + "|"
                    + QString::number(Arrow.listHeads[i].second.y()) + "\n";
                file.write(str.toUtf8());
            }
        }

        size = Circle.listCircles.size();
        for(int i=0;i<size; i++){
            QString str = "1|" + Text.listCircleTexts[i].second + "|" + QString::number(Circle.listCircles[i].first.x())+"|"
                    + QString::number(Circle.listCircles[i].first.y()) + "|"
                    + QString::number(Circle.listCircles[i].second) + "\n";
            file.write(str.toUtf8());
        }

        file.close();
    }
    modified = true;
}
