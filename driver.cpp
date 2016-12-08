//CS370 Computer Graphics
//Final Project
//By Maxwell Meier, Samual Kahsay, Saw Yan Naung, Victor Zuniga
//3D Maze


#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include "mazealg.cpp"

using namespace std;

GLdouble eye_x = 3, eye_y = 2, eye_z = 3, look_x = 0, look_y = 0, look_z = 0;
bool maze[MAX_X][MAX_Z];

//<<<<<<<<<<<<<<<<<Keyboard to move the camera>>>>>>>>>>>>>>>>>>>>>

void keyboard(unsigned char key, int x, int y){
  switch(key){
  case 'w':
    eye_x += 0.5;
    break;
  case 's':
    eye_x -= 0.5;
    break;
  case 'e':
    eye_y += 0.5;
    break;
  case 'd':
    eye_y -= 0.5;
    break;
  case 'r':
    eye_z += 0.5;
    break;
  case 'f':
    eye_z -= 0.5;
    break;
  case 'z':
    look_x += 0.3;
    break;
  case 'x':
    look_x -= 0.3;
    break;
  case 'c':
    look_y += 0.3;
    break;
  case 'v':
    look_y -= 0.3;
    break;
  case 'b':
    look_z += 0.3;
    break;
  case 'n':
    look_z -= 0.3;
    break;
  }
  gluLookAt(eye_x, eye_y, eye_z, look_x, look_y, look_z, 0.0,1.0,0.0);

  glutPostRedisplay();
}

//<<<<<<<<<<<<<<< wall >>>>>>>>>>>>>>>>
void wall()
{ 
  glPushMatrix();
  glTranslated(0.5, 0.5, 0.5);
  glScaled(0.03, 0.03, 0.03);
  glutSolidCube(1.0);
  glPopMatrix();
}

//<<<<<<<<<<<<<<<<<<<<< DrawMaze >>>>>>>>>>>>>>>>>>>>>>
void drawmaze(void)
{
  // set properties of the surface material
  GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f}; // gray
  GLfloat mat_diffuse[] = {0.6f, 0.6f, 0.6f, 1.0f};
  GLfloat mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
  GLfloat mat_shininess[] = {50.0f};
  glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
  glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
  glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
  glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);

  // set the light source properties
  GLfloat lightIntensity[] = {0.7f, 0.7f, 0.7f, 1.0f};
  GLfloat light_position[] = {2.0f, 6.0f, 3.0f, 0.0f};
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);

  // set the camera
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  double winHt = 1.0; // half-height of the window
  glOrtho(-winHt*64/48.0, winHt*64/48.0, -winHt, winHt, 0.1, 100.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(eye_x, eye_y, eye_z, look_x, look_y, look_z, 0.0,1.0,0.0);

  // start drawing
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); // clear the screen
  
  for(unsigned int x = 0; x < sizeof(maze)/sizeof(maze[0]); x++)
    {
      for(unsigned int z = 0; z < sizeof(maze)/sizeof(maze[0]); z++)
        {
          if (maze[x][z] == true)
            {
              glPushMatrix();
              glTranslated((0.03*x), 0, (0.03*z));
              wall();
              glPopMatrix();
            }
        }
    }   
  glFlush();
}

int main(int argc, char **argv)
{
  for(unsigned int a = 0; a < sizeof(maze)/sizeof(maze[0]); a++){
    for(unsigned int b = 0; b < sizeof(maze[0])/sizeof(maze[0][0]); b++){
      maze[a][b] = true;
    }
  }
  generate_maze(&maze);
  for(unsigned int c = 0; c < sizeof(maze)/sizeof(maze[0]); c++){
    for(unsigned int d = 0; d < sizeof(maze[0])/sizeof(maze[0][0]); d++){     
      cout<<maze[c][d]<<" ";
    }
    cout<<endl;
  }
 
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB| GLUT_DEPTH);
  glutInitWindowSize(640,480);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("3D Maze Final Project");
  glutDisplayFunc(drawmaze);
  glEnable(GL_LIGHTING); // enable the light source
  glEnable(GL_LIGHT0);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_DEPTH_TEST); // for hidden surface removal
  glEnable(GL_NORMALIZE); // normalize vectors for proper shading
  glClearColor(0.1f,0.1f,0.1f,0.0f); // background is light gray
  glViewport(0, 0, 640, 480);
  glutKeyboardFunc(keyboard);
  glutMainLoop();
  
  return 0;
}
