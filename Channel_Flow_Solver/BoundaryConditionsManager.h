/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BoundaryConditionsManager.h
 * Author: cd8qvt
 *
 * Created on May 25, 2017, 4:15 PM
 */

#ifndef BOUNDARYCONDITIONSMANAGER_H
#define BOUNDARYCONDITIONSMANAGER_H
#include "BoundaryCondition.h"
#include "VolumeMesh.h"

class BoundaryConditionsManager {
public:
    BoundaryConditionsManager(VolumeMesh* mesh);
    BoundaryConditionsManager(const BoundaryConditionsManager& orig);
    virtual ~BoundaryConditionsManager();
    std::vector<BoundaryCondition*>* getBoundaryConditions();
    void createBoundaryCondition(BoundaryCondition::BcType type, std::vector<Face*> faces, double value);
    void createBoundaryCondition(std::string plane, double faceCoordinate, double faceTolerance, double bcValue);
private:
    std::vector<BoundaryCondition*>* allBoundaryConditions;
    VolumeMesh* mesh;
};

#endif /* BOUNDARYCONDITIONSMANAGER_H */

