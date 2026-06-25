/*
  O Grande Código da Gralha Azul
  — Exemplo CRSF: Servo_Rapido —

  Para servos de micro-asa que vibram como beija-flores.
  Servo recomendado: Blue Arrow D0576HT MG (1.7g, 0.07s/60°).
  Ciclo rápido (~33 Hz) — asas pequenas, batimento frenético.

  O D0576HT MG suporta até 50 Hz sem sobreaquecimento,
  mas a estrutura mecânica impõe o limite: 0.030s de ciclo
  para que a polia não descole da asa. Ajuste CICLO_DO_CORACAO_ALADO
  conforme o servo e a envergadura do seu modelo.

  Sem barómetro, sem telemetria, sem NeoPixel — apenas o vento.

  Para configurar este modelo, edite o arquivo:
  src/GralhaAzulConfig.h

  Lá encontrará todas as constantes documentadas:
  - CICLO_DO_CORACAO_ALADO: 0.030f (~33 Hz, Blue Arrow D0576HT MG)
  - ANGULO_DO_PLANAR_SERENO: -1 (planar quase nulo)
  - GRALHA_AZUL_NEOPIXEL_DESLIGADO: descomentar
  - GRALHA_AZUL_BAROMETRO_DESLIGADO: descomentar
  - GRALHA_AZUL_TELEMETRIA_DESLIGADO: descomentar
  - FEROCIDADE_MINIMA: 1.0f
  - FEROCIDADE_MAXIMA: 10.0f
*/

#include "../../src/GralhaAzul.h"

void setup() {
  gralhaAzulSetup();
}

void loop() {
  gralhaAzulLoop();
}