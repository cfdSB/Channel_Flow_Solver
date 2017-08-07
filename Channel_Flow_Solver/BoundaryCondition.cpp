/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BoundaryCondition.cpp
 * Author: cd8qvt
 * 
 * Created on May 25, 2017, 4:45 PM
 */

#include "BoundaryCondition.h"
#include <sstream>

BoundaryCondition::BoundaryCondition(SolutionVariable *variable, BcType type, double value)
:variable(variable), type(type), value(value){
}

BoundaryCondition::BoundaryCondition(const BoundaryCondition& orig) {
}

BoundaryCondition::~BoundaryCondition() {
}

BoundaryCondition::BcType BoundaryCondition::getType() {
    return type;
}



double BoundaryCondition::getValue() {
    return value;
}

std::string BoundaryCondition::toString() {
    std::ostringstream str;
    if(type == BcType::FIXED_VALUE){
        str<<"BcType : Fixed Value"<<std::endl;
    }else if(type == BcType::ADIABATIC){
        str << "BcType : Adiabatic"<<std::endl;
    }
    
    str << "Bc Value: " << value << std::endl;
    
    return str.str();
}


