/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BoundaryConditionsManager.cpp
 * Author: cd8qvt
 * 
 * Created on May 25, 2017, 4:15 PM
 */

#include "BoundaryConditionsManager.h"
#include "Face.h"

BoundaryConditionsManager::BoundaryConditionsManager(VolumeMesh* mesh):mesh(mesh) {
    allBoundaryConditions = new std::vector<BoundaryCondition*>();
}

BoundaryConditionsManager::BoundaryConditionsManager(const BoundaryConditionsManager& orig) {
}

BoundaryConditionsManager::~BoundaryConditionsManager() {
    for(int i=0; i< allBoundaryConditions->size(); i++){
        BoundaryCondition* bc = (*allBoundaryConditions)[i];
        delete bc;
    }
    delete allBoundaryConditions;
}

std::vector<BoundaryCondition*>* BoundaryConditionsManager::getBoundaryConditions() {
    return allBoundaryConditions;
}

void BoundaryConditionsManager::createBoundaryCondition(BoundaryCondition::BcType type, std::vector<Face*> faces, double value) {
    BoundaryCondition* bc = new BoundaryCondition(type, faces, value);
    allBoundaryConditions->push_back(bc);
}

void BoundaryConditionsManager::createBoundaryCondition(std::string plane, double faceCoordinate, double faceTolerance, double bcValue) {
    std::vector<Face*> matchingFaces = mesh->findFaces(plane,faceCoordinate,faceTolerance);
    createBoundaryCondition(BoundaryCondition::BcType::FIXED_VALUE, matchingFaces, bcValue);
}

void BoundaryConditionsManager::printBoundaryConditionsReport() {
    std::vector<BoundaryCondition*>::iterator it = allBoundaryConditions->begin();
    while(it!= allBoundaryConditions->end()){
        BoundaryCondition* bc = *it;
        std::cout<<"---------"<<std::endl;
        std::cout<<bc->toString()<<std::endl;
        it++;
    }
}




