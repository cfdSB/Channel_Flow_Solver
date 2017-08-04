/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SolutionVariable.h
 * Author: cd8qvt
 *
 * Created on August 2, 2017, 8:28 PM
 */

#ifndef SOLUTIONVARIABLE_H
#define SOLUTIONVARIABLE_H

#include <vector>
#include <iostream>

class SolutionVariable {
public:
    enum variableType {FIXED_FIELD, SOLUTION_FIELD};
    
    SolutionVariable(std::string variableName, long size, variableType type);
    SolutionVariable(const SolutionVariable& orig);
    virtual ~SolutionVariable();
    void initializeVariable(double initValue);
    
    variableType GetType() const {
        return type;
    }

    std::string GetVariableName() const {
        return variableName;
    }

    std::vector<double>* GetVariableValues() const {
        return variableValues;
    }

private:
    std::string variableName;
    std::vector<double>* variableValues;
    variableType type;
};

#endif /* SOLUTIONVARIABLE_H */

