#include <iostream>
#include <math.h>
#include "Graphics3D.h"

using namespace std;


int main() {
    cone c1 = cone(200, 200, 20);
    //c1.rotateFigure(40, 30, 29);
    

    sphere s1 = sphere(500, 10);
    //s1.printAll();
    //s1.rotateFigure(90, 90, 90);

    cone con1 = cone(200, 200, 20);
    con1.printAll();
    double i = 0;

    canvas Canvas1 (1000, 1000, "3D graphics project");

    while (Canvas1.endCondition()) {
        while (true) {
            if (Canvas1.FrameInit()) return 0;

            c1.draw(al_map_rgb(255, 0, 255), 2);
            s1.draw(al_map_rgb(255, 255, 255), 2);
            c1.rotateFigure(0.1, 0.1, 0.1);
            s1.rotateFigure(-0.1, -0.1, -0.1);
            //con1.draw(al_map_rgb(255, 255, 0), 2);
            //con1.drawPixels(al_map_rgb(255, 55, 255), 2);
            //con1.rotateFigure(-0.1, -0.1, -0.1);
            //c1.reposition(i, -i, i);
            i += 0.0001;
            Canvas1.keyframe();
        }
    }

    return 0;
}
