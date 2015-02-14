#include "Objects.h"
using namespace std;


float mod(float a)
{
	if(a<0)
		return -a;
	return a;
}


void Point::normalize()
{
	float mod = x*x + y*y + z*z;
	if(mod==0)
		return;
	mod = sqrt(mod);
	x/=mod, y/=mod, z/=mod;
}


//Makes the image into a texture, and returns the id of the texture
GLuint loadTexture(Image* image)
{
    GLuint textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGB,
                 image->width, image->height,
                 0,
                 GL_RGB,
                 GL_UNSIGNED_BYTE,
                 image->pixels);
    return textureId;
}


void drawWall(Point ll, Point lr, Point ur, Point ul,  Point nor)
{
    glPushMatrix();
    glBegin(GL_POLYGON);
    glVertex3f(ll.x, ll.y, ll.z);
    glVertex3f(lr.x, lr.y, lr.z);
    glVertex3f(ur.x, ur.y, ur.z);
    glVertex3f(ul.x, ul.y, ul.z);
    glEnd();
    glPopMatrix();
}

void drawWallTexture(Point ll, Point lr, Point ur, Point ul,  Point nor, GLuint tex_id)
{
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBegin(GL_POLYGON);
    glNormal3f(nor.x, nor.y, nor.z);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(ll.x, ll.y, ll.z);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(lr.x, lr.y, lr.z);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(ur.x, ur.y, ur.z);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(ul.x, ul.y, ul.z);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void drawTriangle(Point ll, Point lr, Point ur)
{
    glPushMatrix();
    glBegin(GL_POLYGON);
    glVertex3f(ll.x, ll.y, ll.z);
    glVertex3f(lr.x, lr.y, lr.z);
    glVertex3f(ur.x, ur.y, ur.z);
    glEnd();
    glPopMatrix();
}


void Cuboid::draw()
{
	float x = l/2, y = b/2, z = h/2;

	glPushMatrix();
	glTranslatef(center.x, center.y, center.z);
	if(!isTexture)
	{
		glEnable (GL_BLEND);
	    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	    glColor4f(color.x,color.y,color.z, opacity); //lower the last param, lesser the opacity
	    drawWall(Point(x,-y,-z), Point(x,-y,z), Point(x,y,z), Point(x,y,-z),Point(-1,0,0));
	    drawWall(Point(-x,-y,-z), Point(-x,-y,z), Point(-x,y,z), Point(-x,y,-z),Point(1,0,0));
	    drawWall(Point(-x,y,-z), Point(-x,y,z), Point(x,y,z), Point(x,y,-z),Point(0,1,0));
	    drawWall(Point(-x,-y,-z), Point(-x,-y,z), Point(x,-y,z), Point(x,-y,-z),Point(0,-1,0));
	    drawWall(Point(-x,-y,z), Point(-x,y,z), Point(x,y,z), Point(x,-y,z),Point(0,0,1));
	    drawWall(Point(-x,-y,-z), Point(-x,y,-z), Point(x,y,-z), Point(x,-y,-z),Point(0,0,1));
	    glDisable(GL_BLEND);
	
	}

	else
	{
		glEnable (GL_BLEND);
	    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	    glColor4f(color.x,color.y,color.z, opacity);
		drawWallTexture(Point(x,-y,-z), Point(x,-y,z), Point(x,y,z), Point(x,y,-z),Point(-1,0,0), texture_id);
	    drawWallTexture(Point(-x,-y,-z), Point(-x,-y,z), Point(-x,y,z), Point(-x,y,-z),Point(1,0,0), texture_id);
	    drawWallTexture(Point(-x,y,-z), Point(-x,y,z), Point(x,y,z), Point(x,y,-z),Point(0,1,0), texture_id);
	    drawWallTexture(Point(-x,-y,-z), Point(-x,-y,z), Point(x,-y,z), Point(x,-y,-z),Point(0,-1,0), texture_id);
	    drawWallTexture(Point(-x,-y,z), Point(-x,y,z), Point(x,y,z), Point(x,-y,z),Point(0,0,1), texture_id);
	    drawWallTexture(Point(-x,-y,-z), Point(-x,y,-z), Point(x,y,-z), Point(x,-y,-z),Point(0,0,1), texture_id);
		glDisable(GL_BLEND);
	}
    glPopMatrix();
}


void Pyramid::update()
{
	if(isDisappearing)
		opacity -= 0.05;
}

void Pyramid::draw()
{

	glPushMatrix();
	glTranslatef(center.x, center.y, center.z);
	float x = length/2, z = length/2, y = height;
	if(opacity > 0)
	{
		// printf("YYY %f\n",opacity);
		// glScalef(opacity, opacity, opacity);
	    glEnable (GL_BLEND);
	    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	    glColor4f(color.x, color.y, color.z, opacity); //lower the last param, lesser the opacity
        // drawTriangle(Point(0,0,-x), Point(-0.8*x,0,x/2), Point(0.8*x,0,x/2)); //base
        // drawTriangle(Point(0,2*x,0), Point(-0.8*x,0,x/2), Point(0.8*x,0,x/2));
        // drawTriangle(Point(0,0,-x), Point(0,2*x,0), Point(0.8*x,0,x/2));
        // drawTriangle(Point(0,0,-x), Point(-0.8*x,0,x/2), Point(0,2*x,0) );
	    drawWall(Point(-x,0,-z), Point(-x,0,z), Point(x,0,z), Point(x,0,-z), Point(0,1,0));
	    drawTriangle(Point(-x,0,-z), Point(-x,0,z), Point(0,y,0));
	    drawTriangle(Point(x,0,z), Point(-x,0,z), Point(0,y,0));
	    drawTriangle(Point(x,0,-z), Point(x,0,z), Point(0,y,0));
	    drawTriangle(Point(x,0,-z), Point(-x,0,-z), Point(0,y,0));
	    // glPushMatrix();
	    // glTranslatef(0,y/3,0);
	    // // float loc[] = {0,y/3}
	    // float temp_color[] = {1, 0, color.z};
	    // glLightfv(GL_LIGHT2, GL_DIFFUSE, temp_color);
	    // glLightfv(GL_LIGHT2, GL_SPECULAR, temp_color);
	    // // glLightfv(GL_LIGHT2, GL_POSITION, loc);
	    // glPopMatrix();
	    glDisable(GL_BLEND);
	}
	glPopMatrix();

}


void Door::update()
{
	if(xw >= 0.0 && isOpening)
	{
		xinit += 0.01;
		xw -= 0.01;
	}
}



void Door::draw()
{
	Cuboid* c = new Cuboid;
	c->center = Point(0,0,0);
	c->color = color;
	c->isTexture = false;
	c->opacity = opacity;
	c->l = 2*xw, c->b = height, c->h = thickness;
    glPushMatrix();
    glTranslatef(center.x, center.y, center.z);
    glTranslatef(-xinit,0,0);
    // glRotatef(theta, 1,0,0);
    c->draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(center.x, center.y, center.z);
    glTranslatef(xinit, 0, 0);
    c->draw();
    glPopMatrix();

    // glPushMatrix();
    // glTranslatef(center.x-2*xinit, center.y-height/2, center.z);
    // glTranslatef(0,0,25);
    // glColor3f(1,0,0);
    // GLUquadricObj *q = gluNewQuadric();
    // gluQuadricDrawStyle(q, GLU_FILL); //try using different params...
    // gluQuadricNormals(q, GLU_SMOOTH); /* smooth shaded */
    // gluQuadricOrientation(q, GLU_OUTSIDE);
    // gluQuadricTexture(q,1);
    // glPushMatrix();
    // glRotatef(theta,0,1,0);
    // gluCylinder(q, 0.4,0.4,height, 25, 25);
    // glPopMatrix();
    // gluDeleteQuadric(q);
    // glPopMatrix();


}


void OscillatingWindow::update()
{
	if(isRight)
	{
		x += speed;
		if(x > xright)
			x-=speed, isRight = false;
	}
	else
	{
		x-=speed;
		if(x < xleft)
			x += speed, isRight = true;
	}
	if(isDisappearing)
		opacity -= 0.075;

}

void OscillatingWindow::draw()
{
	glPushMatrix();

	glTranslatef(center.x, center.y, center.z);
	glTranslatef(x,0,0);
	if(opacity > 0)
		cb->draw();
	glPopMatrix();
}



void OscillatingWindow::initCuboid()
{
	cb = new Cuboid;
	cb->center = Point(0,0,0);
	cb->l = l, cb->b = b, cb->h = h;
	cb->color = color;
	cb->opacity = opacity;
	cb->isTexture = false;
}


void FlipSlab::update()
{
	if(isFalling)
		angle += 0.05;
	if(angle > 90)
		angle = 90, isFalling = false;
	if(isRising)
		angle -= 10;
	if(angle < 0)
		angle = 0, isRising = false;
}

void FlipSlab::initCuboid()
{
	cb = new Cuboid;
	cb->center = Point(0,0,0);
	cb->l = l, cb->b = b, cb->h = h;
	cb->color = color;
	cb->opacity = opacity;
	cb->isTexture = false;
}

void FlipSlab::draw()
{
	glPushMatrix();
	glTranslatef(0,0,center.z);
	if(center.z > 0)
		glRotatef(-angle, 1, 0, 0);
	else
		glRotatef(angle, 1, 0, 0);
	if(90-angle <= 0.01){}
	else cb->draw();
	glPopMatrix();
}


void Weapon::update()
{
	vy -= gravity;
	center.x += vx;
	center.y += vy;
	center.z += vz;

	if(numCollisions >= 8)
		radius = 0;
	if(center.x >= 40 || center.x <= -40)
		radius = 0;
	if(center.y >= 60)
		radius = 0;
}

void Weapon::collision(vectors normal)
{
	numCollisions++;
	if(normal.x == 0 && normal.y == 0 && normal.z == 0)
		vx *= -1, vy *= -1, vz *= -1;
	vectors incident = multscalar(-1, vectors(vx,vy,vz));
	float speed = incident.mod();
	vectors ref = reflected(incident, normal);
	ref = multscalar(speed*0.9, ref);
	vx = ref.x, vy = ref.y, vz = ref.z;

}

void Weapon::draw()
{
	glPushMatrix();
    glTranslatef(center.x, center.y, center.z);
    glColor3f(1,1,1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    GLUquadricObj *q = gluNewQuadric();
    gluQuadricDrawStyle(q, GLU_FILL); //try using different params...
    gluQuadricNormals(q, GLU_SMOOTH); /* smooth shaded */
    gluQuadricOrientation(q, GLU_OUTSIDE);
    gluQuadricTexture(q,1);
    gluSphere(q, radius, 25, 25);
    gluDeleteQuadric(q);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

// ret = 6, means you're way outta line
// ret = -1, then chill hai
// 0-lower, 1-right, 2-upper, 3-left, 4-back, 5-front
// l,b,h are the dimensions of the cuboid
int ball_inter(double radius, Point center, Point cuboid_center, double l, double b, double h)
{
	double ax = l/2, ay=b/2, az=h/2;
	// center of sphere wrt center of cuboid
	center = Point(center.x - cuboid_center.x, center.y - cuboid_center.y, center.z - cuboid_center.z);
	if(center.x < ax && center.x > -ax && center.y > -ay && center.y < ay && center.z < az && center.z > -az)
		return 6;

	// now we know that the sphere ain't inside the cuboid
	if(mod(center.y + ay) <= radius && center.x >= -ax-radius && center.x <= ax+radius && center.z >= -az-radius && center.z <= az+radius) //lower
		return 0;
	if(mod(ax  - center.x) <= radius && center.y >= -ay-radius && center.y <= ay+radius && center.z >= -az-radius && center.z <= az+radius) //rigt
		return 1;
	if(mod(ay - center.y) <= radius && center.x >= -ax-radius && center.x <= ax+radius && center.z >= -az-radius && center.z <= az+radius)
		return 2;
	if(mod(center.x + ax) <= radius && center.y >= -ay-radius && center.y <= ay+radius && center.z >= -az-radius && center.z <= az+radius)
		return 3;
	if(mod(az - center.z) <= radius && center.x >= -ax-radius && center.x <= ax+radius && center.y >= -ay-radius && center.y <= ay+radius)
		return 4;
	if(mod(center.z + az) <= radius && center.x >= -ax-radius && center.x <= ax+radius && center.y >= -ay-radius && center.y <= ay+radius)
		return 5;
	return -1;
}

vectors reflected(vectors incident, vectors normal)
{
	incident = normalize(incident);
	normal =  normalize(normal);
	vectors ref = multscalar(2*dotproduct(incident,normal), normal);
	ref = subvectors(ref, incident);
	return normalize(ref);
}


float vectors::mod()
{
	return sqrt(x*x+y*y+z*z);
}
float vectors::mod(vectors a)
{
	return sqrt(a.x*a.x+a.y*a.y+a.z*a.z);
}

float dotproduct(vectors a, vectors b)
{
	return ((a.x*b.x)+(a.y*b.y)+(a.z*b.z));
}

vectors crossproduct(vectors a, vectors b)
{
	float cx = a.y*b.z - b.y*a.z;
	float cy = b.x*a.z - b.z*a.x;
	float cz = a.x*b.y - a.y*b.x;
	vectors c = vectors(cx, cy, cz);
	return c;
}

vectors addvectors(vectors a, vectors b)
{
	float vx = a.x+b.x;
	float vy = a.y+b.y;
	float vz = a.z+b.z;
	vectors v = vectors(vx, vy, vz);
	return v;
}

vectors subvectors(vectors a, vectors b)
{
	float vx = a.x-b.x;
	float vy = a.y-b.y;
	float vz = a.z-b.z;
	vectors v = vectors(vx, vy, vz);
	return v;
}

vectors multscalar(float f, vectors a)
{
	float vx = f*a.x;
	float vy = f*a.y;
	float vz = f*a.z;
	vectors v = vectors(vx, vy, vz);
	return v;
}

vectors multvectors(vectors a, vectors b)
{
	float vx = a.x*b.x;
	float vy = a.y*b.y;
	float vz = a.z*b.z;
	vectors v = vectors(vx, vy, vz);
	return v;
}

vectors normalize(vectors a)
{
	if(a.mod()==0.0)
		return a;
	float m = a.mod();
	return multscalar(1.0/m,a);
}

void drawText(string str, float x, float y)
{
   glPushMatrix();
   glMatrixMode(GL_PROJECTION);
   glPushMatrix();
   glLoadIdentity();
   gluOrtho2D(0, 1000, 0, 1000);
   glTranslatef(x,y,0);
   glMatrixMode(GL_MODELVIEW);
   glPushMatrix();
   glLoadIdentity();
   // glColor3f(1.0f, 0.0f, 0.0f);//needs to be called before RasterPos
   std::string s = str;
   void * font = GLUT_STROKE_MONO_ROMAN;
   glScalef(.15,.15,.15);
   for (std::string::iterator i = s.begin(); i != s.end(); ++i)
   {
	   char c = *i;
	   glutStrokeCharacter(font, c);
	   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   }
   glMatrixMode(GL_MODELVIEW);
   glPopMatrix();
   glMatrixMode(GL_PROJECTION);
   glPopMatrix();
   glPopMatrix();
}


string to_string(int a)
{
	string ret = "";
	while(a>0)
	{
		char ch = (a%10) + '0';
		ret = ch + ret;
		a/=10;
	}
	return ret;
}
