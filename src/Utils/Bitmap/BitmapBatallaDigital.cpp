#include <sstream>
#include "BitmapBatallaDigital.h"
#include "EasyBMP_1.06/EasyBMP.h"
#include "EasyBMP_1.06/EasyBMP_Font.h"

#include "../../Jugador/Jugador.h"
#include "../../Tablero/tablero.h"
#include "../../Ficha/Ficha.h"

#define RESOLUCION 50

BitmapBatallaDigital::BitmapBatallaDigital(unsigned int anchoTablero, unsigned int altoTablero) {
    SetEasyBMPwarningsOff(); //APAGA ADVERTENCIAS RELACIONADAS A LAS IMAGENES BMP

    this->resolucionImagenes = RESOLUCION;
    RGBApixel transparente;
	transparente.Red = transparente.Blue = transparente.Green = 0; // Negro
    this->colorTransparente = transparente;

    this->imagenTablero.SetSize(anchoTablero * resolucionImagenes, altoTablero * resolucionImagenes);

    this->imagenPasto.ReadFromFile("res/texturasBMP/pasto.bmp");
    this->imagenTierra.ReadFromFile("res/texturasBMP/tierra.bmp");
    this->imagenAgua.ReadFromFile("res/texturasBMP/agua.bmp");
    this->imagenAguaProfunda.ReadFromFile("res/texturasBMP/aguaProfunda.bmp");
    this->imagenAire.ReadFromFile("res/texturasBMP/aire.bmp");
    this->imagenSoldadoJugador.ReadFromFile("res/texturasBMP/soldadoJugador.bmp");
    this->imagenSoldadoEnemigo.ReadFromFile("res/texturasBMP/soldadoEnemigo.bmp");
    this->imagenQuimicos.ReadFromFile("res/texturasBMP/quimicos.bmp");
    this->imagenMinaJugador.ReadFromFile("res/texturasBMP/minaJugador.bmp");
    this->imagenMinaEnemigo.ReadFromFile("res/texturasBMP/minaEnemigo.bmp");
    this->imagenAvionJugador.ReadFromFile("res/texturasBMP/avionJugador.bmp");
    this->imagenAvionEnemigo.ReadFromFile("res/texturasBMP/avionEnemigo.bmp");
    this->imagenBarcoJugador.ReadFromFile("res/texturasBMP/barcoJugador.bmp");
    this->imagenBarcoEnemigo.ReadFromFile("res/texturasBMP/barcoEnemigo.bmp");
    this->imagenSubmarinoJugador.ReadFromFile("res/texturasBMP/submarinoJugador.bmp");
    this->imagenSubmarinoEnemigo.ReadFromFile("res/texturasBMP/submarinoEnemigo.bmp");
    this->imagenNiebla.ReadFromFile("res/texturasBMP/niebla.bmp");
    this->imagenError.ReadFromFile("res/texturasBMP/error.bmp");
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

void BitmapBatallaDigital::dibujarCasillero(Casillero *casillero, Jugador *jugador, unsigned int altoTablero) {
    unsigned int posX = casillero->getCoordenada()->obtenerX() - 1;
    unsigned int posY = casillero->getCoordenada()->obtenerY() - 1;
    unsigned int posZ = casillero->getCoordenada()->obtenerZ();

    switch (casillero->getTipoCasillero())
    {
    case tierra:
        if(posZ < NIVEL_MAXIMO_TIERRA) {
            dibujar(posX, posY, this->imagenTierra, altoTablero);
        }
        else {
            dibujar(posX, posY, this->imagenPasto, altoTablero);
        }
        break;
    case agua:
        if(posZ < NIVEL_MAXIMO_TIERRA) {
            dibujar(posX, posY, this->imagenAguaProfunda, altoTablero);
        }
        else {
            dibujar(posX, posY, this->imagenAgua, altoTablero);
        }
        break;
    case aire:
        dibujar(posX, posY, this->imagenAire, altoTablero);
        break;
    default:
        dibujar(posX, posY, this->imagenError, altoTablero); // PARA DEBUG
        break;
    }

    if (!casillero->estaActivo()) {
        dibujarTransparente(posX, posY, this->imagenNiebla, altoTablero);
    }

    // Si no esta ocupado no se hace nada mas
    if(!casillero->estaOcupado()) return;
    
    if(jugador != NULL) {   // Si hay una ficha verifico que le pertenezca al jugador del turno
        if (jugador->obtenerFicha(*(casillero->getCoordenada())) == NULL) return;
    }

    // Busco el tipo de ficha
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

// Funcion auxiliar para convertir entero a string y eso a un const char * que pide la funcion de libreria
const char *escribirRuta(unsigned int nivelZ)
{
    std::stringstream temp;
    temp<<nivelZ;
    std::string ruta = "TableroNivel" + temp.str() + ".bmp";
    return ruta.c_str();
}

void BitmapBatallaDigital::dibujarCapa(Tablero *tablero, Jugador *jugador, unsigned int nivelZ) {
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
            dibujarCasillero(casillero, jugador, altoTablero);
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
    this->imagenTablero.WriteToFile(escribirRuta(nivelZ));
}

void BitmapBatallaDigital::dibujarTablero(Tablero *tablero, Jugador *jugador) {
    unsigned int profundidadTablero = tablero->getDimZ();

    for(unsigned int z = 1 ; z <= profundidadTablero ; z++) {
        dibujarCapa(tablero, jugador, z);
    }   
}

BitmapBatallaDigital::~BitmapBatallaDigital() {}
