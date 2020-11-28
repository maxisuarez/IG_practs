// Nombre: Maximino, Apellidos: Suarez van Gelderen, DNI/Pasaporte: 44668999D (DDGG IG curso 20-21) 

#ifndef MODELO_JER_HPP
#define MODELO_JER_HPP


#include "matrices-tr.h"
#include "objeto3d.h"
#include "grafo-escena.h"
#include "malla-revol.h"

class C :  public NodoGrafoEscena
{ 
private:
    //param 0
    Matriz4f* mat_traslacion;
    Matriz4f* mat_mov_brazo1;
    Matriz4f* mat_mov_brazo2;
    Matriz4f* mat_mov_cabeza;


public:
    C();

    void actualizarEstadoParametro(const unsigned iParam, const float t_sec);

    unsigned leerNumParametros() const;

};


class Ojo : public NodoGrafoEscena
{ public:
    Ojo();
};

class Oreja : public NodoGrafoEscena
{ public:
    Oreja();
};

class Cara : public NodoGrafoEscena
{ public:
    Cara();
};

class Cuello : public NodoGrafoEscena
{ public:
    Cuello();
};

class Brazo : public NodoGrafoEscena
{
    private:
    
    public:
        Brazo();
        Matriz4f* mat_mov_brazo;

        /*
        void actualizarEstadoParametro(const unsigned iParam, const float t_sec);

        unsigned leerNumParametros() const;*/
};

class SemiesferaInv : public NodoGrafoEscena
{ public:
    SemiesferaInv();
};

class Tronco : public NodoGrafoEscena
{ public:
    Tronco();
};

class Pierna : public NodoGrafoEscena
{ public:
    Pierna();
};

class Cabeza : public NodoGrafoEscena
{
    private:
     
    public:
        Cabeza();
        Matriz4f* mat_mov_cabeza;

        /*
        void actualizarEstadoParametro(const unsigned iParam, const float t_sec);

        unsigned leerNumParametros() const;*/
};

#endif