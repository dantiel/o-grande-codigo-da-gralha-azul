# O Grande Código da Gralha Azul

**The Great Code of the Azure Jay** — CRSF/PPM servo ornithopter library for RP2040 (Raspberry Pi Pico / Zero).

A C++ library for RP2040-based ornithopters (flapping-wing aircraft) that controls servos, reads CRSF/PPM receivers, manages NeoPixel lighting, and streams telemetry.

## Quick Start

### 1. Install the Library

Copy the `o-grande-codigo-da-gralha-azul` folder to your Arduino libraries directory.

### 2. Wire Your Hardware

### CRSF Receiver (ExpressLRS)

```
RP2040 Zero              ELRS Receiver
═══════════════════════════════════════          ═══════════════════════════════════════
║ GPIO 0 (TX) ════════════════════════════════════ RX               ║  (yellow wire)
║ GPIO 1 (RX) ════════════════════════════════════ TX               ║  (white/blue wire)
║             ║          ║                        ║
║ 3.3V       ═══════════════════════════════════════ VCC (3.3V)     ║
║ GND        ════════════════════════════════════════ GND              ║
═══════════════════════════════════════          ═══════════════════════════════════════
```

**Important:** Some ELRS receivers operate at 3.3V, others at 5V. Check your receiver's specifications. The RP2040 Zero's 3.3V output is sufficient for 3.3V receivers. For 5V receivers, power VCC from the external BEC/battery (same source as servos).

### Servos (External Power)

```
External 5V BEC / Battery
═══════════════════════════════════════════════════════════════════════════
║ 5V+ ═══════════════════════════════════════════════════ Servo Power (red wires, both servos)
║ GND ═══════════════════════════════════════════════════ Servo GND (black/brown wires, both servos)
║                     ║   AND ═══════════ RP2040 GND (common ground!)
═══════════════════════════════════════════════════════════════════════════

RP2040 Zero              Servo Left Wing (GPIO 8)
═══════════════════════════════════════          ═══════════════════════════════════════
║ GPIO 8      ═════════════════════════════════════ Signal (white/yellow)
═══════════════════════════════════════          ═══════════════════════════════════════

RP2040 Zero              Servo Right Wing (GPIO 7)
═══════════════════════════════════════          ═══════════════════════════════════════
║ GPIO 7      ═════════════════════════════════════ Signal (white/yellow)
═══════════════════════════════════════          ═══════════════════════════════════════
```

**Critical:** Servos draw significant current. The RP2040's internal regulator cannot supply this. Always use an external BEC or battery for servo power. Connect **all grounds** (RP2040, servos, receiver, BEC) together.

### NeoPixel — Internal LED (Optional)

The RP2040 Zero has a **built-in NeoPixel (WS2812B)** on GPIO 16. No external wiring is needed.

### BMP180 Barometer (Optional)

```
BMP180 Module            RP2040 Zero
═══════════════════════════════════════        ═══════════════════════════════════════
║ VCC          ═══════════════════════════════════ 3V3           ║
║ GND          ═══════════════════════════════════ GND           ║
║ SDA (GP4)    ═══════════════════════════════════ GPIO 4        ║  (I2C0 SDA)
║ SCL (GP5)    ═══════════════════════════════════ GPIO 5        ║  (I2C0 SCL)
═══════════════════════════════════════        ═══════════════════════════════════════
```

**Enabled by:** `#define ORACULO_DA_PRESSAO_DO_CEU` at the top of the sketch. Without this define, no barometer libraries are required.

**Pin Allocation:**

| Pin    | Function                | Macro                          |
|--------|-------------------------|--------------------------------|
| GPIO 8 | Servo — Left Wing       | `ARTICULACAO_DA_ASA_MATUTINA`  |
| GPIO 7 | Servo — Right Wing      | `ARTICULACAO_DA_ASA_VESPERTINA` |
| GPIO 0 | CRSF TX                 | `VIA_DOS_ECOS_SOLARES`         |
| GPIO 1 | CRSF RX                 | `VIA_DOS_SONHOS_LUNARES`       |
| GPIO 16| NeoPixel (onboard)      | `NUCLEO_DA_CHAMA_AZUL`         |
| GPIO 4 | BMP180 SDA              | `SILENCIO_DA_ALTURA`           |
| GPIO 5 | BMP180 SCL              | `RITMO_DA_PRESSAO`             |

> **Note**: GPIO 5 serves double duty (BMP180 SCL) only if barometer is enabled. Ensure no conflict if using both.

### 3. Create Your Model Sketch

```cpp
// ─── Configuration ────────────────────────────────────────────────
#define ARTICULACAO_DA_ASA_MATUTINA   8
#define ARTICULACAO_DA_ASA_VESPERTINA 7
#define CICLO_DO_CORACAO_ALADO        0.065f

// ─── Optional Features ────────────────────────────────────────────
// #define BAROMETRO_DESLIGADO
// #define TELEMETRIA_DESLIGADO
// #define NEOPIXEL_DESLIGADO

// ─── Debug ──────────────────────────────────────────────────────────
#define ECOS_PRESCINDIVEIS_DA_ALMA_ALADA

// ─── Includes ───────────────────────────────────────────────────────
#include <GralhaAzul.h>

// ─── Instance ─────────────────────────────────────────────────────
GralhaAzul gralha;

// ─── Setup ──────────────────────────────────────────────────────────
void setup() {
  delay(100);
  gralha.ecosPrescindiveis = &Serial;
  gralha.begin();
}
}

// ─── Loop ───────────────────────────────────────────────────────────
void loop() {
  gralha.update();
}
```

### 4. Upload and Fly

The Gralha Azul will read your transmitter, animate the wings, and breathe life into your creation.

## Configuration

Edit `src/GralhaAzul_Padraos.h` — all parameters use `#ifndef` guards, so you can override them in your sketch **before** `#include`:

```cpp
#define CICLO_DO_CORACAO_ALADO 0.080f   // KST MS320 (12 Hz)
#define ANGULO_DO_PLANAR_SERENO -2      // Gentle glide

#include <GralhaAzul.h>
```

### Key Parameters

| Define | Default | Description |
|--------|---------|-------------|
| `CICLO_DO_CORACAO_ALADO` | `0.052f` | Wingbeat period in seconds. See servo table |
| `ANGULO_DO_PLANAR_SERENO` | `-4` | Glide angle (degrees, negative = descend) |
| `ORIGEM_ASA_MATUTINA` | `0` | Left wing neutral offset (µs) |
| `ORIGEM_ASA_VESPERTINA` | `0` | Right wing neutral offset (µs) |
| `FEROCIDADE_MINIMA` | `1.0f` | Minimum stroke amplitude |
| `FEROCIDADE_MAXIMA` | `8.0f` | Maximum stroke amplitude |
| `PULSO_MINIMO_SERVO` | `500` | Servo minimum pulse (µs) |
| `PULSO_MAXIMO_SERVO` | `2500` | Servo maximum pulse (µs) |
| `GRAU_MINIMO_DA_ASA` | `0` | Minimum wing angle (degrees) |
| `GRAU_MAXIMO_DA_ASA` | `90` | Maximum wing angle (degrees) |

Full list: see `src/GralhaAzul_Padraos.h`.

### Optional Modules

```cpp
#define BAROMETRO_DESLIGADO
#define TELEMETRIA_DESLIGADO
#define NEOPIXEL_DESLIGADO
```

Define these **before** `#include <GralhaAzul.h>`.

## Servo Recommendations

Choose `CICLO_DO_CORACAO_ALADO` based on your servo's speed rating at your supply voltage. Add ~20% safety margin. Slower = safer, faster = risk of overheating.

| Servo | Speed (60°) | Torque | Suggested `CICLO_DO_CORACAO_ALADO` | Rate |
|-------|-------------|--------|-----------------------------------|------|
| DSSERVO DS3218 MG (25g) | 0.17s @6V | 3 kg·cm | `0.052f` | ~19 Hz |
| Blue Arrow D0576HT (1.7g) | 0.07s @5V | 0.2 kg·cm | `0.030f` | ~33 Hz |
| KST MS320 (56g) | 0.14s @8.4V | 8.5 kg·cm | `0.080f` | ~12 Hz |

## Receiver Setup

### CRSF

| Parameter | Setting | Reason |
|-----------|---------|--------|
| Protocol | `CRSF` | Serial output |
| Baud | `420000` | Matches firmware default |
| Rate | 50-100 Hz | 100 Hz ideal for ornithopter |

### PPM

```cpp
#define RECEPTOR_PPM
#define PORTAL_DOS_CANTOS_COSMICOS 2
#define NUMERO_DE_CANTOS 8
#include <GralhaAzul.h>
```

PPM input on GPIO 2, up to 8 channels.

## CRSF Channel Mapping

| Chan | Source | Function |
|------|--------|----------|
| CH1 | Aileron (right stick H) | Roll / differential |
| CH2 | Elevator (right stick V) | Pitch |
| CH3 | Throttle (left stick V) | Wingbeat intensity |
| CH4 | Rudder (left stick H) | Yaw / steering |
| CH5 | Switch | Glide toggle |
| CH6 | Potentiometer | Rhythm |
| CH7 | Potentiometer | Downstroke ferocity |
| CH8 | Potentiometer | Upstroke ferocity |
| CH9 | Potentiometer | Rudder differential |
| CH10 | Potentiometer (gain) | Altitude hold gain |

PPM: CH1-CH8 only. CH9-CH10 require `#define CANAL_DO_PLANAR_AMPLIADO`.

## Examples

See the `examples/` folder:
- **CRSF_Exemplo** — Basic CRSF setup
- **PPM_Exemplo** — Basic PPM setup

## Performance

- Loop time (idle): ~200 µs
- Loop time (all features): ~400 µs
- No `delay()` — all waits use `millis()` timers
- No floating-point in ISR — all FP in main loop

## Safety

- **Servo pulse clamping**: `PULSO_MINIMO_SERVO` / `PULSO_MAXIMO_SERVO` enforced
- **Angle clamping**: `GRAU_MINIMO_DA_ASA` / `GRAU_MAXIMO_DA_ASA` enforced
- **CRSF link loss**: Servo hold on last position, timer resets after 1 s
- **BMP180 failure**: Altitude hold gracefully disables, flight continues
- **NeoPixel timeout**: 100 ms max per frame, no animation stalls the loop

## FAQ

**Q: Servo gets hot mid-flight.**
A: Reduce wingbeat rate — increase `CICLO_DO_CORACAO_ALADO`. Check servo speed rating.

**Q: No response from receiver.**
A: Verify CRSF wiring (TX↔RX crossover). Check baud rate (420000). Confirm receiver flashed with CRSF protocol.

**Q: Barometer not detected.**
A: Check I2C wiring (GP4=SDA, GP5=SCL). Ensure BMP180 is 3.3V compatible. I2C address: `0x77` (configurable via `PORTA_DA_ALTITUDE`).

**Q: NeoPixel stays dark.**
A: Confirm `NEOPIXEL_DESLIGADO` is not defined. Check GPIO 16 connection.

**Q: Compilation error — "undefined reference to ..."**
A: Ensure `src/` folder is in the same directory as your sketch. The `.ino` file auto-includes all `.cpp` files in `src/`.

## Requirements

- **Board**: Raspberry Pi Pico / RP2040
- **Framework**: Arduino-Pico
- **Optional**: CrsfSerial.h, PPMReaderRP2040.h, Adafruit_BMP085_U.h, TinyGPSPlus.h, Adafruit_NeoPixel.h

## License

MIT — share, build, fly.