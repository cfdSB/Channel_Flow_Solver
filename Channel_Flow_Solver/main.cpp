/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: cd8qvt
 *
 * Created on May 15, 2017, 4:40 PM
 */

#include <cstdlib>
#include <vector>
#include <iostream>

#include "Point.h"
#include "FvCell.h"
#include "Face.h"
#include "MeshBuilder.h"
#include "MeshDescritizer.h"

using namespace std;
void printCell(FvCell* cell);

/*
 * 
 */
int main(int argc, char** argv) {
       
    int xCells = 5;
    int yCells = 5;
    int zCells = 5;
    
    double xMin = 0.0, xMax = 1.0, yMin = 0.0, yMax = 1.0, zMin = 0.0, zMax = 1.0;
    
    MeshBuilder mesher;
    mesher.buildMesh(xMin, xMax, yMin, yMax, zMin, zMax, xCells, yCells, zCells);
    mesher.printMeshReport();
    
    VolumeMesh* mesh = mesher.getVolumeMesh();
    std::unique_ptr<MeshDescritizer> discretizer(new MeshDescritizer());
    discretizer->computeDiscretizationCoefficients(mesh);

    return 0;
}





