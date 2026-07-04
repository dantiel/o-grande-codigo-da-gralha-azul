# Documentation — O Grande Código da Gralha Azul

## Architecture

The library is **header-only** — all methods are `inline` in `GralhaAzul.h`. `GralhaAzul.cpp` is empty (legacy placeholder). There is nothing to link; a single `#include <GralhaAzul.h>` is sufficient.

External library objects (`CrsfSerial`, `PPMReader`, `Adafruit_NeoPixel`, `Adafruit_BMP085_Unified`) are constructed via **placement-new** into aligned buffers. This avoids dynamic allocation, keeps the header self-contained, and allows the exact same class layout in every translation unit.

### Configuration Flow

```
Sketch #defines (before #include)
        │
        ▼
GralhaAzul.h — "Ponte Arcana"
  ┌─ #ifdef GUARDIAO_DOS_VENTOS_SIDERAIS  →  #define GRALHA_TEM_GUARDIAO_DOS_VENTOS 1
  ├─ #ifdef MENSAGEIRO_DOS_CANTOS_COSMICOS → #define GRALHA_TEM_MENSAGEIRO_DOS_CANTOS 1
  ├─ #ifndef CHAMA_AZUL_DESLIGADA           → #define GRALHA_TEM_CHAMA_AZUL 1 (auto-detect)
  ├─ #ifndef ORACULO_DESLIGADO              → #define GRALHA_TEM_ORACULO 1 (auto-detect)
  └─ #ifndef SUSSURRO_DESLIGADO             → GRALHA_SUSSURRO_DESLIGADO false
        │
        ▼
Member initialization (direct #ifdef)
  #ifdef ARTICULACAO_DA_ASA_MATUTINA  → use sketch value
  #else                               → fallback to _PADRAO
        │
        ▼
begin() — placement-new construction
update() — per-frame logic
```

### ODR Safety

All member initializers use direct `#ifdef` on the sketch's define, never an intermediate `#ifndef` chain. This ensures the class layout is identical regardless of which translation unit the Arduino preprocessor sees first.

## Public API

### Class: `GralhaAzul`

All fields are public. Configure them before calling `begin()`.

#### Servo Pins

| Field | Override via `#define` | Default |
|---|---|---|
| `articulacaoAsaDaManha` | `ARTICULACAO_DA_ASA_MATUTINA` | 8 |
| `articulacaoAsaDoEntardecer` | `ARTICULACAO_DA_ASA_DO_ENTARDECER` | 7 |

#### CRSF UART Pins

| Field | Override via `#define` | Default |
|---|---|---|
| `viaDosSonhosLunares` | `VIA_DOS_SONHOS_LUNARES` | 1 |
| `viaDosEcosSolares` | `VIA_DOS_ECOS_SOLARES` | 0 |
| `frequenciaDoSoproCosmico` | `FREQUENCIA_DO_SOPRO_COSMICO` | 420000 |

The UART port itself is `VIA_DO_SOPRO_COSMICO` (default: `Serial1`), overridable via `#define VIA_DO_SOPRO_COSMICO`.

#### PPM

| Field | Override via `#define` | Default |
|---|---|---|
| `portalDosCantosCosmicos` | `PORTAL_DOS_CANTOS_COSMICOS` | 2 |
| `numeroDeCantos` | `NUMERO_DE_CANTOS` | 8 |

#### Flight Parameters

| Field | Override via `#define` | Default |
|---|---|---|
| `cicloDoCoracaoAlado` | `CICLO_DO_CORACAO_ALADO` | 0.070f |
| `escalaAngularArticulacao` | `ESCALA_ANGULAR_ARTICULACAO` | 0.04f |

`cicloDoCoracaoAlado` is the servo cycle time in seconds. This must match your servo's actual speed — amplitude, frequency, and scaling of the flapping algorithm all derive from it.

#### Optional Module Disable Flags

| Field | Auto-detected | Force-disable via `#define` |
|---|---|---|
| `neopixelDesligado` | `true` if `<Adafruit_NeoPixel.h>` absent | `CHAMA_AZUL_DESLIGADA` |
| `barometroDesligado` | `true` if `<Adafruit_BMP085_U.h>` absent | `ORACULO_DESLIGADO` |
| `telemetriaDesligado` | `false` | `SUSSURRO_DESLIGADO` |

#### Serial Output

```cpp
gralha.ecosPrescindiveis = &Serial;  // assign before begin()
```

If left `nullptr`, debug output is suppressed entirely.

### Methods

#### `void begin()`

Initializes everything in order:

1. Serial (115200 baud, 1.5s wait)
2. CRSF or PPM receiver (placement-new + `begin()`)
3. Servo attachment (pulse range 500–2500µs) + neutral position
4. NeoPixel (`acenderLuzPrimordial()`)
5. Barometer calibration (10 samples, 50ms apart)
6. Link-up event (`aoDespertarParaOCantoDoEter()`)

#### `void update()`

Called every loop iteration. Executes in this order:

1. `crsf->loop()` or `ppm->loop()` — service the receiver
2. `interpretarAsVozesDoFirmamento()` — read 10 channels
3. `animarPulsarDoCoracaoAlado()` — advance the flapping phase
4. `escutarPressaoDoCeu()` — read barometer
5. `sustentarAltura()` — altitude hold PI controller
6. `manifestarOVooNosVentos()` — compute and write servo positions
7. `sussurrarVooAoEter()` — CRSF telemetry
8. `irradiarLuzDaAlma()` — NeoPixel animation
9. Debug status line (every ~1s)
10. `delay(5)`

## Channel Mapping

10 channels, same order for CRSF and PPM:

| Channel | Variable | Function |
|---|---|---|
| 1 | `vozDoAlerao` | Roll |
| 2 | `vozDoProfundor` | Pitch |
| 3 | `vozDoSoproVital` | Throttle |
| 4 | `vozDoLemeEstelar` | Yaw |
| 5 | `vozDoDespertar` | Arm (>1500 = active) |
| 6 | `vozDaFerocidadeDoLeme` | Yaw aggressiveness |
| 7 | `vozDaFerocidadeDoBater` | Downstroke aggressiveness |
| 8 | `vozDaFerocidadeDoRetorno` | Upstroke aggressiveness |
| 9 | `vozDoCompassoDaAlma` | Flapping frequency trim |
| 10 | `vozDoSustentarAltura` | Altitude hold gain |

All channels expect 1000–2000µs range, centered at 1500.

## States and Modes

```
EstadoDaAlmaAlada:
  EM_DANCA_COM_OS_VENTOS           — Armed, responding to controls
  EM_SONHO_NA_QUIETUDE_DA_FLORESTA — Disarmed, idle

ModoDoEspiritoAlado:
  EM_RITMO_DE_BATIDA_DAS_ASAS       — Flapping (throttle > threshold)
  EM_DESLIZE_ETERNO_E_CONTEMPLATIVO — Gliding (throttle ≤ threshold)
```

Disarm triggers when channel 5 drops below 1500. Glide/flap transition uses hysteresis (~50 units on the threshold of 1040).

## Flapping Algorithm

The core resides in `animarPulsarDoCoracaoAlado()` and `manifestarOVooNosVentos()`.

### Phase Accumulation

```
targetCadence = (throttle − 480) × (1/(120 × cycleTime) + (frequencyTrim − 1500) × 0.0000725)
cadence += (targetCadence − 10 × cadence) × dt
phase   += cadence × dt
```

### Waveform Shaping

Each wing's raw sinusoid `sin(phase)` passes through `formaDoBaterDasAsas()`:

```
ferocidade = (half-cycle ≥ 0) ? downFerocidade : upFerocidade
resultado  = tanh(ferocidade × sin(phase)) / tanh(ferocidade)
```

Higher ferocidade → sharper, snappier motion. Lower → smoother, more sinusoidal.

### Wing Mixing

```
magnitude      = (throttle − threshold) × scale × (1 − frequencyTrim × modulation)
leftPulse      = shapeForm(sin, leftFer,  leftReturn)
rightPulse     = shapeForm(sin, rightFer, rightReturn)
yawFactor      = (1500/yawChannel − 1) × 2 + 1

leftDegrees    = magnitude × leftPulse  × yawFactor
rightDegrees   = magnitude × rightPulse / yawFactor

leftServo      = (roll − leftDegrees  + originLeft  − pitch) × finalMultiplier
rightServo     = (roll + rightDegrees + originRight + pitch) × finalMultiplier
```

Yaw differential: ferocidadeDoLeme adds to left wing's downstroke and right wing's upstroke, subtracts from the opposite — producing asymmetric thrust.

## Altitude Hold

A PI controller in `sustentarAltura()`. Channel 10 (1000–2000) maps to gain 0.0–1.0. When gain exceeds `GANHO_LIMIAR_SUSTENTAR_PADRAO` (0.1) and barometer is breathing:

1. **Engage**: capture current altitude as target, reset error integrator, snapshot current throttle
2. **Control loop**:
   ```
   rawError       = targetAlt − currentAlt
   filteredError += 0.1 × (rawError − filteredError)
   targetThrottle = 1500 + filteredError × baseForce × gain
   ```
3. **Climb rate limiting**: throttle ramps at ±50/s, with corrections for excessive climb/descent rates
4. **Disengage**: when gain drops below threshold or barometer is disabled

## NeoPixel Animation

`irradiarLuzDaAlma()` drives a single NeoPixel through several states:

| State | Colors |
|---|---|
| Flapping (armed) | Blue-dominant, brightness pulses with wing phase |
| Gliding (armed) | Blue-green, modulated by pitch |
| Armed but throttle cut | Red alert pulse overlay |
| Disarmed (sleep) | Slow HSV rainbow dream cycle |
| Disarmed + throttle cut | Rainbow with red alert pulse |

Brightness: 70/255. Update rate: every 25ms. The pixel fades through a sinusoidal breath at ~2.5Hz.

## Telemetry (Sussurro ao Éter)

CRSF telemetry is sent via the same UART as the receiver. Two independent timers gate telemetry frames:

- **Luminar** (every ~1s): transmits flight state
- **Térmico** (every ~1s): transmits barometer data (if Oráculo active)

The telemetry block is inside `sussurrarVooAoEter()` and only runs when `GRALHA_TEM_GUARDIAO_DOS_VENTOS` is true and `telemetriaDesligado` is false.

## Debug Output

When `ecosPrescindiveis` is assigned a `Stream*` (typically `&Serial`), the library emits tagged diagnostic lines:

| Tag | Meaning | When |
|---|---|---|
| `[DESPERTAR]` | Initialization sequence | `begin()` |
| `[PULSACAO]` | CRSF loop data | Each `update()` |
| `[ESTADO]` | Link status + channel preview | Each `update()` |
| `[CANTO]` | Channel values decoded | Each `update()` |
| `[PRESAGIO]` | Link up / link down events | On CRSF link change |
| `VOANDO \| SONHANDO` | Periodic status line | Every ~1s |

The periodic status line prints: armed state, mode, throttle, roll, pitch, yaw, arm switch, 3 ferocidade channels, altitude hold gain, channel 10, and (if barometer active) altitude, climb rate, temperature, thermal confidence, and altitude-hold internals.

## Default Values Reference

All defaults live in `GralhaAzul_Padraos.h`. Override by `#define` before `#include <GralhaAzul.h>`.

### Servo & Pin Defaults

| Macro | Default |
|---|---|
| `ARTICULACAO_ASA_DA_MANHA_PADRAO` | 8 |
| `ARTICULACAO_ASA_DO_ENTARDECER_PADRAO` | 7 |
| `VIA_DOS_SONHOS_LUNARES_PADRAO` | 1 |
| `VIA_DOS_ECOS_SOLARES_PADRAO` | 0 |
| `FREQUENCIA_DO_SOPRO_COSMICO_PADRAO` | 420000 |
| `NUCLEO_DA_CHAMA_AZUL_PADRAO` | 16 |
| `QUANTIDADE_DE_CENTELHAS_PADRAO` | 1 |
| `SILENCIO_DA_ALTURA_PADRAO` (I²C SDA) | 4 |
| `RITMO_DA_PRESSAO_PADRAO` (I²C SCL) | 5 |

### Flight Defaults

| Macro | Default |
|---|---|
| `CICLO_DO_CORACAO_ALADO_PADRAO` | 0.070f |
| `LIMIAR_DO_VOO_ATIVO_PADRAO` | 1040 |
| `ESCALA_ANGULAR_DA_ARTICULACAO_PADRAO` | 0.04f |
| `ESCALA_ANGULAR_DO_PROFUNDOR_PADRAO` | 0.06f |
| `MAGNITUDE_ESCALA_DA_FEROCIDADE_PADRAO` | 0.06f |
| `FEROCIDADE_MINIMA_PADRAO` | 1.0f |
| `FEROCIDADE_MAXIMA_PADRAO` | 8.0f |
| `DIFERENCIAL_LEME_MIN_PADRAO` | −4.0f |
| `DIFERENCIAL_LEME_MAX_PADRAO` | 4.0f |
| `MODULACAO_DO_COMPASSO_PADRAO` | 0.0003f |
| `DECAIMENTO_DA_CADENCIA_SONOLENTA_PADRAO` | 0.90f |

### Altitude Hold Defaults

| Macro | Default |
|---|---|
| `FORCA_BASE_DO_SUSTENTAR_PADRAO` | 30 |
| `AMORTECIMENTO_DO_ERRO_SUSTENTAR_PADRAO` | 0.1f |
| `TAXA_DE_SUBIDA_PROGRESSIVA_PADRAO` | 50.0f |
| `LIMITE_DA_SUBIDA_SUSTENTADA_PADRAO` | 5.0f |
| `LIMITE_DA_DESCIDA_SUSTENTADA_PADRAO` | −5.0f |
| `GANHO_LIMIAR_SUSTENTAR_PADRAO` | 0.1f |

## Memory Model

External library objects live in `alignas`-guarded `uint8_t` buffers inside the `GralhaAzul` class:

| Object | Buffer Size | Guard |
|---|---|---|
| `CrsfSerial` | `sizeof(CrsfSerial)` | `#if GRALHA_TEM_GUARDIAO_DOS_VENTOS` |
| `PPMReader` | `sizeof(PPMReader)` | `#if GRALHA_TEM_MENSAGEIRO_DOS_CANTOS` |
| `Adafruit_NeoPixel` | `sizeof(Adafruit_NeoPixel)` | `#if GRALHA_TEM_CHAMA_AZUL` |
| `Adafruit_BMP085_Unified` | `sizeof(Adafruit_BMP085_Unified)` | `#if GRALHA_TEM_ORACULO` |

Buffers are zeroed via `memset` before placement-new to work around library constructors that skip member initialization. Pointers are stored as `void*` and cast back when used — this avoids requiring the external library headers in every translation unit.

When a feature is disabled, its buffer is not declared at all (zero RAM cost). When a library header is absent, `__has_include` causes the feature to auto-disable with `GRALHA_TEM_* = 0`.
