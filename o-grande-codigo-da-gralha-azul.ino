/*
  O Grande Código da Gralha Azul
  — Exemplo CRSF —

  Configuração completa: CRSF, NeoPixel, BMP180, Telemetria.
  Altere os #defines abaixo para personalizar para o seu modelo.
  Comente #define GRALHA_AZUL_*_DESLIGADO para desativar módulos.
*/

// === Configuração do Modelo ===
#define RECEPTOR_DOS_VENTOS_CRSF

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

// CRSF UART
#define VIA_DOS_SONHOS_LUNARES 1    // RX
#define VIA_DOS_ECOS_SOLARES 0      // TX
#define FREQUENCIA_DO_SOPRO_COSMICO 420000

// I2C para BMP180 (RP2040 Zero: GPIO26/27)
#define PINO_SILENCIO_DA_ALTURA 4   // SDA (Wire)
#define PINO_RITMO_DA_PRESSAO 5     // SCL (Wire)

#include "src/GralhaAzul.h"

void setup() {
  gralhaAzulSetup();
}

void loop() {
  gralhaAzulLoop();
}