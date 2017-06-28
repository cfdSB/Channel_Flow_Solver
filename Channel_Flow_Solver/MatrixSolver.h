/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MatrixSolver.h
 * Author: cd8qvt
 *
 * Created on June 21, 2017, 2:33 PM
 */

#ifndef MATRIXSOLVER_H
#define MATRIXSOLVER_H

#include <memory>
#include <iostream>

class MatrixSolver {
    
public:
    
    MatrixSolver(long numberOfVariables, double** coefficientMatrix, double* rhsVector, double* solutionVector);
    MatrixSolver(const MatrixSolver& orig);
    virtual ~MatrixSolver();
    
    void iterateJacobi();
    
private:

    long numberOfVariables;
    double** coefficientMatrix;
    double* rhsVector;
    double* solutionVector;
    double residualTolerance = 1.0e-4;;
    
    double calculateResidual();
    double calculateVectorNorm(double* vector, long numberOfVariables);
};

#endif /* MATRIXSOLVER_H */

