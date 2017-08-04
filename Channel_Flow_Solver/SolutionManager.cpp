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
    solutionVariables = new std::vector<SolutionVariable*>();
}

SolutionManager::SolutionManager(const SolutionManager& orig) {
}

SolutionManager::~SolutionManager() {
    
    std::vector<SolutionVariable*>::iterator it = solutionVariables->begin();
    while(it!=solutionVariables->end()){
        SolutionVariable *solVar = *it;
        volumeMesh->removeSolutionFieldFromMesh(solVar->GetVariableName());
        delete solVar;
        it++;
    }
    delete solutionVariables;
}

SolutionVariable* SolutionManager::createSolutionVariable(std::string variableName, SolutionVariable::variableType varType) {
    long cellCount = volumeMesh->getCellCount();
    SolutionVariable *solVar = new SolutionVariable(variableName, cellCount, varType);
    solutionVariables->push_back(solVar);
    volumeMesh->addSolutionFieldToMesh(variableName, solVar->GetVariableValues());
    return solVar;
}
