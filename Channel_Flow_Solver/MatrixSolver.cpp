/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   JacobiSolver.cpp
 * Author: cd8qvt
 * 
 * Created on June 21, 2017, 2:33 PM
 */

#include "MatrixSolver.h"
#include <cmath>

MatrixSolver::MatrixSolver(long numberOfVariables, double** coefficientMatrix, double* rhsVector, double* solutionVector):
numberOfVariables(numberOfVariables), coefficientMatrix(coefficientMatrix), rhsVector(rhsVector), solutionVector(solutionVector){
}

MatrixSolver::MatrixSolver(const MatrixSolver& orig) {
}

MatrixSolver::~MatrixSolver() {
}

void MatrixSolver::iterateJacobi() {
    std::unique_ptr<double[]> tmpSolution(new double[numberOfVariables]);
    
    //initialize tmp solution with initial solution
    for(long i=0; i< numberOfVariables; i++){
        tmpSolution[i]= solutionVector[i];
    }

    double residual =0.0;
    do {
        for (long i = 0; i < numberOfVariables; i++) {
            double sum = 0.0;
            for (long j = 0; j < numberOfVariables; j++) {
                if (j != i) {
                    sum = sum + coefficientMatrix[i][j] * solutionVector[j];
                }
            }
            tmpSolution[i] = (rhsVector[i] - sum) / coefficientMatrix[i][i];
        }
        residual = calculateResidual();
        std::cout<< "residual: " << residual << std::endl;
        
        for (long i = 0; i < numberOfVariables; i++) {
            solutionVector[i] = tmpSolution[i];
        }
        
    } while (residual > residualTolerance);

}

double MatrixSolver::calculateResidual() {
    std::unique_ptr<double[]> errorVector(new double[numberOfVariables]);
    
    for(long i=0; i< numberOfVariables; i++){
        
        double sum = 0;
        for(long j=0; j<numberOfVariables; j++){
            sum = sum + coefficientMatrix[i][j]*solutionVector[j];
        }
        
        errorVector[i]= rhsVector[i] - sum;
    }
    double residualNorm = calculateVectorNorm(errorVector.get(), numberOfVariables);
    
    return residualNorm;
}

double MatrixSolver::calculateVectorNorm(double* vector, long numberOfVariables) {
    double norm = 0.0;
    
    for(long i=0; i< numberOfVariables; i++){
        norm = norm + pow(vector[i], 2.0);
    }
    norm = sqrt(norm);
    
    return norm;
}


