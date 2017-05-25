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

MeshDescritizer::MeshDescritizer() {
    allDescritizations = new std::vector<CellDescritization*>();
}

MeshDescritizer::MeshDescritizer(const MeshDescritizer& orig) {
}

MeshDescritizer::~MeshDescritizer() {
    size_t size = allDescritizations->size();
    for(size_t i=0; i<size; i++){
        CellDescritization* des = (*allDescritizations)[i];
        delete des;
    }
    delete allDescritizations;
}

void MeshDescritizer::computeDiscretizationCoefficients(VolumeMesh* mesh) {
    std::vector<FvCell*>* allCells = mesh->getCells();
    for(size_t i=0; i< allCells->size(); i++){
        FvCell* cell = (*allCells)[i];
        generateDescritizationCoefficients(cell);
    }
}


void MeshDescritizer::generateDescritizationCoefficients(FvCell* cell) {
    //create a discretization object
    CellDescritization* cd = new CellDescritization(cell);
    allDescritizations->push_back(cd);
    
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
    std::vector<CellDescritization*>::iterator it = allDescritizations->begin();
    while(it!=allDescritizations->end()){
        std::cout<<"---------"<<std::endl;
        std::string output = (*it)->toString();
        std::cout<<output<<std::endl;
        it++;
        
    }
}





