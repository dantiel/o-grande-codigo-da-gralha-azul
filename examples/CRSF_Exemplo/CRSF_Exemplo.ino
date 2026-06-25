/*
  O Grande Código da Gralha Azul
  — Exemplo CRSF: Gralha-das-Araucárias —

  Configuração completa: CRSF, NeoPixel, BMP180, Telemetria.
  Altere as constantes abaixo para tecer a sina do seu modelo.
  Comente #define GRALHA_AZUL_*_DESLIGADO para desativar módulos.
*/

/* A Voz que a Gralha Escuta — CRSF, o guardião sideral. */
#define RECEPTOR_DOS_VENTOS_CRSF

/* Descomente para silenciar os módulos que não precisa:
// #define GRALHA_AZUL_NEOPIXEL_DESLIGADO   — sem a chama azul
// #define GRALHA_AZUL_BAROMETRO_DESLIGADO  — sem o oráculo da pressão
// #define GRALHA_AZUL_TELEMETRIA_DESLIGADO — sem sussurro ao éter
*/

/* Os portais dos tendões alados — onde as asas se fixam. */
#define ARTICULACAO_ASA_DA_MANHA       8   // asa esquerda
#define ARTICULACAO_ASA_DO_ENTARDECER  7   // asa direita

/* A chama que pulsa no peito da Gralha — NeoPixel. */
#define NUCLEO_DA_CHAMA_AZUL          16
#define QUANTIDADE_DE_CENTELHAS_NA_CHAMA 1

/* O portal do rádio — CRSF UART. */
#define VIA_DOS_SONHOS_LUNARES         1   // RX
#define VIA_DOS_ECOS_SOLARES           0   // TX
#define FREQUENCIA_DO_SOPRO_COSMICO 420000

/* O oráculo da pressão — I2C para BMP180 (RP2040 Zero: GPIO26/27). */
#define PINO_SILENCIO_DA_ALTURA        4   // SDA
#define PINO_RITMO_DA_PRESSAO          5   // SCL

/* A geometria do planar sereno — o glide degree.
   A Gralha desliza pelo céu com este ângulo quando não bate as asas.
   Negativo: nariz abaixo. Positivo: nariz acima. */
#define ANGULO_DO_PLANAR_SERENO       -4

/* O ciclo do coração alado — a duração de uma batida de asas (segundos).
   Para servos de 180° com rotação contínua via polia:
   - 0.052f (~19 Hz): asa pequena, ágil, para Gralha-das-Araucárias
   - 0.080f (~12 Hz): asa média, planar suave
   - 0.100f (~10 Hz): asa grande, voo lento e contemplativo
   Consulte a especificação do servo: tempo mínimo de ciclo sem sobreaquecimento. */
#define CICLO_DO_CORACAO_ALADO  0.052f

#include "../../src/GralhaAzul.h"

void setup() {
  gralhaAzulSetup();
}

void loop() {
  gralhaAzulLoop();
}
