# CHANGELOG

## v1.17.1 — All non-code documentation restored to English
- README.md restored from v1.1.0 English base, with library structure, config section, servo recommendations table, and full Portuguese name reference
- DOCUMENTATION.md rewritten in English (~250 lines): technical reference with architecture, API parameters, performance, troubleshooting
- MIGRATION_GUIDE.md rewritten in English: compact step-by-step from monolithic .ino

## v1.17.0 — Servo-specific examples, poetic Brazilian code comments
- **Purificatio**: New `src/GralhaAzulConfig.h` — centralised config header with `#ifndef` guards
- **Purificatio**: src/GralhaAzul.h simplified — includes config, removes redundant defines
- **Purificatio**: 4 examples each tailored to a servo type (Blue Arrow D0576HT, DSSERVO DS3218, KST MS320)
- **Purificatio**: Removed redundant `extern float pulsacao_da_chama_primordial` (is class member)
- **Validatio**: Fixed duplicate externs + missing definitions (potential linker errors)
- **Validatio**: CRSF link loss fallback implemented
- Code comments: 100% poetic Brazilian Portuguese (src/, examples/, .ino)

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
