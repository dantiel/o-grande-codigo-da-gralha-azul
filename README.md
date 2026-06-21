# O Grande Código da Gralha Azul

**The Great Code of the Azure Jay**

An RP2040 Zero servo ornithopter (wing-flapping bird flight simulator) with CRSF or PPM receiver input, NeoPixel LED, and optional barometric altitude hold — inspired by the legend of the *Gralha Azul* (Azure Jay), the guardian of the Araucaria forests of southern Brazil.

> *"Nas eras antigas, quando o aroma dos pinheirais sagrados pairava como prece..."*
> *(In ancient times, when the scent of sacred pine groves hung like prayer...)*

---

## Table of Contents

- [Hardware Requirements](#hardware-requirements)
- [Wiring](#wiring)
- [Receiver Selection — The #define Switch](#receiver-selection--the-define-switch)
- [Channel Mapping (Dual Mode)](#channel-mapping-dual-mode)
- [PPM Mode Specifics](#ppm-mode-specifics)
- [ExpressLRS / CRSF Setup](#expresslrs--crsf-setup)
- [Flashing with Arduino IDE](#flashing-with-arduino-ide)
- [Configuration](#configuration)
- [How It Works](#how-it-works)
  - [Flight Modes](#flight-modes)
  - [Wing Beat Generation](#wing-beat-generation)
  - [Servo Mixing](#servo-mixing)
  - [Altitude-Hold — O Sustentar da Altura](#altitude-hold--o-sustentar-da-altura)
  - [LED Animation](#led-animation)
- [Debug Output & Flight Performance](#debug-output--flight-performance)
- [Portuguese Name Reference](#portuguese-name-reference)
- [License](#license)

---

## Hardware Requirements

| Component | Example / Notes |
|-----------|----------------|
| **Microcontroller** | Waveshare RP2040 Zero (or any RP2040) |
| **RC Receiver** | ExpressLRS receiver with CRSF output (e.g., Happymodel EP2) — OR any PPM-capable receiver |
| **Servos × 2** | Recommended: KST MS320, PTK 7465W MG, Blue Arrow DS 43 AF 6.0, Blue Arrow D0576HT MG |
| **NeoPixel LED** | WS2812B (or compatible) — built-in on RP2040 Zero (GPIO 16) |
| **Battery** | 1S LiPo (3.7V) or 2S LiPo (7.4V) with BEC for servos |
| **BEC / External 5V** | Required for servo power — **do not power servos from the RP2040's internal 3.3V regulator** |
| **Barometer** *(optional)* | BMP180 / BMP085 I2C barometer — for thermal detection and altitude hold |

### Pin Allocation (Waveshare RP2040 Zero)

| Pin | Function | Portuguese Name |
|-----|----------|----------------|
| GPIO 8 | Servo — Left Wing | `ARTICULACAO_ASA_DA_MANHA` |
| GPIO 7 | Servo — Right Wing | `ARTICULACAO_ASA_DO_ENTARDECER` |
| GPIO 0 | CRSF TX (or unused in PPM mode) | `VIA_DOS_ECOS_SOLARES` |
| GPIO 1 | CRSF RX (or unused in PPM mode) | `VIA_DOS_SONHOS_LUNARES` |
| GPIO 2 | PPM Signal Input (PPM mode only) | Uses `PINO_DO_MENSAGEIRO` define |
| GPIO 16 | NeoPixel — internal LED | `NUCLEO_DA_CHAMA_AZUL` |
| GPIO 4 | BMP180 SDA (I2C0/Wire) | `PINO_SILENCIO_DA_ALTURA` |
| GPIO 5 | BMP180 SCL (I2C0/Wire) | `PINO_RITMO_DA_PRESSAO` |

---

## Wiring

### CRSF Receiver (ExpressLRS)

```
RP2040 Zero              ELRS Receiver
┌─────────────┐          ┌──────────────────┐
│ GPIO 0 (TX) ──────────► RX               │  (yellow wire — solar echoes)
│ GPIO 1 (RX) ◄────────── TX               │  (white or blue wire — lunar sounds)
│             │          │                  │
│ 3.3V       ───────────► VCC (3.3V input) │
│ GND        ───────────► GND              │
└─────────────┘          └──────────────────┘
```

**Important:** Some ELRS receivers operate at 3.3V, others at 5V. The RP2040 Zero's 3.3V output is sufficient for 3.3V receivers. For 5V receivers, power VCC from the external BEC/battery. Do **not** connect receiver VCC to the RP2040's 3.3V output if the receiver requires 5V.

**Wire colour guide:** Use a **yellow** wire for `VIA_DOS_ECOS_SOLARES` (GPIO 0 / TX → receiver RX) and a **white or blue** wire for `VIA_DOS_SONHOS_LUNARES` (GPIO 1 / RX ← receiver TX). Golden sunlight out, serene moonlight in.

### PPM Receiver

```
RP2040 Zero              PPM Receiver
┌─────────────┐          ┌──────────────────┐
│ GPIO 2      ◄────────── Signal (PPM sum)  │
│             │          │                  │
│ 3.3V       ───────────► VCC              │
│ GND        ───────────► GND              │
└─────────────┘          └──────────────────┘
```

Connect the PPM sum signal wire to **GPIO 2** (configurable via `#define PINO_DO_MENSAGEIRO`). The PPM frame carries up to 8 channels. CRSF pins (GPIO 0/1) remain unused.

### Servos (External Power)

```
External 5V BEC / Battery
┌──────────────────────┐
│ 5V+ ────────────────► Servo Power (red wires, both servos)
│ GND ────────────────► Servo GND (black/brown wires, both servos)
│                     │   AND ──► RP2040 GND (common ground!)
└──────────────────────┘

RP2040 Zero              Servo Left Wing (GPIO 8)
┌─────────────┐          ┌──────────────────┐
│ GPIO 8      ──────────► Signal (white/yellow)
└─────────────┘          └──────────────────┘

RP2040 Zero              Servo Right Wing (GPIO 7)
┌─────────────┐          ┌──────────────────┐
│ GPIO 7      ──────────► Signal (white/yellow)
└─────────────┘          └──────────────────┘
```

**Critical:** Servos draw significant current. The RP2040's internal regulator cannot supply this. Always use an external BEC or battery for servo power. Connect **all grounds** (RP2040, servos, receiver, BEC) together.

### NeoPixel — Internal LED

The RP2040 Zero has a **built-in NeoPixel (WS2812B)** on GPIO 16 — no external wiring needed. The LED pulses and shifts colour in sync with wingbeat, creating the "soul fire" of the Gralha Azul. May be coupled to an optic glass fibre for in-flight light effects.

### BMP180 Barometer — O Oráculo da Pressão *(optional)*

```
BMP180 Module            RP2040 Zero
┌──────────────┐        ┌───────────────┐
│ VCC          ─────────► 3V3           │
│ GND          ─────────► GND           │
│ SDA (GP4)    ─────────► GPIO 4        │  (PINO_SILENCIO_DA_ALTURA — I2C0 SDA)
│ SCL (GP5)    ─────────► GPIO 5        │  (PINO_RITMO_DA_PRESSAO — I2C0 SCL)
└──────────────┘        └───────────────┘
```

**Enabled by:** `#define ORACULO_DA_PRESSAO_DO_CEU` at the top of the sketch. Without this define, no barometer libraries are required.

---

## Receiver Selection — The #define Switch

At the top of the sketch, uncomment exactly **one** receiver type:

```cpp
#define RECEPTOR_DOS_VENTOS_CRSF      // CRSF via Serial1 (padrão)
// #define RECEPTOR_DOS_VENTOS_PPM     // PPM via PPMReaderRP2040 (pino 2)
```

| Receiver Mode | Library Required | Channels | Telemetry | Pins |
|---------------|------------------|----------|-----------|------|
| `RECEPTOR_DOS_VENTOS_CRSF` | **CRSF** by Sam4uk | 1–16 | Full CRSF telemetry (altitude, temp) | GPIO 0 (TX), GPIO 1 (RX), 420000 baud |
| `RECEPTOR_DOS_VENTOS_PPM` | **PPMReaderRP2040** ([github.com/dantiel/PPMReaderRP2040](https://github.com/dantiel/PPMReaderRP2040)) | 1–8 | None | GPIO 2 (Signal) |

---

## Channel Mapping (Dual Mode)

| CH | Hermetic Name | CRSF | PPM | Default | Description |
|----|---------------|------|-----|---------|-------------|
| 1 | `voz_do_aletao` | ✓ | ✓ | 1500 | Roll (aileron) |
| 2 | `voz_do_profundor` | ✓ | ✓ | 1500 | Pitch (elevator) |
| 3 | `voz_do_sopro_vital` | ✓ | ✓ | 1000 | Throttle / Altitude setpoint |
| 4 | `voz_do_leme_estelar` | ✓ | ✓ | 1500 | Yaw (rudder) |
| 5 | `voz_do_despertar` | ✓ | ✓ | 1000 | Arm/Disarm (>1500 = armed) |
| 6 | `voz_do_compasso_da_alma` | ✓ | ✓ | 1500 | Rhythm modulator (flapping frequency) |
| 7 | `voz_da_ferocidade_do_bater` | ✓ | ✓ | 1000 | Downstroke ferocity |
| 8 | `voz_da_ferocidade_do_retorno` | ✓ | ✓ | 1000 | Upstroke ferocity |
| 9 | `voz_da_ferocidade_do_leme` | ✓ | ✗ | 1500 (fixed) | Rudder ferocity (differential) |
| 10 | `voz_do_sustentar_altura` | ✓ | ✗ | 1000 (fixed) | Altitude hold gain (0–1) |

**PPM users:** CH9 and CH10 are not available via PPM (max 8 channels). They default to fixed values (1500 and 1000 respectively). To use the ferocity/altitude-hold features, switch to CRSF mode or mix CH9/10 from remaining transmitter channels onto a single PPM channel via your transmitter.

---

## PPM Mode Specifics

When using `RECEPTOR_DOS_VENTOS_PPM`:

- **Library:** [PPMReaderRP2040](https://github.com/dantiel/PPMReaderRP2040) — custom rewrite of the classic PPM library for RP2040, available as an Arduino library with full metadata.
- **Pin:** GPIO 2 (configurable via `#define PINO_DO_MENSAGEIRO 2`)
- **Channels:** Up to 8 channels (`#define NUM_CANAIS_DO_MENSAGEIRO 8`). CH9 and CH10 fall back to hardcoded defaults.
- **Telemetry:** Not available in PPM mode. The `SussurrarVooAoEter()` function is a no-op.
- **CRSF library:** Not required. Only PPMReaderRP2040, Servo, and Adafruit_NeoPixel are needed.
- **Link handling:** The PPM reader detects signal loss — when no valid PPM pulses are received, the bird enters `EM_SONHO_NA_QUIETUDE_DA_FLORESTA` (sleep) state.

---

## ExpressLRS / CRSF Setup

### ELRS vs CRSF

| Term | Description |
|------|-------------|
| **ExpressLRS (ELRS)** | The RF link between transmitter and receiver (2.4 GHz or 868/915 MHz) |
| **CRSF (Crossfire)** | The serial protocol **between the receiver and the RP2040** over UART |

### Transmitter Setup (EdgeTX / OpenTX)

1. Install ExpressLRS on your transmitter module
2. Flash the receiver with the same firmware and binding phrase
3. Bind the receiver to your transmitter

### Receiver Configuration

| Parameter | Required Setting | Reason |
|-----------|-----------------|--------|
| **Protocol** | `CRSF` | Must output CRSF over UART |
| **Baud Rate** | `420000` (420k) | Must match `FREQUENCIA_DO_SOPRO_COSMICO` |
| **Packet Rate** | `50 Hz` (or higher) | Standard for CRSF |
| **Telem Ratio** | `1:2` or `1:4` | Controls telemetry bandwidth |

**Important:** The baud rate in ELRS configuration must match `FREQUENCIA_DO_SOPRO_COSMICO` (default 420000).

---

## Flashing with Arduino IDE

### 1. Install Board Support

Add this URL to **Additional Boards Manager URLs**:
```
https://github.com/earlephilhower/arduino-pico/releases/download/global/package_rp2040_index.json
```
Install **"Raspberry Pi Pico/RP2040"** by Earle F. Philhower via Boards Manager.

### 2. Install Libraries

| Library | Author | When Needed |
|---------|--------|-------------|
| **CRSF** | Sam4uk | Only with `RECEPTOR_DOS_VENTOS_CRSF` |
| **PPMReaderRP2040** | [dantiel/PPMReaderRP2040](https://github.com/dantiel/PPMReaderRP2040) | Only with `RECEPTOR_DOS_VENTOS_PPM` |
| **Adafruit NeoPixel** | Adafruit | Always required |

**CRSF library:** Search for "CRSF" by Sam4uk in Library Manager, or get from [github.com/sam4uk/CRSF](https://github.com/sam4uk/CRSF).

**Library conflict warning:** Several RC libraries ship their own `CrsfSerial.h`. If you encounter compilation errors, ensure no other library in your `libraries/` folder contains a conflicting `CrsfSerial.h`.

### 3. Select Board

- **Board:** *Raspberry Pi RP2040 Boards* → *Waveshare RP2040 Zero*
- **Flash Size:** *2MB (no FS)*
- **CPU Speed:** *133 MHz*
- **Optimize:** *Smaller (-Os)* (default)

### 4. Upload

1. Connect the RP2040 Zero via USB while holding the **BOOT** button
2. Select the correct **Port**
3. Click **Upload**

---

## Configuration

All configurable parameters are `#define` constants at the top of the sketch:

| Constant | Default | Description |
|----------|---------|-------------|
| `RECEPTOR_DOS_VENTOS_CRSF` | defined | Enable CRSF receiver mode (default) |
| `RECEPTOR_DOS_VENTOS_PPM` | commented | Enable PPM receiver mode (alternative) |
| `FREQUENCIA_DO_SOPRO_COSMICO` | 420000 | CRSF UART baud rate |
| `CICLO_DO_CORACAO_ALADO` | 0.052 | Wingbeat cycle period (seconds) — base frequency ~19 Hz |
| `LIMIAR_DO_VOO_ATIVO` | 1040 | Throttle threshold for flapping mode |
| `LIMIAR_DO_VOO_ATIVO_HISTERESE` | 20 | Hysteresis band for mode switching |
| `ANGULO_DO_PLANAR_SERENO` | -4 | Glide angle offset (degrees) |
| `ORIGEM_ASA_MATUTINA` | 0 | Left wing neutral offset (degrees) |
| `ORIGEM_ASA_VESPERTINA` | 0 | Right wing neutral offset (degrees) |
| `ALTURA_MAX_DO_SUSTENTAR_M` | 20.0 | Max altitude for Altitude-Hold |
| `SOPRO_MIN_DO_SUSTENTAR` | 1100 | Minimum wingbeat intensity in Hold mode (µs) |
| `SOPRO_MAX_DO_SUSTENTAR` | 1800 | Maximum wingbeat intensity in Hold mode (µs) |
| `FORCA_BASE_DO_SUSTENTAR` | 180 | P-gain for Altitude-Hold |
| `SILENCIO_DO_SUSTENTAR_M` | 0.5 | Deadband in meters |
| `LIMITE_DA_DESCIDA_SUSTENTADA_MS` | 2.0 | Max sink rate limit (m/s) |
| `LIMITE_DA_SUBIDA_SUSTENTADA_MS` | 3.0 | Max climb rate limit (m/s) |

### Barometer — O Oráculo da Pressão *(optional)*

Uncomment to enable the BMP180 barometer:
```cpp
#define ORACULO_DA_PRESSAO_DO_CEU
```

Barometer variables (only available when enabled):

| Variable | Unit | Description |
|----------|------|-------------|
| `pressao_do_ceu_hpa` | hPa | Atmospheric pressure |
| `temperatura_do_ar_c` | °C | Air temperature |
| `altura_do_voo_sideral` | m | Relative altitude |
| `subida_da_gralha_ms` | m/s | Instantaneous vertical speed |
| `sopro_da_subida_alada` | m/s | Low-pass filtered vertical speed |
| `tendencia_da_temperatura_c` | °C | Temperature trend |
| `fe_no_sopro_quente` | — | Thermal confidence |

**Telemetry (CRSF mode only):** `SussurrarVooAoEter()` sends altitude (as GPS alt + 1000) and temperature (as battery voltage × 100) via CRSF every 200/500 ms.

### Debug Mode

```cpp
#define ECOS_PRESCINDIVEIS_DA_ALMA_ALADA
```

**⚠️ Flight performance warning:** Debug output uses `Serial.print()` extensively, consuming CPU time and degrading servo timing. **Always disable for flight.** Use only for bench testing.

---

## How It Works

### Flight Modes

**States** (`EstadoDaAlmaAlada`):
- `EM_DANCA_COM_OS_VENTOS` — Link active, bird responsive
- `EM_SONHO_NA_QUIETUDE_DA_FLORESTA` — Link lost, servos neutral, LED forest-cycle

**Flight Modes** (`ModoDoEspiritoAlado`):
- `EM_RITMO_DE_BATIDA_DAS_ASAS` — Flapping when throttle > 1040
- `EM_DESLIZE_ETERNO_E_CONTEMPLATIVO` — Gliding when throttle ≤ 1040

Mode transitions use hysteresis (±20 units) to prevent oscillation.

### Wing Beat Generation

The wingbeat uses a **phase-accumulator oscillator** with a critically-damped follower loop:

1. Target cadence derived from throttle (CH3) and rhythm modulation (CH6)
2. Damped acceleration (`erro * 8.0`) for smooth frequency transitions
3. Phase angle integrates cadence over time
4. Sine wave produces base wing motion

The **wingbeat waveform** is shaped by `forma_do_bater_das_asas()` with `tanh`-based distortion:

- Downstroke uses `voz_da_ferocidade_do_bater` (CH7)
- Upstroke uses `voz_da_ferocidade_do_retorno` (CH8)
- Rudder ferocity (CH9) applied differentially: left wing ±CH9
- Each servo gets individual ferocity calculation

### Servo Mixing

```
Left Wing  = Roll - WingBeat - Pitch
Right Wing = Roll + WingBeat + Pitch
```

- **Roll** (CH1): Both wings together — banking
- **Pitch** (CH2): Differential — dive/climb
- **Yaw** (CH4): Differential steering via ferocity asymmetry

In **glide mode**, wings set to `ANGULO_DO_PLANAR_SERENO` (-4°) plus roll/pitch.

### Altitude-Hold — O Sustentar da Altura

CH10 (`voz_do_sustentar_altura`) is a **continuous gain** (1000=0%, 2000=100%), not a switch:

| CH10 Value | Gain | Behavior |
|-----------|------|----------|
| 1000 | 0% | Altitude-Hold off — CH3 is direct throttle |
| 1500 | 50% | Hold active, half correction strength |
| 2000 | 100% | Hold active, full correction strength |

When active:
- CH3 sets target altitude: 1000=0m, 2000=`ALTURA_MAX_DO_SUSTENTAR_M` (20m)
- Barometer provides altitude feedback
- P-controller (gain scaled by CH10) adjusts wingbeat intensity between `SOPRO_MIN` (1100µs) and `SOPRO_MAX` (1800µs)
- Sink/climb rate limits prevent abrupt changes
- Hysteresis deadband (`SILENCIO_DO_SUSTENTAR_M`=0.5m) prevents oscillation

Barometer reads at 200ms intervals, temperature only every 5 cycles (~1s) due to thermal inertia.

### LED Animation

The NeoPixel (`NUCLEO_DA_CHAMA_AZUL`) reflects bird state:

| State | Mode | LED Behavior |
|-------|------|-------------|
| Flying | Flapping | Blue-green pulsing with wingbeat |
| Flying | Gliding | Steady soft blue-green, pitch-modulated |
| Sleeping | — | Slow forest-green / night-blue cycle |
| Disarmed (any) | — | Red pulse overlay on any state |

---

## Debug Output & Flight Performance

When `ECOS_PRESCINDIVEIS_DA_ALMA_ALADA` is enabled (115200 baud, ~4 Hz):

```
VOANDO | Modo: RITMADO | SoproV: 1500 | Alet: 1500 | Prof: 1500 | Leme: 1500 | Compasso: 1500 | ...
```

| Field | Meaning |
|-------|---------|
| `VOANDO` / `SONHANDO` | Link state |
| `Modo` | `RITMADO` or `PLANANDO` |
| `SoproV` | Raw CH3 (throttle) |
| `Alet` / `Prof` / `Leme` | CH1 / CH2 / CH4 (roll/pitch/yaw) |
| `Despertar` | CH5 (arm/disarm) |
| `Compasso` | CH6 (rhythm) |
| `FerBater` / `FerRetorno` / `FerLeme` | CH7 / CH8 / CH9 (ferocities) |
| `SustentarGain` | CH10 gain (0.00–1.00) |
| `SustentarCH10` | Raw CH10 value |
| `AltVoo` | Barometric altitude (m) |
| `Subida` | Vertical speed (m/s) |
| `SoproDoCeu` | Temperature (°C) |
| `FeNoSopro` | Thermal confidence |
| `AltDesej` | Target altitude (m) — if hold active |
| `SoproSustentar` | Hold throttle output (µs) |
| `GainEfetivo` | Effective gain (FORCA_BASE * ganho_do_sustentar) |
| `Fase` | Wingbeat phase angle (rad) |
| `Cadencia` | Wingbeat cadence (rad/s) |

**⚠️ Critical:** Always disable debug (`#define ECOS_PRESCINDIVEIS_DA_ALMA_ALADA` commented) for actual flight.

---

## Portuguese Name Reference

| Portuguese (Code) | English (Function) |
|-------------------|-------------------|
| `O Grande Código da Gralha Azul` | The Great Code of the Azure Jay |
| `Gralha Azul` | Azure Jay (*Cyanocorax caeruleus*) |
| `RECEPTOR_DOS_VENTOS_CRSF` | CRSF Receiver Mode |
| `RECEPTOR_DOS_VENTOS_PPM` | PPM Receiver Mode |
| `FREQUENCIA_DO_SOPRO_COSMICO` | CRSF Baud Rate (Cosmic Breath Frequency) |
| `guardiao_dos_ventos_siderais` | CRSF Serial Object (Guardian of Sidereal Winds) |
| `mensageiro_dos_ventos_cosmicos` | PPM Reader Object (Messenger of Cosmic Winds) |
| `ARTICULACAO_ASA_DA_MANHA` | Left Wing Servo Pin (Morning Wing Joint) |
| `ARTICULACAO_ASA_DO_ENTARDECER` | Right Wing Servo Pin (Evening Wing Joint) |
| `VIA_DOS_SONHOS_LUNARES` | CRSF RX Pin (Path of Lunar Dreams) |
| `VIA_DOS_ECOS_SOLARES` | CRSF TX Pin (Path of Solar Echoes) |
| `NUCLEO_DA_CHAMA_AZUL` | NeoPixel Pin (Core of the Blue Flame) |
| `CICLO_DO_CORACAO_ALADO` | Wingbeat Period (Winged Heart Cycle) |
| `LIMIAR_DO_VOO_ATIVO` | Throttle Threshold (Active Flight Threshold) |
| `EstadoDaAlmaAlada` | Link State (Winged Soul State) |
| `EM_DANCA_COM_OS_VENTOS` | Link Up (Dancing with the Winds) |
| `EM_SONHO_NA_QUIETUDE_DA_FLORESTA` | Link Down (Dreaming in the Forest's Quiet) |
| `ModoDoEspiritoAlado` | Flight Mode (Winged Spirit Mode) |
| `EM_RITMO_DE_BATIDA_DAS_ASAS` | Flapping Mode (Rhythm of Wing Beats) |
| `EM_DESLIZE_ETERNO_E_CONTEMPLATIVO` | Glide Mode (Eternal Contemplative Glide) |
| `voz_do_aletao` | CH1 (Voice of the Aileron) — Roll |
| `voz_do_profundor` | CH2 (Voice of the Elevator) — Pitch |
| `voz_do_sopro_vital` | CH3 (Voice of the Vital Breath) — Throttle |
| `voz_do_leme_estelar` | CH4 (Voice of the Starry Rudder) — Yaw |
| `voz_do_despertar` | CH5 (Voice of the Awakening) — Arm/Disarm |
| `voz_do_compasso_da_alma` | CH6 (Voice of the Soul's Compass) — Rhythm |
| `voz_da_ferocidade_do_bater` | CH7 (Voice of the Downstroke Ferocity) |
| `voz_da_ferocidade_do_retorno` | CH8 (Voice of the Upstroke Ferocity) |
| `voz_da_ferocidade_do_leme` | CH9 (Voice of the Rudder Ferocity) |
| `voz_do_sustentar_altura` | CH10 (Voice of Sustaining the Height) — Altitude-Hold Gain |
| `angulo_da_danca_alada` | Wingbeat Phase Angle (Winged Dance Angle) |
| `cadencia_do_destino_alado` | Wingbeat Cadence (Winged Destiny Cadence) |
| `pulso_do_sopro_vital` | Wingbeat Waveform (Vital Breath Pulse) |
| `forma_do_bater_das_asas` | Wingbeat Shape Function (Wing Beat Shape) |
| `MantoDeLuzCelestial` | NeoPixel Controller (Celestial Light Mantle) |
| `AcenderLuzPrimordial` | `begin()` (Ignite the Primordial Light) |
| `IrradiarLuzDaAlma` | `show()` (Radiate the Soul's Light) |
| `manto_celestial_da_gralha` | NeoPixel Instance (Celestial Mantle of the Jay) |
| `InterpretarAsVozesDoFirmamento` | Channel Update Callback |
| `AnimarPulsarDoCoracaoAlado` | Wingbeat Update (Animating the Winged Heart Pulse) |
| `ManifestarOVooNosVentos` | Servo Output (Manifesting Flight in the Winds) |
| `SustentarAltura()` | P-controller for barometric altitude hold |
| `SussurrarVooAoEter()` | CRSF Telemetry Send |
| `DespertarOraculoDaPressao()` | BMP180 Initialization |
| `EscutarPressaoDoCeu()` | Barometer Read (Listen to the Sky's Pressure) |
| `ECOS_PRESCINDIVEIS_DA_ALMA_ALADA` | Debug Flag (Dispensable Echoes of the Winged Soul) |

---

## Changelog

See [CHANGELOG.md](CHANGELOG.md) for version history.

---

## License

This project is open source. The code is poetry, the poetry is code — share it, fly with it, plant seeds with it.

*"E assim, o Grande Código da Gralha Azul se manifesta, em cada ciclo, um testemunho alado da resiliência da vida, da magia da transformação, e da perene esperança semeada entre o céu e a terra, um poema vivo, a canção da floresta que jamais se calará."*