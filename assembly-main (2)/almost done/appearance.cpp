#include "appearance.h"
#include "circle.h"
#include "arrow.h"
#include "scribblearea.h"
#include "tex.h"
#include "text.h"
#include <iostream>

Appearance::Appearance(QWidget *parent): QMainWindow(parent){

    scribbleArea = new ScribbleArea;
    Tex = new tex;
    setCentralWidget(scribbleArea);

    createMenus();
    createTools();
    resize(500,500);
    setWindowTitle("Convert graph to TeX");
}

extern circle Circle;
extern arrow Arrow;
extern text Text;

void Appearance::createMenus(){

    clearScreenAct = new QAction("Clear Screen", this);
    clearScreenAct->setShortcut(tr("Ctrl+L"));
    connect(clearScreenAct, SIGNAL(triggered()), scribbleArea, SLOT(clearScreen()));

    circlePenColorAct = new QAction("Circle Pen Color",this);
    connect(circlePenColorAct, SIGNAL(triggered()), this, SLOT(circlePenColor()));

    circleBrushColorAct = new QAction("Circle Brush",this);
    connect(circleBrushColorAct, SIGNAL(triggered()), this, SLOT(circleBrushColor()));

    circleWidthAct = new QAction("Circle Width",this);
    connect(circleWidthAct, SIGNAL(triggered()), this, SLOT(circleWidth()));

    arrowPenColorAct = new QAction("Arrow Pen Color",this);
    connect(arrowPenColorAct, SIGNAL(triggered()), this, SLOT(arrowPenColor()));

    arrowWidthAct = new QAction("Arrow Width",this);
    connect(arrowWidthAct, SIGNAL(triggered()), this, SLOT(arrowWidth()));

    textArrowColorAct = new QAction("Text Arrow Color", this);
    connect(textArrowColorAct, SIGNAL(triggered()), this, SLOT(textArrowColor()));

    textCircleColorAct = new QAction("Text Circle Color", this);
    connect(textCircleColorAct, SIGNAL(triggered()), this, SLOT(textCircleColor()));

    saveAct = new QAction("Save as image", this);
    saveAct->setShortcut(tr("Ctrl+Shift+S"));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(saveFile()));

    saveToTexAct = new QAction("Export to TeX", this);
    saveToTexAct->setShortcut(tr("Ctrl+Shift+T"));
    connect(saveToTexAct, SIGNAL(triggered()), Tex, SLOT(convertToTex()));

    file = new QMenu(tr("File"),this);
    file->addAction(saveAct);
    file->addAction(saveToTexAct);

    optionMenu = new QMenu(tr("Options"),this);
    optionMenu->addAction(circlePenColorAct);
    optionMenu->addAction(circleBrushColorAct);
    optionMenu->addAction(circleWidthAct);
    optionMenu->addAction(arrowPenColorAct);
    optionMenu->addAction(arrowWidthAct);
    optionMenu->addAction(textArrowColorAct);
    optionMenu->addAction(textCircleColorAct);

    menuBar()->addMenu(file);
    menuBar()->addMenu(optionMenu);
    menuBar()->addSeparator();
    menuBar()->addAction(clearScreenAct);

}

void Appearance::createTools(){

    circle = new QRadioButton(tr("&Circle"),this);
    circle->setCheckable(true);
    connect(circle, SIGNAL(clicked()), scribbleArea, SLOT(clickedCircleButton()));

    arrow = new QRadioButton(tr("&Arrow"),this);
    arrow->setCheckable(true);
    connect(arrow, SIGNAL(clicked()), scribbleArea, SLOT(clickedArrowButton()));

    deleteBut = new QPushButton(tr("&Delete"),this);
    deleteBut->setCheckable(false);
    deleteBut->setShortcut(tr("CTRL+D"));
    deleteBut->setChecked(false);
    connect(deleteBut, SIGNAL(clicked()), scribbleArea, SLOT(clickedDeleteButton()));

    setTextButton = new QPushButton(tr("&Set Text"), this);
    setTextButton->setCheckable(false);
    setTextButton->setChecked(false);
    connect(setTextButton, SIGNAL(clicked()), this, SLOT(clickedSetTextButton()));

    toolbar = addToolBar("main toolbar");
    toolbar->addWidget(circle);
    toolbar->addWidget(arrow);
    toolbar->addWidget(deleteBut);
    toolbar->addWidget(setTextButton);
}

bool Appearance::maybeSave()
{
    if (scribbleArea->isModified()) {
       QMessageBox::StandardButton ret;
       ret = QMessageBox::warning(this, tr("Save"), tr("The image has been modified.\n"
                          "Do you want to save your changes?"),
                          QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        if (ret == QMessageBox::Save) {
            return saveFile();
        } else if (ret == QMessageBox::Cancel) {
            return false;
        }
    }
    return true;
}

void Appearance::closeEvent(QCloseEvent *event)
{
    if (maybeSave()) {
        event->accept();
    } else {
        event->ignore();
    }
}

void Appearance::circlePenColor()
{
    QColor newColor = QColorDialog::getColor();

    if (newColor.isValid())
        Circle.setCirclePenColor(newColor);

    scribbleArea->redraw();
}

void Appearance::circleWidth()
{
    bool ok;

    int newWidth = QInputDialog::getInt(this, tr("Circle Pen Width"), tr("Select pen width:"), Circle.getCirclePenWidth(), 1, 30, 1, &ok);

    if (ok) {
        Circle.setCirclePenWidth(newWidth);
    }

    scribbleArea->redraw();
}

void Appearance::circleBrushColor()
{
    QColor newColor = QColorDialog::getColor();

    if (newColor.isValid())
        Circle.setCircleBrushColor(newColor);

    scribbleArea->redraw();
}

void Appearance::arrowPenColor()
{
    QColor newColor = QColorDialog::getColor();

    if (newColor.isValid()) {
        Arrow.setArrowPenColor(newColor);
    }

    scribbleArea->redraw();
}

void Appearance::arrowWidth()
{
    bool ok;

    int newWidth = QInputDialog::getInt(this, tr("Arrow Pen Width"), tr("Select pen width:"), Arrow.getArrowPenWidth(), 1, 30, 1, &ok);

    if (ok) {
        Arrow.setArrowPenWidth(newWidth);
    }

    scribbleArea->redraw();
}

void Appearance::textArrowColor() {
    QColor newColor = QColorDialog::getColor();

    if (newColor.isValid()) {
        Text.setArrowTextColor(newColor);
    }

    scribbleArea->redraw();
}

void Appearance::textCircleColor() {
    QColor newColor = QColorDialog::getColor();

    if (newColor.isValid()) {
        Text.setCircleTextColor(newColor);
    }

    scribbleArea->redraw();
}

void Appearance::clickedSetTextButton() {
    bool ok;
    QString text = QInputDialog::getText(this, tr("Set Text"),
                                  tr("Text:"), QLineEdit::Normal, "", &ok);
    Text.setTextString(text);
}

bool Appearance::saveFile()
{
    QString initialPath = QDir::currentPath() + "/untitled";

    QString saveFileName = QFileDialog::getSaveFileName(this,  tr("Save as"), initialPath, tr("PNG(*.png);; TIFF(*.tiff *.tif);; JPEG(*.jpg *.jpeg);;All files(*)"));
    int pos = saveFileName.lastIndexOf('.');
    if (pos >= 0){
        return scribbleArea->saveImage(saveFileName);
    }
    else {
         return false;
    }
}
