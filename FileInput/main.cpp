

#include <vector>
#include "FileInput.h"

int main( int argc , char* argv[] )
{
    std::vector<star> my_stars;
    double RADIUS = 10;

    getFileInfo( argc , argv[1] , &my_stars , RADIUS );

    //Now you can do whatever with the vector of stars
    return 0;
}
