# Documentation — O Grande Código da Gralha Azul

**First Official Release**

## Architecture

The Gralha Azul is a **class-based library** with minimal public interface. All configuration happens through public fields before calling `begin()`.

```cpp
class GralhaAzul {
public:
  // The Eleven Relics (configuration)
  uint8_t articulacaoAsaDaManha;
  uint8_t articulacaoAsaDoEntardecer;
  uint8_t viaDosSonhosLunares;
  uint8_t viaDosEcosSolares;
  float cicloDoCoracaoAlado;
  float escalaAngularArticulacao;
  Stream* ecosPrescindiveis;
  bool barometroDesligado;
  bool neopixelDesligado;
  bool telemetriaDesligado;
  
  // The Rituals
  void begin();
  void update();
};
```

## Configuration

### Servo Pins

```cpp
gralha.articulacaoAsaDaManha = 3;      // Left wing
gralha.articulacaoAsaDoEntardecer = 8; // Right wing
```

### CRSF Setup

```cpp
#define RECEPTOR_CRSF
#include <GralhaAzul.h>

gralha.viaDosSonhosLunares = 1;  // RX pin
gralha.viaDosEcosSolares = 0;    // TX pin
```

### PPM Setup

```cpp
#define RECEPTOR_PPM
#define PORTAL_DOS_CANTOS_COSMICOS 1  // PPM input pin
#define NUMERO_DE_CANTOS 8            // Number of channels
#include <GralhaAzul.h>
```

### Flight Parameters

```cpp
gralha.cicloDoCoracaoAlado = 0.065f;      // Flapping speed (lower = faster)
gralha.escalaAngularArticulacao = 0.04f;  // Servo travel multiplier
```

### Optional Features

```cpp
gralha.barometroDesligado = true;    // Disable BMP180
gralha.neopixelDesligado = true;     // Disable NeoPixel
gralha.telemetriaDesligado = true;   // Disable CRSF telemetry
```

## External Control (Injection)

For custom receivers or mixing, use the injection methods:

| Method | Channel | Range | Purpose |
|--------|---------|-------|---------|
| `injetarVozDoAlerao(valor)` | CH1 | 1000-2000 | Aileron |
| `injetarVozDoProfundor(valor)` | CH2 | 1000-2000 | Elevator |
| `injetarVozDoSoproVital(valor)` | CH3 | 1000-2000 | Throttle |
| `injetarVozDoLemeEstelar(valor)` | CH4 | 1000-2000 | Rudder |
| `injetarVozDoDespertar(valor)` | CH5 | 0/1 | Arm switch |
| `injetarVozDoCompassoDaAlma(valor)` | CH6 | 1000-2000 | Flight mode |
| `injetarVozDaFerocidadeDoBater(valor)` | CH7 | 1000-2000 | Flap speed |
| `injetarVozDaFerocidadeDoRetorno(valor)` | CH8 | 1000-2000 | Flap return speed |
| `injetarVozDaFerocidadeDoLeme(valor)` | CH9 | 1000-2000 | Rudder mix |
| `injetarVozDoSustentarAltura(valor)` | CH10 | 1000-2000 | Altitude hold target |
| `injetarEstadoPresenteDaAlma(estado)` | — | enum | `EM_DANCA_COM_OS_VENTOS` or `EM_SONHO_NA_QUIETUDE_DA_FLORESTA` |

## The Pulse Cycle

Each `update()` call performs:

1. **Read the Winds** — CRSF or PPM receiver
2. **Calculate the Heartbeat** — PI controller for altitude hold
3. **Manifest the Wings** — Servo position calculation
4. **Breathe the Light** — NeoPixel animation
5. **Whisper to the Ether** — Telemetry transmission

## Default Values

All defaults are defined in `GralhaAzul_Padraos.h`:

```cpp
#define ARTICULACAO_ASA_DA_MANHA_PADRAO 3
#define ARTICULACAO_ASA_DO_ENTARDECER_PADRAO 8
#define CICLO_DO_CORACAO_ALADO_PADRAO 0.052f
#define ESCALA_ANGULAR_ARTICULACAO_PADRAO 0.04f
// ... etc
```

## Model Sketches

The library is designed for one sketch per model. Each sketch:

1. Includes `GralhaAzul.h`
2. Creates a `GralhaAzul` instance
3. Configures the relics
4. Calls `begin()` in `setup()`
5. Calls `update()` in `loop()`

See the `examples/` folder for complete working sketches.

## The Naming Convention

All identifiers follow Portuguese poetic naming:

| Technical Concept | Poetic Name |
|-------------------|-------------|
| Servo pin | `articulacaoAsaDaManha` |
| Throttle | `vozDoSoproVital` |
| Altitude hold | `sustentar` |
| Flapping | `coracaoAlado` |
| Telemetry | `sussurrarVooAoEter` |
| Receiver | `guardiaoDosVentosSiderais` |
| GPS | `oraculoDosCaminhosCelestes` |
| Barometer | `oraculoDaPressao` |

*The code breathes through these names.*