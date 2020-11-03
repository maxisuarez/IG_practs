#ifndef MODELO_JER_HPP
#define MODELO_JER_HPP


#include "matrices-tr.h"
#include "objeto3d.h"
#include "grafo-escena.h"
#include "malla-revol.h"

class C :  public NodoGrafoEscena
{ public:
    C();
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
{ public:
    Brazo();
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

#endif