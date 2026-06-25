/*
  O Grande Código da Gralha Azul
  — Exemplo PPM: Gralha-dos-Pampas —

  Configuração para receptor PPM (8 canais).
  CH9 e CH10 são fixos (não disponíveis em PPM de 8 canais).
  NeoPixel e BMP180 são opcionais.
  Telemetria CRSF não está disponível em modo PPM.
*/

/* O mensageiro dos ventos cósmicos — PPM. */
#define RECEPTOR_DOS_VENTOS_PPM
#define PINO_DO_MENSAGEIRO            2
#define NUM_CANAIS_DO_MENSAGEIRO       8

/* Descomente para silenciar os módulos que não precisa:
// #define GRALHA_AZUL_NEOPIXEL_DESLIGADO   — sem a chama azul
// #define GRALHA_AZUL_BAROMETRO_DESLIGADO  — sem o oráculo da pressão
*/

/* Os portais dos tendões alados. */
#define ARTICULACAO_ASA_DA_MANHA       8
#define ARTICULACAO_ASA_DO_ENTARDECER  7

/* A chama que pulsa no peito da Gralha. */
#define NUCLEO_DA_CHAMA_AZUL          16
#define QUANTIDADE_DE_CENTELHAS_NA_CHAMA 1

/* O oráculo da pressão — I2C para BMP180. */
#define PINO_SILENCIO_DA_ALTURA        4   // SDA
#define PINO_RITMO_DA_PRESSAO          5   // SCL

/* O ângulo de planar — glide degree para a Gralha-dos-Pampas,
   que prefere planícies abertas com suave descida. */
#define ANGULO_DO_PLANAR_SERENO       -3

/* O ciclo do coração alado.
   Para servos de 180° com rotação contínua via polia.
   Ajuste conforme a especificação do servo: tempo mínimo de ciclo. */
#define CICLO_DO_CORACAO_ALADO  0.052f

#include "../../src/GralhaAzul.h"

void setup() {
  gralhaAzulSetup();
}

void loop() {
  gralhaAzulLoop();
}
