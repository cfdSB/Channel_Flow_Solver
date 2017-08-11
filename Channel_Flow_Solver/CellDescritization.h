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
    
    void addDiffusionCoefficient(const FvCell* cell, double value);
    std::map<const FvCell*, double>* getDiffusionCoefficients();
    std::map<Face*, double>* getDiffusionSuComponents();
    void addDiffusionSuComponent(Face* face, double value);
    void addDiffusionSpComponent(Face* face, double value);
    void scaleDiffusionSuComponent(Face* face, double scaleFactor);
    void scaleDiffusionSpComponent(Face* face, double scaleFactor);
    void appendDiffusionSuComponent(Face* face, double appendValue);
    void scaleAllDiffusionComponentsAndCoefficients(double scaleFactor);
    std::map<Face*, double>* getDiffusionSpComponents();
    
    void addConvectionCoefficient(const FvCell* cell, double coefficient);
    void addConvectionSuComponent(Face* face, double value);
    void addConvectionSpComponent(Face* face, double value);
    void addConvectionMassBalanceComponent(const FvCell* cell, double component);
    void scaleConvectionSuComponent(Face* face, double scaleFactor);
    std::map<const FvCell*, double>* getConvectionCoefficients();
    std::map<Face*, double>* getConvectionSuComponents();
    std::map<Face*, double>* getConvectionSpComponents();
    std::map<const FvCell*, double>* getConvectionMassBalanceComponents();
    
    
    FvCell* getCell();
    std::string toString() override;

    
private:
    FvCell* cell;
    std::map<const FvCell*, double> *diffusionCoefficients;
    std::map<Face*, double> *diffusionSuComponents; //constant part of source term linearization    
    std::map<Face*, double> *diffusionSpComponents;  //variable dependent part of source term linearization and/or artifact
                                           //of the the cell being a boundary cell
    
    std::map<const FvCell*, double> *convectionCoefficients;
    std::map<Face*, double> *convectionSuComponents;
    std::map<Face*, double> *convectionSpComponents;
    std::map<const FvCell*, double> *massBalanceCoefficients;
};

#endif /* CELLDESCRITIZATION_H */

