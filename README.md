# O Grande Código da Gralha Azul

**First Official Release**

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

## The Eleven Relics

These are the fields you can configure before calling `begin()`:

| Field | Type | Default | Meaning |
|-------|------|---------|---------|
| `articulacaoAsaDaManha` | uint8_t | 3 | Left wing servo pin |
| `articulacaoAsaDoEntardecer` | uint8_t | 8 | Right wing servo pin |
| `viaDosSonhosLunares` | uint8_t | 1 | CRSF RX pin |
| `viaDosEcosSolares` | uint8_t | 0 | CRSF TX pin |
| `cicloDoCoracaoAlado` | float | 0.052f | Flapping frequency |
| `escalaAngularArticulacao` | float | 0.04f | Servo travel scale |
| `ecosPrescindiveis` | Stream* | nullptr | Debug stream (Serial) |
| `barometroDesligado` | bool | false | Disable barometer |
| `neopixelDesligado` | bool | false | Disable NeoPixel |
| `telemetriaDesligado` | bool | false | Disable telemetry |

## Receiver Types

### CRSF
```cpp
#define RECEPTOR_CRSF
#include <GralhaAzul.h>

// CRSF uses: viaDosSonhosLunares (RX), viaDosEcosSolares (TX)
```

### PPM
```cpp
#define RECEPTOR_PPM
#define PORTAL_DOS_CANTOS_COSMICOS 1
#define NUMERO_DE_CANTOS 8
#include <GralhaAzul.h>

// PPM is automatic when RECEPTOR_PPM is defined
```

## External Control (Injection)

For custom receivers or mixing, inject channel values directly:

```cpp
gralha.injetarVozDoAlerao(1500);        // Aileron (CH1)
gralha.injetarVozDoProfundor(1500);     // Elevator (CH2)
gralha.injetarVozDoSoproVital(1000);    // Throttle (CH3)
gralha.injetarVozDoLemeEstelar(1500);   // Rudder (CH4)
gralha.injetarVozDoDespertar(0);        // Arm switch (CH5)
gralha.injetarVozDoCompassoDaAlma(1500); // Flight mode (CH6)
gralha.injetarVozDaFerocidadeDoBater(1000);    // Flap speed (CH7)
gralha.injetarVozDaFerocidadeDoRetorno(1000);   // Flap return (CH8)
gralha.injetarVozDaFerocidadeDoLeme(1000);      // Rudder mix (CH9)
gralha.injetarVozDoSustentarAltura(1000);       // Altitude hold (CH10)
gralha.injetarEstadoPresenteDaAlma(EM_DANCA_COM_OS_VENTOS); // Armed
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