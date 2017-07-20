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
#include "MatrixSolver.h"

using namespace std;


/*
 * 
 */
int main(int argc, char** argv) {
       
    int xCells = 6;
    int yCells = 6;
    int zCells = 6;
    
    double xMin = 0.0, xMax = 0.3, yMin = 0.0, yMax = 0.3, zMin = 0.0, zMax = 0.3;
    
    MeshBuilder mesher;
    mesher.buildMesh(xMin, xMax, yMin, yMax, zMin, zMax, xCells, yCells, zCells);
    mesher.printMeshReport();
    
    //define material
    PhysicsContinuum pc;
    //pc.setThermalConductivity(10);
    pc.setDiffusionCoefficient(10);
    
    VolumeMesh* mesh = mesher.getVolumeMesh();
    std::unique_ptr<MeshDescritizer> discretizer(new MeshDescritizer(mesh, &pc));
    discretizer->setConvectionDifferencingScheme(MeshDescritizer::ConvectionDifferencingScheme::CENTRAL);
    discretizer->setsimulationType(MeshDescritizer::SimulationType::DIFFUSION);
    discretizer->computeDiscretizationCoefficients();
    discretizer->printCoefficients();
    
    std::unique_ptr<BoundaryConditionsManager> bcManager (new BoundaryConditionsManager(mesh));
    //std::string plane = "x"; double coord = 0.0; double tolerance = 1.0e-6; double bcValue = 500.00;
    std::string plane = "x"; double coord = 0.0; double tolerance = 1.0e-6; double bcValue = 500.00;
    bcManager->createBoundaryCondition(plane, coord, tolerance, BoundaryCondition::BcType::FIXED_FLUX, bcValue);
    std::string plane2 = "z"; double coord2 = 0.0; double tolerance2 = 1.0e-6; double bcValue2 = 0.00;
    bcManager->createBoundaryCondition(plane2, coord2, tolerance2, BoundaryCondition::BcType::ADIABATIC, bcValue2);
    bcManager->createBoundaryCondition("x", 0.3, 1.0e-6, BoundaryCondition::BcType::FIXED_VALUE,300.00);
    bcManager->createBoundaryCondition("y", 0.0, 1.0e-6, BoundaryCondition::BcType::ADIABATIC,0.0);
    bcManager->createBoundaryCondition("y", 0.3, 1.0e-6, BoundaryCondition::BcType::ADIABATIC,0.0);
    bcManager->createBoundaryCondition("z", 0.3, 1.0e-6, BoundaryCondition::BcType::ADIABATIC,0.0);
    bcManager->printBoundaryConditionsReport();
  
    discretizer->updateCoefficients(bcManager->getBoundaryConditions());
    discretizer->printCoefficients();
    
    Matrix* coefficientMatrix = discretizer->buildMatrix();
    std::string output = coefficientMatrix->toString();
    std::cout<<output;
    
    double** A = coefficientMatrix->getCoefficientArray();
    double* rhs = coefficientMatrix->getRhsArray();
    long numberOfVariables = coefficientMatrix->getNumberOfVariables();
    
    std::unique_ptr<double[]> solnVector(new double[numberOfVariables]);
    
    MatrixSolver *solver = new MatrixSolver(numberOfVariables,A,rhs,solnVector.get());
    solver->iterateJacobi();

    std::cout << "Solution" << std::endl;
    for (long i = 0; i < numberOfVariables; i++) {
        std::cout << solnVector[i] << std::endl;
    }
    
    return 0;
}





