/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CellDescritization.h
 * Author: cd8qvt
 *
 * Created on May 24, 2017, 10:46 AM
 */

#ifndef CELLDESCRITIZATION_H
#define CELLDESCRITIZATION_H

#include "Object.h"
#include <map>
#include <sstream>
class FvCell;    //forward declaration
class Face;

class CellDescritization : public Object {
public:
    CellDescritization(FvCell* cell);
    CellDescritization(const CellDescritization& orig);
    virtual ~CellDescritization();
    
    void addCoefficient(FvCell* cell, double value);
    std::map<FvCell*, double>* getCoefficients();
    std::map<Face*, double>* getSuComponents();
    void addSuComponent(Face* face, double value);
    void addSpComponent(Face* face, double value);
    void scaleSuComponent(Face* face, double scaleFactor);
    void scaleSpComponent(Face* face, double scaleFactor);
    void scaleAllComponentsAndCoefficients(double scaleFactor);
    std::map<Face*, double>* getSpComponents();
    FvCell* getCell();
    std::string toString() override;

    
private:
    FvCell* cell;
    std::map<FvCell*, double> *coefficients;
    std::map<Face*, double> *suComponents; //constant part of source term linearization    
    std::map<Face*, double> *spComponents;  //variable dependent part of source term linearization and/or artifact
                                           //of the the cell being a boundary cell
};

#endif /* CELLDESCRITIZATION_H */

