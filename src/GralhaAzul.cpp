/*
  O Grande Código da Gralha Azul
  v1.23.0 — A Essência Pura: O Código como Encantamento
  
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

#include <new>
#include "GralhaAzul.h"

GralhaAzul* GralhaAzul::instanciaGralhaParaEventos = nullptr;

/* As Invocações de Bibliotecas — os rituais de poder */
#if __has_include(<Adafruit_NeoPixel.h>)
  #include <Adafruit_NeoPixel.h>
#endif
#if __has_include(<Adafruit_BMP085_U.h>)
  #include <Adafruit_Sensor.h>
  #include <Adafruit_BMP085_U.h>
#endif

// ============================================================
//  O DESPERTAR — Quando a Gralha Abre os Olhos
// ============================================================
void GralhaAzul::begin() {
  #ifdef ECOS_PRESCINDIVEIS_DA_ALMA_ALADA
  ecosPrescindiveis->println("O Grande Código da Gralha Azul: A Lenda Viva se Inicia...");
  #endif
  
  // ── A Configuração das Articulações ───────────────────────
  #ifdef ARTICULACAO_DA_ASA_MATUTINA
  articulacaoAsaDaManha = ARTICULACAO_DA_ASA_MATUTINA;
  #endif
  #ifdef ARTICULACAO_DA_ASA_VESPERTINA
  articulacaoAsaDoEntardecer = ARTICULACAO_DA_ASA_VESPERTINA;
  #endif

  // ── O Ciclo do Coração Alado ──────────────────────────────
  #ifdef CICLO_DO_CORACAO_ALADO
  cicloDoCoracaoAlado = CICLO_DO_CORACAO_ALADO;
  #endif

  // ── As Faculdades que Dormem ──────────────────────────────
  #ifdef BAROMETRO_DESLIGADO
  barometroDesligado = true;
  #endif
  #ifdef TELEMETRIA_DESLIGADO
  telemetriaDesligado = true;
  #endif
  #ifdef NEOPIXEL_DESLIGADO
  neopixelDesligado = true;
  #endif
  
  // ── O Despertar dos Guardiões ────────────────────────────
  #ifdef RECEPTOR_CRSF
  #ifndef CRSF_SERIAL
    #define CRSF_SERIAL SOPRO_SERIAL_PADRAO
  #endif
  CRSF_SERIAL.setTX(viaDosEcosSolares);
  CRSF_SERIAL.setRX(viaDosSonhosLunares);
  CRSF_SERIAL.begin(FREQUENCIA_DO_SOPRO_COSMICO_PADRAO);
  memset(guardiaoBuffer, 0, sizeof(guardiaoBuffer));
  guardiaoDosVentosSiderais = new (guardiaoBuffer) CrsfSerial(CRSF_SERIAL, FREQUENCIA_DO_SOPRO_COSMICO_PADRAO);
  guardiaoDosVentosSiderais->begin();
  instanciaGralhaParaEventos = this;
  guardiaoDosVentosSiderais->onLinkUp = &GralhaAzul::eventoLinkUp;
  guardiaoDosVentosSiderais->onLinkDown = &GralhaAzul::eventoLinkDown;
  guardiaoDosVentosSiderais->onPacketChannels = &GralhaAzul::eventoPacketChannels;
  guardiaoDosVentosSiderais->setPassthroughMode(false);
  #endif
  
  // ── O Portal dos Cantos Cósmicos ─────────────────────────
  #ifdef PORTAL_DOS_CANTOS_COSMICOS
  mensageiroDosVentosCosmicos = new PPMReader(PORTAL_DOS_CANTOS_COSMICOS, NUMERO_DE_CANTOS);
  mensageiroDosVentosCosmicos->begin();
  #endif

  tendaoDaAsaMatutina.attach(articulacaoAsaDaManha, PULSO_MINIMO_SERVO_PADRAO, PULSO_MAXIMO_SERVO_PADRAO);
  tendaoDaAsaVespertina.attach(articulacaoAsaDoEntardecer, PULSO_MINIMO_SERVO_PADRAO, PULSO_MAXIMO_SERVO_PADRAO);
  // Posicionar as asas em neutro ao iniciar
  tendaoDaAsaMatutina.write(OFFSET_ANGULAR_NEUTRO_PADRAO);
  tendaoDaAsaVespertina.write(OFFSET_ANGULAR_NEUTRO_PADRAO);

  // ── O Acender da Chama Azul ───────────────────────────────
  #if __has_include(<Adafruit_NeoPixel.h>)
  if (!neopixelDesligado) {
    memset(chamaAzulBuffer, 0, sizeof(chamaAzulBuffer));
    chamaAzulPixel = new (chamaAzulBuffer) Adafruit_NeoPixel(QUANTIDADE_DE_CENTELHAS_PADRAO, NUCLEO_DA_CHAMA_AZUL_PADRAO, NEO_GRB + NEO_KHZ800);
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
void GralhaAzul::update() {
  relogioDasEras.instante_do_agora_cosmico = millis();

  #ifdef RECEPTOR_CRSF
  if (guardiaoDosVentosSiderais) {
    guardiaoDosVentosSiderais->loop();
  }
  #endif
  #ifdef RECEPTOR_PPM
  if (mensageiroDosVentosCosmicos) {
    mensageiroDosVentosCosmicos->loop();
  }
  #endif
  interpretarAsVozesDoFirmamento();

  animarPulsarDoCoracaoAlado();
  escutarPressaoDoCeu();
  sustentarAltura();
  manifestarOVooNosVentos();
  sussurrarVooAoEter();

  // ── O Fulgor da Chama Azul ────────────────────────────────
  if (!neopixelDesligado && chamaAzulPixel) {
    #if __has_include(<Adafruit_NeoPixel.h>)
    if (relogioDasEras.instante_do_agora_cosmico - relogioDasEras.ultimo_fulgor_da_chama_azul >= INTERVALO_DA_CHAMA_AZUL_PADRAO) {
      relogioDasEras.ultimo_fulgor_da_chama_azul = relogioDasEras.instante_do_agora_cosmico;
      irradiarLuzDaAlma();
    }
    #endif
  }

  #ifdef ECOS_PRESCINDIVEIS_DA_ALMA_ALADA
  if (relogioDasEras.instante_do_agora_cosmico - relogioDasEras.ultimo_eco_prescindivei > INTERVALO_DOS_ECOS_PADRAO) {
    relogioDasEras.ultimo_eco_prescindivei = relogioDasEras.instante_do_agora_cosmico;
    ecosPrescindiveis->print(estadoPresenteDaAlma == EM_DANCA_COM_OS_VENTOS ? "VOANDO" : "SONHANDO");
    ecosPrescindiveis->print(" | Modo: ");
    ecosPrescindiveis->print(modoPresenteDoEspirito == EM_RITMO_DE_BATIDA_DAS_ASAS ? "RITMADO" : "PLANANDO");
    ecosPrescindiveis->print(" | SoproV: "); ecosPrescindiveis->print(vozDoSoproVital);
    ecosPrescindiveis->print(" | Alet: "); ecosPrescindiveis->print(vozDoAlerao);
    ecosPrescindiveis->print(" | Prof: "); ecosPrescindiveis->print(vozDoProfundor);
      ecosPrescindiveis->print(" | Leme: "); ecosPrescindiveis->print(vozDoLemeEstelar);
      ecosPrescindiveis->print(" | Despertar: "); ecosPrescindiveis->print(vozDoDespertar);
      ecosPrescindiveis->print(" | FerBater: "); ecosPrescindiveis->print(vozDaFerocidadeDoBater);
      ecosPrescindiveis->print(" | FerRetorno: "); ecosPrescindiveis->print(vozDaFerocidadeDoRetorno);
      ecosPrescindiveis->print(" | FerLeme: "); ecosPrescindiveis->print(vozDaFerocidadeDoLeme);
      ecosPrescindiveis->print(" | SustentarGain: "); ecosPrescindiveis->print(ganhoDoSustentar, 2);
      ecosPrescindiveis->print(" | SustentarCH10: "); ecosPrescindiveis->print(vozDoSustentarAltura);
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
  #endif

  // ── O Descanso entre Batidas ──────────────────────────────
  delay(5);
}

// ============================================================
//  A HARMONIA DAS ESCALAS — Transmutação de Valores
// ============================================================
float GralhaAzul::mapearEntreEscalasHarmonicas(
  float valor, float minOrigem, float maxOrigem,
  float minDestino, float maxDestino
) {
  return (valor - minOrigem) * (maxDestino - minDestino)
       / (maxOrigem - minOrigem) + minDestino;
}

// ============================================================
//  A FORMA DO BATER — A Geometria do Movimento Alado
// ============================================================
float GralhaAzul::formaDoBaterDasAsas(float cantoDoVento, float ferocidadeDoBater, float ferocidadeDoRetorno) {
  float ferocidade = (cantoDoVento >= 0.0f) ? ferocidadeDoBater : ferocidadeDoRetorno;
  float equilibrioDoCeu = tanh(ferocidade);
  if (equilibrioDoCeu < EPSILON_FORMA_BATER_PADRAO) {
    return cantoDoVento;
  }
  float resultado = tanh(ferocidade * cantoDoVento) / equilibrioDoCeu;
  if (resultado > LIMITE_FORMA_BATER_PADRAO) resultado = LIMITE_FORMA_BATER_PADRAO;
  if (resultado < -LIMITE_FORMA_BATER_PADRAO) resultado = -LIMITE_FORMA_BATER_PADRAO;
  return resultado;
}

// ============================================================
//  O PULSAR DO CORAÇÃO — A Dança do Tempo e do Espaço
// ============================================================
void GralhaAzul::animarPulsarDoCoracaoAlado() {
  unsigned long agora = relogioDasEras.instante_do_agora_cosmico;
  unsigned long ultima = relogioDasEras.ultima_pulsacao_do_sopro_alado;
  if (ultima == 0) { ultima = agora; }
  float dt = (agora - ultima) * 0.001f;
  if (dt > DT_MAXIMO_DO_SONHO_PADRAO) dt = DT_MAXIMO_DO_SONHO_PADRAO;
  relogioDasEras.ultima_pulsacao_do_sopro_alado = agora;

  if (estadoPresenteDaAlma == EM_DANCA_COM_OS_VENTOS) {
    // A malha de controle — a vontade se torna movimento
    float intencaoDeCadencia = (vozDoSoproVital - 480.0f) * ((1.0f / (120.0f * cicloDoCoracaoAlado)) +
                               ((vozDoCompassoDaAlma - 1500.0f) * 0.0000725f));
    float variacaoDoDestinoAlado = 1.0f * intencaoDeCadencia - 10.0f * cadenciaDoDestinoAlado;
    cadenciaDoDestinoAlado += variacaoDoDestinoAlado * dt;
    anguloDaDancaAlada += cadenciaDoDestinoAlado * dt;
  } else {
    anguloDaDancaAlada = 0;
    cadenciaDoDestinoAlado *= DECAIMENTO_DA_CADENCIA_SONOLENTA_PADRAO;
    if (fabs(cadenciaDoDestinoAlado) < EPSILON_CADENCIA_ZERO_PADRAO) cadenciaDoDestinoAlado = 0;
  }
}

// ============================================================
//  O SUSTENTAR — A Arte de Flutuar no Éter
// ============================================================
void GralhaAzul::sustentarAltura() {
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
      #ifdef ECOS_PRESCINDIVEIS_DA_ALMA_ALADA
      ecosPrescindiveis->println("A Gralha sente o chamado do éter!");
      #endif
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
void GralhaAzul::manifestarOVooNosVentos() {
  float comandoAlerao = (vozDoAlerao - 1500.0f) * escalaAngularArticulacao;
  float comandoProfundor = (vozDoProfundor - 1500.0f) * ESCALA_ANGULAR_DO_PROFUNDOR_PADRAO;
  int anguloPortalEsquerdo, anguloPortalDireito;
  float soproEfetivo = modoSustentarAtivo ? soproVitalDoSustentar : (float)vozDoSoproVital;

  if (modoPresenteDoEspirito == EM_RITMO_DE_BATIDA_DAS_ASAS) {
    limiarElevado = true;
  }
  int limiarAtual = limiarElevado
    ? LIMIAR_DO_VOO_ATIVO_PADRAO
    : (LIMIAR_DO_VOO_ATIVO_PADRAO - 50);  // histerese

  if (estadoPresenteDaAlma == EM_DANCA_COM_OS_VENTOS) {
    modoPresenteDoEspirito = (soproEfetivo > limiarAtual)
        ? EM_RITMO_DE_BATIDA_DAS_ASAS
        : EM_DESLIZE_ETERNO_E_CONTEMPLATIVO;
    if (modoPresenteDoEspirito == EM_DESLIZE_ETERNO_E_CONTEMPLATIVO) {
      limiarElevado = false;
    }
  } else {
    modoPresenteDoEspirito = EM_DESLIZE_ETERNO_E_CONTEMPLATIVO;
    limiarElevado = false;
  }

  if (modoPresenteDoEspirito == EM_RITMO_DE_BATIDA_DAS_ASAS) {
    float magnitudeDaBatida = ((soproEfetivo - LIMIAR_DO_VOO_ATIVO_PADRAO) * MAGNITUDE_ESCALA_DA_FEROCIDADE_PADRAO) * (1.0f - (vozDoCompassoDaAlma - 1500.0f) * MODULACAO_DO_COMPASSO_PADRAO);
    float cantoOriginalDaAsa = sin(anguloDaDancaAlada);
    float ferocidadeDoBater = mapearEntreEscalasHarmonicas(vozDaFerocidadeDoBater, 1000.0f, 2000.0f, FEROCIDADE_MINIMA_PADRAO, FEROCIDADE_MAXIMA_PADRAO);
    float ferocidadeDoRetorno = mapearEntreEscalasHarmonicas(vozDaFerocidadeDoRetorno, 1000.0f, 2000.0f, FEROCIDADE_MINIMA_PADRAO, FEROCIDADE_MAXIMA_PADRAO);
    float fatorDoLeme = mapearEntreEscalasHarmonicas(vozDaFerocidadeDoLeme, 1000.0f, 2000.0f, DIFERENCIAL_LEME_MIN_PADRAO, DIFERENCIAL_LEME_MAX_PADRAO);
    float ferocidadeBaterEsquerda = ferocidadeDoBater + fatorDoLeme;
    float ferocidadeBaterDireita  = ferocidadeDoBater - fatorDoLeme;
    float ferocidadeRetornoEsquerda = ferocidadeDoRetorno + fatorDoLeme;
    float ferocidadeRetornoDireita  = ferocidadeDoRetorno - fatorDoLeme;
    float pulsoAsaEsquerda = formaDoBaterDasAsas(cantoOriginalDaAsa, ferocidadeBaterEsquerda, ferocidadeRetornoEsquerda);
    float pulsoAsaDireita = formaDoBaterDasAsas(cantoOriginalDaAsa, ferocidadeBaterDireita, ferocidadeRetornoDireita);
    float fatorLemeEstelar = ((1500.0f / (float)vozDoLemeEstelar) - 1.0f) * 2.0f + 1.0f;
    float grausAsaEsquerda = magnitudeDaBatida * pulsoAsaEsquerda * fatorLemeEstelar;
    float grausAsaDireita  = magnitudeDaBatida * pulsoAsaDireita / fatorLemeEstelar;
    anguloPortalEsquerdo = (int)((comandoAlerao - grausAsaEsquerda + ORIGEM_ASA_MATUTINA_PADRAO - comandoProfundor) * MULTIPLICADOR_FINAL_ANGULAR_PADRAO);
    anguloPortalDireito  = (int)((comandoAlerao + grausAsaDireita + ORIGEM_ASA_VESPERTINA_PADRAO + comandoProfundor) * MULTIPLICADOR_FINAL_ANGULAR_PADRAO);
  } else {
    anguloPortalEsquerdo = (int)((comandoAlerao - ANGULO_DO_PLANAR_SERENO_PADRAO + ORIGEM_ASA_MATUTINA_PADRAO - comandoProfundor) * MULTIPLICADOR_FINAL_ANGULAR_PADRAO);
    anguloPortalDireito  = (int)((comandoAlerao + ANGULO_DO_PLANAR_SERENO_PADRAO + ORIGEM_ASA_VESPERTINA_PADRAO + comandoProfundor) * MULTIPLICADOR_FINAL_ANGULAR_PADRAO);
  }

  tendaoDaAsaMatutina.write(constrain(anguloPortalEsquerdo + OFFSET_ANGULAR_NEUTRO_PADRAO, 0, 180));
  tendaoDaAsaVespertina.write(constrain(anguloPortalDireito + OFFSET_ANGULAR_NEUTRO_PADRAO, 0, 180));
}

// ============================================================
//  O SUSSURRO AO ÉTER — A Voz que Viaja aos Céus
// ============================================================
void GralhaAzul::sussurrarVooAoEter() {
  #ifdef RECEPTOR_CRSF
  if (!telemetriaDesligado && guardiaoDosVentosSiderais) {
    unsigned long agora = millis();
    if (agora - ultimo_sopro_sideral >= INTERVALO_DO_GUARDIAO_LUMINAR_PADRAO) {
      // Sopro do Guardião Luminar
    }
    if (agora - ultimo_sopro_termico >= INTERVALO_DO_ORACULO_TERMICO_PADRAO) {
      // Sopro do Oráculo Térmico
    }
  }
  #endif
}

// ============================================================
//  O ORÁCULO DA PRESSÃO — Aquele que Lê o Sopro do Mundo
// ============================================================
void GralhaAzul::despertarOraculoDaPressao() {
  #if __has_include(<Adafruit_BMP085_U.h>)
  Wire.setSDA(SILENCIO_DA_ALTURA_PADRAO);
  Wire.setSCL(RITMO_DA_PRESSAO_PADRAO);
  Wire.begin();
  oraculoDaPressao = (void*)new Adafruit_BMP085_Unified(10085);
  auto* bmp = (Adafruit_BMP085_Unified*)oraculoDaPressao;
  if (!bmp->begin()) {
    oraculoRespira = false;
    #ifdef ECOS_PRESCINDIVEIS_DA_ALMA_ALADA
    ecosPrescindiveis->println("O oráculo da pressão silencia — não ouve o céu.");
    #endif
    return;
  }
  oraculoRespira = true;
  #ifdef ECOS_PRESCINDIVEIS_DA_ALMA_ALADA
  ecosPrescindiveis->println("O oráculo da pressão desperta — escuta a altura invisível.");
  #endif
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
  #ifdef ECOS_PRESCINDIVEIS_DA_ALMA_ALADA
  ecosPrescindiveis->println("A Gralha sente o chamado do éter!");
  #endif
  ultimaAlturaDoVooSideral = 0.0f;
  ultimoSoproDoOraculo = millis();
  ultimaTemperaturaDoArC = 0.0f;
  #endif
}

void GralhaAzul::escutarPressaoDoCeu() {
  #if __has_include(<Adafruit_BMP085_U.h>)
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
void GralhaAzul::aoDespertarParaOCantoDoEter() {
  #ifdef ECOS_PRESCINDIVEIS_DA_ALMA_ALADA
  ecosPrescindiveis->println("A Gralha sente o chamado do éter!");
  #endif
}

void GralhaAzul::aoRecolherSeAoSilencioDaMata() {
  estadoPresenteDaAlma = EM_SONHO_NA_QUIETUDE_DA_FLORESTA;
  modoPresenteDoEspirito = EM_DESLIZE_ETERNO_E_CONTEMPLATIVO;
  limiarElevado = false;
  #ifdef ECOS_PRESCINDIVEIS_DA_ALMA_ALADA
  ecosPrescindiveis->println("A Gralha sente o chamado do éter!");
  #endif
}

void GralhaAzul::interpretarAsVozesDoFirmamento() {
  #ifdef RECEPTOR_CRSF
  if (guardiaoDosVentosSiderais) {
    vozDoAlerao = guardiaoDosVentosSiderais->getChannel(1);
    vozDoProfundor = guardiaoDosVentosSiderais->getChannel(2);
    vozDoSoproVital = guardiaoDosVentosSiderais->getChannel(3);
    vozDoLemeEstelar = guardiaoDosVentosSiderais->getChannel(4);
    vozDoDespertar = guardiaoDosVentosSiderais->getChannel(5);
    vozDaFerocidadeDoLeme = guardiaoDosVentosSiderais->getChannel(6);
    vozDaFerocidadeDoBater = guardiaoDosVentosSiderais->getChannel(7);
    vozDaFerocidadeDoRetorno = guardiaoDosVentosSiderais->getChannel(8);
    vozDoCompassoDaAlma = guardiaoDosVentosSiderais->getChannel(9);
    vozDoSustentarAltura = guardiaoDosVentosSiderais->getChannel(10);
  }
  #endif
  #ifdef RECEPTOR_PPM
  if (mensageiroDosVentosCosmicos) {
    vozDoAlerao = mensageiroDosVentosCosmicos->getChannel(1);
    vozDoProfundor = mensageiroDosVentosCosmicos->getChannel(2);
    vozDoSoproVital = mensageiroDosVentosCosmicos->getChannel(3);
    vozDoLemeEstelar = mensageiroDosVentosCosmicos->getChannel(4);
    vozDoDespertar = mensageiroDosVentosCosmicos->getChannel(5);
    vozDaFerocidadeDoLeme = mensageiroDosVentosCosmicos->getChannel(6);
    vozDaFerocidadeDoBater = mensageiroDosVentosCosmicos->getChannel(7);
    vozDaFerocidadeDoRetorno = mensageiroDosVentosCosmicos->getChannel(8);
    vozDoCompassoDaAlma = mensageiroDosVentosCosmicos->getChannel(9);
    vozDoSustentarAltura = mensageiroDosVentosCosmicos->getChannel(10);
  }
  #endif
  estadoPresenteDaAlma = (vozDoDespertar > 1500)
    ? EM_DANCA_COM_OS_VENTOS
    : EM_SONHO_NA_QUIETUDE_DA_FLORESTA;
}

// ============================================================
//  A CHAMA AZUL — A Alma Luminosa que Pulsa na Escuridão
// ============================================================
void GralhaAzul::acenderLuzPrimordial() {
  #if __has_include(<Adafruit_NeoPixel.h>)
  if (!chamaAzulPixel) return;
  auto* neo = chamaAzulPixel;
  neo->begin();
  neo->setBrightness(70);
  neo->show();
  #endif
}

void GralhaAzul::irradiarLuzDaAlma() {
  #if __has_include(<Adafruit_NeoPixel.h>)
  if (!chamaAzulPixel) return;
  auto* neo = chamaAzulPixel;
  unsigned long agora = millis();
  if (agora - ultimoInstanteRespiracaoLuminescente >= 25) {
    ultimoInstanteRespiracaoLuminescente = agora;
    pulsacaoDaChamaPrimordial += 0.04f;
    if (pulsacaoDaChamaPrimordial > 1.0f) pulsacaoDaChamaPrimordial = 0.0f;
  }
  float respiro = sin(pulsacaoDaChamaPrimordial * 2.0f * PI) * 0.5f + 0.5f;
  float posicaoDasAsasNoCiclo = (sin(anguloDaDancaAlada) + 1.0f) * 0.5f;
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