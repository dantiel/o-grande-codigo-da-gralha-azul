# O Grande Código da Gralha Azul

Ornitóptero CRSF/PPM para RP2040 Zero — Biblioteca do Coração Alado.

## Estrutura

```
src/GralhaAzul.h       — Header: #ifndef-guarded #defines, extern vars, enum/class declarations
src/GralhaAzul.cpp     — Implementação: toda a lógica de voo, setup/loop
examples/CRSF_Exemplo/ — Configuração CRSF completa (NeoPixel + BMP180 + Telemetria)
examples/PPM_Exemplo/  — Configuração PPM mínima (8 canais, CH9/CH10 fixos)
```

## Uso como Biblioteca

1. Instale a library (Arduino IDE: Sketch → Include Library → Add .ZIP Library)
2. Copie um exemplo de `examples/` para seu sketch
3. Altere os `#define`s antes de `#include <GralhaAzul.h>`
4. Compile e carregue

### Módulos Opcionais

Defina **antes** de `#include <GralhaAzul.h>`:

```cpp
#define GRALHA_AZUL_NEOPIXEL_DESLIGADO    // Remove NeoPixel
#define GRALHA_AZUL_BAROMETRO_DESLIGADO   // Remove BMP180
#define GRALHA_AZUL_TELEMETRIA_DESLIGADO  // Remove telemetria CRSF
```

### Configuração de Pinos

Todos os pinos e constantes podem ser sobrescritos via `#define` antes do include.
Veja `src/GralhaAzul.h` para a lista completa.

## Licença

MIT
