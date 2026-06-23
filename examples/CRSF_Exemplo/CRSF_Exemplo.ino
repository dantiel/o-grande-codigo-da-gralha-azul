/*
  CRSF_Exemplo — A Gralha Azul com Receptor CRSF
  Configuração completa: NeoPixel + BMP180 + Telemetria CRSF

  Hardware:
    - RP2040 Zero
    - Receptor CRSF (ELRS) em Serial1 (GPIO0 TX, GPIO1 RX)
    - 2x Servos (GPIO7, GPIO8)
    - NeoPixel (GPIO16)
    - BMP180 (I2C: GPIO4 SDA, GPIO5 SCL)
*/

// --- Configuração específica deste modelo ---
// (Use #define ANTES de #include para sobrescrever os padrões)

// #define RECEPTOR_DOS_VENTOS_PPM    // Descomente para PPM
#define RECEPTOR_DOS_VENTOS_CRSF      // CRSF ativo

// Opcionais — descomente para desligar:
// #define GRALHA_AZUL_NEOPIXEL_DESLIGADO
// #define GRALHA_AZUL_BAROMETRO_DESLIGADO
// #define GRALHA_AZUL_TELEMETRIA_DESLIGADO

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
