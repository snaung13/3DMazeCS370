#ifndef _MAZEALG_CPP_
#define _MAZEALG_CPP_

//edit these to modify how the maze generates
#define paths 12//number of paths created
#define MAX_X 50//number of units wide
#define MAX_Z 50//number of units tall
#define deadends 5//number of deadend paths generated, these are generated independantly of the paths
#define entrancex 12//it is assumed that the entrance is on the bottom edge, this controls where on said edge
#define exitx 7//same as above
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

//pathx and pathy are only used in the generate_maze function, don't worry about them
void pathx(bool (*maze)[MAX_X][MAX_Z], int point1x, int z, int point2x){
  if(point1x < point2x){
    for(int c = point1x; c < point2x; c++){
      (*maze)[c][z] = false;
      //cout << c << ' ' << y << '\n';
    }
  }
  else{
    for(int c = point1x; c > point2x; c--){
      (*maze)[c][z] = false;
      //cout << c << ' ' << y << '\n';
    }
  }
}
void pathz(bool (*maze)[MAX_X][MAX_Z], int x, int point1z, int point2z){
  if(point1z < point2z){
    for(int c = point1z; c < point2z; c++){
      (*maze)[x][c] = false;
      //cout << x << ' ' << c << '\n';
    }
  }
  else{
    for(int c = point1z; c > point2z; c--){
      (*maze)[x][c] = false;
      //cout << x << ' ' << c << '\n';
    }
  }
}

//Call the function using generate_maze(&varname); where varname is an array of bools initialized to all true, with dimensions MAX_X and MAX_Y
void generate_maze(bool (*maze)[MAX_X][MAX_Z]){
  srand(time(NULL));
  int point1x, point1z, point2x, point2z;
  bool xfirst = false;
  point1x = entrancex;
  point1z = 0;
  int xpoints[paths+2];
  int zpoints[paths+2];
  xpoints[0] = entrancex;
  zpoints[0] = 0;
  xpoints[1] = exitx;
  zpoints[1] = MAX_Z;
  for(int c = 0; c < paths; c++){
    bool newpoint;//this is to make sure the paths don't generate too close to each other, xpoints and ypoints track what x and y values have already been used, and if the points are within 1 of one that has been already used, the paths would have a chance of being adjacent to each other, creating a double wide path, so this should prevent that
    do{
      newpoint = true;
      point2x = rand() % (MAX_X - 2) + 1;//less than MAX_X, but greater than 0
      //cout << newxpoint << '\n';
      for(int q = 0; q < c+2; q++){
        //cout << "test " << point2x << " against " << xpoints[q] << " and " << xpoints[q] + 1 << " and " << xpoints[q] - 1 << '\n';
        //cout << (point2x == xpoints[c]) << '\n';
        //cout << (point2x == (xpoints[c] + 1)) << '\n';
        //cout << (point2x == (xpoints[c] - 1)) << '\n';
        if(point2x == (xpoints[q] + 1)){
          newpoint = false;
          //cout << "regenerating\n";
        }
        if(point2x == (xpoints[q] - 1)){
          newpoint = false;
          //cout << "regenerating\n";
        }
        if(point2x == xpoints[q]){
          newpoint = false;
          //cout << "regenerating\n";
        }
      }
    }while(!newpoint);

    do{
      newpoint = true;
      point2z = rand() % (MAX_Z - 2) + 1;//less than MAX_Y, but greater than 0
      //cout << newypoint << '\n';
      for(int q = 0; q < c+2; q++){
        //cout << "test " << point2y << " against " << ypoints[q] <<  " and " << ypoints[q] + 1 << " and " << ypoints[q] - 1 << '\n';
        if(point2z == (zpoints[q] + 1)){
          newpoint = false;
          //cout << "regenerating\n";
        }
        if(point2z == (zpoints[q] - 1)){
          newpoint = false;
          //cout << "regenerating\n";
        }
        if(point2z == zpoints[q]){
          newpoint = false;
          //cout << "regenerating\n";
        }
      }
    }while(!newpoint);
        
    //cout << "Set :" << point2x << ' ' << point2y << '\n';
    if(xfirst){
      pathx(maze,point1x,point1z,point2x);
      pathz(maze,point2x,point1z,point2z);
    }
    else{
      pathz(maze,point1x,point1z,point2z);
      pathx(maze,point1x,point2z,point2x);
    }
    xfirst = rand() % 2;
    xpoints[c+2] = point2x;
    zpoints[c+2] = point2z;
    point1x = point2x;
    point1z = point2z;
  }
  int deadendxs[deadends];
  int deadendzs[deadends];
  for(int c = 0; c < deadends; c++){
    int startpoint = (rand() % paths) + 2;
    point1x = xpoints[startpoint];
    point1z = zpoints[startpoint];
    bool newpoint;//this is to make sure the paths don't generate too close to each other
    do{
      newpoint = true;
      point2x = rand() % (MAX_X - 2) + 1;//less than MAX_X, but greater than 0
      //cout << newxpoint << '\n';
      for(int q = 0; q < paths+2; q++){
        if(point2x == (xpoints[q]+1)){
          newpoint = false;
        }
        if(point2x == (xpoints[q]-1)){
          newpoint = false;
        }
        if(point2x == xpoints[q]){
          newpoint = false;
        }
      }
      for(int r = 0; r < c; r++){
        if(point2x == deadendxs[r]){
          newpoint = false;
        }
        if(point2x == (deadendxs[r]+1)){
          newpoint = false;
        }
        if(point2x == (deadendxs[r]-1)){
          newpoint = false;
        }
      }
    }while(!newpoint);
    do{
      newpoint = true;
      point2z = rand() % (MAX_Z - 2) + 1;//less than MAX_Y, but greater than 0
      for(int q = 0; q < paths+2; q++){
        if(point2z == (zpoints[q]+1)){
          newpoint = false;
        }
        if(point2z == (zpoints[q]-1)){
          newpoint = false;
        }
        if(point2z == zpoints[q]){
          newpoint = false;
        }
      }
      for(int r = 0; r < c; r++){
        if(point2z == deadendzs[r]){
          newpoint = false;
        }
        if(point2z == (deadendzs[r]+1)){
          newpoint = false;
        }
        if(point2z == (deadendzs[r]-1)){
          newpoint = false;
        }
      }
    }while(!newpoint);
    //cout << "Start " << point1x << ' ' << point1y << '\n';
    //cout << "Dead :" << point2x << ' ' << point2y << '\n';
    xfirst = rand() % 2;
    if(xfirst){
      pathx(maze,point1x,point1z,point2x);
      pathz(maze,point2x,point1z,point2z);
    }
    else{
      pathz(maze,point1x,point1z,point2z);
      pathx(maze,point1x,point2z,point2x);
    }
    deadendxs[c] = point2x;
    deadendzs[c] = point2z;
  }
  pathx(maze,xpoints[paths+1],zpoints[paths+1],exitx);
  pathz(maze,exitx,zpoints[paths+1],MAX_Z);
  for(int g = 0; g < MAX_X; g++){
    if(!(*maze)[g][MAX_Z-1] && g != exitx)(*maze)[g][MAX_Z-1] = true;
  }
  for(int g = 0; g < MAX_X; g++){
    if(!(*maze)[g][0] && g != entrancex)(*maze)[g][0] = true;
  }
}
    
#endif
