/*
  O Grande Código da Gralha Azul
  A Inscrição Primordial da Lenda Alada
  — Núcleo Hermético Partilhado entre Modelos —

  Este header contém todas as constantes, tipos e declarações
  que cada modelo (exemplo) pode sobrescrever via #define antes
  de #include <GralhaAzul.h>.

  Uso:
    #define RECEPTOR_DOS_VENTOS_PPM
    #define ARTICULACAO_ASA_DA_MANHA 9
    #include <GralhaAzul.h>
*/

#ifndef GRALHA_AZUL_H
#define GRALHA_AZUL_H

#include <Arduino.h>
#include <Servo.h>

// =======================================================
// MÓDULOS OPCIONAIS (ativados por omissão)
// Defina ANTES de #include <GralhaAzul.h> para desativar
// =======================================================
// #define GRALHA_AZUL_NEOPIXEL_DESLIGADO
// #define GRALHA_AZUL_BAROMETRO_DESLIGADO
// #define GRALHA_AZUL_TELEMETRIA_DESLIGADO

// =======================================================
// ORÁCULOS E CONEXÕES COM O COSMOS
// =======================================================
//#define ECOS_PRESCINDIVEIS_DA_ALMA_ALADA // Se definido, a Gralha partilha seus estados (Debug).
#ifndef FREQUENCIA_DO_SOPRO_COSMICO
  #define FREQUENCIA_DO_SOPRO_COSMICO 420000
#endif
#ifndef PORTAL_DOS_VENTOS_CELESTES
  #define PORTAL_DOS_VENTOS_CELESTES Serial1
#endif

// =======================================================
// ESCOLHA DO RECEPTOR (CRSF por omissão)
// =======================================================
#ifndef RECEPTOR_DOS_VENTOS_CRSF
  #define RECEPTOR_DOS_VENTOS_CRSF
#endif

// =======================================================
// INCLUDES CONDICIONAIS
// =======================================================
#if defined(RECEPTOR_DOS_VENTOS_CRSF)
#include <CrsfSerial.h>
#elif defined(RECEPTOR_DOS_VENTOS_PPM)
#include <PPMReaderRP2040.h>
#endif

#ifndef GRALHA_AZUL_NEOPIXEL_DESLIGADO
#include <Adafruit_NeoPixel.h>
#endif

#ifndef GRALHA_AZUL_BAROMETRO_DESLIGADO
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>
#endif

// =======================================================
// AS RELÍQUIAS DA GRALHA — PINOS
// =======================================================
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

// =======================================================
// FIOS DO ORÁCULO DA PRESSÃO
// =======================================================
#ifndef PINO_SILENCIO_DA_ALTURA
  #define PINO_SILENCIO_DA_ALTURA 4
#endif
#ifndef PINO_RITMO_DA_PRESSAO
  #define PINO_RITMO_DA_PRESSAO 5
#endif

// =======================================================
// CONSTANTES DE VOO
// =======================================================
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

// =======================================================
// VIBRAÇÕES PRIMORDIAIS — CENTROS DOS CANAIS
// =======================================================
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

// =======================================================
// CONSTANTES DO SUSTENTAR ALTURA
// =======================================================
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

// =======================================================
// TIPOS E ENUMERAÇÕES
// =======================================================
enum EstadoDaAlmaAlada : uint8_t {
  EM_DANCA_COM_OS_VENTOS,
  EM_SONHO_NA_QUIETUDE_DA_FLORESTA
};

enum ModoDoEspiritoAlado {
  EM_RITMO_DE_BATIDA_DAS_ASAS,
  EM_DESLIZE_ETERNO_E_CONTEMPLATIVO
};

// =======================================================
// CLASSE MANTO DE LUZ CELESTIAL
// =======================================================
#ifndef GRALHA_AZUL_NEOPIXEL_DESLIGADO
class MantoDeLuzCelestial {
private:
  Adafruit_NeoPixel chama_azul_pixel;
  uint16_t tonalidade_do_sonho_florestal;
  unsigned long ultimo_instante_de_respiracao_luminescente;
  float pulsacao_da_chama_primordial;

public:
  MantoDeLuzCelestial();
  void AcenderLuzPrimordial();
  void IrradiarLuzDaAlma();
};
#else
class MantoDeLuzCelestial {
public:
  MantoDeLuzCelestial() {}
  void AcenderLuzPrimordial() {}
  void IrradiarLuzDaAlma() {}
};
#endif

// =======================================================
// DECLARAÇÕES EXTERN — VARIÁVEIS GLOBAIS
// =======================================================
#if defined(RECEPTOR_DOS_VENTOS_CRSF)
extern CrsfSerial guardiao_dos_ventos_siderais;
#elif defined(RECEPTOR_DOS_VENTOS_PPM)
extern PPMReader mensageiro_dos_ventos_cosmicos;
#endif

extern MantoDeLuzCelestial manto_celestial_da_gralha;
extern Servo tendao_da_asa_matutina;
extern Servo tendao_da_asa_vespertina;

extern bool limiar_elevado;
extern bool oraculo_respira;

extern EstadoDaAlmaAlada estado_presente_da_alma;
extern ModoDoEspiritoAlado modo_presente_do_espirito;

extern int voz_do_sustentar_altura;

extern struct RelogioDasEras {
  unsigned long instante_do_agora_cosmico;
  unsigned long ultimo_fulgor_da_chama_azul;
  unsigned long ultimo_eco_prescindivei;
  unsigned long ultima_pulsacao_do_sopro_alado;
  unsigned long ultimo_instante_de_respiracao_luminescente;
  float intervalo_entre_pulsacoes_do_coracao_alado;
} relogio_das_eras;

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

// =======================================================
// DECLARAÇÕES DE FUNÇÕES
// =======================================================
float mapear_entre_escalas_harmonicas(float valor, float minimo_origem, float max_origem, float minimo_destino, float max_destino);
float forma_do_bater_das_asas(float canto_do_vento, float direcao_do_bater, float ferocidade_do_bater, float ferocidade_do_retorno);

void DespertarOraculoDaPressao();
void EscutarPressaoDoCeu();
void AoDespertarParaOCantoDoEter();
void AoRecolherSeAoSilencioDaMata();
void InterpretarAsVozesDoFirmamento();
void AnimarPulsarDoCoracaoAlado();
void SustentarAltura();
void ManifestarOVooNosVentos();
void SussurrarVooAoEter();

void gralhaAzulSetup();
void gralhaAzulLoop();

#endif // GRALHA_AZUL_H