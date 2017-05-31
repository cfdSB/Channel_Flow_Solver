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
    coefficients = new std::map<FvCell*, double>();
    suComponents = new std::map<Face*, double> ();
    spComponents = new std::map<Face*, double> ();
}

CellDescritization::CellDescritization(const CellDescritization& orig) {
}

CellDescritization::~CellDescritization() {
    delete coefficients;
    delete suComponents;
    delete spComponents;
}

std::map<FvCell*, double>* CellDescritization::getCoefficients() {
    return coefficients;
}

void CellDescritization::addCoefficient(FvCell* cell, double value) {
    coefficients->insert(std::make_pair(cell, value));
}

void CellDescritization::addSpComponent(Face* face, double value) {
    spComponents->insert(std::make_pair(face, value));
}

std::map<Face*, double>* CellDescritization::getSpComponents() {
    return spComponents;
}

void CellDescritization::addSuComponent(Face* face, double value) {
    suComponents->insert(std::make_pair(face, value));
}

std::map<Face*, double>* CellDescritization::getSuComponents() {
    return suComponents;
}

std::string CellDescritization::toString() {
    std::ostringstream output;
    output<<"coefficients: ";
    std::map<FvCell*, double>::iterator it = coefficients->begin();
    while(it!=coefficients->end()){
        output<<","<<it->second;
        it++;
    }
    output<<std::endl;
    output<<"su components: ";
    std::map<Face*, double>::iterator it1 = suComponents->begin();
    while(it1!=suComponents->end()){
        output<<","<<it1->second;
        it1++;
    }
    output<<std::endl;
    output<<"sp components: ";
    std::map<Face*, double>::iterator it2 = spComponents->begin();
    while(it2!=spComponents->end()){
        output<<","<<it2->second;
        it2++;
    }
    
    return output.str();
}








