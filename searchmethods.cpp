//
//  searchmethods.cpp
//  GraphReachability
//
//  Created by Jerry Lacefield on 11/18/16.
//  Copyright © 2016 Jerry Lacefield. All rights reserved.
//

#include "searchmethods.h"

//=========================================
// binarySearch function
//=========================================
int binarySearch(int i, int j, int length, sparseArray neo[])
{
    int first = 0;
    int last = length - 1;
    int mid = 0;
    int x = 0;
    bool found = false;
    
    while (first <= last && !found)
    {
        mid = (first + last) / 2;
        
        if (neo[mid].index == i && neo[mid].vertex == j)
        {
            found = true;
            x = neo[mid].edge;
        }
        else if (neo[mid].index > i)
        {
            last = mid - 1;
        }
        else if (neo[mid].index < i)
        {
            first = mid + 1;
        }
        else if (neo[mid].index == i)
        {
            if (neo[mid].vertex < j)
            {
                first = mid + 1;
            }
            else
            {
                last = mid - 1;
            }
        }
    }
    
    return x;
}

//=========================================
// binarySearch function
// used to search a list that is known to
// contain the ij'th coordinates in a graph
//=========================================
int bsElemPosition(int i, int j, int length, sparseArray neo[])
{
    int first = 0;
    int last = length - 1;
    int mid = 0;
    int x = 0;
    bool found = false;
    
    while (first <= last && !found)
    {
        mid = (first + last) / 2;
        
        if (neo[mid].index == i && neo[mid].vertex == j)
        {
            found = true;
            x = mid;
        }
        else if (neo[mid].index > i)
        {
            last = mid - 1;
        }
        else if (neo[mid].index < i)
        {
            first = mid + 1;
        }
        else if (neo[mid].index == i)
        {
            if (neo[mid].vertex < j)
            {
                first = mid + 1;
            }
            else
            {
                last = mid - 1;
            }
        }
    }
    
    return x;
}

//============================================
// calcMaxVertices
// returns the max vertices of edge list
//============================================
int calcMaxVertices(string file)
{
    string str;
    ifstream ifs(file.c_str());
    
    int currMaxVertex = 0;
    
    while(getline(ifs, str))
    {
        if(!str.empty() && str.at(0) != '#')
        {
            stringstream ss(str.c_str());
            int a, b, c;
            ss >> a;
            ss >> b;
            ss >> c;
            
            if (b > currMaxVertex)
            {
                currMaxVertex = b;
            }
        }
    }
    
    return currMaxVertex;
}
