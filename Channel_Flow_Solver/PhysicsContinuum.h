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

#include "Material.h"

class PhysicsContinuum {
    
public:
    
    enum SimulationType {DIFFUSION, CONVECTION_DIFFUSION}; 
    enum ConvectionDifferencingScheme {CENTRAL, FIRST_ORDER_UPWIND};  
    
    PhysicsContinuum();
    PhysicsContinuum(const PhysicsContinuum& orig);
    virtual ~PhysicsContinuum();
    
    double getThermalConductivity() const;
    double setThermalConductivity(double conductivity);
    double getDiffusionCoefficient() const;
    void setDiffusionCoefficient(double value);
    double getDensity() const;
    void setDensity(double value);
    
    SimulationType getsimulationType() const;
    void setsimulationType(SimulationType type);
    ConvectionDifferencingScheme getConvectionDifferencingScheme() const;
    void setConvectionDifferencingScheme(ConvectionDifferencingScheme differencingScheme);  
    Material* getMaterial() const;
    void setMaterial(Material* mat);
    
private:
    double thermalConductivity;
    double diffusionCoefficient;
    double density;
    
    SimulationType simulationType;
    ConvectionDifferencingScheme differencingScheme;    
    bool diffusionEnabled, convectionEnabled;
    Material* material;
};

#endif /* PHYSICSCONTINUUM_H */

