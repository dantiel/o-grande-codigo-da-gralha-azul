# CHANGELOG

## v1.0.0 — First Official Release

**The Gralha Azul awakens.**

- **Architecture**: Class-based API with public configuration fields
- **Receivers**: CRSF (ExpressLRS) and PPM support
- **Servos**: Dual servo control for flapping wings
- **Lighting**: NeoPixel support with breathing animation
- **Telemetry**: CRSF telemetry output (altitude, battery)
- **Barometer**: Optional altitude hold using BMP280
- **Naming**: Poetic/mystical naming throughout
  - `articulacaoAsaDaManha` — Left wing servo pin
  - `articulacaoAsaDoEntardecer` — Right wing servo pin
  - `viaDosSonhosLunares` — CRSF RX pin
  - `viaDosEcosSolares` — CRSF TX pin
  - `cicloDoCoracaoAlado` — Flapping frequency
  - `escalaAngularArticulacao` — Servo travel range
  - `ecosPrescindiveis` — Debug serial
  - `barometroDesligado` — Disable barometer
  - `neopixelDesligado` — Disable NeoPixel
  - `telemetriaDesligado` — Disable telemetry

### API

```cpp
GralhaAzul gralha;

void setup() {
  gralha.articulacaoAsaDaManha = 3;
  gralha.articulacaoAsaDoEntardecer = 8;
  gralha.begin();
}

void loop() {
  gralha.update();
}
```

### Configuration

Before `begin()`, set the public fields:

| Field | Type | Default | Purpose |
|-------|------|---------|---------|
| `articulacaoAsaDaManha` | `uint8_t` | 3 | Left wing servo pin |
| `articulacaoAsaDoEntardecer` | `uint8_t` | 8 | Right wing servo pin |
| `viaDosSonhosLunares` | `uint8_t` | 1 | CRSF RX pin |
| `viaDosEcosSolares` | `uint8_t` | 0 | CRSF TX pin |
| `cicloDoCoracaoAlado` | `float` | 0.052 | Flapping frequency |
| `escalaAngularArticulacao` | `float` | 1.0 | Servo travel scale |
| `ecosPrescindiveis` | `Stream*` | `&Serial` | Debug output |
| `barometroDesligado` | `bool` | `false` | Disable BMP280 |
| `neopixelDesligado` | `bool` | `false` | Disable NeoPixel |
| `telemetriaDesligado` | `bool` | `false` | Disable telemetry |

### Receiver Selection

Use `#define` before including the header:

```cpp
// For CRSF (ExpressLRS)
#define RECEPTOR_CRSF
#include <GralhaAzul.h>

// For PPM
#define RECEPTOR_PPM
#define PORTAL_DOS_CANTOS_COSMICOS 1
#define NUMERO_DE_CANTOS 8
#include <GralhaAzul.h>
```

### Dependencies

- `CrsfSerial` (for CRSF receiver)
- `PPMReaderRP2040` (for PPM receiver)
- `Adafruit_NeoPixel` (optional, for lighting)
- `Adafruit_BMP280` (optional, for altitude hold)

### Examples

- `CRSF_Exemplo` — Basic CRSF setup
- `PPM_Exemplo` — Basic PPM setup

---

*The Gralha Azul flies.*
