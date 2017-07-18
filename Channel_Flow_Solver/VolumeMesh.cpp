/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   VolumeMesh.cpp
 * Author: cd8qvt
 * 
 * Created on May 19, 2017, 5:12 PM
 */

#include <vector>
#include <cmath>
#include "VolumeMesh.h"

VolumeMesh::VolumeMesh() {
    allPoints = new std::vector<Point*>();
    allFaces = new std::vector<Face*>();
    allCells = new std::vector<FvCell*>();
}

VolumeMesh::VolumeMesh(const VolumeMesh& orig) {
}

VolumeMesh::~VolumeMesh() {
    
    //delete all point objects
    for(int i=0; i<allPoints->size(); i++) {
        Point* p = (*allPoints)[i];
        delete p;
    }
    delete allPoints;   //delete vector object

    //delete all face objects
    for (int i = 0; i < allFaces->size(); i++) {
        Face* p = (*allFaces)[i];
        delete p;
    }
    delete allFaces;    //delete vector object
    
    //delete all cell objects
    for (int i = 0; i < allCells->size(); i++) {
        FvCell* p = (*allCells)[i];
        delete p;
    }
    delete allCells;    //delete vector object    
}

void VolumeMesh::addPoint(Point* point) {
    allPoints->push_back(point);
}

void VolumeMesh::addFace(Face* face) {
    allFaces->push_back(face);
}

void VolumeMesh::addCell(FvCell* cell) {
    allCells->push_back(cell);
}

long VolumeMesh::getCellCount() {
    return static_cast<long>(allCells->size());
}

long VolumeMesh::getFaceCount() {
    return static_cast<long>(allFaces->size());
}

long VolumeMesh::getPointCount() {
    return static_cast<long>(allPoints->size());
}

std::vector<FvCell*>* VolumeMesh::getCells() {
    return allCells;
}

std::vector<Face*>* VolumeMesh::getFaces() {
    return allFaces;
}

Face* VolumeMesh::findFace(Face* faceToCompare, double tolerance){
    Face* faceFound = NULL;
    
    for(int i=0; i< allFaces->size(); i++){
        Face* tmpFace = (*allFaces)[i];
        
        const Point* centroid1 = tmpFace->getCentroid();
        const Point* centroid2 = faceToCompare->getCentroid();
        
        double distance = MeshUtilities::findDistance(*centroid1, *centroid2);
        if(distance < tolerance){
            std::cout << "Distance: " << distance << " less than tolerance "<<tolerance<<std::endl;
            faceFound = tmpFace;
            break;
        }
    }
    
    return faceFound;
}

void VolumeMesh::printCells() {
    for (int i = 0; i < allCells->size(); i++) {
        FvCell* cell = (*allCells)[i];
        std::cout << "-------------------" << std::endl;
        std::string output = cell->toString();
        std::cout << output << std::endl;
        
    }
}

std::vector<Face*> VolumeMesh::findFaces(std::string plane, double value, double tolerance) {
    std::vector<Face*> faces;
    
    for(int i=0; i< allFaces->size(); i++){
        Face* face = (*allFaces)[i];
        double coord = 0.0;
        if(plane == "x"){
            coord = face->getCentroid()->getCoordinates()[0];
        }else if(plane == "z"){
            coord = face->getCentroid()->getCoordinates()[2];
        }else if(plane == "y"){
            coord = face->getCentroid()->getCoordinates()[1];
        }
        double diff = coord - value;
        double absValue = std::abs(diff);
        if(absValue <= tolerance){
            faces.push_back(face);
        }
    }
    
    return faces;
}









