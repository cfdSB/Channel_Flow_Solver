/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BoundaryManager.h
 * Author: cd8qvt
 *
 * Created on August 5, 2017, 11:12 PM
 */

#ifndef BOUNDARYMANAGER_H
#define BOUNDARYMANAGER_H

#include "Boundary.h"
#include "VolumeMesh.h"
#include <vector>

class BoundaryManager {
public:
    BoundaryManager(VolumeMesh *mesh);
    BoundaryManager(const BoundaryManager& orig);
    virtual ~BoundaryManager();
    Boundary* createBoundary(std::string name, std::string plane, double faceCoordinate);
private:
    VolumeMesh *mesh;
    double faceMatchingTolerance = 1.0e-6;
};

#endif /* BOUNDARYMANAGER_H */

