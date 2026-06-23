/*
  O Grande Código da Gralha Azul
  A Inscrição Primordial da Lenda Alada
  — Implementação do Coração Alado Partilhado entre Modelos —
*/

#include "GralhaAzul.h"

// =======================================================
// VARIÁVEIS GLOBAIS — Definições
// =======================================================
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
// === AS JUNTURAS DA ALMA: Onde a Gralha toca o mundo ===
// === FIOS DO ORÁCULO DA PRESSÃO: por onde o céu sussurra à Gralha ===
/*
  Os Mistérios do Voo Sagrado: Leis Imutáveis da Natureza Alada
  Verdades primordiais, a essência do voo e da missão da Gralha.
*/
/*
  As Vibrações Primordiais do Éter: Ecos Neutros das Inspirações
  O silêncio de onde emanam as vontades que guiam a Gralha.
*/
/*
  Os Estados da Alma Alada: Fases da Consciência da Gralha
    O 'despertar' concede à Gralha o sopro da vida; o 'sonho' é seu repouso sagrado,
    mas o voo só se inicia quando o espírito alado a comanda.
  */
bool limiar_elevado = true;
bool oraculo_respira = false; // O oráculo da pressão escuta a altura invisível.
/*
  O Coração do Mistério Alado: Variáveis que Guardam o Ser da Gralha
*/
EstadoDaAlmaAlada estado_presente_da_alma = EM_SONHO_NA_QUIETUDE_DA_FLORESTA; // A Gralha desperta com o chamado.
ModoDoEspiritoAlado modo_presente_do_espirito = EM_DESLIZE_ETERNO_E_CONTEMPLATIVO; // Inicia em serenidade.
  
// Voz do sustentar a altura (CH10): Altitude-Hold
int voz_do_sustentar_altura = 0;
/*
  O Relógio das Eras: Marcadores Temporais da Jornada da Gralha
*/
/*
  As Vozes do Céu: Inspirações que Moldam o Destino da Gralha
*/
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
// O oráculo da pressão escuta a altura invisível.
// A subida da Gralha revela o sopro quente do céu.
// A temperatura apenas sussurra; a subida confirma.
bool modo_de_escuta_termal = false;
float fe_no_sopro_quente = 0.0f;
float ganho_do_sustentar = 0.0f;            // Ganho do sustentar (0..1, do CH10)
float altura_desejada_do_voo = 0.0f;
float sopro_vital_do_sustentar = 1500.0f;  // Sopro efetivo no modo sustentar
bool modo_sustentar_ativo = false;
#ifndef GRALHA_AZUL_BAROMETRO_DESLIGADO
#endif
float pulsacao_da_chama_primordial = 0.0f;
/*
  A Geometria Sagrada do Voo: A Essência do Movimento Alado
  'angulo_da_danca_alada' (theta) é a fase atual no ciclo da batida da asa.
  'cadencia_do_destino_alado' (omega) é a velocidade com que este ângulo muda.
  'pulso_do_sopro_vital' é a manifestação senoidal do movimento, o ritmo da vida.
*/
float angulo_da_danca_alada = 0;
float cadencia_do_destino_alado = 0;
float pulso_do_sopro_vital = 0.0;
// Ritual de Mapeamento Harmônico: Converte vibrações entre escalas.
float mapear_entre_escalas_harmonicas(float valor, float minimo_origem, float max_origem, float minimo_destino, float max_destino) {
  return (valor - minimo_origem) * (max_destino - minimo_destino) / (max_origem - minimo_origem) + minimo_destino;
}
float forma_do_bater_das_asas(float canto_do_vento, float direcao_do_bater, float ferocidade_do_bater, float ferocidade_do_retorno) {
  // A 'direcao_do_bater' revela se a asa desce ou retorna.
  float ferocidade = (direcao_do_bater >= 0.0f) ? ferocidade_do_bater : ferocidade_do_retorno;
  float equilibrio_do_ceu = tanh(ferocidade);
  if (equilibrio_do_ceu < 0.001f) {
    return canto_do_vento;
  }
  float resultado = tanh(ferocidade * canto_do_vento) / equilibrio_do_ceu;
  // Limita a saída para evitar valores extremos quando ferocidade é muito pequena.
  if (resultado > 1.5f) resultado = 1.5f;
  if (resultado < -1.5f) resultado = -1.5f;
  return resultado;
}
/*
  O Manto de Luz Celestial: A Irradiação da Chama Azul da Alma
  Um espelho do estado e da missão da Gralha.
*/
#ifndef GRALHA_AZUL_NEOPIXEL_DESLIGADO
MantoDeLuzCelestial manto_celestial_da_gralha;
#endif
Servo tendao_da_asa_matutina, tendao_da_asa_vespertina;
// --- Rituais de Sintonia e Percepção da Alma Alada ---
#ifndef GRALHA_AZUL_BAROMETRO_DESLIGADO
// O oráculo da pressão desperta: abre o portal que escuta a altura invisível.
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
  // A Gralha aprende a sentir o chão: escuta a altura do ninho várias vezes
  float soma_altura = 0.0f;
  int leituras_validas = 0;
  for (int i = 0; i < 10; i++) {
    sensors_event_t evento;
    oraculo_da_pressao.getEvent(&evento);
    if (evento.pressure > 0) {
      float temperatura;
      oraculo_da_pressao.getTemperature(&temperatura);
      float altitude = oraculo_da_pressao.pressureToAltitude(1013.25f, evento.pressure, temperatura);
      soma_altura += altitude;
      leituras_validas++;
    }
    delay(50);
  }
  if (leituras_validas > 0) {
    altura_inicial_m = soma_altura / leituras_validas;
  }
  ultima_altura_do_voo_sideral = 0.0f;
  ultimo_sopro_do_oraculo = millis();
  ultima_temperatura_do_ar_c = 0.0f;
}
// Escuta a pressão do céu: lê o barômetro e calcula altura e subida.
// Otimizado: getEvent() + getTemperature() a cada 5 ciclos (~1s) em vez de todas as vezes.
// Intervalo de 200ms em vez de 100ms. Tendência da temperatura a partir de valores suavizados.
void EscutarPressaoDoCeu() {
  if (!oraculo_respira) return;
  unsigned long agora = millis();
  if (agora - ultimo_sopro_do_oraculo < 200) return; // A cada 200ms
  float dt = (agora - ultimo_sopro_do_oraculo) * 0.001f;
  if (dt < 0.001f) dt = 0.001f;
  ultimo_sopro_do_oraculo = agora;
  // getEvent() lê a pressão (+ temperatura interna) num único ciclo de ~9ms
  sensors_event_t evento;
  oraculo_da_pressao.getEvent(&evento);
  if (evento.pressure <= 0) return;
  pressao_do_ceu_hpa = evento.pressure;
  // Temperatura apenas a cada 5 ciclos (~1s) — inércia térmica
  static uint8_t ciclo_termico = 0;
  if (++ciclo_termico >= 5) {
    ciclo_termico = 0;
    float nova_temp;
    oraculo_da_pressao.getTemperature(&nova_temp);
    // Suavização 50/50
    temperatura_do_ar_c = temperatura_do_ar_c * 0.5f + nova_temp * 0.5f;
  }
  // Tendência da temperatura (a cada ciclo)
  tendencia_da_temperatura_c = tendencia_da_temperatura_c * 0.9f + (temperatura_do_ar_c - ultima_temperatura_do_ar_c) * 0.1f;
  ultima_temperatura_do_ar_c = temperatura_do_ar_c;
  // Altitude: fórmula barométrica (ISO 1976) — sem chamada de biblioteca
  // h = 44307.69 * (1 - (p/1013.25)^0.190284)
  float razao = pressao_do_ceu_hpa / REFERENCIA_DA_PRESSAO_HPA;
  float fator = 1.0f - powf(razao, 0.190284f);
  float altitude_absoluta = fator * 44307.69f;
  altura_do_voo_sideral = altitude_absoluta - altura_inicial_m;
  // Subida (velocidade vertical)
  subida_da_gralha_ms = (altura_do_voo_sideral - ultima_altura_do_voo_sideral) / dt;
  ultima_altura_do_voo_sideral = altura_do_voo_sideral;
  // Filtro passa-baixa (mais agressivo: ~470ms de constante de tempo)
  sopro_da_subida_alada = sopro_da_subida_alada * 0.7f + subida_da_gralha_ms * 0.3f;
  // Confiança termal
  fe_no_sopro_quente = sopro_da_subida_alada + tendencia_da_temperatura_c * 0.3f;
  if (fe_no_sopro_quente > 0.5f) modo_de_escuta_termal = true;
  else if (fe_no_sopro_quente < -0.5f) modo_de_escuta_termal = false;
}
#else
void DespertarOraculoDaPressao() {}
void EscutarPressaoDoCeu() {}
#endif
void AoDespertarParaOCantoDoEter() {
#ifdef ECOS_PRESCINDIVEIS_DA_ALMA_ALADA
  Serial.println("A Gralha sente o chamado do éter!");
#endif
}
void AoRecolherSeAoSilencioDaMata() {
  // A ligação com o éter se perdeu — a Gralha adormece forçadamente.
  estado_presente_da_alma = EM_SONHO_NA_QUIETUDE_DA_FLORESTA;
  modo_presente_do_espirito = EM_DESLIZE_ETERNO_E_CONTEMPLATIVO;
  limiar_elevado = false;
#ifdef ECOS_PRESCINDIVEIS_DA_ALMA_ALADA
  Serial.println("O éter silencia. A Gralha retorna ao seu sonho na floresta.");
#endif
}
#if defined(RECEPTOR_DOS_VENTOS_CRSF)
void InterpretarAsVozesDoFirmamento() {
  // O despertar: se a voz do ritual ultrapassa o limiar, a Gralha se ergue.
  // Apenas o comando do espírito alado inicia o bater das asas — o despertar
  // concede apenas a prontidão da alma.
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
/*
  O Ritual da Animação Primordial: A Gralha Recebe o Sopro da Existência
  Onde a essência da Gralha se manifesta, pronta para sua jornada.
*/
void gralhaAzulSetup() {
#ifndef GRALHA_AZUL_NEOPIXEL_DESLIGADO
  manto_celestial_da_gralha.AcenderLuzPrimordial();
#endif
  DespertarOraculoDaPressao();
  AoDespertarParaOCantoDoEter();
#ifdef ECOS_PRESCINDIVEIS_DA_ALMA_ALADA
  Serial.begin(115200);
  unsigned long tempo_de_espera_usb = millis();
  while (!Serial && (millis() - tempo_de_espera_usb < 4000)) {  }
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
  tendao_da_asa_matutina.attach(ARTICULACAO_ASA_DA_MANHA, 500, 2500);
  tendao_da_asa_vespertina.attach(ARTICULACAO_ASA_DO_ENTARDECER, 500, 2500);
#ifdef ECOS_PRESCINDIVEIS_DA_ALMA_ALADA
  Serial.println("Asas de anil prontas para a dança dos céus e a canção da vida.");
#endif
}
/*
  A Dança Cósmica: Gerando o Ritmo do Coração Alado
  Calcula a fase e cadência da batida das asas, o pulsar de seu ser.
  Este é o 'AtualizarDestino' do ser da Gralha.
*/
void AnimarPulsarDoCoracaoAlado() {
  // dt atual: delta desde a última animação (fixo, não do loop anterior)
  unsigned long agora = relogio_das_eras.instante_do_agora_cosmico;
  unsigned long ultima = relogio_das_eras.ultima_pulsacao_do_sopro_alado;
  if (ultima == 0) { ultima = agora; }
  float dt = (agora - ultima) * 0.001f;
  // Limita dt a 50ms (evita salto gigante na primeira execução ou após bloqueios)
  if (dt > 0.05f) dt = 0.05f;
  relogio_das_eras.ultima_pulsacao_do_sopro_alado = agora;
  if(estado_presente_da_alma == EM_DANCA_COM_OS_VENTOS) {
    // Intenção de cadência: frequência alvo da batida (rad/s)
    // CH3 (1000..2000) escala a frequência base, CH6 modula-a
    float sopro_norm = (voz_do_sopro_vital - 1000.0f) / 1000.0f; // 0..1
    float compasso_norm = (voz_do_compasso_da_alma - 1500.0f) / 500.0f; // -1..1
    float frequencia_alvo = (2.0f * PI / CICLO_DO_CORACAO_ALADO) * (0.5f + 0.5f * sopro_norm + 0.3f * compasso_norm);
    if (frequencia_alvo < 0.5f) frequencia_alvo = 0.5f;
    // Malha de seguimento suave e superamortecida — sem overshoot, sem solavancos
    float erro_frequencia = frequencia_alvo - cadencia_do_destino_alado;
    float beschleunigung = erro_frequencia * 8.0f; // Constante de tempo ~125ms
    cadencia_do_destino_alado += beschleunigung * dt;
    // Integração do ângulo
    angulo_da_danca_alada += cadencia_do_destino_alado * dt;
    // Mantém o ângulo (opcional, para estabilidade numérica)
    if (angulo_da_danca_alada > 20.0f * PI) angulo_da_danca_alada -= 20.0f * PI;
    if (angulo_da_danca_alada < -20.0f * PI) angulo_da_danca_alada += 20.0f * PI;
  } else { // Em sonho, o coração alado repousa seu ritmo.
    angulo_da_danca_alada = 0;
    cadencia_do_destino_alado *= 0.90f;
    if (fabs(cadencia_do_destino_alado) < 0.001f) cadencia_do_destino_alado = 0;
  }
}
/*
   *  O Sustentar da Altura: O Ganho Que Escuta a Altura
    CH10 é ganho contínuo (1000=0%, 2000=100%) — já não é um interruptor
    Ganho_do_sustentar (0..1) escala FORCA_BASE_DO_SUSTENTAR
    CH3 permanece sempre acelerador direto (sem reatribuição de canal)
    Altitude alvo via CH3 (1000=0m, 2000=ALTURA_MAX_DO_SUSTENTAR_M=20m)
    Zona morta: SILENCIO_DO_SUSTENTAR_M=0.5m
    Com Hold ativo, o regulador P substitui o sinal de acelerador para manter a altura.
    Gain = 0 significa: sem regulação de altura, CH3 direto como Sopro.
  */
  void SustentarAltura() {
  #ifndef GRALHA_AZUL_BAROMETRO_DESLIGADO
    // CH10 como ganho: 1000=0, 2000=1
    ganho_do_sustentar = mapear_entre_escalas_harmonicas(
      (float)voz_do_sustentar_altura, 1000.0f, 2000.0f,
      0.0f, 1.0f);
    ganho_do_sustentar = constrain(ganho_do_sustentar, 0.0f, 1.0f);
    if (oraculo_respira && ganho_do_sustentar > 0.01f) {
      if (!modo_sustentar_ativo) {
        modo_sustentar_ativo = true;
      }
      // CH3 controla a altitude alvo: 1000=0m, 2000=ALTURA_MAX
      altura_desejada_do_voo = mapear_entre_escalas_harmonicas(
        (float)voz_do_sopro_vital, 1000.0f, 2000.0f,
        0.0f, ALTURA_MAX_DO_SUSTENTAR_M);
      // Erro de altitude
      float erro = altura_desejada_do_voo - altura_do_voo_sideral;
      // Regulador P com ganho variável: CH10 escala a força da correção
      if (fabs(erro) < SILENCIO_DO_SUSTENTAR_M) {
        // Zona morta: nulo
      } else {
        sopro_vital_do_sustentar = 1500.0f + erro * FORCA_BASE_DO_SUSTENTAR * ganho_do_sustentar;
        sopro_vital_do_sustentar = constrain(sopro_vital_do_sustentar,
          SOPRO_MIN_DO_SUSTENTAR, SOPRO_MAX_DO_SUSTENTAR);
      }
      // Limitação da taxa de subida/descida
      if (sopro_da_subida_alada > LIMITE_DA_SUBIDA_SUSTENTADA_MS) {
        sopro_vital_do_sustentar -= 10.0f;
      } else if (sopro_da_subida_alada < -LIMITE_DA_DESCIDA_SUSTENTADA_MS) {
        sopro_vital_do_sustentar += 10.0f;
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
  
  /*  O Movimento dos Portais Alados: Manifestando o Voo da Gralha
    Traduz a dinâmica interna e as inspirações celestes em movimento físico.
    Este é o 'MoverPortais' da essência da Gralha.
    No sustentar, o sopro vital é substituído pelo sopro do sustentar a altura.
  */
  void ManifestarOVooNosVentos() {
    float comando_aletao = (voz_do_aletao - 1500.0f) * 0.06f;
    float comando_profundor = (voz_do_profundor - 1500.0f) * 0.06f;
    int angulo_portal_esquerdo, angulo_portal_direito;
  // No modo sustentar, o sopro vital é substituído pelo sopro do sustentar a altura
  float sopro_efetivo = modo_sustentar_ativo ? sopro_vital_do_sustentar : (float)voz_do_sopro_vital;
  // Histerese: uma vez no modo de batida, permanece até abaixo do limiar - histerese
  // O despertar é necessário para o voo: ao acordar, a Gralha plana em silêncio
  // até que o sopro vital a chame ao bater das asas.
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
    // A 'magnitude_da_batida' é a força com que a Gralha impulsiona o ar.
    float magnitude_da_batida = ((sopro_efetivo - LIMIAR_DO_VOO_ATIVO) * 0.06f) * (1.0f - (voz_do_compasso_da_alma - 1500.0f) * 0.0003f);
    // O 'canto_original_da_asa' é o coração senoidal do movimento.
    float canto_original_da_asa = sin(angulo_da_danca_alada);
    // A 'direcao_do_bater' revela se a asa desce ou retorna.
    float direcao_do_bater = cos(angulo_da_danca_alada);
    // Ferocidade para as asas (CH7 = descida, CH8 = subida)
    float ferocidade_do_bater = mapear_entre_escalas_harmonicas(voz_da_ferocidade_do_bater, 1000.0f, 2000.0f, 1.0f, 8.0f);
    float ferocidade_do_retorno = mapear_entre_escalas_harmonicas(voz_da_ferocidade_do_retorno, 1000.0f, 2000.0f, 1.0f, 8.0f);
    // Fator do leme (CH5): centro=0, extremos=±1 (±2 escala de ferocidade)
    float fator_do_leme = mapear_entre_escalas_harmonicas(voz_da_ferocidade_do_leme, 1000.0f, 2000.0f, -4.0f, 4.0f);
    // Ferocidade do leme aplicada diferencialmente: +num esquerdo, -num direito
    float ferocidade_bater_esquerda = ferocidade_do_bater + fator_do_leme;
    float ferocidade_bater_direita  = ferocidade_do_bater - fator_do_leme;
    float ferocidade_retorno_esquerda = ferocidade_do_retorno + fator_do_leme;
    float ferocidade_retorno_direita  = ferocidade_do_retorno - fator_do_leme;
    // Cada tendão recebe sua própria forma de batida
    float pulso_asa_esquerda = forma_do_bater_das_asas(
        canto_original_da_asa, direcao_do_bater,
        ferocidade_bater_esquerda,
        ferocidade_retorno_esquerda);
    float pulso_asa_direita = forma_do_bater_das_asas(
        canto_original_da_asa, direcao_do_bater,
        ferocidade_bater_direita,
        ferocidade_retorno_direita);
    float graus_asa_esquerda = magnitude_da_batida * pulso_asa_esquerda;
    float graus_asa_direita  = magnitude_da_batida * pulso_asa_direita;
    angulo_portal_esquerdo = (int)((comando_aletao - graus_asa_esquerda + ORIGEM_ASA_MATUTINA - comando_profundor) * 2.0f);
    angulo_portal_direito  = (int)((comando_aletao + graus_asa_direita + ORIGEM_ASA_VESPERTINA + comando_profundor) * 2.0f);
  } else { // EM_DESLIZE_ETERNO_E_CONTEMPLATIVO
    angulo_portal_esquerdo = (int)((comando_aletao - ANGULO_DO_PLANAR_SERENO + ORIGEM_ASA_MATUTINA - comando_profundor) * 2.0f);
    angulo_portal_direito  = (int)((comando_aletao + ANGULO_DO_PLANAR_SERENO + ORIGEM_ASA_VESPERTINA + comando_profundor) * 2.0f);
  }
  tendao_da_asa_matutina.write(constrain(angulo_portal_esquerdo + 100, 0, 180));
  tendao_da_asa_vespertina.write(constrain(angulo_portal_direito + 100, 0, 180));
}
/*
   *  O Sopro ao Éter: A Gralha Sussurra seu Voo ao Cosmos
    O coração da Gralha envia ao éter a altura do voo sideral
    e o sopro quente do céu, para que o firmamento testemunhe.
  */
#if !defined(GRALHA_AZUL_TELEMETRIA_DESLIGADO) && defined(RECEPTOR_DOS_VENTOS_CRSF)
  void SussurrarVooAoEter() {
    if (!oraculo_respira) return;
    unsigned long agora = millis();
  
    // Pergaminho do Voo Sideral: envia altura do voo ao firmamento
    if (agora - ultimo_sopro_sideral >= 200) {
      ultimo_sopro_sideral = agora;
      crsf_sensor_gps_t pergaminho_do_voo;
      pergaminho_do_voo.latitude = htobe32(0);
      pergaminho_do_voo.longitude = htobe32(0);
      // Velocidade aparente: módulo da subida alada em km/h
  #ifndef GRALHA_AZUL_BAROMETRO_DESLIGADO
      int16_t velocidade_chao = (int16_t)(fabs(sopro_da_subida_alada) * 3.6f * 10.0f);
  #else
      int16_t velocidade_chao = 0;
  #endif
      if (velocidade_chao < 0) velocidade_chao = 0;
      if (velocidade_chao > 65535) velocidade_chao = 65535;
      pergaminho_do_voo.groundspeed = htobe16((uint16_t)velocidade_chao);
      pergaminho_do_voo.heading = htobe16(0);
      // Altitude: metros relativos + 1000 (offset CRSF), limitado a 0..65535
  #ifndef GRALHA_AZUL_BAROMETRO_DESLIGADO
      int16_t alt_do_voo = (int16_t)(altura_do_voo_sideral + 1000.0f);
  #else
      int16_t alt_do_voo = 0;
  #endif
      if (alt_do_voo < 0) alt_do_voo = 0;
      if (alt_do_voo > 65535) alt_do_voo = 65535;
      pergaminho_do_voo.altitude = htobe16((uint16_t)alt_do_voo);
      pergaminho_do_voo.satellites = 0;
      guardiao_dos_ventos_siderais.queuePacket(
        CRSF_ADDRESS_FLIGHT_CONTROLLER, // O coração da Gralha, endereço no éter
        CRSF_FRAMETYPE_GPS,             // Pergaminho do voo, tipo sideral
        &pergaminho_do_voo,
        sizeof(crsf_sensor_gps_t));
    }
  
    // Bilhete do Sopro Quente: envia temperatura como canto térmico
    if (agora - ultimo_sopro_termico >= 500) {
      ultimo_sopro_termico = agora;
      crsf_sensor_battery_t bilhete_do_sopro_quente;
  #ifndef GRALHA_AZUL_BAROMETRO_DESLIGADO
      uint16_t canto_termico = (uint16_t)(temperatura_do_ar_c * 100.0f);
  #else
      uint16_t canto_termico = 0;
  #endif
      if (canto_termico > 65535) canto_termico = 65535;
      bilhete_do_sopro_quente.voltage = htobe16(canto_termico);
      bilhete_do_sopro_quente.current = htobe16(0);
      bilhete_do_sopro_quente.capacity = 0;
      bilhete_do_sopro_quente.remaining = 0;
      guardiao_dos_ventos_siderais.queuePacket(
        CRSF_ADDRESS_FLIGHT_CONTROLLER, // O coração da Gralha, endereço no éter
        CRSF_FRAMETYPE_BATTERY_SENSOR,  // Bilhete do sopro quente, tipo térmico
        &bilhete_do_sopro_quente,
        sizeof(crsf_sensor_battery_t));
    }
  }
#elif defined(RECEPTOR_DOS_VENTOS_PPM)
  void SussurrarVooAoEter() {
    // PPM não suporta telemetria CRSF — silêncio do éter.
  }
#endif
/*
  O Ciclo Infinito da Lenda Viva: A Gralha Dança com o Cosmos
  Onde a Gralha Azul manifesta sua essência imortal a cada instante.
*/
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
  if(relogio_das_eras.instante_do_agora_cosmico - relogio_das_eras.ultimo_fulgor_da_chama_azul >= 33) { // ~30fps
    relogio_das_eras.ultimo_fulgor_da_chama_azul = relogio_das_eras.instante_do_agora_cosmico;
#ifndef GRALHA_AZUL_NEOPIXEL_DESLIGADO
    manto_celestial_da_gralha.IrradiarLuzDaAlma();
#endif
  }
#ifdef ECOS_PRESCINDIVEIS_DA_ALMA_ALADA
  if (relogio_das_eras.instante_do_agora_cosmico -
        relogio_das_eras.ultimo_eco_prescindivei > 250) {
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
  // Inicialização na primeira execução: evita dt gigantesco na partida
  if (relogio_das_eras.ultima_pulsacao_do_sopro_alado == 0) {
    relogio_das_eras.ultima_pulsacao_do_sopro_alado = relogio_das_eras.instante_do_agora_cosmico;
  }
  relogio_das_eras.ultima_pulsacao_do_sopro_alado = relogio_das_eras.instante_do_agora_cosmico;
}
// E assim, o Grande Código da Gralha Azul se manifesta, em cada ciclo,
// um testemunho alado da resiliência da vida, da magia da transformação,
// e da perene esperança semeada entre o céu e a terra,