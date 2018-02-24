/**
 Ravindu Udugampola
 PIC 10B Winter 2018
 ID: 504419572
 03/05/2018
 This program implements function generate_dragon_sequence(...) which receives 
	three parameters and output a text file with 1's and 0's sequences to 
	generate a dragon curve
 */

#include <ostream>
#include <vector>

using namespace std;

#ifndef dragon_h
#define dragon_h

// Declaration and definition of generate_dragon_sequence()
void generate_dragon_sequence(vector<bool>& v, int numOfFlips, ostream& out){
    // If finish folding the imaginary paper strip, store all the data into ostream
    if(numOfFlips == 0)
	{
        for(size_t i = 0; i < v.size(); i++){
            out << v[i] << endl;
        }
        return;
    }
	else
	{
        // Adding an R at the end
        v.push_back(true);
        // Taking the original iteration, flipping it retrograde
        for(int i = v.size()-2; i>=0; i--){
            //Swapping each letter and adding the result after the R.
            v.push_back(!v[i]);
        }
        // Call function itself with parameter numOfFlips-1, which is one fold fewer
        generate_dragon_sequence(v, numOfFlips-1, out);
    }
}

#endif /* dragon_h */