# CHANGELOG

## v1.23.0 — The Pure Essence

- **Purified**: Removed all meta-commentary about poetry
- **Essence**: Code now IS the incantation, not commentary about it
- **Documentation**: Complete rewrite for class-based API

## v1.22.0 — The Purification

- **Removed**: All technical naming fallbacks (`_PIN`, `_MS`, `_HPA`)
- **Pure**: Only poetic names throughout
- **Sketches**: All 4 models updated to poetic naming

## v1.21.0 — The Great Renaming

- **Poetic naming**: All macros renamed from technical to mystical
  - `ASA_MANHA_PIN` → `ARTICULACAO_DA_ASA_MATUTINA`
  - `PPM_PIN` → `PORTAL_DOS_CANTOS_COSMICOS`
  - `CRSF_BAUDRATE` → `FREQUENCIA_DO_SOPRO_COSMICO`
- **Removed**: `_MS` and `_HPA` suffixes from defaults

## v1.20.0 — The Macro Simplification

- **Optimization**: Using `_PADRAO` macros directly instead of duplicating as fields
- **Memory**: ~160 bytes RAM saved by removing redundant fields
- **Fields reduced**: From ~55 to 8 essential public fields

## v1.19.0 — The Class Awakening

- **Architecture**: Refactored from global functions to class-based
- **API**: `GralhaAzul gralha; gralha.begin(); gralha.update();`
- **Removed**: `gralhaAzulSetup()` / `gralhaAzulLoop()` globals
- **Added**: Proper encapsulation with public configuration fields

## v1.18.0 — The __has_include Architecture

- **Feature**: Auto-detection of `GralhaAzulConfig.h` per model
- **Feature**: `__has_include` for optional dependencies
- **Refactor**: Three models to new architecture

## v1.17.0 — The Event System

- **Feature**: CRSF link up/down callbacks
- **Feature**: `eventoLinkUp()` / `eventoLinkDown()`

## v1.16.0 — The Library Birth

- **Refactor**: Extracted from monolithic .ino to library
- **Structure**: `src/`, `examples/`, `library.properties`
- **Models**: servo_mandorla_entomoid, servo_haliastur_indus, servo_hypervolution_xh4f_aetherwing

## v1.15.1 and earlier

- Monolithic .ino files
- Global variables
- Direct macro dependencies
