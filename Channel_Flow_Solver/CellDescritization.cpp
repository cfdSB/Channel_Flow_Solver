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

CellDescritization::CellDescritization(FvCell* cell):cell(cell) {
}

CellDescritization::CellDescritization(const CellDescritization& orig) {
}

CellDescritization::~CellDescritization() {
}

std::map<FvCell*, double> CellDescritization::getCoefficients() {
    return coefficients;
}

void CellDescritization::addCoefficient(FvCell* cell, double value) {
    coefficients.insert(std::make_pair(cell, value));
}

void CellDescritization::addSpComponent(Face* face, double value) {
    spComponents.insert(std::make_pair(face, value));
}

std::map<Face*, double> CellDescritization::getSpComponents() {
    return spComponents;
}

void CellDescritization::addSuComponent(Face* face, double value) {
    suComponents.insert(std::make_pair(face, value));
}

std::map<Face*, double> CellDescritization::getSuComponents() {
    return suComponents;
}








