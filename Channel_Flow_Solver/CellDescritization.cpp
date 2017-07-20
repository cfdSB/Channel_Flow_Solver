/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CellDescritization.cpp
 * Author: cd8qvt
 * 
 * Created on May 24, 2017, 10:46 AM
 */

#include <map>
#include "CellDescritization.h"
#include "FvCell.h"

CellDescritization::CellDescritization(FvCell* cell):cell(cell) {
    diffusionCoefficients = new std::map<const FvCell*, double>();
    diffusionSuComponents = new std::map<Face*, double> ();
    diffusionSpComponents = new std::map<Face*, double> ();
}

CellDescritization::CellDescritization(const CellDescritization& orig) {
}

CellDescritization::~CellDescritization() {
    delete diffusionCoefficients;
    delete diffusionSuComponents;
    delete diffusionSpComponents;
}

std::map<const FvCell*, double>* CellDescritization::getDiffusionCoefficients() {
    return diffusionCoefficients;
}

void CellDescritization::addDiffusionCoefficient(const FvCell* cell, double value) {
    diffusionCoefficients->insert(std::make_pair(cell, value));
}

void CellDescritization::addDiffusionSpComponent(Face* face, double value) {
    diffusionSpComponents->insert(std::make_pair(face, value));
}

std::map<Face*, double>* CellDescritization::getDiffusionSpComponents() {
    return diffusionSpComponents;
}

void CellDescritization::addDiffusionSuComponent(Face* face, double value) {
    diffusionSuComponents->insert(std::make_pair(face, value));
}

std::map<Face*, double>* CellDescritization::getDiffusionSuComponents() {
    return diffusionSuComponents;
}

std::string CellDescritization::toString() {
    std::ostringstream output;
    output<<"coefficients: ";
    std::map<const FvCell*, double>::iterator it = diffusionCoefficients->begin();
    while(it!=diffusionCoefficients->end()){
        output<<","<<it->second;
        it++;
    }
    output<<std::endl;
    output<<"su components: ";
    std::map<Face*, double>::iterator it1 = diffusionSuComponents->begin();
    while(it1!=diffusionSuComponents->end()){
        output<<","<<it1->second;
        it1++;
    }
    output<<std::endl;
    output<<"sp components: ";
    std::map<Face*, double>::iterator it2 = diffusionSpComponents->begin();
    while(it2!=diffusionSpComponents->end()){
        output<<","<<it2->second;
        it2++;
    }
    
    return output.str();
}

void CellDescritization::scaleDiffusionSuComponent(Face* face, double scaleFactor) {
    std::map<Face*, double>::iterator it = diffusionSuComponents->find(face);
    if (it != diffusionSuComponents->end()) {
        double d = it->second;
        double adjustedValue = d * scaleFactor;
        it->second = adjustedValue;
    }
}

void CellDescritization::scaleDiffusionSpComponent(Face* face, double scaleFactor) {
    std::map<Face*, double>::iterator it = diffusionSpComponents->find(face);
    if (it != diffusionSpComponents->end()) {
        double d = it->second;
        double adjustedValue = d * scaleFactor;
        it->second = adjustedValue;
    }
}

void CellDescritization::scaleAllDiffusionComponentsAndCoefficients(double scaleFactor) {
    
    std::map<Face*, double>::iterator it;
    for(it=diffusionSuComponents->begin(); it!=diffusionSuComponents->end(); it++) {
        double d = it->second;
        double adjustedValue = d * scaleFactor;
        it->second = adjustedValue;
    }
    
    for(it= diffusionSpComponents->begin(); it!= diffusionSpComponents->end(); it++){
        double d = it->second;
        double adjustedValue = d * scaleFactor;
        it->second = adjustedValue;
    }
    
    std::map<const FvCell*, double>::iterator it2;
    
    for(it2=diffusionCoefficients->begin(); it2!=diffusionCoefficients->end(); it2++){
        double d = it2->second;
        double adjustedValue = d * scaleFactor;
        it2->second = adjustedValue;
    }
}

FvCell* CellDescritization::getCell() {
    return cell;
}

void CellDescritization::appendDiffusionSuComponent(Face* face, double appendValue) {
    std::map<Face*, double>::iterator it = diffusionSuComponents->find(face);
    if (it != diffusionSuComponents->end()) {
        double d = it->second;
        double adjustedValue = d + appendValue;
        it->second = adjustedValue;
        //std::cout<<"Flux su component: " << it->second<< std::endl;
    }
}



