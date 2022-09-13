#include <iostream>
#include"sculptor.hpp"

using namespace std;

int main(){
    int c;

    Sculptor mjolnir(150, 150, 150);
    
    //cabe�a do martelo
    mjolnir.setColor(0.502, 0.502, 0.502, 1.0);
    mjolnir.putVoxel(0,0,0);
    mjolnir.putBox(0,50,0,30,0,24);
   
   for (c=0;c<=5;c++){
     //quina direita inferior
     mjolnir.cutBox((44+c),50,(29-c),30-c,0,24);
     //quina esquerda inferior
     mjolnir.cutBox(0,6-c,(29-c),30-c,0,24);
    //quina esquerda superior
      mjolnir.cutBox(0,(6-c),(0+c),1+c,0,24);
    //quina direita superior
      mjolnir.cutBox((44+c),50,(0+c),1+c,0,24);
   }
    
    
    for(c=0;c<=4;c++){
      //quebra frontal inferior
      mjolnir.cutBox((6-c),(45+c),(29-c),30-c,19+c,24);
      //quebra frontal superior
      mjolnir.cutBox((6-c),(45+c),(0+c),1+c,19+c,24);
      //quebra traseira inferior
      mjolnir.cutBox((6-c),(45+c),(29-c),30-c,0,5-c);
      //quebra frontal superior
      mjolnir.cutBox((6-c),(45+c),(0+c),1+c,0,5-c);
    }
    //cabo do martelo
    mjolnir.setColor(0.5882, 0.2941, 0.0, 1.0);
    mjolnir.putBox(22,28,30,80,9,14);
    //recorte do cabo
    for (c=30;c<80;c+=3){
      mjolnir.cutBox(22,28,c,c+1,9,10);
      mjolnir.cutBox(22,28,c,c+1,13,14);
      mjolnir.cutBox(22,23,c,c+1,9,14);
      mjolnir.cutBox(27,28,c,c+1,9,14);
    }
   
    
    mjolnir.writeOFF((char*)"mjonir.off");
	
	return 0;
 }
