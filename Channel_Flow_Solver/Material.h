/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Material.h
 * Author: cd8qvt
 *
 * Created on July 24, 2017, 4:51 PM
 */

#ifndef MATERIAL_H
#define MATERIAL_H

class Material {
public:
    Material();
    Material(const Material& orig);
    virtual ~Material();
    
public:

    double getDiffusionCoefficient() const;
    void setDiffusionCoefficient(double value);
    double getDensity() const;
    void setDensity(double value);
    
private:
    double diffusionCoefficient;
    double density;    

};

#endif /* MATERIAL_H */

