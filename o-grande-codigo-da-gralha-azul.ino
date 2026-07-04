/*
  O Grande Código da Gralha Azul
  — Exemplo Completo: CRSF + NeoPixel + BMP180 + Telemetria —

  Todas as faculdades despertas. Este é o ponto de partida para
  qualquer modelo — descomente os *_DESLIGADO conforme necessário.

  Este sketch vive na raiz do repositório como referência. Para uso
  normal, prefira os exemplos em File → Examples.
*/

// ─── Guardião dos Ventos (CRSF) ──────────────────────────────────
//    Comente esta linha se usar PPM:
#define GUARDIAO_DOS_VENTOS_SIDERAIS

// ─── Pinos dos Servos ─────────────────────────────────────────────
#define ARTICULACAO_ASA_DA_MANHA       3
#define ARTICULACAO_ASA_DO_ENTARDECER  8

// ─── Chama Azul (NeoPixel onboard) ────────────────────────────────
#define NUCLEO_DA_CHAMA_AZUL           16
#define QUANTIDADE_DE_CENTELHAS        1

// ─── Sopros do Guardião (CRSF UART) ───────────────────────────────
#define VIA_DOS_SONHOS_LUNARES         1   // RX (GP1)
#define VIA_DOS_ECOS_SOLARES           0   // TX (GP0)
#define FREQUENCIA_DO_SOPRO_COSMICO    420000

// ─── Oráculo da Pressão (BMP180 via I2C) ─────────────────────────
#define PINO_SILENCIO_DA_ALTURA        26  // SDA
#define PINO_RITMO_DA_PRESSAO          27  // SCL

// ─── Pulsação do Coração ─────────────────────────────────────────
//    DEVE corresponder à velocidade real do seu servo.
//    A amplitude, frequência e escala do algoritmo de batimento
//    derivam deste valor. Se não bater certo, a dança perde a forma.
#define CICLO_DO_CORACAO_ALADO         0.065f

// ─── Faculdades Opcionais ─────────────────────────────────────────
//    Todas ativas. Descomente para desabilitar:
// #define CHAMA_AZUL_DESLIGADA
// #define ORACULO_DESLIGADO
// #define SUSSURRO_DESLIGADO

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