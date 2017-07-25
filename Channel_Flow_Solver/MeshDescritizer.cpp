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

MeshDescritizer::MeshDescritizer(VolumeMesh* mesh, const PhysicsContinuum* pc):mesh(mesh), matrix(NULL),
 physicsContinuum(pc){
    allDescritizations = new std::map<const FvCell*,CellDescritization*>();
}

MeshDescritizer::MeshDescritizer(const MeshDescritizer& orig) {
}


MeshDescritizer::~MeshDescritizer() {
    std::map<const FvCell*, CellDescritization*>::iterator it = allDescritizations->begin();
    while(it!=allDescritizations->end()){
        std::pair<const FvCell*, CellDescritization*> p = *it;
        CellDescritization* cd = p.second;
        delete cd;
        it++;
    }
    delete allDescritizations;
    
    if(matrix!=NULL){
        delete matrix;
    }
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

    populateDiffusionCoefficients(cell);
}

void MeshDescritizer::populateDiffusionCoefficients(FvCell* cell) {

    CellDescritization* cd = allDescritizations->at(cell);
    //grab all faces and compute coefficients
    Face** faces = cell->getFaces();
    for (int i = 0; i < 6; i++) {
        
        Face* face = faces[i];
        const FvCell* connectingCell = face->getConnectingCell(cell);

        if (connectingCell == NULL) {
            //boundary cell
            const Point* faceCentroid = face->getCentroid();
            const Point* cellCentroid = cell->getCentroid();
            double distance = MeshUtilities::findDistance(*faceCentroid, *cellCentroid);
            double faceArea = face->getArea();
            double diffusionCoefficient = physicsContinuum->getDiffusionCoefficient();
            double coeff = faceArea / distance*diffusionCoefficient;
            cd->addDiffusionSuComponent(face, coeff);
            cd->addDiffusionSpComponent(face, -1.0 * coeff);
        } else {
            //regular cell
            const Point* connectingCellCentroid = connectingCell->getCentroid();
            const Point* cellCentroid = cell->getCentroid();
            double distance = MeshUtilities::findDistance(*connectingCellCentroid, *cellCentroid);
            double faceArea = face->getArea();
            double diffusionCoefficient = physicsContinuum->getDiffusionCoefficient();
            //coefficients which conform to Ap*Phi_p + Ae*Phi_e + Aw*Phi_w = Su + volumetric source term
            double coeff = faceArea / distance*diffusionCoefficient*-1.0;
            cd->addDiffusionCoefficient(connectingCell, coeff);
        }
    }
}


void MeshDescritizer::printCoefficients() {
    std::map<const FvCell*, CellDescritization*>::iterator it = allDescritizations->begin();
    while(it!=allDescritizations->end()){
        std::cout<<"---------"<<std::endl;
        CellDescritization* cd = (*it).second;
        std::string output = cd->toString();
        std::cout<<output<<std::endl;
        it++;
        
    }
}

std::map<const FvCell*, CellDescritization*>* MeshDescritizer::getDescritizations() {
    return allDescritizations;
}

void MeshDescritizer::updateCoefficients(std::vector<BoundaryCondition*> *conditions) {
    
    for(int i=0; i< conditions->size(); i++){
        BoundaryCondition* bc = (*conditions)[i];
        std::vector<Face*> *faces = bc->getFaces();
        for(int j=0; j<faces->size(); j++){
            Face* face = (*faces)[j];
            //find connected cell
            const FvCell* cell = face->getCell1();
            if(cell == NULL){
                cell = face->getCell2();
            }
            
            //adjust su or sp component of the particular face
            CellDescritization* des = allDescritizations->find(cell)->second;
            if(bc->getType() == BoundaryCondition::FIXED_VALUE){       
                des->scaleDiffusionSuComponent(face, bc->getValue());
            }else if(bc->getType() == BoundaryCondition::ADIABATIC){
                des->scaleDiffusionSuComponent(face, 0.0);
                des->scaleDiffusionSpComponent(face, 0.0);
            }else if(bc->getType() == BoundaryCondition::FIXED_FLUX){
                des->scaleDiffusionSuComponent(face, 0.0);
                double appendValue = bc->getValue()*face->getArea();
                des->appendDiffusionSuComponent(face, appendValue);
                des->scaleDiffusionSpComponent(face, 0.0);
            }
        }
    }
}


//void MeshDescritizer::updateCoefficients(PhysicsContinuum* pc){
//    std::map<const FvCell*, CellDescritization*>::iterator it;
//    for(it=allDescritizations->begin(); it!= allDescritizations->end(); it++){
//        CellDescritization* cds = it->second;
//        cds->scaleAllComponentsAndCoefficients(pc->getThermalConductivity());
//    }
//}

Matrix* MeshDescritizer::buildMatrix() {
    
    long numberOfVariables = allDescritizations->size();
    if(matrix== NULL){
        matrix = new Matrix(numberOfVariables);
    }
    
    //initialize all coefficients to zero
    for(long i=0; i<numberOfVariables; i++){
        for(long j=0; j<numberOfVariables; j++){
            matrix->setCoefficient(i, j, 0.0);
        }
    }    
    
    for(long i=0; i<numberOfVariables; i++){
        matrix->setRhs(i, 0.0);
    }
    
    //set solution variables (cells)
    typedef std::map<const FvCell*, CellDescritization*>::iterator cellP_desc_map;
    long i = 0;
    for(cellP_desc_map it = allDescritizations->begin(); it!= allDescritizations->end(); it++){
        CellDescritization* cd = it->second;
        matrix->setVariable(i, cd->getCell());
        i++;
    }
    
    //populate matrix coefficients
    i = 0;
    for (cellP_desc_map it = allDescritizations->begin(); it != allDescritizations->end(); it++) {
        
        CellDescritization* cd = it->second;
        std::map<const FvCell*, double>* coeffs = cd->getDiffusionCoefficients();

        //loop through each neighbor cell and update matrix
        typedef std::map<const FvCell*, double>::iterator cellP_double_map;
        double cellCoefficient = 0; //the coefficient of the cell itself
        for (cellP_double_map it = coeffs->begin(); it != coeffs->end(); it++) {
            const FvCell* neighborCell = it->first;
            double value = it->second;
            
            long rowNumber = i;
            long columnNumber = matrix->getVariableIndex(neighborCell);
            
            cellCoefficient = cellCoefficient + value;  //calcuation of ap
            
            //value = value* -1.0;    // matrix rearrangement needs this negation.
            matrix->setCoefficient(rowNumber, columnNumber, value);
        }
        
        //update the coefficient of the cell itself
        std::map<Face*, double>* spComps = cd->getDiffusionSpComponents();
        typedef std::map<Face*, double>::iterator faceP_double_map;
        double spCoefficient = 0; //the coefficient of the cell itself
        for (faceP_double_map it = spComps->begin(); it != spComps->end(); it++) {
            double value = it->second;
            spCoefficient = spCoefficient + value;
        }
        //Ap definition Ap = -(Ae + Aw) - Sp
        cellCoefficient = -1.0*cellCoefficient - spCoefficient; //sum of all neighbor cell coeffs - sp coefficients
        long rowNumber = i;
        long columnNumber = i;
        matrix->setCoefficient(rowNumber, columnNumber, cellCoefficient);

        i++;
    }
    
    //populate RHS coefficients
    i = 0;
    for (cellP_desc_map it = allDescritizations->begin(); it != allDescritizations->end(); it++) {
        
        CellDescritization* cd = it->second;
        
        std::map<Face*, double>* suComps = cd->getDiffusionSuComponents();
        typedef std::map<Face*, double>::iterator faceP_double_map;
        double suCoefficient = 0; //the coefficient of the cell itself
        for (faceP_double_map it = suComps->begin(); it != suComps->end(); it++) {
            double value = it->second;
            suCoefficient = suCoefficient + value;
        }
        matrix->setRhs(i, suCoefficient);
        
        i++;
    }
    
    return matrix;
}


