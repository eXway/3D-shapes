
/** @file Graphics3D.h */

// header file

// prevention of multiple includes
#ifndef Graphics3D_H  // if FUNCTIONS_H is not defined ...
#define Graphics3D_H  // ... then define  FUNCTIONS_H
                     // otherwise jump to #endif

#include <iostream>
#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>


using namespace std;

double aprox(double x, int y);

class Vertice {
    double x{};
    double y{};
    double z{};
    friend ostream& operator<< (ostream& c, const Vertice& orig);
public:
    Vertice& operator+ (Vertice& other) { 
    }
    Vertice& operator- (Vertice& other) {
    }
    Vertice& operator* (double k) {
    }
    Vertice operator[] (int i) {
    }
    double operator() (char type) {
    }
    double operator() (int type) {
    }
    double get2D(char type) {
    }
    double get2D(int type) {
    }

    Vertice(double ix = 0, double iy = 0, double iz = 0) {
    }
    double get(int i) {
    }
    void rePosition(double ax, double ay, double az) {
    }
    void addPosition(double ax, double ay, double az) {
    }
    void multiplePosition(double kx, double ky = 1, double kz = 1) {
    }
    void rotate(double ax, double ay = 0, double az = 0, Vertice anchorPoint = Vertice(0, 0, 0)) {
    }
    void printAll() {
    }
    ostream& printAll(ostream& c);
};
ostream& operator<< (ostream& c, const Vertice& orig);

class Edge {
public:
    Vertice* v1{};
    Vertice* v2{};
    friend ostream& operator<< (ostream& c, const Edge& orig);

    Edge& operator= (const Edge& other) {
    }
    Edge(Vertice& iv1, Vertice& iv2) {
    }
    Edge() {
    }
    void position(double ix, double iy = 0, double iz = 0) {
    }

};
ostream& operator<< (ostream& c, const Edge& orig);

class Obj_3D {
public:
    Vertice anchorPoint{};
    int vArrSize{};
    int eArrSize{};
    Vertice* vArr{};
    Edge* eArr{};

    Obj_3D(int v, int e) : vArrSize{ v }, eArrSize{ e } {
    }
    void rotateFigure(double ax, double ay = 0, double az = 0, Vertice anchorPoint = Vertice(0, 0, 0)) {
    }
    void reposition(double ax, double ay = 0, double az = 0) {
    }
    void printAll() {
    }
    void draw(ALLEGRO_COLOR a = al_map_rgb(255, 0, 0), int b = 2) {
    }
    void drawPixels(ALLEGRO_COLOR a = al_map_rgb(255, 255, 255), int r = 1) {
    }
};

class cube : public Obj_3D {
    double a{};
public:
    cube(double ia, int v = 8, int e = 12) : Obj_3D(v, e) {
    }
};

class sphere : public Obj_3D {
    double r{};
public:
    sphere(double ir, int opt = 10) : Obj_3D(2 * (opt * (opt - 1) + 1), 2 * opt * (2 * opt - 1)) {
    }
};

class cone : public Obj_3D {
    double r{};
    double H{};
public:
    cone(double ir, double iH, int opt = 10) : r{ ir }, H{ iH }, Obj_3D(opt + 1, 2 * opt) {
    }

};

class canvas {
    int x{};
    int y{};
    ALLEGRO_DISPLAY* display{};
    ALLEGRO_EVENT_QUEUE* eQueue{};
    ALLEGRO_KEYBOARD_STATE keyboard{};
    ALLEGRO_EVENT event{};
public:
    canvas(int ix, int iy, const char* ititle);
    void keyframe();
    bool endCondition();
    bool FrameInit(ALLEGRO_COLOR bg = al_map_rgb(0, 0, 0));

    ~canvas() {
    }
};
#endif