/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MeshDescritizer.cpp
 * Author: cd8qvt
 * 
 * Created on May 24, 2017, 9:56 AM
 */

#include "MeshDescritizer.h"
#include "MeshUtilities.h"
#include "VolumeMesh.h"
#include "BoundaryCondition.h"

MeshDescritizer::MeshDescritizer(VolumeMesh* mesh):mesh(mesh) {
    allDescritizations = new std::map<FvCell*,CellDescritization*>();
}

MeshDescritizer::MeshDescritizer(const MeshDescritizer& orig) {
}

MeshDescritizer::~MeshDescritizer() {
    std::map<FvCell*, CellDescritization*>::iterator it = allDescritizations->begin();
    while(it!=allDescritizations->end()){
        std::pair<FvCell*, CellDescritization*> p = *it;
        CellDescritization* cd = p.second;
        delete cd;
        it++;
    }
    delete allDescritizations;
}

void MeshDescritizer::computeDiscretizationCoefficients() {
    std::vector<FvCell*>* allCells = mesh->getCells();
    for(size_t i=0; i< allCells->size(); i++){
        FvCell* cell = (*allCells)[i];
        generateDescritizationCoefficients(cell);
    }
}


void MeshDescritizer::generateDescritizationCoefficients(FvCell* cell) {
    //create a discretization object
    CellDescritization* cd = new CellDescritization(cell);
    allDescritizations->insert(std::make_pair(cell, cd));
    
    //grab all faces and compute coefficients
    Face** faces = cell->getFaces();
    for(int i=0; i<6; i++){
        Face* face = faces[i];
        FvCell* connectingCell = face->getConnectingCell(cell);
        
        if(connectingCell == NULL){
            //boundary cell
            Point* faceCentroid = face->getCentroid();
            Point* cellCentroid = cell->getCentroid();
            double distance = MeshUtilities::findDistance(*faceCentroid, *cellCentroid);
            double faceArea = face->getArea();
            double coeff = faceArea/distance;
            cd->addSuComponent(face, coeff);
            cd->addSpComponent(face, -1.0*coeff);
        }else{
            //regular cell
            Point* connectingCellCentroid = connectingCell->getCentroid();
            Point* cellCentroid = cell->getCentroid();
            double distance = MeshUtilities::findDistance(*connectingCellCentroid, *cellCentroid);
            double faceArea = face->getArea();
            double coeff = faceArea/distance;
            cd->addCoefficient(connectingCell, coeff);
        }
    }
    //add coefficient for the cell itself
    double sumSpCoeff = 0;
    
}

void MeshDescritizer::printCoefficients() {
    std::map<FvCell*, CellDescritization*>::iterator it = allDescritizations->begin();
    while(it!=allDescritizations->end()){
        std::cout<<"---------"<<std::endl;
        CellDescritization* cd = (*it).second;
        std::string output = cd->toString();
        std::cout<<output<<std::endl;
        it++;
        
    }
}

std::map<FvCell*, CellDescritization*>* MeshDescritizer::getDescritizations() {
    return allDescritizations;
}

void MeshDescritizer::updateCoefficients(std::vector<BoundaryCondition*> *conditions) {
    
    for(int i=0; i< conditions->size(); i++){
        BoundaryCondition* bc = (*conditions)[i];
        std::vector<Face*> *faces = bc->getFaces();
        for(int j=0; j<faces->size(); j++){
            Face* face = (*faces)[j];
            //find connected cell
            FvCell* cell = face->getCell1();
            if(cell == NULL){
                cell = face->getCell2();
            }
            
            //adjust su or sp component of the particular face
            CellDescritization* des = allDescritizations->find(cell)->second;
            if(bc->getType() == BoundaryCondition::FIXED_VALUE){
                adjustSuComponent(face, des, bc->getValue());                
            }else if(bc->getType() == BoundaryCondition::ADIABATIC){
                adjustSuComponent(face, des, 0.0);
                adjustSpComponent(face, des, 0.0);
            }
        }
    }
}

void MeshDescritizer::adjustSuComponent(Face* face, CellDescritization* des, double value) {
    std::map<Face*, double> *suCoeffs = des->getSuComponents();
    std::map<Face*, double>::iterator it = suCoeffs->find(face);
    if (it != suCoeffs->end()) {
        double d = it->second;
        double adjustedValue = d * value;
        it->second = adjustedValue;
    }
}

void MeshDescritizer::adjustSpComponent(Face* face, CellDescritization* des, double value) {
    std::map<Face*, double> *spCoeffs = des->getSpComponents();
    std::map<Face*, double>::iterator it = spCoeffs->find(face);
    if (it != spCoeffs->end()) {
        double d = it->second;
        double adjustedValue = d * value;
        it->second = adjustedValue;
    }
}

