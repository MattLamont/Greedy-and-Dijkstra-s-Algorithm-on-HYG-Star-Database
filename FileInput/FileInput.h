//Author    | Matt Lamont
//Date      | 3/5/2014
//Course    | CSCI 3412



#ifndef FILEINPUT_H_INCLUDED
#define FILEINPUT_H_INCLUDED


#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <iostream>



/*-----------------------------------------------FUNCTION DEFINITIONS-------------------------------------*/




//This is the struct that contains all the necessary info for a star
struct star
{
    star():id(0),distance(0),x(0),y(0),z(0){}
    int id;
    double distance;
    double x;
    double y;
    double z;
};



/*
Inputs

    1. int argc ( the first command line argument )
    2. char* argv (the second command line argument pointing to the name of the file)
    3. vector* (a pointer to an empty vector that you want this function to fill with stars)
    4. double radius ( all the stars within this radius from Sol will be put into your vector. All others will be discarded)

Outputs

    1. the pointer to the vector you give this function will be filled with stars within the given radius.
*/
void getFileInfo( int argc , char* argv , std::vector<star>* star_array , double radius );








//used within the getFileInfo Function
void fileErrorCheck( const int argc , const char* argv );

//used within the getFileInfo Function
int getFileLineCount( const char* argv );












/*------------------------------------------IMPLEMENTATION----------------------------------------------*/









void getFileInfo( int argc , char* argv , std::vector<star>* star_array , double radius )
{
    std::ifstream infile( argv );
    std::string line;
    char delim = ',';

    //temporary holders for the data of each star
    int id = 0;
    double distance = 0;
    double x = 0;
    double y = 0;
    double z = 0;

    //checks for problems with the file
    fileErrorCheck( argc , argv );

    //gets the total number of lines of the file
    int line_count = getFileLineCount( argv );

    //ignores the whole first line of the file
    infile.ignore( 126 );

    std::cout << "\n\tThe file is being read...";
    for( int i = 0 ; i < line_count - 2 ; i++ )
    {
        getline( infile , line , delim );

        //get the star id
        id = atoi( line.c_str() );

        //skip over unnecessary data until we reach the distance value of the star
        for( int j = 0; j < 9; j++ )
        {
             getline( infile , line , delim );
        }

        //get the distance of the star
        distance = atof( line.c_str() );

        //skip over unnecessary data until we reach the x value of the star
        for( int j = 0; j < 8; j++ )
        {
             getline( infile , line , delim );
        }

        //get the x value of the star
        x = atof( line.c_str() );

        //get the y value of star
        getline( infile , line , delim );
        y = atof( line.c_str() );

        //get the z value of star
        getline( infile , line , delim );
        z = atof( line.c_str() );

        //skip the rest of star data and move on to next line
        getline( infile , line , '\n' );

        //If star is outside of radius of sol, then it will not be added to the vector
        if( distance > radius )
        {
            continue;
        }

        //because the star is within the wanted radius of sol, it is added to the vector
        else
        {
            star mStar;
            mStar.id = id;
            mStar.distance = distance;
            mStar.x = x;
            mStar.y = y;
            mStar.z = z;
            star_array->push_back( mStar );
        }



    }
    std::cout << "\n\tFinished reading file. " << star_array->size() << " stars were created.\n\n";

    infile.close();
}




void fileErrorCheck( const int argc , const char* argv )
{
    //checks if there was a filename inputted
    if( argc == 1 )
    {
        std::cerr << "\n\n\t ERROR: No input file entered.";
        exit( EXIT_FAILURE );
    }

    //checks if filename is to short or to long
    if( argc < 1 || argc > 500 )
    {
        std::cerr << "\n\n\t ERROR: Bad file name.";
        exit( EXIT_FAILURE );
    }

    //checks if the file can be opened
    std::ifstream infile( argv );

    if( !infile )
    {
        std::cerr << "\n\n\t ERROR: File could not be opened.";
        exit( EXIT_FAILURE );
    }

}

int getFileLineCount( const char* argv )
{
    std::ifstream infile( argv );
    std::string temp;
    int line_count = 0;

    //iterates through each line of file and increments counter for each line
    while( !infile.eof() )
    {
        getline( infile , temp );
        line_count++;
    }

    infile.close();
    return line_count;
}




#endif // FILEINPUT_H_INCLUDED
