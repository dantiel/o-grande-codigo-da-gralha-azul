/*
  O Grande Código da Gralha Azul
  A Inscrição Primordial da Lenda Alada
  — Invocação do Coração Alado Partilhado entre Modelos —
*/

#ifndef GRALHA_AZUL_H
#define GRALHA_AZUL_H

/* O Grimório da Configuração Alada — onde a Gralha guarda os segredos da sua forma. */
#include "GralhaAzulConfig.h"

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
extern float ganho_do_sustentar;
extern float altura_desejada_do_voo;
extern float sopro_vital_do_sustentar;
extern bool modo_sustentar_ativo;
extern float angulo_da_danca_alada;
extern float ultima_altura_do_voo_sideral;
extern unsigned long ultimo_sopro_do_oraculo;
extern float tendencia_da_temperatura_c;
extern float ultima_temperatura_do_ar_c;
extern bool modo_de_escuta_termal;
extern float fe_no_sopro_quente;
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