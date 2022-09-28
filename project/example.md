# Example program: {#example}
 Simple program with some of the methods form this library with comments:
  
  ```
  #include <iostream>
#include <math.h>
#include "Graphics3D.h"

using namespace std;


int main() {
    cube c1 = cube(400 / sqrt(3)); //initiation of a cube by edge with 400 / sqrt(3) length
    c1.reposition(500, 500); //repositioning cube from (0,0) point to (500, 500) with anchor point
    
    sphere s1 = sphere(400, 15); //initiation of a sphere with radius 400 and 15 latitude lines
    s1.printAll(); //printing all plain data

    cone con1 = cone(200, 200, 20); //initiation of a cone with base radius of 200, 200 height and with a base circle with 20 vertices
    con1.printAll();

    canvas Canvas1 (1000, 1000, "3D graphics project"); //initiation of new canvas

    while (Canvas1.endCondition()) {
        while (true) {
            if (Canvas1.FrameInit()) { return 0; }

            c1.draw(al_map_rgb(255, 0, 255), 2); // drawing all edges of cube with pink color and line thickness of 2px
            s1.draw(al_map_rgb(255, 255, 255), 2);
            c1.rotateFigure(0.1, 0.1, 0.1); // rotation figure by (0.1, 0.1, 0.1) in 3D
            s1.rotateFigure(-0.1, -0.1, -0.1);
            con1.draw(al_map_rgb(255, 255, 0), 2);
            con1.drawPixels(al_map_rgb(255, 55, 255), 2); //drawing all vertices as purple points with radius of 2px;
            con1.rotateFigure(-0.1, -0.1, -0.1);
            Canvas1.keyframe();
        }
    }
    return 0;
}

```