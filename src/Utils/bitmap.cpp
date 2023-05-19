

enum obtenerTipoCasilla (TDAtablero tablero, int x, int y, int z){
   return tablero::obtenerCasillero(x,y,z)::getTipoCasillero();
}

void graficarPlanoZ(TDAtablero tablero, int z, int tamaño){
  //crea imagen tamañoxtamaño
   bitmap_image image(tamaño,tamaño);
  
   // pone todo los bloques de base en marron(tierra) o celeste (cielo) segun la altura
  if z<4{
      image.set_all_channels(115, 64, 32);
  } else {
        image.set_all_channels(115, 64, 32);

  for int y=0,y<tamaño,y++{
    
