/*
  O Grande Código da Gralha Azul — Header Primordial
  A Inscrição que Guarda os Limiares da Alma Alada
*/

#ifndef GRALHA_AZUL_H
#define GRALHA_AZUL_H

#include <Arduino.h>
#include <Servo.h>

// =====================================================
// RECEPTOR: Descomente um no sketch antes do #include
// =====================================================
#ifndef RECEPTOR_DOS_VENTOS_CRSF
  #ifndef RECEPTOR_DOS_VENTOS_PPM
    #define RECEPTOR_DOS_VENTOS_CRSF  // padrão
  #endif
#endif

#if defined(RECEPTOR_DOS_VENTOS_CRSF)
  #include <CrsfSerial.h>
#elif defined(RECEPTOR_DOS_VENTOS_PPM)
  #include <PPMReaderRP2040.h>
#else
  #error "Defina RECEPTOR_DOS_VENTOS_CRSF ou RECEPTOR_DOS_VENTOS_PPM"
#endif

// =====================================================
// MÓDULOS OPCIONAIS (desligue antes do #include)
// =====================================================
// #define GRALHA_AZUL_NEOPIXEL_DESLIGADO    // remove NeoPixel
// #define GRALHA_AZUL_BAROMETRO_DESLIGADO   // remove BMP180
// #define GRALHA_AZUL_TELEMETRIA_DESLIGADO  // remove CRSF telemetria

#ifndef GRALHA_AZUL_NEOPIXEL_DESLIGADO
  #include <Adafruit_NeoPixel.h>
#endif

#ifndef GRALHA_AZUL_BAROMETRO_DESLIGADO
  #include <Wire.h>
  #include <Adafruit_Sensor.h>
  #include <Adafruit_BMP085_U.h>
#endif

// =====================================================
// CONSTANTES CONFIGURÁVEIS (com #ifndef para override)
// =====================================================

// --- Portas do Éter (UART) ---
#ifndef FREQUENCIA_DO_SOPRO_COSMICO
  #define FREQUENCIA_DO_SOPRO_COSMICO 420000
#endif
#ifndef PORTAL_DOS_VENTOS_CELESTES
  #define PORTAL_DOS_VENTOS_CELESTES Serial1
#endif

// --- Junturas da Alma (Servos) ---
#ifndef ARTICULACAO_ASA_DA_MANHA
  #define ARTICULACAO_ASA_DA_MANHA 8
#endif
#ifndef ARTICULACAO_ASA_DO_ENTARDECER
  #define ARTICULACAO_ASA_DO_ENTARDECER 7
#endif

// --- Vias de comunicação (UART pins) ---
#ifndef VIA_DOS_SONHOS_LUNARES
  #define VIA_DOS_SONHOS_LUNARES 1
#endif
#ifndef VIA_DOS_ECOS_SOLARES
  #define VIA_DOS_ECOS_SOLARES 0
#endif

// --- Chama Azul (NeoPixel) ---
#ifndef NUCLEO_DA_CHAMA_AZUL
  #define NUCLEO_DA_CHAMA_AZUL 16
#endif
#ifndef QUANTIDADE_DE_CENTELHAS_NA_CHAMA
  #define QUANTIDADE_DE_CENTELHAS_NA_CHAMA 1
#endif

// --- Oráculo da Pressão (BMP180) ---
#ifndef PINO_SILENCIO_DA_ALTURA
  #define PINO_SILENCIO_DA_ALTURA 4
#endif
#ifndef PINO_RITMO_DA_PRESSAO
  #define PINO_RITMO_DA_PRESSAO 5
#endif

// --- Mensageiro PPM ---
#ifndef PINO_DO_MENSAGEIRO
  #define PINO_DO_MENSAGEIRO 2
#endif
#ifndef NUM_CANAIS_DO_MENSAGEIRO
  #define NUM_CANAIS_DO_MENSAGEIRO 8
#endif

// --- Mistérios do Voo ---
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

// --- Constantes do Sustentar Altura ---
#ifndef ALTURA_MAX_DO_SUSTENTAR_M
  #define ALTURA_MAX_DO_SUSTENTAR_M 20.0f
#endif
#ifndef SOPRO_MIN_DO_SUSTENTAR
  #define SOPRO_MIN_DO_SUSTENTAR 1100
#endif
#ifndef SOPRO_MAX_DO_SUSTENTAR
  #define SOPRO_MAX_DO_SUSTENTAR 1800
#endif
#ifndef FORCA_BASE_DO_SUSTENTAR
  #define FORCA_BASE_DO_SUSTENTAR 180
#endif
#ifndef SILENCIO_DO_SUSTENTAR_M
  #define SILENCIO_DO_SUSTENTAR_M 0.5f
#endif
#ifndef LIMITE_DA_DESCIDA_SUSTENTADA_MS
  #define LIMITE_DA_DESCIDA_SUSTENTADA_MS 2.0f
#endif
#ifndef LIMITE_DA_SUBIDA_SUSTENTADA_MS
  #define LIMITE_DA_SUBIDA_SUSTENTADA_MS 3.0f
#endif

// =====================================================
// ESTADOS DA ALMA
// =====================================================
enum EstadoDaAlmaAlada : uint8_t {
  EM_DANCA_COM_OS_VENTOS,
  EM_SONHO_NA_QUIETUDE_DA_FLORESTA
};

enum ModoDoEspiritoAlado {
  EM_RITMO_DE_BATIDA_DAS_ASAS,
  EM_DESLIZE_ETERNO_E_CONTEMPLATIVO
};

// =====================================================
// RELÓGIO DAS ERAS
// =====================================================
struct RelogioDasEras {
  unsigned long instante_do_agora_cosmico;
  unsigned long ultimo_fulgor_da_chama_azul;
  unsigned long ultimo_eco_prescindivei;
  unsigned long ultima_pulsacao_do_sopro_alado;
  unsigned long ultimo_instante_de_respiracao_luminescente;
  float intervalo_entre_pulsacoes_do_coracao_alado;
};

// =====================================================
// EXTERNS — Variáveis globais (definidas em GralhaAzul.cpp)
// =====================================================
extern EstadoDaAlmaAlada estado_presente_da_alma;
extern ModoDoEspiritoAlado modo_presente_do_espirito;
extern bool limiar_elevado;
extern bool oraculo_respira;

extern int voz_do_aletao;
extern int voz_do_profundor;
extern int voz_do_sopro_vital;
extern int voz_do_leme_estelar;
extern int voz_do_despertar;
extern int voz_do_compasso_da_alma;
extern int voz_da_ferocidade_do_bater;
extern int voz_da_ferocidade_do_retorno;
extern int voz_da_ferocidade_do_leme;
extern int voz_do_sustentar_altura;

extern float angulo_da_danca_alada;
extern float cadencia_do_destino_alado;
extern float pulso_do_sopro_vital;
extern float ganho_do_sustentar;
extern float altura_desejada_do_voo;
extern float sopro_vital_do_sustentar;
extern bool modo_sustentar_ativo;
extern float pressao_do_ceu_hpa;
extern float temperatura_do_ar_c;
extern float altura_do_voo_sideral;
extern float altura_inicial_m;
extern float subida_da_gralha_ms;
extern float sopro_da_subida_alada;
extern float fe_no_sopro_quente;
extern bool modo_de_escuta_termal;
extern float pulsacao_da_chama_primordial;

extern RelogioDasEras relogio_das_eras;

// =====================================================
// OBJETOS EXTERNOS (definidos em GralhaAzul.cpp)
// =====================================================
#if defined(RECEPTOR_DOS_VENTOS_CRSF)
  extern CrsfSerial guardiao_dos_ventos_siderais;
#elif defined(RECEPTOR_DOS_VENTOS_PPM)
  extern PPMReader mensageiro_dos_ventos_cosmicos;
#endif

#ifndef GRALHA_AZUL_NEOPIXEL_DESLIGADO
  class MantoDeLuzCelestial {
  public:
    MantoDeLuzCelestial();
    void AcenderLuzPrimordial();
    void IrradiarLuzDaAlma();
  private:
    Adafruit_NeoPixel chama_azul_pixel;
    uint16_t tonalidade_do_sonho_florestal;
    unsigned long ultimo_instante_de_respiracao_luminescente = 0;
    float pulsacao_da_chama_primordial = 0.0f;
  };
  extern MantoDeLuzCelestial manto_celestial_da_gralha;
#endif

extern Servo tendao_da_asa_matutina;
extern Servo tendao_da_asa_vespertina;

// =====================================================
// FUNÇÕES PÚBLICAS
// =====================================================
float mapear_entre_escalas_harmonicas(float valor, float minimo_origem, float max_origem, float minimo_destino, float max_destino);
float forma_do_bater_das_asas(float canto_do_vento, float direcao_do_bater, float ferocidade_do_bater, float ferocidade_do_retorno);

void gralhaAzulSetup();
void gralhaAzulLoop();

// Callbacks (definidos no sketch ou em GralhaAzul.cpp)
void AoDespertarParaOCantoDoEter();
void AoRecolherSeAoSilencioDaMata();
void InterpretarAsVozesDoFirmamento();

// Módulos
#ifdef ORACULO_DA_PRESSAO_DO_CEU
  #ifndef GRALHA_AZUL_BAROMETRO_DESLIGADO
    void DespertarOraculoDaPressao();
    void EscutarPressaoDoCeu();
  #endif
#endif

#if defined(RECEPTOR_DOS_VENTOS_CRSF) && !defined(GRALHA_AZUL_TELEMETRIA_DESLIGADO)
  void SussurrarVooAoEter();
#endif

void AnimarPulsarDoCoracaoAlado();
void SustentarAltura();
void ManifestarOVooNosVentos();

#endif // GRALHA_AZUL_H
