#ifndef TEX_H
#define TEX_H
#include <string>

using namespace std;

class tex
{
public:
    tex();
    void ConvertToTex();
    /*struct Circle getCircle();
    struct Line getLine();
    void setCircle(const struct Circle &circle);
    void setLine(const struct Line &line);*/

//private:
    struct Circle {
        double x;
        double y;
        string name;
        double r;
        string color;
    };

    struct Line {
        double x1;
        double y1;
        double x2;
        double y2;
        string name;
    };
};

#endif // TEX_H
