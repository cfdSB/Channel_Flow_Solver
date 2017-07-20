/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MeshDescritizer.h
 * Author: cd8qvt
 *
 * Created on May 24, 2017, 9:56 AM
 */

#ifndef MESHDESCRITIZER_H
#define MESHDESCRITIZER_H

#include "CellDescritization.h"
#include <vector>
#include <map>
#include "FvCell.h"
#include "Face.h"
#include "BoundaryCondition.h"
#include "PhysicsContinuum.h"
#include "Matrix.h"

class VolumeMesh;   //forward declaration

class MeshDescritizer {
    
public:
    
    enum SimulationType {DIFFUSION, CONVECTION_DIFFUSION}; 
    enum ConvectionDifferencingScheme {CENTRAL, FIRST_ORDER_UPWIND};  
    
    MeshDescritizer(VolumeMesh* mesh, const PhysicsContinuum* pc);
    MeshDescritizer(const MeshDescritizer& orig);
    virtual ~MeshDescritizer();
    void computeDiscretizationCoefficients();
    void printCoefficients();
    std::map<const FvCell*, CellDescritization*>* getDescritizations();
    void updateCoefficients(std::vector<BoundaryCondition*> *conditions);
    //void updateCoefficients(PhysicsContinuum* pc);
    Matrix* buildMatrix();
    SimulationType getsimulationType() const;
    void setsimulationType(SimulationType type);
    ConvectionDifferencingScheme getConvectionDifferencingScheme() const;
    void setConvectionDifferencingScheme(ConvectionDifferencingScheme differencingScheme);    
    
    
private:
    VolumeMesh* mesh;
    const PhysicsContinuum* physicsContinuum;
    std::map<const FvCell*, CellDescritization*>* allDescritizations;    
    Matrix* matrix;
    
    SimulationType simulationType;
    ConvectionDifferencingScheme differencingScheme;
    bool diffusionEnabled, convectionEnabled;
    
    void generateDescritizationCoefficients(FvCell* cell);
    void populateDiffusionCoefficients(FvCell* cell);
    
};

#endif /* MESHDESCRITIZER_H */

