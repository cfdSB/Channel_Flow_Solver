/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PhysicsContinuum.h
 * Author: cd8qvt
 *
 * Created on June 1, 2017, 11:16 AM
 */

#ifndef PHYSICSCONTINUUM_H
#define PHYSICSCONTINUUM_H

class PhysicsContinuum {
public:
    PhysicsContinuum();
    PhysicsContinuum(const PhysicsContinuum& orig);
    virtual ~PhysicsContinuum();
    
    double getThermalConductivity();
    double setThermalConductivity(double conductivity);
    
private:
    double thermalConductivity;
};

#endif /* PHYSICSCONTINUUM_H */

