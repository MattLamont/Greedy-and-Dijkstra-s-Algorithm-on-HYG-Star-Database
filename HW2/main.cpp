


#include <iostream>
#include <climits>
#include "FileInput.h"
//#include "ShortestPath.h"
//#include "A-Star.h"
#include "FloydWarshallPath.h"
double distbetween(star& s1, star& s2);

void greed(std::vector<star> star_array);


int main( int argc , char* argv[] )
{
    std::vector<star> star_list;
    getFileInfo( argc , argv[1] , &star_list , 10 );

    //A_StarSearch( star_list );
    //FloydWarshallPath( star_list );

    greed( star_list );

    return 0;
}


double distbetween(star& s1, star& s2) {
    double dx = s2.x - s1.x;
    double dy = s2.y - s1.y;
    double dz = s2.z - s1.z;
    return sqrt(dx*dx + dy*dy + dz*dz);
}
void greed(std::vector<star> star_array) {
    star source = star_array[0];
    star next;
    unsigned int index = 0;
    double total = 0;
    star_array.erase(star_array.begin() + index);
    while (star_array.empty() == false) {
   	 std::cout << source.id << " -> ";
   	 //selects closest star
   	 double min = INT_MAX;
   	 for (unsigned int i = 0; i< star_array.size(); i++) {
   		 double temp = distbetween(source, star_array[i]);
   		 if (temp <= min) {
   			 index = i;
   			 min = temp;
   			 next = star_array[i];
   		 }
   	 }
   	 //removes source
   	 star_array.erase(star_array.begin() + index);
   	 source = next;
   	 total += min;
   	 std::cout << next.id << ", distance = " << min << ", cumlative = " << total << std::endl;
    }
    std::cout << " Total distance traveled is " << total << " parsecs." << std::endl;
}

