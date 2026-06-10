# O Grande Código da Gralha Azul

**The Great Code of the Azure Jay**

A CRSF-controlled servo ornithopter (wing-flapping bird flight simulator) with NeoPixel LED, inspired by the legend of the *Gralha Azul* (Azure Jay) — the guardian of the Araucaria forests of southern Brazil.

> *"Nas eras antigas, quando o aroma dos pinheirais sagrados pairava como prece..."*
> *(In ancient times, when the scent of sacred pine groves hung like prayer...)*

---

## Table of Contents

- [Hardware Requirements](#hardware-requirements)
- [Wiring](#wiring)
- [ExpressLRS / CRSF Setup](#expresslrs--crsf-setup)
- [CRSF Channel Mapping](#crsf-channel-mapping)
- [Flashing with Arduino IDE](#flashing-with-arduino-ide)
- [Configuration](#configuration)
- [How It Works](#how-it-works)
  - [Flight Modes](#flight-modes)
  - [Wing Beat Generation](#wing-beat-generation)
  - [Servo Mixing](#servo-mixing)
  - [LED Animation](#led-animation)
- [Altitude-Hold — O Par Alado](#altitude-hold--o-par-alado)
- [LED Animation](#led-animation)
- [Debug Output & Flight Performance](#debug-output--flight-performance)
- [Portuguese Name Reference](#portuguese-name-reference)
- [License](#license)

---

## Hardware Requirements

| Component | Example / Notes |
|-----------|----------------|
| **Microcontroller** | Waveshare RP2040 Zero (or any RP2040 with 2+ UARTs) |
| **RC Receiver** | ExpressLRS receiver with CRSF output (e.g., Happymodel EP2 with ceramic antenna — the tiny favourite) |
| **Servos × 2** | Recommended: KST MS320, PTK 7465W MG, Blue Arrow DS 43 AF 6.0, Blue Arrow D0576HT MG |
| **NeoPixel LED** | WS2812B (or compatible), single pixel — may be coupled to an optic glass fibre strand for in-flight light effects |
| **Battery** | 1S LiPo (3.7V) or 2S LiPo (7.4V) with BEC for servos |
| **BEC / External 5V** | Required for servo power — **do not power servos from the RP2040's internal 3.3V regulator** |
| **Barometer** | BMP180 / BMP085 I2C barometer (Elecrow) — for thermal detection | |

### Pin Allocation (Waveshare RP2040 Zero)

| Pin | Function | Portuguese Name | Meaning |
|-----|----------|----------------|---------|
| GPIO 8 | Servo — Left Wing | `ARTICULACAO_ASA_DA_MANHA` | Morning Wing Joint |
| GPIO 7 | Servo — Right Wing | `ARTICULACAO_ASA_DO_ENTARDECER` | Evening Wing Joint |
| GPIO 0 | CRSF TX (yellow wire) | `VIA_DOS_ECOS_SOLARES` | Path of Solar Echoes |
| GPIO 1 | CRSF RX (white/blue wire) | `VIA_DOS_SONHOS_LUNARES` | Path of Lunar Dreams |
| GPIO 16 | NeoPixel — internal LED of RP2040 Zero | `NUCLEO_DA_CHAMA_AZUL` | Core of the Blue Flame |
| GPIO 4 | BMP180 SDA (I2C0/Wire) | `PINO_SILENCIO_DA_ALTURA` | Silence of the Height |
| GPIO 5 | BMP180 SCL (I2C0/Wire) | `PINO_RITMO_DA_PRESSAO` | Rhythm of the Pressure |

All pins are configurable via `#define` at the top of the sketch:

```cpp
#define PINO_ASA_DA_MANHA      8   // ARTICULACAO_ASA_DA_MANHA — Left wing servo
#define PINO_ASA_DO_ENTARDECER 7   // ARTICULACAO_ASA_DO_ENTARDECER — Right wing servo
#define PINO_ECOS_SOLARES      0   // VIA_DOS_ECOS_SOLARES — CRSF TX
#define PINO_SONHOS_LUNARES    1   // VIA_DOS_SONHOS_LUNARES — CRSF RX
#define PINO_CHAMA_AZUL       16   // NUCLEO_DA_CHAMA_AZUL — NeoPixel
#define PINO_SILENCIO_DA_ALTURA    4   // SILENCIO_DA_ALTURA — BMP180 SDA (I2C0/Wire)
#define PINO_RITMO_DA_PRESSAO    5   // RITMO_DA_PRESSAO — BMP180 SCL (I2C0/Wire)
```

---
=======

## Wiring

### CRSF Receiver (ExpressLRS)

```
RP2040 Zero              ELRS Receiver (e.g., Radiomaster ER4)
┌─────────────┐          ┌──────────────────┐
│ GPIO 0 (TX) ──────────► RX               │  (yellow wire — solar echoes)
│ GPIO 1 (RX) ◄────────── TX               │  (white or blue wire — lunar sounds)
│             │          │                  │
│ 3.3V       ───────────► VCC (3.3V input) │
│ GND        ───────────► GND              │
└─────────────┘          └──────────────────┘
```

**Important:** Some ELRS receivers operate at 3.3V, others at 5V, and many support both. Check your receiver's specifications. The RP2040 Zero's 3.3V output is sufficient for 3.3V receivers. For 5V receivers, power VCC from the external BEC/battery (same source as servos). Do **not** connect receiver VCC to the RP2040's 3.3V output if the receiver requires 5V.

**Wire colour guide:** Use a **yellow** wire for `VIA_DOS_ECOS_SOLARES` (GPIO 0 / TX → receiver RX — the solar echoes sent out) and a **white or blue** wire for `VIA_DOS_SONHOS_LUNARES` (GPIO 1 / RX ← receiver TX — the lunar dreams received). This follows the code's poetic colour symbolism: golden sunlight out, serene moonlight in.

### Servos (External Power)

```
External 5V BEC / Battery
┌──────────────────────┐
│ 5V+ ────────────────► Servo Power (red wires, both servos)
│ GND ────────────────► Servo GND (black/brown wires, both servos)
│                     │   AND ──► RP2040 GND (common ground!)
└──────────────────────┘

RP2040 Zero              Servo Left Wing (GPIO 5)
┌─────────────┐          ┌──────────────────┐
│ GPIO 5      ──────────► Signal (white/yellow)
└─────────────┘          └──────────────────┘

RP2040 Zero              Servo Right Wing (GPIO 7)
┌─────────────┐          ┌──────────────────┐
│ GPIO 7      ──────────► Signal (white/yellow)
└─────────────┘          └──────────────────┘
```

**Critical:** Servos draw significant current. The RP2040's internal regulator cannot supply this. Always use an external BEC or battery for servo power. Connect **all grounds** (RP2040, servos, receiver, BEC) together.

### NeoPixel — Internal LED (Optional Fibre Optic)

The RP2040 Zero has a **built-in NeoPixel (WS2812B)** on GPIO 16. No external wiring is needed — the LED is already on the board.

If you wish to use an **external optic glass fibre** for in-flight light effects, you can couple the internal LED to a fibre strand that runs along the bird's body or wing. The LED pulses and shifts colour in sync with the wingbeat phase and control inputs (pitch, throttle, rhythm), creating a luminous "soul fire" effect in flight.

> **Note:** The internal LED is sufficient for bench testing and low-light flight. For bright daylight visibility, consider adding an external high-brightness NeoPixel on the same GPIO line.

### BMP180 Barometer — O Oráculo da Pressão *(optional)*

The BMP180 I2C barometer listens for invisible shifts in pressure — the oracle that senses the sky's whispers.
**Enabled by:** `#define ORACULO_DA_PRESSAO_DO_CEU` at the top of the sketch. Without this define, no barometer libraries are required.

```
BMP180 Module            RP2040 Zero
┌──────────────┐        ┌───────────────┐
│ VCC          ─────────► 3V3           │  (ALIMENTO_DO_ORACULO)
│ GND          ─────────► GND           │  (TERRA_DO_ORACULO)
│ SDA (GP4)    ─────────► GPIO 4        │  (PINO_SILENCIO_DA_ALTURA — I2C0 SDA)
│ SCL (GP5)    ─────────► GPIO 5        │  (PINO_RITMO_DA_PRESSAO — I2C0 SCL)
└──────────────┘        └───────────────┘
```

The barometer uses the **I2C0 (Wire)** bus (GPIO 4/5).

---

## ExpressLRS / CRSF Setup

This project uses the **CRSF protocol** (Crossfire) to communicate between the flight controller and an **ExpressLRS (ELRS)** receiver. Understanding the relationship between ELRS and CRSF is essential for correct setup.

### ELRS vs CRSF

| Term | Description |
|------|-------------|
| **ExpressLRS (ELRS)** | An open-source RC link protocol (the RF layer between transmitter and receiver). It operates on 2.4 GHz or 868/915 MHz. |
| **CRSF (Crossfire)** | The serial protocol used **between the receiver and the flight controller**. ELRS receivers output CRSF over UART. |

In this project, the RP2040 talks **CRSF** to the ELRS receiver. The receiver handles the RF link to your transmitter.

### Transmitter Setup (EdgeTX / OpenTX)

1. **Install ExpressLRS on your transmitter module** (e.g., Radiomaster Ranger, internal ELRS module)
2. **Flash the receiver** with the same ELRS firmware version and binding phrase as your transmitter
3. **Bind** the receiver to your transmitter

### Receiver Configuration

Configure these ELRS receiver parameters via the **ExpressLRS Lua script** on your transmitter or via WiFi:

| Parameter | Required Setting | Reason |
|-----------|-----------------|--------|
| **Protocol** | `CRSF` | The receiver must output CRSF over UART |
| **Baud Rate** | `420000` (420k) | Must match `FREQUENCIA_DO_SOPRO_COSMICO` in the code |
| **Packet Rate** | `50 Hz` (or higher) | Standard for CRSF; higher rates reduce latency |
| **Telem Ratio** | `1:2` or `1:4` | Controls how often telemetry is sent back; higher ratios reduce RC channel update rate |
| **Model Match** | Enabled (optional) | Prevents flying with the wrong model selected |

**Important:** The baud rate in the ELRS WiFi/web configuration tool must be set to **420000** — the same value as `FREQUENCIA_DO_SOPRO_COSMICO` in the code. If you change this constant, update the ELRS receiver's baud rate accordingly.

## CRSF Channel Mapping

The receiver communicates via CRSF protocol over UART at 420000 baud. The following channels are used:

| Channel | Portuguese Name | Translation | Function | Range |
|---------|----------------|-------------|----------|-------|
| CH1 | `voz_do_aletao` | Voice of the Aileron | Roll / Bank | 1000–2000 (center 1500) |
| CH2 | `voz_do_profundor` | Voice of the Elevator | Pitch / Dive & Climb | 1000–2000 (center 1500) |
| CH3 | `voz_do_sopro_vital` | Voice of the Vital Breath | Throttle / Wingbeat intensity | 1000–2000 |
| CH4 | `voz_do_leme_estelar` | Voice of the Starry Rudder | Yaw / Differential steering | 1000–2000 (center 1500) |
| CH5 | `voz_do_despertar` | Voice of the Awakening | Arm / Disarm | 1000–2000 (arm > 1500) |
| CH6 | `voz_do_compasso_da_alma` | Voice of the Soul's Compass | Rhythm modulation | 1000–2000 (center 1500) |
| CH7 | `voz_da_ferocidade_do_bater` | Voice of the Downstroke Ferocity | Downstroke sharpness | 1000–2000 |
| CH8 | `voz_da_ferocidade_do_retorno` | Voice of the Upstroke Ferocity | Upstroke sharpness | 1000–2000 |
| CH9 | `voz_da_ferocidade_do_leme` | Voice of the Rudder Ferocity | Rudder ferocity (differential) | 1000–2000 |
| CH10 | `voz_do_sustentar_altura` | Voice of Sustaining the Height | Altitude-Hold (activate > 1500) | 1000–2000 (active > 1500) |

---

## Flashing with Arduino IDE

### 1. Install Board Support

1. Open **Arduino IDE** → **File** → **Preferences**
2. Add this URL to **Additional Boards Manager URLs**:
   ```
   https://github.com/earlephilhower/arduino-pico/releases/download/global/package_rp2040_index.json
   ```
3. Go to **Tools** → **Board** → **Boards Manager**
4. Search for **"Raspberry Pi Pico/RP2040"** by Earle F. Philhower
5. Click **Install**

### 2. Install Libraries

Go to **Tools** → **Manage Libraries** and install:

| Library | Author | Version | Notes |
|---------|--------|---------|-------|
| **CRSF** | Simon H | ≥ 1.0 | **Important:** The library is named **"CRSF"** in the Arduino Library Manager, but the header file is `CrsfSerial.h`. There are multiple libraries with a file named `CrsfSerial.h` — ensure only the correct one (by Simon H) is present in your libraries folder. Remove any conflicting copies. |
| **Adafruit NeoPixel** | Adafruit | ≥ 1.12 | |

**Library conflict warning:** Several RC-related libraries ship their own `CrsfSerial.h`. If you encounter compilation errors (e.g., missing `CrsfSerial` class), check that no other library in your `libraries/` folder contains a `CrsfSerial.h` file. The correct library is **"CRSF" by Simon H** — search for it by name in the Library Manager.

### 3. Select Board

- **Board:** *Raspberry Pi RP2040 Boards* → *Waveshare RP2040 Zero*
- **Flash Size:** *2MB (no FS)*
- **CPU Speed:** *133 MHz*
- **Optimize:** *Smaller (-Os)* (default)

### 4. Upload

1. Connect the RP2040 Zero via USB while holding the **BOOT** button
2. Select the correct **Port**
3. Click **Upload**

> **Note:** The RP2040 Zero appears as a mass storage device when in bootloader mode. The Arduino IDE handles this automatically.

---

## Configuration

All configurable parameters are `#define` constants at the top of the sketch:

| Constant | Default | Description |
|----------|---------|-------------|
| `FREQUENCIA_DO_SOPRO_COSMICO` | 420000 | CRSF UART baud rate |
| `CICLO_DO_CORACAO_ALADO` | 0.052 | Wingbeat cycle period (seconds) — base frequency ~19 Hz |
| `LIMIAR_DO_VOO_ATIVO` | 1040 | Throttle threshold to enter flapping mode (CRSF value) |
| `LIMIAR_DO_VOO_ATIVO_HISTERESE` | 20 | Hysteresis band to prevent mode oscillation |
| `ANGULO_DO_PLANAR_SERENO` | -4 | Glide angle offset (degrees) when soaring |
| `ORIGEM_ASA_MATUTINA` | 0 | Left wing neutral position offset (degrees) |
| `ORIGEM_ASA_VESPERTINA` | 0 | Right wing neutral position offset (degrees) |
| `ALTURA_MAX_DO_SUSTENTAR_M` | 20.0 | Max altitude for Altitude-Hold (CH3 = 2000 → 20 m) |
| `SOPRO_MIN_DO_SUSTENTAR` | 1100 | Minimum wingbeat intensity in Hold mode (µs) |
| `SOPRO_MAX_DO_SUSTENTAR` | 1800 | Maximum wingbeat intensity in Hold mode (µs) |
| `FORCA_DO_SUSTENTAR` | 180 | P-gain for Altitude-Hold (height error → throttle) |
| `SILENCIO_DO_SUSTENTAR_M` | 0.5 | Deadband in meters (hysteresis) |
| `LIMITE_DA_DESCIDA_SUSTENTADA_MS` | 2.0 | Max sink rate limit (m/s) |
| `LIMITE_DA_SUBIDA_SUSTENTADA_MS` | 3.0 | Max climb rate limit (m/s) |

### Barometer — O Oráculo da Pressão (optional)

Uncomment this line to enable the BMP180 barometer:

```cpp
#define ORACULO_DA_PRESSAO_DO_CEU
```

Barometer variables (only available when enabled):

| Variable | Unit | Description |
|----------|------|-------------|
| `pressao_do_ceu_hpa` | hPa | Atmospheric pressure |
| `temperatura_do_ar_c` | °C | Air temperature |
| `altura_do_voo_sideral` | m | Relative altitude (start average subtracted) |
| `subida_da_gralha_ms` | m/s | Instantaneous vertical speed |
| `sopro_da_subida_alada` | m/s | Low-pass filtered vertical speed (0.85/0.15) |
| `tendencia_da_temperatura_c` | °C | Temperature trend |
| `fe_no_sopro_quente` | — | Thermal confidence (`sopro_da_subida_alada + tendencia * 0.3`) |

Telemetry: `SussurrarVooAoEter()` sends altitude (as GPS alt + 1000) and temperature (as battery voltage × 100) via CRSF every 200/500 ms.

### Debug Mode

Uncomment this line to enable serial debug output at 115200 baud:

```cpp
#define ECOS_PRESCINDIVEIS_DA_ALMA_ALADA
```

**⚠️ Flight performance warning:** When debug output is enabled, the extensive `Serial.print()` calls consume significant CPU time and can degrade servo update timing. **Always disable debug mode for actual flight.** Use it only for bench testing and tuning.

---

## How It Works

### Flight Modes

The ornithopter has two states and two flight modes:

**States** (`EstadoDaAlmaAlada`):
- `EM_DANCA_COM_OS_VENTOS` (Dancing with the Winds) — CRSF link is active, the bird is responsive
- `EM_SONHO_NA_QUIETUDE_DA_FLORESTA` (Dreaming in the Forest's Quiet) — CRSF link is lost, servos go to neutral, LED shows a slow forest-color cycle

**Flight Modes** (`ModoDoEspiritoAlado`):
- `EM_RITMO_DE_BATIDA_DAS_ASAS` (Rhythm of Wing Beats) — Active flapping when throttle > 1040
- `EM_DESLIZE_ETERNO_E_CONTEMPLATIVO` (Eternal Contemplative Glide) — Soaring/gliding when throttle ≤ 1040

The transition between flapping and gliding uses **hysteresis** (±20 CRSF units) to prevent rapid oscillation when the throttle stick is near the threshold.

### Wing Beat Generation

The wingbeat is generated by a **phase-accumulator oscillator**:

1. **Target cadence** (`intencao_de_cadencia`) is derived from throttle (CH3) and rhythm modulation (CH6)
2. **Angular acceleration** (`variacao_do_destino_alado`) applies damping (`-10.0 * cadencia`) for smooth transitions
3. **Phase angle** (`angulo_da_danca_alada`) integrates the cadence over time
4. **Sine wave** (`sin(angulo_da_danca_alada)`) produces the base wing motion

The **wingbeat waveform** is shaped by the `forma_do_bater_das_asas()` function, which applies a `tanh`-based distortion:

- **Downstroke** uses `voz_da_ferocidade_do_bater` (CH7) — higher values = sharper, more aggressive downstroke
- **Upstroke** uses `voz_da_ferocidade_do_retorno` (CH8) — higher values = quicker recovery
- **Rudder ferocity** (CH9) is applied differentially — left wing gets +CH9, right wing gets −CH9
- **Each servo** gets its own `forma_do_bater_das_asas()` calculation with individual ferocity

This creates an asymmetric wingbeat: a powerful downstroke (thrust) and a gentler upstroke (recovery), mimicking natural bird flight. Yaw is achieved by mixing CH4 differentially onto the two wing outputs in the transmitter.

### Servo Mixing

The two wing servos are mixed with roll (CH1), pitch (CH2), and yaw (CH4) for full 3-axis control:

```
Left Wing  = Roll - WingBeat - Pitch
Right Wing = Roll + WingBeat + Pitch
```

- **Roll** (CH1): Both wings move together — bank left/right
- **Pitch** (CH2): Differential — dive (both wings forward) or climb (both wings back)
- **Yaw** (CH4): Mixing is done in the transmitter, not in code

**Rudder ferocity (CH9):**
CH9 (`voz_da_ferocidade_do_leme`) is applied differentially: left wing ferocity is increased by CH9, right wing ferocity is decreased by CH9 (or vice versa). This creates asymmetric wingbeats for yaw control.

In **glide mode**, the wings are set to a fixed angle (`ANGULO_DO_PLANAR_SERENO` = -4°) plus roll and pitch inputs, allowing the bird to soar like a real bird.

### Altitude-Hold — O Sustentar da Altura

When CH10 (`voz_do_sustentar_altura`) > 1500, the bird enters Altitude-Hold mode:

- **CH3 (Throttle)** becomes the **target altitude setpoint** — 1000 µs = 0 m, 2000 µs = `ALTURA_MAX_DO_SUSTENTAR_M` (default 20 m)
- The barometer (`ORACULO_DA_PRESSAO_DO_CEU` must be enabled) provides altitude feedback
- A P-controller with hysteresis adjusts the wingbeat intensity (`sopro_vital_do_sustentar`), replacing the pilot's direct throttle
- The altitude error drives the servo pulse between `SOPRO_MIN_DO_SUSTENTAR` (1100 µs) and `SOPRO_MAX_DO_SUSTENTAR` (1800 µs)
- Sink and climb rates are limited (`LIMITE_DA_DESCIDA_SUSTENTADA_MS` / `LIMITE_DA_SUBIDA_SUSTENTADA_MS`) to prevent abrupt throttle changes
- In gliding mode (throttle stick below threshold), the Hold still applies — no need to keep the throttle stick up

When CH10 < 1500, the pilot regains full manual throttle control.

### LED Animation

The NeoPixel (`NUCLEO_DA_CHAMA_AZUL` / Core of the Blue Flame) reflects the bird's state:

| State | Mode | LED Behavior |
|-------|------|-------------|
| Flying | Flapping | Blue-green with brightness pulsing in sync with wingbeat |
| Flying | Gliding | Steady soft blue-green, modulated by pitch |
| Sleeping | — | Slow color cycle alternating between forest greens and night blues |

The LED may be coupled to an **optic glass fibre strand** that runs along the bird's body or wing structure. As the LED pulses and shifts colour with the wingbeat phase and control inputs (pitch, throttle, rhythm), the fibre glows like a living ember — the "soul fire" of the Gralha Azul illuminating the flight.

---

## Debug Output & Flight Performance

When `ECOS_PRESCINDIVEIS_DA_ALMA_ALADA` is enabled, the sketch outputs telemetry at ~4 Hz over Serial (115200 baud):

```
VOANDO | Modo: RITMADO | SoproV: 1500 | Alet: 1500 | Prof: 1500 | Leme: 1500 | Compasso: 1500 | FerBater: 1000 | FerRetorno: 1000 | Fase: 3.14 | Cadencia: 18.50
```

| Field | Meaning |
|-------|---------|
| `VOANDO` / `SONHANDO` | Link state (Flying / Dreaming) |
| `Modo` | `RITMADO` (flapping) or `PLANANDO` (gliding) |
| `SoproV` | Raw CH3 value (throttle) |
| `Alet` | Raw CH1 value (roll) |
| `Prof` | Raw CH2 value (pitch) |
| `Leme` | Raw CH4 value (yaw) |
| `Compasso` | Raw CH6 value (rhythm) |
| `FerBater` | Raw CH7 value (downstroke ferocity) |
| `FerRetorno` | Raw CH8 value (upstroke ferocity) |
| `FerLeme` | Raw CH9 value (rudder ferocity) |
| `Despertar` | Raw CH5 value (arm/disarm) |
| `BaroAlt` | Barometric altitude (m) — `altura_do_voo_sideral` |
| `Vario` | Vertical speed (m/s) — `subida_da_gralha_ms` |
| `Temp` | Barometer temperature (°C) — `temperatura_do_ar_c` |
| `Termal` | Thermal confidence — `fe_no_sopro_quente` |
| `Sustentar` | Altitude-Hold active flag (0/1) — `modo_sustentar_ativo` |
| `SoproSustentar` | Altitude-Hold throttle output (µs) — `sopro_vital_do_sustentar` |
| `Fase` | Current wingbeat phase angle (radians) |
| `Cadencia` | Current wingbeat cadence (rad/s) |

**⚠️ Critical flight note:** Debug output uses `Serial.print()` extensively, which blocks the main loop and consumes significant CPU time. This can cause servo update jitter and degraded flight performance. **Always disable debug (`#define ECOS_PRESCINDIVEIS_DA_ALMA_ALADA` commented out) for actual flight.**

---

## Portuguese Name Reference

The code uses poetic Portuguese names for all identifiers. This table maps them to their functional English equivalents:

| Portuguese (Code) | English (Function) |
|-------------------|-------------------|
| `O Grande Código da Gralha Azul` | The Great Code of the Azure Jay |
| `Gralha Azul` | Azure Jay (*Cyanocorax caeruleus*) |
| `FREQUENCIA_DO_SOPRO_COSMICO` | CRSF Baud Rate (Cosmic Breath Frequency) |
| `PORTAL_DOS_VENTOS_CELESTES` | CRSF Serial Port (Portal of Celestial Winds) |
| `guardiao_dos_ventos_siderais` | CRSF Serial Object (Guardian of Sidereal Winds) |
| `ARTICULACAO_ASA_DA_MANHA` | Left Wing Servo Pin (Morning Wing Joint) |
| `ARTICULACAO_ASA_DO_ENTARDECER` | Right Wing Servo Pin (Evening Wing Joint) |
| `VIA_DOS_SONHOS_LUNARES` | CRSF RX Pin (Path of Lunar Dreams) |
| `VIA_DOS_ECOS_SOLARES` | CRSF TX Pin (Path of Solar Echoes) |
| `NUCLEO_DA_CHAMA_AZUL` | NeoPixel Pin (Core of the Blue Flame) |
| `QUANTIDADE_DE_CENTELHAS_NA_CHAMA` | NeoPixel LED Count (Number of Sparks in the Flame) |
| `CICLO_DO_CORACAO_ALADO` | Wingbeat Period (Winged Heart Cycle) |
| `LIMIAR_DO_VOO_ATIVO` | Throttle Threshold (Active Flight Threshold) |
| `LIMIAR_DO_VOO_ATIVO_HISTERESE` | Mode Switch Hysteresis |
| `ANGULO_DO_PLANAR_SERENO` | Glide Angle Offset (Serene Glide Angle) |
| `ORIGEM_ASA_MATUTINA` | Left Wing Neutral (Morning Wing Origin) |
| `ORIGEM_ASA_VESPERTINA` | Right Wing Neutral (Evening Wing Origin) |
| `VIBRACAO_NEUTRA_DO_ALETAO` | CH1 Neutral (Neutral Aileron Vibration) |
| `VIBRACAO_NEUTRA_DO_PROFUNDOR` | CH2 Neutral (Neutral Elevator Vibration) |
| `VIBRACAO_MINIMA_DO_SOPRO_VITAL` | CH3 Minimum (Minimum Vital Breath Vibration) |
| `VIBRACAO_NEUTRA_DO_LEME_ESTELAR` | CH4 Neutral (Neutral Starry Rudder Vibration) |
| `VIBRACAO_NEUTRA_DO_COMPASSO_DA_ALMA` | CH6 Neutral (Neutral Soul's Compass Vibration) |
| `VIBRACAO_MINIMA_DA_FEROCIDADE` | CH5/CH7/CH8 Minimum (Minimum Ferocity Vibration) |
| `EstadoDaAlmaAlada` | Link State (Winged Soul State) |
| `EM_DANCA_COM_OS_VENTOS` | Link Up (Dancing with the Winds) |
| `EM_SONHO_NA_QUIETUDE_DA_FLORESTA` | Link Down (Dreaming in the Forest's Quiet) |
| `ModoDoEspiritoAlado` | Flight Mode (Winged Spirit Mode) |
| `EM_RITMO_DE_BATIDA_DAS_ASAS` | Flapping Mode (Rhythm of Wing Beats) |
| `EM_DESLIZE_ETERNO_E_CONTEMPLATIVO` | Glide Mode (Eternal Contemplative Glide) |
| `relogio_das_eras` | Timing Structure (Clock of the Ages) |
| `voz_do_aletao` | CH1 Value (Voice of the Aileron) |
| `voz_do_profundor` | CH2 Value (Voice of the Elevator) |
| `voz_do_sopro_vital` | CH3 Value (Voice of the Vital Breath) |
| `voz_do_despertar` | CH5 Value (Voice of the Awakening) | Arm/Disarm |
| `voz_do_compasso_da_alma` | CH6 Value (Voice of the Soul's Compass) | Rhythm modulation |
| `voz_da_ferocidade_do_bater` | CH7 Value (Voice of the Downstroke Ferocity) | Downstroke sharpness |
| `voz_da_ferocidade_do_retorno` | CH8 Value (Voice of the Upstroke Ferocity) | Upstroke sharpness |
| `voz_da_ferocidade_do_leme` | CH9 Value (Voice of the Rudder Ferocity) | Rudder ferocity (differential) |
| `pressao_do_ceu_hpa` | Barometric pressure (hPa) | Atmospheric pressure |
| `temperatura_do_ar_c` | Air temperature (°C) | Barometer temperature |
| `altura_do_voo_sideral` | Barometric altitude (m) | Sidereal flight altitude (relative) |
| `subida_da_gralha_ms` | Vertical speed (m/s) | Instantaneous vario |
| `sopro_da_subida_alada` | Filtered vertical speed (m/s) | Low-pass vario (0.85/0.15) |
| `fe_no_sopro_quente` | Thermal confidence | `sopro_da_subida_alada + tendencia * 0.3` |
| `tendencia_da_temperatura_c` | Temperature trend (°C) | Thermal trend signal |
| `modo_de_escuta_termal` | Thermal listening mode | Thermal assist flag |
| `DespertarOraculoDaPressao()` | Barometer init | BMP180 initialization (non-blocking) |
| `EscutarPressaoDoCeu()` | Barometer update | Read pressure/altitude/temp every 100ms |
| `SustentarAltura()` | Altitude-Hold | P-controller for baro-based altitude hold |
| `SussurrarVooAoEter()` | CRSF telemetry | Send altitude & temp via CRSF |
| `voz_do_sustentar_altura` | CH10 Value (Voice of Sustaining the Height) | Altitude-Hold activation (> 1500) |
| `modo_sustentar_ativo` | Altitude-Hold active | Flag when CH10 > 1500 |
| `sopro_vital_do_sustentar` | Hold throttle output (µs) | Calculated wingbeat intensity in Hold mode |
| `altura_desejada_do_voo` | Target altitude (m) | Derived from CH3 in Hold mode |
| `pergaminho_do_voo` | CRSF GPS telemetry frame | Pergament of flight (altitude data) |
| `bilhete_do_sopro_quente` | CRSF battery telemetry frame | Billete of warm breath (temperature data) |
| `ultimo_sopro_sideral` | Last CRSF GPS send time | Last sidereal breath timestamp |
| `ultimo_sopro_termico` | Last CRSF battery send time | Last thermal breath timestamp |
| `angulo_da_danca_alada` | Wingbeat Phase Angle (Winged Dance Angle) |
| `cadencia_do_destino_alado` | Wingbeat Cadence (Winged Destiny Cadence) |
| `pulso_do_sopro_vital` | Wingbeat Waveform (Vital Breath Pulse) |
| `mapear_entre_escalas_harmonicas` | Map Function (Harmonic Scale Mapping) |
| `forma_do_bater_das_asas` | Wingbeat Shape Function (Wing Beat Shape) |
| `MantoDeLuzCelestial` | NeoPixel Controller Class (Celestial Light Mantle) |
| `chama_azul_pixel` | NeoPixel Object (Blue Flame Pixel) |
| `tonalidade_do_sonho_florestal` | Sleep Color Cycle (Forest Dream Hue) |
| `AcenderLuzPrimordial` | `begin()` (Ignite the Primordial Light) |
| `IrradiarLuzDaAlma` | `show()` update (Radiate the Soul's Light) |
| `manto_celestial_da_gralha` | NeoPixel Instance (Celestial Mantle of the Jay) |
| `motor_asa_matutina` | Left Wing Servo (Morning Wing Motor) |
| `motor_asa_vespertina` | Right Wing Servo (Evening Wing Motor) |
| `AoDespertarParaOCantoDoEter` | Link Up Callback (Awakening to the Ether's Song) |
| `AoRecolherSeAoSilencioDaMata` | Link Down Callback (Retreating to the Forest's Silence) |
| `InterpretarAsVozesDoFirmamento` | Channel Update Callback (Interpreting the Firmament's Voices) |
| `AnimarPulsarDoCoracaoAlado` | Wingbeat Update (Animating the Winged Heart Pulse) |
| `ManifestarOVooNosVentos` | Servo Output (Manifesting Flight in the Winds) |
| `ECOS_PRESCINDIVEIS_DA_ALMA_ALADA` | Debug Flag (Dispensable Echoes of the Winged Soul) |

---

## License

This project is open source. The code is poetry, the poetry is code — share it, fly with it, plant seeds with it.

*"E assim, o Grande Código da Gralha Azul se manifesta, em cada ciclo, um testemunho alado da resiliência da vida, da magia da transformação, e da perene esperança semeada entre o céu e a terra, um poema vivo, a canção da floresta que jamais se calará."*