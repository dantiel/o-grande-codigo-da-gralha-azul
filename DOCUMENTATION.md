# DOCUMENTAÇÃO — O Grande Código da Gralha Azul

## Visão Geral

**O Grande Código da Gralha Azul** é uma biblioteca para microcontroladores RP2040 (Raspberry Pi Pico, Waveshare RP2040 Zero, etc.) que controla **ornitópteros** — criaturas mecânicas que batem asas e dançam com os ventos. A biblioteca gerencia:

- Recepção por **CRSF** (Crossfire) ou **PPM** (PWM por quadro)
- **Servos de asa** com temporização precisa (ciclo ajustável por modelo)
- **Barómetro BMP180** para altitude hold (opcional)
- **NeoPixel** para a chama azul pulsante (opcional)
- **Telemetria** CRSF (opcional)
- Modos de voo: planar sereno (glide), dança com os ventos (batimento ativo), sustentar (altitude hold)

A arquitetura é modular: cada componente pode ser desligado via `#define` no arquivo central de configuração. O código habita em três camadas — **configuração**, **declaração**, **implementação** — cada uma com o seu propósito e a sua poesia.

---

## Estrutura de Arquivos

```
o-grande-codigo-da-gralha-azul/
├── src/
│   ├── GralhaAzulConfig.h   (314 linhas — grimório centralizado, todos os parâmetros com #ifndef)
│   ├── GralhaAzul.h         (140 linhas — invocação da alma alada, declarações extern, classe MantoDeLuzCelestial)
│   └── GralhaAzul.cpp       (605 linhas — a dança alada em código, implementação completa)
├── examples/
│   ├── CRSF_Exemplo/        (CRSF completo: NeoPixel + BMP180 + Telemetria, DSSERVO DS3218 MG, ~19 Hz)
│   ├── PPM_Exemplo/         (PPM mínimo: 8 canais, CH9/CH10 fixos, ~19 Hz)
│   ├── CRSF_Servo_Rapido/   (Blue Arrow D0576HT MG, 1.7g, ~33 Hz, ultra-leve)
│   └── CRSF_Servo_Torque/   (KST MS320, 56g, 8.5kg·cm, ~12 Hz)
├── DOCUMENTATION.md         (este arquivo — a inscrição técnica do magnum opus)
├── MIGRATION_GUIDE.md       (guia para migrar do monolítico para a biblioteca)
├── README.md                (138 linhas — a introdução poética e prática)
├── CHANGELOG.md             (o histórico das eras — todas as versões)
├── library.properties       (metadados para Arduino IDE)
└── o-grande-codigo-da-gralha-azul.ino (sketch principal, compatibilidade com Arduino IDE)
```

---

## Arquitetura Interna

### Fluxo de Execução

```
O Despertar — gralhaAzulSetup()
  ├── MantoDeLuzCelestial::AcenderLuzPrimordial()  [NeoPixel, se ativo]
  ├── DespertarOraculoDaPressao()                   [BMP180, se ativo]
  ├── AoDespertarParaOCantoDoEter()                 [callback CRSF/PPM]
  ├── Serial.begin(115200)                          [debug, se ECOS_PRESCINDIVEIS ativo]
  ├── CRSF: Serial1.begin(420000), registra callbacks onLinkUp/onLinkDown/onPacketChannels
  │   └── PPM: PPMReader no GPIO2, registra callbacks onConnect/onDisconnect/onNewData
  └── Servo.attach() nos pinos ARTICULACAO_ASA_DA_MANHA/ASA_DO_ENTARDECER

O Ciclo Eterno — gralhaAzulLoop()  [executado a cada ~10ms]
  ├── CRSF/PPM: guardiao.loop() / mensageiro.loop()
  ├── AnimarPulsarDoCoracaoAlado()
  │     ├── Estado = EM_DANCA_COM_OS_VENTOS?
  │     │   ├── SIM: calcula angulo_da_danca_alada (senoide), cadencia ajustável por CH3+CH6
  │     │   └── NÃO: decai cadencia, angulo = 0
  │     └── dt limitado a DT_MAXIMO_DO_SONHO (0.05s) para evitar saltos
  ├── EscutarPressaoDoCeu()                          [BMP180, se ativo, a cada 200ms]
  ├── SustentarAltura()                              [se CH10 > 1% e barómetro ativo]
  │     ├── Calcula ganho_do_sustentar (0..1) de CH10
  │     ├── Calcula altura_desejada (0..20m) de CH3
  │     ├── Erro → sopro_vital_do_sustentar (correção PID-simplificada)
  │     └── Zona morta: SILENCIO_DO_SUSTENTAR_M (0.5m)
  ├── ManifestarOVooNosVentos()
  │     ├── Modo RITMADO: forma_do_bater_das_asas() com ferocidade diferencial (CH9)
  │     ├── Modo PLANAR: ANGULO_DO_PLANAR_SERENO fixo
  │     └── Servo.write() com constrain(0, 180)
  ├── SussurrarVooAoEter()                           [CRSF + telemetria ativa]
  │     ├── GPS frame: altitude, velocidade vertical (a cada 200ms)
  │     └── Battery frame: temperatura como voltage (a cada 500ms)
  ├── MantoDeLuzCelestial::IrradiarLuzDaAlma()       [NeoPixel, se ativo, a cada 33ms]
  └── Serial debug (a cada 250ms, se ECOS_PRESCINDIVEIS ativo)
```

### Módulos Opcionais (Compile-Time)

| Guarda | Efeito | Linhas removidas |
|--------|--------|-----------------|
| `GRALHA_AZUL_NEOPIXEL_DESLIGADO` | Remove todo o código NeoPixel (classe `MantoDeLuzCelestial`, chamadas) | ~120 |
| `GRALHA_AZUL_BAROMETRO_DESLIGADO` | Remove BMP180, altitude hold, leituras de pressão/temperatura | ~100 |
| `GRALHA_AZUL_TELEMETRIA_DESLIGADO` | Remove telemetria CRSF (GPS + battery frames) | ~50 |

Os guards usam `#ifndef` — para desligar, defina **antes** do `#include <GralhaAzul.h>`:

```cpp
#define GRALHA_AZUL_NEOPIXEL_DESLIGADO
#define GRALHA_AZUL_BAROMETRO_DESLIGADO
#include <GralhaAzul.h>
```

---

## API de Configuração (GralhaAzulConfig.h)

Todas as constantes usam `#ifndef` — podem ser sobrescritas por `#define` antes do include, por `-D` no compilador, ou pelo valor padrão no config header.

### Módulos e Receptor

| Constante | Valores | Padrão | Descrição |
|-----------|---------|--------|-----------|
| `ECOS_PRESCINDIVEIS_DA_ALMA_ALADA` | definir/não definir | não definido | Ativa Serial debug (115200 baud) |
| `RECEPTOR_DOS_VENTOS_CRSF` | definir/não definir | definido (se nem CRSF nem PPM) | Usa CRSF via Serial1 |
| `RECEPTOR_DOS_VENTOS_PPM` | definir/não definir | não definido (se CRSF ativo) | Usa PPM via GPIO2 |

### Pinos e Portais

| Constante | Padrão | Descrição |
|-----------|--------|-----------|
| `ARTICULACAO_ASA_DA_MANHA` | 8 | Servo asa esquerda (PWM) |
| `ARTICULACAO_ASA_DO_ENTARDECER` | 7 | Servo asa direita (PWM) |
| `VIA_DOS_SONHOS_LUNARES` | 1 | RX CRSF (Serial1) |
| `VIA_DOS_ECOS_SOLARES` | 0 | TX CRSF (Serial1) |
| `NUCLEO_DA_CHAMA_AZUL` | 16 | NeoPixel (GPIO) |
| `QUANTIDADE_DE_CENTELHAS_NA_CHAMA` | 1 | Número de NeoPixels |
| `PINO_SILENCIO_DA_ALTURA` | 4 | SDA (I2C para BMP180) |
| `PINO_RITMO_DA_PRESSAO` | 5 | SCL (I2C para BMP180) |
| `PINO_DO_MENSAGEIRO` | 2 | PPM input |
| `NUM_CANAIS_DO_MENSAGEIRO` | 8 | Número de canais PPM |

### Geometria do Voo

| Constante | Padrão | Descrição |
|-----------|--------|-----------|
| `CICLO_DO_CORACAO_ALADO` | `0.052f` | Período do ciclo de asa em segundos (~19 Hz) |
| `LIMIAR_DO_VOO_ATIVO` | `1040` | Limiar para entrar em modo batimento (us) |
| `LIMIAR_DO_VOO_ATIVO_HISTERESE` | `20` | Histerese para evitar oscilação (us) |
| `ANGULO_DO_PLANAR_SERENO` | `-4` | Ângulo de glide (graus, negativo = planar descendente) |
| `ORIGEM_ASA_MATUTINA` | `0` | Offset neutro da asa esquerda (graus) |
| `ORIGEM_ASA_VESPERTINA` | `0` | Offset neutro da asa direita (graus) |

### Vibrações dos Canais (valores padrão quando sem sinal)

| Constante | Padrão | Canal |
|-----------|--------|-------|
| `VIBRACAO_NEUTRA_DO_ALETAO` | 1500 | CH1 |
| `VIBRACAO_NEUTRA_DO_PROFUNDOR` | 1500 | CH2 |
| `VIBRACAO_MINIMA_DO_SOPRO_VITAL` | 1000 | CH3 |
| `VIBRACAO_NEUTRA_DO_LEME_ESTELAR` | 1500 | CH4 |
| `VIBRACAO_NEUTRA_DO_COMPASSO_DA_ALMA` | 1500 | CH6 |
| `VIBRACAO_DO_DESPERTAR_DESARMADO` | 1000 | CH5 |
| `VIBRACAO_MINIMA_DA_FEROCIDADE` | 1000 | CH7, CH8, CH9 |
| `VIBRACAO_MINIMA_DO_SUSTENTAR_ALTURA` | 1000 | CH10 |

### Altitude Hold (só quando barómetro ativo)

| Constante | Padrão | Descrição |
|-----------|--------|-----------|
| `ALTURA_MAX_DO_SUSTENTAR_M` | `20.0f` | Altitude máxima do setpoint (CH3=2000 → 20m) |
| `SOPRO_MIN_DO_SUSTENTAR` | `1100` | Limite inferior da correção de throttle |
| `SOPRO_MAX_DO_SUSTENTAR` | `1800` | Limite superior da correção de throttle |
| `FORCA_BASE_DO_SUSTENTAR` | `180` | Ganho proporcional da correção (us/m) |
| `SILENCIO_DO_SUSTENTAR_M` | `0.5f` | Zona morta em metros |
| `GANHO_LIMIAR_SUSTENTAR` | `0.01f` | Ganho mínimo para ativar (CH10 > 1%) |
| `LIMITE_DA_DESCIDA_SUSTENTADA_MS` | `2.0f` | Limite de descida para correção (m/s) |
| `LIMITE_DA_SUBIDA_SUSTENTADA_MS` | `3.0f` | Limite de subida para correção (m/s) |
| `CORRECAO_TAXA_LIMITE_SUSTENTAR` | `10.0f` | Correção quando excede limite de subida/descida |
| `REFERENCIA_DA_PRESSAO_HPA` | `1013.25f` | Pressão de referência ao nível do mar |

### Parâmetros dos Servos

| Constante | Padrão | Descrição |
|-----------|--------|-----------|
| `PULSO_MINIMO_SERVO` | `500` | Pulso mínimo do servo (us) |
| `PULSO_MAXIMO_SERVO` | `2500` | Pulso máximo do servo (us) |

### Dança Secreta dos Ventos (parâmetros da coreografia alada)

| Constante | Padrão | Descrição |
|-----------|--------|-----------|
| `ESCALA_ANGULAR_DA_ARTICULACAO` | `0.06f` | Escala do roll para ângulo do servo |
| `ESCALA_ANGULAR_DO_PROFUNDOR` | `0.06f` | Escala do pitch para ângulo do servo |
| `MAGNITUDE_ESCALA_DA_FEROCIDADE` | `0.06f` | Escala da ferocidade para amplitude |
| `MODULACAO_DO_COMPASSO` | `0.0003f` | Modulação do compasso na amplitude |
| `MULTIPLICADOR_FINAL_ANGULAR` | `2.0f` | Ganho final dos ângulos dos servos |
| `OFFSET_ANGULAR_NEUTRO` | `100` | Offset para centrar servos (graus*multiplicador) |
| `FEROCIDADE_MINIMA` | `1.0f` | Ferocidade mínima (CH7/CH8=1000) |
| `FEROCIDADE_MAXIMA` | `8.0f` | Ferocidade máxima (CH7/CH8=2000) |
| `DIFERENCIAL_LEME_MIN` | `-4.0f` | Diferencial mínimo (CH9=1000) |
| `DIFERENCIAL_LEME_MAX` | `4.0f` | Diferencial máximo (CH9=2000) |
| `EPSILON_FORMA_BATER` | `0.001f` | Proteção contra divisão por zero na forma de bater |
| `LIMITE_FORMA_BATER` | `1.5f` | Limite do resultado da forma de bater |
| `ACELERACAO_DO_COMPASSO` | `8.0f` | Aceleração da cadência (resposta a mudanças de frequência) |
| `MULTIPLICADOR_MINIMO_FREQUENCIA` | `0.5f` | Frequência mínima (fração do ciclo base) |
| `PESO_DO_SOPRO_NA_FREQUENCIA` | `0.5f` | Peso do CH3 na frequência alvo |
| `PESO_DO_COMPASSO_NA_FREQUENCIA` | `0.3f` | Peso do CH6 na frequência alvo |
| `DECAIMENTO_DA_CADENCIA_SONOLENTA` | `0.90f` | Fator de decaimento quando em repouso |
| `EPSILON_CADENCIA_ZERO` | `0.001f` | Limiar para considerar cadência zero |
| `DT_MAXIMO_DO_SONHO` | `0.05f` | dt máximo (50ms) para evitar saltos temporais |
| `LIMITE_ANGULAR_DO_GIRO` | `20π` | Limite do ângulo acumulado antes de wrap |

### Temporização

| Constante | Padrão | Descrição |
|-----------|--------|-----------|
| `INTERVALO_NEO_PIXEL_MS` | `33` | Intervalo entre atualizações NeoPixel (~30 fps) |
| `INTERVALO_SERIAL_DEBUG_MS` | `250` | Intervalo entre prints de debug |
| `BAUDRATE_SERIAL` | `115200` | Baud rate da Serial (debug) |
| `TEMPO_ESPERA_USB_MS` | `4000` | Tempo máximo para aguardar Serial USB |
| `INTERVALO_LEITURA_BAROMETRO_MS` | `200` | Intervalo entre leituras BMP180 (5 Hz) |
| `AMOSTRAS_CALIBRACAO_BAROMETRO` | `10` | Amostras para calibração inicial |
| `ATRASO_CALIBRACAO_BAROMETRO_MS` | `50` | Atraso entre amostras de calibração |
| `SALTOS_CICLO_TEMPERATURA` | `5` | Leituras de pressão entre leituras de temperatura |
| `MINIMO_DT_SEGUNDOS` | `0.001f` | dt mínimo para evitar divisão por zero |

### Filtros

| Constante | Padrão | Descrição |
|-----------|--------|-----------|
| `SUAVIZACAO_TEMPERATURA` | `0.5f` | Fator de suavização da temperatura |
| `FILTRO_TENDENCIA_TEMPERATURA` | `0.9f` | Fator do filtro de tendência |
| `PESO_TENDENCIA_TEMPERATURA` | `0.1f` | Peso da tendência |
| `PESO_VELOCIDADE_VERTICAL_ATUAL` | `0.7f` | Peso da velocidade vertical atual |
| `PESO_VELOCIDADE_VERTICAL_ANTERIOR` | `0.3f` | Peso da velocidade vertical anterior |
| `PESO_CONFIANCA_TERMICA_TEMPERATURA` | `0.3f` | Peso da temperatura na confiança térmica |
| `LIMIAR_CONFIANCA_TERMICA` | `0.5f` | Limiar para ativar modo de escuta termal |

### Telemetria (só CRSF)

| Constante | Padrão | Descrição |
|-----------|--------|-----------|
| `INTERVALO_TELEMETRIA_GPS_MS` | `200` | Intervalo entre frames GPS |
| `INTERVALO_TELEMETRIA_TEMPERATURA_MS` | `500` | Intervalo entre frames battery (temperatura) |
| `FATOR_CONVERSAO_VELOCIDADE` | `36.0f` | Conversão m/s → cm/s × 10 |
| `OFFSET_ALTITUDE_CRSF` | `1000.0f` | Offset para altitude CRSF (evitar negativos) |
| `ESCALA_TEMPERATURA_CRSF` | `100.0f` | Escala para temperatura CRSF (ºC → centésimos) |

### Fórmula Barométrica

| Constante | Padrão | Descrição |
|-----------|--------|-----------|
| `EXPONENTE_FORMULA_BAROMETRICA` | `0.190284f` | Expoente da fórmula barométrica |
| `CONSTANTE_FORMULA_BAROMETRICA` | `44307.69f` | Constante da fórmula barométrica |

---

## Exemplos

### CRSF_Exemplo

Configuração CRSF completa para servos padrão (~19 Hz). Ativa todos os módulos:
- CRSF via Serial1 (GP0/GP1)
- NeoPixel (GP16)
- BMP180 (I2C, GP4/GP5)
- Telemetria CRSF
- CICLO_DO_CORACAO_ALADO = 0.052f (~19 Hz, DSSERVO DS3218 MG)
- ANGULO_DO_PLANAR_SERENO = -4

### PPM_Exemplo

Configuração PPM mínima para 8 canais:
- PPM via GPIO2
- CH9 = 1000 (fixo, sem diferencial de leme)
- CH10 = 1000 (fixo, sem altitude hold)
- NeoPixel e BMP180 opcionais
- CICLO_DO_CORACAO_ALADO = 0.052f (~19 Hz)
- ANGULO_DO_PLANAR_SERENO = -3

### CRSF_Servo_Rapido

Para servos ultrarrápidos como Blue Arrow D0576HT MG (1.7g, 0.07s/60°):
- CICLO_DO_CORACAO_ALADO = 0.030f (~33 Hz)
- ANGULO_DO_PLANAR_SERENO = -1
- Todos os módulos desligados (NeoPixel, barómetro, telemetria)
- FEROCIDADE_MAXIMA = 10.0f
- Ideal para asas ultraleves e batimento frenético

### CRSF_Servo_Torque

Para servos de alto torque como KST MS320 (56g, 0.14s/60° a 8.4V, 8.5kg·cm):
- CICLO_DO_CORACAO_ALADO = 0.080f (~12 Hz)
- ANGULO_DO_PLANAR_SERENO = -2
- NeoPixel ativo, barómetro e telemetria desligados
- FEROCIDADE_MAXIMA = 5.0f
- Ideal para ornitópteros de 1m+ de envergadura

---

## Deploy

### Pré-requisitos

- Arduino IDE (2.x+) ou PlatformIO
- Placa RP2040 (Waveshare RP2040 Zero, Raspberry Pi Pico, etc.)
- Núcleo RP2040 instalado (Raspberry Pi Pico/RP2040 by Earle F. Philhower)
- Bibliotecas (via Arduino Library Manager):
  - `CRSF` by Sam4uk (0.1.0)
  - `Adafruit NeoPixel` (1.15.5+)
  - `Adafruit BMP085 Unified` (1.1.3+)
  - `Adafruit Unified Sensor` (1.1.15+)
  - `PPMReaderRP2040` by Dantiel (se usar PPM)

### Instalação como Biblioteca

```bash
cp -r o-grande-codigo-da-gralha-azul ~/Arduino/libraries/GralhaAzul
```

Depois, em qualquer sketch:
```cpp
#include <GralhaAzul.h>

void setup() { gralhaAzulSetup(); }
void loop()  { gralhaAzulLoop(); }
```

### Compilação Direta (sem instalar)

Basta abrir `o-grande-codigo-da-gralha-azul.ino` no Arduino IDE. Os arquivos em `src/` são compilados automaticamente.

### Seleção do Exemplo

1. **Abra** `File → Examples → GralhaAzul → CRSF_Exemplo` (após instalar a biblioteca)
2. **Ou** navegue até `examples/CRSF_Exemplo/CRSF_Exemplo.ino`
3. **Selecione a placa**: Tools → Board → Raspberry Pi RP2040 → Waveshare RP2040 Zero (ou a sua)
4. **Compile e envie**

### Seleção de Receptor

No arquivo `src/GralhaAzulConfig.h`, descomente:
```cpp
#define RECEPTOR_DOS_VENTOS_PPM
```

Ou defina no sketch antes do include:
```cpp
#define RECEPTOR_DOS_VENTOS_PPM
#include <GralhaAzul.h>
```

### Ajuste de Servo (CICLO_DO_CORACAO_ALADO)

O parâmetro mais crítico. Escolha conforme o servo:

| Servo | Frequência Máxima | Ciclo Seguro | Exemplo |
|-------|-------------------|--------------|---------|
| Blue Arrow D0576HT MG (1.7g) | 50 Hz | 0.030f (~33 Hz) | CRSF_Servo_Rapido |
| DSSERVO DS3218 MG (25g) | 25 Hz | 0.052f (~19 Hz) | CRSF_Exemplo, PPM_Exemplo |
| KST MS320 (56g) | 15 Hz | 0.080f (~12 Hz) | CRSF_Servo_Torque |

⚠️ **Aviso**: Ciclos mais rápidos que o mínimo do servo causam sobreaquecimento da bobina, perda de torque e falha mecânica em voo contínuo.

---

## Mapeamento de Canais

| Canal | Nome Hermético | Função | CRSF | PPM (8ch) |
|-------|---------------|--------|------|-----------|
| CH1 | `voz_do_aletao` | Roll (aileron) | ✅ | ✅ |
| CH2 | `voz_do_profundor` | Pitch (elevator) | ✅ | ✅ |
| CH3 | `voz_do_sopro_vital` | Throttle / Altitude setpoint | ✅ | ✅ |
| CH4 | `voz_do_leme_estelar` | Yaw (rudder) | ✅ | ✅ (não usado) |
| CH5 | `voz_do_despertar` | Arm (>1500) | ✅ | ✅ |
| CH6 | `voz_do_compasso_da_alma` | Wingbeat compass | ✅ | ✅ |
| CH7 | `voz_da_ferocidade_do_bater` | Downstroke ferocity | ✅ | ✅ |
| CH8 | `voz_da_ferocidade_do_retorno` | Upstroke ferocity | ✅ | ✅ |
| CH9 | `voz_da_ferocidade_do_leme` | Rudder differential (-4..+4) | ✅ | ❌ (fixo=1000) |
| CH10 | `voz_do_sustentar_altura` | Altitude hold gain (0-100%) | ✅ | ❌ (fixo=1000) |

---

## Segurança

### Validações Implementadas

| Risco | Proteção |
|-------|----------|
| Divisão por zero | `EPSILON_FORMA_BATER` (0.001f) protege `tanh(ferocidade)` — retorna canto original se muito pequeno |
| Overflow de servo | `constrain(angulo, 0, 180)` em todas as escritas |
| CH3/CH10 sem sinal | `VIBRACAO_MINIMA_DO_SOPRO_VITAL` = 1000 (mínimo seguro) |
| CRSF link loss | `onLinkDown` → `AoRecolherSeAoSilencioDaMata()` → estado = EM_SONHO, cadência = 0 |
| I2C ausente | `bmp.begin()` verificado; se falha, `oraculo_respira = false` e degradação graciosa |
| Loop blocking | Nenhum `delay()` durante o voo; barómetro lido a cada 200ms (~4.5ms blocking = 2.25% overhead) |
| Acumulação angular | `LIMITE_ANGULAR_DO_GIRO` (20π) wrap a cada ~10 ciclos |
| dt excessivo | `DT_MAXIMO_DO_SONHO` (0.05s) limita delta temporal após pausas |

### Verificações de Compilação

- Todos os 21 `extern` no header têm definição correspondente no `.cpp`
- `library.properties` version = 1.17.0 (consistente com CHANGELOG)

---

## Performance

Medições estimadas para RP2040 @ 133 MHz:

| Operação | Tempo | Frequência | Overhead |
|----------|-------|------------|----------|
| CRSF loop() | ~50µs | 420000 baud | <1% |
| AnimarPulsarDoCoracaoAlado() | ~30µs | cada loop | <0.5% |
| ManifestarOVooNosVentos() | ~40µs (modo batida) / ~20µs (modo planar) | cada loop | <0.5% |
| EscutarPressaoDoCeu() | ~4.5ms | a cada 200ms | 2.25% |
| IrradiarLuzDaAlma() | ~300µs | a cada 33ms | ~1% |
| SussurrarVooAoEter() | ~100µs | a cada 200ms | <0.5% |
| Serial debug | ~1ms | a cada 250ms | ~0.4% |
| **Total (sem debug)** | **~200-300µs por loop** | **loop ~10ms** | **<5% CPU** |

---

## Troubleshooting

| Problema | Causa Provável | Solução |
|----------|---------------|---------|
| Servo não se move | Pino errado ou `attach()` não chamado | Verifique `ARTICULACAO_ASA_DA_MANHA` e `ASA_DO_ENTARDECER` |
| Asa vibra sem bater | `CICLO_DO_CORACAO_ALADO` muito pequeno | Aumente para 0.080f e teste |
| Altitude hold não ativa | BMP180 não encontrado | Verifique I2C (GP4/GP5) e alimentação 3.3V |
| NeoPixel apagado | `GRALHA_AZUL_NEOPIXEL_DESLIGADO` definido | Remova o define |
| CRSF sem resposta | Serial errada ou baud rate | CRSF usa Serial1 (GP0 TX, GP1 RX) a 420000 baud |
| Telemetria não aparece | CRSF_ADDRESS errado ou frame incorreto | Verifique `CRSF_ADDRESS_FLIGHT_CONTROLLER` |
| Compilação falha: biblioteca não encontrada | Sketch não está na estrutura correta | Use caminho relativo `../../src/GralhaAzul.h` |
| Linker error: undefined reference | Extern sem definição | Certifique-se de que `GralhaAzul.cpp` está a ser compilado |
| WARNING: `pulsacao_da_chama_primordial` redefinida | Versão antiga com extern redundante | Use v1.17.0+ (extern removido) |

---

## Manutenção

### Adicionar um Novo Parâmetro Configurável

1. Adicione o `#ifndef` / `#define` em `GralhaAzulConfig.h`
2. Declare o `extern` em `GralhaAzul.h` (apenas se for variável global)
3. Defina a variável em `GralhaAzul.cpp`
4. Documente no README.md e DOCUMENTATION.md

### Adicionar um Novo Exemplo

1. Crie `examples/NovoExemplo/NovoExemplo.ino`
2. Inclua `../../src/GralhaAzul.h`
3. Chame `gralhaAzulSetup()` e `gralhaAzulLoop()`
4. Documente em README.md a árvore de exemplos

### Release Checklist

- [ ] Version bump em `library.properties` e `CHANGELOG.md`
- [ ] Todos os `extern` verificados contra definições no `.cpp`
- [ ] `grep -n "extern" src/GralhaAzul.h` vs `src/GralhaAzul.cpp`
- [ ] Nenhum separador `====` fora do CHANGELOG
- [ ] Exemplos compilam (verificação manual no Arduino IDE)
- [ ] README.md atualizado com novos exemplos/seções
- [ ] DOCUMENTATION.md atualizado com novos parâmetros
- [ ] Aegis notes purged (remover notas de versões antigas)

---

## Licença

MIT — A Gralha Azul é livre para voar por todos os céus.

---

*«E assim, o Grande Código da Gralha Azul se manifesta, em cada ciclo, um testemunho alado da resiliência da vida, da magia da transformação, e da perene esperança semeada entre o céu e a terra.»*
