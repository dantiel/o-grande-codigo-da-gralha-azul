/*
  O Grande Código da Gralha Azul
  — Exemplo PPM: Gralha-dos-Pampas —

  Nos pampas infinitos, onde o vento beija o chão,
  a Gralha-dos-Pampas plana sem pressa, guiada por oito vozes
  que ecoam do rádio antigo. PPM puro, sem telemetria —
  apenas a alma e o horizonte.

  Hardware: RP2040 | PPM em GPIO1 | Servos em pinos configuráveis
*/

#include <PPMReaderRP2040.h>
#include <GralhaAzul.h>

GralhaAzul gralha;

void setup() {
  // Articulações das asas
  gralha.articulacaoAsaDaManha = 3;
  gralha.articulacaoAsaDoEntardecer = 8;
  
  // O portal dos cantos cósmicos (PPM)
  gralha.mensageiroDosVentosCosmicos = new PPMReader(1, 8);
  
  // O ciclo do coração alado
  gralha.cicloDoCoracaoAlado = 0.065f;
  
  // Despertar a Gralha
  gralha.begin();
}

void loop() {
  // A pulsação eterna
  gralha.update();
}
