/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SolutionManager.h
 * Author: cd8qvt
 *
 * Created on July 25, 2017, 9:57 PM
 */

#ifndef SOLUTIONMANAGER_H
#define SOLUTIONMANAGER_H

#include <vector>
#include <map>
#include <sstream>
#include "VolumeMesh.h"
#include "SolutionVariable.h"

class SolutionManager {
public:
    SolutionManager(VolumeMesh *mesh);
    SolutionManager(const SolutionManager& orig);
    virtual ~SolutionManager();
    SolutionVariable* createSolutionVariable(std::string variableName, SolutionVariable::variableType varType);
private:
    std::vector<SolutionVariable*> *solutionVariables;
    VolumeMesh *volumeMesh;
};

#endif /* SOLUTIONMANAGER_H */

