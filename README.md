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

Basta copiar um dos exemplos e editar o arquivo de configuração:

**`src/GralhaAzulConfig.h`** — o grimório onde a Gralha guarda os segredos da sua forma.

Edite este arquivo para:
- Ativar/desativar módulos (NeoPixel, Barómetro, Telemetria)
- Ajustar a geometria do voo (CICLO_DO_CORACAO_ALADO, ANGULO_DO_PLANAR_SERENO, etc.)
- Ajustar parâmetros de altitude-hold, ferocidade, diferencial de leme
- Configurar pinos e portais dos tendões alados

**Nota sobre a compilação**: O `.cpp` da biblioteca é compilado como uma unidade de tradução separada. Por isso, as `#define` colocadas no sketch `.ino` **não são visíveis** ao código da biblioteca. A configuração deve ser feita exclusivamente no `GralhaAzulConfig.h`, que é incluído por ambos.

### Configuração de pinos (override)

Todas as constantes têm `#ifndef` — se preferir, pode definir o valor **antes** do `#include` no sketch, desde que a biblioteca seja compilada como parte do mesmo projeto (não como biblioteca instalada):

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

## 🦅 Servos Recomendados

| Servo | Torque | Velocidade | Ciclo ideal | Uso |
|-------|--------|------------|-------------|-----|
| Blue Arrow D0576HT MG | 0.05 kg·cm | 0.07s/60° | 0.030s (~33 Hz) | Asa ultraleve, batimento rápido |
| DSSERVO DS3218 MG | 2.5 kg·cm | 0.08s/60° | 0.052s (~19 Hz) | Asa média, padrão Gralha |
| KST MS320 | 8.5 kg·cm | 0.14s/60° | 0.080s (~12 Hz) | Asa grande, alto torque |

Ajuste `CICLO_DO_CORACAO_ALADO` conforme a especificação do servo. Ciclos mais rápidos que o recomendado podem sobreaquecer a bobina em voo contínuo.

---

## 📜 Estrutura do Código

```
src/GralhaAzul.h                    — Header com #define guards
src/GralhaAzul.cpp                  — Implementação completa
examples/CRSF_Exemplo/              — Config CRSF completa (padrão)
examples/PPM_Exemplo/               — Config PPM mínima
examples/CRSF_Servo_Rapido/         — Para servos rápidos (~33 Hz)
examples/CRSF_Servo_Torque/         — Para servos de torque (~12 Hz)
library.properties                  — Metadados Arduino IDE
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