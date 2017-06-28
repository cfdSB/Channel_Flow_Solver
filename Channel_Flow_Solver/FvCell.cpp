/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "FvCell.h"

long FvCell::idCounter = 0;

FvCell::FvCell(Point* centroid, double dx, double dy, double dz): centroid(centroid), dx(dx),
        dy(dy), dz(dz){
    cellID = idCounter++;
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
    centroid = 0;
}

void FvCell::setFaces(std::vector<Face*>& faces) {
    for(int i=0; i<6; i++){
        this->faces[i] = faces[i];
    }
}

Face** FvCell::getFaces() {
    return faces;
}

long FvCell::getID() {
    return cellID;
}

std::string FvCell::toString() {
    std::ostringstream output;
    std::string pointOutput= centroid->toString();
    output<< "Cell ID: " << cellID;
    output << "Cell Centroid: " << pointOutput << "\n";
    output << "Cell Size:" << dx << "," << dy <<","<< dz << "\n";

    
    std::string faceOutput;
    for (int j = 0; j < 6; j++) {
        faceOutput = faces[j]->toString();
        output << faceOutput << "\n";
    }
    return output.str();

}

