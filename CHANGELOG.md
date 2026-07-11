# CHANGELOG

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