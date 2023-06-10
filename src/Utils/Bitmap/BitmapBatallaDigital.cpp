#include <string>
#include "BitmapBatallaDigital.h"
#include "EasyBMP_1.06/EasyBMP.h"
#include "EasyBMP_1.06/EasyBMP_Font.h"

#include "../../Tablero/tablero.h"
#include "../../Ficha/Ficha.h"

BitmapBatallaDigital::BitmapBatallaDigital(unsigned int resolucionImagenes, RGBApixel colorTransparente, unsigned int anchoTablero, unsigned int altoTablero) {
    //SetEasyBMPwarningsOff(); //APAGA ADVERTENCIAS RELACIONADAS A LAS IMAGENES BMP

    this->resolucionImagenes = resolucionImagenes;
    this->colorTransparente = colorTransparente;

    this->imagenTablero.SetSize(anchoTablero * resolucionImagenes, altoTablero * resolucionImagenes);

    this->imagenPasto.ReadFromFile("Utils/Bitmap/bitmaps/pasto.bmp");
    this->imagenTierra.ReadFromFile("Utils/Bitmap/bitmaps/tierra.bmp");
    this->imagenAgua.ReadFromFile("Utils/Bitmap/bitmaps/agua.bmp");
    this->imagenAguaProfunda.ReadFromFile("Utils/Bitmap/bitmaps/aguaProfunda.bmp");
    this->imagenAire.ReadFromFile("Utils/Bitmap/bitmaps/aire.bmp");
    this->imagenSoldadoJugador.ReadFromFile("Utils/Bitmap/bitmaps/soldadoJugador.bmp");
    this->imagenSoldadoEnemigo.ReadFromFile("Utils/Bitmap/bitmaps/soldadoEnemigo.bmp");
    this->imagenQuimicos.ReadFromFile("Utils/Bitmap/bitmaps/quimicos.bmp");
    this->imagenMinaJugador.ReadFromFile("Utils/Bitmap/bitmaps/minaJugador.bmp");
    this->imagenMinaEnemigo.ReadFromFile("Utils/Bitmap/bitmaps/minaEnemigo.bmp");
    this->imagenAvionJugador.ReadFromFile("Utils/Bitmap/bitmaps/avionJugador.bmp");
    this->imagenAvionEnemigo.ReadFromFile("Utils/Bitmap/bitmaps/avionEnemigo.bmp");
    this->imagenBarcoJugador.ReadFromFile("Utils/Bitmap/bitmaps/barcoJugador.bmp");
    this->imagenBarcoEnemigo.ReadFromFile("Utils/Bitmap/bitmaps/barcoEnemigo.bmp");
    this->imagenSubmarinoJugador.ReadFromFile("Utils/Bitmap/bitmaps/submarinoJugador.bmp");
    this->imagenSubmarinoEnemigo.ReadFromFile("Utils/Bitmap/bitmaps/submarinoEnemigo.bmp");
    this->imagenError.ReadFromFile("Utils/Bitmap/bitmaps/error.bmp");
}

void BitmapBatallaDigital::dibujar(unsigned int x, unsigned int y, BMP &elemento, unsigned int altoTablero)
{   
    unsigned int moverX = x * this->resolucionImagenes;
    unsigned int moverY = this->resolucionImagenes * (altoTablero - 1 - y);
    for (size_t i = 0; i < this->resolucionImagenes; i++) {
        for (size_t j = 0; j < this->resolucionImagenes; j++) {
            PixelToPixelCopy(elemento, i, j, this->imagenTablero, i + moverX, j + moverY);
        }     
    }
}

void BitmapBatallaDigital::dibujarTransparente(unsigned int x, unsigned int y, BMP &elemento, unsigned int altoTablero)
{   
    unsigned int moverX = x * this->resolucionImagenes;
    unsigned int moverY = this->resolucionImagenes * (altoTablero - 1 - y);
    for (size_t i = 0; i < this->resolucionImagenes; i++) {
        for (size_t j = 0; j < this->resolucionImagenes; j++) {
            PixelToPixelCopyTransparent(elemento, i, j, this->imagenTablero, i + moverX, j + moverY, this->colorTransparente);
        }     
    }
}

void BitmapBatallaDigital::dibujarInactivo(unsigned int x, unsigned int y, BMP &elemento, unsigned int altoTablero) {
    BMP elementoEscalaGrises = elemento;
    for( int j=0 ; j < elementoEscalaGrises.TellHeight() ; j++)
    {
        for( int i=0 ; i < elementoEscalaGrises.TellWidth() ; i++)
        {
            int Temp = (int) floor( 0.299*elementoEscalaGrises(i,j)->Red + 0.587*elementoEscalaGrises(i,j)->Green + 0.114*elementoEscalaGrises(i,j)->Blue );
            ebmpBYTE TempBYTE = (ebmpBYTE) Temp;
            elementoEscalaGrises(i,j)->Red = TempBYTE;
            elementoEscalaGrises(i,j)->Green = TempBYTE;
            elementoEscalaGrises(i,j)->Blue = TempBYTE;
        }
    }

    dibujar(x, y, elementoEscalaGrises, altoTablero);
}

void BitmapBatallaDigital::dibujarCoordenadas(RGBApixel colorLetra, unsigned int altoTablero) {
    unsigned int altoLetra = (this->resolucionImagenes)/3;
    char numero[3];
    for (size_t i = 0; i < altoTablero; i++)
    {
        sprintf(numero, "%ld", i + 1);
        PrintString(this->imagenTablero, numero, i * this->resolucionImagenes + this->resolucionImagenes/2, this->resolucionImagenes * altoTablero - altoLetra, altoLetra, colorLetra);
        PrintLetter(this->imagenTablero, 'A' + i, 0, (altoTablero - i - 1) * this->resolucionImagenes, altoLetra, colorLetra);
    }
}

void BitmapBatallaDigital::dibujarCasillero(Casillero *casillero, unsigned int altoTablero) {
    unsigned int posX = casillero->getCoordenada()->obtenerX() - 1;
    unsigned int posY = casillero->getCoordenada()->obtenerY() - 1;
    unsigned int posZ = casillero->getCoordenada()->obtenerZ();
    BMP elemento;

    switch (casillero->getTipoCasillero())
    {
    case tierra:
        if(posZ < NIVEL_MAXIMO_TIERRA) {
            elemento = this->imagenTierra;
        }
        else {
            elemento = this->imagenPasto;
        }
        break;
    case agua:
        if(posZ < NIVEL_MAXIMO_TIERRA) {
            elemento = this->imagenAguaProfunda;
        }
        else {
            elemento = this->imagenAgua;
        }
        break;
    case aire:
        elemento = this->imagenAire;
        break;
    default:
        elemento = this->imagenError; // PARA DEBUG
        break;
    }

    if(!casillero->estaActivo())  {
        dibujarInactivo(posX, posY, elemento, altoTablero);
    }

    else {
        dibujar(posX, posY, this->imagenPasto, altoTablero);
    }

    if (!casillero->estaOcupado()) return;
    switch (casillero->getFichaCasillero()->obtenerTipo())
    {
    case FICHA_BARCO:
        dibujarTransparente(posX, posY, this->imagenBarcoJugador, altoTablero);
        break;
    case FICHA_SOLDADO:
        dibujarTransparente(posX, posY, this->imagenSoldadoJugador, altoTablero);
        break;
    case FICHA_AVION:
        dibujarTransparente(posX, posY, this->imagenAvionJugador, altoTablero);
        break;
    case FICHA_MINA:
        dibujarTransparente(posX, posY, this->imagenMinaJugador, altoTablero);
        break;

    default:
        dibujar(posX, posY, this->imagenError, altoTablero); // PARA DEBUG
        break;
    }
}

void BitmapBatallaDigital::dibujarCapa(Tablero *tablero, unsigned int nivelZ) {
    unsigned int anchoTablero = tablero->getDimX();
    unsigned int altoTablero = tablero->getDimY();

    Casillero *casillero = NULL;
    for(unsigned int y = 1 ; y <= altoTablero ; y++) {
        for(unsigned int x = 1 ; x <= anchoTablero ; x++) {
            casillero = tablero->obtenerCasillero(x, y, nivelZ);
            if (casillero == NULL) {
                imagenTablero.WriteToFile("ERROR");
                throw "Error al obtener casillero";
            }
            dibujarCasillero(casillero, altoTablero);
        }
    }

    RGBApixel colorLetra;
    if (nivelZ < NIVEL_MAXIMO_TIERRA) { // SUBTERRANEO - AZUL
        colorLetra.Red = 38;
        colorLetra.Green = 38;
        colorLetra.Blue = 240;
    }

    else if (nivelZ > NIVEL_MAXIMO_TIERRA) { // AEREO - VERDE
        colorLetra.Red = 20;
        colorLetra.Green = 224;
        colorLetra.Blue = 92;
    }

    else { // Nivel Tierra
        colorLetra.Red = colorLetra.Blue = colorLetra.Green = 255; // BLANCO
    }

    dibujarCoordenadas(colorLetra, altoTablero);

    // ESTO ESCIBRE EL NOMBRE DE LA CAPA
    char ruta[20] = "tableroNivel";
    char numero[4];
    sprintf(numero, "%d", nivelZ);
    strcat(ruta, numero);
    strcat(ruta, ".bmp");
    this->imagenTablero.WriteToFile(ruta);
}

void BitmapBatallaDigital::dibujarTablero(Tablero *tablero) {
    unsigned int profundidadTablero = tablero->getDimZ();

    for(unsigned int z = 1 ; z <= profundidadTablero ; z++) {
        dibujarCapa(tablero, z);
    }   
}

BitmapBatallaDigital::~BitmapBatallaDigital() {}
