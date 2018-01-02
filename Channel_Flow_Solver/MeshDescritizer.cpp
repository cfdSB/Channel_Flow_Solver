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
    populateConvectionCoefficients(cell);
}

void MeshDescritizer::populateConvectionCoefficients(FvCell* cell) {
    CellDescritization* cd = allDescritizations->at(cell);
    //grab all faces and compute coefficients
    Face** faces = cell->getFaces();
    
    Face* xmFace = faces[0];
    Face* xpFace = faces[1];
    Face* ymFace = faces[2];
    Face* ypFace = faces[3];
    Face* zmFace = faces[4];
    Face* zpFace = faces[5];
    
    double density = physicsContinuum->getMaterial()->getDensity();
    
    //x- direction convection flux
    const FvCell* xmCell = xmFace->getConnectingCell(cell);
    if(xmCell==NULL){
        double xmFaceVel = xmFace->getBoundary()->getBoundaryCondition("i_velocity")->getValue();
        double faceFlux = density*xmFace->getArea()*xmFaceVel;
        cd->addConvectionSuComponent(xmFace, faceFlux);
    }else{
        //interpolate face velocity from surrounding cells
        double neighborInterpolationCoeff = computeInterpolationCoefficient(xmFace, cell, xmCell);
        double xmFaceVel = findInterpolatedFaceVariable(neighborInterpolationCoeff, cell, xmCell, "i_velocity");
        double faceFlux = density*xmFace->getArea()*xmFaceVel;
        double xmConvFlux = -1.0*faceFlux*(1.0-neighborInterpolationCoeff);
        cd->addConvectionCoefficient(xmCell, xmConvFlux);
        cd->addConvectionMassBalanceComponent(xmCell,-1.0*faceFlux);
    }
    
    //x+ direction convection flux
    const FvCell* xpCell = xpFace->getConnectingCell(cell);
    if(xpCell == NULL){
        double xpFaceVel = xpFace->getBoundary()->getBoundaryCondition("i_velocity")->getValue();
        double faceFlux = -1.0*density*xpFace->getArea()*xpFaceVel;
        cd->addConvectionSuComponent(xpFace,faceFlux);
    }else {
        double neighborInterpolationCoeff = computeInterpolationCoefficient(xpFace, cell, xpCell);
        double xpFaceVel = findInterpolatedFaceVariable(neighborInterpolationCoeff, cell, xpCell, "i_velocity");
        double faceFlux = density * xpFace->getArea() * xpFaceVel; 
        double xpConvFlux = faceFlux*(1 - neighborInterpolationCoeff);;
        cd->addConvectionCoefficient(xpCell, xpConvFlux);
        cd->addConvectionMassBalanceComponent(xpCell, faceFlux);
    }
    
    //y- direction convective flux
    const FvCell* ymCell = ymFace->getConnectingCell(cell);
    
    if(ymCell == NULL){
        double ymFaceVel = ymFace->getBoundary()->getBoundaryCondition("j_velocity")->getValue();
        double faceFlux = density*ymFace->getArea()*ymFaceVel;
        cd->addConvectionSuComponent(ymFace, faceFlux);
    }else{
        double neighborInterpolationCoeff = computeInterpolationCoefficient(ymFace, cell, ymCell);
        double ymFaceVel = findInterpolatedFaceVariable(neighborInterpolationCoeff, cell, ymCell, "j_velocity");
        double faceFlux = density*ymFace->getArea()*ymFaceVel;
        double ymConvFlux = -1.0*faceFlux*(1-neighborInterpolationCoeff);
        cd->addConvectionCoefficient(ymCell, ymConvFlux);
        cd->addConvectionMassBalanceComponent(ymCell,-1.0*faceFlux);
    }
    
    //y+ direction convective flux
    const FvCell* ypCell = ypFace->getConnectingCell(cell);
    if(ypCell == NULL){
         double ypFaceVel = ypFace->getBoundary()->getBoundaryCondition("j_velocity")->getValue();
         double faceFlux = -1.0*density*ypFace->getArea()*ypFaceVel;
         cd->addConvectionSuComponent(ypFace, faceFlux);
    } else {
        double neighborInterpolationCoeff = computeInterpolationCoefficient(ypFace, cell, ypCell);
        double ypFaceVel = findInterpolatedFaceVariable(neighborInterpolationCoeff, cell, ypCell, "j_velocity");
        double faceFlux = density * ypFace->getArea()*ypFaceVel;
        double ypConvFlux = faceFlux*(1-neighborInterpolationCoeff);
        cd->addConvectionCoefficient(ypCell, ypConvFlux);
        cd->addConvectionMassBalanceComponent(ypCell, faceFlux);
    }

    //z- direction convective flux
    const FvCell* zmCell = zmFace->getConnectingCell(cell);
    if (zmCell == NULL) {
        double zmFaceVel = zmFace->getBoundary()->getBoundaryCondition("k_velocity")->getValue();
        double faceFlux = density * zmFace->getArea()*zmFaceVel;
        cd->addConvectionSuComponent(zmFace, faceFlux);
    } else {
        double neighborInterpolationCoeff = computeInterpolationCoefficient(zmFace, cell, zmCell);
        double zmFaceVel = findInterpolatedFaceVariable(neighborInterpolationCoeff, cell, zmCell, "k_velocity");
        double faceFlux =  density*zmFace->getArea()*zmFaceVel;
        double zmConvFlux = -1.0*faceFlux*(1-neighborInterpolationCoeff);
        cd->addConvectionCoefficient(zmCell, zmConvFlux);
        cd->addConvectionMassBalanceComponent(zmCell,-1.0*faceFlux);
    }
    
    //z+ direction convective flux
    const FvCell* zpCell = zpFace->getConnectingCell(cell);
    if(zpCell == NULL){
        double zpFaceVel = zpFace->getBoundary()->getBoundaryCondition("k_velocity")->getValue();
        double faceFlux = -1.0*density*zpFace->getArea()*zpFaceVel;
        cd->addConvectionSuComponent(zpFace, faceFlux);
    }else{
        double neighborInterpolationCoeff = computeInterpolationCoefficient(zpFace, cell, zpCell);
        double zpFaceVel = findInterpolatedFaceVariable(neighborInterpolationCoeff, cell, zpCell, "k_velocity");
        double faceFlux = zpFaceVel * density * zpFace->getArea();
        double zpConvFlux = faceFlux*(1-neighborInterpolationCoeff);
        cd->addConvectionCoefficient(zpCell, zpConvFlux);
        cd->addConvectionMassBalanceComponent(zpCell, faceFlux);        
    }
        
}

double MeshDescritizer::computeInterpolationCoefficient(Face *face, FvCell *cell, const FvCell *neighborCell){
    double dist1 = MeshUtilities::findDistance(*(face->getCentroid()), *(cell->getCentroid()));
    double dist2 = MeshUtilities::findDistance(*(face->getCentroid()), *(neighborCell->getCentroid()));
    
    double interpolationCoeff = dist2/(dist1+dist2);
    
    //double interpolationCoeff = 1-coeff;
    
    return interpolationCoeff;
}
double MeshDescritizer::findInterpolatedFaceVariable(double interpolationCoeff, FvCell* cell, const FvCell* neighborCell, std::string variable) {
    //interpolate face velocity from surrounding cells
    double var1 = *(cell->getSolutionField(variable));
    double var2 = *(neighborCell->getSolutionField(variable));
    double interpolatedVar = var1* interpolationCoeff + var2*(1-interpolationCoeff);
    
    return interpolatedVar;
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
            double diffusionCoefficient = physicsContinuum->getMaterial()->getDiffusionCoefficient();
            double coeff = faceArea / distance*diffusionCoefficient;
            cd->addDiffusionSuComponent(face, coeff);
            cd->addDiffusionSpComponent(face, coeff);
        } else {
            //regular cell
            const Point* connectingCellCentroid = connectingCell->getCentroid();
            const Point* cellCentroid = cell->getCentroid();
            double distance = MeshUtilities::findDistance(*connectingCellCentroid, *cellCentroid);
            double faceArea = face->getArea();
            double diffusionCoefficient = physicsContinuum->getMaterial()->getDiffusionCoefficient();
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

//void MeshDescritizer::updateCoefficients(std::vector<BoundaryCondition*> *conditions) {
//    
//    for(int i=0; i< conditions->size(); i++){
//        BoundaryCondition* bc = (*conditions)[i];
//        std::vector<Face*> *faces = bc->getFaces();
//        for(int j=0; j<faces->size(); j++){
//            Face* face = (*faces)[j];
//            //find connected cell
//            const FvCell* cell = face->getCell1();
//            if(cell == NULL){
//                cell = face->getCell2();
//            }
//            
//            //adjust su or sp component of the particular face
//            CellDescritization* des = allDescritizations->find(cell)->second;
//            if(bc->getType() == BoundaryCondition::FIXED_VALUE){       
//                des->scaleDiffusionSuComponent(face, bc->getValue());
//            }else if(bc->getType() == BoundaryCondition::ADIABATIC){
//                des->scaleDiffusionSuComponent(face, 0.0);
//                des->scaleDiffusionSpComponent(face, 0.0);
//            }else if(bc->getType() == BoundaryCondition::FIXED_FLUX){
//                des->scaleDiffusionSuComponent(face, 0.0);
//                double appendValue = bc->getValue()*face->getArea();
//                des->appendDiffusionSuComponent(face, appendValue);
//                des->scaleDiffusionSpComponent(face, 0.0);
//            }
//        }
//    }
//}

void MeshDescritizer::updateCoefficientsWithBCs(std::vector<Boundary*> *boundaries){
    for(size_t i=0; i<boundaries->size(); i++){
        Boundary* bnd = boundaries->at(i);
        std::vector<Face*> *faces = bnd->getFaces();
        for(size_t j=0; j<faces->size(); j++){
            Face* face = faces->at(j);
            updateConvectionCoefficientsWithBCs(face);
            updateDiffusionCoefficientsWithBCs(face);
        }
    }
    
}

void MeshDescritizer::updateDiffusionCoefficientsWithBCs(Face* face) {
    //find connected cell
    const FvCell* cell = face->getCell1();
    if (cell == NULL) {
        cell = face->getCell2();
    }
    
    BoundaryCondition *bc = face->getBoundary()->getBoundaryCondition("Temperature");

    //adjust su or sp component of the particular face
    CellDescritization* des = allDescritizations->find(cell)->second;
    if (bc->getType() == BoundaryCondition::FIXED_VALUE) {
        des->scaleDiffusionSuComponent(face, bc->getValue());
    } else if (bc->getType() == BoundaryCondition::ADIABATIC) {
        des->scaleDiffusionSuComponent(face, 0.0);
        des->scaleDiffusionSpComponent(face, 0.0);
    } else if (bc->getType() == BoundaryCondition::FIXED_FLUX) {
        des->scaleDiffusionSuComponent(face, 0.0);
        double appendValue = bc->getValue() * face->getArea();
        des->appendDiffusionSuComponent(face, appendValue);
        des->scaleDiffusionSpComponent(face, 0.0);
    }
}

void MeshDescritizer::updateConvectionCoefficientsWithBCs(Face* face) {
    //find connected cell
    const FvCell* cell = face->getCell1();
    if (cell == NULL) {
        cell = face->getCell2();
    }

    BoundaryCondition *bc = face->getBoundary()->getBoundaryCondition("Temperature");

    //adjust su or sp component of the particular face
    CellDescritization* des = allDescritizations->find(cell)->second;
    if (bc->getType() == BoundaryCondition::FIXED_VALUE) {
        des->scaleConvectionSuComponent(face, bc->getValue());
    }else if(bc->getType() == BoundaryCondition::ADIABATIC){
        double variableValue = *(cell->getSolutionField("Temperature"));
        des->scaleConvectionSuComponent(face, variableValue);
    
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

    if (matrix == NULL) {
        long numberOfVariables = allDescritizations->size();
        matrix = new Matrix(numberOfVariables);

        //initialize all coefficients to zero
        for (long i = 0; i < numberOfVariables; i++) {
            for (long j = 0; j < numberOfVariables; j++) {
                matrix->setCoefficient(i, j, 0.0);
            }
        }

        for (long i = 0; i < numberOfVariables; i++) {
            matrix->setRhs(i, 0.0);
        }

        //set solution variables (cells)
        long i = 0;
        std::vector<FvCell*> *allCells = mesh->getCells();
        for (i = 0; i < allCells->size(); i++) {
            matrix->setVariable(i, allCells->at(i));
        }
    }
    
    //populate matrix coefficients
    std::vector<FvCell*> *allCells = mesh->getCells();
    long i = 0;
    for (i=0; i<allCells->size(); i++) {
        
        FvCell *cell = allCells->at(i);
        CellDescritization* cd = allDescritizations->at(cell);
        
        long rowNumber = i;
        long columnNumber = 0;
        
        std::vector<const FvCell*> neighborCells = mesh->findNeighboringCells(cell);
        for(int j=0; j< neighborCells.size(); j++){
            const FvCell *neighborCell = neighborCells.at(j);
            rowNumber = i;
            columnNumber = matrix->getVariableIndex(neighborCell);
            double value = computeCoefficientForNeighborCell(cd, neighborCell);
             matrix->setCoefficient(rowNumber, columnNumber, value);
        }
        
        //compute the coefficient of the cell itself
        double cellCoefficient = computeCellCoefficientFromNeighborCellsCoefficients(neighborCells, cd);
        rowNumber = i;
        columnNumber = i;
        matrix->setCoefficient(rowNumber, columnNumber, cellCoefficient);
        
        //compute RHS coefficients
        double suCoefficient = computeCellSuCoefficient(cd);
        rowNumber = i;
        matrix->setRhs(i, suCoefficient);
    }
      
    return matrix;
}

double MeshDescritizer::computeCoefficientForNeighborCell(CellDescritization *cd, const FvCell* neighborCell){
    double value = 0.0;
    value = value + cd->getDiffusionCoefficients()->at(neighborCell);
    //value = value + cd->getConvectionCoefficients()->at(neighborCell);
    return value;
}

double MeshDescritizer::computeCellCoefficientFromNeighborCellsCoefficients(std::vector<const FvCell*> neighborCells, CellDescritization *cd) {
    double cellCoefficient = 0; //the coefficient of the cell itself
    for(int i =0; i< neighborCells.size(); i++){
        const FvCell *neighborCell = neighborCells.at(i);
        cellCoefficient = cellCoefficient + computeCoefficientForNeighborCell(cd, neighborCell);
    }
   
    double spCoefficient = computeCellSpCoefficient(cd);
    double massBalanceCoefficient = computeMassBalanceCoefficient(cd);
    //Ap definition Ap = -(Ae + Aw) - Sp + (M_e - M_w)
    cellCoefficient = -1.0 * cellCoefficient + spCoefficient + massBalanceCoefficient;     

    return cellCoefficient;
}

double MeshDescritizer::computeCellSpCoefficient(CellDescritization *cd) {
    double spCoefficient = 0; 
    //currently no Sp coefficient from convection side
    std::map<Face*, double>* spComps = cd->getDiffusionSpComponents();
    typedef std::map<Face*, double>::iterator faceP_double_map;
    for (faceP_double_map it = spComps->begin(); it != spComps->end(); it++) {
        Face* face = it->first;
        double value = it->second;
        BoundaryCondition *bc = face->getBoundary()->getBoundaryCondition("Temperature");
        double adjustedValue = adjustDiffusionSpCoefficientWithBC(value, bc);
        spCoefficient = spCoefficient + adjustedValue;
    }
    
    return spCoefficient;
}

double MeshDescritizer::computeCellSuCoefficient(CellDescritization *cd) {
    double suCoefficient = 0; //the coefficient of the cell itself
    
    std::map<Face*, double>* suComps = cd->getDiffusionSuComponents();
    typedef std::map<Face*, double>::iterator faceP_double_map;
    
    for (faceP_double_map it = suComps->begin(); it != suComps->end(); it++) {
        Face *face = it->first;
        BoundaryCondition *bc = face->getBoundary()->getBoundaryCondition("Temperature");
        double value = it->second;
        double adjustedValue = adjustDiffusionSuCoefficientWithBC(value, bc, face->getArea());
        suCoefficient = suCoefficient + adjustedValue;
    }
    
//    suComps = cd->getConvectionSuComponents();
//    for (faceP_double_map it = suComps->begin(); it != suComps->end(); it++) {
//        Face *face = it->first;
//        double coeff = it->second;
//        double variableValue = computeFaceVariableValueFromBC(face, cd->getCell());
//        double adjustedValue = adjustConvectionSuCoefficientWithBC(coeff, variableValue);
//        suCoefficient = suCoefficient + adjustedValue;
//    }
    
    return suCoefficient;
}

double MeshDescritizer::computeFaceVariableValueFromBC(Face *face, FvCell *cell) {
    BoundaryCondition *bc = face->getBoundary()->getBoundaryCondition("Temperature");

    if (bc->getType() == BoundaryCondition::FIXED_VALUE) {
        return bc->getValue();
    } else if (bc->getType() == BoundaryCondition::ADIABATIC) {
        return *(cell->getSolutionField("Temperature"));
    } else if (bc->getType() == BoundaryCondition::FIXED_FLUX) {
        Face **faces = cell->getFaces();
        if (face == faces[0] || face == faces[2] || face == faces[4]) {
            //face normal in global coordinate axis direction
            double suComponent = allDescritizations->at(cell)->getDiffusionSuComponents()->at(face);
            return bc->getValue()/suComponent + *(cell->getSolutionField("Temperature"));
        }else{
            double suComponent = allDescritizations->at(cell)->getDiffusionSuComponents()->at(face);
            return -1.0*bc->getValue()/suComponent + *(cell->getSolutionField("Temperature"));
        }
    }
}

double MeshDescritizer::computeMassBalanceCoefficient(CellDescritization* cd) {
    double massBalanceCoefficient = 0; //the coefficient of the cell itself
    
//    std::map<const FvCell*, double>* massBalanceComps = cd->getConvectionMassBalanceComponents();
//    typedef std::map<const FvCell*, double>::iterator cellP_double_map;
//    for (cellP_double_map it = massBalanceComps->begin(); it != massBalanceComps->end(); it++) {
//        massBalanceCoefficient = massBalanceCoefficient + it->second;
//    }
    
    return massBalanceCoefficient;    
}

double MeshDescritizer::adjustDiffusionSpCoefficientWithBC(double coeff, BoundaryCondition* bc) {
    if (bc->getType() == BoundaryCondition::FIXED_VALUE) {
        return coeff; //no change
    } else if (bc->getType() == BoundaryCondition::ADIABATIC) {
        return coeff*0.0;
    } else if (bc->getType() == BoundaryCondition::FIXED_FLUX) {
        return coeff*0.0;
    }else{
        return coeff;
    }
}

double MeshDescritizer::adjustDiffusionSuCoefficientWithBC(double coeff, BoundaryCondition* bc, double faceArea) {
    if (bc->getType() == BoundaryCondition::FIXED_VALUE) {
        return coeff*bc->getValue();
    } else if (bc->getType() == BoundaryCondition::ADIABATIC) {
        return coeff*0.0;
    } else if (bc->getType() == BoundaryCondition::FIXED_FLUX) {
        return coeff*0.0 + bc->getValue()*faceArea;
    }else{
        return coeff;
    }
}

double MeshDescritizer::adjustConvectionSpCoefficientWithBC(double coeff, BoundaryCondition* bc) {
    return coeff;
}

double MeshDescritizer::adjustConvectionSuCoefficientWithBC(double coeff, double variableValue) {
    return coeff*variableValue;
}



