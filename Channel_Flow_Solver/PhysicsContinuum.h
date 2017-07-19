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
    
    double getThermalConductivity() const;
    double setThermalConductivity(double conductivity);
    double getDiffusionCoefficient() const;
    void setDiffusionCoefficient(double value);
    double getDensity() const;
    void setDensity(double value);
    
private:
    double thermalConductivity;
    double diffusionCoefficient;
    double density;
};

#endif /* PHYSICSCONTINUUM_H */

