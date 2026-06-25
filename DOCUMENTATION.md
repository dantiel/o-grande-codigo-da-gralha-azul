# Documentation — O Grande Código da Gralha Azul

## Architecture

### File Structure

```
src/GralhaAzulConfig.h   — All tunable parameters (314 lines)
src/GralhaAzul.h         — Extern declarations, enums, MantoDeLuzCelestial class (140 lines)
src/GralhaAzul.cpp       — Wing beat generation, loop orchestration (605 lines)
```

### Execution Flow

`gralhaAzulSetup()` (called once at boot):
1. Initialize NeoPixel (`MantoDeLuzCelestial`)
2. Initialize BMP180 barometer (`DespertarOraculoDaPressao()` — safe on failure)
3. Configure CRSF or PPM input based on `#define RECEPTOR_ALADO`
4. Attach both servos

`gralhaAzulLoop()` (called repeatedly, never blocks):
1. `guardiao.loop()` — parse 12 channels (CRSF) or 8 channels (PPM)
2. `AnimarPulsarDoCoracaoAlado()` — generate sinusoidal wing stroke
3. `ManifestarOVooNosVentos()` — mix RC input with geometry, apply servo angles
4. `MantoDeLuzCelestial.loop()` — NeoPixel animation
5. CRSF telemetry update

Total loop time: ~200–400 µs. No `delay()` calls.

---

## Configuration Reference

All constants are defined in `src/GralhaAzulConfig.h` with `#ifndef` guards, allowing per-model overrides in the sketch.

### Basic Identification

| Constant | Default | Description |
|----------|---------|-------------|
| `NOME_DA_AVE` | `"Gralha Azul"` | Model name for telemetry |
| `NOME_DO_MANTO` | `"Manto de Luz Celestial"` | NeoPixel strip name |
| `FREQUENCIA_DO_SOL_EM_HZ` | `100` | Loop frequency (Hz) |

### Servo Configuration

| Constant | Default | Description |
|----------|---------|-------------|
| `PIN_DO_TENDAO_ESQUERDO` | `0` | Left wing servo pin |
| `PIN_DO_TENDAO_DIREITO` | `1` | Right wing servo pin |
| `CICLO_DO_CORACAO_ALADO` | `0.052f` | Wing beat period (seconds). Servo-specific. See README table. |
| `PULSO_MINIMO_DO_CORACAO` | `500` | Servo minimum pulse (µs) |
| `PULSO_MAXIMO_DO_CORACAO` | `2500` | Servo maximum pulse (µs) |
| `GRAU_MINIMO_DA_ASA` | `0` | Minimum wing angle (degrees) |
| `GRAU_MAXIMO_DA_ASA` | `90` | Maximum wing angle (degrees) |

### Flight Geometry (Sinusoidal Wing Stroke)

| Constant | Default | Description |
|----------|---------|-------------|
| `ANGULO_DE_REPOUSO` | `45.0f` | Mid-stroke angle (degrees). Sets wing amplitude center. |
| `FATOR_DE_AMPLITUDE_ESCALAR` | `1.0f` | Stroke amplitude multiplier. >1 overshoots, <1 reduces. |
| `FASE_DE_ONDULACAO` | `180` | Phase offset between left/right wings (degrees). 180 = symmetric. |
| `PLANADOR_DIVINO` | `0` | Enable glide: servo holds position, no stroke |
| `ANGULO_DO_PLANAR_SERENO` | `-3` | Glide angle offset relative to `ANGULO_DE_REPOUSO` (degrees) |

### RC Channel Mapping

| Constant | Default Channel | Function |
|----------|----------------|----------|
| `CANAL_DO_TENDAO` | 1 | Aileron → wing angle offset |
| `CANAL_DO_CONTROLE` | 2 | Elevator → wing angle offset (orthogonal) |
| `CANAL_DA_MAJESTADE` | 3 | Throttle → wing beat frequency multiplier |
| `CANAL_DO_PLANAR` | 4 | Switch → glide mode toggle. Threshold: `1500` |
| `CANAL_DA_CINTILACAO` | 5 | Switch → NeoPixel animation mode. Step: `250` |

### Receiver Selection

| Constant | Description |
|----------|-------------|
| `RECEPTOR_ALADO` | Define to `1` for CRSF, `0` for PPM. Set in sketch. |

### CRSF Telemetry

| Constant | Default | Description |
|----------|---------|-------------|
| `UART_DO_ORACULO` | `Serial1` | UART for CRSF receiver |
| `TAXA_DE_TRANSMISSAO` | `420000` | Baud rate |
| `PINO_DA_ESCUTA_ORACULAR` | `1` | UART RX pin |
| `PINO_DA_FALA_ORACULAR` | `0` | UART TX pin |
| `BATERIA_MAXIMA` | `8.4f` | Max battery voltage for telemetry (%) |
| `BATERIA_MINIMA` | `6.0f` | Min battery voltage for telemetry (%) |
| `ALTURA_DE_NASCIMENTO` | `100.0f` | Ground altitude (m) for relative altitude telemetry |

### PPM Input

| Constant | Default | Description |
|----------|---------|-------------|
| `PIN_DO_PULSO_ALADO` | `2` | PPM signal pin |
| `SINAL_DE_PAUSA_PPM` | `2000` | PPM frame gap (µs) |
| `NUMERO_DE_CANAIS` | `8` | Number of PPM channels |

### NeoPixel (MantoDeLuzCelestial)

| Constant | Default | Description |
|----------|---------|-------------|
| `PINHO_DO_MANTO` | `7` | NeoPixel data pin |
| `NUMERO_DE_LUZES` | `8` | Number of LEDs |
| `INTENSIDADE_DA_LUZ` | `50` | Brightness (0–255) |
| `MATIZ_DA_LUZ` | `0` | Base hue for animations (0–65535) |

### BMP180 Barometer

| Constant | Default | Description |
|----------|---------|-------------|
| `PORTA_DA_ALTITUDE` | `0x77` | I²C address (0x77 or 0x76) |
| `FREQUENCIA_DA_ESCUTA_DO_VOO` | `10` | Altitude update rate (Hz) |
| `ALTURA_DE_NASCIMENTO_AJUSTE` | `0.0f` | Manual ground offset (m) |

### Altitude Hold

| Constant | Default | Description |
|----------|---------|-------------|
| `ALTURA_DE_DESEJO` | `15.0f` | Target altitude (m) |
| `GANHO_DA_ALTITUDE` | `4.0f` | P-gain for altitude correction |
| `INTENSIDADE_DO_PLANADOR` | `0.0f` | Glide intensity floor for altitude hold |
| `TETO_MAXIMO` | `50.0f` | Maximum altitude limit (m) |

### Debug & Health

| Constant | Default | Description |
|----------|---------|-------------|
| `FREQUENCIA_DO_ORACULO` | `1` | Telemetry/serial update rate (Hz) |
| `SERIAL_DA_VERDADE` | `Serial` | Debug serial port |
| `TAXA_DA_VERDADE` | `115200` | Debug baud rate |
| `INTERVALO_DE_SAUDE` | `500` | Health check interval (ms) |
| `FREQUENCIA_DA_SAUDE` | `10` | Health packet rate (Hz) |

---

## Per-Model Configuration Guide

To create a custom model, copy one of the examples and override constants in your sketch:

```cpp
#define NOME_DA_AIVE "My Ornithopter"
#define CICLO_DO_CORACAO_ALADO 0.080f  // KST MS320 (12 Hz)
#define ANGULO_DO_PLANAR_SERENO -2
#define RECEPTOR_ALADO 1  // CRSF
```

Place these `#define` lines **before** `#include "src/GralhaAzul.h"`. The `#ifndef` guards in `GralhaAzulConfig.h` will respect them.

---

## Channel Mapping (CRSF)

| Channel | CRSF Index | Function | Typical Transmitter |
|---------|------------|----------|---------------------|
| 1 | 0 | Aileron (wing roll offset) | Right stick X |
| 2 | 1 | Elevator (wing pitch offset) | Right stick Y |
| 3 | 2 | Throttle (beat frequency) | Left stick X |
| 4 | 3 | Glide toggle | Switch A (2-pos) |
| 5 | 4 | NeoPixel animation mode | Switch B (multi-pos) |

CRSF telemetry sensors (when enabled):
- **VFAS** — battery voltage (%, mapped from BATERIA_MINIMA to BATERIA_MAXIMA)
- **ALT** — relative altitude (m)
- **TEMP** — temperature (°C × 10)

---

## Hardware Requirements

- **MCU**: RP2040 (Raspberry Pi Pico or compatible)
- **Servos**: 2× standard or micro servo (see README for torque/frequency specs)
- **Receiver**: ExpressLRS CRSF or PPM-compatible
- **Optional**: NeoPixel strip (WS2812B), BMP180 barometer

### Pinout Reference

```
GP0  — Right wing servo (PWM)
GP1  — Left wing servo (PWM)
GP2  — PPM input (if RECEPTOR_ALADO = 0)
GP7  — NeoPixel data (if MANTO_DE_LUZ_CELESTIAL defined)
GP16/17 — CRSF UART (TX/RX, if RECEPTOR_ALADO = 1)
I²C  — BMP180 (SDA/SCL, if ORACULO_DA_ALTITUDE defined)
```

---

## Performance Characteristics

| Metric | Value |
|--------|-------|
| Loop time (idle) | ~200 µs |
| Loop time (all features) | ~400 µs |
| Frequency | 100 Hz (configurable) |
| Flash usage | ~30 kB (RP2040) |
| RAM usage | ~8 kB |
| No `delay()` | ✅ all waits use `millis()` timers |
| No floating point in ISR | ✅ all FP in main loop |

---

## Safety Protections

1. **Servo pulse clamping** — `PULSO_MINIMO_DO_CORACAO` / `PULSO_MAXIMO_DO_CORACAO` enforced
2. **Angle clamping** — `GRAU_MINIMO_DA_ASA` / `GRAU_MAXIMO_DA_ASA` enforced
3. **CRSF link loss** — servo hold on last position, timer resets after 1 second
4. **BMP180 failure** — altitude hold gracefully disables, flight continues
5. **No `delay()`** — loop never blocks, failsafe always reachable
6. **NeoPixel timeout** — 100 ms max per frame, no animation stalls the loop
