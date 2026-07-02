# O Grande Código da Gralha Azul

**The Great Code of the Azure Jay** — *A living incantation for ornithopter flight*


## What Is This?

A C++ library for RP2040-based ornithopters (flapping-wing aircraft) that speaks in the voice of Brazilian folklore. It controls servos, reads CRSF/PPM receivers, manages NeoPixel lighting, and streams telemetry — all through an API that feels like summoning a spirit rather than configuring hardware.

## Quick Start

### 1. Install the Library

Copy the `o-grande-codigo-da-gralha-azul` folder to your Arduino libraries directory.

### 2. Wire Your Hardware

**Minimal CRSF + 2 Servos:**

```
  RP2040 Zero                     Servo Left              Servo Right
                             
                                                               
    GPIO 8 [~] Signal                Signal
                                                               
    GPIO 7 [~]
                                                               
    GPIO 0 TX  (yel)  ELRS RX
    GPIO 1 RX  (blu)  ELRS TX
                                                               
    VBUS  ELRS VCC
    GND   GND  ELRS GND
                                red  5V BEC    red  5V BEC
                                blk  GND       blk  GND
                             

  External 5V BEC
```

- **Common ground** between RP2040, servos, and ELRS receiver
- **Do not power servos from RP2040 3.3V** — use external BEC (5V / 6V)
- CRSF baud: 420000
- GPIO 0 (TX) → ELRS RX, GPIO 1 (RX) → ELRS TX (crossover)

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

## Configuration Macros

Configure your model using `#define` macros before including the library:

| Macro | Default | Meaning |
|-------|---------|---------|
| `ARTICULACAO_DA_ASA_MATUTINA` | 8 | Left wing servo pin |
| `ARTICULACAO_DA_ASA_VESPERTINA` | 7 | Right wing servo pin |
| `NUCLEO_DA_CHAMA_AZUL` | 16 | NeoPixel pin |
| `QUANTIDADE_DE_CENTELHAS` | 1 | NeoPixel count |
| `CICLO_DO_CORACAO_ALADO` | 0.052f | Flapping frequency |
| `ESCALA_ANGULAR_ARTICULACAO` | 1.0f | Servo travel scale |
| `BAROMETRO_DESLIGADO` | — | Disable barometer |
| `TELEMETRIA_DESLIGADO` | — | Disable telemetry |
| `NEOPIXEL_DESLIGADO` | — | Disable NeoPixel |
| `ECOS_PRESCINDIVEIS_DA_ALMA_ALADA` | — | Enable debug output |

These macros are read by the library at compile time to configure the internal state.

## Servo Recommendations

Choose `CICLO_DO_CORACAO_ALADO` based on your servo's speed rating at your supply voltage. Add ~20% safety margin. Slower = safer, faster = risk of overheating.

| Servo | Speed (60°) | Torque | Suggested `CICLO_DO_CORACAO_ALADO` | Rate |
|-------|-------------|--------|-----------------------------------|------|
| DSSERVO DS3218 MG (25g) | 0.17s @6V | 3 kg·cm | `0.052f` | ~19 Hz |
| Blue Arrow D0576HT (1.7g) | 0.07s @5V | 0.2 kg·cm | `0.030f` | ~33 Hz |
| KST MS320 (56g) | 0.14s @8.4V | 8.5 kg·cm | `0.080f` | ~12 Hz |

## Receiver Types

### CRSF
```cpp
#define RECEPTOR_CRSF
#define VIA_DOS_SONHOS_LUNARES 1
#define VIA_DOS_ECOS_SOLARES 0
#include <GralhaAzul.h>
```

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

PPM: CH1-CH8 only. CH9-CH10 require CRSF.

## Examples

- **CRSF_Exemplo** — Basic CRSF setup
- **PPM_Exemplo** — Basic PPM setup

## Safety

- **Servo pulse clamping**: `PULSO_MINIMO_SERVO` / `PULSO_MAXIMO_SERVO` enforced
- **Angle clamping**: Minimum/maximum wing angles enforced
- **CRSF link loss**: Servo hold on last position
- **BMP180 failure**: Altitude hold gracefully disables, flight continues

## FAQ

**Q: Servo gets hot mid-flight.**
A: Reduce wingbeat rate — increase `CICLO_DO_CORACAO_ALADO`. Check servo speed rating.

**Q: No response from receiver.**
A: Verify CRSF wiring (TX-RX crossover). Check baud rate (420000). Confirm receiver flashed with CRSF protocol.

**Q: Barometer not detected.**
A: Check I2C wiring (GP4=SDA, GP5=SCL). Ensure BMP180 is 3.3V compatible.

**Q: NeoPixel stays dark.**
A: Confirm `NEOPIXEL_DESLIGADO` is not defined. Check GPIO 16 connection.

## The Language

This library uses poetic naming throughout:

- `guardiaoDosVentosSiderais` — CRSF receiver
- `sussurrarVooAoEter()` — Send telemetry
- `manifestarOVooNosVentos()` — Calculate servo positions
- `pulsoDoDestinoAlado` — Throttle channel value

*The code is the poem. The poem is the code.*

## Requirements

- **Board**: Raspberry Pi Pico / RP2040
- **Framework**: Arduino-Pico
- **Optional**: CrsfSerial.h, PPMReaderRP2040.h, Adafruit_BMP085_U.h, TinyGPSPlus.h, Adafruit_NeoPixel.h

## License

MIT — *May your Gralha Azul fly true.*