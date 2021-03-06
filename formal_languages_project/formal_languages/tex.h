#pragma once

#include <QApplication>
#include <QWidget>
#include <string>

using namespace std;

class tex : public QObject
{
    Q_OBJECT
public:
    tex(QObject *parent = 0);
    float convertHexToTexDec(const char (&hex)[2]);

public slots:
    bool convertToTex(const QString &path);

private:
    struct Round {
        int x = 0;
        int y = 0;
        string name;
        int r = 0;
    };

    struct Line {
        int x1 = 0;
        int y1 = 0;
        int x2 = 0;
        int y2 = 0;
        string name;
        int head_x1 = 0;
        int head_y1 = 0;
        int head_x2 = 0;
        int head_y2 = 0;
        int text_x = 0;
        int text_y = 0;
    };

};
