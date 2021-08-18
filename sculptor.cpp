#include "sculptor.hpp"//Declara�o das fun�es do header
#include <iostream>
#include <stdlib.h>
#include <cmath> 
#include <vector>
#include <string>
#include <fstream>//Saida com arquivo

 using namespace std;

 Sculptor::Sculptor(int _nx, int _ny, int _nz){//Fun�o construtora -> recebe o n� m�ximo de dimens�es que vou utilizar

	this -> nx = _nx;//This referencia nx como ponteiro
	this -> ny = _ny;
	this -> nz = _nz;
	this -> r = 0;
	this -> g = 0;
	this -> b = 0;
	this -> a = 0;
	
	vox = new Voxel**[_nx]; //1� dimens�o da matriz tem o valor de _nx
	for (int i = 0; i < _nx; i++){
		
		vox[i]= new Voxel *[_ny]; //2� dimens�o da matriz
		for ( int j = 0; j < _ny; j++){
			
			vox [i][j] = new Voxel [_nz];// 3� dimens�o da matriz
			for (int k = 0; k < _nz; k++){
//Reserva o espa�o em 3 dimens�es que eu vou trabalhar					
				this -> vox [i][j][k].r= 0;
				this -> vox [i][j][k].g= 0;
				this -> vox [i][j][k].b= 0;
				this -> vox [i][j][k].a= 0;
				this -> vox [i][j][k].isOn= false;// Por enquanto ainda n�o � vizualiz�vel
			}	
		}
	}			
}


 Sculptor::~Sculptor(){// Fun�o destrutora da classe para liberar a mem�ria
	
	for(int i = 0; i < nx; i++){
		for ( int j = 0; j < ny; j++){
			delete [] vox[i][j];
		}
		delete[] vox [i];
	}
	delete[]vox;	
}	

//Defini�o das fun�es:

//setColor 
 void Sculptor::setColor(float r, float g, float b, float alpha){ // Defini�o das cores dos voxels
 	
	this -> r = r;
	this -> g = g;
	this -> b = b;
	this -> a = alpha;
 	
 }
 
 //putVoxel
 void Sculptor::putVoxel(int x, int y, int z){ //Mostra os voxel e suas caracteristicas de cores
 	
 	this -> vox[x][y][z].r = this -> r;
 	this -> vox[x][y][z].g = this -> g;
 	this -> vox[x][y][z].b = this -> b;
 	this -> vox[x][y][z].a = this -> a;
 	this -> vox[x][y][z].isOn = true;
 	
 }

//cutVoxel
 void Sculptor::cutVoxel(int x, int y, int z){ //Retira o voxel nas cordenadas que se deseja
 	
 	this -> vox[x][y][z].isOn = false;
 	
 }

//putBox
 void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1){ //Adcionar uma quantidade de voxels em serie
	
	//Faz uma verifica�o se o intervalo de entrada est� dentro da dimens�o
	x0 = (x0 < 0) ? 0 : x0;//Menor do que x0 n�o atribui x0 por n�o ter um espa�o reservado
	x1 = (x1 > this-> nx) ? this-> nx : x1; // Delimita uma valor m�ximo para cria�o do Box de Voxels
	y0 = (y0 < 0) ? 0 : y0;
	y1 = (y1 > this-> ny) ? this-> ny : y1;
	z0 = (z0 < 0) ? 0 : z0;
	z1 = (z1 > this-> nz) ? this-> nz : z1;

	//Atribuindo os voxels dentros dos intervalos	
	for (int i = x0; i < x1; i++){
		for (int j = y0; j < y1; j++){
			for (int k = z0; k < z1; k++){
				this -> putVoxel (i, j, k);
			}
		}
	}	
 }
 
 //cutBox
 void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1){ //N�o deixa visivel os voxels construidos pela putBox
 	
	for (int i = x0; i < x1; i++){
		for (int j = y0; j < y1; j++){
			for (int k = z0; k < z1; k++){
				this -> cutVoxel (i, j, k);
			}
		}
	}	
}

//putSphere
 void Sculptor::putSphere( int xcenter , int ycenter, int zcenter, int radius){//Cri�o de uma "esfera"
	putEllipsoid (xcenter, ycenter, zcenter, radius, radius, radius);
 }
 
//cutSphere
 void Sculptor::cutSphere(int xcenter , int ycenter, int zcenter, int radius){// Retirar a "esfera"
	cutEllipsoid (xcenter, ycenter, zcenter, radius, radius, radius);
 }
 
//putEllipsoid
 void Sculptor::putEllipsoid(int xcenter , int ycenter, int zcenter, int rx, int ry, int rz){//Criador de uma elipse
	
	//Faz uma verifica�o se o intervalo de entrada est� dentro da dimens�o, do centro at� o raio
	int x0 = (xcenter - rx < 0)	? 0 : xcenter - rx;
	int x1 = (xcenter + rx > this -> nx) ? this -> nx : xcenter + rx;
	int y0 = (ycenter - ry < 0) ? 0 : ycenter - ry;
    int y1 = (ycenter + ry > this -> ny) ? this -> ny : ycenter + ry;
    int z0 = (zcenter - rz < 0) ? 0 : zcenter - rz;
    int z1 = (zcenter + rz > this -> nz) ? this -> nz : zcenter + rz;

	//Verifica se o centro de elipse mais/menos o raio est�o dentro da elipse
	for(int i = x0; i < x1; i++){
		for (int j = y0; j < y1; j++){
			for (int k = z0; k < z1; k++){
				if(pow(i - xcenter, 2) / pow(rx, 2) + pow(j - ycenter, 2) / pow(ry, 2) + pow(k - zcenter, 2) / pow(rz, 2) < 1){
				this -> putVoxel (i,j,k);
				}
			}
		}
	}
 } 
 
//cutEllipsoid
 void Sculptor::cutEllipsoid(int xcenter , int ycenter, int zcenter, int rx, int ry, int rz){//Criador de uma elipse
	
	//Faz uma verifica�o se o intervalo de entrada est� dentro da dimens�o, do centro at� o raio
	int x0 = (xcenter - rx < 0)	? 0 : xcenter - rx;
	int x1 = (xcenter + rx > this -> nx) ? this -> nx : xcenter + rx;
	int y0 = (ycenter - ry < 0) ? 0 : ycenter - ry;
    int y1 = (ycenter + ry > this -> ny) ? this -> ny : ycenter + ry;
    int z0 = (zcenter - rz < 0) ? 0 : zcenter - rz;
    int z1 = (zcenter + rz > this -> nz) ? this -> nz : zcenter + rz;

	//Verifica se o centro de elipse mais/menos o raio est�o dentro da elipse
	for(int i = x0; i < x1; i++){
		for (int j = y0; j < y1; j++){
			for (int k = z0; k < z1; k++){
				if(pow(i - xcenter, 2) / pow(rx, 2) + pow(j - ycenter, 2) / pow(ry, 2) + pow(k - zcenter, 2) / pow(rz, 2) < 1){
				this -> cutVoxel (i,j,k);
				}
			}
		}
	}
 } 
 
 void Sculptor::writeOFF(char *filename){

    ofstream myFile(filename);
    
    if (!myFile.is_open()){
        cout << "Error while open file: "<< filename << endl;
        exit(1);
    }
    //Contador de voxels
    int vOn = 0, i, j, k;
    for (i = 0; i < nx; i++){
        for (j = 0; j < ny; j++){
            for (k = 0; k < nz; k++){
                if (this->vox[i][j][k].isOn){
                    vOn++;
                }
            }
        }
    }

//Escrevendo em OFF
    myFile << "OFF" << endl;
    myFile << 8 * vOn << " " << 6 * vOn << " 0" << endl;

 for (i = 0; i < nx; i++) {
        for (j = 0; j < ny; j++){
            for (k = 0; k < nz; k++){
                if (this->vox[i][j][k].isOn){
                    
                    myFile << i - 0.5 << " " << j + 0.5 << " " << k - 0.5 << endl;
                    myFile << i - 0.5 << " " << j - 0.5 << " " << k - 0.5 << endl;
                    myFile << i + 0.5 << " " << j - 0.5 << " " << k - 0.5 << endl;
                    myFile << i + 0.5 << " " << j + 0.5 << " " << k - 0.5 << endl;
                    myFile << i - 0.5 << " " << j + 0.5 << " " << k + 0.5 << endl;
                    myFile << i - 0.5 << " " << j - 0.5 << " " << k + 0.5 << endl;
                    myFile << i + 0.5 << " " << j - 0.5 << " " << k + 0.5 << endl;
                    myFile << i + 0.5 << " " << j + 0.5 << " " << k + 0.5 << endl;
                }
            }
        }
    }

//Contador -> escreve em qual face eu quero cada propriedade    
 int contVOn = 0;
    for (i = 0; i < nx; i++){
        for (j = 0; j < ny; j++){
            for (k = 0; k < nz; k++){
                if (this->vox[i][j][k].isOn){
                	//origem de cordenadas ; 1� face 0, 3 ,2 1; cor ; transpar�ncia
                    myFile << "4 " << contVOn * 8 + 0 << " " << contVOn * 8 + 3 << " " << contVOn * 8 + 2 << " " << contVOn * 8 + 1 << " " << this->vox[i][j][k].r << ".0 " << this->vox[i][j][k].g << ".0 " << this->vox[i][j][k].b << ".0 " << this->vox[i][j][k].a << ".0" << endl;
                    myFile << "4 " << contVOn * 8 + 4 << " " << contVOn * 8 + 5 << " " << contVOn * 8 + 6 << " " << contVOn * 8 + 7 << " " << this->vox[i][j][k].r << ".0 " << this->vox[i][j][k].g << ".0 " << this->vox[i][j][k].b << ".0 " << this->vox[i][j][k].a << ".0" << endl;
                    myFile << "4 " << contVOn * 8 + 0 << " " << contVOn * 8 + 1 << " " << contVOn * 8 + 5 << " " << contVOn * 8 + 4 << " " << this->vox[i][j][k].r << ".0 " << this->vox[i][j][k].g << ".0 " << this->vox[i][j][k].b << ".0 " << this->vox[i][j][k].a << ".0" << endl;
                    myFile << "4 " << contVOn * 8 + 0 << " " << contVOn * 8 + 4 << " " << contVOn * 8 + 7 << " " << contVOn * 8 + 3 << " " << this->vox[i][j][k].r << ".0 " << this->vox[i][j][k].g << ".0 " << this->vox[i][j][k].b << ".0 " << this->vox[i][j][k].a << ".0" << endl;
                    myFile << "4 " << contVOn * 8 + 3 << " " << contVOn * 8 + 7 << " " << contVOn * 8 + 6 << " " << contVOn * 8 + 2 << " " << this->vox[i][j][k].r << ".0 " << this->vox[i][j][k].g << ".0 " << this->vox[i][j][k].b << ".0 " << this->vox[i][j][k].a << ".0" << endl;
                    myFile << "4 " << contVOn * 8 + 1 << " " << contVOn * 8 + 2 << " " << contVOn * 8 + 6 << " " << contVOn * 8 + 5 << " " << this->vox[i][j][k].r << ".0 " << this->vox[i][j][k].g << ".0 " << this->vox[i][j][k].b << ".0 " << this->vox[i][j][k].a << ".0" << endl;
                    contVOn++;
                }
            }
        }
    }
   
    myFile.close();
 }
	
	

