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
#include "BoundaryConditionsManager.h"
#include "PhysicsContinuum.h"

using namespace std;


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
    std::unique_ptr<MeshDescritizer> discretizer(new MeshDescritizer(mesh));
    discretizer->computeDiscretizationCoefficients();
    discretizer->printCoefficients();
    
    std::unique_ptr<BoundaryConditionsManager> bcManager (new BoundaryConditionsManager(mesh));
    std::string plane = "x"; double coord = 0.0; double tolerance = 1.0e-6; double bcValue = 100.00;
    bcManager->createBoundaryCondition(plane, coord, tolerance, BoundaryCondition::BcType::FIXED_VALUE, bcValue);
    std::string plane2 = "z"; double coord2 = 0.0; double tolerance2 = 1.0e-6; double bcValue2 = 0.00;
    bcManager->createBoundaryCondition(plane2, coord2, tolerance2, BoundaryCondition::BcType::ADIABATIC, bcValue2);
    bcManager->printBoundaryConditionsReport();

    PhysicsContinuum pc;
    pc.setThermalConductivity(10);
    
    discretizer->updateCoefficients(bcManager->getBoundaryConditions());
    discretizer->updateCoefficients(&pc);
    discretizer->printCoefficients();
    
    return 0;
}





