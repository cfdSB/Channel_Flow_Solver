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
    for(size_t i=0; i< allBoundaryConditions->size(); i++){
        BoundaryCondition* bc = allBoundaryConditions->at(i);
        delete bc;
    }
    delete allBoundaryConditions;
}

std::vector<BoundaryCondition*>* BoundaryConditionsManager::getBoundaryConditions() {
    return allBoundaryConditions;
}

BoundaryCondition* BoundaryConditionsManager::createBoundaryCondition(SolutionVariable* variable, BoundaryCondition::BcType type, double value) {
    BoundaryCondition* bc = new BoundaryCondition(variable, type, value);
    allBoundaryConditions->push_back(bc);
    return bc;
}

//void BoundaryConditionsManager::createBoundaryCondition(std::string plane, double faceCoordinate, double faceTolerance, BoundaryCondition::BcType type, double bcValue) {
//    
//    createBoundaryCondition(type, bcValue);
//}

void BoundaryConditionsManager::printBoundaryConditionsReport() {
    std::vector<BoundaryCondition*>::iterator it = allBoundaryConditions->begin();
    while(it!= allBoundaryConditions->end()){
        BoundaryCondition* bc = *it;
        std::cout<<"---------"<<std::endl;
        std::cout<<bc->toString()<<std::endl;
        it++;
    }
}




