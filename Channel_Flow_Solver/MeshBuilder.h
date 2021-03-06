/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MeshBuilder.h
 * Author: cd8qvt
 *
 * Created on May 16, 2017, 3:27 PM
 */

#ifndef MESHBUILDER_H
#define MESHBUILDER_H

#include <vector>
#include <iostream>
#include "Point.h"
#include "Face.h"
#include "FvCell.h"
#include <memory>
#include <cmath>
#include "VolumeMesh.h"

class MeshBuilder{
    
public:
    MeshBuilder();
    ~MeshBuilder();
    void buildMesh(double xMin, double xMax, double yMin, double yMax, double zMin, double zMax, int xCells, int yCells, int zCells);    
    void printCells();
    const double faceMatchTolerance = 1e-6;
    void printMeshReport();
    VolumeMesh* getVolumeMesh();

private:

    std::unique_ptr<VolumeMesh> volumeMesh;
    double domain_xMin, domain_xMax, domain_yMin, domain_yMax, domain_zMin, domain_zMax;
    int xCells, yCells, zCells;
    
    std::vector<Face*> buildFaces(FvCell* cell);
    void printCell(FvCell* cell);
    double findDistance(Point& p1, Point& p2);
    void assignFaceToCell(Face* face, FvCell* cell);
    Face* FindFaceAndConnectToCell(std::unique_ptr<Point> &pnt, std::unique_ptr<Face> &face, FvCell* cell);
    void printFace(Face* face);
};

#endif /* MESHBUILDER_H */

