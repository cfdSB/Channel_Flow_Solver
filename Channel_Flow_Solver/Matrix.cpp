/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Matrix.cpp
 * Author: cd8qvt
 * 
 * Created on June 2, 2017, 2:22 PM
 */

#include <memory>
#include "Matrix.h"

Matrix::Matrix(long numberOfVariables): numberOfVariables(numberOfVariables) {
    coefficientArray = NULL;
    variableArray = NULL;
    rhsArray = NULL;
    
    allocateArray();
}

Matrix::Matrix(const Matrix& orig) {
}

Matrix::~Matrix() {
    if(variableArray!=NULL){
        delete[] variableArray;
    }
    
    if(coefficientArray!=NULL){
        for(int i=0; i<numberOfVariables; i++){
            delete[] coefficientArray[i];
        }
        delete[] coefficientArray;
    }
    
    if(rhsArray!=NULL){
        delete[] rhsArray;
        
    }
}

void Matrix::allocateArray() {
    variableArray = new FvCell*[numberOfVariables];
    rhsArray = new double[numberOfVariables];
    
    coefficientArray = new double*[numberOfVariables];
    for(long i=0; i< numberOfVariables; i++){
        coefficientArray[i] = new double[numberOfVariables];
    }
}

void Matrix::setCoefficient(long row, long column, double value) {
    coefficientArray[row][column] = value;
}

void Matrix::setVariable(long row, FvCell* cell) {
    variableArray[row] = cell;
}

void Matrix::setRhs(long row, double value) {
    rhsArray[row] = value;
}

long Matrix::getVariableIndex(FvCell* cell) {
    long index = -1;
    for(long i=0; i<numberOfVariables; i++){
        FvCell* currentCell = variableArray[i];
        if(currentCell == cell){
            index = i;
            break;
        }
                
    }
    return index;
}

std::string Matrix::toString() {
    std::ostringstream output;
    
    for (long i=0; i<numberOfVariables; i++){
        for(long j=0; j< numberOfVariables; j++){
            output<<coefficientArray[i][j] << " ";
        }
        output<<i<< " ";
        output<<rhsArray[i];
        output<<"\n";
    }
   
   
    return output.str();
    
    
    
}




