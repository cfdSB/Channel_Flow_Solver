/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Boundary.cpp
 * Author: cd8qvt
 * 
 * Created on August 4, 2017, 5:13 PM
 */

#include "Boundary.h"

Boundary::Boundary(std::string name, std::vector<Face*> *faces):name(name), faces(faces) {
    boundaryConditions = new std::map<std::string, BoundaryCondition*>();
}

Boundary::Boundary(const Boundary& orig) {
}

Boundary::~Boundary() {
    delete faces;
    delete boundaryConditions;
}

void Boundary::addBoundaryCondition(std::string variableName, BoundaryCondition* bc) {
    boundaryConditions->insert(std::make_pair(variableName, bc));
}

