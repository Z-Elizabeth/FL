#include <QApplication>
#include <QWidget>
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <fstream>
#include <vector>
#include <utility>
#include "tex.h"

using namespace std;

tex::tex(QObject *parent)
    : QObject(parent)
{}

float tex::convertHexToTexDec(const char (&hex)[2]) {
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


bool tex::convertToTex(const QString &saveTexFileName) {

    string path = qPrintable(saveTexFileName);
    ofstream output(path);
    ifstream input ("../../../text.txt");

    string name;
    string ifRound_string;
    string x1_string;
    string x2_string;
    string y1_string;
    string y2_string;
    string r_string;
    string head_x1_string;
    string head_y1_string;
    string head_x2_string;
    string head_y2_string;
    string text_x_string;
    string text_y_string;

    vector <Line> lines;
    vector <Round> rounds;

    string roundPenColor;
    char roundRed_c[2];
    char roundGreen_c[2];
    char roundBlue_c[2];
    float roundRed = 0.0;
    float roundGreen = 0.0;
    float roundBlue = 0.0;
    string roundBrushColor;
    char roundBrushRed_c[2];
    char roundBrushGreen_c[2];
    char roundBrushBlue_c[2];
    float roundBrushRed = 0.0;
    float roundBrushGreen = 0.0;
    float roundBrushBlue = 0.0;
    string roundWidth_str;
    float roundWidth = 0.0;
    string arrowPenColor;
    char arrowRed_c[2];
    char arrowGreen_c[2];
    char arrowBlue_c[2];
    float arrowRed = 0.0;
    float arrowGreen = 0.0;
    float arrowBlue = 0.0;
    string arrowWidth_str;
    float arrowWidth = 0.0;
    string textCircleColor;
    char textCircleRed_c[2];
    char textCircleGreen_c[2];
    char textCircleBlue_c[2];
    float textCircleRed = 0.0;
    float textCircleGreen = 0.0;
    float textCircleBlue = 0.0;
    string textArrowColor;
    char textArrowRed_c[2];
    char textArrowGreen_c[2];
    char textArrowBlue_c[2];
    float textArrowRed = 0.0;
    float textArrowGreen = 0.0;
    float textArrowBlue = 0.0;

    if (input.is_open()) {

        getline(input, roundPenColor, '|');
        roundRed_c[0] = roundPenColor[1];
        roundRed_c[1] = roundPenColor[2];
        roundGreen_c[0] = roundPenColor[3];
        roundGreen_c[1] = roundPenColor[4];
        roundBlue_c[0] = roundPenColor[5];
        roundBlue_c[0] = roundPenColor[6];
        //convert to TeX color rgb format
        roundRed = convertHexToTexDec(roundRed_c);
        roundGreen = convertHexToTexDec(roundGreen_c);
        roundBlue = convertHexToTexDec(roundBlue_c);

        getline(input, roundBrushColor, '|');
        roundBrushRed_c[0] = roundBrushColor[1];
        roundBrushRed_c[1] = roundBrushColor[2];
        roundBrushGreen_c[0] = roundBrushColor[3];
        roundBrushGreen_c[1] = roundBrushColor[4];
        roundBrushBlue_c[0] = roundBrushColor[5];
        roundBrushBlue_c[1] = roundBrushColor[6];
        //convert to TeX color rgb format
        roundBrushRed = convertHexToTexDec(roundBrushRed_c);
        roundBrushGreen = convertHexToTexDec(roundBrushGreen_c);
        roundBrushBlue = convertHexToTexDec(roundBrushBlue_c);

        getline(input, roundWidth_str, '|');

        int size = roundWidth_str.size();
        for (int i = 0; i < size; i++) {
                int a = pow(10, size - i - 1);
                roundWidth += a * (int(roundWidth_str[i] - '0'));
        }

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

        getline(input, arrowWidth_str, '|');

        size = arrowWidth_str.size();
        for (int i = 0; i < size; i++) {
                int a = pow(10, size - i - 1);
                arrowWidth += a * (int(arrowWidth_str[i] - '0'));
        }

        getline(input, textCircleColor, '|');
        textCircleRed_c[0] = textCircleColor[1];
        textCircleRed_c[1] = textCircleColor[2];
        textCircleGreen_c[0] = textCircleColor[3];
        textCircleGreen_c[1] = textCircleColor[4];
        textCircleBlue_c[0] = textCircleColor[5];
        textCircleBlue_c[1] = textCircleColor[6];
        //convert to TeX color rgb format
        textCircleRed = convertHexToTexDec(textCircleRed_c);
        textCircleGreen = convertHexToTexDec(textCircleGreen_c);
        textCircleBlue = convertHexToTexDec(textCircleBlue_c);

        getline(input, textArrowColor, '\n');
        textArrowRed_c[0] = textArrowColor[1];
        textArrowRed_c[1] = textArrowColor[2];
        textArrowGreen_c[0] = textArrowColor[3];
        textArrowGreen_c[1] = textArrowColor[4];
        textArrowBlue_c[0] = textArrowColor[5];
        textArrowBlue_c[1] = textArrowColor[6];
        //convert to TeX color rgb format
        textArrowRed = convertHexToTexDec(textArrowRed_c);
        textArrowGreen = convertHexToTexDec(textArrowGreen_c);
        textArrowBlue = convertHexToTexDec(textArrowBlue_c);

    }


    while (getline(input, ifRound_string, '|')) {

        if (ifRound_string == "0") {
            struct Line line;
            getline(input, name, '|');
            getline(input, text_x_string, '|');
            getline(input, text_y_string, '|');
            getline(input, x1_string, '|');
            getline(input, y1_string, '|');
            getline(input, x2_string, '|');
            getline(input, y2_string, '|');
            getline(input, head_x1_string, '|');
            getline(input, head_y1_string, '|');
            getline(input, head_x2_string, '|');
            getline(input, head_y2_string, '\n');

            int size = text_x_string.size();
            for (int i = 0; i < size; i++) {
                int a = pow(10, size - i - 1);
                line.text_x += a * (int(text_x_string[i] - '0'));
            }
            line.text_x += 5;

            size = text_y_string.size();
            for (int i = 0; i < size; i++) {
                int a = pow(10, size - i - 1);
                line.text_y += a * (int(text_y_string[i] - '0'));
            }
            line.text_y = - line.text_y;

            size = x1_string.size();
            for (int i = 0; i < size; i++) {
                int a = pow(10, size - i - 1);
                line.x1 += a * (int(x1_string[i] - '0'));
            }

            size = y1_string.size();
            for (int i = 0; i < size; i++) {
                int a = pow(10, size - i - 1);
                line.y1 += a * (int(y1_string[i] - '0'));
            }
            line.y1 = - line.y1;

            size = x2_string.size();
            for (int i = 0; i < size; i++) {
                int a = pow(10, size - i - 1);
                line.x2 += a * (int(x2_string[i] - '0'));
            }

            size = y2_string.size();
            for (int i = 0; i < size; i++) {
                int a = pow(10, size - i - 1);
                line.y2 += a * (int(y2_string[i] - '0'));
            }

            line.y2 = - line.y2;

            size = head_x1_string.size();
            for (int i = 0; i < size; i++) {
                int a = pow(10, size - i - 1);
                line.head_x1 += a * (int(head_x1_string[i] - '0'));
            }

            size = head_y1_string.size();
            for (int i = 0; i < size; i++) {
                int a = pow(10, size - i - 1);
                line.head_y1 += a * (int(head_y1_string[i] - '0'));
            }

            line.head_y1 = - line.head_y1;

            size = head_x2_string.size();
            for (int i = 0; i < size; i++) {
                int a = pow(10, size - i - 1);
                line.head_x2 += a * (int(head_x2_string[i] - '0'));
            }

            size = head_y2_string.size();
            for (int i = 0; i < size; i++) {
                int a = pow(10, size - i - 1);
                line.head_y2 += a * (int(head_y2_string[i] - '0'));
            }

            line.head_y2 = - line.head_y2;

            line.name = name;

            lines.push_back(line);
        }

        else if (ifRound_string == "1") {
            getline(input, name, '|');
            getline(input, x1_string, '|');
            getline(input, y1_string, '|');
            getline(input, r_string, '\n');
            struct Round round;

            int size = x1_string.size();
            for (int i = 0; i < size; i++) {
                int a = pow(10, size - i - 1);
                round.x += a * (int(x1_string[i] - '0'));
            }

            size = y1_string.size();
            for (int i = 0; i < size; i++) {
                int a = pow(10, size - i - 1);
                round.y += a * (int(y1_string[i] - '0'));
            }

            round.y = -round.y;

            size = r_string.size();
            for (int i = 0; i < size; i++) {
                int a = pow(10, size - i - 1);
                round.r += a * (int(r_string[i] - '0'));
            }

            round.name = name;
            //cir.color = y2_string;

            rounds.push_back(round);

        }

    }

    output << "\\documentclass[12pt]{article}" << endl;
    output << "\\usepackage{tikz}" << endl;
    output << "\\begin{document}" << endl;
    output << "\\definecolor{arrowPenColor}{rgb}{" << arrowRed << ", " << arrowGreen << ", " << arrowBlue << "}" << endl;
    output << "\\definecolor{roundPenColor}{rgb}{" << roundRed << ", " << roundGreen << ", " << roundBlue << "}" << endl;
    output << "\\definecolor{roundBrushColor}{rgb}{" << roundBrushRed << ", " << roundBrushGreen << ", " << roundBrushBlue << "}" << endl;
    output << "\\definecolor{textCircleColor}{rgb}{" << textCircleRed << ", " << textCircleGreen << ", " << textCircleBlue << "}" << endl;
    output << "\\definecolor{textArrowColor}{rgb}{" << textArrowRed << ", " << textArrowGreen << ", " << textArrowBlue << "}" << endl;
    output << "\\begin{center}\n\t\\begin{tikzpicture}[scale=0.03]" << endl;

    for (auto el : lines) {
        output << "\t\t\\draw [line width = " << arrowWidth << ", arrowPenColor] (" <<
                                                        el.x1 << "," << el.y1 << ") -- (" << el.x2 << "," << el.y2 << ");" << endl;
        output << "\t\t\\draw [line width = " << arrowWidth << ", arrowPenColor] (" <<
                                                        el.head_x1 << "," << el.head_y1 << ") -- (" << el.x2 << "," << el.y2 << ");" << endl;
        output << "\t\t\\draw [line width = " << arrowWidth << ", arrowPenColor] (" <<
                                                        el.head_x2 << "," << el.head_y2 << ") -- (" << el.x2 << "," << el.y2 << ");" << endl;
        output << "\t\t\\draw[textArrowColor](" << el.text_x << "," << el.text_y << ") node [below] {$" << el.name << "$};" << endl;
    }

    for (auto el : rounds) {

        output << "\t\t\\draw[line width = " << roundWidth << ", roundPenColor, fill = roundBrushColor](" << el.x <<
                                                        ", " << el.y << ") circle(" << el.r << ");\n";
        output << "\t\t\\draw[textCircleColor](" << el.x << ", " << el.y << ") node {$" << el.name << "$};" << endl;
    }

    output << "\t\\end{tikzpicture}" << endl << "\\end{center}" << endl;
    output << "\\end{document}" << endl;

    return true;
}
