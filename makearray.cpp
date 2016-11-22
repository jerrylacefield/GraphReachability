//
//  makearray.cpp
//  Reachability
//
//  Created by Jerry Lacefield on 11/16/16.
//  Copyright © 2016 Jerry Lacefield. All rights reserved.
//

#include "makearray.h"
#include "searchmethods.h"

sparseArray::sparseArray()
{
    index = 0;
    vertex = 0;
    edge = 0;
    visited = false;
}

sparseArray::sparseArray(int i, int j, int v)
{
    index = i;
    vertex = j;
    edge = v;
    visited = false;
}

//====================================
// Default Constructor
//====================================
GraphMatrix::GraphMatrix()
{
    //cout << "graph object created" << endl;
    currentLength = 0;
    maxLength = 0;
    nextOpen = 0;
}

//====================================
// Default Constructor w/Parameters
//====================================
GraphMatrix::GraphMatrix(int n)
{
    currentLength = n;
    maxLength = n;
}

//====================================
// Destructor
//====================================
GraphMatrix::~GraphMatrix()
{
    //delete [] matrix;
}

//====================================
// setArray function
//====================================
void GraphMatrix::setEdgesMatrix(int bounds, string file, sparseArray neo[])
{
    ifstream ifs;
    string str;
    
    int lewp = 0;   //lewp variable will dynamically set the actual length of list
    
    ifs.open(file.c_str());
    while (getline(ifs, str))
    {
        if (!str.empty() && str.at(0) != '#')
        {
            stringstream ss(str.c_str());
            int i, j, v;
            
            ss >> i;
            ss >> j;
            ss >> v;
            
            if (i > 0 && j > 0)
            {
                if (i == bounds && j == bounds)
                {
                    neo[lewp].index = i;
                    neo[lewp].vertex = j;
                    neo[lewp].edge = v;
                    setCurrentLength(lewp + 1);
                    lewp++;
                }
                else if (v != 0)
                {
                    //cout << "Placing r,c,v " << i << "," << j << "," << v << " into position " << lewp << endl;
                    neo[lewp].index = i;
                    neo[lewp].vertex = j;
                    neo[lewp].edge = v;
                    setCurrentLength(lewp + 1);
                    lewp++;
                }
                else
                {
                    
                }
            }
        }
        else
        {
            //skipping line
            //bad characters
        }
    }
    
    matrix = neo;
    
    ifs.close();
    
}

//=============================================
// setDefaultVector
//=============================================
void GraphMatrix::setDefaultVector(int lim, sparseArray neo[])
{
    for (int elem = 0; elem < lim; elem++)
    {
        neo[elem].index = 1;
        neo[elem].vertex = elem + 1;
        neo[elem].edge = 0;
        neo[elem].visited = false;
    }
}

//=============================================
// setReachableVertices
//=============================================
void GraphMatrix::setReachableVertices(int limit, sparseArray R[])
{
    for (int elem = 0; elem < limit; elem++)
    {
        R[elem].index = 1;
        R[elem].vertex = 0;
        R[elem].edge = 0;
        R[elem].visited = false;
    }
}

//=============================================
// setSourceVector
//=============================================
void GraphMatrix::setSourcesVector(int s, int lim, sparseArray neo[])
{
        setEdge(1, s - 1, neo);
}

//=============================================
// updateSV
// updates the source vector with next sources
//=============================================
void GraphMatrix::updateSources(int lim, sparseArray neo[], sparseArray trinity[])
{
    
    //contents of trinity will be copied to neo
    
    for (int elem = 0; elem < lim; elem++)
    {
        neo[elem].edge = trinity[elem].edge;
    }
}

//=============================================
// updateSourceFlag
//=============================================
void GraphMatrix::updateSourceFlag(int s, sparseArray S[])
{
    S[s].edge = 1;
}

//=============================================
// updateSourceVisit
//=============================================
void GraphMatrix::updateSourceVisit(int s, sparseArray S[], bool t)
{
    S[s].visited = t;
}

//=============================================
// updateResults
//=============================================
void GraphMatrix::updateReached(int lim, sparseArray neo[], sparseArray trinity[])
{
    
    //contents of trinity will be used to update neo
    
    for (int elem = 0; elem < lim; elem++)
    {
        if (neo[elem].edge == 0 && trinity[elem].edge > 0)
            neo[elem].edge = trinity[elem].edge;
    }
}

//=============================================
// setSortStatus
//=============================================
void GraphMatrix::setSortStatus(bool status)
{
    sortStatus = status;
}

//=============================================
// setCurrentLength
// stores the current length in currentLength
//=============================================
void GraphMatrix::setCurrentLength(int n)
{
    currentLength = n;
}

//=============================================
// calcMaxLength function used to return the
// number of lines in the sparse file
//=============================================
void GraphMatrix::calcMaxLength(string file)
{
    string str;
    ifstream ifs(file.c_str());
    int n = 0;
    
    while(getline(ifs, str))
    {
        if (!str.empty() && str.at(0) != '#')
        {
            n++;
        }
    }
    
    maxLength = n;
}

//============================================
// calcMaxVertices
// returns the max vertices of edge list
//============================================
void GraphMatrix::calcMaxVertices(string file)
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
    
    maxVertex = currMaxVertex;
}

//==============================================
// setElement function used to set the row, col,
// and value at ij for the specified string
//==============================================
void GraphMatrix::setEdge(int v, int elem, sparseArray neo[])
{
    neo[elem].edge = v;
}

//============================================
// multiply function
//============================================
void GraphMatrix::multiply(int vectorLength, int matrixLength, sparseArray neo[], sparseArray morpheus[], sparseArray reddress[])
{
    //array neo[] represents the row vector
    //array morpheus[] represents the edge matrix
    //array reddress[] represents the results matrix

    int i, j, k;
    //int v = 0;
    
    for (i = 1; i < 2; i++)
    {
        for (j = 1; j < vectorLength + 1; j++)
        {
            int targetIndex, targetVertex, targetEdge, targetElem;
            int vectorValue, matrixValue;
            targetEdge = 0;
            targetElem = 0;
            
            for (k = 1; k < vectorLength + 1; k++)
            {
                targetIndex = 1;
                targetVertex = j;
                
                vectorValue = binarySearch(1, k, vectorLength, neo);
                if (vectorValue != 0)
                {
                    matrixValue = binarySearch(k, j, matrixLength, morpheus);
                
                    targetEdge += (vectorValue * matrixValue);
                
                    //redefining target edge to show if it's been reached
                    if (targetEdge > 0)
                        targetEdge = 1;
                    else
                        targetEdge = 0;
                }
                else
                {
                    targetEdge += 0;
                }
                
                targetElem = bsElemPosition(targetIndex, targetVertex, vectorLength, reddress);
            }

            setEdge(targetEdge, targetElem, reddress);
        }
    }
}

//============================================
// depthFirstSearch
//============================================
void GraphMatrix::dfsRecursive(int s, int k, int c, int max, sparseArray E[], sparseArray S[], sparseArray R[])
{
    //cout << "entered dfs recursive" << endl;
//    int V = getMaxVertices();
    
//    int elem = getNextOpen();
//    cout << "Next open slot in R is " << elem << endl;
//    cout << "Source = " << s << endl;
    
    while (c <= k && !S[s - 1].visited)
    {
//        cout << "DFS While Loop Pass " << c << " where k is " << k << "\n-----------------------" << endl;
        for (int i = 0; i < max; i++)
        {
            //cout << "DFS For Loop Pass " << i << endl;
            
            if (E[i].index == s)// && !E[i].visited) //&& !S[E[i].vertex].visited)
            {
//                cout << "S[" << s - 1 << "] visit status: " << S[s].visited << endl;
                if (!S[s - 1].visited)
                {
                    int elem = getNextOpen();
                
//                    cout << "Next open slot @ R[" << elem << "]" << endl;
//                    cout << "Source " << s << " found @ E[" << i << "]" << endl;
                
                    int nextSource = E[i].vertex;    //setting v to be value of vertex at i-th element of matrix E
//                    cout << "Next Source will be " << nextSource << endl;

//                    R[elem].vertex = s;
//                    R[elem].edge = 1;
                    updateSourceFlag(nextSource - 1, S);
                    setNextOpen(elem + 1);
                    updateSourceVisit(s - 1, S, true);

//                    cout << "Current Source Vector" << "\n====================" << endl;
//                    printArray(V, S);
//                    cout << "Current Reached Vertices" << "\n====================" << endl;
//                    printArray(V, R);
                
                    dfsRecursive(nextSource, k, c + 1, max, E, S, R);
                    R[elem].vertex = s;
                    R[elem].edge = 1;
                    updateSourceVisit(s - 1, S, true);
                
//                    cout << "Current Reached Vertices" << "\n====================" << endl;
//                    printArray(V, R);
                
                    //cout << "E[" << i <<"].index = " << s << " and is not visited; store " << v << " into R[" << elem << "]" << endl;
                
//                    dfsRecursive(nextSource, k, c + 1, max, E, S, R);
                }
                else
                {
//                    int elem = getNextOpen();
//                    cout << "Next open slot @ R[" << elem << "]" << endl;
//                    cout << "Source " << s << " found @ E[" << i << "]" << endl;

                    int nextSource = E[i].vertex;
//                    cout << "Next Source will be " << nextSource << endl;
                    
                    updateSourceFlag(nextSource - 1, S);
//                    cout << "Current Source Vector (Part 2)" << "\n====================" << endl;
//                    printArray(V, S);
                    
                    dfsRecursive(nextSource, k, c + 1, max, E, S, R);
                    
//                    cout << "Current Reached Vertices (Part 2)" << "\n====================" << endl;
//                    printArray(V, R);
                }
                
            }
            else if (!verticeExists(s, max, E))
            {
                
//                cout << "vertice does not point to anything" << endl;
                int elem = getNextOpen();
                
                R[elem].vertex = s;
                R[elem].edge = 1;
                updateSourceVisit(s - 1, S, true);
//                cout << "Final Reached Vertices" << "\n====================" << endl;
//                printArray(V, R);
            }
            
//            if (E[i].index > s)
//            {
//                i = max;
//                k = c;
//            }
        }
        c++;
    }
}

//============================================
// setNextOpen
//============================================
void GraphMatrix::setNextOpen(int n)
{
    nextOpen = n;
}

//============================================
// verticeExists
// returns true if vertice exists
//============================================
bool GraphMatrix::verticeExists(int s, int size, sparseArray S[])
{
    bool test = false;
    int i = 0;
    
    while (i < size && !test)
    {
        if (S[i].index == s)
        {
            test = true;
        }
        i++;
    }
    
    return test;
}

//============================================
// getIndex
// returns the index of the requested element
//============================================
int GraphMatrix::getIndex(int elem, sparseArray neo[])
{
    return neo[elem].index;
}

//============================================
// getVertex
// returns the vertex of the requested element
//============================================
int GraphMatrix::getVertex(int elem, sparseArray neo[])
{
    return neo[elem].vertex;
}

//============================================
// getIndexMax
// returns the maximum source index value
//============================================
int GraphMatrix::getMaxVertices()
{
    return maxVertex;
}

//============================================
// getCurrLength
// returns the current length of sparse array
// where edges are greater than 0
//============================================
int GraphMatrix::getCurrentLength()
{
    return currentLength;
}

//============================================
// getMaxLength
// returns the maximum length of sparse array
//============================================
int GraphMatrix::getMaxLength()
{
    return maxLength;
}

//============================================
// allVerticesOn
//============================================
bool GraphMatrix::allVerticesOn(int elem, int lim, sparseArray neo[])
{
    bool allActive = true;
    
    while (allActive && elem < lim)
    {
        if (neo[elem].edge == 0)
            allActive = false;
        
        elem++;
    }
    
    return allActive;
}

//============================================
// getNextOpen
//============================================
int GraphMatrix::getNextOpen()
{
    return nextOpen;
}

//============================================
// printArray
// prints contents of an array
//============================================
void GraphMatrix::printArray(int limit, sparseArray neo[])
{
    int elem = 0;
//    int len = getCurrentLength();
    
    int maxV = getMaxVertices();
    
    while (elem < limit)
    {
        if (neo[elem].edge != 0)
        {
            if (neo[elem].index == maxV && neo[elem].vertex == maxV)
            {
                cout << neo[elem].index << " " << neo[elem].vertex << " " << neo[elem].edge << " " << neo[elem].visited << endl;
            }
            else
            {
                cout << neo[elem].index << " " << neo[elem].vertex << " " << neo[elem].edge << " " << neo[elem].visited << endl;
            }
        }
        
        elem++;
    }
    
}

//===========================================
// outputFoward function sends the contents
// of the results array to the specified file
//===========================================
void GraphMatrix::outputForward(string outfile, sparseArray neo[])
{
    int elem = 0;
    int length = getMaxVertices();
    
    ofstream ofs(outfile.c_str());
    
    //std::cout << "writing to file ... " << length << " lines" << std::endl;
    
    //write the header to outfile
    //ofs << "### MATRIX C = A * B\n#" << endl;
    
    while (elem < length)
    {
        if (neo[elem].edge != 0)
        {
            //std::cout << "outputing to line " << index << std::endl;
            ofs << neo[elem].vertex << endl;
        }
        elem++;
    }
    
    ofs.close();
}
