# CHANGELOG

## v1.16.0 — Refatoração em Biblioteca Modular
- Código dividido em `src/GralhaAzul.h` (header com #ifndef guards) e `src/GralhaAzul.cpp` (implementação)
- `setup()` → `gralhaAzulSetup()`, `loop()` → `gralhaAzulLoop()`
- Módulos opcionais: `GRALHA_AZUL_NEOPIXEL_DESLIGADO`, `GRALHA_AZUL_BAROMETRO_DESLIGADO`, `GRALHA_AZUL_TELEMETRIA_DESLIGADO`
- Exemplos: `examples/CRSF_Exemplo/` e `examples/PPM_Exemplo/`
- `library.properties` para Arduino IDE
- Todo o código original preservado — poesia, comentários, lógica intactos

## v1.15.1 — Purga dos últimos resquícios de alemão/inglês nos comentários
- 6 correções: aus→do, vertical speed→velocidade vertical, Zeitkonstante→Constante de tempo, down/up→descida/subida, clamp→limitado, Limitação de taxa→Limitação da taxa de subida/descida
- Código 100% português nos comentários

## v1.15.0 — Comentários em português, README reestruturada com foco RP2040 + modo PPM
- Todos os comentários traduzidos para português
- README completamente reestruturada
