/*
  O Grande Código da Gralha Azul
  — Exemplo PPM: Gralha-dos-Pampas —

  Nos pampas infinitos, onde o vento beija o chão,
  a Gralha-dos-Pampas plana sem pressa, guiada por oito vozes
  que ecoam do rádio antigo. PPM puro, sem telemetria —
  apenas a alma e o horizonte.

  Hardware: RP2040 | PPM em GPIO1 | Servos em pinos configuráveis
*/

// ─── Configuração da Gralha ───────────────────────────────────────
#define MENSAGEIRO_DOS_CANTOS_COSMICOS
#define PORTAL_DOS_CANTOS_COSMICOS  1
#define NUMERO_DE_CANTOS            8

#define ARTICULACAO_DA_ASA_MATUTINA   3
#define ARTICULACAO_DA_ASA_VESPERTINA 8
#define NUCLEO_DA_CHAMA_AZUL          16
#define QUANTIDADE_DE_CENTELHAS       1
#define CICLO_DO_CORACAO_ALADO        0.065f   // Deve corresponder à velocidade real do servo. Amplitude, frequência e escala do batimento derivam daqui.

// ─── Faculdades Opcionais ─────────────────────────────────────────
#define ORACULO_DESLIGADO
#define SUSSURRO_DESLIGADO
// #define CHAMA_AZUL_DESLIGADA

// ─── Includes ───────────────────────────────────────────────────────
#include <PPMReaderRP2040.h>
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