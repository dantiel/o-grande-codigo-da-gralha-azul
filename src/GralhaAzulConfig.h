/*
  O Grande Código da Gralha Azul
  — A Inscrição da Configuração Alada —

  Este é o grimório onde a Gralha guarda os segredos da sua forma.
  Edite este arquivo para tecer a sina do seu modelo:
  - Ativar/desativar módulos (NeoPixel, Barómetro, Telemetria)
  - Ajustar a geometria do voo (ciclo, planar, ferocidade)
  - Configurar pinos e portais dos tendões alados

  As constantes têm guardas #ifndef para que possam ser
  sobrescritas por -D no compilador ou por defines no sketch
  antes do #include <GralhaAzul.h>.
*/

#ifndef GRALHA_AZUL_CONFIG_H
#define GRALHA_AZUL_CONFIG_H

/* —————————— Módulos Opcionais ——————————
   Descomente a linha para desligar o módulo correspondente.

   #define GRALHA_AZUL_NEOPIXEL_DESLIGADO    — sem a chama azul
   #define GRALHA_AZUL_BAROMETRO_DESLIGADO   — sem o oráculo da pressão
   #define GRALHA_AZUL_TELEMETRIA_DESLIGADO  — sem sussurro ao éter
*/

/* —————————— Oráculos e Conexões com o Cosmos —————————— */

#ifndef ECOS_PRESCINDIVEIS_DA_ALMA_ALADA
  //#define ECOS_PRESCINDIVEIS_DA_ALMA_ALADA   /* Serial debug */
#endif

#ifndef FREQUENCIA_DO_SOPRO_COSMICO
  #define FREQUENCIA_DO_SOPRO_COSMICO 420000
#endif

#ifndef PORTAL_DOS_VENTOS_CELESTES
  #define PORTAL_DOS_VENTOS_CELESTES Serial1
#endif

/* —————————— A Escolha do Mensageiro dos Ventos ——————————
   CRSF — o guardião sideral que sussurra em ondas de rádio.
   PPM  — o mensageiro cósmico dos pulsos antigos. */

#ifndef RECEPTOR_DOS_VENTOS_CRSF
  #ifndef RECEPTOR_DOS_VENTOS_PPM
    #define RECEPTOR_DOS_VENTOS_CRSF
  #endif
#endif

/* —————————— Os Portais dos Tendões Alados ——————————
   Pinos que a Gralha toca para mover as asas. */

#ifndef ARTICULACAO_ASA_DA_MANHA
  #define ARTICULACAO_ASA_DA_MANHA        8   /* asa esquerda */
#endif
#ifndef ARTICULACAO_ASA_DO_ENTARDECER
  #define ARTICULACAO_ASA_DO_ENTARDECER   7   /* asa direita */
#endif
#ifndef VIA_DOS_SONHOS_LUNARES
  #define VIA_DOS_SONHOS_LUNARES          1   /* RX */
#endif
#ifndef VIA_DOS_ECOS_SOLARES
  #define VIA_DOS_ECOS_SOLARES            0   /* TX */
#endif
#ifndef NUCLEO_DA_CHAMA_AZUL
  #define NUCLEO_DA_CHAMA_AZUL           16   /* NeoPixel */
#endif
#ifndef QUANTIDADE_DE_CENTELHAS_NA_CHAMA
  #define QUANTIDADE_DE_CENTELHAS_NA_CHAMA  1
#endif
#ifndef PINO_SILENCIO_DA_ALTURA
  #define PINO_SILENCIO_DA_ALTURA         4   /* SDA */
#endif
#ifndef PINO_RITMO_DA_PRESSAO
  #define PINO_RITMO_DA_PRESSAO           5   /* SCL */
#endif
#ifndef PINO_DO_MENSAGEIRO
  #define PINO_DO_MENSAGEIRO              2   /* PPM input */
#endif
#ifndef NUM_CANAIS_DO_MENSAGEIRO
  #define NUM_CANAIS_DO_MENSAGEIRO        8
#endif

/* —————————— A Geometria Sagrada do Voo ——————————
   Constantes que esculpem a dança alada. */

#ifndef CICLO_DO_CORACAO_ALADO
  #define CICLO_DO_CORACAO_ALADO  0.052f  /* segundos (~19 Hz) */
#endif
#ifndef LIMIAR_DO_VOO_ATIVO
  #define LIMIAR_DO_VOO_ATIVO          1040
#endif
#ifndef LIMIAR_DO_VOO_ATIVO_HISTERESE
  #define LIMIAR_DO_VOO_ATIVO_HISTERESE  20
#endif
#ifndef ANGULO_DO_PLANAR_SERENO
  #define ANGULO_DO_PLANAR_SERENO        -4  /* graus de glide */
#endif
#ifndef ORIGEM_ASA_MATUTINA
  #define ORIGEM_ASA_MATUTINA             0
#endif
#ifndef ORIGEM_ASA_VESPERTINA
  #define ORIGEM_ASA_VESPERTINA           0
#endif

/* —————————— As Vozes do Céu ——————————
   Vibrações que chegam do firmamento para ditar o destino. */

#ifndef VIBRACAO_NEUTRA_DO_ALETAO
  #define VIBRACAO_NEUTRA_DO_ALETAO                1500
#endif
#ifndef VIBRACAO_NEUTRA_DO_PROFUNDOR
  #define VIBRACAO_NEUTRA_DO_PROFUNDOR             1500
#endif
#ifndef VIBRACAO_MINIMA_DO_SOPRO_VITAL
  #define VIBRACAO_MINIMA_DO_SOPRO_VITAL           1000
#endif
#ifndef VIBRACAO_NEUTRA_DO_LEME_ESTELAR
  #define VIBRACAO_NEUTRA_DO_LEME_ESTELAR          1500
#endif
#ifndef VIBRACAO_NEUTRA_DO_COMPASSO_DA_ALMA
  #define VIBRACAO_NEUTRA_DO_COMPASSO_DA_ALMA      1500
#endif
#ifndef VIBRACAO_DO_DESPERTAR_DESARMADO
  #define VIBRACAO_DO_DESPERTAR_DESARMADO          1000
#endif
#ifndef VIBRACAO_MINIMA_DA_FEROCIDADE
  #define VIBRACAO_MINIMA_DA_FEROCIDADE            1000
#endif
#ifndef VIBRACAO_MINIMA_DO_SUSTENTAR_ALTURA
  #define VIBRACAO_MINIMA_DO_SUSTENTAR_ALTURA      1000
#endif

/* —————————— O Hálito que Sustenta ——————————
   Parâmetros do voo pairante quando a Gralha escuta a pressão do céu. */

#ifndef GRALHA_AZUL_BAROMETRO_DESLIGADO
#ifndef ALTURA_MAX_DO_SUSTENTAR_M
  #define ALTURA_MAX_DO_SUSTENTAR_M       20.0f
#endif
#ifndef SOPRO_MIN_DO_SUSTENTAR
  #define SOPRO_MIN_DO_SUSTENTAR          1100
#endif
#ifndef SOPRO_MAX_DO_SUSTENTAR
  #define SOPRO_MAX_DO_SUSTENTAR          1800
#endif
#ifndef FORCA_BASE_DO_SUSTENTAR
  #define FORCA_BASE_DO_SUSTENTAR         180
#endif
#ifndef SILENCIO_DO_SUSTENTAR_M
  #define SILENCIO_DO_SUSTENTAR_M         0.5f
#endif
#ifndef LIMITE_DA_DESCIDA_SUSTENTADA_MS
  #define LIMITE_DA_DESCIDA_SUSTENTADA_MS      2.0f
#endif
#ifndef LIMITE_DA_SUBIDA_SUSTENTADA_MS
  #define LIMITE_DA_SUBIDA_SUSTENTADA_MS       3.0f
#endif
#ifndef REFERENCIA_DA_PRESSAO_HPA
  #define REFERENCIA_DA_PRESSAO_HPA       1013.25f
#endif
#endif /* GRALHA_AZUL_BAROMETRO_DESLIGADO */

/* —————————— O Batimento dos Tendões ——————————
   Limites do pulso que move as asas. */

#ifndef PULSO_MINIMO_SERVO
  #define PULSO_MINIMO_SERVO    500
#endif
#ifndef PULSO_MAXIMO_SERVO
  #define PULSO_MAXIMO_SERVO   2500
#endif

/* —————————— A Dança Secreta dos Ventos ——————————
   Parâmetros que tecem a coreografia alada. */

#ifndef ESCALA_ANGULAR_DA_ARTICULACAO
  #define ESCALA_ANGULAR_DA_ARTICULACAO    0.06f
#endif
#ifndef ESCALA_ANGULAR_DO_PROFUNDOR
  #define ESCALA_ANGULAR_DO_PROFUNDOR      0.06f
#endif
#ifndef MAGNITUDE_ESCALA_DA_FEROCIDADE
  #define MAGNITUDE_ESCALA_DA_FEROCIDADE   0.06f
#endif
#ifndef MODULACAO_DO_COMPASSO
  #define MODULACAO_DO_COMPASSO            0.0003f
#endif
#ifndef MULTIPLICADOR_FINAL_ANGULAR
  #define MULTIPLICADOR_FINAL_ANGULAR      2.0f
#endif
#ifndef OFFSET_ANGULAR_NEUTRO
  #define OFFSET_ANGULAR_NEUTRO          100
#endif
#ifndef FEROCIDADE_MINIMA
  #define FEROCIDADE_MINIMA               1.0f
#endif
#ifndef FEROCIDADE_MAXIMA
  #define FEROCIDADE_MAXIMA               8.0f
#endif
#ifndef DIFERENCIAL_LEME_MIN
  #define DIFERENCIAL_LEME_MIN           -4.0f
#endif
#ifndef DIFERENCIAL_LEME_MAX
  #define DIFERENCIAL_LEME_MAX            4.0f
#endif
#ifndef EPSILON_FORMA_BATER
  #define EPSILON_FORMA_BATER             0.001f
#endif
#ifndef LIMITE_FORMA_BATER
  #define LIMITE_FORMA_BATER              1.5f
#endif
#ifndef ACELERACAO_DO_COMPASSO
  #define ACELERACAO_DO_COMPASSO          8.0f
#endif
#ifndef MULTIPLICADOR_MINIMO_FREQUENCIA
  #define MULTIPLICADOR_MINIMO_FREQUENCIA 0.5f
#endif
#ifndef PESO_DO_SOPRO_NA_FREQUENCIA
  #define PESO_DO_SOPRO_NA_FREQUENCIA     0.5f
#endif
#ifndef PESO_DO_COMPASSO_NA_FREQUENCIA
  #define PESO_DO_COMPASSO_NA_FREQUENCIA  0.3f
#endif
#ifndef DECAIMENTO_DA_CADENCIA_SONOLENTA
  #define DECAIMENTO_DA_CADENCIA_SONOLENTA 0.90f
#endif
#ifndef EPSILON_CADENCIA_ZERO
  #define EPSILON_CADENCIA_ZERO           0.001f
#endif
#ifndef DT_MAXIMO_DO_SONHO
  #define DT_MAXIMO_DO_SONHO              0.05f
#endif
#ifndef LIMITE_ANGULAR_DO_GIRO
  #define LIMITE_ANGULAR_DO_GIRO          (20.0f * PI)
#endif
#ifndef INTERVALO_NEO_PIXEL_MS
  #define INTERVALO_NEO_PIXEL_MS          33
#endif
#ifndef INTERVALO_SERIAL_DEBUG_MS
  #define INTERVALO_SERIAL_DEBUG_MS       250
#endif
#ifndef BAUDRATE_SERIAL
  #define BAUDRATE_SERIAL                 115200
#endif
#ifndef TEMPO_ESPERA_USB_MS
  #define TEMPO_ESPERA_USB_MS             4000
#endif
#ifndef INTERVALO_LEITURA_BAROMETRO_MS
  #define INTERVALO_LEITURA_BAROMETRO_MS  200
#endif
#ifndef AMOSTRAS_CALIBRACAO_BAROMETRO
  #define AMOSTRAS_CALIBRACAO_BAROMETRO   10
#endif
#ifndef ATRASO_CALIBRACAO_BAROMETRO_MS
  #define ATRASO_CALIBRACAO_BAROMETRO_MS  50
#endif
#ifndef SALTOS_CICLO_TEMPERATURA
  #define SALTOS_CICLO_TEMPERATURA        5
#endif
#ifndef SUAVIZACAO_TEMPERATURA
  #define SUAVIZACAO_TEMPERATURA          0.5f
#endif
#ifndef FILTRO_TENDENCIA_TEMPERATURA
  #define FILTRO_TENDENCIA_TEMPERATURA    0.9f
#endif
#ifndef PESO_TENDENCIA_TEMPERATURA
  #define PESO_TENDENCIA_TEMPERATURA      0.1f
#endif
#ifndef PESO_VELOCIDADE_VERTICAL_ATUAL
  #define PESO_VELOCIDADE_VERTICAL_ATUAL      0.7f
#endif
#ifndef PESO_VELOCIDADE_VERTICAL_ANTERIOR
  #define PESO_VELOCIDADE_VERTICAL_ANTERIOR   0.3f
#endif
#ifndef PESO_CONFIANCA_TERMICA_TEMPERATURA
  #define PESO_CONFIANCA_TERMICA_TEMPERATURA  0.3f
#endif
#ifndef LIMIAR_CONFIANCA_TERMICA
  #define LIMIAR_CONFIANCA_TERMICA        0.5f
#endif
#ifndef MINIMO_DT_SEGUNDOS
  #define MINIMO_DT_SEGUNDOS              0.001f
#endif
#ifndef CORRECAO_TAXA_LIMITE_SUSTENTAR
  #define CORRECAO_TAXA_LIMITE_SUSTENTAR  10.0f
#endif
#ifndef INTERVALO_TELEMETRIA_GPS_MS
  #define INTERVALO_TELEMETRIA_GPS_MS     200
#endif
#ifndef INTERVALO_TELEMETRIA_TEMPERATURA_MS
  #define INTERVALO_TELEMETRIA_TEMPERATURA_MS 500
#endif
#ifndef FATOR_CONVERSAO_VELOCIDADE
  #define FATOR_CONVERSAO_VELOCIDADE      (3.6f * 10.0f)
#endif
#ifndef OFFSET_ALTITUDE_CRSF
  #define OFFSET_ALTITUDE_CRSF            1000.0f
#endif
#ifndef ESCALA_TEMPERATURA_CRSF
  #define ESCALA_TEMPERATURA_CRSF         100.0f
#endif
#ifndef GANHO_LIMIAR_SUSTENTAR
  #define GANHO_LIMIAR_SUSTENTAR          0.01f
#endif
#ifndef EXPONENTE_FORMULA_BAROMETRICA
  #define EXPONENTE_FORMULA_BAROMETRICA   0.190284f
#endif
#ifndef CONSTANTE_FORMULA_BAROMETRICA
  #define CONSTANTE_FORMULA_BAROMETRICA   44307.69f
#endif

#endif /* GRALHA_AZUL_CONFIG_H */
