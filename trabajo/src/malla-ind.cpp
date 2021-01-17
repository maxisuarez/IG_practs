// Nombre: Maximino, Apellidos: Suarez van Gelderen, DNI/Pasaporte: 44668999D (DDGG IG curso 20-21) 

// *********************************************************************
// **
// ** Informática Gráfica, curso 2020-21
// ** Declaraciones de la clase Objeto3D.hpp
// **
// *********************************************************************



//#include <set>   // std::set
#include "ig-aux.h"
#include "tuplasg.h"
#include "malla-ind.h"   // declaración de 'ContextoVis'
#include "lector-ply.h"


// *****************************************************************************
// funciones auxiliares

// *****************************************************************************
// métodos de la clase MallaInd.

MallaInd::MallaInd()
{
   // nombre por defecto
   ponerNombre("malla indexada, anónima");
   ponerIdentificador( 10046464 );
}
// -----------------------------------------------------------------------------

MallaInd::MallaInd( const std::string & nombreIni )
{
   // 'identificador' puesto a 0 por defecto, 'centro_oc' puesto a (0,0,0)
   ponerNombre(nombreIni) ;
   ponerIdentificador( 10046464 );
}

//-----------------------------------------------------------------------------
// calcula la tabla de normales de triángulos una sola vez, si no estaba calculada

void MallaInd::calcularNormalesTriangulos()
{

   // si ya está creada la tabla de normales de triángulos, no es necesario volver a crearla
   const unsigned nt = triangulos.size() ;
   assert( 1 <= nt );
   if ( 0 < nor_tri.size() )
   {
      assert( nt == nor_tri.size() );
      return ;
   }

   // COMPLETAR: Práctica 4: creación de la tabla de normales de triángulos
   // ....

   Tupla3f a,b,m;
   
   for(int i = 0; i < triangulos.size(); i++){
     a = vertices[triangulos[i][1]]-vertices[triangulos[i][0]];
     b = vertices[triangulos[i][2]]-vertices[triangulos[i][0]];

     m = a.cross(b);

     if( (m[X] != 0) || (m[Y] != 0) || (m[Z] != 0))
       m = m.normalized();

     nor_tri.push_back(m);
   }

}


// -----------------------------------------------------------------------------
// calcula las dos tablas de normales

void MallaInd::calcularNormales()
{
   // COMPLETAR: en la práctica 4: calculo de las normales de la malla
   // se debe invocar en primer lugar 'calcularNormalesTriangulos'
   // .......
     calcularNormalesTriangulos();

   for(int i = 0; i < vertices.size(); i++)
      nor_ver.push_back({0.0,0.0,0.0});

   for(int i = 0; i < triangulos.size(); i++)
      for(int j = 0; j < 3; j++)
         nor_ver[triangulos[i][j]] = nor_ver[triangulos[i][j]]+nor_tri[i];

   for(int i = 0; i < nor_ver.size(); i++)
      if(nor_ver[i][X]!= 0 || nor_ver[i][Y]!= 0 || nor_ver[i][Z]!= 0)
         nor_ver[i]=nor_ver[i].normalized();

}




// ----------------------------------------------------------------------------


void MallaInd::visualizarGL( ContextoVis & cv )
{

   using namespace std ;
   assert( cv.cauce_act != nullptr );


/* INTENTO DE METER NORMALES
   if(cv.visualizando_normales){
      visualizarNormales();
      return;
   }
*/

   if ( triangulos.size() == 0 || vertices.size() == 0 )
   {  cout << "advertencia: intentando dibujar malla vacía '" << leerNombre() << "'" << endl << flush ;
      return ;
   }

   // guardar el color previamente fijado
   const Tupla4f color_previo = leerFijarColVertsCauce( cv );

   // COMPLETAR: práctica 1: si el puntero 'array_verts' es nulo, crear el objeto ArrayVerts
   //   * en el constructor se dan los datos de la tabla de coordenadas de vértices (tabla 'vertices')
   //   * después hay que invocar a 'fijarIndices', usando el formato y datos de la tabla de triángulos ('triangulos')
   //   * si las tablas 'col_ver', 'cc_tt_ver' o 'nor_ver' no están vacías, hay que invocar los métodos
   //     'fijarColores', 'fijarCoordText' y 'fijarNormales', como corresponda.
   if(array_verts == nullptr){
     array_verts = new ArrayVertices(GL_FLOAT,3,(const GLsizei) vertices.size(),( const GLvoid *) vertices[0]);

     //fijamos los indices

     array_verts->fijarIndices(GL_UNSIGNED_INT, (const GLsizei ) triangulos.size()*3, ( const GLvoid *) triangulos[0] );
  }

   if ( col_ver.size()!=0){
     array_verts->fijarColores(GL_FLOAT, 3,( const GLvoid *) col_ver[0]);
  }

  if ( cc_tt_ver.size()!=0 ){
     array_verts->fijarCoordText(GL_FLOAT, 2,( const GLvoid *) cc_tt_ver[0]);
  }
  if ( nor_ver.size()!=0 ){
     array_verts->fijarNormales(GL_FLOAT, ( const GLvoid *) nor_ver[0]);
  }



  // COMPLETAR: práctica 1: visualizar según el modo (en 'cv.modo_envio')
  //   ** inmediato begin/end       : usar método 'visualizarGL_MI_BVE' de 'ArrayVerts'
  //   ** inmediato con una llamada : usar método 'visualizarGL_MI_DAE' de 'ArrayVerts'
  //   ** diferido (con un VAO)     : usar método 'visualizarGL_MD_VAO' de 'ArrayVerts'
  // (en cualquier caso hay que pasar como parámetro el tipo de primitiva adecuada a una malla de triángulos).
  // .....
  if (cv.modo_envio == ModosEnvio::inmediato_begin_end)
     array_verts->visualizarGL_MI_BVE(GL_TRIANGLES);
  else if (cv.modo_envio == ModosEnvio::diferido_vao)
     array_verts->visualizarGL_MD_VAO(GL_TRIANGLES);
  else if (cv.modo_envio == ModosEnvio::inmediato_drawelements)
     array_verts->visualizarGL_MI_DAE(GL_TRIANGLES);


  // restaurar el color previamente fijado
  glColor4fv( color_previo );
}






// *****************************************************************************


// ****************************************************************************
// Clase 'MallaPLY'

MallaPLY::MallaPLY( const std::string & nombre_arch )
{
   ponerNombre( std::string("malla leída del archivo '") + nombre_arch + "'" );

   // COMPLETAR: práctica 2: leer archivo PLY e inicializar la malla
   // ..........................
   LeerPLY(nombre_arch, vertices, triangulos);

   // COMPLETAR: práctica 4: invocar  a 'calcularNormales' para el cálculo de normales
   // .................

   calcularNormales();


}

// ****************************************************************************
// Clase 'Cubo

Cubo::Cubo()
:  MallaInd( "cubo 8 vértices" )
{

   vertices =
      {  { -1.0, -1.0, -1.0 }, // 0
         { -1.0, -1.0, +1.0 }, // 1
         { -1.0, +1.0, -1.0 }, // 2
         { -1.0, +1.0, +1.0 }, // 3
         { +1.0, -1.0, -1.0 }, // 4
         { +1.0, -1.0, +1.0 }, // 5
         { +1.0, +1.0, -1.0 }, // 6
         { +1.0, +1.0, +1.0 }, // 7
      } ;



   triangulos =
      {  {0,1,3}, {0,3,2}, // X-
         {4,7,5}, {4,6,7}, // X+ (+4)

         {0,5,1}, {0,4,5}, // Y-
         {2,3,7}, {2,7,6}, // Y+ (+2)

         {0,6,4}, {0,2,6}, // Z-
         {1,5,7}, {1,7,3}  // Z+ (+1)
      } ;

   calcularNormales();

   ponerIdentificador( 10046464 );
}

Tetaedro::Tetaedro()
    : MallaInd("tetaedro")
{
    vertices =
    {
        { 0, 0, 0 }, // 0
        { +1.0, 0, 0 }, // 1
        { 0, +1.0, 0 }, // 2
        { 0, 0, +1.0 }, // 3
    };

    triangulos =
    {
        { 0, 1, 2 },
        { 0, 1, 3 },
        { 0, 2, 3},
        { 1, 2, 3},
    };

    ponerColor({ 0.15, 0.15, 0.30 });

   calcularNormales();


}

CuboColores::CuboColores()
    : MallaInd("cubo 8 vértices con colores")
{

    vertices =
    { { -1.0, -1.0, -1.0 }, // 0
       { -1.0, -1.0, +1.0 }, // 1
       { -1.0, +1.0, -1.0 }, // 2
       { -1.0, +1.0, +1.0 }, // 3
       { +1.0, -1.0, -1.0 }, // 4
       { +1.0, -1.0, +1.0 }, // 5
       { +1.0, +1.0, -1.0 }, // 6
       { +1.0, +1.0, +1.0 }, // 7
    };



    triangulos =
    { {0,1,3}, {0,3,2}, // X-
       {4,7,5}, {4,6,7}, // X+ (+4)

       {0,5,1}, {0,4,5}, // Y-
       {2,3,7}, {2,7,6}, // Y+ (+2)

       {0,6,4}, {0,2,6}, // Z-
       {1,5,7}, {1,7,3}  // Z+ (+1)
    };

    for (int i = 0; i < vertices.size(); i++) {
        Tupla3f aux(vertices[i](0) * 0.5 + 0.5, vertices[i](1) * 0.5 + 0.5, vertices[i](2) * 0.5 + 0.5);
        col_ver.push_back(aux);
    }

    calcularNormales();
}


Cubo24::Cubo24() : MallaInd("Cubo de 24 vértices")
{
  vertices =
      {  { -1.0, -1.0, -1.0 }, // 0
         { -1.0, -1.0, +1.0 }, // 1
         { -1.0, +1.0, -1.0 }, // 2
         { -1.0, +1.0, +1.0 }, // 3
         { +1.0, -1.0, -1.0 }, // 4
         { +1.0, -1.0, +1.0 }, // 5
         { +1.0, +1.0, -1.0 }, // 6
         { +1.0, +1.0, +1.0 }, // 7

	       { -1.0, -1.0, -1.0 }, // 0 +8
         { -1.0, -1.0, +1.0 }, // 1 +8
         { -1.0, +1.0, -1.0 }, // 2 +8
         { -1.0, +1.0, +1.0 }, // 3 +8
         { +1.0, -1.0, -1.0 }, // 4 +8
         { +1.0, -1.0, +1.0 }, // 5 +8
         { +1.0, +1.0, -1.0 }, // 6 +8
         { +1.0, +1.0, +1.0 }, // 7 +8

	      { -1.0, -1.0, -1.0 }, // 0 +16
         { -1.0, -1.0, +1.0 }, // 1 +16
         { -1.0, +1.0, -1.0 }, // 2 +16 
         { -1.0, +1.0, +1.0 }, // 3 +16
         { +1.0, -1.0, -1.0 }, // 4 +16
         { +1.0, -1.0, +1.0 }, // 5 +16
         { +1.0, +1.0, -1.0 }, // 6 +16
         { +1.0, +1.0, +1.0 } // 7 +16
      } ;


   triangulos =
      {  {0,1,3}, {0,3,2}, // X-
         {4,7,5}, {4,6,7}, // X+ (+4)
         {8,13,9}, {8,12,13}, // Y-
         {10,11,15}, {10,15,14}, // Y+ (+2)
         {16,22,20}, {16,18,22}, // Z-
         {17,21,23}, {17,23,19}  // Z+ (+1)
      } ;

   cc_tt_ver=
     {{0,1}, // 0
      {1,1}, // 1
      {0,0}, // 2
      {1,0}, // 3
      {1,1}, // 4
      {0,1}, // 5
      {1,0}, // 6
      {0,0}, // 7

      {0,0}, // 0 +8
      {1,0}, // 1 +8
      {1,0}, // 2 +8
      {0,0}, // 3 +8
      {0,1}, // 4 +8
      {1,1}, // 5 +8
      {1,1}, // 6 +8
      {0,1}, // 7 +8

      {1,1}, // 0 +16
      {0,1}, // 1 +16
      {1,0}, // 2 +16 
      {0,0}, // 3 +16
      {0,1}, // 4 +16
      {1,1}, // 5 +16
      {0,0}, // 6 +16
      {1,0} // 7 +16
     };

   calcularNormales();
};

NodoCubo :: NodoCubo(){
   Textura * tex = new Textura("../recursos/imgs/window-icon.jpg");
   agregar( new Material(tex, 0.5, 0.4, 0.4, 50) );

   agregar(new Cubo24());

   ponerNombre("Cubo 24 vertices");
}

void MallaInd::visualizarNormales()
{
   using namespace std ;

   if ( nor_ver.size() == 0 )
   {
      cout << "Advertencia: intentando dibujar normales de una malla que no tiene tabla (" << leerNombre() << ")." << endl ;
      return ;
   }  
   if ( array_verts_normales == nullptr )
   {  
      for( unsigned i = 0 ; i < vertices.size() ; i++ )
      {  
         segmentos_normales.push_back( vertices[i] );
         segmentos_normales.push_back( vertices[i]+ 0.35f*(nor_ver[i]) );
      }
      array_verts_normales = new ArrayVertices( GL_FLOAT, 3, segmentos_normales.size(), segmentos_normales.data() );
   }

   array_verts_normales->visualizarGL_MI_DAE( GL_LINES );
   CError();
}

// -----------------------------------------------------------------------------------------------
