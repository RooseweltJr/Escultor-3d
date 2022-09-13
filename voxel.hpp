#ifndef VOXEL_H
#define VOXEL_H

struct Voxel{
	float r, g , b;// // gama de core "r, g, b"
	float a; //"a" denota a tranpar�ncia da cor para o voxel
	bool isOn;// verdeadeiro ou falso, inclus�o ou n�o inclus�o do voxel
};
#endif
