# Documentation — O Grande Código da Gralha Azul v1.23.0

## Architecture

The Gralha Azul is a **class-based library** with minimal public interface. All configuration happens through public fields before calling `begin()`.

```cpp
class GralhaAzul {
public:
  // The Eight Relics (configuration)
  uint8_t articulacaoAsaDaManha;
  uint8_t articulacaoAsaDoEntardecer;
  uint8_t viaDosSonhosLunares;
  uint8_t viaDosEcosSolares;
  float cicloDoCoracaoAlado;
  float escalaAngularArticulacao;
  Stream* ecosPrescindiveis;
  bool barometroDesligado;
  bool neopixelDesligado;
  bool telemetriaDesligada;
  
  // The Messenger (for PPM)
  void* mensageiroDosVentosCosmicos;
  
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

CRSF is automatic if `CrsfSerial.h` is available at compile time:

```cpp
gralha.viaDosSonhosLunares = 1;  // RX pin
gralha.viaDosEcosSolares = 0;    // TX pin
```

### PPM Setup

```cpp
#include <PPMReaderRP2040.h>

gralha.mensageiroDosVentosCosmicos = new PPMReader(PIN, CHANNELS);
```

If `mensageiroDosVentosCosmicos` is set, CRSF will not be initialized.

### Flight Parameters

```cpp
gralha.cicloDoCoracaoAlado = 0.065f;      // Flapping speed (lower = faster)
gralha.escalaAngularArticulacao = 0.04f;  // Servo travel multiplier
```

### Optional Features

```cpp
gralha.barometroDesligado = true;    // Disable BMP180
gralha.neopixelDesligado = true;     // Disable NeoPixel
gralha.telemetriaDesligada = true;   // Disable CRSF telemetry
```

## The Pulse Cycle

Each `update()` call performs:

1. **Read the Winds** — CRSF or PPM receiver
2. **Calculate the Heartbeat** — PI controller for altitude hold
3. **Manifest the Wings** — Servo position calculation
4. **Breathe the Light** — NeoPixel animation
5. **Whisper to the Ether** — Telemetry transmission

## CRSF Events

The library provides callbacks for CRSF link state:

```cpp
void eventoLinkUp();    // Called when CRSF connects
void eventoLinkDown();  // Called when CRSF disconnects
```

These are handled internally but can be extended.

## Default Values

All defaults are defined in `GralhaAzul_Padraos.h`:

```cpp
#define ARTICULACAO_DA_ASA_MATUTINA_PADRAO 3
#define ARTICULACAO_DA_ASA_VESPERTINA_PADRAO 8
#define CICLO_DO_CORACAO_ALADO_PADRAO 0.052f
#define ESCALA_ANGULAR_ARTICULACAO_PADRAO 0.04f
// ... etc
```

## Model Sketches

The library is designed for one sketch per model. Each sketch:

1. Includes `GralhaAzul.h`
2. Creates a `GralhaAzul` instance
3. Configures the 8 relics
4. Calls `begin()` in `setup()`
5. Calls `update()` in `loop()`

See the `examples/` folder for complete working sketches.

## The Naming Convention

All identifiers follow Portuguese poetic naming:

| Technical Concept | Poetic Name |
|-------------------|-------------|
| Servo pin | `articulacaoAsaDaManha` |
| Throttle | `pulsoDoDestinoAlado` |
| Altitude hold | `sustentar` |
| Flapping | `coracaoAlado` |
| Telemetry | `sussurrarVooAoEter` |
| Receiver | `guardiaoDosVentosSiderais` |
| GPS | `oraculoDosCaminhosCelestes` |
| Barometer | `oraculoDaPressao` |

*The code breathes through these names.*
