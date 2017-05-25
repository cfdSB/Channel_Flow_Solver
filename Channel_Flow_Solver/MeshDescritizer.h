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
#include "FvCell.h"
#include "Face.h"

class VolumeMesh;   //forward declaration

class MeshDescritizer {
    
public:
    MeshDescritizer();
    MeshDescritizer(const MeshDescritizer& orig);
    virtual ~MeshDescritizer();
    void computeDiscretizationCoefficients(VolumeMesh* mesh);
    void printCoefficients();
private:
    std::vector<CellDescritization*>* allDescritizations;
    void generateDescritizationCoefficients(FvCell* cell);
};

#endif /* MESHDESCRITIZER_H */

