/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Matrix.h
 * Author: cd8qvt
 *
 * Created on June 2, 2017, 2:22 PM
 */

#ifndef MATRIX_H
#define MATRIX_H

#include "Object.h"
#include <sstream>
#include"FvCell.h"

class FvCell;   //forward declaration

class Matrix: public Object {

public:
    double** getCoefficientArray() const {
        return coefficientArray;
    }

    long getNumberOfVariables() const {
        return numberOfVariables;
    }

    double* getRhsArray() const {
        return rhsArray;
    }

public:
    Matrix(long numberOfVariables);
    Matrix(const Matrix& orig);
    virtual ~Matrix();
    void setCoefficient(long row, long column, double value);
    void setVariable(long row, FvCell* cell);
    void setRhs(long row, double value);
    long getVariableIndex(FvCell* cell);
    std::string toString() override;

private:
    long numberOfVariables; //variable numbers
    double** coefficientArray;  //2D array of double
    FvCell** variableArray;     //1D array of FvCell*
    double* rhsArray;           //1D array of double
    
    void allocateArray();

};

#endif /* MATRIX_H */

