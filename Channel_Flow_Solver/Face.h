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
#include "FvCell.h"

class FvCell;   //forward declaration to avoid circular dependency situation in header files

class Face : public Object{
    
private:
    Point* centroid;    //face centroid
    double length, width;   //face dimensions
    FvCell *cell1, *cell2;  //cells connected to faces
    
public:
    Face(Point* centroid, double length, double width);
    ~Face();
    Point* getCentroid();
    double getLength();
    double getWidth();
    FvCell* getCell1();
    FvCell* getCell2();
    void setCell1(FvCell* cell1);
    void setCell2(FvCell* cell2);
    std::string toString() override;
    FvCell* getConnectingCell(FvCell* cell);
    double getArea();

    
};

#endif /* FACE_H */

