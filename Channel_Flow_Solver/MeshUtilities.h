/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MeshUtilities.h
 * Author: cd8qvt
 *
 * Created on May 20, 2017, 4:54 PM
 */

#ifndef MESHUTILITIES_H
#define MESHUTILITIES_H

#include "Point.h"
#include <cmath>

class MeshUtilities {
public:
    MeshUtilities();
    MeshUtilities(const MeshUtilities& orig);
    virtual ~MeshUtilities();
    static double findDistance(Point& p1, Point& p2);
private:

};

#endif /* MESHUTILITIES_H */

