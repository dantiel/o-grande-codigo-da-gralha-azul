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

  Para configurar este modelo, crie um arquivo GralhaAzulConfig.h
  no diretório do sketch com as constantes desejadas.
*/

#include <GralhaAzul.h>

void setup() {
  gralhaAzulSetup();
}

void loop() {
  gralhaAzulLoop();
}