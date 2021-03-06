/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BoundaryCondition.h
 * Author: cd8qvt
 *
 * Created on May 25, 2017, 4:45 PM
 */

#ifndef BOUNDARYCONDITION_H
#define BOUNDARYCONDITION_H
#include "Face.h"
#include <vector>
#include "Object.h"
#include "SolutionVariable.h"

class BoundaryCondition: public Object {
    
public:
    enum BcType {FIXED_VALUE, ADIABATIC, FIXED_FLUX};
    
    BoundaryCondition(SolutionVariable *variable, BcType type, double value);
    BoundaryCondition(const BoundaryCondition& orig);
    virtual ~BoundaryCondition();    
    BcType getType() const;
    SolutionVariable* getSolutionVariable() const;
    double getValue() const;
    std::string toString() override;

private:
    BcType type;
    SolutionVariable *variable;
    double value;

};

#endif /* BOUNDARYCONDITION_H */

