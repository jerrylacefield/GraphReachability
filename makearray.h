//
//  makearray.h
//  Reachability
//
//  Created by Jerry Lacefield on 11/15/16.
//  Copyright © 2016 Jerry Lacefield. All rights reserved.
//

#ifndef MAKEARRAY_H
#define MAKEARRAY_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
using namespace std;

struct sparseArray
{
    int index;
    int vertex;
    int edge;
    bool visited;
    sparseArray();
    sparseArray(int i, int j, int v);
};

class GraphMatrix
{
private:
    int currentLength;      //current length of list
    int maxLength;          //max length allowed for list
    int maxVertex;        //defines upper source bound of sparseArray
    bool sortStatus;        //sort status indicator
    int nextOpen;       //value that defines next open slot in Reachable vector from DFS call

public:
    //constructors & destructor
    GraphMatrix();        //default constructor
    GraphMatrix(int);   //default constructor accepts parameters
    ~GraphMatrix();       //destructor
    
    sparseArray* matrix;  //pointer of sparseArray type
    
    //setters
    void setEdgesMatrix(int, string, sparseArray[]);                //read contents of Edges file into sparse matrix
    void setDefaultVector(int, sparseArray[]);                      //defines the default row vector with each edge set to 0
    void setReachableVertices(int, sparseArray[]);                  //defines the reachable vertices for DFS
    void setSourcesVector(int, int, sparseArray[]);                 //define the Source vector
    void updateSources(int, sparseArray[], sparseArray[]);          //redefines the Source vector for VM functions
    void updateSourceFlag(int, sparseArray[]);                      //updates Source vector for DFS functions
    void updateSourceVisit(int, sparseArray[], bool);                     //updates Source vector visit flag for DFS functions
    
    void updateReached(int, sparseArray[], sparseArray[]);          //updates the Results vector
    void setSortStatus(bool);                                       //sets sort status of list
    void setCurrentLength(int);                                     //sets current length of list
    void calcMaxLength(string);                                     //calculate and set max possible length of array
    void calcMaxVertices(string);
    void setEdge(int, int, sparseArray[]);
    void multiply(int, int, sparseArray[], sparseArray[], sparseArray[]);
    void dfsRecursive(int s, int k, int counter, int max, sparseArray E[], sparseArray S[], sparseArray R[]);
    void setNextOpen(int);
    bool verticeExists(int, int, sparseArray[]);
    
    //getters
    int getIndex(int, sparseArray[]);
    int getVertex(int, sparseArray[]);
    int getMaxVertices();
    int getCurrentLength();
    int getMaxLength();
    bool allVerticesOn(int, int, sparseArray[]);
    int getNextOpen();
    
    void printArray(int, sparseArray[]);
    void outputForward(string outfile, sparseArray[]);
    
};


#endif /* makearray_h */
