/*
  //  O Grande Código da Gralha Azul — v1.30.30
  * v1.30.30: formaDoBaterDasAsas(): ferocidade >= 90% (CH7/CH8 ≥ 1900)
  *   → onda quadrada pura (sign do seno), sem tanh. Merge do algoritmo
  *   Kazu-kaku com o Dantiel. MODO_DE_VOO_ALTERNATIVO: removido
  *   *magnitudeDaBatida espúrio que reduzia amplitude a 4%.
  * v1.30.29: velocidadeAngularPorMicros movida para fora do bloco flap
  *   em respirarAlmaAlada(). Era calculada só EM_RITMO_DE_BATIDA_DAS_ASAS,
  *   ficando a 0.0f no arranque (EM_DESLIZE_ETERNO_E_CONTEMPLATIVO).
  *   tecerTransicaoGlide() via passoMax=0 → asas imóveis. Agora comum.
  * v1.30.28: jaCruzouLimiarDeVoo impede que o glide no arranque active
  *   a histerese. Asas batem ao passar 1040 mesmo que o throttle tenha
  *   estado abaixo disso ao armar. Só após a primeira transição flap→glide
  *   é que a histerese centrada (±50) entra em efeito.
  * v1.30.27: limiarElevado = false no arranque e no failsafe.

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
#include <new>
#include "GralhaAzul_Padraos.h"
#include <cmath>

/* ═══════════════════════════════════════════════════════════════
   A PONTE ARCANA — Tradução dos #define do Sketch
   O sketch define ANTES de #include <GralhaAzul.h>.
   O header lê esses defines (visíveis nesta TU) e os traduz
   em macros GRALHA_TEM_* que o .cpp também vê (pois inclui este header).
   ═══════════════════════════════════════════════════════════════ */

/* ── O Guardião dos Ventos Siderais ───────────────────────── */
#ifdef GUARDIAO_DOS_VENTOS_SIDERAIS
  #include <CrsfSerial.h>
  #define GRALHA_TEM_GUARDIAO_DOS_VENTOS 1
#else
  #define GRALHA_TEM_GUARDIAO_DOS_VENTOS 0
#endif

/* ── O Mensageiro dos Cantos Cósmicos ─────────────────────── */
#ifdef MENSAGEIRO_DOS_CANTOS_COSMICOS
  #include <PPMReaderRP2040.h>
  #define GRALHA_TEM_MENSAGEIRO_DOS_CANTOS 1
#else
  #define GRALHA_TEM_MENSAGEIRO_DOS_CANTOS 0
#endif

/* ── A Chama Azul ──────────────────────────────────────────── */
#ifdef CHAMA_AZUL_DESLIGADA
  #define GRALHA_TEM_CHAMA_AZUL 0
#elif __has_include(<Adafruit_NeoPixel.h>)
  #include <Adafruit_NeoPixel.h>
  #define GRALHA_TEM_CHAMA_AZUL 1
#else
  #define GRALHA_TEM_CHAMA_AZUL 0
#endif

/* ── O Oráculo da Pressão ──────────────────────────────────── */
#ifdef ORACULO_DESLIGADO
  #define GRALHA_TEM_ORACULO 0
#elif __has_include(<Adafruit_BMP085_U.h>)
  #include <Adafruit_Sensor.h>
  #include <Adafruit_BMP085_U.h>
  #define GRALHA_TEM_ORACULO 1
#else
  #define GRALHA_TEM_ORACULO 0
#endif

#include <Servo.h>

/* ═══════════════════════════════════════════════════════════════
   VALORES CONFIGURÁVEIS — Com fallback aos padrões
   O sketch pode sobrescrever definindo ANTES do #include.
   ═══════════════════════════════════════════════════════════════ */

/* ── O Portal dos Cantos Cósmicos ──────────────────────────── */
#ifndef PORTAL_DOS_CANTOS_COSMICOS
  #define PORTAL_DOS_CANTOS_COSMICOS  2
#endif
#ifndef NUMERO_DE_CANTOS
  #define NUMERO_DE_CANTOS            8
#endif

/* ── A Via do Sopro Cósmico ────────────────────────────────── */
#ifndef VIA_DO_SOPRO_COSMICO
  #define VIA_DO_SOPRO_COSMICO VIA_DO_SOPRO_COSMICO_PADRAO
#endif

/* ── Módulos Desligados ────────────────────────────────────── */
#ifndef SUSSURRO_DESLIGADO
  #define GRALHA_SUSSURRO_DESLIGADO false
#else
  #define GRALHA_SUSSURRO_DESLIGADO true
#endif


/* ═══════════════════════════════════════════════════════════════
   OS ESTADOS DA ALMA ALADA
   ═══════════════════════════════════════════════════════════════ */

enum EstadoDaAlmaAlada : uint8_t {
  EM_DANCA_COM_OS_VENTOS,              // Ativa, respondendo aos chamados.
  EM_SONHO_NA_QUIETUDE_DA_FLORESTA    // Conexão abrandada, medita no ninho.
};

enum ModoDoEspiritoAlado : uint8_t {
  EM_RITMO_DE_BATIDA_DAS_ASAS,         // Voo impulsionado.
  EM_DESLIZE_ETERNO_E_CONTEMPLATIVO    // Planar sereno.
};

/* ── O Relógio das Eras ────────────────────────────────────── */
struct RelogioDasEras {
  unsigned long instante_do_agora_cosmico;
  unsigned long ultimo_fulgor_da_chama_azul;
  unsigned long ultimo_eco_prescindivei;
  unsigned long ultima_pulsacao_do_sopro_alado;
  unsigned long ultimo_instante_de_respiracao_luminescente;
  float intervalo_entre_pulsacoes_do_coracao_alado;
};


/* ═══════════════════════════════════════════════════════════════
   O CORAÇÃO DO MISTÉRIO ALADO — A Essência da Gralha
   Layout da classe é sempre idêntico em todas as TUs.
   ═══════════════════════════════════════════════════════════════ */

class GralhaAzul {
public:
  /* ── Relíquias Configuráveis ─────────────────────────────── */
#ifdef ARTICULACAO_DA_ASA_MATUTINA
  uint8_t articulacaoAsaDaManha      = ARTICULACAO_DA_ASA_MATUTINA;
#else
  uint8_t articulacaoAsaDaManha      = ARTICULACAO_ASA_DA_MANHA_PADRAO;
#endif
#ifdef ARTICULACAO_DA_ASA_DO_ENTARDECER
  uint8_t articulacaoAsaDoEntardecer = ARTICULACAO_DA_ASA_DO_ENTARDECER;
#else
  uint8_t articulacaoAsaDoEntardecer = ARTICULACAO_ASA_DO_ENTARDECER_PADRAO;
#endif

#ifdef VIA_DOS_SONHOS_LUNARES
  uint8_t viaDosSonhosLunares = VIA_DOS_SONHOS_LUNARES;
#else
  uint8_t viaDosSonhosLunares = VIA_DOS_SONHOS_LUNARES_PADRAO;
#endif
#ifdef VIA_DOS_ECOS_SOLARES
  uint8_t viaDosEcosSolares   = VIA_DOS_ECOS_SOLARES;
#else
  uint8_t viaDosEcosSolares   = VIA_DOS_ECOS_SOLARES_PADRAO;
#endif
#ifdef FREQUENCIA_DO_SOPRO_COSMICO
  uint32_t frequenciaDoSoproCosmico = FREQUENCIA_DO_SOPRO_COSMICO;
#else
  uint32_t frequenciaDoSoproCosmico = FREQUENCIA_DO_SOPRO_COSMICO_PADRAO;
#endif

#ifdef CICLO_DO_CORACAO_ALADO
  float cicloDoCoracaoAlado      = CICLO_DO_CORACAO_ALADO;
#else
  float cicloDoCoracaoAlado      = CICLO_DO_CORACAO_ALADO_PADRAO;
#endif
#ifdef ESCALA_ANGULAR_ARTICULACAO
  float escalaAngularArticulacao = ESCALA_ANGULAR_ARTICULACAO;
#else
  float escalaAngularArticulacao = ESCALA_ANGULAR_DA_ARTICULACAO_PADRAO;
#endif
#ifdef MAGNITUDE_DA_BATIDA
  float magnitudeDaBatida = MAGNITUDE_DA_BATIDA;
#else
  float magnitudeDaBatida = MAGNITUDE_DA_BATIDA_PADRAO;
#endif
#ifdef ANGULO_DO_PLANAR_SERENO
  float anguloDoPlanarSereno = ANGULO_DO_PLANAR_SERENO;
#else
  float anguloDoPlanarSereno = ANGULO_DO_PLANAR_SERENO_PADRAO;
#endif

  /* ── Ecos Prescindíveis ── */
  decltype(&Serial) ecosPrescindiveis = nullptr; 


  /* ── Módulos Desligados ──────────────────────────────────── */
  bool barometroDesligado   = (GRALHA_TEM_ORACULO == 0);
  bool neopixelDesligado    = (GRALHA_TEM_CHAMA_AZUL == 0);
  bool telemetriaDesligado  = GRALHA_SUSSURRO_DESLIGADO;

  /* ── Modo de Voo ─────────────────────────────────────────── */
#ifdef MODO_DE_VOO_ALTERNATIVO
  bool modoDeVooAlternativo  = true;   // runtime toggle, compile-time default
#else
  bool modoDeVooAlternativo  = false;  // runtime toggle, compile-time default
#endif

  /* ── Portal dos Cantos ───────────────────────────────────── */
  uint8_t portalDosCantosCosmicos = PORTAL_DOS_CANTOS_COSMICOS;
  uint8_t numeroDeCantos          = NUMERO_DE_CANTOS;

  /* ── Os Rituais ──────────────────────────────────────────── */
  void begin();
  void update();

private:
  /* ── Ponte para os Presságios do Firmamento ──────────────── */
  inline static GralhaAzul* instanciaGralhaParaEventos = nullptr;
  static void eventoLinkUp()        { if (instanciaGralhaParaEventos) instanciaGralhaParaEventos->aoDespertarParaOCantoDoEter(); }
  static void eventoLinkDown()      { if (instanciaGralhaParaEventos) instanciaGralhaParaEventos->aoRecolherSeAoSilencioDaMata(); }
  static void eventoPacketChannels(){ if (instanciaGralhaParaEventos) instanciaGralhaParaEventos->interpretarAsVozesDoFirmamento(); }

  /* ── Guardião dos Ventos Siderais ────────────────────────── */
  #if GRALHA_TEM_GUARDIAO_DOS_VENTOS
  alignas(alignof(CrsfSerial)) uint8_t guardiaoBuffer[sizeof(CrsfSerial)];
  #endif
  void* guardiaoDosVentosSiderais = nullptr;

  /* ── Mensageiro dos Cantos Cósmicos ──────────────────────── */
  #if GRALHA_TEM_MENSAGEIRO_DOS_CANTOS
  alignas(alignof(PPMReader)) uint8_t mensageiroBuffer[sizeof(PPMReader)];
  #endif
  void* mensageiroDosVentosCosmicos = nullptr;

  /* ── Tendões das Asas ────────────────────────────────────── */
  Servo tendaoDaAsaMatutina;
  Servo tendaoDaAsaVespertina;
  float emaServoEsquerdo = OFFSET_ANGULAR_NEUTRO_PADRAO;
  float emaServoDireito  = OFFSET_ANGULAR_NEUTRO_PADRAO;
  int ultimoEscritoEsquerdo = OFFSET_ANGULAR_NEUTRO_PADRAO;
  int ultimoEscritoDireito  = OFFSET_ANGULAR_NEUTRO_PADRAO;
  uint32_t ultimoMicrosEscritaEsquerdo = 0;
  uint32_t ultimoMicrosEscritaDireito  = 0;

  /* ── A Chama Azul ────────────────────────────────────────── */
  #if GRALHA_TEM_CHAMA_AZUL
  alignas(alignof(Adafruit_NeoPixel)) uint8_t chamaBuffer[sizeof(Adafruit_NeoPixel)];
  #endif
  void* chamaAzulPixel = nullptr;
  uint16_t tonalidadeDoSonhoFlorestal = 0;
  unsigned long ultimoInstanteRespiracaoLuminescente = 0;
  float pulsacaoDaChamaPrimordial = 0.0f;

  /* ── O Oráculo da Pressão ────────────────────────────────── */
  #if GRALHA_TEM_ORACULO
  alignas(alignof(Adafruit_BMP085_Unified)) uint8_t oraculoBuffer[sizeof(Adafruit_BMP085_Unified)];
  #endif
  void* oraculoDaPressao = nullptr;

  /* ── Estado Interno ──────────────────────────────────────── */
  EstadoDaAlmaAlada estadoPresenteDaAlma = EM_SONHO_NA_QUIETUDE_DA_FLORESTA;
  ModoDoEspiritoAlado modoPresenteDoEspirito = EM_DESLIZE_ETERNO_E_CONTEMPLATIVO;
  bool limiarElevado = false;
  bool jaCruzouLimiarDeVoo = false;
  bool oraculoRespira = false;
#ifdef MODO_DE_VOO_ALTERNATIVO
  bool _modoAlternativoEfetivo = true;
#else
  bool _modoAlternativoEfetivo = false;
#endif

  /* ── Vozes do Céu ────────────────────────────────────────── */
  int vozDoAletao = 1500;
  int vozDoProfundor = 1500;
  int vozDoSoproVital = 1000;
  int vozDoLemeEstelar = 1500;
  int vozDoDespertar = 0;
  int vozDoCompassoDaAlma = 1500;
  int vozDaFerocidadeDoBater = 1000;
  int vozDaFerocidadeDoRetorno = 1000;
  int vozDaFerocidadeDoLeme = 1000;
  int vozDoSustentarAltura = 1000;

  /* ── Guardião contra Fantasmas Eléctricos ────────────────── */
  // CRSF corre a ~250Hz (4ms entre frames).
  // Um stick físico não pode mover >100µs em 4ms — se moveu,
  // é um glitch eléctrico do recetor e o frame é rejeitado.
  // CH5 (arm) pode saltar 1000↔2000 legitimamente.
  // O primeiro frame após link-up é aceite incondicionalmente
  // para inicializar as referências do Guardião.
  static constexpr int DELTA_MAXIMO_DO_GUARDIAO = 100;
  static constexpr int DELTA_MAXIMO_DO_GUARDIAO_ARM = 500;
  bool guardiaoInicializado = false;
  int guardiaoVoz1 = 1500;
  int guardiaoVoz2 = 1500;
  int guardiaoVoz3 = 1000;
  int guardiaoVoz4 = 1500;
  int guardiaoVoz5 = 1000;
  int guardiaoVoz6 = 1500;
  int guardiaoVoz7 = 1500;
  int guardiaoVoz8 = 1500;
  int guardiaoVoz9 = 1500;
  int guardiaoVoz10 = 1500;

  // Persistência temporal: 2 frames consecutivos com delta anómalo
  // confirmam stick legítimo. 1 frame isolado = fantasma (bloqueado).
  int guardiaoCandidato[10] = {0};
  uint8_t guardiaoPersistencia[10] = {0};
  static constexpr int DELTA_PERSISTENCIA_DO_GUARDIAO = 200;

  /* ── Telemetria ──────────────────────────────────────────── */
  unsigned long ultimo_sopro_sideral = 0;
  unsigned long ultimo_sopro_termico = 0;

  /* ── Leituras do Oráculo ─────────────────────────────────── */
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

  /* ── Geometria do Voo ────────────────────────────────────── */
  float anguloDaDancaAlada = 0;
  float cadenciaDoDestinoAlado = 0;
  float amplitudeMaximaPermitida = 0.0f;  // em MODO_DE_VOO_ALTERNATIVO: amp máx baseada em frequência
  float pulsoDoSoproVital = 0.0;
  float ganhoDoSustentar = 0.0f;
  float alturaDesejadaDoVoo = 0.0f;
  float soproVitalDoSustentar = 1000.0f;
  bool modoSustentarAtivo = false;
  float erroFiltradoSustentar = 0.0f;

  /* ── Transição Suave para Glide ────────────────────────────── */
  bool emTransicaoParaGlide = false;
  float anguloGlideEsquerdo = INFINITY;  // INFINITY = não inicializado
  float anguloGlideDireito = INFINITY;
  uint32_t microsUltimoPasso = 0;
  float velocidadeAngularPorMicros = 0.0f;  // °/µs = (60/ciclo) / 1e6

  /* ── Relógio ─────────────────────────────────────────────── */
  RelogioDasEras relogioDasEras = {0};

  /* ── Métodos Privados ────────────────────────────────────── */
  void tecerTransicaoGlide(float alvoEsquerdo, float alvoDireito);
  float mapearEntreEscalasHarmonicas(float valor, float minOrigem, float maxOrigem, float minDestino, float maxDestino);
  float formaDoBaterDasAsas(float anguloDoCiclo, float ferocidadeDoBater, float ferocidadeDoRetorno, float limiarShared = NAN);
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

//  O DESPERTAR — Quando a Gralha Abre os Olhos
// ============================================================
inline void GralhaAzul::begin() {
  delay(1000);
  
  if (ecosPrescindiveis) {

    ecosPrescindiveis->begin(115200);
    delay(1500);  // Aguardar Serial estabilizar
    ecosPrescindiveis->println("O Grande Código da Gralha Azul: A Lenda Viva se Inicia...");
  }
  
  // ── O Despertar dos Guardiões ────────────────────────────
  // Receptor determinado pelo sketch via #define RECEPTOR_*
  #if GRALHA_TEM_GUARDIAO_DOS_VENTOS
    if (ecosPrescindiveis) ecosPrescindiveis->println("O Guardião dos Ventos Siderais desperta...");
    if (ecosPrescindiveis) {
      ecosPrescindiveis->print("[DESPERTAR] Ecos Solares=");
      ecosPrescindiveis->print(viaDosEcosSolares);
      ecosPrescindiveis->print(" Sonhos Lunares=");
      ecosPrescindiveis->println(viaDosSonhosLunares);
    }
    if (ecosPrescindiveis) {
      ecosPrescindiveis->print("[DESPERTAR] Abrindo o Sopro Cósmico: Ecos=");
      ecosPrescindiveis->print(viaDosEcosSolares);
      ecosPrescindiveis->print(" Sonhos=");
      ecosPrescindiveis->println(viaDosSonhosLunares);
    }
    VIA_DO_SOPRO_COSMICO.setTX(viaDosEcosSolares);
    VIA_DO_SOPRO_COSMICO.setRX(viaDosSonhosLunares);
    VIA_DO_SOPRO_COSMICO.begin(frequenciaDoSoproCosmico);
    if (ecosPrescindiveis) ecosPrescindiveis->println("[DESPERTAR] Sopro Cósmico aberto");
    memset(guardiaoBuffer, 0, sizeof(guardiaoBuffer));
    if (ecosPrescindiveis) ecosPrescindiveis->println("[DESPERTAR] Forjando o Guardião dos Ventos...");
    CrsfSerial* crsf = new (guardiaoBuffer) CrsfSerial(VIA_DO_SOPRO_COSMICO, frequenciaDoSoproCosmico);
    guardiaoDosVentosSiderais = crsf;
    if (ecosPrescindiveis) ecosPrescindiveis->println("[DESPERTAR] Guardião forjado");
    instanciaGralhaParaEventos = this;
    crsf->onLinkUp = &GralhaAzul::eventoLinkUp;
    crsf->onLinkDown = &GralhaAzul::eventoLinkDown;
    crsf->onPacketChannels = &GralhaAzul::eventoPacketChannels;
    crsf->setPassthroughMode(false);
    crsf->begin(0);
    if (ecosPrescindiveis) ecosPrescindiveis->println("[DESPERTAR] Guardião ungido — ouvidos atentos");
    if (ecosPrescindiveis) ecosPrescindiveis->println("[DESPERTAR] Pronto para os Cantos do Firmamento");
    if (ecosPrescindiveis) {
      ecosPrescindiveis->print("[DESPERTAR] Sopro disponível: ");
      ecosPrescindiveis->println(VIA_DO_SOPRO_COSMICO.available());
    }
  #endif

  // ── O Portal dos Cantos Cósmicos ─────────────────────────
  #if GRALHA_TEM_MENSAGEIRO_DOS_CANTOS
    if (ecosPrescindiveis) ecosPrescindiveis->println("O Mensageiro dos Cantos Cósmicos desperta...");
    memset(mensageiroBuffer, 0, sizeof(mensageiroBuffer));
    PPMReader* ppm = new (mensageiroBuffer) PPMReader(portalDosCantosCosmicos, numeroDeCantos);
    mensageiroDosVentosCosmicos = ppm;
    ppm->begin();
  #endif

  tendaoDaAsaMatutina.attach(articulacaoAsaDaManha, PULSO_MINIMO_SERVO_PADRAO, PULSO_MAXIMO_SERVO_PADRAO);
  tendaoDaAsaVespertina.attach(articulacaoAsaDoEntardecer, PULSO_MINIMO_SERVO_PADRAO, PULSO_MAXIMO_SERVO_PADRAO);
  // Posicionar as asas em neutro ao iniciar
  tendaoDaAsaMatutina.write(OFFSET_ANGULAR_NEUTRO_PADRAO);
  tendaoDaAsaVespertina.write(OFFSET_ANGULAR_NEUTRO_PADRAO);

  // ── O Acender da Chama Azul ───────────────────────────────
  #if GRALHA_TEM_CHAMA_AZUL
  if (!neopixelDesligado) {
    memset(chamaBuffer, 0, sizeof(chamaBuffer));
    Adafruit_NeoPixel* neo = new (chamaBuffer) Adafruit_NeoPixel(QUANTIDADE_DE_CENTELHAS_PADRAO, NUCLEO_DA_CHAMA_AZUL_PADRAO, NEO_GRB + NEO_KHZ800);
    chamaAzulPixel = neo;
    acenderLuzPrimordial();
  }
  #endif

  // ── O Despertar do Oráculo ────────────────────────────────
  if (!barometroDesligado) {
    despertarOraculoDaPressao();
  }

  aoDespertarParaOCantoDoEter();
}

// ============================================================
//  A PULSAÇÃO — O Batimento Contínuo do Coração Alado
// ============================================================
inline void GralhaAzul::update() {
  relogioDasEras.instante_do_agora_cosmico = millis();
  // ── O Processamento das Vozes do Éter ────────────────────
  #if GRALHA_TEM_GUARDIAO_DOS_VENTOS
    if (guardiaoDosVentosSiderais) {
      auto* crsf = static_cast<CrsfSerial*>(guardiaoDosVentosSiderais);
      int bytesAvail = VIA_DO_SOPRO_COSMICO.available();
      if (ecosPrescindiveis && bytesAvail > 0) {
        ecosPrescindiveis->print("[PULSACAO] Antes da escuta: ");
        ecosPrescindiveis->print(bytesAvail);
        ecosPrescindiveis->println(" sopros");
      }
      crsf->loop();
      if (ecosPrescindiveis && bytesAvail > 0) {
        int bytesAfter = VIA_DO_SOPRO_COSMICO.available();
        ecosPrescindiveis->print("[PULSACAO] Depois da escuta: ");
        ecosPrescindiveis->print(bytesAfter);
        ecosPrescindiveis->println(" sopros restantes");
        ecosPrescindiveis->print("[ESTADO] Elo=");
        ecosPrescindiveis->print(crsf->isLinkUp());
        ecosPrescindiveis->print(" C1=");
        ecosPrescindiveis->print(crsf->getChannel(1));
        ecosPrescindiveis->print(" C2=");
        ecosPrescindiveis->print(crsf->getChannel(2));
        ecosPrescindiveis->print(" C3=");
        ecosPrescindiveis->print(crsf->getChannel(3));
        ecosPrescindiveis->print(" C4=");
        ecosPrescindiveis->println(crsf->getChannel(4));
      }
    } else if (ecosPrescindiveis) {
      ecosPrescindiveis->println("[PULSACAO] O Guardião dos Ventos Siderais está adormecido!");
    }
  #endif
  #if GRALHA_TEM_MENSAGEIRO_DOS_CANTOS
    if (mensageiroDosVentosCosmicos) {
      static_cast<PPMReader*>(mensageiroDosVentosCosmicos)->loop();
    }
  #endif

  interpretarAsVozesDoFirmamento();

  animarPulsarDoCoracaoAlado();
  escutarPressaoDoCeu();
  sustentarAltura();
  manifestarOVooNosVentos();
  sussurrarVooAoEter();
  irradiarLuzDaAlma();

  // ── O Eco Prescindível — Quando a Gralha Sussurra ao Vento ─
  if (ecosPrescindiveis) {
    if (relogioDasEras.instante_do_agora_cosmico - relogioDasEras.ultimo_eco_prescindivei > INTERVALO_DOS_ECOS_PADRAO) {
      relogioDasEras.ultimo_eco_prescindivei = relogioDasEras.instante_do_agora_cosmico;
      ecosPrescindiveis->print(estadoPresenteDaAlma == EM_DANCA_COM_OS_VENTOS ? "VOANDO" : "SONHANDO");
      ecosPrescindiveis->print(" | Modo: ");
      ecosPrescindiveis->print(modoPresenteDoEspirito == EM_RITMO_DE_BATIDA_DAS_ASAS ? "RITMADO" : "PLANANDO");
      ecosPrescindiveis->print(" | SoproV: "); ecosPrescindiveis->print(vozDoSoproVital);
      ecosPrescindiveis->print(" | Alet: "); ecosPrescindiveis->print(vozDoAletao);
      ecosPrescindiveis->print(" | Prof: "); ecosPrescindiveis->print(vozDoProfundor);
      ecosPrescindiveis->print(" | Leme: "); ecosPrescindiveis->print(vozDoLemeEstelar);
      ecosPrescindiveis->print(" | Despertar: "); ecosPrescindiveis->print(vozDoDespertar);
      ecosPrescindiveis->print(" | FerBater: "); ecosPrescindiveis->print(vozDaFerocidadeDoBater);
      ecosPrescindiveis->print(" | FerRetorno: "); ecosPrescindiveis->print(vozDaFerocidadeDoRetorno);
      ecosPrescindiveis->print(" | FerLeme: "); ecosPrescindiveis->print(vozDaFerocidadeDoLeme);
      ecosPrescindiveis->print(" | GainSust: "); ecosPrescindiveis->print(ganhoDoSustentar, 2);
      ecosPrescindiveis->print(" | CH10Sust: "); ecosPrescindiveis->print(vozDoSustentarAltura);
      if (!barometroDesligado && oraculoRespira) {
        ecosPrescindiveis->print(" | AltVoo: "); ecosPrescindiveis->print(alturaDoVooSideral, 1);
        ecosPrescindiveis->print(" | Subida: "); ecosPrescindiveis->print(soproDaSubidaAlada, 2);
        ecosPrescindiveis->print(" | SoproDoCeu: "); ecosPrescindiveis->print(temperaturaDoArC, 1);
        ecosPrescindiveis->print(" | FeNoSopro: "); ecosPrescindiveis->print(feNoSoproQuente, 2);
        if (modoSustentarAtivo) {
          ecosPrescindiveis->print(" | AltDesej: "); ecosPrescindiveis->print(alturaDesejadaDoVoo, 1);
          ecosPrescindiveis->print(" | SoproSustentar: "); ecosPrescindiveis->print(soproVitalDoSustentar, 0);
          ecosPrescindiveis->print(" | GainEfetivo: "); ecosPrescindiveis->print(ganhoDoSustentar * FORCA_BASE_DO_SUSTENTAR_PADRAO, 1);
        }
      }
      ecosPrescindiveis->print(" | Fase: "); ecosPrescindiveis->print(anguloDaDancaAlada, 2);
      ecosPrescindiveis->print(" | Cadencia: "); ecosPrescindiveis->print(cadenciaDoDestinoAlado, 2);
      ecosPrescindiveis->println();
    }
  }

  // ── O Descanso entre Batidas ──────────────────────────────
  delay(5);
}

// ============================================================
//  A TRANSIÇÃO SUAVE — Quando as Asas Se Preparam para Planar
// ============================================================
inline void GralhaAzul::tecerTransicaoGlide(float alvoEsquerdo, float alvoDireito) {
  // Inicialização: quando entra em glide pela primeira vez ou sai e volta
  if (!emTransicaoParaGlide) {
    emTransicaoParaGlide = true;
    // Captura a posição actual das asas — evita salto brusco no primeiro frame
    int posEsq = tendaoDaAsaMatutina.read();
    int posDir = tendaoDaAsaVespertina.read();
    // Servo.read()=0 before first write on some platforms — clamp to neutral
    if (posEsq == 0 && posDir == 0) {
      anguloGlideEsquerdo = 0;
      anguloGlideDireito = 0;
    } else {
      anguloGlideEsquerdo = posEsq - OFFSET_ANGULAR_NEUTRO_PADRAO;
      anguloGlideDireito = posDir - OFFSET_ANGULAR_NEUTRO_PADRAO;
    }
    microsUltimoPasso = micros();
    return;
  }

  // Clamp glide angles to servo range (±AMPLITUDE_MAXIMA_SERVO_PADRAO)
  alvoEsquerdo = constrain(alvoEsquerdo, -AMPLITUDE_MAXIMA_SERVO_PADRAO, AMPLITUDE_MAXIMA_SERVO_PADRAO);
  alvoDireito  = constrain(alvoDireito,  -AMPLITUDE_MAXIMA_SERVO_PADRAO, AMPLITUDE_MAXIMA_SERVO_PADRAO);

  // Nota: servo 0 = -60° (up position), 180 = +60° (down position)
  // Logo "subir" = mover para menor ângulo = decrescer posicao servo
  float ferocidadeEsquerdo = (anguloGlideEsquerdo > alvoEsquerdo)
    ? mapearEntreEscalasHarmonicas(vozDaFerocidadeDoRetorno, 1000.0f, 2000.0f, FEROCIDADE_MINIMA_PADRAO, FEROCIDADE_MAXIMA_PADRAO)
    : mapearEntreEscalasHarmonicas(vozDaFerocidadeDoBater, 1000.0f, 2000.0f, FEROCIDADE_MINIMA_PADRAO, FEROCIDADE_MAXIMA_PADRAO);
  float ferocidadeDireito = (anguloGlideDireito > alvoDireito)
    ? mapearEntreEscalasHarmonicas(vozDaFerocidadeDoRetorno, 1000.0f, 2000.0f, FEROCIDADE_MINIMA_PADRAO, FEROCIDADE_MAXIMA_PADRAO)
    : mapearEntreEscalasHarmonicas(vozDaFerocidadeDoBater, 1000.0f, 2000.0f, FEROCIDADE_MINIMA_PADRAO, FEROCIDADE_MAXIMA_PADRAO);

  // Glide mínimo: mesmo com CH7/CH8 a 1000, as asas respondem ao stick
  static constexpr float FEROCIDADE_MINIMA_GLIDE = 1.0f;
  ferocidadeEsquerdo = fmax(ferocidadeEsquerdo, FEROCIDADE_MINIMA_GLIDE);
  ferocidadeDireito  = fmax(ferocidadeDireito,  FEROCIDADE_MINIMA_GLIDE);

  // Taxa de movimento = ferocidade * velocidadeAngular * delta_micros
  uint32_t agora = micros();
  uint32_t deltaMicros = agora - microsUltimoPasso;
  if (deltaMicros > 100000) deltaMicros = 100000;  // max 100ms safety
  microsUltimoPasso = agora;

  // Passo máximo permitido para cada asa
  float passoMaxEsquerdo = ferocidadeEsquerdo * velocidadeAngularPorMicros * deltaMicros;
  float passoMaxDireito = ferocidadeDireito * velocidadeAngularPorMicros * deltaMicros;

  // Calcula erros
  float erroEsquerdo = alvoEsquerdo - anguloGlideEsquerdo;
  float erroDireito = alvoDireito - anguloGlideDireito;

  // Move na direção correta, limitado ao passo máximo
  if (fabs(erroEsquerdo) <= passoMaxEsquerdo) {
    anguloGlideEsquerdo = alvoEsquerdo;  // Chegou ao alvo
  } else {
    anguloGlideEsquerdo += (erroEsquerdo > 0) ? passoMaxEsquerdo : -passoMaxEsquerdo;
  }

  if (fabs(erroDireito) <= passoMaxDireito) {
    anguloGlideDireito = alvoDireito;  // Chegou ao alvo
  } else {
    anguloGlideDireito += (erroDireito > 0) ? passoMaxDireito : -passoMaxDireito;
  }

  // Debug: reportar progresso (~2Hz)
  if (ecosPrescindiveis && (agora % 500000 < deltaMicros)) {
    ecosPrescindiveis->print("[GLIDE] Transição: esq=");
    ecosPrescindiveis->print(anguloGlideEsquerdo);
    ecosPrescindiveis->print(" dir=");
    ecosPrescindiveis->print(anguloGlideDireito);
    ecosPrescindiveis->print(" alvos=");
    ecosPrescindiveis->print(alvoEsquerdo);
    ecosPrescindiveis->print("/");
    ecosPrescindiveis->print(alvoDireito);
    ecosPrescindiveis->print(" feroc=");
    ecosPrescindiveis->print(ferocidadeEsquerdo);
    ecosPrescindiveis->print("/");
    ecosPrescindiveis->println(ferocidadeDireito);
  }
}

// ============================================================
//  A HARMONIA DAS ESCALAS — Transmutação de Valores
// ============================================================
inline float GralhaAzul::mapearEntreEscalasHarmonicas(
  float valor, float minOrigem, float maxOrigem,
  float minDestino, float maxDestino
) {
  return (valor - minOrigem) * (maxDestino - minDestino)
       / (maxOrigem - minOrigem) + minDestino;
}

// ============================================================
//  A FORMA DO BATER — A Geometria do Movimento Alado
// ============================================================
inline float GralhaAzul::formaDoBaterDasAsas(float anguloDoCiclo, float ferocidadeDoBater, float ferocidadeDoRetorno, float limiarShared) {
  // ── Modelo Trapezoidal Extremo-a-Extremo com Duração Variável ──
  // Cada meia-onda (descida [0,π) ou subida [π,2π)) tem duração
  // proporcional a (8-f): mais suave = mais longa, mais feroz = mais curta.
  // Dentro de cada meia-onda: dwell d/2 no extremo inicial + rampa cos +
  // dwell d/2 no extremo final. Nos extremos, os dwells de duas meias-ondas
  // adjacentes somam-se, mantendo os planaltos simétricos.
  // O limiar (fronteira descida/subida) é partilhado entre asas — calculado
  // das ferocidades base (sem CH9). Cada asa aplica o seu próprio dwell dentro
  // da mesma janela temporal, mantendo o sincronismo do bater.

  float theta = fmod(anguloDoCiclo, LIMITE_ANGULAR_DO_GIRO_PADRAO);
  if (theta < 0.0f) theta += LIMITE_ANGULAR_DO_GIRO_PADRAO;

  const float pi = 3.14159265358979f;
  const float twoPi = LIMITE_ANGULAR_DO_GIRO_PADRAO;

  float fD = constrain(ferocidadeDoBater,   0.0f, 8.0f);
  float fS = constrain(ferocidadeDoRetorno, 0.0f, 8.0f);

  // Limiar partilhado — ambas as asas mudam de direcção no mesmo θ.
  // Se não for passado (NaN), calcula das ferocidades locais (fallback).
  float limiar;
  if (!isnan(limiarShared)) {
    limiar = limiarShared;
  } else {
    float wD_fb = fmax(8.0f - fD, 0.01f);
    float wS_fb = fmax(8.0f - fS, 0.01f);
    limiar = twoPi * wD_fb / (wD_fb + wS_fb);
  }

  bool descida = (theta < limiar);
  float t, ferocidade, d, dh;
  if (descida) {
    t = theta / limiar;
    ferocidade = fD;
  } else {
    t = (theta - limiar) / (twoPi - limiar);
    ferocidade = fS;
  }
  d = ferocidade * 0.125f;  // f/8, [0,1]
  dh = d * 0.5f;            // d/2 por extremo

  if (d >= 1.0f) return descida ? 1.0f : -1.0f;
  if (t < dh) return descida ? 1.0f : -1.0f;             // dwell extremo inicial
  if (t > 1.0f - dh) return descida ? -1.0f : 1.0f;      // dwell extremo final

  float ramp = cosf(pi * (t - dh) / (1.0f - d));
  return descida ? ramp : -ramp;
}

// ============================================================
//  O PULSAR DO CORAÇÃO — A Dança do Tempo e do Espaço
// ============================================================
inline void GralhaAzul::animarPulsarDoCoracaoAlado() {
  unsigned long agora = relogioDasEras.instante_do_agora_cosmico;
  unsigned long ultima = relogioDasEras.ultima_pulsacao_do_sopro_alado;
  if (ultima == 0) { ultima = agora; }
  float dt = (agora - ultima) * 0.001f;
  if (dt > DT_MAXIMO_DO_SONHO_PADRAO) dt = DT_MAXIMO_DO_SONHO_PADRAO;
  relogioDasEras.ultima_pulsacao_do_sopro_alado = agora;

  // Velocidade angular do servo (comum a ambos os modos)
  // 60° / CICLO segundos = °/s → °/µs para a transição suave do glide
  float velocidadeAngularServo = 60.0f / cicloDoCoracaoAlado;
  velocidadeAngularPorMicros = velocidadeAngularServo / 1e6f;

  if (estadoPresenteDaAlma == EM_DANCA_COM_OS_VENTOS && modoPresenteDoEspirito == EM_RITMO_DE_BATIDA_DAS_ASAS) {

    // A malha de controle — a vontade se torna movimento
    if (_modoAlternativoEfetivo) {
      // Modo alternativo BIRD-LIKE: CH6 → frequência, throttle → % de amplitude permitida
      // Física: A_max = velocidadeAngular / (2 * freq) [graus]
      float bracosDoRelogio = constrain((vozDoCompassoDaAlma - 1000.0f) * 0.001f, 0.0f, 1.0f);
      
      // CH6 1000–2000 → 0.5–f_max Hz. f_max = v_servo/(4·55°) — o servo
      // percorre o arco em 50% do tempo; 50% para pausar nos extremos (águia).
      const float FREQ_MINIMA = 0.5f;
      const float FREQ_MAXIMA = velocidadeAngularServo / (4.0f * AMPLITUDE_MAXIMA_SERVO_PADRAO);
      float freqEfetiva = FREQ_MINIMA + bracosDoRelogio * (FREQ_MAXIMA - FREQ_MINIMA);
      
      amplitudeMaximaPermitida = velocidadeAngularServo / (2.0f * freqEfetiva);
      // Apenas o limite mecânico do servo — sem floor artificial
      if (amplitudeMaximaPermitida > AMPLITUDE_MAXIMA_SERVO_PADRAO)
        amplitudeMaximaPermitida = AMPLITUDE_MAXIMA_SERVO_PADRAO;
      
      cadenciaDoDestinoAlado = freqEfetiva * 6.283185307f;  // 2*PI rad/s para o integrador
    } else {
      // Modo padrão (PI): throttle modula cadência + compasso afecta proporcionalmente
      float intencaoDeCadencia = (vozDoSoproVital - 480.0f) * ((1.0f / (120.0f * cicloDoCoracaoAlado)) +
                                 ((vozDoCompassoDaAlma - 1500.0f) * 0.0000725f));
      float variacaoDoDestinoAlado = 1.0f * intencaoDeCadencia - 10.0f * cadenciaDoDestinoAlado;
      cadenciaDoDestinoAlado += variacaoDoDestinoAlado * dt;
    }
    anguloDaDancaAlada += cadenciaDoDestinoAlado * dt;
    if (fabs(anguloDaDancaAlada) > LIMITE_ANGULAR_DO_GIRO_PADRAO)
      anguloDaDancaAlada = fmod(anguloDaDancaAlada, LIMITE_ANGULAR_DO_GIRO_PADRAO);
  } else {
    if (_modoAlternativoEfetivo) {
      // Modo alternativo: o ângulo continua a avançar com cadência decrescente
      // para manter continuidade de fase ao retomar o bater
      anguloDaDancaAlada += cadenciaDoDestinoAlado * dt;
      if (fabs(anguloDaDancaAlada) > LIMITE_ANGULAR_DO_GIRO_PADRAO)
        anguloDaDancaAlada = fmod(anguloDaDancaAlada, LIMITE_ANGULAR_DO_GIRO_PADRAO);
    } else {
      anguloDaDancaAlada *= DECAIMENTO_DA_CADENCIA_SONOLENTA_PADRAO;
      if (fabs(anguloDaDancaAlada) < EPSILON_CADENCIA_ZERO_PADRAO) anguloDaDancaAlada = 0;
    }
    cadenciaDoDestinoAlado *= DECAIMENTO_DA_CADENCIA_SONOLENTA_PADRAO;
    if (fabs(cadenciaDoDestinoAlado) < EPSILON_CADENCIA_ZERO_PADRAO) cadenciaDoDestinoAlado = 0;
  }
}

// ============================================================
//  O SUSTENTAR — A Arte de Flutuar no Éter
// ============================================================
inline void GralhaAzul::sustentarAltura() {
  if (!barometroDesligado) {
    ganhoDoSustentar = mapearEntreEscalasHarmonicas(
      (float)vozDoSustentarAltura, 1000.0f, 2000.0f,
      0.0f, 1.0f);
    ganhoDoSustentar = constrain(ganhoDoSustentar, 0.0f, 1.0f);
    if (oraculoRespira && ganhoDoSustentar > GANHO_LIMIAR_SUSTENTAR_PADRAO) {
      if (!modoSustentarAtivo) {
        modoSustentarAtivo = true;
        alturaDesejadaDoVoo = alturaDoVooSideral;
        erroFiltradoSustentar = 0.0f;
        soproVitalDoSustentar = (float)vozDoSoproVital;
      }
      float erroBruto = alturaDesejadaDoVoo - alturaDoVooSideral;
      erroFiltradoSustentar += AMORTECIMENTO_DO_ERRO_SUSTENTAR_PADRAO * (erroBruto - erroFiltradoSustentar);
      if (ecosPrescindiveis) ecosPrescindiveis->println("A Gralha sente o chamado do éter!");
      float soproAlvo = 1500.0f + erroFiltradoSustentar * FORCA_BASE_DO_SUSTENTAR_PADRAO * ganhoDoSustentar;
      soproAlvo = constrain(soproAlvo, (float)SOPRO_MIN_DO_SUSTENTAR_PADRAO, (float)SOPRO_MAX_DO_SUSTENTAR_PADRAO);
      float delta = soproAlvo - soproVitalDoSustentar;
      if (delta > TAXA_DE_SUBIDA_PROGRESSIVA_PADRAO) {
        soproVitalDoSustentar += TAXA_DE_SUBIDA_PROGRESSIVA_PADRAO;
      } else if (delta < -TAXA_DE_SUBIDA_PROGRESSIVA_PADRAO) {
        soproVitalDoSustentar -= TAXA_DE_SUBIDA_PROGRESSIVA_PADRAO;
      } else {
        soproVitalDoSustentar = soproAlvo;
      }
      if (soproDaSubidaAlada > LIMITE_DA_SUBIDA_SUSTENTADA_PADRAO) {
        soproVitalDoSustentar -= CORRECAO_DA_TAXA_LIMITE_SUSTENTAR_PADRAO;
      } else if (soproDaSubidaAlada < LIMITE_DA_DESCIDA_SUSTENTADA_PADRAO) {
        soproVitalDoSustentar += (float)CORRECAO_DA_TAXA_LIMITE_SUSTENTAR_PADRAO;
      }
      soproVitalDoSustentar = constrain(soproVitalDoSustentar, (float)SOPRO_MIN_DO_SUSTENTAR_PADRAO, (float)SOPRO_MAX_DO_SUSTENTAR_PADRAO);
    } else {
      modoSustentarAtivo = false;
      soproVitalDoSustentar = (float)vozDoSoproVital;
    }
  } else {
    modoSustentarAtivo = false;
    soproVitalDoSustentar = (float)vozDoSoproVital;
  }
}

// ============================================================
//  A MANIFESTAÇÃO — Quando a Vontade se Torna Voo
// ============================================================
inline void GralhaAzul::manifestarOVooNosVentos() {
  float comandoAletao = (vozDoAletao - 1500.0f) * escalaAngularArticulacao;
  float comandoProfundor = (vozDoProfundor - 1500.0f) * ESCALA_ANGULAR_DO_PROFUNDOR_PADRAO;
  int anguloPortalEsquerdo, anguloPortalDireito;
  float soproEfetivo = modoSustentarAtivo ? soproVitalDoSustentar : (float)vozDoSoproVital;

  if (modoPresenteDoEspirito == EM_RITMO_DE_BATIDA_DAS_ASAS) {
    limiarElevado = false;
    jaCruzouLimiarDeVoo = true;
  }
  int limiarAtual = limiarElevado
    ? (LIMIAR_DO_VOO_ATIVO_PADRAO + 50)
    : LIMIAR_DO_VOO_ATIVO_PADRAO;  // histerese

  if (estadoPresenteDaAlma == EM_DANCA_COM_OS_VENTOS) {
    modoPresenteDoEspirito = (soproEfetivo > limiarAtual)
        ? EM_RITMO_DE_BATIDA_DAS_ASAS
        : EM_DESLIZE_ETERNO_E_CONTEMPLATIVO;
    if (modoPresenteDoEspirito == EM_DESLIZE_ETERNO_E_CONTEMPLATIVO && jaCruzouLimiarDeVoo) {
      limiarElevado = true;
    }
    // ÆtherCodex: modo de voo só comuta em glide (throttle zero)
    if (modoPresenteDoEspirito == EM_DESLIZE_ETERNO_E_CONTEMPLATIVO) {
      _modoAlternativoEfetivo = modoDeVooAlternativo;
    }
  } else {
    modoPresenteDoEspirito = EM_DESLIZE_ETERNO_E_CONTEMPLATIVO;
    limiarElevado = true;
    _modoAlternativoEfetivo = modoDeVooAlternativo;
  }

  float amplitudeDoBater = 0.0f;
  if (modoPresenteDoEspirito == EM_RITMO_DE_BATIDA_DAS_ASAS) {
    // Sai do modo glide: reseta transição suave para futura entrada suave
    emTransicaoParaGlide = false;
    anguloGlideEsquerdo = INFINITY;  // Força recaptura na próxima entrada
    anguloGlideDireito = INFINITY;
    if (_modoAlternativoEfetivo) {
      // Modo alternativo BIRD-LIKE: frequência(CH6) → amplitude_max, throttle → % dessa amplitude
      // CH9 = rudder ferocity (independente)
      // Throttle escala de 0 até amplitudeMaximaPermitida (calculada acima pela física do servo)
      float percentagemSopro = constrain((soproEfetivo - 1000.0f) * 0.001f, 0.0f, 1.0f);  // 1000→2000 → 0→1, usa soproEfetivo (respeita sustentar)
      // Fallback: primeiro frame de flap após armar — amplitudeMaximaPermitida ainda 0
      // porque animarPulsarDoCoracaoAlado() correu em modo glide. Calcula localmente.
      if (amplitudeMaximaPermitida <= 0.0f) {
        float bracos = constrain((vozDoCompassoDaAlma - 1000.0f) * 0.001f, 0.0f, 1.0f);
        const float FR_MIN = 1.0f, FR_MAX = 15.0f;
        float fE = FR_MIN + bracos * (FR_MAX - FR_MIN);
        float vServo = 60.0f / cicloDoCoracaoAlado;
        amplitudeMaximaPermitida = vServo / (2.0f * fE);
        if (amplitudeMaximaPermitida > AMPLITUDE_MAXIMA_SERVO_PADRAO)
          amplitudeMaximaPermitida = AMPLITUDE_MAXIMA_SERVO_PADRAO;
      }
      // Quadrático: início muito suave. 25% throttle → 6%, 50%→25%, 100%→100%
      amplitudeDoBater = percentagemSopro * percentagemSopro * amplitudeMaximaPermitida;
    } else {
      // Modo padrão: throttle modula ambos (cadência + amplitude via compasso)
      amplitudeDoBater = ((soproEfetivo - (float)limiarAtual) * magnitudeDaBatida) * (1.0f - (vozDoCompassoDaAlma - 1500.0f) * MODULACAO_DO_COMPASSO_PADRAO);
    }
    float ferocidadeDoBater = mapearEntreEscalasHarmonicas(vozDaFerocidadeDoBater, 1000.0f, 2000.0f, FEROCIDADE_MINIMA_PADRAO, FEROCIDADE_MAXIMA_PADRAO);
    float ferocidadeDoRetorno = mapearEntreEscalasHarmonicas(vozDaFerocidadeDoRetorno, 1000.0f, 2000.0f, FEROCIDADE_MINIMA_PADRAO, FEROCIDADE_MAXIMA_PADRAO);
    float fatorDoLeme = mapearEntreEscalasHarmonicas(vozDaFerocidadeDoLeme, 1000.0f, 2000.0f, DIFERENCIAL_LEME_MIN_PADRAO, DIFERENCIAL_LEME_MAX_PADRAO);

    // Limiar e ferocidades por asa.
    // CH9 desloca ferocidades no regime trapezoidal (f→0) e desloca o
    // limiar (duty cycle) no regime quadrado (f→8). A transição é contínua:
    // quadFactor = 0 → puro f-shift; 1 → puro limiar-shift.
    const float pi = 3.14159265358979f;
    const float twoPi = LIMITE_ANGULAR_DO_GIRO_PADRAO;
    float fDbase = constrain(ferocidadeDoBater, 0.0f, 8.0f);
    float fSbase = constrain(ferocidadeDoRetorno, 0.0f, 8.0f);
    float wDbase = fmax(8.0f - fDbase, 0.01f);
    float wSbase = fmax(8.0f - fSbase, 0.01f);
    float limiarBase = twoPi * wDbase / (wDbase + wSbase);
    float avgF = (fDbase + fSbase) * 0.5f;
    float quadFactor = constrain((avgF - 6.0f) / 2.0f, 0.0f, 1.0f);  // 0@f≤6 → 1@f=8
    float shift = fatorDoLeme * (pi / 8.0f);

    // Limiar: interpola do base (trapezoidal) para pi±shift (quadrado)
    float limiarEsq = (1.0f - quadFactor) * limiarBase + quadFactor * constrain(pi - shift, 0.05f, twoPi - 0.05f);
    float limiarDir = (1.0f - quadFactor) * limiarBase + quadFactor * constrain(pi + shift, 0.05f, twoPi - 0.05f);

    // Ferocidades: CH9 shift atenua com quadFactor; em quad puro fica 8
    float fBE = constrain(ferocidadeDoBater + fatorDoLeme * (1.0f - quadFactor), FEROCIDADE_MINIMA_PADRAO, 8.0f);
    float fBD = constrain(ferocidadeDoBater - fatorDoLeme * (1.0f - quadFactor), FEROCIDADE_MINIMA_PADRAO, 8.0f);
    float fRE = constrain(ferocidadeDoRetorno + fatorDoLeme * (1.0f - quadFactor), FEROCIDADE_MINIMA_PADRAO, 8.0f);
    float fRD = constrain(ferocidadeDoRetorno - fatorDoLeme * (1.0f - quadFactor), FEROCIDADE_MINIMA_PADRAO, 8.0f);
    float pulsoAsaEsquerda = formaDoBaterDasAsas(anguloDaDancaAlada, fBE, fRE, limiarEsq);
    float pulsoAsaDireita = formaDoBaterDasAsas(anguloDaDancaAlada, fBD, fRD, limiarDir);
    float denominadorLeme = (vozDoLemeEstelar > 0) ? (float)vozDoLemeEstelar : 1500.0f;
    float fatorLemeEstelar = ((1500.0f / denominadorLeme) - 1.0f) * 2.0f + 1.0f;
    float grausAsaEsquerda = amplitudeDoBater * pulsoAsaEsquerda * fatorLemeEstelar;
    float grausAsaDireita  = amplitudeDoBater * pulsoAsaDireita / fatorLemeEstelar;
    anguloPortalEsquerdo = (int)lround((comandoAletao - grausAsaEsquerda + ORIGEM_ASA_MATUTINA_PADRAO - comandoProfundor) * MULTIPLICADOR_FINAL_ANGULAR_PADRAO);
    anguloPortalDireito  = (int)lround((comandoAletao + grausAsaDireita + ORIGEM_ASA_VESPERTINA_PADRAO + comandoProfundor) * MULTIPLICADOR_FINAL_ANGULAR_PADRAO);
  } else {
    // ── Modo Glide com Transição Suave ─────────────────────
    // Alvo em graus (mundo real, antes de converter para servo)
    float alvoEsquerdoGraus = comandoAletao - anguloDoPlanarSereno - comandoProfundor;
    float alvoDireitoGraus = comandoAletao + anguloDoPlanarSereno + comandoProfundor;
    
    // Processa a transição suave
    tecerTransicaoGlide(alvoEsquerdoGraus, alvoDireitoGraus);
    
    // Converte posição suave em graus para posição servo
    anguloPortalEsquerdo = (int)lround((anguloGlideEsquerdo + ORIGEM_ASA_MATUTINA_PADRAO) * MULTIPLICADOR_FINAL_ANGULAR_PADRAO);
    anguloPortalDireito  = (int)lround((anguloGlideDireito + ORIGEM_ASA_VESPERTINA_PADRAO) * MULTIPLICADOR_FINAL_ANGULAR_PADRAO);
  }

  int novoEsquerdo = constrain(anguloPortalEsquerdo + OFFSET_ANGULAR_NEUTRO_PADRAO, 0, 180);
  int novoDireito  = constrain(anguloPortalDireito + OFFSET_ANGULAR_NEUTRO_PADRAO, 0, 180);
  // Filtro EMA sincronizado com cadência de 50Hz.
  // v1.30.15 dessincronizava EMA (200Hz) das escritas (50Hz),
  // causando saltos de 10–52 passos entre writes consecutivos —
  // o servo recebia valores "fantasma" do EMA de há 15ms atrás.
  // Agora: EMA e write correm ambos a 50Hz. O raw é capturado
  // no momento exacto da escrita, eliminando a perseguição atrasada.
  // EMA adaptativo: flap rápido precisa de alpha alto para seguir a onda;
  // glide lento usa alpha baixo para suavidade. cutoff(−3dB) = α/(2π·Ts·(1−α))
  // α=0.30 → fc=3.4Hz (glide); α=0.85 → fc≈30Hz (flap até 43Hz)
  bool emFlap = (modoPresenteDoEspirito == EM_RITMO_DE_BATIDA_DAS_ASAS);
  const float ALPHA_EMA = emFlap ? 0.85f : 0.30f;
  const uint32_t INTERVALO_MIN_US = 20000;  // 20ms = 50Hz
  uint32_t agoraUs = micros();
  bool tickE = (agoraUs - ultimoMicrosEscritaEsquerdo >= INTERVALO_MIN_US);
  bool tickD = (agoraUs - ultimoMicrosEscritaDireito >= INTERVALO_MIN_US);
  bool escreveuE = false;
  bool escreveuD = false;
  int escreveEsq = (int)lround(emaServoEsquerdo);
  int escreveDir = (int)lround(emaServoDireito);
  if (tickE) {
    emaServoEsquerdo = ALPHA_EMA * novoEsquerdo + (1.0f - ALPHA_EMA) * emaServoEsquerdo;
    escreveEsq = (int)lround(emaServoEsquerdo);
    if (escreveEsq != ultimoEscritoEsquerdo) {
      tendaoDaAsaMatutina.write(escreveEsq);
      ultimoEscritoEsquerdo = escreveEsq;
      escreveuE = true;
    }
    ultimoMicrosEscritaEsquerdo = agoraUs;
  }
  if (tickD) {
    emaServoDireito = ALPHA_EMA * novoDireito + (1.0f - ALPHA_EMA) * emaServoDireito;
    escreveDir = (int)lround(emaServoDireito);
    if (escreveDir != ultimoEscritoDireito) {
      tendaoDaAsaVespertina.write(escreveDir);
      ultimoEscritoDireito = escreveDir;
      escreveuD = true;
    }
    ultimoMicrosEscritaDireito = agoraUs;
  }
  // Debug servo: mostra raw, EMA, write status
  if (ecosPrescindiveis) {
    ecosPrescindiveis->print(F("[SERVO] rawE="));
    ecosPrescindiveis->print(novoEsquerdo);
    ecosPrescindiveis->print(F(" emaE="));
    ecosPrescindiveis->print(emaServoEsquerdo, 1);
    ecosPrescindiveis->print(escreveuE ? F("→") : F("✗"));
    ecosPrescindiveis->print(escreveEsq);
    ecosPrescindiveis->print(F(" | rawD="));
    ecosPrescindiveis->print(novoDireito);
    ecosPrescindiveis->print(F(" emaD="));
    ecosPrescindiveis->print(emaServoDireito, 1);
    ecosPrescindiveis->print(escreveuD ? F("→") : F("✗"));
    ecosPrescindiveis->print(escreveDir);
    ecosPrescindiveis->print(F(" | portalE="));
    ecosPrescindiveis->print(anguloPortalEsquerdo);
    ecosPrescindiveis->print(F(" portalD="));
    ecosPrescindiveis->println();
  }
}

// ============================================================
//  O SUSSURRO AO ÉTER — A Voz que Viaja aos Céus
// ============================================================
inline void GralhaAzul::sussurrarVooAoEter() {
  #if GRALHA_TEM_GUARDIAO_DOS_VENTOS
  if (!telemetriaDesligado && guardiaoDosVentosSiderais) {
    unsigned long agora = millis();
    if (agora - ultimo_sopro_sideral >= INTERVALO_DO_GUARDIAO_LUMINAR_PADRAO) {
    }
    if (agora - ultimo_sopro_termico >= INTERVALO_DO_ORACULO_TERMICO_PADRAO) {
    }
  }
  #endif
}

// ============================================================
//  O ORÁCULO DA PRESSÃO — Aquele que Lê o Sopro do Mundo
// ============================================================
inline void GralhaAzul::despertarOraculoDaPressao() {
#if GRALHA_TEM_ORACULO
  Wire.setSDA(SILENCIO_DA_ALTURA_PADRAO);
  Wire.setSCL(RITMO_DA_PRESSAO_PADRAO);
  Wire.begin();
  memset(oraculoBuffer, 0, sizeof(oraculoBuffer));
  Adafruit_BMP085_Unified* bmp = new (oraculoBuffer) Adafruit_BMP085_Unified(10085);
  oraculoDaPressao = bmp;
  if (!bmp->begin()) {
    oraculoRespira = false;
    if (ecosPrescindiveis) ecosPrescindiveis->println("O oráculo da pressão silencia — não ouve o céu.");
    return;
  }
  oraculoRespira = true;
  if (ecosPrescindiveis) ecosPrescindiveis->println("O oráculo da pressão desperta — escuta a altura invisível.");

  float somaAltura = 0.0f;
  int leiturasValidas = 0;
  for (int i = 0; i < AMOSTRAS_DE_CALIBRACAO_PADRAO; i++) {
    sensors_event_t evento;
    bmp->getEvent(&evento);
    if (evento.pressure > 0) {
      float temperatura;
      bmp->getTemperature(&temperatura);
      float altitude = bmp->pressureToAltitude(REFERENCIA_DA_PRESSAO_PADRAO, evento.pressure, temperatura);
      somaAltura += altitude;
      leiturasValidas++;
    }
    delay(ATRASO_DE_CALIBRACAO_PADRAO);
  }
  if (leiturasValidas > 0) {
    alturaInicialM = somaAltura / (float)leiturasValidas;
  }
  if (ecosPrescindiveis) {
    ecosPrescindiveis->print("A Gralha sente o chamado do éter! (zero: ");
    ecosPrescindiveis->print(alturaInicialM, 1);
    ecosPrescindiveis->println("m)");
  }
  alturaDoVooSideral = 0.0f;
  ultimaAlturaDoVooSideral = 0.0f;
  ultimoSoproDoOraculo = millis();
  ultimaTemperaturaDoArC = 0.0f;
#endif
}

inline void GralhaAzul::escutarPressaoDoCeu() {
#if GRALHA_TEM_ORACULO
  if (!oraculoRespira || !oraculoDaPressao) return;
  auto* bmp = (Adafruit_BMP085_Unified*)oraculoDaPressao;
  unsigned long agora = millis();
  if (agora - ultimoSoproDoOraculo < INTERVALO_DE_LEITURA_PADRAO) return;
  float dt = (agora - ultimoSoproDoOraculo) * 0.001f;
  if (dt < MINIMO_DT_SEGUNDOS_PADRAO) dt = MINIMO_DT_SEGUNDOS_PADRAO;
  ultimoSoproDoOraculo = agora;
  sensors_event_t evento;
  bmp->getEvent(&evento);
  if (evento.pressure <= 0) return;
  pressaoDoCeuHpa = evento.pressure;
  static uint8_t cicloTermico = 0;
  if (++cicloTermico >= SALTOS_DO_CICLO_TERMICO_PADRAO) {
    cicloTermico = 0;
    float novaTemp;
    bmp->getTemperature(&novaTemp);
    temperaturaDoArC = temperaturaDoArC * SUAVIZACAO_TERMICA_PADRAO + novaTemp * SUAVIZACAO_TERMICA_PADRAO;
  }
  tendenciaDaTemperaturaC = tendenciaDaTemperaturaC * FILTRO_DE_TENDENCIA_PADRAO + (temperaturaDoArC - ultimaTemperaturaDoArC) * PESO_DA_TENDENCIA_PADRAO;
  ultimaTemperaturaDoArC = temperaturaDoArC;
  float razao = pressaoDoCeuHpa / REFERENCIA_DA_PRESSAO_PADRAO;
  float fator = 1.0f - powf(razao, EXPONENTE_DA_FORMULA_PADRAO);
  float altitudeAbsoluta = fator * CONSTANTE_DA_FORMULA_PADRAO;
  alturaDoVooSideral = altitudeAbsoluta - alturaInicialM;
  subidaDaGralhaMs = (alturaDoVooSideral - ultimaAlturaDoVooSideral) / dt;
  ultimaAlturaDoVooSideral = alturaDoVooSideral;
  soproDaSubidaAlada = soproDaSubidaAlada * PESO_DA_SUBIDA_ATUAL_PADRAO + subidaDaGralhaMs * PESO_DA_SUBIDA_PASSADA_PADRAO;
  feNoSoproQuente = soproDaSubidaAlada + tendenciaDaTemperaturaC * PESO_DA_CONFIANCA_TERMICA_PADRAO;
  if (feNoSoproQuente > LIMIAR_DE_CONFIANCA_PADRAO) modoDeEscutaTermal = true;
  else if (feNoSoproQuente < -LIMIAR_DE_CONFIANCA_PADRAO) modoDeEscutaTermal = false;
#endif
}

// ============================================================
//  OS EVENTOS — Quando o Destino Toca a Gralha
// ============================================================
inline void GralhaAzul::aoDespertarParaOCantoDoEter() {
  modoPresenteDoEspirito = EM_DESLIZE_ETERNO_E_CONTEMPLATIVO;
  limiarElevado = false;
  jaCruzouLimiarDeVoo = false;
  guardiaoInicializado = false;
  // Reset limpo — sem memória de voo anterior
  anguloDaDancaAlada = 0;
  cadenciaDoDestinoAlado = 0;
  amplitudeMaximaPermitida = 0.0f;
  // Reset do glide — força recaptura da posição actual das asas
  emTransicaoParaGlide = false;
  anguloGlideEsquerdo = INFINITY;
  anguloGlideDireito = INFINITY;
  if (ecosPrescindiveis) {
    ecosPrescindiveis->println("[PRESAGIO] O Elo Cósmico se formou — o Firmamento canta!");
    ecosPrescindiveis->print("[PRESAGIO] Sopros no vento após o elo: ");
    ecosPrescindiveis->println(VIA_DO_SOPRO_COSMICO.available());
  }
}

inline void GralhaAzul::aoRecolherSeAoSilencioDaMata() {
  modoPresenteDoEspirito = EM_DESLIZE_ETERNO_E_CONTEMPLATIVO;
  limiarElevado = false;
  guardiaoInicializado = false; // re-inicializar o Guardião quando o elo voltar
  for (int i = 0; i < 10; i++) { guardiaoPersistencia[i] = 0; }
  if (ecosPrescindiveis) ecosPrescindiveis->println("[PRESAGIO] O Elo Cósmico se rompeu — a Gralha só ouve o silêncio da mata.");
}

inline void GralhaAzul::interpretarAsVozesDoFirmamento() {
  #if GRALHA_TEM_GUARDIAO_DOS_VENTOS
  if (guardiaoDosVentosSiderais) {
    auto* crsf = static_cast<CrsfSerial*>(guardiaoDosVentosSiderais);
    if (!crsf->isLinkUp()) return;
    if (ecosPrescindiveis) {
      ecosPrescindiveis->println("[CANTO] A Gralha interpreta as vozes do Firmamento...");
      ecosPrescindiveis->print("[CANTO] Voz1="); ecosPrescindiveis->print(crsf->getChannel(1));
      ecosPrescindiveis->print(" Voz2="); ecosPrescindiveis->print(crsf->getChannel(2));
      ecosPrescindiveis->print(" Voz3="); ecosPrescindiveis->print(crsf->getChannel(3));
      ecosPrescindiveis->print(" Voz4="); ecosPrescindiveis->println(crsf->getChannel(4));
    }
    int cru1 = crsf->getChannel(1);
    int cru2 = crsf->getChannel(2);
    int cru3 = crsf->getChannel(3);
    int cru4 = crsf->getChannel(4);
    int cru5 = crsf->getChannel(5);
    int cru6 = crsf->getChannel(6);
    int cru7 = crsf->getChannel(7);
    int cru8 = crsf->getChannel(8);
    int cru9 = crsf->getChannel(9);
    int cru10 = crsf->getChannel(10);

    // Guardião contra Fantasmas: rejeição por canal, não por frame.
    // Cada canal tem o seu próprio delta máximo. Se um canal excede,
    // só esse canal congela — os outros 9 continuam a actualizar.
    // O primeiro frame após link-up inicializa as referências sem verificação.
    if (!guardiaoInicializado) {
      guardiaoInicializado = true;
      guardiaoVoz1 = cru1; guardiaoVoz2 = cru2; guardiaoVoz3 = cru3;
      guardiaoVoz4 = cru4; guardiaoVoz5 = cru5; guardiaoVoz6 = cru6;
      guardiaoVoz7 = cru7; guardiaoVoz8 = cru8; guardiaoVoz9 = cru9;
      guardiaoVoz10 = cru10;
      for (int i = 0; i < 10; i++) { guardiaoPersistencia[i] = 0; }
      vozDoAletao = cru1; vozDoProfundor = cru2; vozDoSoproVital = cru3;
      vozDoLemeEstelar = cru4; vozDoDespertar = cru5; vozDoCompassoDaAlma = cru6;
      vozDaFerocidadeDoBater = cru7; vozDaFerocidadeDoRetorno = cru8;
      vozDaFerocidadeDoLeme = cru9; vozDoSustentarAltura = cru10;
      if (ecosPrescindiveis) {
        ecosPrescindiveis->println(F("[GUARDIAO] Inicializado com o primeiro sopro dos ventos."));
      }
      // Sem return — o primeiro frame também voa.
    }

    // ── Detecção de simultaneidade ──────────────────────────
    // Fantasmas eléctricos corrompem muitos canais ao mesmo tempo.
    // Sticks reais: no máximo 3 eixos mudam simultaneamente.
    // Se ≥4 canais excedem delta no mesmo frame → fantasma colectivo.
    static constexpr int LIMIAR_SIMULTANEIDADE_DO_GUARDIAO = 4;

    // Primeira passagem: contar canais anómalos
    int canaisAnomalos = 0;
    int deltaCanal[10];
    int deltas[10];
    deltas[0] = abs(cru1 - guardiaoVoz1);
    deltas[1] = abs(cru2 - guardiaoVoz2);
    deltas[2] = abs(cru3 - guardiaoVoz3);
    deltas[3] = abs(cru4 - guardiaoVoz4);
    deltas[4] = abs(cru5 - guardiaoVoz5);
    deltas[5] = abs(cru6 - guardiaoVoz6);
    deltas[6] = abs(cru7 - guardiaoVoz7);
    deltas[7] = abs(cru8 - guardiaoVoz8);
    deltas[8] = abs(cru9 - guardiaoVoz9);
    deltas[9] = abs(cru10 - guardiaoVoz10);

    int deltaMaxCanal[10] = {
      DELTA_MAXIMO_DO_GUARDIAO, DELTA_MAXIMO_DO_GUARDIAO,
      DELTA_MAXIMO_DO_GUARDIAO, DELTA_MAXIMO_DO_GUARDIAO,
      DELTA_MAXIMO_DO_GUARDIAO_ARM, DELTA_MAXIMO_DO_GUARDIAO,
      DELTA_MAXIMO_DO_GUARDIAO, DELTA_MAXIMO_DO_GUARDIAO,
      DELTA_MAXIMO_DO_GUARDIAO, DELTA_MAXIMO_DO_GUARDIAO
    };

    for (int i = 0; i < 10; i++) {
      if (deltas[i] > deltaMaxCanal[i]) canaisAnomalos++;
    }

    bool assombrado = false;

    if (canaisAnomalos >= LIMIAR_SIMULTANEIDADE_DO_GUARDIAO) {
      // ── Fantasma colectivo: rejeitar frame inteiro ──────
      assombrado = true;
      for (int i = 0; i < 10; i++) { guardiaoPersistencia[i] = 0; }
      if (ecosPrescindiveis) {
        ecosPrescindiveis->print(F("[GUARDIAO] 👻 Fantasma colectivo: "));
        ecosPrescindiveis->print(canaisAnomalos);
        ecosPrescindiveis->println(F(" canais anómalos → frame rejeitado"));
      }
    } else {
      // ── Persistência por canal (1-3 canais) ─────────────
      auto verificarCanal = [&](int cru, int& guardiao, int& voz, int deltaMax,
                                 int canal, const char* nome) {
        int idx = canal - 1;
        int delta = abs(cru - guardiao);

        if (delta <= deltaMax) {
          voz = cru;
          guardiao = cru;
          guardiaoPersistencia[idx] = 0;
        } else if (guardiaoPersistencia[idx] == 0) {
          guardiaoCandidato[idx] = cru;
          guardiaoPersistencia[idx] = 1;
          assombrado = true;
          if (ecosPrescindiveis) {
            ecosPrescindiveis->print(F("[GUARDIAO] CH")); ecosPrescindiveis->print(canal);
            ecosPrescindiveis->print(F(" ")); ecosPrescindiveis->print(nome);
            ecosPrescindiveis->print(F(": ")); ecosPrescindiveis->print(guardiao);
            ecosPrescindiveis->print(F("→")); ecosPrescindiveis->print(cru);
            ecosPrescindiveis->print(F(" (Δ")); ecosPrescindiveis->print(delta);
            ecosPrescindiveis->println(F(") aguarda confirmacao"));
          }
        } else if (abs(cru - guardiaoCandidato[idx]) <= DELTA_PERSISTENCIA_DO_GUARDIAO) {
          voz = cru;
          guardiao = cru;
          guardiaoPersistencia[idx] = 0;
          if (ecosPrescindiveis) {
            ecosPrescindiveis->print(F("[GUARDIAO] CH")); ecosPrescindiveis->print(canal);
            ecosPrescindiveis->print(F(" ")); ecosPrescindiveis->print(nome);
            ecosPrescindiveis->print(F(": ")); ecosPrescindiveis->print(cru);
            ecosPrescindiveis->println(F(" confirmado (stick legitimo)"));
          }
        } else {
          guardiaoCandidato[idx] = cru;
          guardiaoPersistencia[idx] = 1;
          assombrado = true;
          if (ecosPrescindiveis) {
            ecosPrescindiveis->print(F("[GUARDIAO] CH")); ecosPrescindiveis->print(canal);
            ecosPrescindiveis->print(F(" ")); ecosPrescindiveis->print(nome);
            ecosPrescindiveis->print(F(": ")); ecosPrescindiveis->print(cru);
            ecosPrescindiveis->println(F(" inconsistente, novo candidato"));
          }
        }
      };

      verificarCanal(cru1, guardiaoVoz1, vozDoAletao, DELTA_MAXIMO_DO_GUARDIAO, 1, "Aletao");
      verificarCanal(cru2, guardiaoVoz2, vozDoProfundor, DELTA_MAXIMO_DO_GUARDIAO, 2, "Profundor");
      verificarCanal(cru3, guardiaoVoz3, vozDoSoproVital, DELTA_MAXIMO_DO_GUARDIAO, 3, "Sopro");
      verificarCanal(cru4, guardiaoVoz4, vozDoLemeEstelar, DELTA_MAXIMO_DO_GUARDIAO, 4, "Leme");
      verificarCanal(cru5, guardiaoVoz5, vozDoDespertar, DELTA_MAXIMO_DO_GUARDIAO_ARM, 5, "Arm");
      verificarCanal(cru6, guardiaoVoz6, vozDoCompassoDaAlma, DELTA_MAXIMO_DO_GUARDIAO, 6, "Compasso");
      verificarCanal(cru7, guardiaoVoz7, vozDaFerocidadeDoBater, DELTA_MAXIMO_DO_GUARDIAO, 7, "FeroBater");
      verificarCanal(cru8, guardiaoVoz8, vozDaFerocidadeDoRetorno, DELTA_MAXIMO_DO_GUARDIAO, 8, "FeroRetorno");
      verificarCanal(cru9, guardiaoVoz9, vozDaFerocidadeDoLeme, DELTA_MAXIMO_DO_GUARDIAO, 9, "FeroLeme");
      verificarCanal(cru10, guardiaoVoz10, vozDoSustentarAltura, DELTA_MAXIMO_DO_GUARDIAO, 10, "Sustentar");
    }

    if (assombrado && ecosPrescindiveis) {
      ecosPrescindiveis->println(F("[GUARDIAO] Frame parcialmente retido (canais assombrados congelados)."));
    }
    if (ecosPrescindiveis) {
      ecosPrescindiveis->print(F("VOANDO | Arm:"));
      ecosPrescindiveis->print(estadoPresenteDaAlma == EM_DANCA_COM_OS_VENTOS ? F("SIM") : F("NAO"));
      ecosPrescindiveis->print(F(" | Modo:"));
      ecosPrescindiveis->print(modoPresenteDoEspirito == EM_RITMO_DE_BATIDA_DAS_ASAS ? F("FLAP") : F("GLIDE"));
      ecosPrescindiveis->print(F(" | SoproV:")); ecosPrescindiveis->print(vozDoSoproVital);
      ecosPrescindiveis->print(F(" | FerB:")); ecosPrescindiveis->print(vozDaFerocidadeDoBater);
      ecosPrescindiveis->print(F(" | FerR:")); ecosPrescindiveis->print(vozDaFerocidadeDoRetorno);
      ecosPrescindiveis->print(F(" | Batida:")); ecosPrescindiveis->print(anguloDaDancaAlada, 2);
      ecosPrescindiveis->println();
    }
  }
  #endif
  #if GRALHA_TEM_MENSAGEIRO_DOS_CANTOS
  if (mensageiroDosVentosCosmicos) {
    auto* ppm = static_cast<PPMReader*>(mensageiroDosVentosCosmicos);
    vozDoAletao = ppm->getChannel(1);
    vozDoProfundor = ppm->getChannel(2);
    vozDoSoproVital = ppm->getChannel(3);
    vozDoLemeEstelar = ppm->getChannel(4);
    vozDoDespertar = ppm->getChannel(5);
    vozDaFerocidadeDoLeme = ppm->getChannel(9);
    vozDaFerocidadeDoBater = ppm->getChannel(7);
    vozDaFerocidadeDoRetorno = ppm->getChannel(8);
    vozDoCompassoDaAlma = ppm->getChannel(6);
    vozDoSustentarAltura = ppm->getChannel(10);
    if (ecosPrescindiveis) {
      ecosPrescindiveis->print(F("PLANANDO | Modo: "));
      ecosPrescindiveis->print(estadoPresenteDaAlma == EM_DANCA_COM_OS_VENTOS ? F("RITMADO") : F("SONOLENTO"));
      ecosPrescindiveis->print(F(" | SoproV:")); ecosPrescindiveis->print(vozDoSoproVital);
      ecosPrescindiveis->print(F(" AltVoo:")); ecosPrescindiveis->print(soproVitalDoSustentar, 1);
      ecosPrescindiveis->print(F(" Batida:")); ecosPrescindiveis->print(anguloDaDancaAlada, 2);
      ecosPrescindiveis->println();
    }
  }
  #endif
  estadoPresenteDaAlma = (vozDoDespertar > 1500)
    ? EM_DANCA_COM_OS_VENTOS
    : EM_SONHO_NA_QUIETUDE_DA_FLORESTA;
}

// ============================================================
//  A CHAMA AZUL — A Alma Luminosa que Pulsa na Escuridão
// ============================================================
inline void GralhaAzul::acenderLuzPrimordial() {
  #if GRALHA_TEM_CHAMA_AZUL
  if (!chamaAzulPixel) return;
  auto* neo = static_cast<Adafruit_NeoPixel*>(chamaAzulPixel);
  neo->begin();
  neo->setBrightness(70);
  neo->show();
  #endif
}

inline void GralhaAzul::irradiarLuzDaAlma() {
  #if GRALHA_TEM_CHAMA_AZUL
  if (!chamaAzulPixel) return;
  auto* neo = static_cast<Adafruit_NeoPixel*>(chamaAzulPixel);
  unsigned long agora = millis();
  if (agora - ultimoInstanteRespiracaoLuminescente >= 25) {
    ultimoInstanteRespiracaoLuminescente = agora;
    pulsacaoDaChamaPrimordial += 0.04f;
    if (pulsacaoDaChamaPrimordial > 1.0f) pulsacaoDaChamaPrimordial = 0.0f;
  }
  float respiro = sin(pulsacaoDaChamaPrimordial * 2.0f * PI) * 0.5f + 0.5f;
  float posicaoDasAsasNoCiclo = (cos(anguloDaDancaAlada) + 1.0f) * 0.5f;
  float eixoDoProfundorCeleste = mapearEntreEscalasHarmonicas(vozDoProfundor, 1000.0f, 2000.0f, -1.0f, 1.0f);
  float eixoDoSoproDeVida = mapearEntreEscalasHarmonicas(vozDoSoproVital, 1000.0f, 2000.0f, 0.0f, 1.0f);
  float eixoDoCompassoAnimico = mapearEntreEscalasHarmonicas(vozDoCompassoDaAlma, 1000.0f, 2000.0f, -1.0f, 1.0f);
  bool despertou = (vozDoDespertar > 1500);
  byte r=0, g=0, b=0;
  byte rAlerta=0, gAlerta=0, bAlerta=0;

  if (estadoPresenteDaAlma == EM_DANCA_COM_OS_VENTOS) {
    if (modoPresenteDoEspirito == EM_RITMO_DE_BATIDA_DAS_ASAS) {
      b = (150 + 105 * (1.0f - eixoDoCompassoAnimico * 0.5f)) * eixoDoSoproDeVida;
      g = (80 + 70 * (1.0f + eixoDoProfundorCeleste * 0.5f)) * eixoDoSoproDeVida;
      r = (30 + 20 * (1.0f + eixoDoCompassoAnimico * 0.3f)) * eixoDoSoproDeVida;
      float moduladorDeBrilho = posicaoDasAsasNoCiclo * 0.8f + 0.2f;
      r *= moduladorDeBrilho; g *= moduladorDeBrilho; b *= moduladorDeBrilho;
    } else {
      b = 180 * (1.0f - eixoDoProfundorCeleste * 0.2f);
      g = 90 * (1.0f + eixoDoProfundorCeleste * 0.3f);
      r = 10;
    }
    if (!despertou) {
      rAlerta = 200; gAlerta = 20; bAlerta = 20;
      float peso = respiro * 0.6f;
      r = r * (1.0f - peso) + rAlerta * peso;
      g = g * (1.0f - peso) + gAlerta * peso;
      b = b * (1.0f - peso) + bAlerta * peso;
    }
  } else {
    tonalidadeDoSonhoFlorestal = (tonalidadeDoSonhoFlorestal + 250) % 65536;
    uint16_t matizBase = (sin(tonalidadeDoSonhoFlorestal * 0.0001f) > 0) ? 20000 : 42000;
    uint32_t corSonho = neo->gamma32(neo->ColorHSV(
        matizBase + (int)(sin(millis()*0.0003f)*1800.0f), 210, 90));
    if (!despertou) {
      rAlerta = 200; gAlerta = 20; bAlerta = 20;
      byte rSonho = (corSonho >> 16) & 0xFF;
      byte gSonho = (corSonho >> 8) & 0xFF;
      byte bSonho = corSonho & 0xFF;
      float peso = respiro * 0.5f;
      r = rSonho * (1.0f - peso) + rAlerta * peso;
      g = gSonho * (1.0f - peso) + gAlerta * peso;
      b = bSonho * (1.0f - peso) + bAlerta * peso;
      neo->setPixelColor(0, constrain(r,0,255), constrain(g,0,255), constrain(b,0,255));
      neo->show();
      return;
    }
    float peso = respiro * 0.6f;
    uint32_t corMesclada = neo->gamma32(neo->ColorHSV(
        matizBase + (int)(sin(millis()*0.0003f)*1800.0f), 210, 90 * (1.0f - peso) + 180 * peso));
    neo->setPixelColor(0, corMesclada);
    neo->show();
    return;
  }
  neo->setPixelColor(0, constrain(r,0,255), constrain(g,0,255), constrain(b,0,255));
  neo->show();
  #endif
}
#endif /* GRALHA_AZUL_H */