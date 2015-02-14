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

// double globZ = 0;
// double angX = 0, angZ = 0, angY = 0;
// GLuint _textureId, floor_id;
// float opacity = 1;

// float cuboid_width = 3, cuboid_length = 5; 
// float oscx = 0;
// bool right_movement = true, left_movement = false;
// float initX = 2.5, initW = 2.5;

// Cuboid* cb, Pyramid *pr, Door *dr;

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
//     }
//     glutPostRedisplay();
// }

// void handleSpecialKeypress(int key, int x, int y)
// {
//     switch (key)
//     {
//     case GLUT_KEY_UP:
//         globZ += 0.2;
//         break;
//     case GLUT_KEY_DOWN:
//         globZ -= 0.2;
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
// GLuint loadTexture(Image* image)
// {
//     GLuint textureId;
//     glGenTextures(1, &textureId);
//     glBindTexture(GL_TEXTURE_2D, textureId);
//     glTexImage2D(GL_TEXTURE_2D,
//                  0,
//                  GL_RGB,
//                  image->width, image->height,
//                  0,
//                  GL_RGB,
//                  GL_UNSIGNED_BYTE,
//                  image->pixels);
//     return textureId;
// }


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


// void drawScene()
// {
//     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//     glMatrixMode(GL_MODELVIEW);
//     glLoadIdentity();
//     gluLookAt(0,9,25,0,9,0,0,1,0);

//     GLfloat ambientLight1[] = {0.2f, 0.2f, 0.2f, 1.0f};
//     glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight1);
//     glTranslatef(0,0,globZ);
//     glRotatef(angX, 1, 0,0);
//     glRotatef(angZ, 0,0,1);
//     glRotatef(angY,0,1,0);
//     glColor3f(0,0.5,0.7);

    
//     float ar[] = {5,6,7,3,6,5.5,6.6,8.7};
//     for(int i=0; i<8; i++)
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

//     // floor
//     drawWallTexture(Point(-1000,0,-1000), Point(-1000,0,1000), Point(1000,0,1000), Point(1000,0,-1000), Point(0,1,0), floor_id);


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
//     drawDoor(initX, initW, 8.5);
//     glPopMatrix();

//     // glPushMatrix();
//     // glTranslatef(0,5.5,0);
//     // drawDoor(initX, initW, 8.5);
//     // glPopMatrix();
    
//     glPushMatrix();
//     // glTranslatef(cuboid_width + 7.5, 2*ar[5], -2*5*cuboid_length);
//     glTranslatef(0,5,0);
//     glScalef(opacity, opacity, opacity);
//     drawTetrahedron(1);
//     glPopMatrix();

//     glPushMatrix();
//     glTranslatef(0,5,0);
//     glRotatef(180,0,0,1);
//     glScalef(opacity,opacity,opacity);
//     drawTetrahedron(1);
//     glPopMatrix();

//     glPushMatrix();
//     // glRotatef(90,0,0,1);
//     glTranslatef(oscx, 4,-25);
//     drawCuboid(3.5,6,1, 0.5);
//     glPopMatrix();

//     glutSwapBuffers();

// }

// void initRendering(void)
// {
//     globZ = 0;
//     glEnable(GL_DEPTH_TEST);
//     glEnable(GL_LIGHTING);
//     glEnable(GL_COLOR_MATERIAL);
//     glClearColor(0.2, 0.2, 0.2, 1.0);
//     Image* image = loadBMP("ball2.bmp");
//     _textureId = loadTexture(image);

//     image = loadBMP("floor.bmp");
//     floor_id = loadTexture(image);
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
//     // opacity -= 0.01;
//     if(initW >= 0.0)
//     {
//         initX += 0.02;
//         initW -= 0.02;
//     }
//     else
//         opacity -= 0.01;

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
//     glutPostRedisplay();
//     glutTimerFunc(25, time_update, 0);
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
// 	glutReshapeFunc(handleResize);
// 	glutTimerFunc(25, time_update, 0);
// 	glutMainLoop();

// 	return 0;
// }


