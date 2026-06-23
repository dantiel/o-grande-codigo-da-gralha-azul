/*
  O Grande Código da Gralha Azul
  — Exemplo PPM —

  Configuração para receptor PPM (8 canais).
  CH9 e CH10 são fixos (não disponíveis em PPM de 8 canais).
  NeoPixel e BMP180 são opcionais.
  Telemetria CRSF não está disponível em modo PPM.
*/

// === Configuração do Modelo ===
#define RECEPTOR_DOS_VENTOS_PPM
#define PINO_DO_MENSAGEIRO 2
#define NUM_CANAIS_DO_MENSAGEIRO 8

// Descomente para desativar módulos opcionais:
// #define GRALHA_AZUL_NEOPIXEL_DESLIGADO
// #define GRALHA_AZUL_BAROMETRO_DESLIGADO
// #define GRALHA_AZUL_TELEMETRIA_DESLIGADO

// Pinos dos servos (RP2040 Zero)
#define ARTICULACAO_ASA_DA_MANHA 8
#define ARTICULACAO_ASA_DO_ENTARDECER 7

// NeoPixel
#define NUCLEO_DA_CHAMA_AZUL 16
#define QUANTIDADE_DE_CENTELHAS_NA_CHAMA 1

// I2C para BMP180 (RP2040 Zero: GPIO26/27)
#define PINO_SILENCIO_DA_ALTURA 4   // SDA (Wire)
#define PINO_RITMO_DA_PRESSAO 5     // SCL (Wire)

#include "../../src/GralhaAzul.h"

void setup() {
  gralhaAzulSetup();
}

void loop() {
  gralhaAzulLoop();
}