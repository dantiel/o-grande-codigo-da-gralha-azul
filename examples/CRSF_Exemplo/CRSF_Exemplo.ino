/*
  O Grande Código da Gralha Azul
  — Exemplo CRSF: Gralha-das-Araucárias —

  A Gralha-das-Araucárias dança entre os pinheiros centenários
  com asas que cortam o crepúsculo. Esta é a configuração completa:
  CRSF, NeoPixel, BMP180, Telemetria — todos os sentidos despertos.

  Hardware: RP2040 | CRSF Serial1 | Servos em pinos configuráveis
*/

#include <GralhaAzul.h>

GralhaAzul gralha;

void setup() {
  // Articulações das asas
  gralha.articulacaoAsaDaManha = 3;
  gralha.articulacaoAsaDoEntardecer = 8;
  
  // O ciclo do coração alado
  gralha.cicloDoCoracaoAlado = 0.065f;
  
  // Despertar a Gralha
  gralha.begin();
}

void loop() {
  // A pulsação eterna
  gralha.update();
}
