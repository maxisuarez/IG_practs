#include <math.h>
#include "matrices-tr.h"
#include "grafo-escena.h"
#include "modelo-jer.h"
#include "malla-revol.h"

using namespace std;

C::C(){
  agregar(new Pierna());
  agregar(MAT_Escalado(-1,1,1));
  agregar(new Pierna());
  agregar(MAT_Traslacion(0,0.3,0));
  agregar(new Brazo());
  agregar(MAT_Escalado(-1,1,1));
  agregar(new Brazo());

  agregar(new Tronco());
  //agregar(MAT_Traslacion(0,0.8,0));
 // agregar(new Cuello());
  agregar(MAT_Traslacion(0,0.88,0));
  agregar(new Cara());
  agregar(new Ojo());
  agregar(MAT_Escalado(-1, 1, 1));
  agregar(new Ojo());
  agregar(new Oreja());
  agregar(MAT_Escalado(-1,1,1));
  agregar(new Oreja());
}

Ojo::Ojo()
{ 
  agregar(MAT_Traslacion(0.15, 0.3, 0.38));
  agregar(MAT_Escalado(0.03, 0.03, 0.03));
  agregar(MAT_Rotacion(65.0, 1,0,0));
  CilindroCerrado* ojo1 = new CilindroCerrado(50,100);
  ojo1->ponerColor({1.0,1.0,1.0});
  agregar(ojo1);
}

Oreja::Oreja()
{
  agregar(MAT_Traslacion(0.2, 0.45, 0.2));
  agregar(MAT_Escalado(0.03, 0.1, 0.03));
  agregar(MAT_Rotacion(45.0, 0,0,1));
  CilindroCerrado* oreja1 = new CilindroCerrado(50,100);
  oreja1->ponerColor({0.0,1.0,0.0});
  agregar(oreja1);
}

Cara::Cara()
{
  agregar(MAT_Escalado(0.5,0.5,0.5));
  Semiesfera* s = new Semiesfera(50, 100);
  s->ponerColor({0.0,1,0.0});
  agregar(s);
}

/*Cuello::Cuello()
{
  agregar(MAT_Escalado(0.45, 0.08, 0.45));
  CilindroCerrado* cuello1 = new CilindroCerrado(50,100);
  cuello1->ponerColor({1.0,1.0,1.0});
  agregar(cuello1);
}*/

Tronco::Tronco()
{
  agregar(MAT_Escalado(0.5, 0.8, 0.5));
  CilindroCerrado* tronco1 = new CilindroCerrado(50,100);
  tronco1->ponerColor({0.0,1.0,0.0});
  agregar(tronco1);
}

SemiesferaInv::SemiesferaInv()
{
  agregar(MAT_Escalado(1,-1,1));
  Semiesfera* s = new Semiesfera(50,100);
  s-> ponerColor({0.0, 1.0, 0.0});
  agregar(s);
}

Brazo::Brazo()
{
  agregar(MAT_Traslacion(0.65, 0.25, 0));
  agregar(MAT_Escalado(0.1, 0.1, 0.1));
  agregar(new SemiesferaInv());

  agregar(MAT_Escalado(1,4,1));
  CilindroCerrado* c = new CilindroCerrado(50,100);
  c->ponerColor({0.0,1.0,0.0});
  agregar(c);

  agregar(MAT_Escalado(1,0.25,1));
  agregar(MAT_Traslacion(0,4,0));
  Semiesfera* s1 = new Semiesfera(50,100);
  s1-> ponerColor({0.0, 1.0, 0.0});
  agregar(s1);
}


Pierna::Pierna()
{
  agregar(MAT_Traslacion(0.2, 0.1, 0));
  agregar(MAT_Escalado(0.1, 0.1, 0.1));
  agregar(new SemiesferaInv());

  agregar(MAT_Escalado(1,3,1));
  CilindroCerrado* c = new CilindroCerrado(50,100);
  c->ponerColor({0.0,1.0,0.0});
  agregar(c);
}

