#ifndef FLOYDWARSHALL_H_INCLUDED
#define FLOYDWARSHALL_H_INCLUDED

#include <cmath>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "FileInput.h"

bool findInVector( std::vector<int>& used , int val );

double calculateDistance( star& , star& );

void FloydWarshallPath( std::vector<star>& star_list )
{
    //Number of stars in graph
    const unsigned int STAR_COUNT = star_list.size();

    //Initialize distance array to the distance between stars
    double dist[STAR_COUNT][STAR_COUNT];
    for( unsigned int i = 0 ; i < STAR_COUNT ; i++ )
    {
        for( unsigned int j = 0 ; j < STAR_COUNT ; j++ )
        {
            double distance = calculateDistance( star_list[i] , star_list[j] );
            dist[i][j] = distance;
            dist[j][i] = distance;
        }
    }

    //Initialize Next Array
    unsigned int next[STAR_COUNT][STAR_COUNT];
    for( unsigned int i = 0 ; i < STAR_COUNT ; i++ )
    {
        for( unsigned int j = 0 ; j < STAR_COUNT ; j++ )
        {
            if( i == j )
            {
                next[i][j] = 9999;
                next[j][i] = 9999;
            }
            else
            {
                next[i][j] = i;
                next[j][i] = i;
            }
        }
    }

    //Floyd Warshall Algorithm
    for( unsigned int k = 0 ; k < STAR_COUNT ; k++ )
    {
        for( unsigned int i = 0 ; i < STAR_COUNT ; i++ )
        {
            for( unsigned int j = 0 ; j < STAR_COUNT ; j++ )
            {
                if( dist[i][k] + dist[k][j] < dist[i][j] )
                {
                    std::cout << "\nif loop entered";
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[k][j];
                }
            }
        }
    }

    std::vector<int> used;;
    for( unsigned int i = 0 ; i < STAR_COUNT ; i++ )
    {
        used.push_back(i);
    }


    double running_total = 0;

    int current = 0;
    while( used.size() != 1 )
    {
        for( int i = 0; i < STAR_COUNT ; i++ )
        {
            if( current == i || !findInVector( used , i ) )
            {
                continue;
            }
            else
            {
                std::cout << "\n\ncurrent = " << current;
                running_total += dist[i][current];
                used.erase( std::find( used.begin() , used.end() , current ));
                current = i;
                std::cout << "\nnew current = " << current;
            }
        }
    }



    std::cout << "\n\nTotal Distance = " << running_total /2;


}


bool findInVector( std::vector<int>& used , int val )
{
    for( int i = 0 ; i < used.size() ; i++ )
    {
        if( used[i] == val )
        {
            return true;
        }
    }

    return false;
}


double calculateDistance( star& star1 , star& star2 )
{
    double x = star1.x - star2.x;
    double y = star1.y - star2.y;
    double z = star1.z - star2.z;

    return sqrt( x*x + y*y + z*z );
}
#endif // FLOYDWARSHALL_H_INCLUDED
