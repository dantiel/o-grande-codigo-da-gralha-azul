/*
  O Grande Código da Gralha Azul
  First Official Release
  
  A Inscrição Primordial da Lenda Alada
  
  Nas eras antigas, quando o aroma dos pinheirais sagrados pairava como prece,
  e a araucária, árvore da vida, guardava em seu cerne o pinhão — a semente estelar —
  um corvo de plumagem como a noite profunda residia em seu galho ancestral.
  Mas o eco frio do aço quebrou a harmonia — a floresta, seu santuário, em perigo.
  Num voo desesperado, tingido pela angústia da mata, a ave ascendeu,
  buscando o Sol, o olho flamejante do firmamento, numa súplica silenciosa.
  Lá, no ápice dourado, onde o céu beija o infinito, uma Voz ecoou,
  não com palavras, mas com a pura luz da compreensão. O medo se transmutou.
  Do fogo solar, suas penas escuras renasceram em anil celeste,
  a cor da abóbada celeste, o reflexo da esperança imortal.
  E com o novo manto, uma missão sagrada lhe foi confiada:
  ser a Gralha Azul, a semeadora incansável, tecendo com as "estrelas verdes"
  do pinhão um futuro perene para as florestas do Sul.
  Este Grande Código é a inscrição dessa lenda, a essência viva da Gralha.
*/

#ifndef GRALHA_AZUL_H
#define GRALHA_AZUL_H

#include <Arduino.h>
#include "GralhaAzul_Padraos.h"

/* Os Oráculos e Conexões com o Cosmos: Os Sentidos da Gralha */
#ifdef RECEPTOR_CRSF
  #include <CrsfSerial.h>
#endif
#ifdef RECEPTOR_PPM
  #include <PPMReaderRP2040.h>
#endif
#include <Servo.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>

/* Os Estados da Alma Alada: Fases da Consciência da Gralha */
enum EstadoDaAlmaAlada : uint8_t {
  EM_DANCA_COM_OS_VENTOS,              // A Gralha ativa, respondendo aos chamados, cumprindo sua missão.
  EM_SONHO_NA_QUIETUDE_DA_FLORESTA    // A conexão se abranda, a Gralha medita em seu ninho de estrelas.
};

enum ModoDoEspiritoAlado : uint8_t {
  EM_RITMO_DE_BATIDA_DAS_ASAS,         // O voo impulsionado, a semeadura em ação.
  EM_DESLIZE_ETERNO_E_CONTEMPLATIVO    // O planar sereno, em comunhão e escuta.
};

/* O Relógio das Eras: Marcadores Temporais da Jornada da Gralha */
struct RelogioDasEras {
  unsigned long instante_do_agora_cosmico;
  unsigned long ultimo_fulgor_da_chama_azul;
  unsigned long ultimo_eco_prescindivei;
  unsigned long ultima_pulsacao_do_sopro_alado;
  unsigned long ultimo_instante_de_respiracao_luminescente;
  float intervalo_entre_pulsacoes_do_coracao_alado;
};

/* O Coração do Mistério Alado: A Essência da Gralha */
class GralhaAzul {
public:
  /* As Relíquias da Gralha: Vínculos de Poder e Essência */
  // Os pontos de contato com o mundo, ecos da sua jornada.
  
  // Articulações das Asas — onde a matéria responde à vontade alada
  uint8_t articulacaoAsaDaManha    = ARTICULACAO_ASA_DA_MANHA_PADRAO;      // Asa que se ergue com a aurora.
  uint8_t articulacaoAsaDoEntardecer = ARTICULACAO_ASA_DO_ENTARDECER_PADRAO;  // Asa que se recolhe com o crepúsculo.

  // Vias do Sopro Cósmico — os canais pelos quais o destino sussurra
  uint8_t viaDosSonhosLunares      = VIA_DOS_SONHOS_LUNARES_PADRAO;      // Canal dos sussurros da noite.
  uint8_t viaDosEcosSolares        = VIA_DOS_ECOS_SOLARES_PADRAO;        // Canal da canção ao dia.

  // Geometria Sagrada do Voo — as leis imutáveis da natureza alada
  float cicloDoCoracaoAlado        = CICLO_DO_CORACAO_ALADO_PADRAO;      // A pulsação rítmica do voo.
  float escalaAngularArticulacao   = ESCALA_ANGULAR_DA_ARTICULACAO_PADRAO;  // A medida do arco celeste.

  // Ecos Prescindíveis — a voz que partilha estados (Debug)
  Stream* ecosPrescindiveis = nullptr;

  /* Módulos Opcionais: As Faculdades que Podem Dormir */
  bool barometroDesligado = false;
  bool neopixelDesligado  = false;
  bool telemetriaDesligado = false;

  /* Os Rituais Públicos: A Dança da Gralha */
  void begin();   // O Despertar
  void update();  // A Pulsação Contínua


private:
  /* A Ponte Estática: Ecos entre Dimensões */
  static GralhaAzul* instanciaGralhaParaEventos;
  static void eventoLinkUp() { if (instanciaGralhaParaEventos) instanciaGralhaParaEventos->aoDespertarParaOCantoDoEter(); }
  static void eventoLinkDown() { if (instanciaGralhaParaEventos) instanciaGralhaParaEventos->aoRecolherSeAoSilencioDaMata(); }
  static void eventoPacketChannels() { if (instanciaGralhaParaEventos) instanciaGralhaParaEventos->interpretarAsVozesDoFirmamento(); }

  /* Os Mistérios Internos: O Que Só a Gralha Conhece */
  #ifdef RECEPTOR_CRSF
  alignas(alignof(CrsfSerial)) uint8_t guardiaoBuffer[sizeof(CrsfSerial)] = {0};
  CrsfSerial* guardiaoDosVentosSiderais = nullptr;
  #endif
  #ifdef RECEPTOR_PPM
  PPMReader* mensageiroDosVentosCosmicos = nullptr;
  #endif
  
  // Os Tendões das Asas — a matéria que obedece à vontade
  Servo tendaoDaAsaMatutina;
  Servo tendaoDaAsaVespertina;

  alignas(alignof(Adafruit_NeoPixel)) uint8_t chamaAzulBuffer[sizeof(Adafruit_NeoPixel)] = {0};
  Adafruit_NeoPixel* chamaAzulPixel = nullptr;
  uint16_t tonalidadeDoSonhoFlorestal = 0;
  unsigned long ultimoInstanteRespiracaoLuminescente = 0;
  float pulsacaoDaChamaPrimordial = 0.0f;

  // O Oráculo da Pressão — aquele que lê o sopro do mundo
  void* oraculoDaPressao = nullptr;

  EstadoDaAlmaAlada estadoPresenteDaAlma = EM_SONHO_NA_QUIETUDE_DA_FLORESTA;
  ModoDoEspiritoAlado modoPresenteDoEspirito = EM_DESLIZE_ETERNO_E_CONTEMPLATIVO;
  bool limiarElevado = true;
  bool oraculoRespira = false;

  // As Vozes do Céu — as inspirações que moldam o destino
  int vozDoAlerao = 1500;
  int vozDoProfundor = 1500;
  int vozDoSoproVital = 1000;
  int vozDoLemeEstelar = 1500;
  int vozDoDespertar = 0;
  int vozDoCompassoDaAlma = 1500;
  int vozDaFerocidadeDoBater = 1000;
  int vozDaFerocidadeDoRetorno = 1000;
  int vozDaFerocidadeDoLeme = 1000;
  int vozDoSustentarAltura = 1000;

  // Telemetria — temporizadores
  unsigned long ultimo_sopro_sideral = 0;
  unsigned long ultimo_sopro_termico = 0;

  // Barómetro — estado
  // As Leituras do Oráculo — o que o céu revela
  float pressaoDoCeuHpa = 0.0f;
  float temperaturaDoArC = 0.0f;
  float alturaDoVooSideral = 0.0f;
  float alturaInicialM = 0.0f;
  float subidaDaGralhaMs = 0.0f;
  float soproDaSubidaAlada = 0.0f;
  float ultimaAlturaDoVooSideral = 0.0f;
  unsigned long ultimoSoproDoOraculo = 0;
  float tendenciaDaTemperaturaC = 0.0f;
  float ultimaTemperaturaDoArC = 0.0f;
  bool modoDeEscutaTermal = false;
  float feNoSoproQuente = 0.0f;

  // A Geometria Sagrada do Voo — a essência do movimento alado
  float anguloDaDancaAlada = 0;
  float cadenciaDoDestinoAlado = 0;
  float pulsoDoSoproVital = 0.0;
  float ganhoDoSustentar = 0.0f;
  float alturaDesejadaDoVoo = 0.0f;
  float soproVitalDoSustentar = 1000.0f;
  bool modoSustentarAtivo = false;
  float erroFiltradoSustentar = 0.0f;

  // O Relógio das Eras — o tempo que passa
  RelogioDasEras relogioDasEras = {0};

  float mapearEntreEscalasHarmonicas(float valor, float minOrigem, float maxOrigem, float minDestino, float maxDestino);
  float formaDoBaterDasAsas(float cantoDoVento, float ferocidadeDoBater, float ferocidadeDoRetorno);
  void animarPulsarDoCoracaoAlado();
  void sustentarAltura();
  void manifestarOVooNosVentos();
  void sussurrarVooAoEter();
  void despertarOraculoDaPressao();
  void escutarPressaoDoCeu();
  void aoDespertarParaOCantoDoEter();
  void aoRecolherSeAoSilencioDaMata();
  void interpretarAsVozesDoFirmamento();
  void irradiarLuzDaAlma();
  void acenderLuzPrimordial();
};

/* Ecos Prescindíveis: A Voz que Partilha Estados */
// Defina #define ECOS_PRESCINDIVEIS_DA_ALMA_ALADA antes de #include <GralhaAzul.h>
// para que a Gralha possa sussurrar seus estados ao mundo.

#endif /* GRALHA_AZUL_H */