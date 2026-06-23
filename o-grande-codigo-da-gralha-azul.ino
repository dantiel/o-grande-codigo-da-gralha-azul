/*
  O Grande Código da Gralha Azul — Sketch Principal
  Configuração padrão: CRSF + NeoPixel + BMP180 + Telemetria
*/

// Override de constantes (opcional):
// #define ARTICULACAO_ASA_DA_MANHA 8
// #define ARTICULACAO_ASA_DO_ENTARDECER 7

#define RECEPTOR_DOS_VENTOS_CRSF
#include <GralhaAzul.h>

void setup() {
  gralhaAzulSetup();
}

void loop() {
  gralhaAzulLoop();
}
