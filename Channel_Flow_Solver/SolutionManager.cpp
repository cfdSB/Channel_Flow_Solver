/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SolutionManager.cpp
 * Author: cd8qvt
 * 
 * Created on July 25, 2017, 9:57 PM
 */

#include "SolutionManager.h"
#include "VolumeMesh.h"

SolutionManager::SolutionManager(VolumeMesh *mesh): volumeMesh(mesh) {
    solutionVariables = new std::map<std::string, std::vector<double>* >();
}

SolutionManager::SolutionManager(const SolutionManager& orig) {
}

SolutionManager::~SolutionManager() {
    std::map<std::string, std::vector<double>* >::iterator it = solutionVariables->begin();
    while(it!=solutionVariables->end()){
        std::pair<std::string, std::vector<double>* >  pair = *it;
        std::string variableName = pair.first;
        volumeMesh->removeSolutionFieldFromMesh(variableName);
        std::vector<double>* cd = pair.second;
        delete cd;
        it++;
    }
    delete solutionVariables;
}

void SolutionManager::createSolutionVariable(std::string variableName) {
    long cellCount = volumeMesh->getCellCount();
    std::vector<double>* solution = new std::vector<double>(cellCount);
    solutionVariables->insert(std::make_pair(variableName, solution));
    volumeMesh->addSolutionFieldToMesh(variableName, solution);
    
}
