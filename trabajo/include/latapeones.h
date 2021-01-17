// Nombre: Maximino, Apellidos: Suarez van Gelderen, DNI/Pasaporte: 44668999D (DDGG IG curso 20-21) 

#ifndef LATA_PEONES_HPP
#define LATA_PEONES_HPP


#include <string>
#include "matrices-tr.h"
#include "objeto3d.h"
#include "grafo-escena.h"
#include "malla-revol.h"


class LataPeones: public NodoGrafoEscena
{

public:

  LataPeones(const std::string & tex, std::string nombre, int id);
};

class Lata: public NodoGrafoEscena
{

public:

  Lata(const std::string & tex, std::string nombre, int id);
};


class LataSuperior: public NodoGrafoEscena{
  public:
    LataSuperior();
};

class LataInferior: public NodoGrafoEscena{
  public:
    LataInferior();
};


class LataCentral: public NodoGrafoEscena{
  public:
    LataCentral(const std::string & fichero);
};


class PeonMadera: public NodoGrafoEscena{
  public:
    PeonMadera();
};

class PeonBlanco: public NodoGrafoEscena{
  public:
    PeonBlanco();
};

class PeonNegro: public NodoGrafoEscena{
  public:
    PeonNegro();
};

class VariasLatasPeones: public NodoGrafoEscena{
  public:
    VariasLatasPeones();
};


#endif // LATA_PEONES_HPP