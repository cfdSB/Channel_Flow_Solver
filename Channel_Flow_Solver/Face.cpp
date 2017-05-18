/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Face.h"

Face::Face(Point* centroid, double length, double width):
centroid(centroid), length(length), width(width){
    
}

Face::~Face(){
    centroid = 0;
}

Point* Face::getCentroid() {
    return centroid;
}

double Face::getLength() {
    return length;
}

double Face::getWidth() {
    return width;
}



