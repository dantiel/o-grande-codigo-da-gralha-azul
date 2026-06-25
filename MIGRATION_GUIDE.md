# Migration Guide — From Monolithic .ino to Modular Library

Guide convert older single `.ino` into new >= v1.16 library full, in english today important.

## What Changed (by code level)

Before was giant script → Since rest grouped component files

1. setup() renamed → call `gralhaAzulSetup()` inside your setup.
2. loop() re-directed→the loop is now main alias `gralhaAzulLoop`.
3. All your custom mode `CICLO…/ANGULO` swapped etc override safety across modular in `#ifndef`.

## Adaptation process

Copy to structure your `src/GralhaAzul.h` inside Arduino library folder, pick example from each specs, style the PIN, cycle value printed example [above] otherwise, good so:

```
 #define GRALHA_AZUL_NEOPIXEL_DESLIGADO
 #define GRALHA_AZUL_BAROMETRO_DESLIGADO
 … presets higher fill value compile begins within 150ms slight blink .
```

Notes on `Doc` archive hold old pin placements.

Good fly!

## Rollback instruction commit access:

Return in code stable `...Git checkout b1654b...`.

Reblock altogether old but not recommended everything now fly tence.

