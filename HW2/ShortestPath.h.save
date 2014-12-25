#ifndef SHORTESTPATH_H_INCLUDED
#define SHORTESTPATH_H_INCLUDED


#include "FileInput.h"
#include <climits>
#include <iomanip>
#include <queue>
#include <algorithm>
#include <cmath>


const unsigned int STAR_COUNT = 12;


bool compare( const star* , const star* );

star* findSmallestDistanceStar( std::vector<star>* );

double star_length( const star* current , const star* neighbor );

void changePrevious( std::vector<star*>* previous , star* current , star* neighbor );

void changeDistance( std::vector<star*>* dist_array , star* neighbor , double alt );

template <size_t size_y>
void initNextArray( double* dist , unsigned int* next , unsigned int vertice_count );

std::string findPath( double[STAR_COUNT][STAR_COUNT] , unsigned int[STAR_COUNT][STAR_COUNT] , unsigned int i , unsigned int j );

/*
double star_length( const star* current , const star* neighbor );

function Dijkstra(Graph, source):
 2      for each vertex v in Graph:                                // Initializations
 3          dist[v]  := infinity ;                                  // Unknown distance function from
 4                                                                 // source to v
 5          previous[v]  := undefined ;                             // Previous node in optimal path
 6      end for                                                    // from source
 7
 8      dist[source]  := 0 ;                                        // Distance from source to source
 9      Q := the set of all nodes in Graph ;                       // All nodes in the graph are
10                                                                 // unoptimized – thus are in Q
11      while Q is not empty:                                      // The main loop
12          u := vertex in Q with smallest distance in dist[] ;    // Source node in first case
13          remove u from Q ;
14          if dist[u] = infinity:
15              break ;                                            // all remaining vertices are
16          end if                                                 // inaccessible from source
17
18          for each neighbor v of u:                              // where v has not yet been
19                                                                 // removed from Q.
20              alt := dist[u] + dist_between(u, v) ;
21              if alt < dist[v]:                                  // Relax (u,v,a)
22                  dist[v]  := alt ;
23                  previous[v]  := u ;
24                  decrease-key v in Q;                           // Reorder v in the Queue
25              end if
26          end for
27      end while
28      return dist;
29  end function
*/

void pathfinder( std::vector<star>& star_list )
{
    std::vector<star*> dist_array;
    std::vector<star*> previous;

    for( unsigned int i = 0; i < star_list.size(); i++ )
    {
        star* temp = &star_list[i];
        temp->alg_dist = INT_MAX;
        dist_array.push_back( temp );
        previous.push_back( &star_list[i] );
    }
    star* source = dist_array[0];
    source->alg_dist = 0;

    while( !star_list.empty() )
    {
        star* current = findSmallestDistanceStar( &star_list );

        for( unsigned int i = 0 ; i < star_list.size() ; i++ )
        {
            star* neighbor = &star_list[i];
            if( neighbor->id != current->id )
            {
                double alt = current->alg_dist + star_length( current , neighbor );

                if( alt < neighbor->alg_dist )
                {
                    changeDistance( &dist_array , neighbor , alt );
                    changePrevious( &previous , current , neighbor );
                }
            }



            std::cout << "\n\n" << "Q:  ";
            for(int i = 0 ; i < star_list.size() ; i++ )
            {
                star* temp = &star_list[i];
                std::cout << temp->id << " ";
            }

            std::cout << "\nPrevious:  ";
            for( int i = 0 ; i < previous.size() ; i++ )
            {
                if( previous[i] != NULL )
                {
                    star* temp = previous[i];
                    std::cout << temp->id << " ";
                }
            }

        }

    }



}


star* findSmallestDistanceStar( std::vector<star>* star_list )
{
    star* return_star = &star_list->at(0);
    int index = NULL;

    for( unsigned int i = 1 ; i < star_list->size() ; i++ )
    {
        star* temp = &star_list->at(i);
        if( temp->alg_dist < return_star->alg_dist )
        {
            return_star = temp;
            index = i;
        }
    }

    star_list->erase( star_list->begin() + index );
    return return_star;
}


void changeDistance( std::vector<star*>* dist_array , star* neighbor , double alt )
{
    for( unsigned int i = 0 ; i < dist_array->size() ; i++ )
    {
        star* temp = dist_array->at(i);
        if( temp->id == neighbor->id )
        {
            neighbor->alg_dist = alt;
        }
    }
}


void changePrevious( std::vector<star*>* previous , star* current , star* neighbor )
{
    for( unsigned int i = 0 ; i < previous->size() ; i++ )
    {
        star* temp1 = previous->at(i);

        if( temp1->id == neighbor->id )
        {
            previous->at(i) = current;
        }
    }
}




bool compare( const star* lhs , const star* rhs )
{
    if( rhs->alg_dist > lhs->alg_dist )
    {
        return false;
    }

    else
    {
        return true;
    }
}


double star_length( const star& current , const star& neighbor )
{
    double length = 0;
    double x = abs( current.x - neighbor.x );
    double y = abs( current.y - neighbor.y );
    double z = abs( current.z - neighbor.z );

    length = ( x*x + y*y + z*z );
    length = sqrt( length );

    return length;
}



/*
let dist be a |V| × |V| array of minimum distances initialized to ∞ (infinity)
let next be a |V| × |V| array of vertex indices initialized to null

procedure initNextArray ()
   for i from 1 to |V|
      for j from 1 to |V|
         if i = j or dist[i][j] = ∞ (infinity) then
            next[i][j] ← 0
         else
            next[i][j] ← i

procedure FloydWarshallWithPathReconstruction ()
   for each vertex v
      dist[v][v] ← 0
   for each edge (u,v)
      dist[u][v] ← w(u,v)  // the weight of the edge (u,v)
   initNextArray()
   for k from 1 to |V|
      for i from 1 to |V|
         for j from 1 to |V|
            if dist[i][k] + dist[k][j] < dist[i][j] then
               dist[i][j] ← dist[i][k] + dist[k][j]
               next[i][j] ← next[k][j]

function Path (i, j)
   if dist[i][j] = ∞ then
     return "no path"
   var intermediate ← next[i][j]
   if intermediate = null then
     return " "   // the direct edge from i to j gives the shortest path
   else
     return Path(i, intermediate) + intermediate + Path(intermediate, j)

*/



void FloydWarshall( std::vector<star>& star_list )
{
    double dist[ STAR_COUNT ][ STAR_COUNT ];
    unsigned int next[ STAR_COUNT ][ STAR_COUNT ];

    //initialize the dist array to the star distances
    for( unsigned int i = 0 ; i < STAR_COUNT ; i++ )
    {
        for( unsigned int j = 0 ; j < STAR_COUNT ; j++ )
        {
            dist[i][j] = star_length( star_list[i] , star_list[j] );
            std::cout << " " << star_length(star_list[i] , star_list[j]);
            next[i][j] = NULL;
        }
        std::cout << "\n";
    }


    std::cout << "\n\n\n\n\nMy Distance Matrix";
    for( unsigned int i = 0 ; i < STAR_COUNT ; i++ )
    {
        for( unsigned int j = 0 ; j < STAR_COUNT ; j++ )
        {
            std::cout << " " << dist[i][j];
        }
        std::cout << "\n";
    }



    //Initialize Next Array
    for( unsigned int i = 0 ; i < STAR_COUNT ; i++ )
    {
        for( unsigned int j = 0 ; j < STAR_COUNT ; j++ )
        {
            if( i == j )
            {
                next[i][j] = 0;
            }
            else
            {
                next[i][j] = i;
            }
        }
    }

    for( unsigned int k = 0 ; k < STAR_COUNT ; k++ )
    {
        for( unsigned int i = 0 ; i < STAR_COUNT ; i++ )
        {
            for( unsigned int j = 0 ; j < STAR_COUNT ; j++ )
            {
                if( (dist[i][k] + dist[k][j]) < dist[i][j] )
                {
                    std::cout << "\n entered if";
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[k][j];
                }
            }
        }
    }

    std::cout << "\n\n";
    for( int i = 0 ; i < STAR_COUNT ; i++ )
    {
        for( int j = 0 ; j < STAR_COUNT ; j++ )
        {
            std::cout << "  " << std::setprecision(2) <<  next[i][j];
        }
        std::cout << "\n";
    }

    double running_total = 0;
    std::cout << "\n\n";
    for( int i = 0 ; i < STAR_COUNT ; i++ )
    {
        for( int j = 0 ; j < STAR_COUNT ; j++ )
        {
            running_total += dist[i][j];
            std::cout << " " << std::setprecision(1) << dist[i][j];
        }
        std::cout << "\n";
    }

    running_total = running_total / 2;
    std::cout << "\n\n\n\nTotal Distance = " << running_total;

    //std::cout << "\n\nintermediate = " << next[1][0];
    //std::string myPath = findPath( dist , next , 0 , 11 );
    //std::cout << "\n\n" << myPath;

}

/*
function Path (i, j)
   if dist[i][j] = ∞ then
     return "no path"
   var intermediate ← next[i][j]
   if intermediate = null then
     return " "   // the direct edge from i to j gives the shortest path
   else
     return Path(i, intermediate) + intermediate + Path(intermediate, j)
*/


std::string findPath( double dist[STAR_COUNT][STAR_COUNT] , unsigned int next[STAR_COUNT][STAR_COUNT] , unsigned int i , unsigned int j )
{
    /*
    unsigned int intermediate = next[i][j];
    if( intermediate == NULL )
    {
        return " ";
    }
    else
    {
        std::string temp1 = findPath( dist , next , i , intermediate );
        std::string temp2 = findPath( dist , next , intermediate , j );
        std::string temp3 = temp1;
        temp3 += temp1;
        temp3 += intermediate;
        temp3 += temp2;
        return temp3;
    }
    */
    double running_total = 0;

    for( unsigned int k = 0 ; k < i ; k++ )
    {
        for( unsigned int l ; l < j ; l++ )
        {
            running_total += dist[k][l];
        }
    }

    std::cout << "\n\n\n\nTotal Distance = " << running_total;
}
#endif // SHORTESTPATH_H_INCLUDED
