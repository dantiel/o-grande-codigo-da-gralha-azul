/*
  O Grande Código da Gralha Azul
  — Exemplo CRSF: Gavião-Cinzento —

  Asa grande, voo lento e planado.
  Servo de alto torque, ciclo mais lento para não sobreaquecer.
  Sem barómetro (voo puramente acrobático).
  Sem telemetria (foco na simplicidade).
*/

/* A Voz que a Gralha Escuta — CRSF. */
#define RECEPTOR_DOS_VENTOS_CRSF

/* Módulos desligados para este modelo:
   - sem barómetro (puro voo acrobático)
   - sem telemetria (simplicidade)
   - com NeoPixel (a chama azul pulsa) */
// #define GRALHA_AZUL_NEOPIXEL_DESLIGADO
#define GRALHA_AZUL_BAROMETRO_DESLIGADO
#define GRALHA_AZUL_TELEMETRIA_DESLIGADO

/* As asas do Gavião-Cinzento — portais amplos. */
#define ARTICULACAO_ASA_DA_MANHA       8
#define ARTICULACAO_ASA_DO_ENTARDECER  7

/* A chama que pulsa. */
#define NUCLEO_DA_CHAMA_AZUL          16
#define QUANTIDADE_DE_CENTELHAS_NA_CHAMA 1

/* O portal do rádio. */
#define VIA_DOS_SONHOS_LUNARES         1   // RX
#define VIA_DOS_ECOS_SOLARES           0   // TX
#define FREQUENCIA_DO_SOPRO_COSMICO 420000

/* O planar suave — glide degree para asa grande.
   O Gavião-Cinzento plana com o nariz levemente abaixo. */
#define ANGULO_DO_PLANAR_SERENO       -2

/* O ciclo do coração alado — mais lento para asa grande.
   Servo de alto torque (ex.: SG90 modificado com polia):
   ciclo mínimo seguro: ~0.080s (~12 Hz).
   Consulte a folha de dados do servo: evitar >15 Hz contínuos
   para não sobreaquecer a bobina. */
#define CICLO_DO_CORACAO_ALADO  0.080f

/* A ferocidade do bater — mais suave para asa grande,
   evitando stress no servo e na estrutura. */
#define FEROCIDADE_MINIMA   1.0f
#define FEROCIDADE_MAXIMA   5.0f  // menos agressivo que o padrão (8.0f)

#include "../../src/GralhaAzul.h"

void setup() {
  gralhaAzulSetup();
}

void loop() {
  gralhaAzulLoop();
}
