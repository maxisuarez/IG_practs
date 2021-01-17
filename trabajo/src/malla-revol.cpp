// Nombre: Maximino, Apellidos: Suarez van Gelderen, DNI/Pasaporte: 44668999D (DDGG IG curso 20-21) 

// *********************************************************************
// **
// ** Informática Gráfica, curso 2019-20
// ** Implementación de la clase 'MallaRevol'
// **
// *********************************************************************

#include "ig-aux.h"
#include "tuplasg.h"
#include "lector-ply.h"
#include "matrices-tr.h"
#include "malla-revol.h"

using namespace std ;

// *****************************************************************************

// Método que crea las tablas de vértices, triángulos, normales y cc.de.tt.
// a partir de un perfil y el número de copias que queremos de dicho perfil.
void MallaRevol::inicializar
(
   const std::vector<Tupla3f> & perfil,     // tabla de vértices del perfil original
   const unsigned               num_copias  // número de copias del perfil
)
{

	std::vector<Tupla3f> normalesAristas, vertsAux;
   Tupla3f normal, aux;
   for(unsigned i = 0; i<perfil.size()-1; i++){

      aux = (perfil[i+1]-perfil[i]);
      normal(0)=aux(1);
      normal(1)=-aux(0);
      normal(2)=0;
      if(normal.lengthSq()>0)
         normalesAristas.push_back(normal.normalized());
      else
         normalesAristas.push_back(normal);
      
   }

   nor_ver.insert(nor_ver.begin(), perfil.size(), {0.0, 0.0 , 0.0});
   if(normalesAristas[0].lengthSq()!=0)
      nor_ver[0]=normalesAristas[0].normalized();
   
   for(unsigned i=1; i<perfil.size()-1; i++){
      nor_ver[i]=normalesAristas[i]+normalesAristas[i-1];
      if(nor_ver[i].lengthSq()!=0)
         nor_ver[i]=nor_ver[i].normalized();
   }

   if(normalesAristas[perfil.size()-2].lengthSq()!=0)
      nor_ver[perfil.size()-1]=normalesAristas[perfil.size()-2];


   // Calcular Coordenadas de textura

   std::vector<float> d, t;
   float den=0;
   for(unsigned int i = 0; i<perfil.size()-1; i++){
      d.push_back(sqrt((perfil[i+1]-perfil[i]).lengthSq()));
      den += d[i];
   }
   t.push_back(0);
   for(unsigned int i = 1; i<perfil.size(); i++)
      t.push_back(t[i-1]+d[i-1]/den);
   
   // COMPLETAR: Práctica 2: completar: creación de la malla....
   const int m = perfil.size();
   int k;
   Tupla3f q;
   Matriz4f rot;
   Tupla2f textura;
   float t_x, t_y;
   
   for (unsigned i = 0; i < num_copias; i++){
      rot = MAT_Rotacion((360.0*i)/(num_copias-1), 0.0, 1.0, 0.0);
      for (int j = 0; j < m; j++){
         q = rot * perfil[j];
         nor_ver.push_back(rot*nor_ver[j]);
         t_x = (float)i/(num_copias-1);
         t_y = 1.0-t[j];
         textura = {t_x, t_y};
         vertices.push_back(q);
         cc_tt_ver.push_back(textura);
      }
   }

   for (unsigned i = 0; i < num_copias-1; i++){
      for (int j = 0; j < m-1; j++){
         k = i*m+j;
         triangulos.push_back({k, k+m, k+m+1});
         triangulos.push_back({k, k+m+1, k+1});
      }
   }
/*	int m = perfil.size();
	 // Cálculo normales de los vértices
	 vector<Tupla3f> nor_arist;
	Tupla3f aux;
	
	for(int j = 0; j < m-1; j++){
		aux = perfil[j+1]-perfil[j];
		aux={aux[Y],-aux[X],0.0};

		if(aux[X]!=0 || aux[Y]!=0 || aux[Z]!=0)
		aux = aux.normalized();
		
		nor_arist.push_back(aux);
	}

	vector<Tupla3f> nor_ver_perfil;
	
	nor_ver_perfil.push_back(nor_arist.front());
	
	
	for(int j = 1; j < m-1; j++){
		aux = nor_arist[j-1]+nor_arist[j];

		if(aux[X]!=0 || aux[Y]!=0 || aux[Z]!=0)
		aux = aux.normalized();
		
		nor_ver_perfil.push_back(aux);
	}
	
	nor_ver_perfil.push_back(nor_arist.back());

	//texturas
	vector<float> d;

	for(int j = 0; j < m-1; j++)
	d.push_back(sqrt(pow(perfil[j][X]-perfil[j+1][X],2.0)+pow(perfil[j][Y]-perfil[j+1][Y],2.0)));

	vector<float> t;

	float suma = 0;
	float total = 0;

	for(int j = 0; j < m-1; j++)
	total+=d[j];

	for(int j = 0; j < m-1; j++){
	t.push_back(suma/total);
	suma += d[j];
	}
	t.push_back(1.0);
	
   // COMPLETAR: Práctica 2: completar: creación de la malla....

	for (int i = 0; i < num_copias; i++) {
		for (int j = 0; j < m; j++) {
			float alpha = 2 * M_PI * i / (num_copias - 1);
			float c = cos(alpha);
			float s = sin(alpha);
			vertices.push_back({ perfil[j][X]*c, perfil[j][Y], perfil[j][X]*s });
		 }
	 }

	for (int i = 0; i < num_copias - 1; i++) {
		for (int j = 0; j < m - 1; j++) {
			int k = i * m + j;
			triangulos.push_back({ k, k + m, k + m + 1 });
			triangulos.push_back({ k, k + m + 1, k + 1 });
		}
	}*/


}

// -----------------------------------------------------------------------------
// constructor, a partir de un archivo PLY

MallaRevolPLY::MallaRevolPLY
(
   const std::string & nombre_arch,
   const unsigned      nperfiles
)
{
   ponerNombre( std::string("malla por revolución del perfil en '"+ nombre_arch + "'" ));
   // COMPLETAR: práctica 2: crear la malla de revolución
   // Leer los vértice del perfil desde un PLY, después llamar a 'inicializar'
   // ...........................
   std::vector<Tupla3f> perfil;
   LeerVerticesPLY(nombre_arch, perfil);
   inicializar(perfil, nperfiles);

}

Cilindro::Cilindro(const int num_verts_per, const unsigned nperfiles)
{
	ponerNombre("Cilindro");
	std::vector<Tupla3f> perfil;
	for (int i = 0; i < num_verts_per; i++)
		perfil.push_back({ 1, float(i / (num_verts_per - 1)), 0 });

	inicializar(perfil, nperfiles);
}

Cono::Cono(const int num_verts_per, const unsigned nperfiles)
{
	ponerNombre("Esfera");
	std::vector<Tupla3f> perfil;
	for (int i = 0; i < num_verts_per; i++)
		perfil.push_back({ float(1-i/(num_verts_per-1)),  float(i / (num_verts_per - 1)), 0 });

	inicializar(perfil, nperfiles);
}

Esfera::Esfera(const int num_verts_per, const unsigned nperfiles)
{

  ponerNombre("Esfera");

  std::vector<Tupla3f> perfil;

  for(int i = 0; i < num_verts_per; i++){
    float alpha = M_PI*((float)i/(num_verts_per-1)-(float)1/2);
    perfil.push_back({cos(alpha),sin(alpha),0});
  }
  
  inicializar(perfil, nperfiles);
   /*
	ponerNombre("Esfera");
	std::vector<Tupla3f> perfil;
	for (int i = 0; i < num_verts_per; i++) {
		float alpha = 2 * M_PI * i / (num_verts_per - 1);
		perfil.push_back({ cos(alpha),  sin(alpha), 0 });
	}

	inicializar(perfil, nperfiles);*/
}

Semiesfera::Semiesfera(const int num_verts_per, const unsigned nperfiles)
{
	ponerNombre("Semi-Esfera");
	std::vector<Tupla3f> perfil;
	for (int i = 0; i < num_verts_per; i++) {
		float alpha = M_PI*((float)i/(num_verts_per-1)-(float)1/2);
		perfil.push_back({ cos(alpha),  abs(sin(alpha)), 0 });
	}
	inicializar(perfil, nperfiles);
}


CilindroCerrado::CilindroCerrado(const int num_verts_per,
				 const unsigned nperfiles){
    
  std::vector<Tupla3f> perfil; 
  perfil.push_back({0.0,0.0,0.0}); 
  perfil.push_back({1.0,0.0,0.0});
  
  for(int i = 0; i < num_verts_per; i++)
    perfil.push_back({1.0,float(i/(num_verts_per-1)),0.0});

  perfil.push_back({1.0,1.0,0.0});
  perfil.push_back({0.0,1.0,0.0});
  inicializar(perfil, nperfiles);
}






