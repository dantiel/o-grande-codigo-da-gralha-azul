# Guia de Migração — Do Monolítico .ino para a Biblioteca Modular

Este guia explica como converter sketches antigos (anteriores a v1.16.0) que usavam o código monolítico `o-grande-codigo-da-gralha-azul.ino` para a nova estrutura de biblioteca (v1.17.0+).

---

## O Que Mudou

### Antes (v1.15.1)

- Código único em um arquivo `.ino` (846 linhas)
- Configurações espalhadas por todo o código, sem separação clara
- Sem separação entre configuração, declaração e implementação
- Nomes herméticos brasileiros sem documentação de uso
- Compilação direta — só funcionava como sketch único

### Depois (v1.17.0+)

```
src/
├── GralhaAzulConfig.h   (314 linhas — todas as constantes configuráveis com #ifndef)
├── GralhaAzul.h          (140 linhas — declarações extern, enum, struct, class)
└── GralhaAzul.cpp        (605 linhas — implementação completa, poesia incluída)

examples/
├── CRSF_Exemplo/         (CRSF completo: NeoPixel + BMP180 + Telemetria)
├── PPM_Exemplo/          (PPM mínimo: 8 canais)
├── CRSF_Servo_Rapido/    (Blue Arrow D0576HT MG, 33Hz, ultra-leve)
└── CRSF_Servo_Torque/    (KST MS320, 12Hz, torque)

README.md                 (introdução poética e prática)
DOCUMENTATION.md          (documentação técnica completa)
MIGRATION_GUIDE.md        (este guia)
library.properties         (metadados para Arduino IDE)
```

### Principais Diferenças

| Aspecto | Antigo (.ino) | Novo (biblioteca) |
|---------|---------------|-------------------|
| Configuração | Diretamente no código, misturada | `GralhaAzulConfig.h` — um grimório centralizado |
| Inicialização | `setup()` direto | `gralhaAzulSetup()` |
| Loop | `loop()` direto | `gralhaAzulLoop()` |
| Módulos opcionais | Não existiam | `#define GRALHA_AZUL_*_DESLIGADO` |
| Pinos | Fixos no código | Configuráveis via `#ifndef` no config header |
| Exemplos | Nenhum | 4 exemplos específicos por servo |
| Documentação | Comentários soltos | README + DOCUMENTATION + MIGRATION GUIDE |

---

## Passo a Passo para Migrar um Sketch Personalizado

### 1. Substituir os Includes

**Antes:**
```cpp
#include <Arduino.h>
#include <Servo.h>
#include <CrsfSerial.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_BMP085_U.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
```

**Depois:**
```cpp
#include "src/GralhaAzulConfig.h"   // opcional — só se quiser sobrescrever padrões
#include "src/GralhaAzul.h"         // já inclui tudo que precisa
```

### 2. Renomear Funções

| Nome Antigo (no .ino) | Nome Novo (na biblioteca) |
|------------------------|----------------------------|
| `setup()` | `gralhaAzulSetup()` — chame dentro do seu `setup()` |
| `loop()` | `gralhaAzulLoop()` — chame dentro do seu `loop()` |
| (funções auxiliares) | Mantêm os mesmos nomes (estão em `GralhaAzul.cpp`, compiladas separadamente) |

### 3. Mover Configurações para o Config Header

**Antes** (no meio do código):
```cpp
#define CICLO_DO_CORACAO_ALADO  0.065f
#define ANGULO_DO_PLANAR_SERENO -3
int meu_pino_servo = 8;
```

**Depois** (no início do sketch, ANTES do include):
```cpp
#define CICLO_DO_CORACAO_ALADO  0.065f   // seu valor personalizado
#define ANGULO_DO_PLANAR_SERENO -3
#include "src/GralhaAzul.h"
```

Ou, melhor ainda, edite diretamente `src/GralhaAzulConfig.h`.

### 4. Desligar Módulos Não Usados

Se o seu modelo não tem NeoPixel, barómetro ou telemetria:

```cpp
#define GRALHA_AZUL_NEOPIXEL_DESLIGADO
#define GRALHA_AZUL_BAROMETRO_DESLIGADO
#define GRALHA_AZUL_TELEMETRIA_DESLIGADO
#include "src/GralhaAzul.h"
```

### 5. Reconfigurar Pinos

Se usa pinos diferentes dos padrão:

```cpp
#define ARTICULACAO_ASA_DA_MANHA      9    // em vez de 8
#define ARTICULACAO_ASA_DO_ENTARDECER 10   // em vez de 7
#define NUCLEO_DA_CHAMA_AZUL          15   // em vez de 16
#include "src/GralhaAzul.h"
```

### 6. Exemplo de Sketch Migrado Mínimo

```cpp
// Meu ornitóptero personalizado — baseado na Gralha Azul v1.17.0
#define GRALHA_AZUL_BAROMETRO_DESLIGADO
#define GRALHA_AZUL_TELEMETRIA_DESLIGADO
#define CICLO_DO_CORACAO_ALADO  0.040f   // servo rápido personalizado

#include "src/GralhaAzul.h"

void setup() {
    gralhaAzulSetup();
    // minha inicialização adicional (ex: LED externo)
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    gralhaAzulLoop();
    // meu código extra (ex: piscar LED a cada ciclo)
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}
```

---

## Se o Sketch Incluía Código Personalizado

### Código no `setup()` original

O `gralhaAzulSetup()` já chama:
- `MantoDeLuzCelestial::AcenderLuzPrimordial()` (NeoPixel)
- `DespertarOraculoDaPressao()` (BMP180)
- `AoDespertarParaOCantoDoEter()` (callback CRSF/PPM)
- Inicialização Serial1 (CRSF) ou PPM
- `Servo.attach()` para ambos os servos

Se precisava de inicialização extra, coloque **depois** de `gralhaAzulSetup()`.

### Código no `loop()` original

O `gralhaAzulLoop()` já chama, nesta ordem:
1. CRSF/PPM loop
2. `AnimarPulsarDoCoracaoAlado()`
3. `EscutarPressaoDoCeu()`
4. `SustentarAltura()`
5. `ManifestarOVooNosVentos()`
6. `SussurrarVooAoEter()`
7. NeoPixel (a cada 33ms)
8. Serial debug (a cada 250ms)

Se o seu loop tinha código extra, coloque **depois** de `gralhaAzulLoop()`.

---

## Verificações Pós-Migração

- [ ] Os servos movem-se na frequência esperada?
- [ ] O altitude hold funciona (se barómetro ativo)?
- [ ] NeoPixel acende (se ativo)?
- [ ] Telemetria CRSF aparece no radiomaster (se ativa)?
- [ ] Não há erros de compilação (especialmente "undefined reference")?
- [ ] Os pinos correspondem à sua montagem física?
- [ ] As constantes personalizadas foram todas movidas para antes do `#include`?

---

## Rollback

Caso algo não funcione, mantenha uma cópia do `.ino` antigo. Pode reverter o repositório:

```bash
git checkout b1654a7 -- o-grande-codigo-da-gralha-azul.ino
```

E apagar os arquivos novos (`src/`, `examples/`, `DOCUMENTATION.md`, `MIGRATION_GUIDE.md`) — mas perderá todas as melhorias de configuração, os exemplos específicos por servo e a documentação técnica.

---

## Suporte

Se encontrar problemas na migração:

1. Consulte `DOCUMENTATION.md` — contém a API completa e troubleshooting
2. Consulte `README.md` — visão geral e instruções de uso
3. Abra uma issue no GitHub: https://github.com/dantiel/o-grande-codigo-da-gralha-azul

---

## Notas da Versão

| Versão | Mudanças na Migração |
|--------|----------------------|
| v1.15.1 | Código monolítico original. Última versão sem biblioteca. |
| v1.16.0 | Primeira versão como biblioteca. `setup()` → `gralhaAzulSetup()`, `loop()` → `gralhaAzulLoop()`. |
| v1.16.3 | `.cpp` reescrito do zero a partir do original v1.15.1. Caminho relativo `../../src/GralhaAzul.h`. |
| v1.17.0 | Config centralizada (`GralhaAzulConfig.h`), 4 exemplos, documentação completa. |

---

*«A Gralha Azul migrou do seu galho solitário para um ninho de biblioteca — as mesmas asas, agora mais fortes e mais fáceis de ajustar para cada novo voo.»*
