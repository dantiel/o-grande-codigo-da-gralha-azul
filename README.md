# O Grande Código da Gralha Azul v1.23.0

**The Great Code of the Azure Jay** — *A living incantation for ornithopter flight*

> *"In the language of the Gralha Azul, every variable is a spirit, every function a ritual."*

## What Is This?

A C++ library for RP2040-based ornithopters (flapping-wing aircraft) that speaks in the voice of Brazilian folklore. It controls servos, reads CRSF/PPM receivers, manages NeoPixel lighting, and streams telemetry — all through an API that feels like summoning a spirit rather than configuring hardware.

## Quick Start

### 1. Install the Library

Copy the `o-grande-codigo-da-gralha-azul` folder to your Arduino libraries directory.

### 2. Create Your Model Sketch

```cpp
#include <GralhaAzul.h>

// The spirit that will animate your craft
GralhaAzul gralha;

void setup() {
  // Configure the wings
  gralha.articulacaoAsaDaManha = 3;      // Left wing servo pin
  gralha.articulacaoAsaDoEntardecer = 8;  // Right wing servo pin
  
  // The heartbeat of flight
  gralha.cicloDoCoracaoAlado = 0.065f;
  
  // Awaken the spirit
  gralha.begin();
}

void loop() {
  // The eternal pulse
  gralha.update();
}
```

### 3. Upload and Fly

The Gralha Azul will read your transmitter, animate the wings, and breathe life into your creation.

## The Eight Relics

These are the only fields you need to configure:

| Field | Default | Meaning |
|-------|---------|---------|
| `articulacaoAsaDaManha` | 3 | Left wing servo pin |
| `articulacaoAsaDoEntardecer` | 8 | Right wing servo pin |
| `viaDosSonhosLunares` | 1 | CRSF RX pin |
| `viaDosEcosSolares` | 0 | CRSF TX pin |
| `cicloDoCoracaoAlado` | 0.052f | Flapping frequency |
| `escalaAngularArticulacao` | 0.04f | Servo travel scale |
| `ecosPrescindiveis` | nullptr | Debug stream (Serial) |
| `barometroDesligado` | false | Disable barometer |
| `neopixelDesligado` | false | Disable NeoPixel |
| `telemetriaDesligada` | false | Disable telemetry |

## Receiver Types

### CRSF (Default)
```cpp
// CRSF is automatic if CrsfSerial.h is available
// Pins: viaDosSonhosLunares (RX), viaDosEcosSolares (TX)
```

### PPM (Optional)
```cpp
#include <PPMReaderRP2040.h>

GralhaAzul gralha;

void setup() {
  gralha.mensageiroDosVentosCosmicos = new PPMReader(1, 8);  // Pin 1, 8 channels
  gralha.begin();
}
```

## Examples

- **CRSF_Exemplo** — Basic CRSF setup (Gralha-das-Araucárias)
- **PPM_Exemplo** — Basic PPM setup (Gralha-dos-Pampas)

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
