/*
 * main.cpp
 *
 *  Created on: 08-Nov-2014
 *      Author: aakash
 */

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <bits/stdc++.h>
#include <unistd.h>
#include "glm.h"
#include "Objects.h"
#include "imageloader.h"
using namespace std;

bool gameStart = false;

int refresh_rate = 25;
// bool startGame = true;
bool endingGame = false;
int available_weapons = 25;
float udt_count = 0;
float prev_click = 0;
int clicks = 0;
GLMmodel *myModel;
bool mypause;
double z_global = 0;
double angX = 0, angZ = 0, angY = 0; //this is for rotation of view port, for debugging purposes
GLuint _textureId, floor_id, _metalId, _wallId, _startId, _exitId;
vectors plane_normals[7];
float heights[2000];
bool printscore = false;
// float opacity = 1;
// float angWindow = 0;
const float cuboid_width = 10, cuboid_length = 10, y_offset = 15; //width and length of cuboids to be placed on sides
const float weapon_radius = 1.0; //radius of weapon
const float const_gravity = 0.01;
// Objects
vector<Cuboid*> l_cuboid(0);
vector<Weapon*> l_weapons(0);
vector<OscillatingWindow*> l_oscWindow(0);
vector<Pyramid*> l_pyramid(0);
vector<Door*> l_door(0);
vector<FlipSlab*> l_flipSlab(0);
// End Objects

Cuboid *strt_cuboid, *exit_cuboid;

float global_size = 1000;

// score
long long int score = 0;


float getRand(float LO, float HI)
{
	float r3 = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
	return r3;
}

void gameOver()
{
    score += available_weapons * 1000;
    string highscore;
    ifstream readfile;
    readfile.open("highscores.txt");
    getline(readfile, highscore);
    istringstream iss(highscore);
    int hscore;
    if(!(iss >> hscore))
    	{exit;}
    if(score > hscore)
    	printscore = true;
    mypause = true;
    endingGame = true;
    glutPostRedisplay();
}

// Mouse control function
void mouse(int state, int button, int x, int y)
{
    float diff = udt_count - prev_click;
    if( diff <= 0.1)
        return;
    if(available_weapons == 0)
        gameOver();
    available_weapons--;
    clicks++;
    printf("clicks = %d, time = %f, prev_click = %f\n",clicks,udt_count,prev_click);
    prev_click = udt_count;
    GLint viewport[4];
    GLdouble modelview[16],projection[16];
    GLfloat wx=x,wy,wz;
    double ox, oy, oz;
    if(state!=GLUT_DOWN)
        return;
    if(button==GLUT_RIGHT_BUTTON)
        exit(0);
    glGetIntegerv(GL_VIEWPORT,viewport);
    y=viewport[3]-y;
    wy=y;
    glGetDoublev(GL_MODELVIEW_MATRIX,modelview);
    glGetDoublev(GL_PROJECTION_MATRIX,projection);
    glReadPixels(x,y,1,1,GL_DEPTH_COMPONENT,GL_FLOAT,&wz);
    gluUnProject(wx,wy,wz,modelview,projection,viewport,&ox,&oy,&oz);
    // cout << ox << " , " << oy << " , "<< oz << endl;
    Point direction(ox - 0, oy - 9, oz + z_global - 25);
    direction.normalize();


    Weapon* wn = new Weapon;
    wn->radius = weapon_radius;
    float factor = 3;
    wn->vx = factor * (direction.x), wn->vy = (factor) * (direction.y), wn->vz = factor * (direction.z);
    if(wn->vz > 0)
        wn->vz *= -1;
    // wn->vz = -1.3;
    wn->center = Point(0,9,-z_global+25);
    wn->gravity = const_gravity;
    wn->texture_id = _metalId;
    wn->numCollisions = 0;
    l_weapons.push_back(wn);

    glutPostRedisplay();
}
// End Mouse control function




// Keyboard functions
void handleKeypress(unsigned char key, int x, int y)
{
    switch (key) 
    {
    case 27:
        exit(0);
    case 'w':
        angX += 1;
        break;
    case 's':
        angX -= 1;
        break;
    case 'a':
        angZ += 1;
        break;
    case 'd':
        angZ -= 1;
        break;
    case 'p':
        mypause = !mypause;
        break;
    case 'x':
        l_door[0]->theta += 1;
        break;
    case 'c':
        l_door[0]->theta -= 1;
        break;
    // case 'o':
    // 	dr->isOpening = true;
    // 	break;
    // case 'p':
    // 	dr->isOpening = false;
    // 	break;
    // case 'c':
    //     angWindow += 10;
    //     if(angWindow > 90)
    //         angWindow = 90;
    //     break;
    // case 'v':
    //     angWindow -= 10;
    //     if(angWindow < 0)
    //         angWindow = 0;
    //     break;
    // case 'f':
    //     fs->isFalling = true;
    //     break;
    // case 'r':
    //     fs->isRising = true;
    //     break;
    // case 'm':
    //     moveWeapon = true;
    //     break;
    // case 'n':
    //     moveWeapon = false;
    //     break;

    }
    glutPostRedisplay();
}

void handleSpecialKeypress(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP:
        z_global += 2;
        break;
    case GLUT_KEY_DOWN:
        z_global -= 2;
        break;
    case GLUT_KEY_LEFT:
        angY += 1;
        break;
    case GLUT_KEY_RIGHT:
        angY -= 1;
        break;
    }

}

void handleSpecialKeyRelease(int key, int x, int y)
{
    switch(key)
    {
    case GLUT_KEY_UP:
        break;
    case GLUT_KEY_DOWN:
        break;
    case GLUT_KEY_LEFT:
        break;
    case GLUT_KEY_RIGHT:
        break;
    }
}
// end Keyboard functions



void drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,9,25-z_global,0,9,-z_global,0,1,0);

    GLfloat ambientLight1[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight1);

    GLfloat fogColor[] = {0.5f, 0.5f, 0.5f, 1};
    glFogfv(GL_FOG_COLOR, fogColor);
    glFogi(GL_FOG_MODE, GL_LINEAR);
    glFogf(GL_FOG_START, 10.0f);
    glFogf(GL_FOG_END, 20.0f);
    glDisable(GL_FOG);
    // glTranslatef(0,-9,-25);
    // glTranslatef(0,0,z_global);
    glRotatef(angX, 1, 0,0);
    glRotatef(angZ, 0,0,1);
    glRotatef(angY,0,1,0);
    

    // draw opaque things first
    
    glPushMatrix();
    // glColor3f(1,0,0);
    drawText("Score: ",800,900);
    drawText(to_string(score),900,900);
    drawText("Weapons: ", 400, 900);
    drawText(to_string(available_weapons), 550,900);
    if(endingGame)
    {
        glPushMatrix();
        glScalef(2,2,2);
        drawText("Game Over :D", 400, 800);
        glPopMatrix();
    }
    if(mypause && !endingGame)
    {
        drawText("Paused", 450, 500);
    }
    glColor3f(1,1,1);
    glPopMatrix();
    // end text

	//drawing floor
	glPushMatrix();
    // drawWallTexture(Point(-1000,0,-1000), Point(-1000,0,1000), Point(1000,0,1000), Point(1000,0,-1000), Point(0,1,0), floor_id);
    drawWallTexture(Point(-global_size,0,-global_size), Point(-global_size,0,global_size), Point(global_size,0,global_size), Point(global_size,0,-global_size), Point(0,1,0), floor_id);
    glPopMatrix();
	//end floor code 

    if(!gameStart)
    {
        // create dabbas
        // printf("KKKKKK\n");
        glPushMatrix();
        strt_cuboid->draw();
        exit_cuboid->draw();
        glPopMatrix();
    }
    else
    {

    
        // drawing cuboids on sides
        f(i,l_cuboid.size())
        	l_cuboid[i]->draw();
        // ending cuboids on sides

        


        // oscillating windows
        f(i,l_oscWindow.size())
        	l_oscWindow[i]->draw();
       	
       	// pyramids
       	f(i,l_pyramid.size())
        {
            glColor3f(1,1,1);
       		l_pyramid[i]->draw();
        }

       	// doors
       	f(i,l_door.size())
       		l_door[i]->draw();

       	// flipping glass slabs
       	f(i,l_flipSlab.size())
       		l_flipSlab[i]->draw();
        
        // weapons
        

        if(printscore==true)
    	{
    		drawText("CONGRATS HIGHSCORE",400,500);
    		ofstream writefile;
    		writefile.open("highscores.txt");
    		writefile << score <<endl;
    		writefile.close();

    	}
    }
    f(i,l_weapons.size())
            l_weapons[i]->draw();
    
    glutSwapBuffers();

}



// side cuboids
void intiCuboids()
{
	
    int tf = 1;
	f(i,tf*200) heights[i] = getRand(2.0,8.0);

	f(i,tf*100)
	{

		Cuboid* cb = new Cuboid;
		cb->center = Point(-(cuboid_width/2)- y_offset, heights[i]/2, -i*cuboid_length);
		cb->color = Point(1,1,1);
		cb->l = cuboid_width, cb->b = heights[i], cb->h = cuboid_length;
		cb->isTexture = true;
		cb->texture_id = _wallId;
		cb->opacity = 1;
		l_cuboid.push_back(cb);

		cb = new Cuboid;
		cb->center = Point(cuboid_width/2 + y_offset, (heights[i])/2, -i*cuboid_length);
		cb->color = Point(1,1,1);
		cb->l = cuboid_width, cb->b = heights[i], cb->h = cuboid_length;
		cb->isTexture = true;
		cb->texture_id = _wallId;
		cb->opacity = 1;
		l_cuboid.push_back(cb);
        
	}

	f(i,tf*100)
	{
		int j = tf*100+i;
		Cuboid* cb = new Cuboid;
		cb->center = Point(-(cuboid_width/2)- y_offset, heights[j]/2, i*cuboid_length);
		cb->color = Point(1,1,1);
		cb->l = cuboid_width, cb->b = heights[j], cb->h = cuboid_length;
		cb->isTexture = true;
		cb->texture_id = _wallId;
		cb->opacity = 1;
		l_cuboid.push_back(cb);

		cb = new Cuboid;
		cb->center = Point(cuboid_width/2 + y_offset, heights[j]/2, i*cuboid_length);
		cb->color = Point(1,1,1);
		cb->l = cuboid_width, cb->b = heights[j], cb->h = cuboid_length;
		cb->isTexture = true;
		cb->texture_id = _wallId;
		cb->opacity = 1;
		l_cuboid.push_back(cb);
        
	}
}
// end side cuboids

// weapon collision code
void weapon_collision_detection()
{
    if(!gameStart)
    {
        f(i,l_weapons.size())
        {
            Weapon* wn = l_weapons[i];
            Cuboid* cb = strt_cuboid;
            int it = ball_inter(wn->radius, wn->center, cb->center, cb->l, cb->b, cb->h);
            if(it==-1)
            {
                // printf("Chill hai\n");
                // continue;
            }
            else 
            {
                gameStart = true;
                available_weapons = 25;
                l_weapons.clear();
                return;
                // cout << "Colliding Cuboid "<<i << endl;
                // wn->collision(plane_normals[i]);
            }

            cb = exit_cuboid;
            it = ball_inter(wn->radius, wn->center, cb->center, cb->l, cb->b, cb->h);
            if(it==-1)
            {
                // printf("Chill hai\n");
                continue;
            }
            else
            {
                printf("Tada\n");
                exit(0);
                // cout << "Colliding Cuboid "<<i << endl;
                // wn->collision(plane_normals[i]);
            }
        }
        return;
    }
    vector<Weapon*> nlist(0);
    f(i,l_weapons.size())
    {
        Weapon* wn = l_weapons[i];

        // cuboids on sides
        f(j,l_cuboid.size())
        {
            Cuboid* cb = l_cuboid[j];
            int it = ball_inter(wn->radius, wn->center, cb->center, cb->l, cb->b, cb->h);
            if(it==-1)
            {
                // printf("Chill hai\n");
                continue;
            }
            else if(it==6)
            {
                printf("Colliding Cuboid\n");
                wn->collision(vectors(0,0,0));
            }
            else
            {
                cout << "Colliding Cuboid "<<i << endl;
                wn->collision(plane_normals[i]);
            }
        }

       

        // floor
        if (wn->center.y <= wn->radius)
        {
            printf("Colliding floor\n");
            wn->collision(vectors(0,1,0));
            wn->vx *= 0.1, wn->vy *= 0.1, wn->vz *= 0.1;
        }
        
        // pyramid
        f(j,l_pyramid.size())
        {
            Pyramid* pr = l_pyramid[j];
            if(pr->isDisappearing)
                continue;
            Point temp_cen(pr->center.x, pr->center.y + (pr->height)/2, pr->center.z);
            int it = ball_inter(wn->radius, wn->center, temp_cen, pr->length, pr->height, pr->length);
            if(it==-1)
            {
                // printf("Chill hai\n");
                continue;
            }
            else if(it==6)
            {
                printf("Colliding Pyramid\n");
                score += 10000;
                pr->isDisappearing = true;
                wn->collision(vectors(0,0,0));
                wn->numCollisions = 8;
                available_weapons += 3;

            }
            else
            {
                printf("Colliding Pyramid\n");
                score += 10000;
                pr->isDisappearing = true; //delete this if it has disappeared
                // cout << "collision "<<i << endl;
                wn->collision(plane_normals[i]);
                wn->numCollisions = 8;
                available_weapons += 3;
            }
        }
        
        //end pyramid

        // door
        f(j,l_door.size())
        {
            Door *dr = l_door[j];
            if(dr->isOpening)
                continue;
            Point temp_cen(dr->center.x + dr->xinit, dr->center.y, dr->center.z);
            int it = ball_inter(wn->radius, wn->center, temp_cen, 2*dr->xw, dr->height, dr->thickness);
            temp_cen = Point(dr->center.x - dr->xinit, dr->center.y, dr->center.z);
            int it2 = ball_inter(wn->radius, wn->center, temp_cen, 2*dr->xw, dr->height, dr->thickness);
            if(it==-1 && it2==-1)
                continue;
            else if(it==-1)
            {
                wn->numCollisions = 8;
                dr->isOpening = true;
                wn->collision(plane_normals[it2]);
                printf("Colliding Door: %f, %d\n", udt_count, wn->numCollisions);
                score += 10000;
            }
            else 
            {
                // shit
                wn->numCollisions = 8;
                dr->isOpening = true;
                wn->collision(plane_normals[it]);
                printf("Colliding Door: %f, %d\n", udt_count, wn->numCollisions);
                score += 10000;
            }
        }
        
        // end door

        // flipslab
        f(j,l_flipSlab.size())
        {
            FlipSlab* fs = l_flipSlab[j];
            if(fs->isFalling)
                continue;
            Point temp_cen(0,0,fs->center.z);
            int it = ball_inter(wn->radius, wn->center, temp_cen, fs->l, fs->b, fs->h);
            if(it == -1)
                continue;
            else
            {
                fs->isFalling = true;
                wn->collision(plane_normals[it]);
                wn->numCollisions = 8;
                printf("Colliding FlipSlab: %f, %d\n", udt_count, wn->numCollisions);
                score += 10000;
            }


        }
        
        // end flipslab

        // osc win
        f(j,l_oscWindow.size())
        {
            OscillatingWindow* ow = l_oscWindow[j];
            if(ow->opacity <= 0)
                continue;
            Point temp_cen(ow->center.x + ow->x, ow->center.y, ow->center.z);
            int it = ball_inter(wn->radius, wn->center, temp_cen, ow->l, ow->b, ow->h);
            if(it==-1)
                continue;
            else
            {
                ow->isDisappearing = true;
                wn->collision(plane_normals[it]);
                wn->numCollisions = 8;
                printf("Colliding OscillatingWindow: %f, %d\n", udt_count, wn->numCollisions);
                score += 10000;
            }
        }
        // end osc win

        if(wn->radius > 0)
            nlist.push_back(wn);
        else
            delete wn;  
    }

    l_weapons = vector<Weapon*>(nlist.begin(), nlist.end());
    // printf("Num weapons = %d\n", l_weapons.size());

    vector<FlipSlab*> nlist_f(0);

    f(i,l_flipSlab.size())
    {
        FlipSlab* fs = l_flipSlab[i];
        if(!fs->isFalling && z_global > (-fs->center.z+25))
        {
            available_weapons -= 5;
            score -= 1000;
            if(score<0)score=0;
            printf("!!!\n");
        }
        else
            nlist_f.push_back(fs);
    }

    vector<OscillatingWindow*> nlist_os(0);
    f(i, l_oscWindow.size())
    {
        OscillatingWindow* ow = l_oscWindow[i];
        if(ow->opacity > 0 && z_global > (-ow->center.z + 25))
        {
            available_weapons -= 5;
            score -= 1000;
            if(score<0) score = 0;
            printf("Swag\n");
        }
        else
            nlist_os.push_back(ow);

    }
    l_oscWindow = vector<OscillatingWindow*>(nlist_os.begin(), nlist_os.end());
    l_flipSlab = vector<FlipSlab*>(nlist_f.begin(), nlist_f.end());
}
// weapon collision code ends

void initRendering(void)
{
    mypause = false;
   	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
   	GLfloat mat_shininess[] = { 10.0 };
   	GLfloat light_position[] = { 1, 1, 1, 0.0 };
   	glClearColor (0.0, 0.0, 0.0, 0.0);
   	glShadeModel (GL_SMOOTH);

   	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
   	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    // z_global = 0;


   	glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT2);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_FOG);

    plane_normals[0] = vectors(0,-1,0);
    plane_normals[1] = vectors(1,0,0);
    plane_normals[2] = vectors(0,1,0);
    plane_normals[3] = vectors(-1,0,0);
    plane_normals[4] = vectors(0,0,-1);
    plane_normals[5] = vectors(0,0,1);
    plane_normals[6] = vectors(0,0,0);
    // loading textures
    Image* image = loadBMP("glossy.bmp");
    _textureId = loadTexture(image);

    image = loadBMP("floor2.bmp");
    floor_id = loadTexture(image);

    image = loadBMP("metallic.bmp");
    _metalId = loadTexture(image);

    image = loadBMP("walltile.bmp");
    _wallId = loadTexture(image);

    image = loadBMP("start2.bmp");
    _startId = loadTexture(image);

    image = loadBMP("exit2.bmp");
    _exitId = loadTexture(image);
    // end loading textures

    intiCuboids();

    

    Door* dr = new Door;
    dr->thickness = 1.5, dr->height = 10, dr->xinit = dr->xw = 5;
    dr->isOpening = false;
    dr->center = Point(0,5,-z_global-40);
    dr->color = Point(0.5,0.1,0.7);
    dr->opacity = 0.95;
    dr->theta = 0;
    l_door.push_back(dr);

    // flip slabs
    float ztemp = -z_global - 100;
    f(i,10)
    {
        FlipSlab *fs = new FlipSlab;
        fs->center = Point(0,0,ztemp);
        fs->color = Point(1,getRand(0,0.4),getRand(0,0.4));
        fs->opacity = 0.5;
        fs->l = 25;
        fs->b = 22;
        fs->h = 2;
        fs->isTexture = false;
        fs->initCuboid();
        fs->angle = 0;
        fs->isFalling = false;
        fs->isRising = false;
        l_flipSlab.push_back(fs);
        // ztemp -= getRand(50,100);
        ztemp -= getRand(150,200);
        if(ztemp < -(global_size-10))
            break;
    }

    // pyramids
    srand (time(NULL));
    int kk = 0;
    f(i,25)
    {
        int r = rand()%10;
        kk += r;
        if(kk >= 100) break;
        Pyramid* pr = new Pyramid;
        pr->center = Point(-(cuboid_width/2)- y_offset, heights[kk], -kk*cuboid_length);
        pr->length = 4, pr->height = 8;
        pr->color = Point(0,0,1);
        pr->isDisappearing = false;
        pr->opacity = 0.7;
        l_pyramid.push_back(pr);
    }
    kk = 0;
    f(i,25)
    {
        int r = rand()%10;
        kk += r;
        if(kk >= 100) break;
        Pyramid* pr = new Pyramid;
        pr->center = Point((cuboid_width/2) + y_offset, heights[kk], -kk*cuboid_length);
        pr->length = 4, pr->height = 8;
        pr->color = Point(0,0,1);
        pr->isDisappearing = false;
        pr->opacity = 0.7;
        l_pyramid.push_back(pr);
    }

    // oscillating windows.
    ztemp = -z_global - 120;
    f(i,7)
    {
        OscillatingWindow* ow = new OscillatingWindow;
        ow->speed = 0.2;
        ow->isRight = true;
        ow->center = Point(0,2.5,ztemp);
        ow->l = 7, ow->b = 10, ow->h = 1;
        ow->x = 0;
        ow->opacity = 0.7;
        ow->isDisappearing = false;
        ow->color = Point(getRand(0,0.5),getRand(0.5,1),getRand(0,1));
        ow->initCuboid();
        ow->xright = 11, ow->xleft = -11;
        l_oscWindow.push_back(ow);
        ztemp -= getRand(90,150);
        if(ztemp < -(global_size-10))
            break;
    }


    strt_cuboid = new Cuboid;
    strt_cuboid->center = Point(-(cuboid_width/2)- y_offset, 7.5, -80);
    strt_cuboid->color = Point(1,1,1);
    strt_cuboid->l = cuboid_width + 6, strt_cuboid->b = 15, strt_cuboid->h = cuboid_length;
    strt_cuboid->isTexture = true;
    strt_cuboid->texture_id = _startId;
    strt_cuboid->opacity = 1;

    exit_cuboid = new Cuboid;
    exit_cuboid->center = Point((cuboid_width/2) + y_offset, 7.5, -80);
    exit_cuboid->color = Point(1,1,1);
    exit_cuboid->l = cuboid_width + 6, exit_cuboid->b = 15, exit_cuboid->h = cuboid_length;
    exit_cuboid->isTexture = true;
    exit_cuboid->texture_id = _exitId;
    exit_cuboid->opacity = 1;
    
}


void handleResize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w / (float)h, 1.0, 200.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -5.0);
}

//Called every 25 milliseconds
void time_update(int value) 
{
    
    udt_count += 0.01;
    if(!mypause && gameStart)
    {
        score += 1;
        z_global += 1;
        if(z_global > (global_size-10) || available_weapons <= 0)
            gameOver();
        f(i,l_oscWindow.size())
        	l_oscWindow[i]->update();
       	f(i,l_pyramid.size())
       		l_pyramid[i]->update();
       	f(i,l_door.size())
       		l_door[i]->update();
       	f(i,l_flipSlab.size())
       		l_flipSlab[i]->update();
        

        
    }
    if(!mypause)
    {
        f(i,l_weapons.size())
            l_weapons[i]->update();
        weapon_collision_detection();
    }
    glutPostRedisplay();
    glutTimerFunc(refresh_rate, time_update, 0);
}


int main(int argc, char** argv)
{
	myModel = (GLMmodel*)malloc(sizeof(GLMmodel));
//	readObject("bullet.obj");

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1000, 1000);
	glutCreateWindow("Smash Hit!");

	initRendering();

	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutSpecialFunc(handleSpecialKeypress);
//	glutSpecialUpFunc(handleSpecialKeyRelease);
    glutFullScreen();
    glutMouseFunc(mouse);
	glutReshapeFunc(handleResize);
	glutTimerFunc(refresh_rate, time_update, 0);
	glutMainLoop();

	return 0;
}


