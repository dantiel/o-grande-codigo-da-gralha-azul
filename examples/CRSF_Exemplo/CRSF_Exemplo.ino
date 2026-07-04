/*
  O Grande Código da Gralha Azul
  — Exemplo CRSF: Gralha-das-Araucárias —

  A Gralha-das-Araucárias dança entre os pinheiros centenários
  com asas que cortam o crepúsculo. Esta é a configuração completa:
  CRSF, NeoPixel, BMP180, Telemetria — todos os sentidos despertos.

  Hardware: RP2040 | CRSF Serial1 | Servos em pinos configuráveis
*/

// ─── Configuração da Gralha ───────────────────────────────────────
#define GUARDIAO_DOS_VENTOS_SIDERAIS
#define ARTICULACAO_DA_ASA_MATUTINA   3
#define ARTICULACAO_DA_ASA_VESPERTINA 8
#define NUCLEO_DA_CHAMA_AZUL          16
#define QUANTIDADE_DE_CENTELHAS       1
#define CICLO_DO_CORACAO_ALADO        0.065f

// ─── Faculdades Opcionais ─────────────────────────────────────────
// #define ORACULO_DESLIGADO
// #define SUSSURRO_DESLIGADO
// #define CHAMA_AZUL_DESLIGADA

// ─── Debug ──────────────────────────────────────────────────────────
#define ECOS_PRESCINDIVEIS_DA_ALMA_ALADA

// ─── Includes ───────────────────────────────────────────────────────
#include <GralhaAzul.h>

// ─── Instância ──────────────────────────────────────────────────────
GralhaAzul gralha;

// ─── Setup ──────────────────────────────────────────────────────────
void setup() {
  delay(100);
  gralha.ecosPrescindiveis = &Serial;
  gralha.begin();
}

// ─── Loop ───────────────────────────────────────────────────────────
void loop() {
  gralha.update();
}
