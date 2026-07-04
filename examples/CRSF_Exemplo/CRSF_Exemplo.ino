/*
  O Grande Código da Gralha Azul
  — Exemplo CRSF: Servo + NeoPixel —

  CRSF, um par de servos, NeoPixel onboard. Tudo que é essencial
  para o primeiro voo. Altere os defines conforme seu hardware.

  Hardware: RP2040 | CRSF Serial1 | Servos em pinos configuráveis
*/

// ─── Guardião dos Ventos (CRSF) ──────────────────────────────────
#define GUARDIAO_DOS_VENTOS_SIDERAIS

// ─── Pinos dos Servos ─────────────────────────────────────────────
#define ARTICULACAO_DA_ASA_MATUTINA   3
#define ARTICULACAO_DA_ASA_VESPERTINA 8

// ─── Chama Azul (NeoPixel onboard) ────────────────────────────────
#define NUCLEO_DA_CHAMA_AZUL          16
#define QUANTIDADE_DE_CENTELHAS       1

// ─── Pulsação do Coração ─────────────────────────────────────────
//    Deve corresponder à velocidade real do servo. Amplitude,
//    frequência e escala do batimento derivam daqui.
#define CICLO_DO_CORACAO_ALADO        0.065f

// ─── Faculdades Opcionais ─────────────────────────────────────────
#define ORACULO_DESLIGADO
#define SUSSURRO_DESLIGADO
// #define CHAMA_AZUL_DESLIGADA

// ─── O Despertar ──────────────────────────────────────────────────
#include <GralhaAzul.h>

GralhaAzul gralha;

void setup() {
  delay(100);
  gralha.ecosPrescindiveis = &Serial;
  gralha.begin();
}

void loop() {
  gralha.update();
}