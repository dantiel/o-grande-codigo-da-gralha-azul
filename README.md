# O Grande Código da Gralha Azul

**Ornitóptero CRSF/PPM para RP2040 Zero**

Uma inscrição alada que transforma um RP2040 Zero no cérebro de um ornitóptero — uma criatura mecânica que bate asas e dança com os ventos. O coração pulsante da Gralha Azul, a semeadora incansável das florestas do Sul.

---

## 📦 Como usar como Biblioteca

Este projeto está estruturado como uma **biblioteca Arduino**. Para usar:

1. Copie a pasta `src/` para a sua pasta `libraries/` como `GralhaAzul/`
2. Ou mantenha a estrutura do repositório e use os exemplos em `examples/`
3. Inclua `#include <GralhaAzul.h>` no seu sketch
4. Chame `gralhaAzulSetup()` no `setup()` e `gralhaAzulLoop()` no `loop()`

### Criar um modelo novo

Basta copiar um dos exemplos e alterar as `#define` **antes** do `#include <GralhaAzul.h>`:

```cpp
#define RECEPTOR_DOS_VENTOS_PPM
#define GRALHA_AZUL_BAROMETRO_DESLIGADO
#define GRALHA_AZUL_NEOPIXEL_DESLIGADO
#include <GralhaAzul.h>

void setup() { gralhaAzulSetup(); }
void loop()  { gralhaAzulLoop(); }
```

### Configuração de pinos (override)

Todas as constantes têm `#ifndef` — basta definir o valor **antes** do `#include`:

```cpp
#define ARTICULACAO_ASA_DA_MANHA 9       // em vez de 8
#define NUCLEO_DA_CHAMA_AZUL 15          // NeoPixel no GPIO15
#include <GralhaAzul.h>
```

---

## 🔧 Módulos opcionais

| Módulo | Guarda | Efeito |
|--------|--------|--------|
| NeoPixel | `GRALHA_AZUL_NEOPIXEL_DESLIGADO` | Remove LED RGB |
| BMP180 | `GRALHA_AZUL_BAROMETRO_DESLIGADO` | Remove barómetro + altitude hold |
| Telemetria CRSF | `GRALHA_AZUL_TELEMETRIA_DESLIGADO` | Remove telemetria (só CRSF) |

---

## 📡 Receptor

### CRSF (padrão)
- `RECEPTOR_DOS_VENTOS_CRSF` (default)
- 10 canais via Serial1 (GPIO0 TX, GPIO1 RX)
- Telemetria de altitude e temperatura
- Requer a biblioteca [CRSF by Sam4uk](https://github.com/Sam4uk/CRSF)

### PPM (alternativa)
- `RECEPTOR_DOS_VENTOS_PPM`
- 8 canais via GPIO2
- Sem telemetria CRSF
- Requer a biblioteca [PPMReaderRP2040](https://github.com/dantiel/PPMReaderRP2040)

---

## 🎮 Mapeamento de Canais

| Canal | Nome | CRSF | PPM (8 canais) |
|-------|------|------|----------------|
| CH1 | `voz_do_aletao` (Roll) | ✅ | ✅ |
| CH2 | `voz_do_profundor` (Pitch) | ✅ | ✅ |
| CH3 | `voz_do_sopro_vital` (Throttle) | ✅ | ✅ |
| CH4 | `voz_do_leme_estelar` (Yaw) | ✅ | ✅ (não usado) |
| CH5 | `voz_do_despertar` (Arm) | ✅ | ✅ |
| CH6 | `voz_do_compasso_da_alma` (Compasso) | ✅ | ✅ |
| CH7 | `voz_da_ferocidade_do_bater` (Downstroke Ferocity) | ✅ | ✅ |
| CH8 | `voz_da_ferocidade_do_retorno` (Upstroke Ferocity) | ✅ | ✅ |
| CH9 | `voz_da_ferocidade_do_leme` (Rudder Ferocity, -4..+4) | ✅ | ❌ (fixo=1000) |
| CH10 | `voz_do_sustentar_altura` (Altitude Hold Gain) | ✅ | ❌ (fixo=1000) |

---

## 🌡️ Altitude Hold

Ativado por CH10 (Ganho 0–100%) + BMP180 (opcional, `ORACULO_DA_PRESSAO_DO_CEU`):
- CH10 = 1000 → Hold desligado, CH3 é acelerador direto
- CH10 = 2000 → Hold a 100% de força de correção
- CH3 define a altitude alvo (1000=0m, 2000=20m)
- Zona morta de 0.5m para evitar oscilações

---

## 📜 Estrutura do Código

```
src/GralhaAzul.h       — Header: #define guards, extern vars, declarações
src/GralhaAzul.cpp     — Implementação completa
examples/CRSF_Exemplo/ — Config CRSF completa
examples/PPM_Exemplo/  — Config PPM mínima
library.properties     — Metadados Arduino IDE
```

---

## 🧠 Como funciona

1. **Receptor** lê os canais (CRSF via UART ou PPM via GPIO)
2. **AnimarPulsarDoCoracaoAlado()** gera a senoide do batimento das asas
3. **ManifestarOVooNosVentos()** calcula os ângulos dos servos com:
   - Roll (diff) + Pitch (common mode)
   - Ferocity diferencial por CH9
4. **EscutarPressaoDoCeu()** (opcional) lê BMP180
5. **SustentarAltura()** (opcional) regula altitude com CH10
6. **SussurrarVooAoEter()** envia telemetria CRSF

---

## 📜 Licença

MIT — A Gralha Azul é livre para voar por todos os céus.
