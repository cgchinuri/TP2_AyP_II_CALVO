#include <cmath>

//recibe un jugador, un tablero y las posiciones de una casilla, devuelve el ocupante (nombre provisional), que puede ser un Armamento
//una ficha o su tipo si no tiene ficha o carta, idealmente chequea una sola funcion y recibe menos
string obtenerOcupanteCasilla (TDAJugador jugador,TDAtablero tablero, int x, int y, int z){
   TDACarta armamento=jugador::buscarArmamento(x,y,z);
   TDAFicha ficha=jugador::buscarFicha(x,y,z)
   if (armamento==NULL){
      if (ficha==NULL){
         return tablero::obtenerCasillero(x,y,z)casillero::getTipoCasillero();
      }
      return ficha::getTipoFicha;
   }
 return armamento::GetNombre;
}

//recibe un int/string que le indica lo que ocupa(nombre provisional) la casilla,
//pinta o coloca una imagen  segun que tiene la casilla, todo lo que no son tipos las imagenes voy a posiblemente dibujarlas dsps

void dibujarBloque(int x, int y, int z, string tipoCasilla, image imagen){
   if (tipoCasilla=="tierra" || tipoCasilla=="cielo"){
      
      return
   }
   if (tipoCasilla=="agua"){
      34, 27, 245
      return
   }
   if tipoCasilla=="soldado"{
      imgsoldado
      return
   }
   if tipoCasilla=="mina"{
      imgmina
      return
   }
   if tipoCasilla=="destruida"{
      imgdestruida
      return
   }
   if tipoCasilla==6{
      imgcarta1
      return
   }
}

void graficarPlanoZ(TDAtablero tablero, int z, int tamaño){
  //crea imagen tamañoxtamaño
   bitmap_image image(tamaño,tamaño);
  
   // pone todo los bloques de base en marron(tierra) o celeste (cielo) segun la altura, para ahorrar pintar de ese color
  if z<4{
     //color marron/tierra a todo bajo el nivel 4
      image.set_all_channels(115, 64, 32);
  } else {
     //cielo por defecto a todo sobre el nivel 4
        image.set_all_channels(92, 198, 219);
  }
   for (int y=0,y<tamaño,y++){
      for (int x=0,x<tamaño,x++){
         int tipoCasilla=obtenerOcupanteCasilla(jugador,tablero,x,y,z);
         dibujarbloque(x,y,z, tipoCasilla, image);
      }
   }
}
  


void GraficarTablerodeJugador(TDAJugador jugador){
   
   
          
