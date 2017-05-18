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

#include "Point.h"

class Face{
    
private:
    Point* centroid;
    double length, width;
    
public:
    Face(Point* centroid, double length, double width);
    ~Face();
    Point* getCentroid();
    double getLength();
    double getWidth();
    
    
};

#endif /* FACE_H */

