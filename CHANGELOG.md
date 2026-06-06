# Changelog — O Grande Código da Gralha Azul

## [1.3.0] — 2026-06-04

### Changed
- **CH5 rudder ferocity now differential** — CH5 (`voz_da_ferocidade_do_leme`) is added to the left wing's ferocity and subtracted from the right wing's ferocity. This creates asymmetric wingbeats: the bird turns towards the side with sharper (more ferocious) downstrokes. Yaw mixing is handled in the transmitter.
- **Removed separate rudder pulse** — `pulso_leme` no longer exists. Each servo gets its own `forma_do_bater_das_asas()` with independent ferocity values.
- **Removed CH4-based differential modulation** — the old `mod_leme = (CH4 - 1500) * 0.0005` calculation is gone.
- **Removed `fator_leme_sutil`** — the old yaw amplitude modulation formula is gone.

---

All notable changes to this project will be documented in this file.

---

## [1.1.0] — 2026-06-04

### Added
- **README** (`README.md`) — comprehensive documentation covering hardware requirements, wiring, ExpressLRS/CRSF setup, channel mapping, flashing guide, configuration, flight mechanics, LED animation, debug output, and full Portuguese–English name reference.
- **CHANGELOG** (`CHANGELOG.md`) — this file.

### Fixed
- **`abs()` → `fabs()`** — `abs(cadencia_do_destino_alado)` in `AnimarPulsarDoCoracaoAlado()` used integer `abs()` on a float, causing the comparison `< 0.001` to always be true (float→int truncation). Changed to `fabs()` for correct floating-point comparison.
- **Division by zero protection** — `1500.0f / voz_do_leme_estelar` in `ManifestarOVooNosVentos()` could divide by zero if CH4 was 0 (link down). Added fallback to 1500 when channel value is 0.
- **`forma_do_bater_das_asas` output clamping** — When ferocity values are very small, `tanh(ferocidade * canto) / equilibrio_do_ceu` could produce extreme outputs. Added hard clamping to ±1.5 to prevent servo overdrive.
- **First-loop giant dt** — `ultima_pulsacao_do_sopro_alado` was initialised to 0, causing the first `dt = millis() * 0.001` to be ~2.5 seconds, producing a massive phase jump. Added initialisation guard in `loop()` that sets `ultima_pulsacao_do_sopro_alado` on first pass.
- **Flight mode hysteresis** — Added `LIMIAR_DO_VOO_ATIVO_HISTERESE` (±20 CRSF units) to prevent rapid oscillation between flapping and gliding modes when throttle is near the threshold. Once in flapping mode, the bird stays flapping until throttle drops below `(LIMIAR_DO_VOO_ATIVO - LIMIAR_DO_VOO_ATIVO_HISTERESE)`.
- **`volatile` qualifier removed** — CRSF callbacks run from `guardiao.loop()`, not from an interrupt context. The `volatile` keyword was misleading and has been removed from all channel variables.
- **Asymmetric flapping ferocity logic** — `forma_do_bater_das_asas()` now selects downstroke vs upstroke ferocity based on stroke direction (`cos(angulo_da_danca_alada)`) rather than wing position (`sin(angulo_da_danca_alada)`). This ensures the correct ferocity is applied to the actual downstroke and upstroke phases.

### Added
- **Per-servo ferocity** — Each servo (left wing, right wing, rudder) now gets its own `forma_do_bater_das_asas()` calculation. CH5 (`voz_da_ferocidade_do_leme`) provides independent rudder ferocity, while CH7/CH8 control wing downstroke/upstroke ferocity. Yaw mixing (differential amplitude) remains unchanged.

### Documentation
- Created full English README with wiring diagrams, ELRS/CRSF setup guide, channel mapping table, flashing instructions for Waveshare RP2040 Zero, configuration reference, flight mechanics explanation, LED animation description, and Portuguese–English name translation table.
- Added critical flight performance warning about debug output degrading servo timing.
- Corrected servo power wiring, ELRS/CRSF relationship, library name, NeoPixel as internal LED, wire colour symbolism, receiver/servo recommendations, and ELRS receiver focus on Happymodel EP2.