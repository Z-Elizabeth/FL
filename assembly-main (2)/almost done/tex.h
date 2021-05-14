#ifndef TEX_H
#define TEX_H
#include <QApplication>
#include <QWidget>
#include <string>

using namespace std;

class tex : public QObject
{
    Q_OBJECT
public:
    tex(QObject *parent = 0);

public slots:
    void convertToTex();
};

#endif // TEX_H
