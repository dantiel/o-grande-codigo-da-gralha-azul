# O Grande Código da Gralha Azul

**The Great Code of the Azure Jay** — CRSF/PPM servo ornithopter library for RP2040 (Raspberry Pi Pico / Zero).

A C++ library for RP2040-based ornithopters (flapping-wing aircraft) that controls servos, reads CRSF/PPM receivers, manages NeoPixel lighting, and streams telemetry.

## Quick Start

### 1. Install the Library

**The entire repository is the library.** Place the whole `o-grande-codigo-da-gralha-azul` folder into your Arduino libraries directory:

- **macOS**: `~/Documents/Arduino/libraries/o-grande-codigo-da-gralha-azul/`
- **Linux**: `~/Arduino/libraries/o-grande-codigo-da-gralha-azul/`
- **Windows**: `Documents\Arduino\libraries\o-grande-codigo-da-gralha-azul\`

After placing, restart the Arduino IDE. The library and its examples will appear under **File → Examples → O Grande Código da Gralha Azul**.

**Target board:** select **Tools → Board → Waveshare RP2040 Zero** when uploading.

### 2. Wire Your Hardware
### 2a. Power & Servos

Two separate BECs from the same battery: one for the RP2040 (5V), one for the servos (6V, high current).

```
    Battery (2S-4S LiPo)
    ┌────────────────────┐
    │ +V ─────┬──────────┼──┐
    │ GND ────│──────────┼──│─── common GND
    └─────────┼──────────┘  │
              │             │
         ┌────┘        ┌────┘
         ▼             ▼
    ┌─────────┐   ┌─────────┐
    │BEC → 5V │   │BEC → 6V │
    │ (to RP) │   │(servos) │
    └────┬────┘   └────┬────┘
         │             │
         ▼             ├──────────┬──────────┐
    ┌─────────┐        ▼          ▼          ▼
    │ RP2040  │   ┌──────────┐┌──────────┐
    │         │   │ Servo L  ││ Servo R  │
    │ GPIO 8 ─┼───┼► Signal  ││          │
    │ GPIO 7 ─┼───┼──────────┼┼► Signal  │
    │ GND ────┼───┼─ common ─┼┼─ common ─┼─── all tied
    └─────────┘   └──────────┘└──────────┘
```

> ⚠️ **Servos draw high current** — never power them from the RP2040's 3.3V pin. Always use a dedicated BEC. If your servos are small direct-drive, a single BEC (5V) may suffice, but separate rails are safer.

### 2b. Receiver (CRSF)

```
    RP2040                         CRSF Receiver
    ┌──────────────┐               ┌──────────────┐
    │ GPIO 0 (TX)  ├──────────────►│ RX           │
    │ GPIO 1 (RX)  ├──────────────◄│ TX           │
    │ VBUS (5V)    ├──────────────►│ VCC          │
    │ GND          ├───────────────│ GND          │
    └──────────────┘               └──────────────┘

    Baud rate: 420000 (fixed in library)
```

> Some ELRS receivers run at 3.3V — check your receiver's specs. Power from the RP2040's 5V VBUS pin (not 3.3V), which covers both 3.3V and 5V receivers.

### 2c. Barometer — BMP180 (Optional)

```
    RP2040                         BMP180 Module
    ┌──────────────┐               ┌─────────────┐
    │ GPIO 4 (SDA) ├──────────────►│ SDA         │
    │ GPIO 5 (SCL) ├──────────────►│ SCL         │
    │ 3.3V         ├──────────────►│ 3.3V        │
    │ GND          ├──────────────►│ GND         │
    └──────────────┘               └─────────────┘
```

To disable, define `ORACULO_DESLIGADO` before `#include <GralhaAzul.h>`.

### 2d. NeoPixel — Onboard LED

The RP2040 Zero has a built-in WS2812B on **GPIO 16**. No external wiring needed. Auto-detected.

To disable: `#define CHAMA_AZUL_DESLIGADA` before `#include <GralhaAzul.h>`.

**Pin Reference:**

| Pin    | Function                | Macro                          |
|--------|-------------------------|--------------------------------|
| GPIO 8 | Servo — Left Wing       | `ARTICULACAO_DA_ASA_MATUTINA`  |
| GPIO 7 | Servo — Right Wing      | `ARTICULACAO_DA_ASA_VESPERTINA` |
| GPIO 0 | CRSF TX                 | `VIA_DOS_ECOS_SOLARES`         |
| GPIO 1 | CRSF RX                 | `VIA_DOS_SONHOS_LUNARES`       |
| GPIO 16| NeoPixel (onboard)      | `NUCLEO_DA_CHAMA_AZUL`         |
| GPIO 4 | BMP180 SDA              | `SILENCIO_DA_ALTURA`           |
| GPIO 5 | BMP180 SCL              | `RITMO_DA_PRESSAO`             |

### 3. Create Your Model Sketch

```cpp
// ─── Choose Your Receiver ─────────────────────────────────────────
#define GUARDIAO_DOS_VENTOS_SIDERAIS      // CRSF receiver
// #define MENSAGEIRO_DOS_CANTOS_COSMICOS // PPM receiver (uncomment instead)

// ─── Configuration ────────────────────────────────────────────────
#define ARTICULACAO_DA_ASA_MATUTINA   8
#define ARTICULACAO_DA_ASA_VESPERTINA 7
#define CICLO_DO_CORACAO_ALADO        0.065f   // Must match your servo's 60° speed. Amplitude, frequency, and scaling derive from this.

// ─── Optional Features ────────────────────────────────────────────
#define ORACULO_DESLIGADO
#define SUSSURRO_DESLIGADO
// #define CHAMA_AZUL_DESLIGADA

// ─── Ecos ao Monitor Serial ───────────────────────────────────────
// (debug output via gralha.ecosPrescindiveis = &Serial; — see setup)

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

// ─── Loop ───────────────────────────────────────────────────────────
void loop() {
  gralha.update();
}
```

### 4. Upload and Fly

The Gralha Azul will read your transmitter, animate the wings, and breathe life into your creation.

## Configuration

Override these in your sketch **before** `#include <GralhaAzul.h>`. For all other parameters, edit `src/GralhaAzul_Padraos.h` directly.

```cpp
#define CICLO_DO_CORACAO_ALADO     0.070f   // servo max speed rating (60° travel time)
#define ESCALA_ANGULAR_ARTICULACAO 0.05f    // elevator movement scale

#include <GralhaAzul.h>
```

### Key Parameters

These can be overridden with `#define` **before** `#include <GralhaAzul.h>`:

| Define | Default | Description |
|--------|---------|-------------|
| `CICLO_DO_CORACAO_ALADO` | `0.070f` | Servo max speed rating (60° travel time). Actual frequency depends on throttle and cadence modifiers |
| `ARTICULACAO_DA_ASA_MATUTINA` | `8` | Left wing servo GPIO pin |
| `ARTICULACAO_DA_ASA_DO_ENTARDECER` | `7` | Right wing servo GPIO pin |
| `ESCALA_ANGULAR_ARTICULACAO` | `0.04f` | Elevator movement scale |
| `ANGULO_DO_PLANAR_SERENO` | `-4` | Glide position offset (°). **0** = upstroke/downstroke centered in glide position, **-4** = default dihedral |
| `VIA_DOS_SONHOS_LUNARES` | `1` | CRSF RX GPIO pin |
| `VIA_DOS_ECOS_SOLARES` | `0` | CRSF TX GPIO pin |
| `FREQUENCIA_DO_SOPRO_COSMICO` | `420000` | CRSF baud rate |
| `MAGNITUDE_DA_BATIDA` | `0.04f` | Stroke amplitude scale |
| `DECAIMENTO_DA_CADENCIA_SONOLENTA_PADRAO` | `0.90f` | Glide decay factor per frame. Lower = faster fade to stop. `0.99` slow, `0.50` instant |
| `LIMIAR_DO_VOO_ATIVO_PADRAO` | `1040` | Throttle threshold for glide entry (center of 50µs hysteresis band) |

> **All other parameters** (pulse limits, gain values, PID constants, etc.) are in `src/GralhaAzul_Padraos.h` — edit that file directly. Parameters with `#ifndef` guards (like the two above) can be overridden in your sketch before `#include`.

### Guardião dos Ventos Siderais (CRSF Frame Integrity)

When `GUARDIAO_DOS_VENTOS_SIDERAIS` is defined (CRSF mode), the Guardião automatically filters ghost frames caused by servo EMI on the CRSF UART bus. No configuration needed — it's always active with CRSF.

**How it works:**

| Stage | Mechanism |
|-------|-----------|
| 1. Per-channel delta | Frame with any channel Δ >100µs flagged |
| 2. Simultaneity check | ≥4 channels anomalous in same frame → ghost collective (rejected) |
| 3. Temporal persistence | 1-3 channels anomalous → requires 2nd consecutive frame within ±200µs to confirm as stick movement |
| 4. First frame | After link-up or failsafe recovery, first frame accepted unconditionally to initialize references |

A ghost frame (isolated single-frame anomaly) is blocked. A fast stick sweep (sustained across consecutive frames) passes through.

### Optional Modules

```cpp
#define ORACULO_DESLIGADO
#define SUSSURRO_DESLIGADO
#define CHAMA_AZUL_DESLIGADA
```

Define these **before** `#include <GralhaAzul.h>`.

## Glide Position (`ANGULO_DO_PLANAR_SERENO`)

Controls the **static wing position** when CH5 (flight mode) is in glide position (centered).

| Value | Behavior |
|-------|----------|
| **`-4`** (default) | Wings maintain a slight dihedral (left 4° down, right 4° up relative to neutral) |
| **`0`** | **Upstroke and downstroke are centered** — glide position equals the average of both wing endpoints. Useful for symmetric gliding where neither wing is biased |
| **`+4`** | Reverse dihedral (left 4° up, right 4° down) |

```cpp
// In your sketch, before #include:
#define ANGULO_DO_PLANAR_SERENO   0   // Center glide position

#include <GralhaAzul.h>
```

This parameter can also be changed at runtime: `gralha.anguloDoPlanarSereno = 0;`

### Glide Behaviour

When throttle drops below `LIMIAR_DO_VOO_ATIVO_PADRAO` (default `1040`), the wings enter glide:

| Mode | Behaviour |
|------|-----------|
| **Normal** | Angle resets toward 0 with configurable decay (`DECAIMENTO_DA_CADENCIA_SONOLENTA_PADRAO`). Wingbeat restarts predictably from mid-stroke. |
| **`MODO_DE_VOO_ALTERNATIVO`** | Angle continues advancing with decaying cadence — phase continuity preserved when flapping resumes. |

**Hysteresis:** exit glide when throttle rises above `LIMIAR + 50` (default `1090`), preventing oscillation at the boundary.

```cpp
// Raise glide threshold (enter glide with less throttle reduction):
#define LIMIAR_DO_VOO_ATIVO_PADRAO  1100

// Gentler fade when entering glide:
#define DECAIMENTO_DA_CADENCIA_SONOLENTA_PADRAO  0.95f

#include <GralhaAzul.h>
```

## Servo Recommendations

**`CICLO_DO_CORACAO_ALADO` is your servo's max speed rating — the time it takes for 60° travel at your supply voltage.** Set it to the servo's spec (or slightly slower). Actual wingbeat frequency depends on throttle position and cadence modifiers at runtime.

| Servo | Speed (60°) | Torque | Weight | `CICLO_DO_CORACAO_ALADO` |
|-------|-------------|--------|--------|--------------------------|
| PTK 7465W | 0.07s @8.4V | 5.5 kg·cm | 13g | `0.070f` |
| Blue Arrow AF D43S-6.0-MG | 0.041s @6V | 1.76 kg·cm | 5.6g | `0.041f` |
| Blue Arrow D0576HT | 0.056s @7.4V | 4.2 kg·cm | 7.9g | `0.056f` |
| KST MS320 | 0.08s @8.4V | 4.5 kg·cm | 21g | `0.080f` |

> **Tip:** For complete frequency/amplitude scaling tables for each servo (especially in `MODO_DE_VOO_ALTERNATIVO`), see [SERVO_SCALING_TABLES.md](SERVO_SCALING_TABLES.md).

## Receiver Setup

### CRSF

| Parameter | Setting | Reason |
|-----------|---------|--------|
| Protocol | `CRSF` | Serial output |
| Baud | `420000` | Matches firmware default |
| Rate | 50-100 Hz | 100 Hz ideal for ornithopter |

### PPM

```cpp
#define MENSAGEIRO_DOS_CANTOS_COSMICOS
#define PORTAL_DOS_CANTOS_COSMICOS  2
#define NUMERO_DE_CANTOS            8
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
| CH5 | Switch | Glide toggle (arm/disarm) |
| CH6 | Potentiometer | Flapping frequency trim |
| CH7 | Potentiometer | Downstroke ferocity |
| CH8 | Potentiometer | Upstroke ferocity |
| CH9 | Potentiometer | Yaw aggressiveness / rudder differential |
| CH10 | Potentiometer (gain) | Altitude hold gain |

### Alternative Control Mode

Define `MODO_DE_VOO_ALTERNATIVO` before `#include <GralhaAzul.h>` for **physics-based direct control**:

```cpp
#define MODO_DE_VOO_ALTERNATIVO
#define CICLO_DO_CORACAO_ALADO 0.070f   // Your servo's actual speed
#include <GralhaAzul.h>
```

In this mode, **CH6 sets frequency** and **throttle sets percentage of maximum possible amplitude** at that frequency — constrained by servo physics (velocity = 60° / CICLO).

| Channel | Function | Range |
|---------|----------|-------|
| CH3 (Throttle) | Amplitude % of max permitted | 0% → 0°, 100% → physics-limited max |
| CH6 (Potentiometer) | Flapping frequency | 0 Hz → 30/CICLO Hz (e.g., 0→42.9Hz for CICLO=0.07s) |

**Physics relationship:** Higher frequency → lower max amplitude (servo can't move far fast). At CH6=100%, amplitude max is always **~10°** regardless of servo speed.

> **See [SERVO_SCALING_TABLES.md](SERVO_SCALING_TABLES.md)** for complete frequency/amplitude tables for common servos.

**Default mode channels:**
- CH3 → modulates both cadence and amplitude via PI
- CH6 → frequency trim (additive to throttle-derived cadence)
- CH9 → yaw differential (asymmetric wing thrust)

**Alternative mode channels:**
- CH3 → amplitude % of physics max (0→100%)
- CH6 → frequency direct (0→servo_max_Hz)
- CH9 → (configurable, typically yaw differential)

PPM: CH1-CH8 only. CH9-CH10 require `#define CANAL_DO_PLANAR_AMPLIADO`.

## Telemetry (Sussurro ao Éter)

When `SUSSURRO_DESLIGADO` is **not** defined, the Gralha whispers flight data to the serial monitor every second (via `INTERVALO_DOS_ECOS_PADRAO`, default 1000 ms). Output is formatted as space-separated key-value pairs on a single line.

### Always sent

| Campo | Significado |
|-------|-------------|
| VOANDO / SONHANDO | Flight state (flying / standby) |
| Modo: RITMADO / PLANANDO | Wing mode (flapping / gliding) |
| SoproV | Throttle channel raw value |
| Alet | Aileron channel raw value |
| Prof | Elevator channel raw value |
| Leme | Rudder channel raw value |
| Despertar | Arming switch state |
| FerBater | Downstroke ferocity |
| FerRetorno | Upstroke ferocity |
| FerLeme | Rudder ferocity differential |
| GainSust | Altitude hold gain |
| CH10Sust | Altitude hold channel raw value |
| Fase | Wing phase angle (radians) |
| Cadencia | Wingbeat frequency (Hz) |

### When Oráculo (barometer) is active

These additional fields appear only if the barometer is enabled and breathing:

| Campo | Significado |
|-------|-------------|
| AltVoo | Altitude above launch (m) |
| Subida | Vertical speed / climb rate (m/s) |
| SoproDoCeu | Air temperature (°C) |
| FeNoSopro | Barometer confidence (0–1) |
| AltDesej | Target altitude, altitude hold active (m) |
| SoproSustentar | Throttle pulse for altitude hold (µs) |
| GainEfetivo | Effective altitude hold gain |

**Without the Oráculo**, barometric fields are omitted — only flight surface and rhythm data is sent.

To disable telemetry entirely: `#define SUSSURRO_DESLIGADO`.

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

- **Servo pulse clamping**: internal limits enforced (500–2500 µs)
- **CRSF link loss**: Servo hold on last position, timer resets after 1 s
- **BMP180 failure**: Altitude hold gracefully disables, flight continues
- **NeoPixel timeout**: 100 ms max per frame, no animation stalls the loop

## FAQ

**Q: Wingbeat feels wrong — wrong amplitude, frequency, or scaling.**
A: `CICLO_DO_CORACAO_ALADO` must match your servo's 60° travel time. The entire algorithm derives from it. Also check servo speed rating for overheating.

**Q: No response from receiver.**
A: Verify CRSF wiring (TX↔RX crossover). Check baud rate (420000). Confirm receiver flashed with CRSF protocol.

**Q: Barometer not detected.**
A: Check I2C wiring (GP4=SDA, GP5=SCL). Ensure BMP180 is 3.3V compatible. I2C address: `0x77`.

**Q: NeoPixel stays dark.**
A: Confirm `CHAMA_AZUL_DESLIGADA` is not defined. Check GPIO 16 connection.

**Q: Compilation error — "undefined reference to ..."**
A: Ensure `src/` folder is in the same directory as your sketch. The `.ino` file auto-includes all `.cpp` files in `src/`.

## Requirements

- **Board**: Raspberry Pi Pico / RP2040
- **Framework**: Arduino-Pico
- **Optional**: CrsfSerial.h, PPMReaderRP2040.h, Adafruit_BMP085_U.h, TinyGPSPlus.h, Adafruit_NeoPixel.h

## License

MIT — share, build, fly.