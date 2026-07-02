/*
  O Grande Código da Gralha Azul
  — Exemplo CRSF: Gralha-das-Araucárias —

  A Gralha-das-Araucárias dança entre os pinheiros centenários
  com asas que cortam o crepúsculo. Esta é a configuração completa:
  CRSF, NeoPixel, BMP180, Telemetria — todos os sentidos despertos.

  Para configurar este modelo, crie um arquivo GralhaAzulConfig.h
  no diretório do sketch com as constantes desejadas.
  Sem ele, a biblioteca usará GralhaAzulConfig_Defaults.h.
*/

#include <GralhaAzul.h>

void setup() {
  gralhaAzulSetup();
}

void loop() {
  gralhaAzulLoop();
}