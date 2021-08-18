#ifndef VOXEL_H
#define VOXEL_H

struct Voxel{
	float r, g , b;// // gama de core "r, g, b"
	float a; //"a" denota a tranparência da cor para o voxel
	bool isOn;// verdeadeiro ou falso, inclusão ou não inclusão do voxel
};
#endif
