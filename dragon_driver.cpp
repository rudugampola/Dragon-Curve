#include "ccc_win.h"
#include "dragon.h"
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>

using std::vector;
using std::ofstream;
using std::cout;

enum direction_t { NORTH, SOUTH, EAST, WEST };

/** 
    Display a sequence of 0's and 1's as a curve.

    Idea: 
         - Set initial direction to EAST.
         - Repeatedly obtain a bit from the source
	     - if direction is EAST 
	          draw a line to the right and 
		  set direction to NORTH if bit is 0
		  set direction to SOUTH if bit is 1
	     - else if direction is WEST 
	          draw a line to the left and 
		  set direction to SOUTH if bit is 0
		  set direction to SOUTH is bit is 1
	     - else if direction is NORTH 
	          draw a line upward and 
		  set direction to WEST if bit is 0
		  set direction to EAST if bit is 1
	     - else SOUTH 
		  draw a line downward and 
		  set direction to EAST if bit is 0
		  set direction to WEST if bit is 1
*/
void displayData(istream& in ){

    // Read elements from the source
    vector<bool> v;
    bool x;

    while ( in >> x ) {
        v.push_back(x);
    }
    // The vector should contain (2^n)-1 entries where n is the
    // number of folds. To recover n let us compute an approximation
    // to the logarithm in base 2 of the v.size.

    int n = v.size() + 1;
    int m = 0;
    while ( n > 1 ) {
        n /= 2;
	m++;
    }
    // m now holds the desired value. log_2 (n)

    /**
       We want our curve to remain within 8 units of the origin
       (recall that the viewing window defaults to -10 to 10 in 
       both, the x- and the y- directions). To achieve this we 
       adjust the length of the lines that are drawn. Divide by 
       sqrt(2) once per every fold.
    */
    double step = 8/pow(sqrt(2), m  );

    // Time to draw...
    direction_t current_dir = NORTH;
    Point p(0,0);
    Point q(p);

    // Lazy way to draw the last leg of the curve
    // One last direction will be set but will not be drawn
    v.push_back(true);

    for ( int i = 0 ; i < v.size() ; i++ ){
        switch( current_dir ){
	    case EAST:  q.move(step,0);
		        if ( !v[i] ) 
		            current_dir = NORTH;
		        else 
		            current_dir = SOUTH;
		        break;
	    case WEST:  q.move(-step,0);
		        if ( !v[i] ) 
		            current_dir = SOUTH;
		        else 
		            current_dir = NORTH;
	                break;
	    case NORTH: q.move(0,step);
		        if ( !v[i] ) 
		            current_dir = WEST;
		        else 
		            current_dir = EAST;
	                break;
	    case SOUTH: q.move(0,-step);
		        if ( !v[i] ) 
		            current_dir = EAST;
		        else 
		            current_dir = WEST;
	                break;
	}
	cwin << Line(p,q);
	p = q;
    }

   return;
}

/* **********************************************************
                        M A I N   
   ********************************************************** */
int ccc_win_main(){  

   // read data and display to viewing window

	vector<bool> dragon;

    // Sequence (3 folds) sent to the console
    generate_dragon_sequence( dragon, 17, cout );

    // reset the vector
    dragon.resize(0);

    // open file
    ofstream fout;
    fout.open("dragon.txt");

    // Sequence (5 folds) sent to a file
    generate_dragon_sequence( dragon, 17, fout );

    // close file
    fout.close();

   ifstream fin;
   fin.open("dragon.txt");

   displayData(fin);

   fin.close();

   return 0;
}
