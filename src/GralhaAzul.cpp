/*
  O Grande Código da Gralha Azul
  A Inscrição Primordial da Lenda Alada
  — Implementação do Coração Alado Partilhado entre Modelos —

  Nas eras antigas, quando o aroma dos pinheirais sagrados pairava como prece,
  e a araucária, árvore da vida, guardava em seu cerne o pinhão – a semente estelar –
  um corvo de plumagem como a noite profunda residia em seu galho ancestral.
  Mas o eco frio do aço quebrou a harmonia – a floresta, seu santuário, em perigo.
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

#include "GralhaAzul.h"

/* As Relíquias da Gralha — Onde a memória do voo se guarda entre ciclos. */
#if defined(RECEPTOR_DOS_VENTOS_CRSF)
// O Guardião dos Ventos Siderais, intérprete dos desígnios para a Gralha.
CrsfSerial guardiao_dos_ventos_siderais(PORTAL_DOS_VENTOS_CELESTES);
#elif defined(RECEPTOR_DOS_VENTOS_PPM)
// O Mensageiro dos Ventos Cósmicos, que lê os pulsos do éter.
PPMReader mensageiro_dos_ventos_cosmicos(PINO_DO_MENSAGEIRO, NUM_CANAIS_DO_MENSAGEIRO);
#endif

// O éter que leva as novas da Gralha ao mundo: instantes do último sopro ao firmamento.
unsigned long ultimo_sopro_sideral = 0;
unsigned long ultimo_sopro_termico = 0;

/* As Relíquias da Gralha: Vínculos de Poder e Essência
  Os pontos de contato com o mundo, ecos da sua jornada.
*/
bool limiar_elevado = true;
bool oraculo_respira = false; // O oráculo da pressão escuta a altura invisível.

/* Os Estados da Alma Alada: Fases da Consciência da Gralha
  O 'despertar' concede à Gralha o sopro da vida; o 'sonho' é seu repouso sagrado,
  mas o voo só se inicia quando o espírito alado a comanda.
*/
EstadoDaAlmaAlada estado_presente_da_alma = EM_SONHO_NA_QUIETUDE_DA_FLORESTA;
ModoDoEspiritoAlado modo_presente_do_espirito = EM_DESLIZE_ETERNO_E_CONTEMPLATIVO;

int voz_do_sustentar_altura = 0;

/* O Relógio das Eras: Marcadores Temporais da Jornada da Gralha */
RelogioDasEras relogio_das_eras = {0};

/* As Vozes do Céu: Inspirações que Moldam o Destino da Gralha */
int voz_do_aletao = VIBRACAO_NEUTRA_DO_ALETAO;
int voz_do_profundor = VIBRACAO_NEUTRA_DO_PROFUNDOR;
int voz_do_sopro_vital = VIBRACAO_MINIMA_DO_SOPRO_VITAL;
int voz_do_leme_estelar = VIBRACAO_NEUTRA_DO_LEME_ESTELAR;
int voz_do_despertar = 0;
int voz_do_compasso_da_alma = VIBRACAO_NEUTRA_DO_COMPASSO_DA_ALMA;
int voz_da_ferocidade_do_bater = VIBRACAO_MINIMA_DA_FEROCIDADE;
int voz_da_ferocidade_do_retorno = VIBRACAO_MINIMA_DA_FEROCIDADE;
int voz_da_ferocidade_do_leme = VIBRACAO_MINIMA_DA_FEROCIDADE;

// O oráculo da pressão escuta a altura invisível.
#ifndef GRALHA_AZUL_BAROMETRO_DESLIGADO
Adafruit_BMP085_Unified oraculo_da_pressao = Adafruit_BMP085_Unified(10085);
#endif
float pressao_do_ceu_hpa = 0.0f;
float temperatura_do_ar_c = 0.0f;
float altura_do_voo_sideral = 0.0f;
float altura_inicial_m = 0.0f;
float subida_da_gralha_ms = 0.0f;
float sopro_da_subida_alada = 0.0f;
float ultima_altura_do_voo_sideral = 0.0f;
unsigned long ultimo_sopro_do_oraculo = 0;
float tendencia_da_temperatura_c = 0.0f;
float ultima_temperatura_do_ar_c = 0.0f;
bool modo_de_escuta_termal = false;
float fe_no_sopro_quente = 0.0f;
float ganho_do_sustentar = 0.0f;
float altura_desejada_do_voo = 0.0f;
float sopro_vital_do_sustentar = 1500.0f;
bool modo_sustentar_ativo = false;
float pulsacao_da_chama_primordial = 0.0f;

/* A Geometria Sagrada do Voo */
float angulo_da_danca_alada = 0;
float cadencia_do_destino_alado = 0;
float pulso_do_sopro_vital = 0.0;

#ifndef GRALHA_AZUL_NEOPIXEL_DESLIGADO
MantoDeLuzCelestial manto_celestial_da_gralha;
#endif
Servo tendao_da_asa_matutina, tendao_da_asa_vespertina;

/* A Alquimia dos Números — Rituais que transformam vibrações em movimento. */
// Ritual de Mapeamento Harmônico: Converte vibrações entre escalas.
float mapear_entre_escalas_harmonicas(float valor, float minimo_origem, float max_origem, float minimo_destino, float max_destino) {
  return (valor - minimo_origem) * (max_destino - minimo_destino) / (max_origem - minimo_origem) + minimo_destino;
}

float forma_do_bater_das_asas(float canto_do_vento, float direcao_do_bater, float ferocidade_do_bater, float ferocidade_do_retorno) {
  float ferocidade = (direcao_do_bater >= 0.0f) ? ferocidade_do_bater : ferocidade_do_retorno;
  float equilibrio_do_ceu = tanh(ferocidade);
  if (equilibrio_do_ceu < EPSILON_FORMA_BATER) {
    return canto_do_vento;
  }
  float resultado = tanh(ferocidade * canto_do_vento) / equilibrio_do_ceu;
  if (resultado > LIMITE_FORMA_BATER) resultado = LIMITE_FORMA_BATER;
  if (resultado < -LIMITE_FORMA_BATER) resultado = -LIMITE_FORMA_BATER;
  return resultado;
}

/* O Manto de Luz — A chama azul que pulsa com o coração da Gralha. */
#ifndef GRALHA_AZUL_NEOPIXEL_DESLIGADO
void MantoDeLuzCelestial::AcenderLuzPrimordial() {
  chama_azul_pixel.begin();
  chama_azul_pixel.setBrightness(70);
  chama_azul_pixel.show();
}

void MantoDeLuzCelestial::IrradiarLuzDaAlma() {
  unsigned long agora = millis();
  if (agora - ultimo_instante_de_respiracao_luminescente >= 25) {
    ultimo_instante_de_respiracao_luminescente = agora;
    pulsacao_da_chama_primordial += 0.04f;
    if (pulsacao_da_chama_primordial > 1.0f) pulsacao_da_chama_primordial = 0.0f;
  }
  float respiro = sin(pulsacao_da_chama_primordial * 2.0f * PI) * 0.5f + 0.5f;
  float posicao_das_asas_no_ciclo = (sin(angulo_da_danca_alada) + 1.0f) * 0.5f;
  float eixo_do_profundor_celeste = mapear_entre_escalas_harmonicas(voz_do_profundor, 1000.0f, 2000.0f, -1.0f, 1.0f);
  float eixo_do_sopro_de_vida = mapear_entre_escalas_harmonicas(voz_do_sopro_vital, 1000.0f, 2000.0f, 0.0f, 1.0f);
  float eixo_do_compasso_animico = mapear_entre_escalas_harmonicas(voz_do_compasso_da_alma, 1000.0f, 2000.0f, -1.0f, 1.0f);
  bool despertou = (voz_do_despertar > 1500);
  byte r=0, g=0, b=0;
  byte r_alerta=0, g_alerta=0, b_alerta=0;

  if (estado_presente_da_alma == EM_DANCA_COM_OS_VENTOS) {
    if (modo_presente_do_espirito == EM_RITMO_DE_BATIDA_DAS_ASAS) {
      b = (150 + 105 * (1.0f - eixo_do_compasso_animico * 0.5f)) * eixo_do_sopro_de_vida;
      g = (80 + 70 * (1.0f + eixo_do_profundor_celeste * 0.5f)) * eixo_do_sopro_de_vida;
      r = (30 + 20 * (1.0f + eixo_do_compasso_animico * 0.3f)) * eixo_do_sopro_de_vida;
      float modulador_de_brilho = posicao_das_asas_no_ciclo * 0.8f + 0.2f;
      r *= modulador_de_brilho; g *= modulador_de_brilho; b *= modulador_de_brilho;
    } else {
      b = 180 * (1.0f - eixo_do_profundor_celeste * 0.2f);
      g = 90 * (1.0f + eixo_do_profundor_celeste * 0.3f);
      r = 10;
    }
    if (!despertou) {
      r_alerta = 200; g_alerta = 20; b_alerta = 20;
      float peso = respiro * 0.6f;
      r = r * (1.0f - peso) + r_alerta * peso;
      g = g * (1.0f - peso) + g_alerta * peso;
      b = b * (1.0f - peso) + b_alerta * peso;
    }
  } else {
    tonalidade_do_sonho_florestal = (tonalidade_do_sonho_florestal + 250) % 65536;
    uint16_t matiz_base = (sin(tonalidade_do_sonho_florestal * 0.0001f) > 0) ? 20000 : 42000;
    uint32_t cor_sonho = chama_azul_pixel.gamma32(chama_azul_pixel.ColorHSV(
        matiz_base + (int)(sin(millis()*0.0003f)*1800.0f), 210, 90));
    if (!despertou) {
      r_alerta = 200; g_alerta = 20; b_alerta = 20;
      byte r_sonho = (cor_sonho >> 16) & 0xFF;
      byte g_sonho = (cor_sonho >> 8) & 0xFF;
      byte b_sonho = cor_sonho & 0xFF;
      float peso = respiro * 0.5f;
      r = r_sonho * (1.0f - peso) + r_alerta * peso;
      g = g_sonho * (1.0f - peso) + g_alerta * peso;
      b = b_sonho * (1.0f - peso) + b_alerta * peso;
      chama_azul_pixel.setPixelColor(0, constrain(r,0,255), constrain(g,0,255), constrain(b,0,255));
      chama_azul_pixel.show();
      return;
    }
    float peso = respiro * 0.6f;
    uint32_t cor_mesclada = chama_azul_pixel.gamma32(chama_azul_pixel.ColorHSV(
        matiz_base + (int)(sin(millis()*0.0003f)*1800.0f), 210, 90 * (1.0f - peso) + 180 * peso));
    chama_azul_pixel.setPixelColor(0, cor_mesclada);
    chama_azul_pixel.show();
    return;
  }
  chama_azul_pixel.setPixelColor(0, constrain(r,0,255), constrain(g,0,255), constrain(b,0,255));
  chama_azul_pixel.show();
}
#endif

/* Os Rituais de Escuta — A Gralha sintoniza seus oráculos para sentir o mundo. */
#ifndef GRALHA_AZUL_BAROMETRO_DESLIGADO
void DespertarOraculoDaPressao() {
  Wire.setSDA(PINO_SILENCIO_DA_ALTURA);
  Wire.setSCL(PINO_RITMO_DA_PRESSAO);
  Wire.begin();
  if (!oraculo_da_pressao.begin()) {
    oraculo_respira = false;
#ifdef ECOS_PRESCINDIVEIS_DA_ALMA_ALADA
    Serial.println("O oráculo da pressão silencia — não ouve o céu.");
#endif
    return;
  }
  oraculo_respira = true;
#ifdef ECOS_PRESCINDIVEIS_DA_ALMA_ALADA
  Serial.println("O oráculo da pressão desperta — escuta a altura invisível.");
#endif
  float soma_altura = 0.0f;
  int leituras_validas = 0;
  for (int i = 0; i < AMOSTRAS_CALIBRACAO_BAROMETRO; i++) {
    sensors_event_t evento;
    oraculo_da_pressao.getEvent(&evento);
    if (evento.pressure > 0) {
      float temperatura;
      oraculo_da_pressao.getTemperature(&temperatura);
      float altitude = oraculo_da_pressao.pressureToAltitude(REFERENCIA_DA_PRESSAO_HPA, evento.pressure, temperatura);
      soma_altura += altitude;
      leituras_validas++;
    }
    delay(ATRASO_CALIBRACAO_BAROMETRO_MS);
  }
  if (leituras_validas > 0) {
    altura_inicial_m = soma_altura / leituras_validas;
  }
  ultima_altura_do_voo_sideral = 0.0f;
  ultimo_sopro_do_oraculo = millis();
  ultima_temperatura_do_ar_c = 0.0f;
}

void EscutarPressaoDoCeu() {
  if (!oraculo_respira) return;
  unsigned long agora = millis();
  if (agora - ultimo_sopro_do_oraculo < INTERVALO_LEITURA_BAROMETRO_MS) return;
  float dt = (agora - ultimo_sopro_do_oraculo) * 0.001f;
  if (dt < MINIMO_DT_SEGUNDOS) dt = MINIMO_DT_SEGUNDOS;
  ultimo_sopro_do_oraculo = agora;
  sensors_event_t evento;
  oraculo_da_pressao.getEvent(&evento);
  if (evento.pressure <= 0) return;
  pressao_do_ceu_hpa = evento.pressure;
  static uint8_t ciclo_termico = 0;
  if (++ciclo_termico >= SALTOS_CICLO_TEMPERATURA) {
    ciclo_termico = 0;
    float nova_temp;
    oraculo_da_pressao.getTemperature(&nova_temp);
    temperatura_do_ar_c = temperatura_do_ar_c * SUAVIZACAO_TEMPERATURA + nova_temp * SUAVIZACAO_TEMPERATURA;
  }
  tendencia_da_temperatura_c = tendencia_da_temperatura_c * FILTRO_TENDENCIA_TEMPERATURA + (temperatura_do_ar_c - ultima_temperatura_do_ar_c) * PESO_TENDENCIA_TEMPERATURA;
  ultima_temperatura_do_ar_c = temperatura_do_ar_c;
  float razao = pressao_do_ceu_hpa / REFERENCIA_DA_PRESSAO_HPA;
  float fator = 1.0f - powf(razao, EXPONENTE_FORMULA_BAROMETRICA);
  float altitude_absoluta = fator * CONSTANTE_FORMULA_BAROMETRICA;
  altura_do_voo_sideral = altitude_absoluta - altura_inicial_m;
  subida_da_gralha_ms = (altura_do_voo_sideral - ultima_altura_do_voo_sideral) / dt;
  ultima_altura_do_voo_sideral = altura_do_voo_sideral;
  sopro_da_subida_alada = sopro_da_subida_alada * PESO_VELOCIDADE_VERTICAL_ATUAL + subida_da_gralha_ms * PESO_VELOCIDADE_VERTICAL_ANTERIOR;
  fe_no_sopro_quente = sopro_da_subida_alada + tendencia_da_temperatura_c * PESO_CONFIANCA_TERMICA_TEMPERATURA;
  if (fe_no_sopro_quente > LIMIAR_CONFIANCA_TERMICA) modo_de_escuta_termal = true;
  else if (fe_no_sopro_quente < -LIMIAR_CONFIANCA_TERMICA) modo_de_escuta_termal = false;
}
#endif

void AoDespertarParaOCantoDoEter() {
#ifdef ECOS_PRESCINDIVEIS_DA_ALMA_ALADA
  Serial.println("A Gralha sente o chamado do éter!");
#endif
}

void AoRecolherSeAoSilencioDaMata() {
  estado_presente_da_alma = EM_SONHO_NA_QUIETUDE_DA_FLORESTA;
  modo_presente_do_espirito = EM_DESLIZE_ETERNO_E_CONTEMPLATIVO;
  limiar_elevado = false;
#ifdef ECOS_PRESCINDIVEIS_DA_ALMA_ALADA
  Serial.println("O éter silencia. A Gralha retorna ao seu sonho na floresta.");
#endif
}

#if defined(RECEPTOR_DOS_VENTOS_CRSF)
void InterpretarAsVozesDoFirmamento() {
  estado_presente_da_alma = (voz_do_despertar > 1500)
    ? EM_DANCA_COM_OS_VENTOS
    : EM_SONHO_NA_QUIETUDE_DA_FLORESTA;
  voz_do_aletao = guardiao_dos_ventos_siderais.getChannel(1);
  voz_do_profundor = guardiao_dos_ventos_siderais.getChannel(2);
  voz_do_sopro_vital = guardiao_dos_ventos_siderais.getChannel(3);
  voz_do_leme_estelar = guardiao_dos_ventos_siderais.getChannel(4);
  voz_do_despertar = guardiao_dos_ventos_siderais.getChannel(5);
  voz_do_compasso_da_alma = guardiao_dos_ventos_siderais.getChannel(6);
  voz_da_ferocidade_do_bater = guardiao_dos_ventos_siderais.getChannel(7);
  voz_da_ferocidade_do_retorno = guardiao_dos_ventos_siderais.getChannel(8);
  voz_da_ferocidade_do_leme = guardiao_dos_ventos_siderais.getChannel(9);
  voz_do_sustentar_altura = guardiao_dos_ventos_siderais.getChannel(10);
}
#elif defined(RECEPTOR_DOS_VENTOS_PPM)
void InterpretarAsVozesDoFirmamento(const unsigned long* channelValues, byte numChannels) {
  (void)channelValues;
  (void)numChannels;
  voz_do_aletao = mensageiro_dos_ventos_cosmicos.latestValidChannelValue(1, VIBRACAO_NEUTRA_DO_ALETAO);
  voz_do_profundor = mensageiro_dos_ventos_cosmicos.latestValidChannelValue(2, VIBRACAO_NEUTRA_DO_PROFUNDOR);
  voz_do_sopro_vital = mensageiro_dos_ventos_cosmicos.latestValidChannelValue(3, VIBRACAO_MINIMA_DO_SOPRO_VITAL);
  voz_do_leme_estelar = mensageiro_dos_ventos_cosmicos.latestValidChannelValue(4, VIBRACAO_NEUTRA_DO_LEME_ESTELAR);
  voz_do_despertar = mensageiro_dos_ventos_cosmicos.latestValidChannelValue(5, VIBRACAO_DO_DESPERTAR_DESARMADO);
  voz_do_compasso_da_alma = mensageiro_dos_ventos_cosmicos.latestValidChannelValue(6, VIBRACAO_NEUTRA_DO_COMPASSO_DA_ALMA);
  voz_da_ferocidade_do_bater = mensageiro_dos_ventos_cosmicos.latestValidChannelValue(7, VIBRACAO_MINIMA_DA_FEROCIDADE);
  voz_da_ferocidade_do_retorno = mensageiro_dos_ventos_cosmicos.latestValidChannelValue(8, VIBRACAO_MINIMA_DA_FEROCIDADE);
  voz_da_ferocidade_do_leme = mensageiro_dos_ventos_cosmicos.latestValidChannelValue(9, VIBRACAO_MINIMA_DA_FEROCIDADE);
  voz_do_sustentar_altura = mensageiro_dos_ventos_cosmicos.latestValidChannelValue(10, VIBRACAO_MINIMA_DO_SUSTENTAR_ALTURA);
  estado_presente_da_alma = (voz_do_despertar > 1500)
    ? EM_DANCA_COM_OS_VENTOS
    : EM_SONHO_NA_QUIETUDE_DA_FLORESTA;
}
#endif

/* O Acordar da Lenda — gralhaAzulSetup()
   Quando a Gralha desperta, cada tendão se estica, cada oráculo escuta. */
void gralhaAzulSetup() {
#ifndef GRALHA_AZUL_NEOPIXEL_DESLIGADO
  manto_celestial_da_gralha.AcenderLuzPrimordial();
#endif
  DespertarOraculoDaPressao();
  AoDespertarParaOCantoDoEter();

#ifdef ECOS_PRESCINDIVEIS_DA_ALMA_ALADA
  Serial.begin(BAUDRATE_SERIAL);
  unsigned long tempo_de_espera_usb = millis();
  while (!Serial && (millis() - tempo_de_espera_usb < TEMPO_ESPERA_USB_MS)) {  }
  Serial.println("O Grande Código da Gralha Azul: A Lenda Viva se Inicia...");
#endif

#if defined(RECEPTOR_DOS_VENTOS_CRSF)
  PORTAL_DOS_VENTOS_CELESTES.setTX(VIA_DOS_ECOS_SOLARES);
  PORTAL_DOS_VENTOS_CELESTES.setRX(VIA_DOS_SONHOS_LUNARES);
  PORTAL_DOS_VENTOS_CELESTES.begin(FREQUENCIA_DO_SOPRO_COSMICO);
  while(PORTAL_DOS_VENTOS_CELESTES.available()) { PORTAL_DOS_VENTOS_CELESTES.read(); }
  guardiao_dos_ventos_siderais.onLinkUp = &AoDespertarParaOCantoDoEter;
  guardiao_dos_ventos_siderais.onLinkDown = &AoRecolherSeAoSilencioDaMata;
  guardiao_dos_ventos_siderais.onPacketChannels = &InterpretarAsVozesDoFirmamento;
  guardiao_dos_ventos_siderais.setPassthroughMode(false);
#elif defined(RECEPTOR_DOS_VENTOS_PPM)
  mensageiro_dos_ventos_cosmicos.onConnect(AoDespertarParaOCantoDoEter);
  mensageiro_dos_ventos_cosmicos.onDisconnect(AoRecolherSeAoSilencioDaMata);
  mensageiro_dos_ventos_cosmicos.onNewData(InterpretarAsVozesDoFirmamento);
#endif

  tendao_da_asa_matutina.attach(ARTICULACAO_ASA_DA_MANHA, PULSO_MINIMO_SERVO, PULSO_MAXIMO_SERVO);
  tendao_da_asa_vespertina.attach(ARTICULACAO_ASA_DO_ENTARDECER, PULSO_MINIMO_SERVO, PULSO_MAXIMO_SERVO);

#ifdef ECOS_PRESCINDIVEIS_DA_ALMA_ALADA
  Serial.println("Asas de anil prontas para a dança dos céus e a canção da vida.");
#endif
}

/* O Coração que Pulso no Tempo — AnimarPulsarDoCoracaoAlado()
   A cadência do bater das asas, tecida pelo sopro vital e pelo compasso da alma. */
void AnimarPulsarDoCoracaoAlado() {
  unsigned long agora = relogio_das_eras.instante_do_agora_cosmico;
  unsigned long ultima = relogio_das_eras.ultima_pulsacao_do_sopro_alado;
  if (ultima == 0) { ultima = agora; }
  float dt = (agora - ultima) * 0.001f;
  if (dt > DT_MAXIMO_DO_SONHO) dt = DT_MAXIMO_DO_SONHO;
  relogio_das_eras.ultima_pulsacao_do_sopro_alado = agora;

  if(estado_presente_da_alma == EM_DANCA_COM_OS_VENTOS) {
    float sopro_norm = (voz_do_sopro_vital - 1000.0f) / 1000.0f;
    float compasso_norm = (voz_do_compasso_da_alma - 1500.0f) / 500.0f;
    float frequencia_alvo = (2.0f * PI / CICLO_DO_CORACAO_ALADO) * (MULTIPLICADOR_MINIMO_FREQUENCIA + PESO_DO_SOPRO_NA_FREQUENCIA * sopro_norm + PESO_DO_COMPASSO_NA_FREQUENCIA * compasso_norm);
    if (frequencia_alvo < MULTIPLICADOR_MINIMO_FREQUENCIA) frequencia_alvo = MULTIPLICADOR_MINIMO_FREQUENCIA;
    float erro_frequencia = frequencia_alvo - cadencia_do_destino_alado;
    float beschleunigung = erro_frequencia * ACELERACAO_DO_COMPASSO;
    cadencia_do_destino_alado += beschleunigung * dt;
    angulo_da_danca_alada += cadencia_do_destino_alado * dt;
    if (angulo_da_danca_alada > LIMITE_ANGULAR_DO_GIRO) angulo_da_danca_alada -= LIMITE_ANGULAR_DO_GIRO;
    if (angulo_da_danca_alada < -LIMITE_ANGULAR_DO_GIRO) angulo_da_danca_alada += LIMITE_ANGULAR_DO_GIRO;
  } else {
    angulo_da_danca_alada = 0;
    cadencia_do_destino_alado *= DECAIMENTO_DA_CADENCIA_SONOLENTA;
    if (fabs(cadencia_do_destino_alado) < EPSILON_CADENCIA_ZERO) cadencia_do_destino_alado = 0;
  }
}

/* O Hálito que Sustenta o Voo — SustentarAltura()
   Quando a Gralha ouve a pressão do céu, ela se segura no ar como uma prece. */
void SustentarAltura() {
#ifndef GRALHA_AZUL_BAROMETRO_DESLIGADO
  ganho_do_sustentar = mapear_entre_escalas_harmonicas(
    (float)voz_do_sustentar_altura, 1000.0f, 2000.0f,
    0.0f, 1.0f);
  ganho_do_sustentar = constrain(ganho_do_sustentar, 0.0f, 1.0f);
  if (oraculo_respira && ganho_do_sustentar > GANHO_LIMIAR_SUSTENTAR) {
    if (!modo_sustentar_ativo) {
      modo_sustentar_ativo = true;
    }
    altura_desejada_do_voo = mapear_entre_escalas_harmonicas(
      (float)voz_do_sopro_vital, 1000.0f, 2000.0f,
      0.0f, ALTURA_MAX_DO_SUSTENTAR_M);
    float erro = altura_desejada_do_voo - altura_do_voo_sideral;
    if (fabs(erro) < SILENCIO_DO_SUSTENTAR_M) {
      // Zona morta: nulo
    } else {
      sopro_vital_do_sustentar = 1500.0f + erro * FORCA_BASE_DO_SUSTENTAR * ganho_do_sustentar;
      sopro_vital_do_sustentar = constrain(sopro_vital_do_sustentar,
        SOPRO_MIN_DO_SUSTENTAR, SOPRO_MAX_DO_SUSTENTAR);
    }
    if (sopro_da_subida_alada > LIMITE_DA_SUBIDA_SUSTENTADA_MS) {
      sopro_vital_do_sustentar -= CORRECAO_TAXA_LIMITE_SUSTENTAR;
    } else if (sopro_da_subida_alada < -LIMITE_DA_DESCIDA_SUSTENTADA_MS) {
      sopro_vital_do_sustentar += CORRECAO_TAXA_LIMITE_SUSTENTAR;
    }
    sopro_vital_do_sustentar = constrain(sopro_vital_do_sustentar,
      SOPRO_MIN_DO_SUSTENTAR, SOPRO_MAX_DO_SUSTENTAR);
  } else {
    modo_sustentar_ativo = false;
    sopro_vital_do_sustentar = (float)voz_do_sopro_vital;
  }
#else
  modo_sustentar_ativo = false;
  sopro_vital_do_sustentar = (float)voz_do_sopro_vital;
#endif
}

/* A Dança das Asas no Vento — ManifestarOVooNosVentos()
   Onde o comando se faz carne, e a Gralha desenha no céu a sua sina. */
void ManifestarOVooNosVentos() {
  float comando_aletao = (voz_do_aletao - 1500.0f) * ESCALA_ANGULAR_DA_ARTICULACAO;
  float comando_profundor = (voz_do_profundor - 1500.0f) * ESCALA_ANGULAR_DO_PROFUNDOR;
  int angulo_portal_esquerdo, angulo_portal_direito;
  float sopro_efetivo = modo_sustentar_ativo ? sopro_vital_do_sustentar : (float)voz_do_sopro_vital;
  if (modo_presente_do_espirito == EM_RITMO_DE_BATIDA_DAS_ASAS) {
    limiar_elevado = true;
  }
  int limiar_atual = limiar_elevado
    ? LIMIAR_DO_VOO_ATIVO
    : (LIMIAR_DO_VOO_ATIVO - LIMIAR_DO_VOO_ATIVO_HISTERESE);
  if(estado_presente_da_alma == EM_DANCA_COM_OS_VENTOS) {
    modo_presente_do_espirito = (sopro_efetivo > limiar_atual)
        ? EM_RITMO_DE_BATIDA_DAS_ASAS
        : EM_DESLIZE_ETERNO_E_CONTEMPLATIVO;
    if (modo_presente_do_espirito == EM_DESLIZE_ETERNO_E_CONTEMPLATIVO) {
      limiar_elevado = false;
    }
  } else {
    modo_presente_do_espirito = EM_DESLIZE_ETERNO_E_CONTEMPLATIVO;
    limiar_elevado = false;
  }
  if(modo_presente_do_espirito == EM_RITMO_DE_BATIDA_DAS_ASAS) {
    float magnitude_da_batida = ((sopro_efetivo - LIMIAR_DO_VOO_ATIVO) * MAGNITUDE_ESCALA_DA_FEROCIDADE) * (1.0f - (voz_do_compasso_da_alma - 1500.0f) * MODULACAO_DO_COMPASSO);
    float canto_original_da_asa = sin(angulo_da_danca_alada);
    float direcao_do_bater = cos(angulo_da_danca_alada);
    float ferocidade_do_bater = mapear_entre_escalas_harmonicas(voz_da_ferocidade_do_bater, 1000.0f, 2000.0f, FEROCIDADE_MINIMA, FEROCIDADE_MAXIMA);
    float ferocidade_do_retorno = mapear_entre_escalas_harmonicas(voz_da_ferocidade_do_retorno, 1000.0f, 2000.0f, FEROCIDADE_MINIMA, FEROCIDADE_MAXIMA);
    float fator_do_leme = mapear_entre_escalas_harmonicas(voz_da_ferocidade_do_leme, 1000.0f, 2000.0f, DIFERENCIAL_LEME_MIN, DIFERENCIAL_LEME_MAX);
    float ferocidade_bater_esquerda = ferocidade_do_bater + fator_do_leme;
    float ferocidade_bater_direita  = ferocidade_do_bater - fator_do_leme;
    float ferocidade_retorno_esquerda = ferocidade_do_retorno + fator_do_leme;
    float ferocidade_retorno_direita  = ferocidade_do_retorno - fator_do_leme;
    float pulso_asa_esquerda = forma_do_bater_das_asas(canto_original_da_asa, direcao_do_bater, ferocidade_bater_esquerda, ferocidade_retorno_esquerda);
    float pulso_asa_direita = forma_do_bater_das_asas(canto_original_da_asa, direcao_do_bater, ferocidade_bater_direita, ferocidade_retorno_direita);
    float graus_asa_esquerda = magnitude_da_batida * pulso_asa_esquerda;
    float graus_asa_direita  = magnitude_da_batida * pulso_asa_direita;
    angulo_portal_esquerdo = (int)((comando_aletao - graus_asa_esquerda + ORIGEM_ASA_MATUTINA - comando_profundor) * MULTIPLICADOR_FINAL_ANGULAR);
    angulo_portal_direito  = (int)((comando_aletao + graus_asa_direita + ORIGEM_ASA_VESPERTINA + comando_profundor) * MULTIPLICADOR_FINAL_ANGULAR);
  } else {
    angulo_portal_esquerdo = (int)((comando_aletao - ANGULO_DO_PLANAR_SERENO + ORIGEM_ASA_MATUTINA - comando_profundor) * MULTIPLICADOR_FINAL_ANGULAR);
    angulo_portal_direito  = (int)((comando_aletao + ANGULO_DO_PLANAR_SERENO + ORIGEM_ASA_VESPERTINA + comando_profundor) * MULTIPLICADOR_FINAL_ANGULAR);
  }
  tendao_da_asa_matutina.write(constrain(angulo_portal_esquerdo + OFFSET_ANGULAR_NEUTRO, 0, 180));
  tendao_da_asa_vespertina.write(constrain(angulo_portal_direito + OFFSET_ANGULAR_NEUTRO, 0, 180));
}

/* O Sussurro ao Firmamento — SussurrarVooAoEter()
   A Gralha conta ao cosmos onde dança, para que o mundo saiba do seu voo. */
#if !defined(GRALHA_AZUL_TELEMETRIA_DESLIGADO) && defined(RECEPTOR_DOS_VENTOS_CRSF)
void SussurrarVooAoEter() {
  if (!oraculo_respira) return;
  unsigned long agora = millis();
  if (agora - ultimo_sopro_sideral >= INTERVALO_TELEMETRIA_GPS_MS) {
    ultimo_sopro_sideral = agora;
    crsf_sensor_gps_t pergaminho_do_voo;
    pergaminho_do_voo.latitude = htobe32(0);
    pergaminho_do_voo.longitude = htobe32(0);
#ifndef GRALHA_AZUL_BAROMETRO_DESLIGADO
    int16_t velocidade_chao = (int16_t)(fabs(sopro_da_subida_alada) * FATOR_CONVERSAO_VELOCIDADE);
#else
    int16_t velocidade_chao = 0;
#endif
    if (velocidade_chao < 0) velocidade_chao = 0;
    if (velocidade_chao > 65535) velocidade_chao = 65535;
    pergaminho_do_voo.groundspeed = htobe16((uint16_t)velocidade_chao);
    pergaminho_do_voo.heading = htobe16(0);
#ifndef GRALHA_AZUL_BAROMETRO_DESLIGADO
    int16_t alt_do_voo = (int16_t)(altura_do_voo_sideral + OFFSET_ALTITUDE_CRSF);
#else
    int16_t alt_do_voo = 0;
#endif
    if (alt_do_voo < 0) alt_do_voo = 0;
    if (alt_do_voo > 65535) alt_do_voo = 65535;
    pergaminho_do_voo.altitude = htobe16((uint16_t)alt_do_voo);
    pergaminho_do_voo.satellites = 0;
    guardiao_dos_ventos_siderais.queuePacket(
      CRSF_ADDRESS_FLIGHT_CONTROLLER,
      CRSF_FRAMETYPE_GPS,
      &pergaminho_do_voo,
      sizeof(crsf_sensor_gps_t));
  }
  if (agora - ultimo_sopro_termico >= INTERVALO_TELEMETRIA_TEMPERATURA_MS) {
    ultimo_sopro_termico = agora;
    crsf_sensor_battery_t bilhete_do_sopro_quente;
#ifndef GRALHA_AZUL_BAROMETRO_DESLIGADO
    uint16_t canto_termico = (uint16_t)(temperatura_do_ar_c * ESCALA_TEMPERATURA_CRSF);
#else
    uint16_t canto_termico = 0;
#endif
    if (canto_termico > 65535) canto_termico = 65535;
    bilhete_do_sopro_quente.voltage = htobe16(canto_termico);
    bilhete_do_sopro_quente.current = htobe16(0);
    bilhete_do_sopro_quente.capacity = 0;
    bilhete_do_sopro_quente.remaining = 0;
    guardiao_dos_ventos_siderais.queuePacket(
      CRSF_ADDRESS_FLIGHT_CONTROLLER,
      CRSF_FRAMETYPE_BATTERY_SENSOR,
      &bilhete_do_sopro_quente,
      sizeof(crsf_sensor_battery_t));
  }
}
#endif

/* O Ciclo Eterno — gralhaAzulLoop()
   A cada batida do tempo, a Gralha renova a sua dança. */
void gralhaAzulLoop() {
  relogio_das_eras.instante_do_agora_cosmico = millis();

#if defined(RECEPTOR_DOS_VENTOS_CRSF)
  guardiao_dos_ventos_siderais.loop();
#elif defined(RECEPTOR_DOS_VENTOS_PPM)
  mensageiro_dos_ventos_cosmicos.loop();
#endif

  AnimarPulsarDoCoracaoAlado();
  EscutarPressaoDoCeu();
  SustentarAltura();
  ManifestarOVooNosVentos();
  SussurrarVooAoEter();

  if(relogio_das_eras.instante_do_agora_cosmico - relogio_das_eras.ultimo_fulgor_da_chama_azul >= INTERVALO_NEO_PIXEL_MS) {
    relogio_das_eras.ultimo_fulgor_da_chama_azul = relogio_das_eras.instante_do_agora_cosmico;
#ifndef GRALHA_AZUL_NEOPIXEL_DESLIGADO
    manto_celestial_da_gralha.IrradiarLuzDaAlma();
#endif
  }

#ifdef ECOS_PRESCINDIVEIS_DA_ALMA_ALADA
  if (relogio_das_eras.instante_do_agora_cosmico -
        relogio_das_eras.ultimo_eco_prescindivei > INTERVALO_SERIAL_DEBUG_MS) {
      relogio_das_eras.ultimo_eco_prescindivei = relogio_das_eras.instante_do_agora_cosmico;
    Serial.print(estado_presente_da_alma == EM_DANCA_COM_OS_VENTOS ? "VOANDO" : "SONHANDO");
    Serial.print(" | Modo: ");
    Serial.print(modo_presente_do_espirito == EM_RITMO_DE_BATIDA_DAS_ASAS ? "RITMADO" : "PLANANDO");
    Serial.print(" | SoproV: "); Serial.print(voz_do_sopro_vital);
    Serial.print(" | Alet: "); Serial.print(voz_do_aletao);
    Serial.print(" | Prof: "); Serial.print(voz_do_profundor);
    Serial.print(" | Leme: "); Serial.print(voz_do_leme_estelar);
    Serial.print(" | Despertar: "); Serial.print(voz_do_despertar);
    Serial.print(" | FerBater: "); Serial.print(voz_da_ferocidade_do_bater);
    Serial.print(" | FerRetorno: "); Serial.print(voz_da_ferocidade_do_retorno);
    Serial.print(" | FerLeme: "); Serial.print(voz_da_ferocidade_do_leme);
    Serial.print(" | SustentarGain: "); Serial.print(ganho_do_sustentar, 2);
    Serial.print(" | SustentarCH10: "); Serial.print(voz_do_sustentar_altura);
    if (oraculo_respira) {
#ifndef GRALHA_AZUL_BAROMETRO_DESLIGADO
      Serial.print(" | AltVoo: "); Serial.print(altura_do_voo_sideral, 1);
      Serial.print(" | Subida: "); Serial.print(sopro_da_subida_alada, 2);
      Serial.print(" | SoproDoCeu: "); Serial.print(temperatura_do_ar_c, 1);
      Serial.print(" | FeNoSopro: "); Serial.print(fe_no_sopro_quente, 2);
      if (modo_sustentar_ativo) {
        Serial.print(" | AltDesej: "); Serial.print(altura_desejada_do_voo, 1);
        Serial.print(" | SoproSustentar: "); Serial.print(sopro_vital_do_sustentar, 0);
        Serial.print(" | GainEfetivo: "); Serial.print(ganho_do_sustentar * FORCA_BASE_DO_SUSTENTAR, 1);
      }
#endif
    }
    Serial.print(" | Fase: "); Serial.print(angulo_da_danca_alada, 2);
    Serial.print(" | Cadencia: "); Serial.print(cadencia_do_destino_alado, 2);
    Serial.println();
  }
#endif
  if (relogio_das_eras.ultima_pulsacao_do_sopro_alado == 0) {
    relogio_das_eras.ultima_pulsacao_do_sopro_alado = relogio_das_eras.instante_do_agora_cosmico;
  }
  relogio_das_eras.ultima_pulsacao_do_sopro_alado = relogio_das_eras.instante_do_agora_cosmico;
}
/* E assim, o Grande Código da Gralha Azul se manifesta, em cada ciclo,
   um testemunho alado da resiliência da vida, da magia da transformação,
   e da perene esperança semeada entre o céu e a terra. */