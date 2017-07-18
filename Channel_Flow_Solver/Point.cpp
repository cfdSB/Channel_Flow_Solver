/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "Point.h"

Point::Point(double xCoord, double yCoord, double zCoord){   
    coordinates[0]= xCoord;
    coordinates[1] = yCoord;
    coordinates[2] = zCoord;
}

Point::~Point() {

}

const double* Point::getCoordinates() const {
    return coordinates;
}

std::string Point::toString(){
    
    std::ostringstream output;
    double xp = coordinates[0]; double yp = coordinates[1]; double zp= coordinates[2];
    output<<"Point: "<<xp<<","<<yp<<","<<zp;
    return output.str();
}
