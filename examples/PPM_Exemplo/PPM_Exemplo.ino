/*
  PPM_Exemplo — A Gralha Azul com Receptor PPM
  Configuração mínima: sem CRSF, sem telemetria, sem BMP180.
  NeoPixel pode ser ligado ou desligado.

  Hardware:
    - RP2040 Zero
    - Receptor PPM no GPIO2 (8 canais)
    - 2x Servos (GPIO7, GPIO8)
    - NeoPixel (GPIO16) — opcional
*/

#define RECEPTOR_DOS_VENTOS_PPM

// Desligar módulos não usados com PPM (sem CRSF, sem telemetria):
#define GRALHA_AZUL_TELEMETRIA_DESLIGADO
#define GRALHA_AZUL_BAROMETRO_DESLIGADO

// NeoPixel pode ficar ligado ou desligado:
// #define GRALHA_AZUL_NEOPIXEL_DESLIGADO

// Override de pinos (opcional):
// #define ARTICULACAO_ASA_DA_MANHA 8
// #define ARTICULACAO_ASA_DO_ENTARDECER 7

#include <GralhaAzul.h>

void setup() {
  gralhaAzulSetup();
}

void loop() {
  gralhaAzulLoop();
}
