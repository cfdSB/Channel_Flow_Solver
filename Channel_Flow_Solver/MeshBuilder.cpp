/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "MeshBuilder.h"


MeshBuilder::MeshBuilder() {
    volumeMesh.reset(new VolumeMesh());
}

MeshBuilder::~MeshBuilder() {

}

void MeshBuilder::buildMesh(double xMin, double xMax, double yMin, double yMax, double zMin, double zMax, int xCells, int yCells, int zCells){    
    
    double dx = (xMax - xMin)/xCells;
    double dy = (yMax - yMin)/yCells;
    double dz = (zMax - zMin)/zCells;
    
    double currentX = 0.0;
    for(int i =0; i< xCells; i++){
        
        if(i==0){
            currentX = currentX + dx/2.0;
        }else{
            currentX = currentX + dx;
        }
        double currentY = 0.0;
        for(int j = 0; j< yCells; j++){
            
            if (j == 0) {
                currentY = currentY + dy / 2.0;
            } else {
                currentY = currentY + dy;
            }

            double currentZ = 0.0;
            for (int k = 0; k < zCells; k++) {
                
                if (k == 0) {
                    currentZ = currentZ + dz / 2.0;
                } else {
                    currentZ = currentZ + dz;
                }
                
                //create cell
                Point* cellCenter = new Point(currentX, currentY, currentZ);
                FvCell* cell = new FvCell(cellCenter, dx, dy, dz);
                volumeMesh->addPoint(cellCenter);
                volumeMesh->addCell(cell);
                std::vector<Face*> faces = buildFaces(cell);
                cell->setFaces(faces);
                                        
            }
        }
    }    
}


void MeshBuilder::printCell(FvCell* cell){
    std::cout<<"-----------------"<<std::endl;
    double* centroid = cell->getCentroid()->getCoordinates();
    std::cout<<centroid[0]<<","<<centroid[1]<<","<<centroid[2]<<","<<cell->getDx()<<","<<cell->getDy()<<","<<cell->getDz()<<std::endl;
    
    //print faces
    for(int i=0; i<6; i++){
        Face* face = (cell->getFaces())[i];
        printFace(face);
    }
}

void MeshBuilder::printFace(Face* face) {
    double* centroidF = face->getCentroid()->getCoordinates();
    std::cout << centroidF[0] << "," << centroidF[1] << "," << centroidF[2] << "," << face->getLength() << "," << face->getWidth() << std::endl;
}


std::vector<Face*> MeshBuilder:: buildFaces(FvCell* cell){
    std::vector<Face*> faces;
    double* cellCentroid = cell->getCentroid()->getCoordinates();
    //x- face
    double xm_x = cellCentroid[0] - cell->getDx()/2.0;
    double xm_y = cellCentroid[1];
    double xm_z = cellCentroid[2];
    
    std::unique_ptr<Point> tmpPointXm(new Point(xm_x, xm_y, xm_z));
    std::unique_ptr<Face> tmpFaceXm (new Face(tmpPointXm.get(), cell->getDy(), cell->getDz()));
    
    Face* face1 = FindFaceAndConnectToCell(tmpPointXm, tmpFaceXm, cell);
    faces.push_back(face1);
    
    //x+ face
    double xp_x = cellCentroid[0] + cell->getDx()/2.0;
    double xp_y = cellCentroid[1];
    double xp_z = cellCentroid[2];

    std::unique_ptr<Point> tmpPointXp(new Point(xp_x, xp_y, xp_z));
    std::unique_ptr<Face> tmpFaceXp (new Face(tmpPointXp.get(), cell->getDy(), cell->getDz()));
    
    Face* face2 = FindFaceAndConnectToCell(tmpPointXp, tmpFaceXp, cell); 
    faces.push_back(face2);
    
    //y- face
    double ym_x = cellCentroid[0];
    double ym_y = cellCentroid[1] - cell->getDy()/2.0;
    double ym_z = cellCentroid[2];
    
    std::unique_ptr<Point> tmpPointYm(new Point(ym_x, ym_y, ym_z));
    std::unique_ptr<Face> tmpFaceYm (new Face(tmpPointYm.get(), cell->getDx(), cell->getDz())); 
   
    Face* face3 = FindFaceAndConnectToCell(tmpPointYm, tmpFaceYm, cell);
    faces.push_back(face3);
    
    //y+ face
    double yp_x = cellCentroid[0];
    double yp_y = cellCentroid[1] + cell->getDy()/2.0;
    double yp_z = cellCentroid[2];  
    
    std::unique_ptr<Point> tmpPointYp(new Point(yp_x, yp_y, yp_z));
    std::unique_ptr<Face> tmpFaceYp (new Face(tmpPointYp.get(), cell->getDx(), cell->getDz())); 
    
    Face* face4 = FindFaceAndConnectToCell(tmpPointYp, tmpFaceYp, cell); 
    faces.push_back(face4);
    
    //z- face
    double zm_x = cellCentroid[0];
    double zm_y = cellCentroid[1];
    double zm_z = cellCentroid[2] - cell->getDz()/2.0;
    
    std::unique_ptr<Point> tmpPointZm(new Point(zm_x, zm_y, zm_z));
    std::unique_ptr<Face> tmpFaceZm (new Face(tmpPointZm.get(), cell->getDx(), cell->getDy())); 
    
    Face* face5 = FindFaceAndConnectToCell(tmpPointZm, tmpFaceZm, cell);
    faces.push_back(face5);
    
    //z+ face
    double zp_x = cellCentroid[0];
    double zp_y = cellCentroid[1];
    double zp_z = cellCentroid[2] + cell->getDz()/2.0;
    
    std::unique_ptr<Point> tmpPointZp(new Point(zp_x, zp_y, zp_z));
    std::unique_ptr<Face> tmpFaceZp (new Face(tmpPointZp.get(), cell->getDx(), cell->getDy())); 
    
    Face* face6 = FindFaceAndConnectToCell(tmpPointZp, tmpFaceZp, cell);
    faces.push_back(face6);
    
    return faces;
}

void MeshBuilder::assignFaceToCell(Face* face, FvCell* cell) {
    if(face->getCell1()==NULL){
        face->setCell1(cell);
    }else if(face->getCell2()==NULL){
        face->setCell2(cell);
    }
}

Face* MeshBuilder::FindFaceAndConnectToCell(std::unique_ptr<Point>& pnt, std::unique_ptr<Face>& face, FvCell* cell) {
    Face* faceFound = volumeMesh->findFace(face.get(),faceMatchTolerance); //find existing face, or return the comparing face

    //face does not exist already
    if (faceFound == NULL) {
        std::cout<<"Face does not exist"<<std::endl;
        volumeMesh->addFace(face.get());
        volumeMesh->addPoint(pnt.get());
        faceFound = face.get();   //return the newly created face
        assignFaceToCell(face.get(), cell);
        pnt.release(); //so that point is not destroyed when unique_ptr goes out of scope
        face.release();
        
    } else { //face already exists
        std::cout << "Face already exists"<<std::endl;
        assignFaceToCell(faceFound, cell);
    }
    
    return faceFound;
}

void MeshBuilder::printMeshReport() {
    volumeMesh->printCells();
    std::cout<<"Cell Count: "<< volumeMesh->getCellCount()<<std::endl;
    std::cout<<"Face Count: "<< volumeMesh->getFaceCount()<<std::endl;
    std::cout<<"Point Count: "<< volumeMesh->getPointCount()<< std::endl;
}

VolumeMesh* MeshBuilder::getVolumeMesh() {
    return volumeMesh.get();
}

   





