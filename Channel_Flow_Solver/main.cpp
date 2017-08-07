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
#include "Material.h"
#include "SolutionManager.h"
#include "BoundaryManager.h"

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
    Material air;
    air.setDiffusionCoefficient(10.0);
    PhysicsContinuum pc;
    pc.setMaterial(&air);
    
    VolumeMesh* mesh = mesher.getVolumeMesh();
    
    std::unique_ptr<BoundaryManager> bndManager(new BoundaryManager(mesh));
    Boundary *bnd_xm = bndManager->createBoundary("xm", "x", xMin);
    Boundary *bnd_xp = bndManager->createBoundary("xp", "x", xMax);
    Boundary *bnd_ym = bndManager->createBoundary("ym", "y", yMin);
    Boundary *bnd_yp = bndManager->createBoundary("yp", "y", yMax);
    Boundary *bnd_zm = bndManager->createBoundary("zm", "z", zMin);
    Boundary *bnd_zp = bndManager->createBoundary("zp", "z", zMax);
    
    std::unique_ptr<SolutionManager> solManager (new SolutionManager(mesh));
    SolutionVariable* vel_i = solManager->createSolutionVariable("i_velocity", SolutionVariable::variableType::FIXED_FIELD);
    vel_i->initializeVariable(30.0);
    SolutionVariable* vel_j = solManager->createSolutionVariable("j_velocity", SolutionVariable::variableType::FIXED_FIELD);
    vel_j->initializeVariable(10.0);
    SolutionVariable* vel_k = solManager->createSolutionVariable("k_velocity", SolutionVariable::variableType::FIXED_FIELD);
    vel_k->initializeVariable(10.0);
    SolutionVariable* temperature = solManager->createSolutionVariable("Temperature", SolutionVariable::variableType::SOLUTION_FIELD);
    temperature->initializeVariable(0.0);

    //debug statements
    std::vector<FvCell*> *cells = mesh->getCells();
    for (size_t i = 0; i < cells->size(); i++) {
        double val1 = *(cells->at(i)->getSolutionField("i_velocity"));
        double val2 = *(cells->at(i)->getSolutionField("j_velocity"));
        std::cout << val1 << ", " << val2 << std::endl;
    }
    
    std::unique_ptr<BoundaryConditionsManager> bcManager (new BoundaryConditionsManager(mesh));
    BoundaryCondition* bc_xm = bcManager->createBoundaryCondition(temperature, BoundaryCondition::BcType::FIXED_FLUX, 500.00);
    BoundaryCondition* bc_zm = bcManager->createBoundaryCondition(temperature, BoundaryCondition::BcType::ADIABATIC, 0.0);
    BoundaryCondition* bc_xp = bcManager->createBoundaryCondition(temperature, BoundaryCondition::BcType::FIXED_VALUE,300.00);
    BoundaryCondition* bc_ym = bcManager->createBoundaryCondition(temperature, BoundaryCondition::BcType::ADIABATIC,0.0);
    BoundaryCondition* bc_yp = bcManager->createBoundaryCondition(temperature, BoundaryCondition::BcType::ADIABATIC,0.0);
    BoundaryCondition* bc_zp = bcManager->createBoundaryCondition(temperature, BoundaryCondition::BcType::ADIABATIC,0.0);
    BoundaryCondition* bc_vel1_xm = bcManager->createBoundaryCondition(vel_i, BoundaryCondition::BcType::FIXED_VALUE, 0.1);
    BoundaryCondition* bc_vel1_xp = bcManager->createBoundaryCondition(vel_i, BoundaryCondition::BcType::FIXED_VALUE, 0.1);
    BoundaryCondition* bc_vel1_rest = bcManager->createBoundaryCondition(vel_i, BoundaryCondition::BcType::FIXED_VALUE, 0.0);
    BoundaryCondition* bc_vel2_rest = bcManager->createBoundaryCondition(vel_j, BoundaryCondition::BcType::FIXED_VALUE, 0.0);
    BoundaryCondition* bc_vel3_rest = bcManager->createBoundaryCondition(vel_k, BoundaryCondition::BcType::FIXED_VALUE, 0.0);



    bcManager->printBoundaryConditionsReport();    
    
    bnd_xm->addBoundaryCondition(bc_xm); bnd_xm->addBoundaryCondition(bc_vel1_xm); bnd_xm->addBoundaryCondition(bc_vel2_rest); bnd_xm->addBoundaryCondition(bc_vel3_rest);
    bnd_xp->addBoundaryCondition(bc_xp); bnd_xp->addBoundaryCondition(bc_vel1_xp); bnd_xp->addBoundaryCondition(bc_vel2_rest); bnd_xp->addBoundaryCondition(bc_vel3_rest);
    bnd_ym->addBoundaryCondition(bc_ym); bnd_ym->addBoundaryCondition(bc_vel1_rest); bnd_ym->addBoundaryCondition(bc_vel2_rest); bnd_ym->addBoundaryCondition(bc_vel3_rest);
    bnd_yp->addBoundaryCondition(bc_yp); bnd_yp->addBoundaryCondition(bc_vel1_rest); bnd_yp->addBoundaryCondition(bc_vel2_rest); bnd_yp->addBoundaryCondition(bc_vel3_rest);
    bnd_zm->addBoundaryCondition(bc_zm); bnd_zm->addBoundaryCondition(bc_vel1_rest); bnd_zm->addBoundaryCondition(bc_vel2_rest); bnd_zm->addBoundaryCondition(bc_vel3_rest);
    bnd_zp->addBoundaryCondition(bc_zp); bnd_zp->addBoundaryCondition(bc_vel1_rest); bnd_zp->addBoundaryCondition(bc_vel2_rest); bnd_zp->addBoundaryCondition(bc_vel3_rest);
    
    
    std::unique_ptr<MeshDescritizer> discretizer(new MeshDescritizer(mesh, &pc));
    discretizer->computeDiscretizationCoefficients();
    discretizer->printCoefficients();
   
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





