/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Boundary.h
 * Author: cd8qvt
 *
 * Created on August 4, 2017, 5:13 PM
 */

#ifndef BOUNDARY_H
#define BOUNDARY_H

#include <vector>
#include <map>
#include <iostream>
#include "BoundaryCondition.h"

class Face; //forward declaration

class Boundary {
public:
    Boundary(std::string name, std::vector<Face*> *faces);
    Boundary(const Boundary& orig);
    virtual ~Boundary();
    void addBoundaryCondition(std::string variableName, BoundaryCondition *bc);
    BoundaryCondition* getBoundaryCondition(std::string variableName) const;
    std::vector<Face*>* getFaces() const;
private:
    std::string name;
    std::vector<Face*> *faces;
    std::map<std::string, BoundaryCondition*> *boundaryConditions;
    
    void connectBoundaryToFaces();
};

#endif /* BOUNDARY_H */

