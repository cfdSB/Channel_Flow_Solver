/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Face.h
 * Author: cd8qvt
 *
 * Created on May 15, 2017, 4:56 PM
 */

#ifndef FACE_H
#define FACE_H

#include "Object.h"
#include "Point.h"
#include <iostream>
#include <sstream>
#include <map>
#include "FvCell.h"

class FvCell;   //forward declaration to avoid circular dependency situation in header files
class Boundary;

class Face : public Object{

public:
    enum FaceType {INTERNAL_FACE, BOUNDARY_FACE};
    
private:
    Point* centroid;    //face centroid
    double length, width;   //face dimensions
    FvCell *cell1, *cell2;  //cells connected to faces
    Boundary *boundary;     //boundary connected to face
    std::map<std::string, double*>* solutionFields;
    FaceType fType;
    
public: 
    Face(Point* centroid, double length, double width);
    ~Face();
    const Point* getCentroid() const;
    double getLength() const;
    double getWidth() const;
    const FvCell* getCell1() const;
    const FvCell* getCell2() const;
    void setCell1(FvCell* cell1);
    void setCell2(FvCell* cell2);
    std::string toString() override;
    const FvCell* getConnectingCell(FvCell* cell) const;
    double getArea() const;
    Boundary* getBoundary() const;
    void setBoundary(Boundary* boundary);
    
    void addSolutionField(std::string fieldName, double* val);
    void removeSolutionField(std::string fieldName);
    double* getSolutionField(std::string fieldName) const;
    
    FaceType getType() const;
    void setType(FaceType type);

    
};

#endif /* FACE_H */

