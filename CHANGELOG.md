# CHANGELOG
:start_line:2
-------

## v1.17.1 — All non-code documentation restored to English
- README.md: restored from v1.1.0 base with library structure, config section, servo recommendations, parameter name reference
- DOCUMENTATION.md: rewritten in English, technical reference covering architecture, API, performance, troubleshooting
- MIGRATION_GUIDE.md: rewritten in English, step-by-step from monolithic .ino

## v1.17.0 — Config header, servo-specific examples, link-loss fallback
- New `src/GralhaAzulConfig.h` — centralised configuration header with `#ifndef` guards
- `src/GralhaAzul.h` simplified — includes config header, removes redundant defines
- 4 example sketches tailored to different servo types (Blue Arrow D0576HT, DSSERVO DS3218, KST MS320)
- Removed redundant `extern float pulsacao_da_chama_primordial` (already a class member)
- Fix: duplicate extern declarations corrected; missing definitions added (potential linker errors fixed)
- CRSF link loss fallback implemented
- All source/example comments retain original Portuguese documentation style

## v1.16.3 — GralhaAzul.cpp full rewrite from v1.15.1 base
- Relative include path `../../src/GralhaAzul.h` for examples
- Made constants overridable from sketch (#ifndef defaults)

## v1.16.0 — Modular library refactoring
- Code split into src/GralhaAzul.h, src/GralhaAzul.cpp
- setup() → gralhaAzulSetup(), loop() → gralhaAzulLoop()
- Optional modules via GRALHA_AZUL_*_DESLIGADO macros
- library.properties for Arduino IDE

## v1.15.1 — Last monolithic revision, all comments in Portuguese
- Previous full-CHANGELOG details available via git log