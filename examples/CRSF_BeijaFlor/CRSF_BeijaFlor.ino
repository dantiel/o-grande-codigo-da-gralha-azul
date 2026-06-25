/*
  O Grande Código da Gralha Azul
  — Exemplo CRSF: Beija-Flor-de-Fogo —

  Asa ultraleve, batimento rápido.
  Servo de micro-asa com suporte a altas frequências.
  Sem barómetro, sem telemetria — apenas a chama e o vento.
*/

#define RECEPTOR_DOS_VENTOS_CRSF

#define GRALHA_AZUL_NEOPIXEL_DESLIGADO    // sem NeoPixel (peso extra)
#define GRALHA_AZUL_BAROMETRO_DESLIGADO   // sem barómetro
#define GRALHA_AZUL_TELEMETRIA_DESLIGADO  // sem telemetria

#define ARTICULACAO_ASA_DA_MANHA       8
#define ARTICULACAO_ASA_DO_ENTARDECER  7

#define VIA_DOS_SONHOS_LUNARES         1
#define VIA_DOS_ECOS_SOLARES           0
#define FREQUENCIA_DO_SOPRO_COSMICO 420000

/* Planar quase nulo — o Beija-Flor não plana, só bate asas. */
#define ANGULO_DO_PLANAR_SERENO       -1

/* O ciclo do coração alado — ultrarrápido!
   Para servos de micro-asa com suporte a altas frequências
   (ex.: servos de 1.5g para ornitópteros miniatura).
   Ciclo mínimo seguro: ~0.030s (~33 Hz).
   Consulte a especificação do servo: não exceda o limite de
   banda passante para evitar danos. */
#define CICLO_DO_CORACAO_ALADO  0.030f

/* Ferocidade máxima para o bater frenético. */
#define FEROCIDADE_MINIMA   1.0f
#define FEROCIDADE_MAXIMA  10.0f

#include "../../src/GralhaAzul.h"

void setup() {
  gralhaAzulSetup();
}

void loop() {
  gralhaAzulLoop();
}
