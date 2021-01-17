// Nombre: Maximino, Apellidos: Suarez van Gelderen, DNI/Pasaporte: 44668999D (DDGG IG curso 20-21) 

#include <math.h>
#include "matrices-tr.h"
#include "grafo-escena.h"
#include "modelo-jer.h"
#include "malla-revol.h"

using namespace std;

C::C(){

	ponerNombre("Muneco Android");
	int i = agregar(MAT_Traslacion(0.0, 0.0, 0.0));
	mat_traslacion = leerPtrMatriz(i);

	agregar(new Pierna());
	agregar(MAT_Escalado(-1,1,1));
	agregar(new Pierna());


	agregar(MAT_Traslacion(0,0.3,0));
	Brazo* brazo1 = new Brazo();
	mat_mov_brazo1 = brazo1->mat_mov_brazo;
	//i = brazo1->agregar(MAT_Rotacion(0.0, 1.0, 0.0, 0.0));
	agregar(brazo1);
	//mat_mov_brazo1 = leerPtrMatriz(i);

	agregar(MAT_Escalado(-1,1,1));

	Brazo* brazo2 = new Brazo();
	mat_mov_brazo2 = brazo2->mat_mov_brazo;
	//i = brazo2->agregar(MAT_Rotacion(0.0, 1.0, 0.0, 0.0));
	agregar(brazo2);
	//mat_mov_brazo2 = leerPtrMatriz(i);

	agregar(new Tronco());
	//agregar(MAT_Traslacion(0,0.8,0));
	// agregar(new Cuello());
	agregar(MAT_Traslacion(0,0.88,0));

	Cabeza* cabeza1 = new Cabeza();
	mat_mov_cabeza = cabeza1->mat_mov_cabeza;
	//i = cabeza1->agregar(MAT_Rotacion(0.0, 0.0, 1.0, 0.0));
	agregar(cabeza1);
	//mat_mov_cabeza = leerPtrMatriz(i);

}

unsigned C::leerNumParametros() const {

	return 0;
}


void C::actualizarEstadoParametro(const unsigned iParam, const float t_sec) {

	assert(iParam < leerNumParametros());

	float v;

	switch (iParam) {

	case 0:
		v = sin( 2 * M_PI * t_sec * 0.1);
		*mat_traslacion = MAT_Traslacion(0.0, 0.0, v);
		break;
	case 1:
		*mat_mov_brazo1 = MAT_Rotacion(t_sec * 50, 1.0, 0.0, 0.0);
		break; 
	case 2:
		*mat_mov_brazo2 = MAT_Rotacion(t_sec * 50, 1.0, 0.0, 0.0);
		break; 
	case 3:
		*mat_mov_cabeza = MAT_Rotacion(t_sec * 50, 0.0, 1.0, 0.0);
		break;

	}
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

	ponerIdentificador(143047);
	ponerNombre("Tronco Android");
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

	agregar(MAT_Traslacion(0.65, 0.65, 0));

	int i = agregar(MAT_Rotacion(0.0, 1.0, 0.0, 0.0));
	mat_mov_brazo = leerPtrMatriz(i);


	agregar(MAT_Escalado(0.1, -0.1, 0.1));
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

/*
unsigned Brazo::leerNumParametros() const {

	return 1;
}


void Brazo::actualizarEstadoParametro(const unsigned iParam, const float t_sec) {

	assert(iParam < leerNumParametros());

	float v;

	if (iParam == 0) {
		*mat_mov_brazo = MAT_Rotacion(t_sec * 50, 1.0, 0.0, 0.0);
	}
}

*/

Pierna::Pierna()
{
	agregar(MAT_Traslacion(0.2, 0.1, 0));
	agregar(MAT_Escalado(0.1, 0.1, 0.1));
	agregar(new SemiesferaInv());

	agregar(MAT_Escalado(1,3,1));
	CilindroCerrado* c = new CilindroCerrado(50,100);
	c->ponerColor({0.0,1.0,0.0});
	agregar(c);

	ponerNombre("Cuerpo Android");
	ponerIdentificador(143047);
	
	}

Cabeza::Cabeza()
{
	int i = agregar(MAT_Rotacion(0.0, 0.0, 1.0, 0.0));
	mat_mov_cabeza = leerPtrMatriz(i);

	agregar(new Cara());
	agregar(new Ojo());
	agregar(MAT_Escalado(-1, 1, 1));
	agregar(new Ojo());
	agregar(new Oreja());
	agregar(MAT_Escalado(-1, 1, 1));
	agregar(new Oreja());

	ponerNombre("Cabeza Android");
	ponerIdentificador(143047);
}

/*
unsigned Cabeza::leerNumParametros() const {

	return 1;
}


void Cabeza::actualizarEstadoParametro(const unsigned iParam, const float t_sec) {

	assert(iParam < leerNumParametros());

	float v;

	if (iParam == 0) {
		*mat_mov_cabeza = MAT_Rotacion(t_sec * 50, 0.0, 1.0, 0.0);
	}
}
*/