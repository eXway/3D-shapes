#pragma once
/**
 * @file Graphics3D.h
 *
 * @author Robert Okenczyc ( robeoke723@student.polsl.pl)
 * @name Assignment 110 3 dimensional graphics
 * @brief Write a library drawing objects defined as simple 3-dimensional shapes. These shapes should be stored separately e.g. as a collection of lines, arcs etc. and drawn on request. Use the Allegro library.
 * @version 1.0
 * @date 2021-06-24
 *
 * @copyright Copyright (c) 2021
 *
 */


#include <iostream>
#include <math.h>
#define pi 3.14159265359
#define eps 6
#define depth 200
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

using namespace std;


/** 
 * \brief Approximate value 
 * \brief Woring with more than few double types could slow down work so this fucntion is for approximate purpuses, but
 * \brief using it could result in wrong positions after few changes  
 * \param x value to approx
 * \param y how many decimal numbers will there be ( 10 ^ y )
 * \return Approximated value with 10^y of decimal numbers
 * .
 */
double aprox(double x, int y);


/**
 * \brief Vertice is point in 3D space, it is the most basic class of 3D classes
 * \param x - width
 * \param y - height
 * \param z - depth
 */
class Vertice {
    double x;
    double y;
    double z;
    friend ostream& operator<< (ostream& c, const Vertice& orig);
public:
    /**
    * \brief Vertice Constructor with no values (default: (0, 0, 0) )
    */
    Vertice();
    /**
    * \brief Vertice Constructor with values (ix, iy, iz) 
    * \param ix - ix = x
    * \param iy - ix = x
    * \param iz - ix = x
    * \see Vertice
    */
    Vertice(double ix, double iy, double iz);
    /**
     * @brief Adding two Vertice objects (changes main Vertice)
     * \warning This function will change Vertice before operator
     * 
     * \param other Vertice after '+' operator to add
     * \return Main Vertice that has been changed
     */
    Vertice& operator+ (Vertice& other);
    /**
     * @brief Substracting two Vertice objects (changes main Vertice)
     * \warning This function will change Vertice before operator
     *
     * \param other Vertice after '-' will be substractor to first object
     * \return Main Vertice that has been changed
     */
    Vertice& operator- (Vertice& other);
    /**
     * @brief Multipling Vertice object by number (changes Vertice)
     * \warning This function will change Vertice before operator
     *
     * \param k multiplier for every value in Vertice (x, y ,z) 
     * \see Vertice
     * \return Main Vertice that has been changed
     */
    Vertice& operator* (double k);
    /**
     * \brief Getting data Vertice as one number (x, y or z)
     * \see Vertice
     * 
     * \param i 0-2 for values inside of Vertice
     * \return 0 for x, 1 for y, 2 for z; as one value
     */
    Vertice operator[] (int i);
    /**
     * \brief Getting data Vertice as one number (x, y or z)
     * \see Vertice
     * 
     * \param type x, y, z according to Vertice values
     * \return 'x' for x, 'y' for y, 'z' for z; as one value
     */
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
    /**
     * \brief Getting data Vertice as one number (x, y or z)
     * \see Vertice::operator[]()
     */
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

    double get2D(char type);
    double get2D(int type);
    /**
     * \brief Same as Vertice::operator[]
     * 
     * \param i 0-2
     * \see Vertice::operator[]()
     */
    double get(int i);
    /**
     * \brief Sets new position for x, y, z
     * 
     * \param ax New position of x
     * \param ay New position of y
     * \param az New position of z
     */
    void rePosition(double ax, double ay, double az);
    /**
     * \brief Adds values according to Vertice data
     * \see Vertice::operator+()
     * \param ax Value added to x
     * \param ay Value added to y
     * \param az Value added to z
     */
    void addPosition(double ax, double ay, double az);
    /**
     * \brief Multiplies values according to Vertice data
     * \see Vertice::operator*()
     * \param ax Mulitplier for x
     * \param ay Mulitplier for y
     * \param az Mulitplier for z
     */
    void multiplePosition(double kx, double ky = 1, double kz = 1);
    /**
     * @brief Rotates the Vertice accorging to Anchor Point position as center by angle as parameters
     * 
     * \param ax Angle in which Vertice will rotate by x axis
     * \param ay Angle in which Vertice will rotate by y axis
     * \param az Angle in which Vertice will rotate by z axis
     * \param anchorPoint Center pont for axis to be rotated of
     */
    void rotate(double ax, double ay = 0, double az = 0, Vertice anchorPoint = Vertice(0, 0, 0));
    /**
     * \brief Prints all the data as plain text
     * 
     */
    void printAll();
    ostream& printAll(ostream& c);
};

ostream& operator<< (ostream& c, const Vertice& orig);

/**
 * \brief Edge is a line between two Vertices in 3D space 
 * \see Vertice
 * \param *v1 Pointer to the first Vertice of this Edge
 * \param *v2 Pointer to the seccond Vertice of this Edge
 */
class Edge {
public:
    Vertice* v1;
    Vertice* v2;
    friend ostream& operator<< (ostream& c, const Edge& orig);

    /**
     * @brief Pasting data from *Edge other* to original one (before '=' operator)
     * \warning This function will change Edge before operator
     *
     * \param other The Edge which from data comes
     * \return Main Edge that has been changed
     */
    Edge& operator= (const Edge& other);

    /**
     * @brief Constructor of an Edge
     * 
     * \param iv1 Vertice 1 for v1
     * \param iv2 Vertice 2 for v2
     * \see Edge
     */
    Edge(Vertice& iv1, Vertice& iv2);
    /**
     * @brief Constructor without parameters (default) 
     * @brief Values of the data will be set to nullptr
     * 
     */
    Edge();
    /**
     * \brief Adding values to Vertices in Edge values
     * \see Vertice
     * \see Edge 
     * \see Vertice::addPosition()
     * \param ix Value added to both Vertices in Edge xs
     * \param iy Value added to both Vertices in Edge ys
     * \param iz Value added to both Vertices in Edge zs
     */
    void position(double ix, double iy = 0, double iz = 0);

};

ostream& operator<< (ostream& c, const Edge& orig);

/**
 * @brief Basic Figure class, base class for some of the next Figure classes. It contains every method to manipulate Figures.
 * \see Sphere
 * \see Cube
 * \see Cone
 * \param anchorPoint Center of the figure
 * \param vArrSize Size of the vArr array ( array of Vertices )
 * \param eArrSize Size of the eArr array ( array of Edges )
 * \param *vArr Array of pointers for Vertices
 * \param *eArr Arrat of ponters for Edges
 */
class Obj_3D {
public:
    Vertice anchorPoint;
    int vArrSize;
    int eArrSize;
    Vertice* vArr;
    Edge* eArr;

    /**
     * @brief Constructor of an Obj_3D
     *
     * \param v value for vArrSize
     * \see Obj_3D::vArrSize
     * \param e value for eArrSize
     * \see Obj_3D::eArrSize
     */
    Obj_3D(int v, int e);
    /**
     * \brief Rotates every Vertice in figure by 3D axis with anchorPoint in center
     * \see Vertice::rotate() 
     * \param ax Angle in which Figure will rotate by x axis
     * \param ay Angle in which Figure will rotate by y axis
     * \param az Angle in which Figure will rotate by z axis
     * \param anchorPoint Center pont for axis to be rotated of
     */
    void rotateFigure(double ax, double ay = 0, double az = 0, Vertice anchorPoint = Vertice(0, 0, 0));
    /**
     * @brief Sets new position of figure
     * 
     * \param ax Distance for xs to move
     * \param ay Distance for ys to move
     * \param az Distance for zs to move
     */
    void reposition(double ax, double ay = 0, double az = 0);
    /**
     * @biref Prints all data (Vertices, Edges) from a figure as a plain text
     * \see Vertice::printAll()
     * \see Edge::operator<<
     */
    void printAll();
    void draw(ALLEGRO_COLOR a = al_map_rgb(255, 0, 0), int b = 2);
    void drawPixels(ALLEGRO_COLOR a = al_map_rgb(255, 255, 255), int r = 1);
    ~Obj_3D();
};

/**
 * @brief Class with inherited methods from Obj_3D that contains constructor for Cube figure
 *
 * \param a Length of an Cube edge
 */
class cube : public Obj_3D {
    double a;
public:
    /**
     * @brief Constrctor for a Cube, made in (0, 0, 0) position 
     * @brief It also calls the constructor of an Obj_3D base class
     * 
     * \param ia Length of an Cube edge a{ia}
     * \param v Vertices count
     * \param e Edges count
     */
    cube(double ia, int v = 8, int e = 12);
};

/**
 * @brief Class with inherited methods from Obj_3D that contains constructor for Sphere figure
 * @brief It also calls the constructor of an Obj_3D base class
 * \param r Length of an Sphere radius
 */
class sphere : public Obj_3D {
    double r;
public:
    /**
     * @brief Constrctor for a sphere, made in (0, 0, 0) position
     *
     * \param ir Length of an sphere radius r{ir}
     * \param opt For information aobut opt check documentation main site
     */
    sphere(double ir, int opt = 10);
};

/**
 * @brief Class with inherited methods from Obj_3D that contains constructor for Cone figure
 * @brief It also calls the constructor of an Obj_3D base class
 * \param r Length of an base circe radius
 * \param H Length of a height of cone
 */
class cone : public Obj_3D {
    double r;
    double H;
    /**
     * @brief Constrctor for a cone, made in (0, 0, 0) position
     *
     * \param ir Length of an base circle radius r{ir}
     * \param iH Length of an height of the cone H{iH}
     * \param opt For information aobut opt check documentation main site
     */
public:
    cone(double ir, double iH, int opt = 10);

};

/**
 * @brief Class for Allegro 5 canvas initiation and animation handeling
 * \param x = width of an Allegro 5 window
 * \param y = height of an Allego 5 window
 */
class canvas {
    int x{};
    int y{};
    ALLEGRO_DISPLAY* display{};
    ALLEGRO_EVENT_QUEUE* eQueue{};
    ALLEGRO_KEYBOARD_STATE keyboard{};
    ALLEGRO_EVENT event{};
public:
    canvas(int ix = 1000, int iy = 1000, const char* ititle = "3D program");
    void keyframe();
    bool endCondition();
    bool FrameInit(ALLEGRO_COLOR bg = al_map_rgb(0, 0, 0));
    ~canvas();
};
