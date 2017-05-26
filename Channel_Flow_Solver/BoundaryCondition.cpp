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

BoundaryCondition::BoundaryCondition(BcType type, std::vector<Face*> faces, double value)
:type(type), faces(faces), value(value){
}

BoundaryCondition::BoundaryCondition(const BoundaryCondition& orig) {
}

BoundaryCondition::~BoundaryCondition() {
}

BoundaryCondition::BcType BoundaryCondition::getType() {
    return type;
}

std::vector<Face*> BoundaryCondition::getFaces() {
    return faces;
}

double BoundaryCondition::getValue() {
    return value;
}


