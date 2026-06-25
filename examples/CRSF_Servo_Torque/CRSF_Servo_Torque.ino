/*
  O Grande Código da Gralha Azul
  — Exemplo CRSF: Servo_Torque —

  Para servos de alto torque que movem asas grandes com paciência.
  Servo recomendado: KST MS320 (56g, 0.14s/60° a 8.4V).
  Ciclo lento (~12 Hz) — asas amplas, batimento contemplativo.

  O KST MS320 tem torque de 8.5kg·cm a 8.4V, ideal para
  ornitópteros de 1m+ de envergadura. Ciclo mínimo seguro:
  0.080s para não sobreaquecer a bobina em voo contínuo.
  Ajuste CICLO_DO_CORACAO_ALADO para cima se a estrutura
  da asa exigir ainda mais calma.

  Com NeoPixel (a chama azul pulsa), sem barómetro,
  sem telemetria — foco na simplicidade do voo.

  Para configurar este modelo, edite o arquivo:
  src/GralhaAzulConfig.h

  Lá encontrará todas as constantes documentadas:
  - CICLO_DO_CORACAO_ALADO: 0.080f (~12 Hz, KST MS320)
  - ANGULO_DO_PLANAR_SERENO: -2 (planar suave)
  - GRALHA_AZUL_BAROMETRO_DESLIGADO: descomentar
  - GRALHA_AZUL_TELEMETRIA_DESLIGADO: descomentar
  - FEROCIDADE_MINIMA: 1.0f
  - FEROCIDADE_MAXIMA: 5.0f
*/

#include "../../src/GralhaAzul.h"

void setup() {
  gralhaAzulSetup();
}

void loop() {
  gralhaAzulLoop();
}