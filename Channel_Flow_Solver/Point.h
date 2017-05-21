/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Point.h
 * Author: cd8qvt
 *
 * Created on May 15, 2017, 4:41 PM
 */

#ifndef POINT_H
#define POINT_H
#include "Object.h"
#include <iostream>
#include <sstream>

class Point: public Object{
private:
    double coordinates[3];    //array holding coordinate values
    
public:
    Point(double xCoord, double yCoord, double zCoord);
    double* getCoordinates();
    ~Point();
    std::string toString() override;

    
};


#endif /* POINT_H */

