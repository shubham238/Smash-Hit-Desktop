#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <bits/stdc++.h>
#include "imageloader.h"
using namespace std;
#ifndef __OBJECTS__H__
#define __OBJECTS__H__

#define g(n) scanf("%d",&n)
// #define g(n) inp(n)
#define gl(n) scanf("%lld", &n)
#define f(i,n) for(int i=0; i<n; i++)
#define pb push_back
#define mp make_pair
#define fab(i,a,b) for(int i=a; i<=b; i++)
#define test(t) while(t--)
#define getcx getchar//_unlocked

typedef long long int lli;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector< vi > vvi;

float mod(float a);

class Point 
{
public:
    float x,y,z;
    Point(float a, float b, float c)
    {
        x=a,y=b,z=c;
    }
    Point()
    {
        x=y=z=0;
    }

    void normalize();
};

//Makes the image into a texture, and returns the id of the texture
GLuint loadTexture(Image* image);

void drawWall(Point ll, Point lr, Point ur, Point ul,  Point nor);

void drawWallTexture(Point ll, Point lr, Point ur, Point ul,  Point nor, GLuint tex_id);

void drawTriangle(Point ll, Point lr, Point ur);

class Cuboid
{
public:
	Point center;
	Point color; //color if texturing is not to be done
	float l,b,h; //length in each direction
	GLuint texture_id;
	bool isTexture; //true if texturing to be done
	float opacity; //default 1, if = 0, then dont draw

	void draw(); //draws this cuboid
};


class Pyramid
{
public:
	Point center; // coords of center of base of tetrahedron
	float length, height; //length of equilateral triangle base, height of tet
	Point color;
	bool isDisappearing;
	float opacity; //make this equal to scale
	void update(); //call this from time update
	void draw();
	
};

class Door //this can easily implement horizontal and vertical opening doors
{
public:
	float thickness, height, xinit, xw;
	bool isOpening;
	Point center;
	Point color;
	float opacity;
	float theta;
	void update(); //call from time update
	void draw();
};


class OscillatingWindow
{
public:
	float speed;
	bool isRight; //if true, then increase 
	Point center; //center of the door;
	float l,b,h;
	Cuboid *cb;
	float x;
	float opacity;
	Point color;
	bool isDisappearing;

	float xright, xleft; //these are the limits of the window, not the center of the window

	void draw();
	void update();
	void initCuboid();

};


class FlipSlab
{
public:
	Point center;
	Point color; //color if texturing is not to be done
	float l,b,h; //length in each direction
	GLuint texture_id;
	bool isTexture; //true if texturing to be done
	float opacity; //default 1, if = 0, then dont draw
	Cuboid* cb;
	
	float angle;
	bool isFalling;
	bool isRising;
	void update();
	void initCuboid();
	void draw(); //draws this cuboid
};

class vectors
{
public:
	float x, y, z;
	vectors(){x=0;y=0;z=0;};
	vectors(float u, float v, float w)
	{	x = u;
		y = v;
		z = w;};
	float mod();
	float mod(vectors a);

};

class Weapon
{
public:
	float radius; //sphere's radius
	float vx, vy, vz; 
	Point center; //center of weapon
	float gravity; 
	int numCollisions;
	GLuint texture_id;
	void update(); //updates the center of the sphere based on the velocity
	void draw();
	void collision(vectors normal);

};






float dotproduct(vectors a, vectors b);

vectors crossproduct(vectors a, vectors b);

vectors addvectors(vectors a, vectors b);

vectors subvectors(vectors a, vectors b);

vectors multscalar(float f, vectors a);

vectors multvectors(vectors a, vectors b);

vectors normalize(vectors a);


// ret = 6, 
// ret = -1 if no collision
// 0-lower, 1-right, 2-upper, 3-left, 4-back, 5-front
int ball_inter(double radius, Point center, Point cuboid_center, double l, double b, double h);

vectors reflected(vectors incident, vectors normal);

void drawText(string str, float x, float y);

string to_string(int a);

#endif
