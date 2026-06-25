/*
  O Grande Código da Gralha Azul
  — Exemplo PPM: Gralha-dos-Pampas —

  Nos pampas infinitos, onde o vento beija o chão,
  a Gralha-dos-Pampas plana sem pressa, guiada por oito vozes
  que ecoam do rádio antigo. PPM puro, sem telemetria —
  apenas a alma e o horizonte.

  Configuração para receptor PPM (8 canais).
  CH9 e CH10 são fixos (não disponíveis em PPM de 8 canais).
  NeoPixel e BMP180 são opcionais.
  Telemetria CRSF não está disponível em modo PPM.

  Para configurar este modelo, edite o arquivo:
  src/GralhaAzulConfig.h

  Lá encontrará todas as constantes documentadas:
  - RECEPTOR_DOS_VENTOS_PPM (em vez de CRSF)
  - PINO_DO_MENSAGEIRO: 2
  - NUM_CANAIS_DO_MENSAGEIRO: 8
  - CICLO_DO_CORACAO_ALADO: 0.052f (~19 Hz)
  - ANGULO_DO_PLANAR_SERENO: -3 (glide degree suave)
  - Módulos: todos ativos (NeoPixel, BMP180)
*/

#include "../../src/GralhaAzul.h"

void setup() {
  gralhaAzulSetup();
}

void loop() {
  gralhaAzulLoop();
}