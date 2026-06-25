# O Grande Código da Gralha Azul

**The Great Code of the Azure Jay** — CRSF/PPM servo ornithopter library for RP2040 (Raspberry Pi Pico / Zero).

---

## Quick Start

```cpp
#include <GralhaAzul.h>

void setup() { gralhaAzulSetup(); }
void loop()  { gralhaAzulLoop();  }
```

Open `o-grande-codigo-da-gralha-azul.ino` in Arduino IDE with the `src/` folder alongside it. The `.ino` automatically includes all library files.

---

## Wiring

### Minimal — CRSF + 2 Servos

```
  RP2040 Zero                     Servo Left              Servo Right
  ┌──────────────┐               ┌──────────┐            ┌──────────┐
  │              │               │          │            │          │
  │  GPIO 5 [~]──►──────────────►│ Signal   │            │ Signal   │
  │              │               │          │            │          │
  │  GPIO 7 [~]──►──────────────►│          │════════════│          │
  │              │               │          │            │          │
  │  GPIO 0 TX ──► (yel) ──────►│ ELRS RX  │            │          │
  │  GPIO 1 RX ◄─── (blu) ◄─────│ ELRS TX  │            │          │
  │              │               │          │            │          │
  │  VBUS ────────► ELRS VCC     │          │            │          │
  │  GND  ◄── GND ◄── ELRS GND ◄┼──────────┼────────────┼──────────┤
  │              │               │ red ─────┼── 5V BEC   │ red ─────┼── 5V BEC
  │              │               │ blk ─────┼── GND      │ blk ─────┼── GND
  └──────────────┘               └──────────┘            └──────────┘

  External 5V BEC ───────►───────►──────────────────────►────────────┘
```

- **Common ground** between RP2040, servos, and ELRS receiver
- **Do not power servos from RP2040 3.3V** — use external BEC (5V / 6V)
- CRSF baud: 420000 (`FREQUENCIA_DO_SOPRO_COSMICO`)
- GPIO 0 (TX) → ELRS RX, GPIO 1 (RX) → ELRS TX (crossover)

### Pin Allocation

| Pin    | Function                | Portuguese Name                |
|--------|-------------------------|--------------------------------|
| GPIO 5 | Servo — Left Wing       | `ARTICULACAO_ASA_DA_MANHA`     |
| GPIO 7 | Servo — Right Wing      | `ARTICULACAO_ASA_DO_ENTARDECER`|
| GPIO 0 | CRSF TX                 | `VIA_DOS_ECOS_SOLARES`         |
| GPIO 1 | CRSF RX                 | `VIA_DOS_SONHOS_LUNARES`       |
| GPIO 16| NeoPixel (onboard)      | `NUCLEO_DA_CHAMA_AZUL`         |
| GPIO 4 | BMP180 SDA              | `PINO_SILENCIO_DA_ALTURA`      |
| GPIO 5 | BMP180 SCL              | `PINO_RITMO_DA_PRESSAO`        |
| GPIO 2 | PPM input (alternative) | `PINO_DO_MENSAGEIRO`           |

> **Note**: GPIO 5 serves double duty (Servo Left + BMP180 SCL) only if barometer is enabled. Ensure no conflict if using both.

---

## Configuration

Edit `src/GralhaAzulConfig.h` — all parameters use `#ifndef` guards, so you can override them in your sketch **before** `#include`:

```cpp
#define CICLO_DO_CORACAO_ALADO 0.080f   // KST MS320 (12 Hz)
#define ANGULO_DO_PLANAR_SERENO -2      // Gentle glide
#define RECEPTOR_ALADO 1                // CRSF

#include <GralhaAzul.h>
```

### Key Parameters

| Define                    | Default  | Description                                |
|---------------------------|----------|--------------------------------------------|
| `CICLO_DO_CORACAO_ALADO` | `0.052f` | Wingbeat period in seconds. See servo table|
| `ANGULO_DO_PLANAR_SERENO`| `-4`     | Glide angle (degrees, negative = descend)  |
| `ORIGEM_ASA_MATUTINA`    | `0`      | Left wing neutral offset (µs)              |
| `ORIGEM_ASA_VESPERTINA`  | `0`      | Right wing neutral offset (µs)             |
| `FEROCIDADE_MINIMA`      | `1.0f`   | Minimum stroke amplitude                   |
| `FEROCIDADE_MAXIMA`      | `8.0f`   | Maximum stroke amplitude                   |
| `PULSO_MINIMO_DO_CORACAO`| `500`    | Servo minimum pulse (µs)                   |
| `PULSO_MAXIMO_DO_CORACAO`| `2500`   | Servo maximum pulse (µs)                   |
| `GRAU_MINIMO_DA_ASA`     | `0`      | Minimum wing angle (degrees)               |
| `GRAU_MAXIMO_DA_ASA`     | `90`     | Maximum wing angle (degrees)               |

Full list of all 35+ parameters: see `src/GralhaAzulConfig.h`.

### Optional Modules

```cpp
#define GRALHA_AZUL_NEOPIXEL_DESLIGADO
#define GRALHA_AZUL_BAROMETRO_DESLIGADO
#define GRALHA_AZUL_TELEMETRIA_DESLIGADO
```

Define these **before** `#include <GralhaAzul.h>`.

> **Compilation note**: Because GralhaAzul is structured as a compiled library, `#define`s in your `.ino` are visible to the library `.cpp` only via the `#ifndef` guard mechanism. If you prefer, edit `GralhaAzulConfig.h` directly (recommended for beginners).

---

## Servo Recommendations

Choose `CICLO_DO_CORACAO_ALADO` based on your servo's speed rating at your supply voltage. Add ~20% safety margin. Slower = safer, faster = risk of overheating.

| Servo                     | Speed (60°) | Torque    | Suggested `CICLO_DO_CORACAO_ALADO` | Rate   |
|---------------------------|-------------|-----------|-------------------------------------|--------|
| DSSERVO DS3218 MG (25g)  | 0.17s @6V   | 3 kg·cm   | `0.052f`                            | ~19 Hz |
| Blue Arrow D0576HT (1.7g)| 0.07s @5V   | 0.2 kg·cm | `0.030f`                            | ~33 Hz |
| KST MS320 (56g)          | 0.14s @8.4V | 8.5 kg·cm | `0.080f`                            | ~12 Hz |

---

## CRSF Channel Mapping

| Chan | Source                   | Function              |
|------|--------------------------|-----------------------|
| CH1  | Aileron (right stick H)  | Roll / differential   |
| CH2  | Elevator (right stick V) | Pitch                 |
| CH3  | Throttle (left stick V)  | Wingbeat intensity    |
| CH4  | Rudder (left stick H)    | Yaw / steering        |
| CH5  | Switch                   | Glide toggle          |
| CH6  | Potentiometer            | Rhythm                |
| CH7  | Potentiometer            | Downstroke ferocity   |
| CH8  | Potentiometer            | Upstroke ferocity     |
| CH9  | Potentiometer            | Rudder differential   |
| CH10 | Potentiometer (gain)     | Altitude hold gain    |

PPM: CH1–CH8 only. CH9–CH10 require `#define CANAL_DO_PLANAR_AMPLIADO`.

---

## Receiver Setup

### ExpressLRS / CRSF

| Parameter | Setting  | Reason                        |
|-----------|----------|-------------------------------|
| Protocol  | `CRSF`   | Serial output                 |
| Baud      | `420000` | Matches firmware default      |
| Rate      | ≥50 Hz   | 100 Hz ideal for ornithopter  |

### PPM

```cpp
#define RECEPTOR_DOS_VENTOS_PPM
```

PPM input on GPIO 2, up to 8 channels.

---

## Performance

- Loop time (idle): ~200 µs
- Loop time (all features): ~400 µs
- No `delay()` — all waits use `millis()` timers
- No floating-point in ISR — all FP in main loop

---

## Safety

- **Servo pulse clamping**: `PULSO_MINIMO_DO_CORACAO` / `PULSO_MAXIMO_DO_CORACAO` enforced
- **Angle clamping**: `GRAU_MINIMO_DA_ASA` / `GRAU_MAXIMO_DA_ASA` enforced
- **CRSF link loss**: servo hold on last position, timer resets after 1 s
- **BMP180 failure**: altitude hold gracefully disables, flight continues
- **NeoPixel timeout**: 100 ms max per frame, no animation stalls the loop

---

## FAQ

**Q: Servo gets hot mid-flight.**  
A: Reduce wingbeat rate — increase `CICLO_DO_CORACAO_ALADO`. Check servo speed rating.

**Q: No response from receiver.**  
A: Verify CRSF wiring (TX↔RX crossover). Check baud rate (420000). Confirm receiver flashed with CRSF protocol.

**Q: Barometer not detected.**  
A: Check I²C wiring (GP4=SDA, GP5=SCL). Ensure BMP180 is 3.3V compatible. I²C address: `0x77` (configurable via `PORTA_DA_ALTITUDE`).

**Q: NeoPixel stays dark.**  
A: Confirm `GRALHA_AZUL_NEOPIXEL_DESLIGADO` is not defined. Check GPIO 16 connection.

**Q: Compilation error — "undefined reference to ..."**  
A: Ensure `src/` folder is in the same directory as your sketch. The `.ino` file auto-includes all `.cpp` files in `src/`.

---

## License

MIT — share, build, fly.
