#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <fstream>
#include <vector>
#include <utility>

using namespace std;

#define d 8
#define c 1
struct Circle {
    int x = 0;
    int y = 0;
    //string name;
    int r = 0;
};

struct Line {
    int x1 = 0;
    int y1 = 0;
    int x2 = 0;
    int y2 = 0;
    //string name;
};

float convertHexToTexDec(const char (&hex)[2]) {
    int dec = 0;
    for (int i = 0; i < 2; i++) {
        if (int(hex[i]) < 58) {
            //digit
            dec += pow(16, 1 - i)*(int(hex[i]) - 48);
        }
        else {
            //letter
            dec += pow(16, 1 - i)*(int(hex[i]) - 87);
        }
    }

    //convert to tex rgb format: 1 instead of 255
    float ans = dec/255.0;
    ans = int(ans*100 + 0.5)/100.0;
    return ans;
}


//—˜ËÚ‡ÂÏ, ˜ÚÓ double ÔËÌËÏ‡ÂÚÒˇ ‚ ‚Ë‰Â x.xx
int main() {

    /*char ao[2] = {'0', '0'};
    float oa = convertHexToTexDec(ao);
    cout << oa << endl;*/

    ofstream output("output.txt");
    ifstream input ("text.txt");
    //string name;

    string ifCircle_string;
    string x1_string;
    string x2_string;
    string y1_string;
    string y2_string;
    string r_string;

    vector <Line> lines;
    vector <Circle> circles;

    string circlePenColor;
    char circleRed_c[2];
    char circleGreen_c[2];
    char circleBlue_c[2];
    float circleRed;
    float circleGreen;
    float circleBlue;
    string circleBrushColor;
    char circleBrushRed_c[2];
    char circleBrushGreen_c[2];
    char circleBrushBlue_c[2];
    float circleBrushRed;
    float circleBrushGreen;
    float circleBrushBlue;
    string circleWidth_str;
    float circleWidth;
    string arrowPenColor;
    char arrowRed_c[2];
    char arrowGreen_c[2];
    char arrowBlue_c[2];
    float arrowRed;
    float arrowGreen;
    float arrowBlue;
    string arrowWidth_str;
    float arrowWidth;

    if (input.is_open()) {

        getline(input, circlePenColor, '|');
        circleRed_c[0] = circlePenColor[1];
        circleRed_c[1] = circlePenColor[2];
        //cout << " dsijkvnsd " << circleRed_c[0] << " " << circleRed_c[1] << endl;
        circleGreen_c[0] = circlePenColor[3];
        circleGreen_c[1] = circlePenColor[4];
        circleBlue_c[0] = circlePenColor[5];
        circleBlue_c[0] = circlePenColor[6];
        //convert to TeX color rgb format
        circleRed = convertHexToTexDec(circleRed_c);
        circleGreen = convertHexToTexDec(circleGreen_c);
        circleBlue = convertHexToTexDec(circleBlue_c);

        getline(input, circleBrushColor, '|');
        circleBrushRed_c[0] = circleBrushColor[1];
        circleBrushRed_c[1] = circleBrushColor[2];
        circleBrushGreen_c[0] = circleBrushColor[3];
        circleBrushGreen_c[1] = circleBrushColor[4];
        circleBrushBlue_c[0] = circleBrushColor[5];
        circleBrushBlue_c[1] = circleBrushColor[6];
        //convert to TeX color rgb format
        circleBrushRed = convertHexToTexDec(circleBrushRed_c);
        circleBrushGreen = convertHexToTexDec(circleBrushGreen_c);
        circleBrushBlue = convertHexToTexDec(circleBrushBlue_c);

        getline(input, circleWidth_str, '|');

        for (int i = 0; i < circleWidth_str.size(); i++) {
                int a = pow(10, circleWidth_str.size() - i - 1);
                circleWidth += a * (int(circleWidth_str[i] - '0'));
        }
        circleWidth = circleWidth;

        getline(input, arrowPenColor, '|');
        arrowRed_c[0] = arrowPenColor[1];
        arrowRed_c[1] = arrowPenColor[2];
        arrowGreen_c[0] = arrowPenColor[3];
        arrowGreen_c[1] = arrowPenColor[4];
        arrowBlue_c[0] = arrowPenColor[5];
        arrowBlue_c[1] = arrowPenColor[6];
        //convert to TeX color rgb format
        arrowRed = convertHexToTexDec(arrowRed_c);
        arrowGreen = convertHexToTexDec(arrowGreen_c);
        arrowBlue = convertHexToTexDec(arrowBlue_c);

        getline(input, arrowWidth_str, '\n');

        for (int i = 0; i < arrowWidth_str.size(); i++) {
                int a = pow(10, arrowWidth_str.size() - i - 1);
                arrowWidth += a * (int(arrowWidth_str[i] - '0'));
        }
        arrowWidth = arrowWidth;

    }

    int j = 0;
    while (j < d) {
        if (input.is_open()) {
            getline(input, ifCircle_string, '|');
            j++;
        }

        if (ifCircle_string == "0") {
            cout << "Line" << endl;
            struct Line line;
            //getline(input, name, '|');
            getline(input, x1_string, '|');
            getline(input, y1_string, '|');
            getline(input, x2_string, '|');
            getline(input, y2_string, '\n');

            for (int i = 0; i < x1_string.size(); i++) {
                int a = pow(10, x1_string.size() - i - 1);
                line.x1 += a * (int(x1_string[i] - '0'));
            }

            for (int i = 0; i < y1_string.size(); i++) {
                int a = pow(10, y1_string.size() - i - 1);
                line.y1 += a * (int(y1_string[i] - '0'));
            }

            for (int i = 0; i < x2_string.size(); i++) {
                int a = pow(10, x2_string.size() - i - 1);
                line.x2 += a * (int(x2_string[i] - '0'));
            }

            for (int i = 0; i < y2_string.size(); i++) {
                int a = pow(10, y2_string.size() - i - 1);
                line.y2 += a * (int(y2_string[i] - '0'));
            }

            cout << line.x1 << " " << line.y1 << " " << line.x2 << " " << line.y2 << endl;
            //l.name = name;

            lines.push_back(line);
        }

        else if (ifCircle_string == "1") {
            cout << "Circle" << endl;
            getline(input, x1_string, '|');
            getline(input, y1_string, '|');
            getline(input, r_string, '\n');
            struct Circle circle;

            //cout << str_length << endl;
            for (int i = 0; i < x1_string.size(); i++) {
                int a = pow(10, x1_string.size() - i - 1);
                circle.x += a * (int(x1_string[i] - '0'));
            }

            for (int i = 0; i < y1_string.size(); i++) {
                int a = pow(10, y1_string.size() - i - 1);
                circle.y += a * (int(y1_string[i] - '0'));
            }

            for (int i = 0; i < r_string.size(); i++) {
                int a = pow(10, r_string.size() - i - 1);
                circle.r += a * (int(r_string[i] - '0'));
            }

            cout << circle.x << " " << circle.y << " " << circle.r << endl;
            //cir.name = name;
            //cir.color = y2_string;

            circles.push_back(circle);

        }

    }

    output << "\\definecolor{arrowPenColor}{rgb}{" << arrowRed << ", " << arrowGreen << ", " << arrowBlue << "}" << endl;
    output << "\\definecolor{circlePenColor}{rgb}{" << circleRed << ", " << circleGreen << ", " << circleBlue << "}" << endl;
    output << "\\definecolor{circleBrushColor}{rgb}{" << circleBrushRed << ", " << circleBrushGreen << ", " << circleBrushBlue << "}" << endl;
    output << "\\begin{center}\n\t\\begin{tikzpicture}[scale=0.03]" << endl;

    for (auto el : lines) {
        double alpha = atan((el.y2 - el.y1) / (el.x2 - el.x1));
        output << "\t\t\\draw [line width = " << arrowWidth << ", arrowPenColor] (" <<
                                                        el.x1 << "," << el.y1 << ") -- (" << el.x2 << "," << el.y2 << ");" << endl;
        //output << "\t\t\\draw (" << (el.x2 + el.x1)/2 << "," << (el.y2 + el.y1)/2 << ") node [below] {$" << "el.name" << "$};" << endl;
        //output << "\t\t\\fill [black] (" << el.x2 << "," << el.y2 << ") -- (" << el.x2 - c * cos(0.52 + alpha) << "," << el.y2 - c * sin(0.52 + alpha) << ") -- (" << el.x2 - c * cos(alpha - 0.52) << "," << el.y2 - c * sin(alpha - 0.52) << ");" << endl;
    }

    for (auto el : circles) {
        //output << "\t\t\\fill [circleBrushColor] (" <<
        //                                                el.x << "," << el.y << ") -- (" << el.r << "," << el.r << ");" << endl;
        output << "\t\t\\draw[line width = " << circleWidth << ", circlePenColor, fill = circleBrushColor](" << el.x <<
                                                        ", " << el.y << ") circle(" << el.r << ");\n";
        //output << "\t\t\\draw(" << el.x << ", " << el.y << ") node {$" << "el.name" << "$};" << endl;
    }

    output << "\t\\end{tikzpicture}" << endl << "\\end{center}" << endl;


    return 0;
}
