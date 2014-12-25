#ifndef A-STAR_H_INCLUDED
#define A-STAR_H_INCLUDED


#include "FileInput.h"
#include <climits>
#include <iomanip>
#include <queue>
#include <algorithm>
#include <cmath>

double calculateDistance( star& star1 , star& star2 );

bool openSetEmpty( std::vector<bool>& open_set );

int findOpenEntry( std::vector<bool>& open_set , std::vector<double>& g_score );





void A_StarSearch( std::vector<star>& star_list )
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

    //Create and Initialize closed and open sets
    std::vector<bool> open_set;
    std::vector<bool> closed_set;
    std::vector<int> came_from;
    for( unsigned int i = 0 ; i < STAR_COUNT ; i++ )
    {
        open_set.push_back( true );
        closed_set.push_back( false );
        came_from.push_back( 0 );
    }

    //Create and initialize heuristic vectors
    std::vector<double> g_score;
    std::vector<double> f_score;
    for( unsigned int i = 0 ; i < STAR_COUNT ; i++ )
    {
        g_score.push_back( calculateDistance( star_list[0] , star_list[i]));
        f_score.push_back(0);
    }

    while( !openSetEmpty( open_set ) )
    {
        int current = findOpenEntry( open_set , g_score );
        open_set[current] = false;
        closed_set[current] = true;

        std::cout << "\n\nOpen Set: ";
        for( unsigned int i = 0 ; i < STAR_COUNT ; i++ )
        {
            std::cout << " " << open_set[i];
        }

        std::cout << "\nG-Score: ";
        for( unsigned int i = 0 ; i < STAR_COUNT ; i++ )
        {
            std::cout << " " << std::setprecision(2) << g_score[i];
        }

        int best = 1;
        for( unsigned int i = 0 ; i < STAR_COUNT ; i++ )
        {
            if( current == i || closed_set[i] == true )
            {
                continue;
            }

            double tentative_g_score = g_score[current] + dist[i][current];

            if( open_set[i] == false || tentative_g_score < g_score[i] )
            {
                std::cout << "\n\nentered if";
                came_from[i] = current;
                g_score[i] = tentative_g_score;
                if( open_set[i] == false )
                {
                    open_set[i] = true;
                }
            }

        }

    }

    std::cout << "\n\n\n";
    for( unsigned int i = 0 ; i < STAR_COUNT; i++ )
    {
        std::cout << " " << came_from[i];
    }
}


double calculateDistance( star& star1 , star& star2 )
{
    double x = star1.x - star2.x;
    double y = star1.y - star2.y;
    double z = star1.z - star2.z;

    return sqrt( x*x + y*y + z*z );
}


bool openSetEmpty( std::vector<bool>& open_set )
{
    for( unsigned int i = 0 ; i < open_set.size() ; i++ )
    {
        if( open_set[i] == true )
        {
            return false;
        }
    }

    return true;
}

int findOpenEntry( std::vector<bool>& open_set , std::vector<double>& g_score )
{
    int best = 0;
    for( unsigned int i = 0 ; i < open_set.size() ; i++ )
    {
        if( open_set[i] == true && g_score[i] < g_score[best] )
        {
            best = i;
        }
    }
    return best;
}



#endif // A-STAR_H_INCLUDED
