/*
  O Grande Código da Gralha Azul
  A Inscrição Primordial da Lenda Alada
  — Invocação do Coração Alado Partilhado entre Modelos —
*/

#ifndef GRALHA_AZUL_H
#define GRALHA_AZUL_H

/* Oráculos e Conexões com o Cosmos
   O sopro do firmamento que a Gralha escuta para dançar nos céus. */
#ifndef ECOS_PRESCINDIVEIS_DA_ALMA_ALADA
  //#define ECOS_PRESCINDIVEIS_DA_ALMA_ALADA
#endif
#ifndef FREQUENCIA_DO_SOPRO_COSMICO
  #define FREQUENCIA_DO_SOPRO_COSMICO 420000
#endif
#ifndef PORTAL_DOS_VENTOS_CELESTES
  #define PORTAL_DOS_VENTOS_CELESTES Serial1
#endif

/* A Escolha do Mensageiro dos Ventos
   CRSF — o guardião sideral que sussurra em ondas de rádio.
   PPM — o mensageiro cósmico dos pulsos antigos. */
#ifndef RECEPTOR_DOS_VENTOS_CRSF
  #ifndef RECEPTOR_DOS_VENTOS_PPM
    #define RECEPTOR_DOS_VENTOS_CRSF
  #endif
#endif

/* Bibliotecas que a Gralha invoca para seus rituais. */
#include <Arduino.h>
#if defined(RECEPTOR_DOS_VENTOS_CRSF)
  #include <CrsfSerial.h>
#elif defined(RECEPTOR_DOS_VENTOS_PPM)
  #include <PPMReaderRP2040.h>
#endif
#ifndef GRALHA_AZUL_BAROMETRO_DESLIGADO
  #include <Wire.h>
  #include <Adafruit_Sensor.h>
  #include <Adafruit_BMP085_U.h>
#endif
#include <Servo.h>
#ifndef GRALHA_AZUL_NEOPIXEL_DESLIGADO
  #include <Adafruit_NeoPixel.h>
#endif

/* Os Portais dos Tendões Alados — Pinos que a Gralha toca para mover as asas. */
#ifndef ARTICULACAO_ASA_DA_MANHA
  #define ARTICULACAO_ASA_DA_MANHA 8
#endif
#ifndef ARTICULACAO_ASA_DO_ENTARDECER
  #define ARTICULACAO_ASA_DO_ENTARDECER 7
#endif
#ifndef VIA_DOS_SONHOS_LUNARES
  #define VIA_DOS_SONHOS_LUNARES 1
#endif
#ifndef VIA_DOS_ECOS_SOLARES
  #define VIA_DOS_ECOS_SOLARES 0
#endif
#ifndef NUCLEO_DA_CHAMA_AZUL
  #define NUCLEO_DA_CHAMA_AZUL 16
#endif
#ifndef QUANTIDADE_DE_CENTELHAS_NA_CHAMA
  #define QUANTIDADE_DE_CENTELHAS_NA_CHAMA 1
#endif
#ifndef PINO_SILENCIO_DA_ALTURA
  #define PINO_SILENCIO_DA_ALTURA 4
#endif
#ifndef PINO_RITMO_DA_PRESSAO
  #define PINO_RITMO_DA_PRESSAO 5
#endif
#ifndef PINO_DO_MENSAGEIRO
  #define PINO_DO_MENSAGEIRO 2
#endif
#ifndef NUM_CANAIS_DO_MENSAGEIRO
  #define NUM_CANAIS_DO_MENSAGEIRO 8
#endif

/* A Geometria Sagrada do Voo — Constantes que esculpem a dança alada. */
#ifndef CICLO_DO_CORACAO_ALADO
  #define CICLO_DO_CORACAO_ALADO 0.052f
#endif
#ifndef LIMIAR_DO_VOO_ATIVO
  #define LIMIAR_DO_VOO_ATIVO 1040
#endif
#ifndef LIMIAR_DO_VOO_ATIVO_HISTERESE
  #define LIMIAR_DO_VOO_ATIVO_HISTERESE 20
#endif
#ifndef ANGULO_DO_PLANAR_SERENO
  #define ANGULO_DO_PLANAR_SERENO -4
#endif
#ifndef ORIGEM_ASA_MATUTINA
  #define ORIGEM_ASA_MATUTINA 0
#endif
#ifndef ORIGEM_ASA_VESPERTINA
  #define ORIGEM_ASA_VESPERTINA 0
#endif

/* As Vozes do Céu — Vibrações que chegam do firmamento para ditar o destino. */
#ifndef VIBRACAO_NEUTRA_DO_ALETAO
  #define VIBRACAO_NEUTRA_DO_ALETAO 1500
#endif
#ifndef VIBRACAO_NEUTRA_DO_PROFUNDOR
  #define VIBRACAO_NEUTRA_DO_PROFUNDOR 1500
#endif
#ifndef VIBRACAO_MINIMA_DO_SOPRO_VITAL
  #define VIBRACAO_MINIMA_DO_SOPRO_VITAL 1000
#endif
#ifndef VIBRACAO_NEUTRA_DO_LEME_ESTELAR
  #define VIBRACAO_NEUTRA_DO_LEME_ESTELAR 1500
#endif
#ifndef VIBRACAO_NEUTRA_DO_COMPASSO_DA_ALMA
  #define VIBRACAO_NEUTRA_DO_COMPASSO_DA_ALMA 1500
#endif
#ifndef VIBRACAO_DO_DESPERTAR_DESARMADO
  #define VIBRACAO_DO_DESPERTAR_DESARMADO 1000
#endif
#ifndef VIBRACAO_MINIMA_DA_FEROCIDADE
  #define VIBRACAO_MINIMA_DA_FEROCIDADE 1000
#endif
#ifndef VIBRACAO_MINIMA_DO_SUSTENTAR_ALTURA
  #define VIBRACAO_MINIMA_DO_SUSTENTAR_ALTURA 1000
#endif

/* O Hálito que Sustenta — Parâmetros do voo pairante quando a Gralha escuta a pressão do céu. */
#ifndef GRALHA_AZUL_BAROMETRO_DESLIGADO
#ifndef ALTURA_MAX_DO_SUSTENTAR_M
  #define ALTURA_MAX_DO_SUSTENTAR_M    20.0f
#endif
#ifndef SOPRO_MIN_DO_SUSTENTAR
  #define SOPRO_MIN_DO_SUSTENTAR       1100
#endif
#ifndef SOPRO_MAX_DO_SUSTENTAR
  #define SOPRO_MAX_DO_SUSTENTAR       1800
#endif
#ifndef FORCA_BASE_DO_SUSTENTAR
  #define FORCA_BASE_DO_SUSTENTAR      180
#endif
#ifndef SILENCIO_DO_SUSTENTAR_M
  #define SILENCIO_DO_SUSTENTAR_M      0.5f
#endif
#ifndef LIMITE_DA_DESCIDA_SUSTENTADA_MS
  #define LIMITE_DA_DESCIDA_SUSTENTADA_MS   2.0f
#endif
#ifndef LIMITE_DA_SUBIDA_SUSTENTADA_MS
  #define LIMITE_DA_SUBIDA_SUSTENTADA_MS    3.0f
#endif
#ifndef REFERENCIA_DA_PRESSAO_HPA
  #define REFERENCIA_DA_PRESSAO_HPA 1013.25f
#endif
#endif

/* O Batimento dos Tendões — Limites do pulso que move as asas. */
#ifndef PULSO_MINIMO_SERVO
  #define PULSO_MINIMO_SERVO 500
#endif
#ifndef PULSO_MAXIMO_SERVO
  #define PULSO_MAXIMO_SERVO 2500
#endif

/* A Dança Secreta dos Ventos — Parâmetros que tecem a coreografia alada. */
#ifndef ESCALA_ANGULAR_DA_ARTICULACAO
  #define ESCALA_ANGULAR_DA_ARTICULACAO 0.06f
#endif
#ifndef ESCALA_ANGULAR_DO_PROFUNDOR
  #define ESCALA_ANGULAR_DO_PROFUNDOR 0.06f
#endif
#ifndef MAGNITUDE_ESCALA_DA_FEROCIDADE
  #define MAGNITUDE_ESCALA_DA_FEROCIDADE 0.06f
#endif
#ifndef MODULACAO_DO_COMPASSO
  #define MODULACAO_DO_COMPASSO 0.0003f
#endif
#ifndef MULTIPLICADOR_FINAL_ANGULAR
  #define MULTIPLICADOR_FINAL_ANGULAR 2.0f
#endif
#ifndef OFFSET_ANGULAR_NEUTRO
  #define OFFSET_ANGULAR_NEUTRO 100
#endif
#ifndef FEROCIDADE_MINIMA
  #define FEROCIDADE_MINIMA 1.0f
#endif
#ifndef FEROCIDADE_MAXIMA
  #define FEROCIDADE_MAXIMA 8.0f
#endif
#ifndef DIFERENCIAL_LEME_MIN
  #define DIFERENCIAL_LEME_MIN -4.0f
#endif
#ifndef DIFERENCIAL_LEME_MAX
  #define DIFERENCIAL_LEME_MAX 4.0f
#endif
#ifndef EPSILON_FORMA_BATER
  #define EPSILON_FORMA_BATER 0.001f
#endif
#ifndef LIMITE_FORMA_BATER
  #define LIMITE_FORMA_BATER 1.5f
#endif
#ifndef ACELERACAO_DO_COMPASSO
  #define ACELERACAO_DO_COMPASSO 8.0f
#endif
#ifndef MULTIPLICADOR_MINIMO_FREQUENCIA
  #define MULTIPLICADOR_MINIMO_FREQUENCIA 0.5f
#endif
#ifndef PESO_DO_SOPRO_NA_FREQUENCIA
  #define PESO_DO_SOPRO_NA_FREQUENCIA 0.5f
#endif
#ifndef PESO_DO_COMPASSO_NA_FREQUENCIA
  #define PESO_DO_COMPASSO_NA_FREQUENCIA 0.3f
#endif
#ifndef DECAIMENTO_DA_CADENCIA_SONOLENTA
  #define DECAIMENTO_DA_CADENCIA_SONOLENTA 0.90f
#endif
#ifndef EPSILON_CADENCIA_ZERO
  #define EPSILON_CADENCIA_ZERO 0.001f
#endif
#ifndef DT_MAXIMO_DO_SONHO
  #define DT_MAXIMO_DO_SONHO 0.05f
#endif
#ifndef LIMITE_ANGULAR_DO_GIRO
  #define LIMITE_ANGULAR_DO_GIRO (20.0f * PI)
#endif
#ifndef INTERVALO_NEO_PIXEL_MS
  #define INTERVALO_NEO_PIXEL_MS 33
#endif
#ifndef INTERVALO_SERIAL_DEBUG_MS
  #define INTERVALO_SERIAL_DEBUG_MS 250
#endif
#ifndef BAUDRATE_SERIAL
  #define BAUDRATE_SERIAL 115200
#endif
#ifndef TEMPO_ESPERA_USB_MS
  #define TEMPO_ESPERA_USB_MS 4000
#endif
#ifndef INTERVALO_LEITURA_BAROMETRO_MS
  #define INTERVALO_LEITURA_BAROMETRO_MS 200
#endif
#ifndef AMOSTRAS_CALIBRACAO_BAROMETRO
  #define AMOSTRAS_CALIBRACAO_BAROMETRO 10
#endif
#ifndef ATRASO_CALIBRACAO_BAROMETRO_MS
  #define ATRASO_CALIBRACAO_BAROMETRO_MS 50
#endif
#ifndef SALTOS_CICLO_TEMPERATURA
  #define SALTOS_CICLO_TEMPERATURA 5
#endif
#ifndef SUAVIZACAO_TEMPERATURA
  #define SUAVIZACAO_TEMPERATURA 0.5f
#endif
#ifndef FILTRO_TENDENCIA_TEMPERATURA
  #define FILTRO_TENDENCIA_TEMPERATURA 0.9f
#endif
#ifndef PESO_TENDENCIA_TEMPERATURA
  #define PESO_TENDENCIA_TEMPERATURA 0.1f
#endif
#ifndef PESO_VELOCIDADE_VERTICAL_ATUAL
  #define PESO_VELOCIDADE_VERTICAL_ATUAL 0.7f
#endif
#ifndef PESO_VELOCIDADE_VERTICAL_ANTERIOR
  #define PESO_VELOCIDADE_VERTICAL_ANTERIOR 0.3f
#endif
#ifndef PESO_CONFIANCA_TERMICA_TEMPERATURA
  #define PESO_CONFIANCA_TERMICA_TEMPERATURA 0.3f
#endif
#ifndef LIMIAR_CONFIANCA_TERMICA
  #define LIMIAR_CONFIANCA_TERMICA 0.5f
#endif
#ifndef MINIMO_DT_SEGUNDOS
  #define MINIMO_DT_SEGUNDOS 0.001f
#endif
#ifndef CORRECAO_TAXA_LIMITE_SUSTENTAR
  #define CORRECAO_TAXA_LIMITE_SUSTENTAR 10.0f
#endif
#ifndef INTERVALO_TELEMETRIA_GPS_MS
  #define INTERVALO_TELEMETRIA_GPS_MS 200
#endif
#ifndef INTERVALO_TELEMETRIA_TEMPERATURA_MS
  #define INTERVALO_TELEMETRIA_TEMPERATURA_MS 500
#endif
#ifndef FATOR_CONVERSAO_VELOCIDADE
  #define FATOR_CONVERSAO_VELOCIDADE (3.6f * 10.0f)
#endif
#ifndef OFFSET_ALTITUDE_CRSF
  #define OFFSET_ALTITUDE_CRSF 1000.0f
#endif
#ifndef ESCALA_TEMPERATURA_CRSF
  #define ESCALA_TEMPERATURA_CRSF 100.0f
#endif
#ifndef GANHO_LIMIAR_SUSTENTAR
  #define GANHO_LIMIAR_SUSTENTAR 0.01f
#endif
#ifndef EXPONENTE_FORMULA_BAROMETRICA
  #define EXPONENTE_FORMULA_BAROMETRICA 0.190284f
#endif
#ifndef CONSTANTE_FORMULA_BAROMETRICA
  #define CONSTANTE_FORMULA_BAROMETRICA 44307.69f
#endif

/* As Relíquias da Gralha — Onde a memória do voo se guarda entre ciclos. */
#if defined(RECEPTOR_DOS_VENTOS_CRSF)
extern CrsfSerial guardiao_dos_ventos_siderais;
#elif defined(RECEPTOR_DOS_VENTOS_PPM)
extern PPMReader mensageiro_dos_ventos_cosmicos;
#endif
extern unsigned long ultimo_sopro_sideral;
extern unsigned long ultimo_sopro_termico;
extern bool limiar_elevado;
extern bool oraculo_respira;

/* Os Estados da Alma — A Gralha sonha na floresta ou dança com os ventos? */
enum EstadoDaAlmaAlada : uint8_t {
  EM_DANCA_COM_OS_VENTOS,
  EM_SONHO_NA_QUIETUDE_DA_FLORESTA
};
enum ModoDoEspiritoAlado {
  EM_RITMO_DE_BATIDA_DAS_ASAS,
  EM_DESLIZE_ETERNO_E_CONTEMPLATIVO
};

extern EstadoDaAlmaAlada estado_presente_da_alma;
extern ModoDoEspiritoAlado modo_presente_do_espirito;
extern int voz_do_sustentar_altura;

struct RelogioDasEras {
  unsigned long instante_do_agora_cosmico;
  unsigned long ultimo_fulgor_da_chama_azul;
  unsigned long ultimo_eco_prescindivei;
  unsigned long ultima_pulsacao_do_sopro_alado;
  unsigned long ultimo_instante_de_respiracao_luminescente;
  float intervalo_entre_pulsacoes_do_coracao_alado;
};
extern RelogioDasEras relogio_das_eras;

extern int voz_do_aletao;
extern int voz_do_profundor;
extern int voz_do_sopro_vital;
extern int voz_do_leme_estelar;
extern int voz_do_despertar;
extern int voz_do_compasso_da_alma;
extern int voz_da_ferocidade_do_bater;
extern int voz_da_ferocidade_do_retorno;
extern int voz_da_ferocidade_do_leme;

#ifndef GRALHA_AZUL_BAROMETRO_DESLIGADO
extern Adafruit_BMP085_Unified oraculo_da_pressao;
#endif
extern float pressao_do_ceu_hpa;
extern float temperatura_do_ar_c;
extern float altura_do_voo_sideral;
extern float altura_inicial_m;
extern float subida_da_gralha_ms;
extern float sopro_da_subida_alada;
extern float ultima_altura_do_voo_sideral;
extern unsigned long ultimo_sopro_do_oraculo;
extern float tendencia_da_temperatura_c;
extern float ultima_temperatura_do_ar_c;
extern bool modo_de_escuta_termal;
extern float fe_no_sopro_quente;
extern float ganho_do_sustentar;
extern float altura_desejada_do_voo;
extern float sopro_vital_do_sustentar;
extern bool modo_sustentar_ativo;
extern float pulsacao_da_chama_primordial;
extern float angulo_da_danca_alada;
extern float cadencia_do_destino_alado;
extern float pulso_do_sopro_vital;

/* As Invocações da Alma Alada — Rituais que a Gralha chama para manifestar o voo. */
float mapear_entre_escalas_harmonicas(float valor, float minimo_origem, float max_origem, float minimo_destino, float max_destino);
float forma_do_bater_das_asas(float canto_do_vento, float direcao_do_bater, float ferocidade_do_bater, float ferocidade_do_retorno);

#ifndef GRALHA_AZUL_NEOPIXEL_DESLIGADO
class MantoDeLuzCelestial {
private:
  Adafruit_NeoPixel chama_azul_pixel;
  uint16_t tonalidade_do_sonho_florestal;
  unsigned long ultimo_instante_de_respiracao_luminescente = 0;
  float pulsacao_da_chama_primordial = 0.0f;
public:
  MantoDeLuzCelestial() : chama_azul_pixel(QUANTIDADE_DE_CENTELHAS_NA_CHAMA, NUCLEO_DA_CHAMA_AZUL, NEO_GRB + NEO_KHZ800), tonalidade_do_sonho_florestal(0) {}
  void AcenderLuzPrimordial();
  void IrradiarLuzDaAlma();
};
extern MantoDeLuzCelestial manto_celestial_da_gralha;
#endif

extern Servo tendao_da_asa_matutina;
extern Servo tendao_da_asa_vespertina;

#ifndef GRALHA_AZUL_BAROMETRO_DESLIGADO
void DespertarOraculoDaPressao();
void EscutarPressaoDoCeu();
#else
inline void DespertarOraculoDaPressao() {}
inline void EscutarPressaoDoCeu() {}
#endif

void AoDespertarParaOCantoDoEter();
void AoRecolherSeAoSilencioDaMata();
#if defined(RECEPTOR_DOS_VENTOS_CRSF)
void InterpretarAsVozesDoFirmamento();
#elif defined(RECEPTOR_DOS_VENTOS_PPM)
void InterpretarAsVozesDoFirmamento(const unsigned long* channelValues, byte numChannels);
#endif
void gralhaAzulSetup();
void AnimarPulsarDoCoracaoAlado();
void SustentarAltura();
void ManifestarOVooNosVentos();
#if !defined(GRALHA_AZUL_TELEMETRIA_DESLIGADO) && defined(RECEPTOR_DOS_VENTOS_CRSF)
void SussurrarVooAoEter();
#else
inline void SussurrarVooAoEter() {}
#endif
void gralhaAzulLoop();

#endif