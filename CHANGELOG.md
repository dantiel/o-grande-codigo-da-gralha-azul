# CHANGELOG

## v1.17.0 — Exemplos baseados em servos reais, README poética restaurada
- README.md restaurada da versão `6855701` com estrutura de biblioteca atual
- Novos exemplos específicos por servo:
  - `CRSF_Servo_Rapido/` — para servos rápidos (ex.: Blue Arrow D0576HT MG, ~33 Hz)
  - `CRSF_Servo_Torque/` — para servos de alto torque (ex.: KST MS320, ~12 Hz)
- Removidos `CRSF_BeijaFlor/` e `CRSF_Gaviao_Cinzento/`
- Comentários poéticos em todos os exemplos, sem separadores `====`
- **Purificatio**: Novo `src/GralhaAzulConfig.h` — grimório centralizado de configuração
- **Purificatio**: `src/GralhaAzul.h` simplificado — inclui `GralhaAzulConfig.h`, remove defines redundantes
- **Purificatio**: Exemplos simplificados — referenciam o config, sem defines duplicados
- **Purificatio**: Removido `extern float pulsacao_da_chama_primordial` redundante (já é membro da classe)
- **Purificatio**: README documenta modelo de compilação e configuração via config header
- **Validatio**: Removidos externs duplicados em GralhaAzul.h (ganho_do_sustentar, altura_desejada_do_voo, sopro_vital_do_sustentar, modo_sustentar_ativo, angulo_da_danca_alada)
- **Validatio**: Adicionadas definições faltantes em GralhaAzul.cpp para ganho_do_sustentar, altura_desejada_do_voo, sopro_vital_do_sustentar, modo_sustentar_ativo (corrige erro de linker)
- **Documentatio**: Criado `DOCUMENTATION.md` — documentação técnica completa (arquitetura, API, deploy, troubleshooting, performance, segurança, manutenção)
- **Documentatio**: Criado `MIGRATION_GUIDE.md` — guia passo a passo para migrar do monolítico .ino para a biblioteca modular
- **Documentatio**: Ambas as documentações em português brasileiro poético, formato GitHub-flavored Markdown

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