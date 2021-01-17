// Nombre: Maximino, Apellidos: Suarez van Gelderen, DNI/Pasaporte: 44668999D (DDGG IG curso 20-21) 

#include <math.h>
#include "ig-aux.h"
#include "matrices-tr.h"
#include "grafo-escena.h"
#include "malla-revol.h"
#include "materiales-luces.h"
#include "latapeones.h"

using namespace std;

LataPeones::LataPeones(const std::string & tex, std::string nombre, int id){
  agregar(new Lata(tex, nombre, id));
  agregar(new PeonMadera());
  agregar(new PeonBlanco());
  agregar(new PeonNegro());

  ponerNombre("Lata y Peones");

}


Lata::Lata(const std::string & tex, std::string nombre, int id){
  ponerIdentificador(id);
  ponerNombre(nombre);
  agregar(MAT_Escalado(1.5, 1.5, 1.5));
  agregar(new LataSuperior());
  agregar(new LataInferior());
  agregar(new LataCentral(tex));

}

LataSuperior::LataSuperior(){

  agregar(new Material(0.5,0.5,0.9,20.0));
  agregar(new  MallaRevolPLY("../recursos/plys/lata-psup.ply",30));

  ponerNombre("Lata parte superior");
}

LataInferior::LataInferior(){
  agregar(new Material(0.5,0.5,0.9,20.0));
  agregar(new  MallaRevolPLY("../recursos/plys/lata-pinf.ply",30));

  ponerNombre("Lata parte inferior");
}

LataCentral::LataCentral(const std::string & fichero){
  Textura * tex = new Textura(fichero);
  agregar( new Material(tex, 0.2, 0.4, 0.4, 20) );
  agregar(new  MallaRevolPLY("../recursos/plys/lata-pcue.ply",30));

  ponerNombre("Lata parte central");
}

PeonMadera::PeonMadera(){

  Textura * tex = new Textura("../recursos/imgs/text-madera.jpg");
  agregar(MAT_Traslacion(0.15, 0.3, 1.0));
  agregar(MAT_Escalado(0.3, 0.3, 0.3));
  agregar(new Material(tex, 0.2, 0.4, 0.4, 20));
  agregar(new MallaRevolPLY("../recursos/plys/peon.ply", 30));

  ponerIdentificador( 10046464 );
  ponerNombre("Peon de Madera");
}

PeonBlanco::PeonBlanco(){

  ponerColor({1.0,1.0,1.0});
  agregar(MAT_Traslacion(0.8, 0.3, 1.0));
  agregar(MAT_Escalado(0.3, 0.3, 0.3));
  agregar(new Material(0.1, 0.8, 0.1, 20));
  agregar(new MallaRevolPLY("../recursos/plys/peon.ply", 30));

  ponerIdentificador( 13369446 );
  ponerNombre("Peon blanco");
}

PeonNegro::PeonNegro(){
  ponerColor({0.0,0.0,0.0});
  agregar(MAT_Traslacion(1.5, 0.3, 1.0));
  agregar(MAT_Escalado(0.3, 0.3, 0.3));
  agregar(new Material(0.1, 0.1, 0.8, 20));
  agregar(new MallaRevolPLY("../recursos/plys/peon.ply", 30));

  ponerIdentificador( 65535 );
  ponerNombre("Peon blanco");
}

VariasLatasPeones::VariasLatasPeones(){
  
  agregar(new LataPeones("../recursos/imgs/lata-coke.jpg", "Lata Coca-Cola", 16711680  ));

  agregar(MAT_Traslacion(1.0, 0.0, 0.0));

  agregar(new Lata("../recursos/imgs/lata-pepsi.jpg", "Lata Pepsi",  255 ));

  agregar(MAT_Traslacion(1.0, 0.0, 0.0));
  agregar(new Lata("../recursos/imgs/window-icon.jpg", "Lata UGR", 8421504 ));

  ponerNombre("Varias Latas y Peones");
}



