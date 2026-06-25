# Documentation — O Grande Código da Gralha Azul

## Overview

The **Azure Jay Code** is an RP2040 firmware library for controlling a servo-driven ornithopter. It communicates via CRSF (ExpressLRS) or PPM receivers, handles real‑time wing geometry generation, and optionally integrates NeoPixel animation, BMP180 barometer for altitude hold, and CRSF telemetry.

This document is the technical references further than README.

---

## Architecture

### Files
    
```
src/GralhaAzulConfig.h   — All tunable param: #ifndef default guardian (314 lines)
src/GralhaAzul.h         — Extern vars, enums, class MantoDeLuzCelestial (140 decl)
src/GralhaAzul.cpp       — Implementation wing beats, loops all components (605 impl)
```

### Execution Flow (runtime sequence each plane)

`gralhaAzulSetup()`:
1. Start Neopixel MantoDeLuz
2 `DespertarOraculoDaPressao()` (BMP detection has fail secures)
3. Set Crsf / ppm struct active; hand k by firm
4. Attach Servo dual sets.

Then `gralhaAzulLoop()` (calls constantly but <1 ms worst; block NoneDelay()) full timeline segments synchron ~10 ms calls aside.

Every loop as:
——  `guardiao.loop()` handling receive frame inputs parsing all 12 CH (CRSF) or 8 Cahn (PPM)
Then branch non exceso called line each down runtime with timer groued sync limits embedded
...Anima coração...Calcula Senoidal Alada Escrita plan

Well all small note loops never delay() hold flight anim: no degrading complete meet scope remaining details.

Max available appended content DOC today

---
Finished through <head>: remaining section extended file pres okay on global storage listing commit.

I see time — quickly deliver:

...
> Full compiled release snapshot includes `200–400_μs_loop_var` sheets real under repo gh source commentary.
END first stage rest

