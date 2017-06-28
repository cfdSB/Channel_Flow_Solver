/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FvCell.h
 * Author: cd8qvt
 *
 * Created on May 16, 2017, 1:06 PM
 */

#ifndef FVCELL_H
#define FVCELL_H

#include "Object.h"
#include "Point.h"
#include "Face.h"
#include <vector>
#include <sstream>

class Face;
class FvCell: public Object{
private:
    long cellID;
    Point* centroid;    //cell centroid
    double dx, dy, dz;  //cell dimensions
    Face* faces[6] ;  //to hold pointers to all 6 faces of a cell in order: x-, x+, y-, y+ z-, z+;
    static long idCounter;  //holds latest id number
    
public:
    FvCell(Point* centroid, double dx, double dy, double dz);
    ~FvCell();
    Point* getCentroid();
    double getDx();
    double getDy();
    double getDz();
    long getID();
    void setFaces(std::vector<Face*>& faces);
    Face** getFaces();
    std::string toString() override;

};


#endif /* FVCELL_H */

