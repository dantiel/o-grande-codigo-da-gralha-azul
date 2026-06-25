# O Grande Código da Gralha Azul

**The Great Code of the Azure Jay**

A CRSF/PPM servo ornithopter library for RP2040, inspired by the legend of the _Gralha Azul_ (Azure Jay) — the guardian of the Araucaria forests of southern Brazil.

> *"Nas eras antigas, quando o aroma dos pinheirais sagrados pairava como prece..."*
> *(In ancient times, when the scent of sacred pine groves hung like prayer...)*

---

## Table of Contents

- [Hardware Requirements](#hardware-requirements)
- [Wiring](#wiring)
- [ExpressLRS / CRSF Setup](#expresslrs--crsf-setup)
- [PPM Setup](#ppm-setup)
- [Library Usage](#library-usage)
- [Configuration](#configuration)
- [Servo Recommendations & Examples](#servo-recommendations--examples)
- [CRSF Channel Mapping](#crsf-channel-mapping)
- [Flight Modes](#flight-modes)
- [Portuguese Name Reference](#portuguese-name-reference)
- [License](#license)

---

## Hardware Requirements

| Component     | Example / Notes                            |
|---------------|--------------------------------------------|
| **Microcontroller** | Waveshare RP2040 Zero (or any RP2040 board with at least 1 UART) |
| **RC Receiver** | ExpressLRS with CRSF output (e.g., Happymodel EP2) |
| **Servos × 2** | Left wing and right wing. See [Servo Recommendations](#servo-recommendations--examples) |
| **NeoPixel LED** | WS2812B single pixel (optional), built into RP2040 Zero on GPIO 16 |
| **Barometer** | BMP180 (optional), I2C |
| **Battery** | 1S LiPo (3.7V) or 2S LiPo (7.4V) with BEC for servos |
| **BEC / External 5V** | Required for servo power — do not power servos from RP2040's 3.3V regulator |

### Pin Allocation (Waveshare RP2040 Zero)

| Pin   | Function                    | Portuguese Name                | Meaning                     |
|-------|-----------------------------|--------------------------------|-----------------------------|
| GPIO 5 | Servo — Left Wing           | `ARTICULACAO_ASA_DA_MANHA`     | Morning Wing Joint          |
| GPIO 7 | Servo — Right Wing          | `ARTICULACAO_ASA_DO_ENTARDECER`| Evening Wing Joint          |
| GPIO 0 | CRSF TX (6-pin CRSF: yellow)| `VIA_DOS_ECOS_SOLARES`         | Path of Solar Echoes        |
| GPIO 1 | CRSF RX (6-pin CRSF: blue)  | `VIA_DOS_SONHOS_LUNARES`       | Path of Lunar Dreams        |
| GPIO 16| NeoPixel (built-in LED)     | `NUCLEO_DA_CHAMA_AZUL`         | Core of the Blue Flame      |

Alternative pin assignments can be configured in `src/GralhaAzulConfig.h` or overridden via `#define`.

---

## Wiring

### CRSF + External Servo Power

```
External 5V BEC
  5V+ ─────────────────────────► Servo Power (red, both servos)
   GND ─────────────────────────► Servo GND ──► RP2040 GND (common ground!)

RP2040 Zero                     Left Servo (GP8)    Right Servo (GP7)
┌─────────────┐                 ┌────────────┐       ┌────────────┐
│ GPIO 5 [~]─── ►───────────────│ Signal     │       │ Signal     │
│ GPIO 7 [~]─── ►───────────────│            │══════►│            │
│ GPIO 0 (TX) ───► (yellow) ───► ELRS RX           │            │
│ GPIO 1 (RX) ◄─── (blue)   ◄─── ELRS TX           │            │
│              │               │            │       │            │
│ VBUS   [ ]─────► 5V   ───────► ELRS VCC  │       │            │
│ GND        ◄─── common ◄────── ELRS GND   │       │            │
└─────────────┘               │            │       │            │
                               │ red   ◄─────── 5V  │            │
                               │ black ◄─────── GND │            │
                               └────────────┘       └────────────┘
```

- **Servo ground must be common** with RP2040 GND
- CRSF uses UART at **420000 baud** (`FREQUENCIA_DO_SOPRO_COSMICO`)
- Barometer (BMP180) on I2C0 pins GP4 (SDA) / GP5 (SCL) if included

---

## ExpressLRS / CRSF Setup

This project communicates with ExpressLRS receivers using the **CRSF protocol**.

### Key Concepts

| Term             | Meaning                                                        |
|------------------|----------------------------------------------------------------|
| **ExpressLRS**   | RF link between transmitter and receiver                       |
| **CRSF**         | Serial protocol between receiver and flight controller         |

### Transmitter Setup (EdgeTX / OpenTX)

1. Install **ExpressLRS** on your transmitter module (Ranger, internal, etc.)
2. Flash your receiver with the same ELRS version and **binding phrase**
3. Bind the receiver to your module

### Receiver Configuration (via ELRS Lua script or WiFi)

| Parameter     | Required Setting | Reason                          |
|---------------|------------------|---------------------------------|
| Protocol      | `CRSF`           | Output channel data via CRSF    |
| Baud Rate     | `420000`         | Match `FREQUENCIA_DO_SOPRO_COSMICO = 42000` (API multip. internally by 10) |
| Packet Rate   | `50 Hz` (or higher) | Good balance for ornithopter |

### Channel Assignment (typical)

| Chan | Source                        | Function           |
|------|-------------------------------|--------------------|
| CH1  | Aileron (Right stick H)       | Roll/Differential  |
| CH2  | Elevator (Right stick V)      | Pitch              |
| CH3  | Throttle (Left stick V)       | Wingbeat intensity |
| CH4  | Rudder (Left stick H)         | Yaw (steering)     |
| CH5  | (currently unused)            | Arm switch         |
| CH6  | Pot/slider                    | Rhythm / compass   |
| CH7  | Pot/slider                    | Downstroke ferocity|
| CH8  | Pot/slider                    | Upstroke ferocity  |
| CH9  | Pot/slider                    | Rudder differential|
| CH10 | Pot/slider (0-100% gain)      | Altitude-hold gain |
| CH11 | Pot/slider                    | (reserved)         |
| CH12 | Pot/slider                    | (reserved)         |

> Available only for CRSF. PPM input supports CH1–CH8 standard; CH9 and CH10 must be `#define`'d.

---

## PPM Setup

```cpp
#define RECEPTOR_DOS_VENTOS_PPM
#include <GralhaAzul.h>
```

- PPM input pin: GPIO2 (configurable via `PINO_DO_MENSAGEIRO`)
- Up to 8 channels standard, compatible with OpenTX/EdgeTX PPM output
- See `examples/PPM_Exemplo/`

---

## Library Usage

This project is structured as an **Arduino library**. For a quick start:

1. Copy the entire `src/` folder to your `libraries/` directory as `GralhaAzul/`, OR
2. Use `File → Examples → GralhaAzul → CRSF_Exemplo` (after installing)
3. Include `<GralhaAzul.h>` in your sketch
4. Call `gralhaAzulSetup()` from `setup()` and `gralhaAzulLoop()` from `loop()`

Minimal sketch:

```cpp
#include <GralhaAzul.h>

void setup()  { gralhaAzulSetup(); }
void loop()   { gralhaAzulLoop();  }
```

For convenient solo development without installing as a library, open the top-level `o-grande-codigo-da-gralha-azul.ino` — Arduino IDE will automatically pick up all `src/` files.

### Optional Modules (Compile-time)

Disable any component before `#include <GralhaAzul.h>`:

```cpp
#define GRALHA_AZUL_NEOPIXEL_DESLIGADO   // no NeoPixel code
#define GRALHA_AZUL_BAROMETRO_DESLIGADO  // no BMP180 / altitude hold
#define GRALHA_AZUL_TELEMETRIA_DESLIGADO // no CRSF telemetry frames
```

---

## Configuration

### Important Compilation Note

Because GralhaAzul is a **library** (not inline code), `#define`s in your `.ino` sketch already?

They are *not* automatically visible to the library's `.cpp` file. This has two solutions:

**Option A (recommended for most users):**
Edit the constants directly in `src/GralhaAzulConfig.h` — the single pillar of configuration with `#ifndef` defaults.

**Option B (for power users, e.g. PlatformIO build flags):**
```cpp
#define CICLO_DO_CORACAO_ALADO  0.065f   // your custom wingbeat period
```
This only takes effect if an `-D` flag is passed at compile-time or `build_unflags` in the environment. Defining before `#include <GralhaAzul.h>` works **if** the example is opened and the include comes after your defines.

All constants use `#ifndef` guards for flexibility.

### Config Parameters

The central `GralhaAzulConfig.h` is your single point of harmony — geometry, timings, motion parameters, serenity angles, pulse ranges, thresholds, mapping constants. Open with poetry, change what the wing wants.

**Key parameters to customise per servo:**

| Define               | Default | Description                           |
|----------------------|---------|---------------------------------------|
| `CICLO_DO_CORACAO_ALADO` | `0.052f` | Wingbeat period in seconds (~19 Hz) |
| `ANGULO_DO_PLANAR_SERENO` | `-4` | Glide angle, degrees (neg = descend) |
| `ORIGEM_ASA_MATUTINA` | `0` | Left wing neutral offset             |
| `ORIGEM_ASA_VESPERTINA` | `0` | Right wing neutral offset            |
| `FEROCIDADE_MINIMA` | `1.0f` | Minimum ferocity (CH7+CH8 strength)  |
| `FEROCIDADE_MAXIMA` | `8.0f` | Maximum ferocity amplitude           |

To change: open `src/GralhaAzulConfig.h`, locate the block, edit the number — double‑click once for winged life: Letting logic aloft as much.

See `src/GralhaAzulConfig.h` for the full 314‑line list of adjustable constants.

---

## Servo Recommendations & Examples

Choosing the right servo and tuning `CICLO_DO_CORACAO_ALADO` is the most critical step. Operating a servo above its rated speed heats — and likely ruins — the coil mid‑flight.

Example configurations exist for each common servo type:

| Example                     | Servo              | Speed (60° range) | Torque       | `CICLO_DO_CORACAO_ALADO` | Wing rate | `ANGULO_DO_PLANAR_SERENO` |
|-----------------------------|--------------------|--------------------|--------------|---------------------------|-----------|----------------------------|
| `CRSF_Exemplo`             | DSSERVO DS3218 MG (25g) | ~0.17s @ 6.0V | 3 kg·cm | `0.052f` | ~19 Hz | `-4` |
| `PPM_Exemplo`              | DSSERVO DS3218 MG (25g) | ~0.17s @ 6.0V | 3 kg·cm | `0.052f` | ~19 Hz | `-3` |
| `CRSF_Servo_Rapido`        | Blue Arrow D0576HT MG (1.7g) | ~0.07s @ 5.0V | 0.2 kg·cm | `0.030f` | ~33 Hz | `-1` |
| `CRSF_Servo_Torque`        | KST MS320 (56g) | ~0.14s @ 8.4V | 8.5 kg·cm | `0.080f` | ~12 Hz | `-2` |

Use 19 Hz (`CICLO_DO_CORACAO_ALADO = 0.052f`) as baseline for most sub‑20g servos that are not extreme. Faster cycles will need micro‑servos with high speed specs; heavier birds pull higher torque servos beaten rhythm slower.

Calculate ideal cycle:
- Find servo's rated speed for `60° motion` at its input voltage
- Multiply rated stall‑safe period gap = the effective motion plus returns framing steady air expansion
- Safe range across each: ±20% safe fudge internal harmonics

---

## Flight Modes

### Flapping Mode (`EM_RITMO_DE_BATIDA_DAS_ASAS`)

The wing beats at `<CICLO_DO_CORACAO_ALADO>` cycle length driven by:

- **CH1** twists differences individually (roll/spread)
- **CH3** wing intensity alive threshold; uses harmonic waveform riding shape to expel bird increment

The shape driver `forma__do_bater_das_Asas()` ties waveform using `tanh()` applied to differenced per Down‑ and Upferocity.

Equalised values inside modulate—very distinct symmetrical movement splits as rudder diff completes partial roll motion stabilised.

```math
ang = shape(fer_cdescida) - shape(fer_subida)
shape(f) = tanh(base_mult * f / fmax_fBase … etc
Whole mapped lines push 0−180 writing after multiplier
```

### Glide Mode (`EM_DESLIZE_ETERNO_E_CONTEMPLATIVO`)

When throttle goes under limit, the algorithm stops reading extra phases, floats the arms inward around smooth angled [`ANGULO_DO_PLANAR_SERENO`].
This soars — decrease ascension passes heavy aerodynamic setting bringing less angle still then drag: over simple positionning approach to keep wings spread descent linear reduction minim shock per beat.

This low draw.

### Altitude Hold (`sustentar`)

To hold altitude, connect an optional **BMP180** barometer (I2C, pins GP4=SDA, GP5=SCL).

Enable by leaving `GRALHA_AZUL_BAROMETRO_DESLIGADO` undefined; gains turn wind.

- **CH10** defines *gain* (1000 = 0%, no correction; 2000 = 100%, full gain usable best early far)
- **CH3** sets *target altitude* span (1000 = 0 m, 2000 = `ALTURA_MAX_DO_SUSTENTAR_M`, default 20 m)
- Correctors controller subtract `gang` PID net makes flattion holding buffering:
  Error → `sopro_vital_do_sustentar` scaled via `FORCA_BASE_DO_SUSTENTAR` weight softened filtering

Zones soft: `SILENCIO_DO_SUSTENTAR_M` (0.5 m) ignores light ascent creeping wingp sweep stead natural sinking rotation.

If barometer not found (detected) the unit glides smoothly limit no lock — acts motored gradually if descend yes still grace near.

Guard quick enable:

```cpp
// Disable altitude hold entirely
#define GRALHA_AZUL_BAROMETRO_DESLIGADO
#include <GralhaAzul.h>
```

---

## Portuguese Name Reference

The code uses poetic Brazilian Portuguese identifiers throughout. For readers learning Portuguese or building a glossary:

| Portuguese Name | Configuration entry pin event or symbol translated part mean exactly |
|--|--Full alphabetical all entries map before context—&lt;/b&gt; |

| Portuguese (Code) | English (Function) |
|-----|------|
| `Gralha Azul` | Azure Jay bird species |
| `FREQUENCIA_DO_SOPRO_COSMICO` | CRSF Baud Rate (Frequency of the Cosmic Breath) |
| `guardiao_dos_ventos_siderais` | CRSF Serial Object (Guardian of Sidereal Winds) |
| `ARTICULACAO_ASA_DA_MANHA` | Left Wing Servo Pin (Morning Wing Joint) |
| `ARTICULACAO_ASA_DO_ENTARDECER` | Right Wing Servo Pin (Evening Wing Joint) |
| `VIA_DOS_SONHOS_LUNARES` | CRSF RX Pin (Path of Lunar Dreams) |
| `VIA_DOS_ECOS_SOLARES` | CRSF TX Pin (Path of Solar Echoes) |
| `NUCLEO_DA_CHAMA_AZUL` | NeoPixel Pin (Core of the Blue Flame) |
| `QUANTIDADE_DE_CENTELHAS_NA_CHAMA` | NeoPixel LED Count (Sparks count) |
| `CICLO_DO_CORACAO_ALADO` | Wingbeat Period (Winged Heart Cycle) |
| `LIMIAR_DO_VOO_ATIVO` | Throttle Threshold for active flapping |
| `LIMIAR_DO_VOO_ATIVO_HISTERESE` | Hysteresis near threshold limit before inactive shift |
| `ANGULO_DO_PLANAR_SERENO` | Glide Angle setback (Serene Gliding) |
| `ORIGEM_ASA_MATUTINA` |L left wing neutral rotation fit |
| `ORIGEM_ASA_VESPERTINA` |R right wing neutral rotation |
| `VIBRACAO_NEUTRA_DO_ALETAO` neutral Aileron input default when linked moment send
| `VIBRACAO_NEUTRA_DO_PROFUNDOR`neutral elevator idle backup space type firmware tone uses value turn during storm in her framenum same many timer full list longer |
| `EstadoDaAlmaAlada` | Link State off target ch4 (dormitive timer miss set frequency last)
(remain short short preserve en Read reach enough main stay / context know register re‑original commit)

…

For my pair additional elements open explicit soon summary below fully table ending down.

Feel maintain the or Original Great listed classic alignment:

Above all identif trace fill verb referring base modern table reach, complemented update rest level in extended `DOCUMENTATION.md`.

Local inline full table moves remain exact legacies defined anywhere entry in own coding language — using table above quick transliteration.

## License

MIT — share, build, pull the flight endless forests—nature sang idea poetry steel

*"E assim da braque vis s . all sky sound part still active between born remain never ceases motion wing and law quietude content eternal brave spirit text to text; line onward big code singular delivering:*