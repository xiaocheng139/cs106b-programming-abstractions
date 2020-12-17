#include "Plotter.h"
#include "strlib.h"
using namespace std;

/*
 * void drawLine(double x0, double y0, double x1, double y1, PenStyle info);
 */

void runPlotterScript(istream& input) {
    // Initialise
    PenStyle style = {1, "black"};
    double x = 0, y = 0;
    bool penUp = true;

    // Read and execute each line
    for (string line; getline(input, line);) {
        Vector<string> words = stringSplit(line, " ");
        string action = toLowerCase(words[0]);

        if (startsWith(action, "penup")) {
            penUp = true;

        } else if (startsWith(action, "pendown")) {
            penUp = false;

        } else if (startsWith(action, "moveabs")) {
            double x1 = stringToReal(words[1]);
            double y1 = stringToReal(words[2]);
            if (penUp == false) {
                drawLine(x, y, x1, y1, style);
            }
            x = x1;
            y = y1;

        } else if (startsWith(action, "moverel")) {
            double xMove = stringToReal(words[1]);
            double yMove = stringToReal(words[2]);
            if (penUp == false) {
                drawLine(x, y, x + xMove, y + yMove, style);
            }
            x += xMove;
            y += yMove;

        } else if (startsWith(action, "penwidth")) {
            style.width = stringToReal(words[1]);

        } else if (startsWith(action, "pencolor")) {
            style.color = words[1];

        }

    }
}
