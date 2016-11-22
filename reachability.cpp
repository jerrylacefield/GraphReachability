//
//  reachability.cpp
//  Reachability
//
//  Created by Jerry Lacefield on 11/15/16.
//  Copyright © 2016 Jerry Lacefield. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>

#include "ArgumentManager.h"
#include "makearray.h"
#include "searchmethods.h"

using namespace std;

GraphMatrix Matrix;

void doVectorMult(string, int, int, string);
void doDepthFirst(string, int, int, string);

int main(int argc, char *argv[])
{
    ArgumentManager am(argc, argv);
    
    string edgesFile = am.get("E");
    string labelFile = am.get("labels");
    string result = am.get("result");
    string source = am.get("source");
    string depth = am.get("k");
    string dfs = am.get("dfs");
    
    int s = atoi(source.c_str());
    int k = atoi(depth.c_str());
    
    if (dfs !="recursive" && dfs != "iterative")
    {
        //do vector-multiplication function
        doVectorMult(edgesFile, s, k, result);
    }
    else
    {
        if (dfs == "recursive")
        {
            //do depth-first search, recursively
            doDepthFirst(edgesFile, s, k, result);
        }
        else
        {
            //do depth-first search, iteratively
        }
    }
    
    return 0;
    
}

void doDepthFirst(string file, int s, int k, string outfile)
{
    //calculate number of vertices
    Matrix.calcMaxLength(file);
    Matrix.calcMaxVertices(file);
    
    const int GRAPH_SIZE = Matrix.getMaxLength();
    const int MAX_COLUMNS = Matrix.getMaxVertices();
    
    sparseArray *E = new sparseArray[GRAPH_SIZE];   //edges matrix
    sparseArray *S = new sparseArray[MAX_COLUMNS];  //source vector
    sparseArray *R = new sparseArray[MAX_COLUMNS];  //reachable vertices vector
    
    //setting default vectors
    Matrix.setDefaultVector(MAX_COLUMNS, S);
    Matrix.setDefaultVector(MAX_COLUMNS, R);
    Matrix.setReachableVertices(MAX_COLUMNS, R);
    
    //Matrix.printArray(MAX_COLUMNS, R);
    
    //reading contents of edge file into edge matrix
    Matrix.setEdgesMatrix(MAX_COLUMNS, file, E);
    
    //defining the source for the source vector
    Matrix.setSourcesVector(s, MAX_COLUMNS, S);
    
    //Matrix.printArray(MAX_COLUMNS, S);
    
    Matrix.dfsRecursive(s, k, 0, GRAPH_SIZE, E, S, R);
    
//    cout << "=== REACHABLE VERTICES ===" << endl;
//    Matrix.printArray(MAX_COLUMNS, R);
    Matrix.outputForward(outfile, R);
    
    delete [] E;
    delete [] S;
    delete [] R;
    
}

void doVectorMult(string file, int s, int k, string outfile)
{
    //defining matrix and row vector characteristics
    Matrix.calcMaxLength(file);
    Matrix.calcMaxVertices(file);
    
    const int GRAPH_SIZE = Matrix.getMaxLength();
    const int MAX_COLUMNS = Matrix.getMaxVertices();
    
    sparseArray *E = new sparseArray[GRAPH_SIZE];   //edges matrix
    sparseArray *S = new sparseArray[MAX_COLUMNS];  //source vector
    sparseArray *M = new sparseArray[MAX_COLUMNS];  //multiplication results vector
    sparseArray *R = new sparseArray[MAX_COLUMNS];  //reachable vertices vector
    
    //setting default i,j values for the row vectors
    Matrix.setDefaultVector(MAX_COLUMNS, S);
    Matrix.setDefaultVector(MAX_COLUMNS, M);
    Matrix.setDefaultVector(MAX_COLUMNS, R);
    
    //defining the edges for the matrix
    Matrix.setEdgesMatrix(MAX_COLUMNS, file, E);
    
    //defining the source for the row vector
    Matrix.setSourcesVector(s, MAX_COLUMNS, S);
    
//    cout << "=== Edges  Matrix ===" << endl;
//    Matrix.printArray(GRAPH_SIZE, E);
    
    //calculating reachable vertices
    Matrix.updateReached(MAX_COLUMNS, R, S);
    
    int count = 0;
    
    while (!Matrix.allVerticesOn(0, MAX_COLUMNS, R) && count < k)
    {
//        cout << "=== Source Vector " << count + 1 <<" ===" << endl;
//        Matrix.printArray(MAX_COLUMNS, S);
        
        //do multiplication
        Matrix.multiply(MAX_COLUMNS, GRAPH_SIZE, S, E, M);
        
        //use contents of vResults to update flags in vReached
        Matrix.updateReached(MAX_COLUMNS, R, M);
        
        //copy contents of vResults to vSources
        Matrix.updateSources(MAX_COLUMNS, S, M);
        
//        cout << "All Vertices Reached Check: " << Matrix.allVerticesOn(0, MAX_COLUMNS, R) << endl;
        
        count++;
    }
    
//    cout << "==== FINAL REACHED VERTICES ====" << endl;
//    Matrix.printArray(MAX_COLUMNS, R);
    Matrix.outputForward(outfile, R);
    
    delete [] E;
    delete [] S;
    delete [] M;
    delete [] R;
}
