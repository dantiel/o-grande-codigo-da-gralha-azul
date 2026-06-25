/*
  O Grande Código da Gralha Azul
  — Exemplo CRSF: Gralha-das-Araucárias —

  A Gralha-das-Araucárias dança entre os pinheiros centenários
  com asas que cortam o crepúsculo. Esta é a configuração completa:
  CRSF, NeoPixel, BMP180, Telemetria — todos os sentidos despertos.

  Para configurar este modelo, edite o arquivo:
  src/GralhaAzulConfig.h

  Lá encontrará todas as constantes documentadas:
  - CICLO_DO_CORACAO_ALADO: 0.052f (~19 Hz, DSSERVO DS3218 MG)
  - ANGULO_DO_PLANAR_SERENO: -4 (glide degree)
  - Módulos: todos ativos (NeoPixel, BMP180, Telemetria)
  - Pinos: conforme abaixo

  As #define abaixo são apenas documentação — o valor real
  é definido no GralhaAzulConfig.h com guardas #ifndef.
*/

#include "../../src/GralhaAzul.h"

void setup() {
  gralhaAzulSetup();
}

void loop() {
  gralhaAzulLoop();
}