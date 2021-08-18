#ifndef SCULPTOR_H
#define SCULPTOR_H
#include "voxel.hpp"


class Sculptor {

private:
  Voxel ***vox;// Matriz em 3 dimens�es para cria�o dos voxels. Como se cada ponteiro representasse uma dimens�o da matriz.
  int nx,ny,nz; // Dimens�es
  float r,g,b,a; // Serve para manipular as cores para cada parte do desenho que desejo colorir
  
public:
  Sculptor(int _nx, int _ny, int _nz);
  ~Sculptor();// Destrutor
  void setColor(float r, float g, float b, float alpha);
  void putVoxel(int x, int y, int z);//Adiona um voxel na determinada posi�o de x,y,z
  void cutVoxel(int x, int y, int z);//Remove um voxel na determinada posi�o de x,y,z
  void putBox(int x0, int x1, int y0, int y1, int z0, int z1);//Implementa um s�rie de voxels em um espa�o determinado das cordenadas
  void cutBox(int x0, int x1, int y0, int y1, int z0, int z1);//Retira uma s�rie de voxels em um espa�o determinado das cordenadas
  void putSphere(int xcenter, int ycenter, int zcenter, int radius);//Criar uma esfera
  void cutSphere(int xcenter, int ycenter, int zcenter, int radius);//Retirar uma esfera
  void putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);//Criar elipsoide
  void cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);//Retirar elipsoide
  void writeOFF(char *filename);//Fun�o que vai escrever meu arquivo .off
};
#endif
