/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MeshUtilities.cpp
 * Author: cd8qvt
 * 
 * Created on May 20, 2017, 4:54 PM
 */

#include "MeshUtilities.h"

MeshUtilities::MeshUtilities() {
}

MeshUtilities::MeshUtilities(const MeshUtilities& orig) {
}

MeshUtilities::~MeshUtilities() {
}

double MeshUtilities::findDistance(Point& p1, Point& p2) {

    double* d1 = p1.getCoordinates();
    double* d2 = p2.getCoordinates();

    double distance = pow((d2[0] - d1[0]), 2) + pow((d2[1] - d1[1]), 2) + pow((d2[2] - d1[2]), 2);
    distance = sqrt(distance);
    return distance;

}

