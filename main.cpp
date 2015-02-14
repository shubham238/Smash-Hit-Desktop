// /*
//  * main.cpp
//  *
//  *  Created on: 08-Nov-2014
//  *      Author: aakash
//  */

// #include <GL/gl.h>
// #include <GL/glu.h>
// #include <GL/glut.h>
// #include <bits/stdc++.h>
// #include "glm.h"
// #include "Objects.h"
// #include "imageloader.h"
// using namespace std;

// GLMmodel *myModel;
// OscillatingWindow *ow;
// Pyramid *pr;
// Door *dr;
// FlipSlab* fs;
// double globZ = 0;
// double angX = 0, angZ = 0, angY = 0;
// GLuint _textureId, floor_id, _metalId, _wallId;
// float opacity = 1;
// float angWindow = 0;
// float cuboid_width = 3, cuboid_length = 5; 
// float oscx = 0;
// bool right_movement = true, left_movement = false;
// float initX = 2.5, initW = 2.5;
// bool moveWeapon = false;
// vector<Weapon*> wn_list(0);

// //Cuboid* cb, Pyramid *pr, Door *dr;



// // Mouse control function
// void mouse(int state, int button, int x, int y)
// {
//     GLint viewport[4];
//     GLdouble modelview[16],projection[16];
//     GLfloat wx=x,wy,wz;
//     double ox, oy, oz;
//     if(state!=GLUT_DOWN)
//         return;
//     if(button==GLUT_RIGHT_BUTTON)
//         exit(0);
//     glGetIntegerv(GL_VIEWPORT,viewport);
//     y=viewport[3]-y;
//     wy=y;
//     glGetDoublev(GL_MODELVIEW_MATRIX,modelview);
//     glGetDoublev(GL_PROJECTION_MATRIX,projection);
//     glReadPixels(x,y,1,1,GL_DEPTH_COMPONENT,GL_FLOAT,&wz);
//     gluUnProject(wx,wy,wz,modelview,projection,viewport,&ox,&oy,&oz);
//     cout << ox << " , " << oy << " , "<< oz << endl;
//     // weapons[currentweapon]->wtarget = Point(ox,oy,oz);
//     // weapons[currentweapon]->hit = true;
//     // currentweapon += 1;
//     Point direction(ox - 0, oy - 5, oz + globZ);
//     direction.normalize();


//     Weapon* wn = new Weapon;
//     wn->radius = 1.5;
//     float factor = 3;
//     wn->vx = factor * (direction.x), wn->vy = (factor) * (direction.y), wn->vz = factor * (direction.z);
//     if(wn->vz > 0)
//         wn->vz *= -1;
//     // wn->vz = -1.3;
//     wn->center = Point(0,5,-globZ);
//     wn->gravity = 0.01;
//     wn->texture_id = _metalId;
//     wn_list.push_back(wn);
//     glutPostRedisplay();
// }
// // End Mouse control function


// // Keyboard functions
// void handleKeypress(unsigned char key, int x, int y)
// {
//     switch (key) 
//     {
//     case 27:
//         exit(0);
//     case 'w':
//         angX += 1;
//         break;
//     case 's':
//         angX -= 1;
//         break;
//     case 'a':
//         angZ += 1;
//         break;
//     case 'd':
//         angZ -= 1;
//         break;
//     case 'o':
//     	dr->isOpening = true;
//     	break;
//     case 'p':
//     	dr->isOpening = false;
//     	break;
//     case 'c':
//         angWindow += 10;
//         if(angWindow > 90)
//             angWindow = 90;
//         break;
//     case 'v':
//         angWindow -= 10;
//         if(angWindow < 0)
//             angWindow = 0;
//         break;
//     case 'f':
//         fs->isFalling = true;
//         break;
//     case 'r':
//         fs->isRising = true;
//         break;
//     case 'm':
//         moveWeapon = true;
//         break;
//     case 'n':
//         moveWeapon = false;
//         break;

//     }
//     glutPostRedisplay();
// }

// void handleSpecialKeypress(int key, int x, int y)
// {
//     switch (key)
//     {
//     case GLUT_KEY_UP:
//         globZ += 2;
//         break;
//     case GLUT_KEY_DOWN:
//         globZ -= 2;
//         break;
//     case GLUT_KEY_LEFT:
//         angY += 1;
//         break;
//     case GLUT_KEY_RIGHT:
//         angY -= 1;
//         break;
//     }

// }

// void handleSpecialKeyRelease(int key, int x, int y)
// {
//     switch(key)
//     {
//     case GLUT_KEY_UP:
//         break;
//     case GLUT_KEY_DOWN:
//         break;
//     case GLUT_KEY_LEFT:
//         break;
//     case GLUT_KEY_RIGHT:
//         break;
//     }
// }
// // end Keyboard functions

// //Makes the image into a texture, and returns the id of the texture
// // GLuint loadTexture(Image* image)
// // {
// //     GLuint textureId;
// //     glGenTextures(1, &textureId);
// //     glBindTexture(GL_TEXTURE_2D, textureId);
// //     glTexImage2D(GL_TEXTURE_2D,
// //                  0,
// //                  GL_RGB,
// //                  image->width, image->height,
// //                  0,
// //                  GL_RGB,
// //                  GL_UNSIGNED_BYTE,
// //                  image->pixels);
// //     return textureId;
// // }


// void renderObject()
//  {
//     glEnable(GL_TEXTURE_2D);
//     glBindTexture(GL_TEXTURE_2D, _textureId);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
// 	 for(int i = 0; i < myModel->numpolygons; i++)
//         {
//        	glBegin(GL_POLYGON);
//       	    GLMpolygon poly = myModel->polygons[i];
//     	    int numver = poly.numvertices;
//     	    for(int j = 0; j < numver; j++)
//     	    {
//     	    	// vertex indices
//     	    	int vi = poly.vindices[j];
//        		glNormal3f(myModel->normals[3*vi],myModel->normals[3*vi+1],myModel->normals[3*vi+2]);
//        		glVertex3f(myModel->vertices[3*vi],myModel->vertices[3*vi+1],myModel->vertices[3*vi+2]);
//        		// glTexCoord3f(myModel->vertices[3*vi],myModel->vertices[3*vi+1],myModel->vertices[3*vi+2]);
//        	    // glTexCoord2fv(myModel->texcoords[2 * (&T(myModel->groups->triangles[i]))->tindices[1]]);
//         }
//        	glEnd();
//         }
//     glDisable(GL_TEXTURE_2D);
//  }


// void readObject(char* fname)
// {
// 	myModel = (GLMmodel*)malloc(sizeof(GLMmodel));
// 	myModel = glmReadOBJ(fname);
// 	glmUnitize(myModel);
// 	glmScale(myModel, 1);
// 	// glmFacetNormals(myModel);
// 	// glmVertexNormals(myModel, 20);
// 	glmSpheremapTexture(myModel);
// }



// void drawCuboid(float x, float y, float z, float op)
// {
//     // glColor3f(1,1,1);
//     glEnable (GL_BLEND);
//     glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//     glColor4f(1,1,1, op); //lower the last param, lesser the opacity
//     // drawWall(Point(x,-y,-z), Point(x,-y,z), Point(x,y,z), Point(x,y,-z),Point(-1,0,0));
//     // drawWall(Point(-x,-y,-z), Point(-x,-y,z), Point(-x,y,z), Point(-x,y,-z),Point(1,0,0));
//     // drawWall(Point(-x,y,-z), Point(-x,y,z), Point(x,y,z), Point(x,y,-z),Point(0,1,0));
//     // drawWall(Point(-x,-y,-z), Point(-x,-y,z), Point(x,-y,z), Point(x,-y,-z),Point(0,-1,0));
//     // drawWall(Point(-x,-y,z), Point(-x,y,z), Point(x,y,z), Point(x,-y,z),Point(0,0,-1));
//     // drawWall(Point(-x,-y,-z), Point(-x,y,-z), Point(x,y,-z), Point(x,-y,-z),Point(0,0,1));
//     drawWallTexture(Point(x,-y,-z), Point(x,-y,z), Point(x,y,z), Point(x,y,-z),Point(-1,0,0),_wallId);
//     drawWallTexture(Point(-x,-y,-z), Point(-x,-y,z), Point(-x,y,z), Point(-x,y,-z),Point(1,0,0),_wallId);
//     drawWallTexture(Point(-x,y,-z), Point(-x,y,z), Point(x,y,z), Point(x,y,-z),Point(0,1,0),_wallId);
//     drawWallTexture(Point(-x,-y,-z), Point(-x,-y,z), Point(x,-y,z), Point(x,-y,-z),Point(0,-1,0),_wallId);
//     drawWallTexture(Point(-x,-y,z), Point(-x,y,z), Point(x,y,z), Point(x,-y,z),Point(0,0,-1),_wallId);
//     drawWallTexture(Point(-x,-y,-z), Point(-x,y,-z), Point(x,y,-z), Point(x,-y,-z),Point(0,0,1),_wallId);

//     glDisable(GL_BLEND);

// }


// void drawTetrahedron(float x)
// {
//     if(opacity <= 0)
//         return;
//     glEnable (GL_BLEND);
//     glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//     glColor4f(0.0,0.0,1, opacity); //lower the last param, lesser the opacity
//     if(opacity > 0)
//     {
//         // drawTriangle(Point(0,0,-x), Point(-0.8*x,0,x/2), Point(0.8*x,0,x/2));
//         // drawTriangle(Point(0,2*x,0), Point(-0.8*x,0,x/2), Point(0.8*x,0,x/2));
//         // drawTriangle(Point(0,0,-x), Point(0,2*x,0), Point(0.8*x,0,x/2));
//         // drawTriangle(Point(0,0,-x), Point(-0.8*x,0,x/2), Point(0,2*x,0) );
//         float z = x, y = 2*x;
//         drawWall(Point(-x,0,-z), Point(-x,0,z), Point(x,0,z), Point(x,0,-z), Point(0,1,0));
//         drawTriangle(Point(-x,0,-z), Point(-x,0,z), Point(0,y,0));
//         drawTriangle(Point(x,0,z), Point(-x,0,z), Point(0,y,0));
//         drawTriangle(Point(x,0,-z), Point(x,0,z), Point(0,y,0));
//         drawTriangle(Point(x,0,-z), Point(-x,0,-z), Point(0,y,0));
//     // drawTriangle(Point(1,0,0), Point(0,1,0), Point(1,1,0), Point(0,0,1));
//     }
//     glDisable(GL_BLEND);
// }

// void drawDoor(float cx, float x, float y)
// {
//     glPushMatrix();
//     glTranslatef(-cx,0,0);
//     drawCuboid(x,y,1,1);
//     glPopMatrix();

//     glPushMatrix();
//     glTranslatef(cx, 0, 0);
//     drawCuboid(x,y,1,1);
//     glPopMatrix();

// }

// void drawScene()
// {
//     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//     glMatrixMode(GL_MODELVIEW);
//     glLoadIdentity();
//     gluLookAt(0,9,25,0,9,0,0,1,0);

//     GLfloat ambientLight1[] = {1.0f, 1.0f, 1.0f, 1.0f};
//     glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight1);
//     glTranslatef(0,0,globZ);
//     glRotatef(angX, 1, 0,0);
//     glRotatef(angZ, 0,0,1);
//     glRotatef(angY,0,1,0);
//     // glColor3f(0,0.5,0.7);


//     // glPushMatrix();
//     // glTranslatef(0,10,0);
//     // glColor3f(1,1,1);
//     // glEnable(GL_TEXTURE_2D);
//     // glBindTexture(GL_TEXTURE_2D, _metalId);
//     // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//     // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//     // GLUquadricObj *q = gluNewQuadric();
//     // gluQuadricDrawStyle(q, GLU_FILL); //try using different params...
//     // gluQuadricNormals(q, GLU_SMOOTH); /* smooth shaded */
//     // gluQuadricOrientation(q, GLU_OUTSIDE);
//     // gluQuadricTexture(q,1);
//     // gluSphere(q, 1, 25, 25);
//     // gluDeleteQuadric(q);
//     // glDisable(GL_TEXTURE_2D);
//     // glPopMatrix();

//     glPushMatrix();
//     // glColor3f(1,0,0);
//     glRotatef(170,0,1,0);
//     glTranslatef(0,5,-5);
//     // renderObject();
//     glPopMatrix();
    
//     Cuboid* cb = new Cuboid;
//     cb->center = Point(0,0,0);
//     cb->color = Point(0, 0.2, 0.8);
//     cb->l = 8, cb->b = 10, cb->h = 0.15;
//     cb->isTexture = true;
//     cb->opacity = 0.8;
//     cb->texture_id = _textureId;
//     glPushMatrix();
//     // glTranslatef()
//     glTranslatef(0,5,5);
//     // glRotatef(-angWindow, 1,0,0);
//     // if(90-angWindow <= 0.01){}
//     // glTranslatef(0,-4,5);
//     // else
//     // cb->draw();

//     glPopMatrix();

//     glPushMatrix();
//     float ar[] = {1,2,3,4,5,6,7,3,6,5.5,6.6,8.7,5,6,7,3,6,5.5,6.6,8.7,5,6,7,3,6,5.5,6.6,8.7,3,6,5.5,6.6,8.7,5,6,3,6,5.5,6.6,8.7,5,6,5,6,7,3,6,5.5,6.6,8.7,5,6,7,3,6,5.5,6.6,8.7,5,6,7,3,6,5.5,6.6,8.7,3,6,5.5,6.6,8.7,5,6,3,6,5.5,6.6,8.7,5,6,8.7,5,6,3,6,5.5,6.6,8.7,5,6,8.7,5,6,3,6,5.5,6.6,8.7,5,6};
//     for(int i=0; i<100; i++)
//     {
//         glPushMatrix();
//         glTranslatef(-cuboid_width-7.5, ar[i], - 2*i*cuboid_length);
//         drawCuboid(cuboid_width, ar[i], cuboid_length, 0.8);
//         glPopMatrix();

//         glPushMatrix();
//         glTranslatef(cuboid_width+7.5, ar[i], - 2*i*cuboid_length);
//         drawCuboid(cuboid_width, ar[i], cuboid_length, 1);
//         glPopMatrix();
//     }
//     glPopMatrix();



//     glPushMatrix();
//     glColor3f(0.7,0.5,0.7);
//     glTranslatef(-cuboid_width-7.5,ar[7],-2*7*cuboid_length);
//     glTranslatef(0,2+ar[7],0);
//     glutSolidSphere(2,25,25);
//     glPopMatrix();
//     // drawCuboid(4,4,1);
    

// //    glmDraw(myModel,GLM_NONE);
// //    glutWireSphere(0.5,500,500);
//     glPushMatrix();
//     glTranslatef(0,5.5,0);
//     // glRotatef(90,0,0,1);
//     // drawDoor(initX, initW, 8.5);
//     glPopMatrix();

//     // glPushMatrix();
//     // glTranslatef(0,5.5,0);
//     // drawDoor(initX, initW, 8.5);
//     // glPopMatrix();
//     glPushMatrix();
//     // glColor3f(0,0.2,0.6);
//     drawWallTexture(Point(-1000,0,-1000), Point(-1000,0,1000), Point(1000,0,1000), Point(1000,0,-1000), Point(0,1,0), floor_id);
//     glPopMatrix();




//     glPushMatrix();
//     // glTranslatef(0,fs->b/2,0);
//     // glRotatef(180,0,0,1);
//     fs->draw();
//     glPopMatrix();


//     glPushMatrix();
//     // glTranslatef(cuboid_width + 7.5, 2*ar[5], -2*5*cuboid_length);
//     glTranslatef(0,5,0);
//     glScalef(opacity, opacity, opacity);
//     drawTetrahedron(1);
//     glPopMatrix();

//     // glPushMatrix();
//     // glTranslatef(0,5,0);
//     // glRotatef(180,0,0,1);
//     // glScalef(opacity,opacity,opacity);
//     // drawTetrahedron(1);
//     // glPopMatrix();

//     glPushMatrix();
//     // glRotatef(90,0,0,1);
//     glTranslatef(oscx, 4,-25);
//     // drawCuboid(3.5,6,1, 0.5);
//     glPopMatrix();



//     // pr->draw();
//     dr->draw();
//     // ow->draw();
//     f(i,wn_list.size())
//     wn_list[i]->draw();
  
//     glutSwapBuffers();

// }

// void initRendering(void)
// {
//     GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
//    GLfloat mat_shininess[] = { 10.0 };
//    GLfloat light_position[] = { 1, 1, 1, 0.0 };
//    glClearColor (0.0, 0.0, 0.0, 0.0);
//    glShadeModel (GL_SMOOTH);

//    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
//    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
//    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
//     globZ = 0;
//     glEnable(GL_DEPTH_TEST);
//     glEnable(GL_LIGHTING);
//     glEnable(GL_LIGHT0);
//     glEnable(GL_COLOR_MATERIAL);
//     // glClearColor(0.2, 0.2, 0.2, 1.0);
//     Image* image = loadBMP("glossy.bmp");
//     _textureId = loadTexture(image);

//     image = loadBMP("floor2.bmp");
//     floor_id = loadTexture(image);

//     image = loadBMP("metallic.bmp");
//     _metalId = loadTexture(image);

//     image = loadBMP("walltile.bmp");
//     _wallId = loadTexture(image);


//     pr = new Pyramid;
//     pr->center = Point(0,7.5,4);
//     pr->length = 1.5, pr->height = 3.3;
//     pr->color = Point(0,0.4,0.9);
//     pr->isDisappearing = false;
//     pr->opacity = 1.0;

//     dr = new Door;
//     dr->thickness = 1, dr->height = 7.5; dr->xinit =  dr->xw = 2;
//     dr->isOpening = false; dr->center = Point(0,5,10);
//     dr->color = Point(0.0, 0.5, 1.0);
//     dr->opacity = 0.5;

//     ow = new OscillatingWindow;
//     ow->speed = 0.2;
//     ow->isRight = true;
//     ow->center = Point(0,2.5,15);
//     ow->l = 3, ow->b = 5, ow->h = 1;
//     ow->x = 0;
//     ow->opacity = 0.7;
//     ow->color = Point(0,0.8,0.9);
//     ow->initCuboid();
//     ow->xright = 4, ow->xleft = -4;

//     fs = new FlipSlab;
//     fs->center = Point(0,0,-45);
//     fs->color = Point(1,0,0);
//     fs->opacity = 0.5;
//     fs->l = 14;
//     fs->b = 18;
//     fs->h = 0.3;
//     fs->isTexture = false;
//     fs->initCuboid();
//     fs->angle = 0;
//     fs->isFalling = false;
//     fs->isRising = false;

//     // wn = new Weapon;
//     // wn->radius = 0;
//     // wn->vx = 0.2, wn->vy = 1, wn->vz = -0.1;
//     // wn->center = Point(0,5,0);
//     // wn->gravity = 0.01;
//     // wn->texture_id = _metalId;


// }


// void handleResize(int w, int h)
// {
//     glViewport(0, 0, w, h);
//     glMatrixMode(GL_PROJECTION);
//     glLoadIdentity();
//     gluPerspective(45.0, (float)w / (float)h, 1.0, 200.0);
//     glMatrixMode(GL_MODELVIEW);
//     glLoadIdentity();
//     glTranslatef(0.0, 0.0, -5.0);

// }

// //Called every 25 milliseconds
// void time_update(int value) 
// {
//     globZ += 0.5;
//     // opacity -= 0.01;
//     if(initW >= 0.0)
//     {
//         initX += 0.02;
//         initW -= 0.02;
//     }
//     else
//     {
//         pr->isDisappearing = true;
//         //dr->isOpening = true;
//         opacity -= 0.01;
//     }

//     if(right_movement)
//     {
//         oscx += 0.03;
//         if(oscx > 4)
//             right_movement = false, left_movement = true, oscx -= 0.03;
//     }
//     else
//     {
//         oscx -= 0.03;
//         if(oscx < -4)
//             right_movement = true, left_movement = false, oscx += 0.03;
//     }
//     pr->update();
//     dr->update();
//     ow->update();
//     fs->update();
//     // if(moveWeapon)
//         // wn->update();
//     f(i,wn_list.size())
//         wn_list[i]->update();
//     angWindow += 1;
//     glutPostRedisplay();
//     glutTimerFunc(10, time_update, 0);
// }



// int main(int argc, char** argv)
// {
// 	myModel = (GLMmodel*)malloc(sizeof(GLMmodel));
// 	readObject("bullet.obj");

// 	glutInit(&argc, argv);
// 	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
// 	glutInitWindowSize(1000, 1000);
// 	glutCreateWindow("Object Rendering");

// 	initRendering();

// 	glutDisplayFunc(drawScene);
// 	glutKeyboardFunc(handleKeypress);
// 	glutSpecialFunc(handleSpecialKeypress);
// //	glutSpecialUpFunc(handleSpecialKeyRelease);
//     glutMouseFunc(mouse);
// 	glutReshapeFunc(handleResize);
// 	glutTimerFunc(10, time_update, 0);
// 	glutMainLoop();

// 	return 0;
// }


