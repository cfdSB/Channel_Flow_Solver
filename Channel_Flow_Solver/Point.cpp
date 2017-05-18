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

double* Point::getCoordinates() {
    return coordinates;
}


