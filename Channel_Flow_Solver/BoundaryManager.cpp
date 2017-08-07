/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BoundaryManager.cpp
 * Author: cd8qvt
 * 
 * Created on August 5, 2017, 11:12 PM
 */

#include "BoundaryManager.h"

BoundaryManager::BoundaryManager(VolumeMesh *mesh): mesh(mesh) {
    boundaries = new std::vector<Boundary*>();
}

BoundaryManager::BoundaryManager(const BoundaryManager& orig) {
}

BoundaryManager::~BoundaryManager() {
    for(size_t i=0; i<boundaries->size(); i++){
        delete boundaries->at(i);
    }
    delete boundaries;
}

Boundary* BoundaryManager::createBoundary(std::string name, std::string plane, double faceCoordinate) {
    
    std::vector<Face*> matchingFaces = mesh->findFaces(plane,faceCoordinate,faceMatchingTolerance);
    std::vector<Face*> *boundaryFaces = new std::vector<Face*>();
    for(size_t i=0; i< matchingFaces.size(); i++){
        boundaryFaces->push_back(matchingFaces.at(i));
    }
    Boundary *newBoundary = new Boundary(name, boundaryFaces);
    boundaries->push_back(newBoundary);
    return newBoundary;
}

std::vector<Boundary*>* BoundaryManager::getBoundaries() {
    return boundaries;
}


