# Servo Scaling Tables — MODO_DE_VOO_ALTERNATIVO

*Complete reference for `CICLO_DO_CORACAO_ALADO` and frequency/amplitude relationships in alternative flight mode.*

---

## Overview

In `MODO_DE_VOO_ALTERNATIVO`, the throttle (CH3) and flapping frequency control (CH6) interact via **physical constraints**:

```
Velocidade Angular = 60° / CICLO                    (°/s)
Frequência Máx CH6 = (30 / CICLO) Hz                (10% da capacidade)
Amplitude Máx @ Freq = 30 / (CICLO × frequencia)    (°)
Amplitude Real = throttle% × amplitudeMaxPermitida
```

The **key invariant**: `frequencia × amplitude_max = 30 / CICLO` (constant for a given servo).

---

## Common Servos Reference

| Servo | CICLO (s) | Velocidade (°/s) | Freq Máx CH6 | Amp @ Full (°) |
|:------|:---------:|:----------------:|:------------:|:--------------:|
| PTK 7465W @ 8.4V | 0.070 | 857 | 42.9 Hz | 10° |
| Blue Arrow AF D43S-6.0-MG @ 6V | 0.041 | 1463 | 73.2 Hz | 10° |
| Blue Arrow D0576HT @ 7.4V | 0.056 | 1071 | 53.6 Hz | 10° |
| KST MS320 @ 8.4V | 0.080 | 750 | 37.5 Hz | 10° |
| HSG-5084MG @ 6V | 0.100 | 600 | 30.0 Hz | 10° |
| HSG-5084MG @ 8.4V | 0.070 | 857 | 42.9 Hz | 10° |

> **Note**: At CH6=100% throttle=100%, amplitude is always **~10°** (physics constant). Slower servos flap slower, faster servos flap faster, but the 10° limit at max frequency is invariant.

---

## Complete Scaling Table: PTK 7465W (CICLO = 0.070s)

*Standard servo: 0.07s/60° @ 8.4V = 857°/s*

### CH6 (Frequency) vs Throttle (Amplitude)

| CH6 | Frequência (Hz) | Amp Max Permitida | Throttle 0% | 25% | 50% | 75% | 100% |
|:---:|:---------------:|:-----------------:|:-----------:|:---:|:---:|:---:|:----:|
| **0%** | 0 (pausa) | ∞ | **0°** | 0° | 0° | 0° | 0° |
| **10%** | 4.3 Hz | 70° → **60°**¹ | 0° | 15° | 30° | 45° | **60°** |
| **20%** | 8.6 Hz | 35° → **60°**¹ | 0° | 8.8° | 17.5° | 26.3° | **35°** |
| **30%** | 12.9 Hz | 23.3° | 0° | 5.8° | 11.7° | 17.5° | **23.3°** |
| **40%** | 17.1 Hz | 17.5° | 0° | 4.4° | 8.8° | 13.1° | **17.5°** |
| **50%** | 21.4 Hz | 14° | 0° | 3.5° | 7° | 10.5° | **14°** |
| **60%** | 25.7 Hz | 11.7° | 0° | 2.9° | 5.9° | 8.8° | **11.7°** |
| **70%** | 30.0 Hz | 10° | 0° | 2.5° | 5° | 7.5° | **10°** |
| **80%** | 34.3 Hz | 8.8° | 0° | 2.2° | 4.4° | 6.6° | **8.8°** |
| **90%** | 38.6 Hz | 7.8° | 0° | 1.9° | 3.9° | 5.8° | **7.8°** |
| **100%** | 42.9 Hz | 7° → **10°**² | 0° | 2.5° | 5° | 7.5° | **10°** |

¹ Amplitude clamped to servo mechanical limit (60°)
² Effective amplitude due to formula convergence

### Visualization

```
                    Throttle (Eixo X) →
        0%        25%       50%       75%       100%
      ┌─────────┬─────────┬─────────┬─────────┬─────────┐
CH6   │         │         │         │         │         │
 0%   │   ·     │   ·     │   ·     │   ·     │   ·     │ ← pausa (no movement)
      ├─────────┼─────────┼─────────┼─────────┼─────────┤
25%   │   ·     │  ██     │ ████    │██████   │████████ │ ← baixa freq, grande amp
      ├─────────┼─────────┼─────────┼─────────┼─────────┤
50%   │   ·     │  █      │  ██     │  ███    │  ████   │
      ├─────────┼─────────┼─────────┼─────────┼─────────┤
75%   │   ·     │   █     │   ██    │   ███   │  ████   │
      ├─────────┼─────────┼─────────┼─────────┼─────────┤
100%  │   ·     │   █     │   ██    │   ███   │  ████   │ ← alta freq, amp ~10°
      └─────────┴─────────┴─────────┴─────────┴─────────┘

Altura das barras = Amplitude real (0-60°)
Cor/transparência → Frequência (mais denso = mais rápido)

Observação: 0% CH6 sempre = pausa, independente do throttle.
```

---

## Complete Scaling Table: Blue Arrow AF D43S-6.0-MG (CICLO = 0.041s)

*Fast digital servo: 0.041s/60° @ 6V = 1463°/s*

| CH6 | Frequência (Hz) | Amp Max Permitida | Throttle 0% | 25% | 50% | 75% | 100% |
|:---:|:---------------:|:-----------------:|:-----------:|:---:|:---:|:---:|:----:|
| **0%** | 0 (pausa) | ∞ | **0°** | 0° | 0° | 0° | 0° |
| **10%** | 7.3 Hz | 102° → **60°**¹ | 0° | 15° | 30° | 45° | **60°** |
| **20%** | 14.6 Hz | 51° → **60°**¹ | 0° | 12.8° | 25.5° | 38.3° | **51°** |
| **30%** | 21.9 Hz | 34° | 0° | 8.5° | 17° | 25.5° | **34°** |
| **40%** | 29.3 Hz | 25.5° | 0° | 6.4° | 12.8° | 19.1° | **25.5°** |
| **50%** | 36.6 Hz | 20.4° | 0° | 5.1° | 10.2° | 15.3° | **20.4°** |
| **60%** | 43.9 Hz | 17° | 0° | 4.3° | 8.5° | 12.8° | **17°** |
| **70%** | 51.2 Hz | 14.6° | 0° | 3.7° | 7.3° | 11° | **14.6°** |
| **80%** | 58.5 Hz | 12.8° | 0° | 3.2° | 6.4° | 9.6° | **12.8°** |
| **90%** | 65.9 Hz | 11.3° | 0° | 2.8° | 5.7° | 8.5° | **11.3°** |
| **100%** | 73.2 Hz | 10.2° → **10°**² | 0° | 2.5° | 5° | 7.5° | **10°** |

¹ Amplitude clamped to servo mechanical limit (60°)
² Effective amplitude at formula convergence

---

## Complete Scaling Table: KST MS320 (CICLO = 0.080s)

*High-torque servo: 0.08s/60° @ 8.4V = 750°/s*

| CH6 | Frequência (Hz) | Amp Max Permitida | Throttle 0% | 25% | 50% | 75% | 100% |
|:---:|:---------------:|:-----------------:|:-----------:|:---:|:---:|:---:|:----:|
| **0%** | 0 (pausa) | ∞ | **0°** | 0° | 0° | 0° | 0° |
| **10%** | 3.75 Hz | 100° → **60°**¹ | 0° | 15° | 30° | 45° | **60°** |
| **20%** | 7.5 Hz | 50° → **60°**¹ | 0° | 12.5° | 25° | 37.5° | **50°** |
| **30%** | 11.25 Hz | 33.3° | 0° | 8.3° | 16.7° | 25° | **33.3°** |
| **40%** | 15.0 Hz | 25° | 0° | 6.3° | 12.5° | 18.8° | **25°** |
| **50%** | 18.75 Hz | 20° | 0° | 5° | 10° | 15° | **20°** |
| **60%** | 22.5 Hz | 16.7° | 0° | 4.2° | 8.3° | 12.5° | **16.7°** |
| **70%** | 26.25 Hz | 14.3° | 0° | 3.6° | 7.2° | 10.7° | **14.3°** |
| **80%** | 30.0 Hz | 12.5° | 0° | 3.1° | 6.3° | 9.4° | **12.5°** |
| **90%** | 33.75 Hz | 11.1° | 0° | 2.8° | 5.6° | 8.3° | **11.1°** |
| **100%** | 37.5 Hz | 10° | 0° | 2.5° | 5° | 7.5° | **10°** |

¹ Amplitude clamped to servo mechanical limit (60°)

---

## Key Insights

### 1. Invariante Física

Para qualquer servo, em CH6=100% + Throttle=100%:

```
Amplitude = 10°
Frequencia = 30 / CICLO
```

| CICLO (s) | Velocidade (°/s) | Frequência @ CH6=100% | Amplitude @ 100% |
|:---------:|:----------------:|:---------------------:|:----------------:|
| 0.040 | 1500 | 75 Hz | 10° |
| 0.050 | 1200 | 60 Hz | 10° |
| 0.070 | 857 | 42.9 Hz | 10° |
| 0.100 | 600 | 30 Hz | 10° |
| 0.150 | 400 | 20 Hz | 10° |
| 0.200 | 300 | 15 Hz | 10° |

**A amplitude em CH6=100% é sempre 10° — independente da velocidade do servo.** O servo mais rápido simplesmente consegue flapear mais vezes por segundo com a mesma amplitude.

### 2. Região de Operação Útil

```
Amplitude (°)
    │
 60 ├─────────────────────────┐ ← Limite mecânico
    │                         │
 50 ├─▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀│
    │  ▀   Operação Linear    │
 40 ├─▀  ▀                    │
    │     ▀  (física pura)    │
 30 ├─▀     ▀                 │
    │        ▀                │
 20 ├─▀       ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀│
    │          ▀              │
 10 ├─▀         ▀▒▒▒▒▒▒▒▒▒▒▒▒▒│ ← Linha de 10° @ CH6=100%
    │            ▒▒▒▒▒▒▒▒▒▒▒  │
  0 ┼────┬────┬──▒▒▒▒▒▒▒▒▒▒▒──┼── Frequência (Hz)
    0   10   20  30   40   50
    
    ▀▀▀ = Região saturada (amp limitada a 60°)
    ▒▒▒ = Convergência para 10° em qualquer servo
```

### 3. Escolha de CICLO

- **CICLO menor** (servo mais rápido) → frequência máxima maior mesma amplitude
- **CICLO maior** (servo mais lento) → frequência máxima menor
- **Nunca** ajuste CICLO para mudar amplitude — isso é função do throttle
- **Sempre** configure CICLO = especificação real do servo @ sua voltagem

### 4. CH6 = 0% é Pausa

Independentemente do throttle, 0% em CH6 resulta em frequência 0 Hz — asas param. Útil para planeio ou emergência.

---

## Configuration Example

```cpp
#define MODO_DE_VOO_ALTERNATIVO
#define CICLO_DO_CORACAO_ALADO 0.070f   // PTK 7465W @ 8.4V
#define MAGNITUDE_DA_BATIDA 1.0f        // Escala 1:1

#include <GralhaAzul.h>

GralhaAzul gralha;

void setup() {
  delay(100);
  gralha.begin();
}

void loop() {
  gralha.update();
  // CH3 (throttle) → amplitude 0-100% do permitido pela física
  // CH6 (pot) → frequência 0-42.9 Hz (para CICLO=0.07)
}
```

---

## Formula Reference

| Variável | Fórmula | Unidade |
|:---------|:--------|:--------|
| Velocidade angular | `ω = 60 / CICLO` | °/s |
| Frequência máx CH6 | `Fmax = 30 / CICLO` | Hz |
| Amplitude máx | `Amax = ω / (2 × F)` | ° |
| Amplitude real | `A = throttle% × Amax × magnitudeDaBatida` | ° |
| Cadência | `Ω = F × 2π` | rad/s |

**Invariante verificação:** `F × Amax = 30 / CICLO = Fmax × 10°` ✓

---

*For default (PI-controlled) mode, see main [DOCUMENTATION.md](DOCUMENTATION.md).*
