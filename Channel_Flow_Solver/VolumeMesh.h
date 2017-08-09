/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   VolumeMesh.h
 * Author: cd8qvt
 *
 * Created on May 19, 2017, 5:12 PM
 */

#ifndef VOLUMEMESH_H
#define VOLUMEMESH_H

#include "Point.h"
#include "Face.h"
#include "FvCell.h"
#include "MeshUtilities.h"
#include "Boundary.h"

class VolumeMesh {
public:
    VolumeMesh();
    VolumeMesh(const VolumeMesh& orig);
    virtual ~VolumeMesh();
    long getCellCount();
    long getFaceCount();
    long getPointCount();
    std::vector<FvCell*>* getCells();
    std::vector<Face*>* getFaces();
    Face* findFace(Face* faceToCompare, double tolerance);
    std::vector<Face*> findFaces(std::string plane, double value, double tolerance);
    void printCells();
    void addSolutionFieldToMesh(std::string fieldName, std::vector<double>* values);
    void removeSolutionFieldFromMesh(std::string fieldName);
    friend class MeshBuilder;
    
    void addBoundary(Boundary* boundary);
    std::vector<Boundary*>* getBoundaries() const;    
    
private:
    std::vector<Point*>* allPoints;
    std::vector<Face*>* allFaces;
    std::vector<FvCell*>* allCells;
    std::vector<Boundary*>* allBoundaries;
    
    void addPoint(Point* point);
    void addFace(Face* face);
    void addCell(FvCell* cell);
};

#endif /* VOLUMEMESH_H */

