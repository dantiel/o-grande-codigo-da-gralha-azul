# CHANGELOG

## v1.30.26 — Histerese Centrada no Glide
- **Histerese do limiar de voo activo centrada no valor configurado.**
  - `LIMIAR_DO_VOO_ATIVO_PADRAO` (1040) como ponto central: abaixo → glide, acima +50 (1090) → flap.
  - Banda morta de 50 agora equilibrada à volta do limiar, em vez de deslocada para baixo.

## v1.30.25 — Decaimento Configurável no Glide
- **Decaimento do ângulo no glide** em modo normal: `anguloDaDancaAlada *= DECAIMENTO_DA_CADENCIA_SONOLENTA_PADRAO` (default `0.90f`) com epsilon-zero.
  - Substitui snap a zero da v1.30.24 — asas desvanecem suavemente.
- **`LIMIAR_DO_VOO_ATIVO_PADRAO`** agora com guarda `#ifndef` (default `1040`), sobrescritível no sketch.

## v1.30.24 — Reset de Glide: Modo Normal vs Alternativo
- **Reset do ângulo no glide apenas em modo normal.**
  - Normal: `anguloDaDancaAlada = 0` — ciclo recomeça do meio-curso ao retomar o bater.
  - `MODO_DE_VOO_ALTERNATIVO`: ângulo continua a avançar com cadência decrescente — continuidade de fase.

## v1.30.23 — Reset do Batimento ao Entrar em Glide
- **Reset do ângulo de batida ao entrar em glide.**
  - `animarPulsarDoCoracaoAlado()` agora verifica também `modoPresenteDoEspirito`: só avança em `EM_RITMO_DE_BATIDA_DAS_ASAS`.
  - Em `EM_DESLIZE_ETERNO_E_CONTEMPLATIVO`, ângulo = 0 e cadência decai.

## v1.30.22 — Guardião: Detecção de Simultaneidade
- **≥4 canais anómalos no mesmo frame → fantasma colectivo** (frame rejeitado).
  - Ghost frames em pares consecutivos já não enganam a persistência de 2 frames.
  - 1-3 canais anómalos → verificação de persistência individual (stick multi-eixo legítimo).

## v1.30.21 — Guardião: Persistência Temporal
- **Confirmação por 2 frames consecutivos.** Um frame anómalo isolado é fantasma (bloqueado); o mesmo delta sustentado 2 frames é stick legítimo (confirmado).
  - Elimina falsos positivos em movimentos rápidos sem sacrificar rejeição de ghost frames.
  - Latência de 1 frame (4ms) apenas para movimentos >100µs/frame.

## v1.30.20 — Guardião: Rejeição por Canal
- **Cada canal verificado independentemente.** v1.30.19 causava lockout total quando um stick legítimo excedia 100µs/frame.
  - Canal anómalo congela só esse canal — os outros 9 voam.

## v1.30.19 — Guardião: Primeiro Frame Incondicional
- **Corrige lockout do primeiro frame.** v1.30.18 rejeitava o primeiro frame porque deltas contra defaults (1500/1000) excediam 100µs em canais como CH3=1196, CH6=1860.
  - Primeiro frame após link-up aceite incondicionalmente para inicializar referências.
  - `guardiaoInicializado` resetado no failsafe.

## v1.30.18 — Guardião Expandido CH1-10
- **Todos os 10 canais verificados.** v1.30.17 só verificava CH1-4 — ghost frames que corrompiam CH6/CH7/CH8 passavam.
  - CH5 (arm) usa delta 500µs (switch legítimo 1000↔2000).

## v1.30.17 — Guardião contra Fantasmas Eléctricos
- **Filtro de integridade CRSF:** rejeita frames com delta >100µs por canal entre frames consecutivos.
  - Ghost frames que passam CRC-8 (1/256 falsos positivos) são bloqueados.
  - Resolve shaking+freeze causado por EMI de servos de alta corrente no barramento CRSF.

## v1.30.16 — EMA Sincronizado 50Hz
- **Correcção da dessincronização EMA/write** que causava saltos de 10-52 passos entre escritas consecutivas.
  - EMA e write agora correm ambos a 50Hz, eliminando perseguição atrasada.

## v1.30.15 — EMA + Write-on-Change com Cadência
- **Filtro EMA (α=0.3) + write-on-change** com intervalo mínimo 20ms entre escritas (máx. 50 writes/s).
  - Write-on-change puro escrevia ~185-200/s saturado o PIO do RP2040 e causando glitches.

## v1.30.14 — EMA + Write-on-Change
- Filtro passa-baixo EMA (α=0.5) + write-on-change — elimina escritas redundantes ao servo.

## v1.30.3–13 — Diagnóstico e Afinação
- Diagnóstico expandido de servos e canais ([CANAL], [SERVO]).
- Ajuste iterativo de deadband (±1 → ±2 → ±3 → ±5) para absorver oscilação soft-float RP2040.
- Blend linear (±0.1 rad) substitui switch discreto na ferocidade.

## v1.29.2
- Added `MODO_DE_VOO_ALTERNATIVO` — alternative flight control mode
  - CH3 (throttle) → amplitude direct
  - CH9 (vozDaFerocidadeDoLeme) → flapping frequency direct (0→~2.5Hz)
  - Bypasses PI-controlled cadence and throttle-modulated amplitude
  - For testing or manual frequency management preference
- Fixed CH6/CH9 swap for documentation consistency (v1.29.0)
  - CH6 now controls flapping frequency trim (vozDoCompassoDaAlma)
  - CH9 now controls yaw aggressiveness / rudder differential (vozDaFerocidadeDoLeme)
- Combined 8 fixes from v1.29.0-v1.29.1: barometer calibration, div/0 guard, state restore, failsafe, fabs() waveform, fmax() ferocity, fmod() angle

## v1.28.8
- Pure poetic naming: all technical acronyms transmuted
  - GUARDIAO_DOS_VENTOS_SIDERAIS (was RECEPTOR_CRSF)
  - MENSAGEIRO_DOS_CANTOS_COSMICOS (was RECEPTOR_PPM)
  - CHAMA_AZUL_DESLIGADA (was NEOPIXEL_DESLIGADO)
  - ORACULO_DESLIGADO (was BAROMETRO_DESLIGADO)
  - SUSSURRO_DESLIGADO (was TELEMETRIA_DESLIGADO)
  - VIA_DO_SOPRO_COSMICO (was SOPRO_SERIAL)
- Header-only architecture with inline methods
- Example sketches with practical section headers, comment cleanup
- README: corrected installation instructions, poetic defines, telemetry section
- Root .ino: full-featured reference sketch (CRSF + NeoPixel + BMP180 + telemetry)
- ECOS_PRESCINDIVEIS_DA_ALMA_ALADA removed from examples (outdated after refactor)
- CICLO_DO_CORACAO_ALADO comments: clarified relation to amplitude/frequency/scaling
- library.properties updated to 1.28.8

## v1.28.7
- Debug tags transmuted to poetic form: [DESPERTAR], [PULSACAO], [ESTADO], [CANTO], [PRESAGIO]
- GRALHA_TIPO_RECEPTOR removed (dead code)
- Header-only architecture maintained

## v1.28.6
- Comprehensive debug tracing for CRSF initialization and communication

## v1.28.5
- Placement-new buffer guards: only declared when corresponding features enabled

## v1.28.4
- Placement-new with zero-initialization for CrsfSerial, PPMReader, NeoPixel, BMP085

## v1.28.3
- Debug output restored from git history: periodic state every 250ms, channel values, barometer init

## v1.28.2
- Removed tipoReceptor and runtime receiver checks — pure compile-time selection

## v1.28.1
- Crashfix: restored guarded interpretarAsVozesDoFirmamento() in CRSF path
- PPM receiver support corrected

## v1.28.0
- Inicialização Blindada: direct #ifdef for member initialization
- Header-only with empty .cpp
- Include guard restored

## v1.27.x
- Placement-new architecture for external library objects
- ODR-safe header-only design

## v1.26.x
- Bugfix series: double Serial1.begin(), NeoPixel/barometer/telemetry disable

## v1.23.0
- Essência Pura: meta-poetic comments removed, code breathes as direct enchantment
- Class-based architecture with 8 essential fields
- Documentation fully rewritten

## v1.22.0
- Refatoração Poética Completa: all technical terms eliminated
- Pure poetic naming throughout library and sketches

## v1.20.0
- ~40 magic-number fields removed from class
- Macros _PADRAO used directly — ~160 bytes RAM reduction

## v1.17.x
- Wiring diagram fixes, documentation integration
- Configurable flight parameters

## v1.16.0
- Modular library refactoring

## v1.15.1
- Portuguese naming, RP2040 focus with PPM mode

## v0.x (Early Development)
- Initial ornithopter control experiments
- Basic servo flapping algorithms
- CRSF receiver integration