/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "FvCell.h"

FvCell::FvCell(Point* centroid, double dx, double dy, double dz): centroid(centroid), dx(dx),
        dy(dy), dz(dz){
}

Point* FvCell::getCentroid() {
    return centroid;
}

double FvCell::getDx() {
    return dx;
}

double FvCell::getDy() {
    return dy;
}

double FvCell::getDz(){
    return dz;
}

FvCell::~FvCell() {

}

void FvCell::setFaces(std::vector<Face*>& faces) {
    for(int i=0; i<6; i++){
        this->faces[i] = faces[i];
    }
}

Face** FvCell::getFaces() {
    return faces;
}





