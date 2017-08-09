/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SolutionVariable.cpp
 * Author: cd8qvt
 * 
 * Created on August 2, 2017, 8:28 PM
 */

#include "SolutionVariable.h"

SolutionVariable::SolutionVariable(std::string variableName, long size, variableType vType): variableName(variableName),
type(vType){
    variableValues = new std::vector<double>(size);
}

SolutionVariable::SolutionVariable(const SolutionVariable& orig) {
}

SolutionVariable::~SolutionVariable() {
    variableValues->clear();
    delete variableValues;
}

void SolutionVariable::initializeVariable(double initValue) {
    for (size_t i=0; i< variableValues->size(); i++){
        variableValues->at(i) = initValue;
    }
}

