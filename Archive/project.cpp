#include <iostream>
#include <math.h>
  
using namespace std;

#define pi 3.14159265359
#define eps 6
#define depth 200
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>


using namespace std;

double aprox(double x, int y) { //for smaller numbers, but less accurate
    return x;
    //return round((10 ^ y) * x) / (10 ^ y);
}

class Vertice {
    double x;
    double y;
    double z;
    friend ostream& operator<< (ostream& c, const Vertice& orig);
public:
    Vertice& operator+ (Vertice& other) { //changes the original
        x = other.x;
        y = other.y;
        z = other.z;
        return *this;
    }
    Vertice& operator- (Vertice& other) { //changes the original
        Vertice temp = Vertice();
        x = other.x;
        y = other.y;
        z = other.z;
        return *this;
    }
    /*Vertice& operator= (const Vertice& other) {
        if (this == &other) return *this;
        x = other.x;
        y = other.y;
        z = other.z;
        return *this;
    }*/
    Vertice& operator* (double k) {
        x = x * k;
        y = y * k;
        z = z * k;
        return *this;
    }
    /*Vertice& operator= (Vertice&& other) {
        if (this == &other) return *this;
        x = move(other.x);
        y = move(other.y);
        z = move(other.z);
        return *this;
    }*/
    Vertice operator[] (int i) {
        switch (i) {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        default:
            cerr << "Returns value only on 0-2";
            return NULL;
        }
    }
    double operator() (char type) { //() to change coordinates from 3D obj on to 2D plane
        type = tolower(type);
        switch (type) {
        case 'x':
            return x * depth / z;
        case 'y':
            return y * depth / z;
        default:
            cerr << "You have to choose beetwen x or y\n";
        }
    }
    double operator() (int type) { //() to change coordinates from 3D obj on to 2D plane
        switch (type) {
        case 0:
            return x * depth / z;
        case 1:
            return y * depth / z;
        default:
            cerr << "You have to choose beetwen x/0 or y/1\n";
        }
    }
    double get2D(char type) {
        type = tolower(type);
        switch (type) {
        case 'x':
            return x * depth / z + 500;
        case 'y':
            return y * depth / z + 500;
        default:
            cerr << "You have to choose beetwen x or y\n";
        }
    }
    double get2D(int type) { //() to change coordinates from 3D obj on to 2D plane
        switch (type) {
        case 0:
            return x * depth / z + 500;
        case 1:
            return y * depth / z + 500;
        default:
            cerr << "You have to choose beetwen x/0 or y/1\n";
        }
    }

    Vertice(double ix = 0, double iy = 0, double iz = 0) {
        x = ix;
        y = iy;
        z = iz;
    }
    double get(int i) {
        switch (i) {
        case 0:
            return x + 500;
        case 1:
            return y + 500;
        case 2:
            return z + 500;
        default:
            cerr << "Returns value only on 0-2";
            return NULL;
        }
    }
    void rePosition(double ax, double ay, double az) {
        x = ax;
        y = ay;
        z = az;
    }
    void addPosition(double ax, double ay, double az) {
        x += ax;
        y += ay;
        z += az;
    }
    void multiplePosition(double kx, double ky = 1, double kz = 1) {
        z *= kx;
        y *= ky;
        z *= kz;
    }
    void rotate(double ax, double ay = 0, double az = 0, Vertice anchorPoint = Vertice(0, 0, 0)) { //rotate in 3D (angle) axis using anchor point
        Vertice tempVertice = *this;
        double cosX = cos(ax * pi / 180), cosY = cos(ay * pi / 180), cosZ = cos(az * pi / 180), sinX = sin(ax * pi / 180), sinY = sin(ay * pi / 180), sinZ = sin(az * pi / 180);

        double Axx = cosX * cosY;
        double Axy = cosX * sinY * sinZ - sinX * cosZ;
        double Axz = cosX * sinY * cosZ + sinX * sinZ;

        double Ayx = sinX * cosY;
        double Ayy = sinX * sinY * sinZ + cosX * cosZ;
        double Ayz = sinX * sinY * cosZ - cosX * sinZ;

        double Azx = -sinY;
        double Azy = cosY * sinZ;
        double Azz = cosY * cosZ;

        tempVertice.x = aprox(Axx * x + Axy * y + Axz * z, eps);
        tempVertice.y = aprox(Ayx * x + Ayy * y + Ayz * z, eps);
        tempVertice.z = aprox(Azx * x + Azy * y + Azz * z, eps);
        *this = tempVertice;
    }
    void printAll() {
        cout << "(" << x << ", " << y << ", " << z << ")";
    }
    ostream& printAll(ostream& c) {
        cout << "(" << x << ", " << y << ", " << z << ")";
        return c;
    }
};
ostream& operator<< (ostream& c, const Vertice& orig) { //using << operator to stream data from vertice
    cout << "(" << orig.x << ", " << orig.y << ", " << orig.z << ")";
    return c;
}

class Edge {
public:
    Vertice* v1;
    Vertice* v2;
    friend ostream& operator<< (ostream& c, const Edge& orig);

    Edge& operator= (const Edge& other) {
        if (this == &other) return *this;
        v1 = other.v1;
        v2 = other.v2;
        return *this;
    }
    Edge(Vertice& iv1, Vertice& iv2) {
        v1 = &iv1;
        v2 = &iv2;
    }
    Edge() {
        v1 = nullptr;
        v2 = nullptr;
    }
    void position(double ix, double iy = 0, double iz = 0) {
        v1->addPosition(ix, iy, iz);
        v2->addPosition(ix, iy, iz);
    }

};
ostream& operator<< (ostream& c, const Edge& orig) { //using << operator to stream data from vertice
    orig.v1->printAll(); cout << " -> "; orig.v2->printAll(); cout << endl;
    return c;
}

class Obj_3D {
public:
    Vertice anchorPoint;
    int vArrSize;
    int eArrSize;
    Vertice* vArr;
    Edge* eArr;

    Obj_3D(int v, int e) : vArrSize{ v }, eArrSize{ e } {
        vArr = new Vertice[vArrSize];
        eArr = new Edge[eArrSize];
    }
    void rotateFigure(double ax, double ay = 0, double az = 0, Vertice anchorPoint = Vertice(0, 0, 0)) {
        for (int i = 0; i < vArrSize; i++) {
            vArr[i].rotate(ax, ay, az, anchorPoint);
        }
    }
    void reposition(double ax, double ay = 0, double az = 0) {
        for (int i = 0; i < vArrSize; i++) {
            vArr[i].addPosition(ax, ay, az);
        }
    }
    void printAll() {
        cout << "Vertices:\n";
        for (int i = 0; i < vArrSize; i++) {
            cout << i << ". " << vArr[i] << endl;
        }
        cout << "Edges:\n";
        for (int i = 0; i < eArrSize; i++) {
            cout << i << ". " << eArr[i];
        }
    }
    void draw(ALLEGRO_COLOR a = al_map_rgb(255, 0, 0), int b = 2) {
        for (int i = 0; i < eArrSize; i++) {
            al_draw_line(eArr[i].v1->get(0), eArr[i].v1->get(1), eArr[i].v2->get(0), eArr[i].v2->get(1), a, b);

        }
    }
    void drawPixels(ALLEGRO_COLOR a = al_map_rgb(255, 255, 255), int r = 1) {
        for (int i = 0; i < vArrSize; i++) {
            al_draw_filled_circle(vArr[i].get(0), vArr[i].get(1), r, a);
        }
    }
};

class cube : public Obj_3D {
    double a;
public:
    cube(double ia, int v = 8, int e = 12) : Obj_3D(v, e) {
        double R = ia * sqrt(3) / 2;
        int alph = 45, beta = 0;

        for (int i = 0; i < v; i++) {
            vArr[i] = Vertice(R, R, R);
            vArr[i].rotate(alph, beta);
            alph += 90;
            if (alph > 360) { alph = 45; beta += 90; }
        }
        for (int i = 0; i < 4; i++) {
            eArr[i] = Edge(vArr[i], vArr[(i + 1) % 4]);
            eArr[i + 4] = Edge(vArr[i + 4], vArr[(i + 1) % 4 + 4]);
            eArr[i + 8] = Edge(vArr[i], vArr[i + 4]);
        }
    }
};
class sphere : public Obj_3D {
    double r;
public:
    sphere(double ir, int opt = 10) : Obj_3D(2 * (opt * (opt - 1) + 1), 2 * opt * (2 * opt - 1)) {
        r = ir;
        vArr[0] = Vertice(0, r, 0); // First Vertice

        double sphereAngle = 180.00 / opt;
        double alpha;
        double beta;

        //verices
        for (int i = 0; i < opt * 2; i++) {
            alpha = sphereAngle * (i);
            for (int j = 0; j < opt; j++) {
                beta = sphereAngle * (j + 1);
                vArr[j + (opt - 1) * i + 1] = Vertice(0, r, 0);
                vArr[j + (opt - 1) * i + 1].rotate(0, alpha, beta);
            }
        }
        vArr[vArrSize - 1] = Vertice(0, -r, 0); // Last Vertice
        //edges
        for (int i = 0; i < opt * 2; i++) {
            for (int j = 0; j < opt; j++) {
                int base = j + i * opt;
                int baseV = j + i * (opt - 1);
                if (j == 0) eArr[base] = Edge(vArr[0], vArr[baseV + 1]);
                else if (j == opt - 1) eArr[base] = Edge(vArr[baseV], vArr[vArrSize - 1]);
                else eArr[base] = Edge(vArr[baseV], vArr[baseV + 1]);
            }
        }
        for (int i = vArrSize + 2 * (opt - 1); i < eArrSize; i++) {
            int base = i % (vArrSize + 2 * (opt - 1)) + 1;
            eArr[i] = Edge(vArr[base], vArr[(base + opt - 2) % (vArrSize - 2) + 1]);
        }
    }
};
class cone : public Obj_3D {
    double r;
    double H;
public:
    cone(double ir, double iH, int opt = 10) : r{ ir }, H{ iH }, Obj_3D(opt + 1, 2 * opt) {
        vArr[0] = Vertice(0, H / 2.00, 0);
        double R = sqrt(pow((H / 2.00), 2) + pow(r, 2));
        double alpha = acos((2 / H / R) * pi / 180);
        double beta = 360.00 / (opt - 1);
        //Vertices
        for (int i = 1; i < opt + 1; i++) {
            vArr[i] = Vertice(r, 0, 0);
            vArr[i].rotate(0, beta * i);
            vArr[i].addPosition(0, -H, 0);
        }
        //Edges
        for (int i = 0; i < opt; i++) {
            eArr[i] = Edge(vArr[i], vArr[0]);
            eArr[i + opt] = Edge(vArr[i], vArr[(i) % (opt - 1) + 1]);
        }
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
    canvas(int ix, int iy, const char* ititle) : x{ ix }, y{ iy }{
        al_init();
        al_init_primitives_addon();
        al_install_keyboard();

        display = al_create_display(x, y);
        al_set_new_display_flags(ALLEGRO_WINDOWED);
        al_set_window_title(display, ititle);
        eQueue = al_create_event_queue();
        al_register_event_source(eQueue, al_get_display_event_source(display));
    }
    void keyframe() {
        al_flip_display();
        al_rest(0.005);
    }
    bool endCondition() {
        return !al_key_down(&keyboard, ALLEGRO_KEY_ESCAPE);
    }
    bool FrameInit(ALLEGRO_COLOR bg = al_map_rgb(0, 0, 0)) {
        al_get_next_event(eQueue, &event);
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) { return true; }
        al_get_keyboard_state(&keyboard);
        al_clear_to_color(bg);
        return false;
    }

    ~canvas() {
        al_destroy_display(display);
        al_destroy_event_queue(eQueue);
    }
};

int main() {
    cube c1 = cube(400 / sqrt(3));
    //c1.reposition(500, 500);
    //c1.rotateFigure(40, 30, 29);
    

    sphere s1 = sphere(200, 20);
    //s1.printAll();
    //s1.rotateFigure(90, 90, 90);

    cone con1 = cone(200, 200, 20);
    con1.printAll();

    canvas Canvas1 (1000, 1000, "3D graphics project");

    while (Canvas1.endCondition())
        while (true) {
            if (Canvas1.FrameInit()) { return 0; }

            c1.draw(al_map_rgb(255, 0, 255), 2);
            s1.drawPixels(al_map_rgb(255, 255, 255), 2);
            c1.rotateFigure(0.1, 0.1, 0.1);
            s1.rotateFigure(-0.1, -0.1, -0.1);
            con1.draw(al_map_rgb(255, 255, 0), 2);
            con1.drawPixels(al_map_rgb(255, 55, 255), 2);
            con1.rotateFigure(-0.1, -0.1, -0.1);
            Canvas1.keyframe();
        }

    return 0;
}
