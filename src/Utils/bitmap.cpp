#include <cmath>

//recibe un tablero y posicioens de una casilla y devuelve su tipo
int obtenerTipoCasilla (TDAtablero tablero, int x, int y, int z){
   
   return tablero::obtenerCasillero(x,y,z)casillero::getTipoCasillero();
}

void dibujarBloque(int x, int y, int z, int tipoCasilla, image imagen){
   if tipoCasilla==0{
      115, 64, 32
      return
   }
   if tipoCasilla==1{
      34, 27, 245
      return
   }
   if tipoCasilla==2{
      92, 198, 219
      return
   }
   if tipoCasilla==3{
      
      return
   }
   if tipoCasilla==4{
      
      return
   }
   if tipoCasilla==5{
      
      return
   }
   if tipoCasilla==6{
      
      return
   }
   

void graficarPlanoZ(TDAtablero tablero, int z, int tamaño){
  //crea imagen tamañoxtamaño
   bitmap_image image(tamaño,tamaño);
  
   // pone todo los bloques de base en marron(tierra) o celeste (cielo) segun la altura
  if z<4{
     
      image.set_all_channels(115, 64, 32);
  } else {
        image.set_all_channels(92, 198, 219);
  }
   for int y=0,y<tamaño,y++{
      for int x=0,x<tamaño,x++{
         int tipoCasilla=obtenerTipoCasilla(tablero,x,y,z);
         dibujarbloque(x,y,z, tipoCasilla, image);
      }
   }
}
  
          
