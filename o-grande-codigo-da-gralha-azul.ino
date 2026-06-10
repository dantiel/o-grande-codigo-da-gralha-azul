/*
  O Grande Código da Gralha Azul
  A Inscrição Primordial da Lenda Alada

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

// --- Oráculos e Conexões com o Cosmos: Os Sentidos da Gralha ---
//#define ECOS_PRESCINDIVEIS_DA_ALMA_ALADA // Se definido, a Gralha partilha seus estados (Debug).
#define FREQUENCIA_DO_SOPRO_COSMICO 420000 // O ritmo da comunicação com o éter (420000 baud).
#define PORTAL_DOS_VENTOS_CELESTES Serial1  // O limiar por onde as influências astrais tocam a Gralha.

#include <Arduino.h>
#include <CrsfSerial.h>

//#define ORACULO_DA_PRESSAO_DO_CEU // Descomente para ativar o oráculo da pressão (requer Adafruit_BMP085_Unified e Adafruit_Sensor).
#ifdef ORACULO_DA_PRESSAO_DO_CEU
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>
#endif

// O Guardião dos Ventos Siderais, intérprete dos desígnios para a Gralha.
CrsfSerial guardiao_dos_ventos_siderais(PORTAL_DOS_VENTOS_CELESTES);

// O éter que leva as novas da Gralha ao mundo: instantes do último sopro ao firmamento.
unsigned long ultimo_sopro_sideral = 0;
unsigned long ultimo_sopro_termico = 0;

#include <Servo.h> // A arte ancestral de animar os tendões de luz.
#include <Adafruit_NeoPixel.h> // O encanto para acender a chama da alma.

/* As Relíquias da Gralha: Vínculos de Poder e Essência
  Os pontos de contato com o mundo, ecos da sua jornada.
*/
// === PINOS DA ALMA: Onde a Gralha toca o mundo ===
#define ARTICULACAO_ASA_DA_MANHA 5    // Asa que se ergue com a aurora.
#define ARTICULACAO_ASA_DO_ENTARDECER 7 // Asa que se recolhe com o crepúsculo.
#define VIA_DOS_SONHOS_LUNARES 1    // Canal dos sussurros da noite (CRSF RX).
#define VIA_DOS_ECOS_SOLARES 0  // Canal da canção ao dia (CRSF TX).

#define NUCLEO_DA_CHAMA_AZUL 16    // Onde a alma da Gralha brilha, sua essência anil.
#define QUANTIDADE_DE_CENTELHAS_NA_CHAMA 1 // Uma única, mas intensa, luz interior.

// === PINOS DO ORÁCULO DA PRESSÃO (BMP180) – I2C1 do RP2040 ===
// Wire1 usa GPIO26 (SDA) e GPIO27 (SCL) por padrão no RP2040 Zero.
// Estes pinos são livres (sem conflito com servos, CRSF ou NeoPixel).
#define PINO_SILENCIO_DA_ALTURA 26
#define PINO_RITMO_DA_PRESSAO 27

/*
  Os Mistérios do Voo Sagrado: Leis Imutáveis da Natureza Alada
  Verdades primordiais, a essência do voo e da missão da Gralha.
*/
#define CICLO_DO_CORACAO_ALADO 0.052f // A pulsação rítmica do voo, como a respiração da mata.
#define LIMIAR_DO_VOO_ATIVO 1040      // O ímpeto para o bater das asas, a dança da vida.
#define LIMIAR_DO_VOO_ATIVO_HISTERESE 20 // Zona morta para evitar oscilação do modo.
#define ANGULO_DO_PLANAR_SERENO -4   // Postura de escuta, em comunhão com os ventos.
#define ORIGEM_ASA_MATUTINA 0         // Posição de repouso da Asa Matutina.
#define ORIGEM_ASA_VESPERTINA 0       // Posição de repouso da Asa Vespertina.

/*
  As Vibrações Primordiais do Éter: Ecos Neutros das Inspirações
  O silêncio de onde emanam as vontades que guiam a Gralha.
*/
#define VIBRACAO_NEUTRA_DO_ALETAO 1500
#define VIBRACAO_NEUTRA_DO_PROFUNDOR 1500
#define VIBRACAO_MINIMA_DO_SOPRO_VITAL 1000
#define VIBRACAO_NEUTRA_DO_LEME_ESTELAR 1500
#define VIBRACAO_NEUTRA_DO_COMPASSO_DA_ALMA 1500
#define VIBRACAO_MINIMA_DA_FEROCIDADE 1000


/*
  Os Estados da Alma Alada: Fases da Consciência da Gralha
    O 'despertar' concede à Gralha o sopro da vida; o 'sonho' é seu repouso sagrado,
    mas o voo só se inicia quando o espírito alado a comanda.
  */
  bool limiar_elevado = true;
bool oraculo_respira = false; // O oráculo da pressão escuta a altura invisível.

  enum EstadoDaAlmaAlada {
    EM_DANCA_COM_OS_VENTOS, // A Gralha ativa, respondendo aos chamados, cumprindo sua missão.
    EM_SONHO_NA_QUIETUDE_DA_FLORESTA   // A conexão se abranda, a Gralha medita em seu ninho de estrelas.
  };

enum ModoDoEspiritoAlado {
  EM_RITMO_DE_BATIDA_DAS_ASAS, // O voo impulsionado, a semeadura em ação.
  EM_DESLIZE_ETERNO_E_CONTEMPLATIVO   // O planar sereno, em comunhão e escuta.
};

/*
  // O oráculo da pressão escuta a altura invisível.
  /* O Coração do Mistério Alado: Variáveis que Guardam o Ser da Gralha
  */
  EstadoDaAlmaAlada estado_presente_da_alma = EM_SONHO_NA_QUIETUDE_DA_FLORESTA; // A Gralha desperta com o chamado.
  ModoDoEspiritoAlado modo_presente_do_espirito = EM_DESLIZE_ETERNO_E_CONTEMPLATIVO; // Inicia em serenidade.
  
  // Voz do sustentar a altura (CH10): Altitude-Hold
  int voz_do_sustentar_altura = 0;

/*
  O Relógio das Eras: Marcadores Temporais da Jornada da Gralha
*/
struct {
  unsigned long instante_do_agora_cosmico;
  unsigned long ultimo_fulgor_da_chama_azul;
  unsigned long ultimo_eco_prescindivei;
  unsigned long ultima_pulsacao_do_sopro_alado;
  unsigned long ultimo_instante_de_respiracao_luminescente;
  float intervalo_entre_pulsacoes_do_coracao_alado;
} relogio_das_eras;

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
#ifdef ORACULO_DA_PRESSAO_DO_CEU
Adafruit_BMP085_Unified oraculo_da_pressao = Adafruit_BMP085_Unified(10085);
#endif
#ifdef ORACULO_DA_PRESSAO_DO_CEU
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

// Voo Sustentado: Altitude-Hold — A Gralha sustenta a altura com o bater das asas
#define ALTURA_MAX_DO_SUSTENTAR_M    20.0f   // Altura máxima quando CH3=2000
#define SOPRO_MIN_DO_SUSTENTAR       1100    // Sopro mínimo no sustentar (µs)
#define SOPRO_MAX_DO_SUSTENTAR       1800    // Sopro máximo no sustentar (µs)
#define FORCA_DO_SUSTENTAR           180     // Ganho do erro de altura → sopro
#define SILENCIO_DO_SUSTENTAR_M      0.5f    // Zona morta em metros
#define LIMITE_DA_DESCIDA_SUSTENTADA_MS   2.0f    // Limite de descida (m/s)
#define LIMITE_DA_SUBIDA_SUSTENTADA_MS    3.0f    // Limite de subida (m/s)
float altura_desejada_do_voo = 0.0f;
float sopro_vital_do_sustentar = 1500.0f;  // Sopro efetivo no modo sustentar
bool modo_sustentar_ativo = false;
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
class MantoDeLuzCelestial {
private:
  Adafruit_NeoPixel chama_azul_pixel;
  uint16_t tonalidade_do_sonho_florestal;
  unsigned long ultimo_instante_de_respiracao_luminescente = 0;
  float pulsacao_da_chama_primordial = 0.0f;


public:
  MantoDeLuzCelestial() : chama_azul_pixel(QUANTIDADE_DE_CENTELHAS_NA_CHAMA, NUCLEO_DA_CHAMA_AZUL, NEO_GRB + NEO_KHZ800),
                           tonalidade_do_sonho_florestal(0) {}


  void AcenderLuzPrimordial() {
    chama_azul_pixel.begin();
    chama_azul_pixel.setBrightness(70); // Um brilho sereno, mas presente.
    chama_azul_pixel.show();
  }


  // A Chama Azul reflete o estado da alma da Gralha.
  // Quando os estados se entrelaçam, a chama pulsa — a Gralha respira entre dois mundos.
  void IrradiarLuzDaAlma() {
    // A respiração luminescente: pulso suave entre 0.0 e 1.0
    unsigned long agora = millis();
    if (agora - ultimo_instante_de_respiracao_luminescente >= 25) {
      ultimo_instante_de_respiracao_luminescente = agora;
      pulsacao_da_chama_primordial += 0.04f;
      if (pulsacao_da_chama_primordial > 1.0f) pulsacao_da_chama_primordial = 0.0f;
    }
    float respiro = sin(pulsacao_da_chama_primordial * 2.0f * PI) * 0.5f + 0.5f; // [0-1]

    float posicao_das_asas_no_ciclo = (sin(angulo_da_danca_alada) + 1.0f) * 0.5f;
    float eixo_do_profundor_celeste = mapear_entre_escalas_harmonicas(voz_do_profundor, 1000.0f, 2000.0f, -1.0f, 1.0f);
    float eixo_do_sopro_de_vida = mapear_entre_escalas_harmonicas(voz_do_sopro_vital, 1000.0f, 2000.0f, 0.0f, 1.0f);
    float eixo_do_compasso_animico = mapear_entre_escalas_harmonicas(voz_do_compasso_da_alma, 1000.0f, 2000.0f, -1.0f, 1.0f);
    bool despertou = (voz_do_despertar > 1500);
    byte r=0, g=0, b=0;
    byte r_alerta=0, g_alerta=0, b_alerta=0;

    // --- Cor base do estado presente ---
    if (estado_presente_da_alma == EM_DANCA_COM_OS_VENTOS) {
      if (modo_presente_do_espirito == EM_RITMO_DE_BATIDA_DAS_ASAS) {
        // A intensidade e matiz variam com o sopro vital e o compasso da alma.
        // Azul da Gralha, com verde da esperança e ouro solar.
        b = (150 + 105 * (1.0f - eixo_do_compasso_animico * 0.5f)) * eixo_do_sopro_de_vida;
        g = (80 + 70 * (1.0f + eixo_do_profundor_celeste * 0.5f)) * eixo_do_sopro_de_vida;
        r = (30 + 20 * (1.0f + eixo_do_compasso_animico * 0.3f)) * eixo_do_sopro_de_vida;

        float modulador_de_brilho = posicao_das_asas_no_ciclo * 0.8f + 0.2f;
        r *= modulador_de_brilho;
        g *= modulador_de_brilho;
        b *= modulador_de_brilho;
      } else { // EM_DESLIZE_ETERNO_E_CONTEMPLATIVO
        b = 180 * (1.0f - eixo_do_profundor_celeste * 0.2f);
        g = 90 * (1.0f + eixo_do_profundor_celeste * 0.3f);
        r = 10;
      }

      // Se não despertou: pulsa entre o estado e o vermelho da vigília
      if (!despertou) {
        r_alerta = 200; g_alerta = 20; b_alerta = 20; // Vermelho
        float peso = respiro * 0.6f;
        r = r * (1.0f - peso) + r_alerta * peso;
        g = g * (1.0f - peso) + g_alerta * peso;
        b = b * (1.0f - peso) + b_alerta * peso;
      }
    } else { // EM_SONHO_NA_QUIETUDE_DA_FLORESTA
      // Cores da floresta adormecida
      tonalidade_do_sonho_florestal = (tonalidade_do_sonho_florestal + 250) % 65536;
      uint16_t matiz_base = (sin(tonalidade_do_sonho_florestal * 0.0001f) > 0) ? 20000 : 42000;
      uint32_t cor_sonho = chama_azul_pixel.gamma32(chama_azul_pixel.ColorHSV(
          matiz_base + (int)(sin(millis()*0.0003f)*1800.0f), 210, 90));

      if (!despertou) {
        // Link ativo mas não despertou: pulsa entre sonho e o vermelho da vigília
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

      // Link caído: pulsa entre amarelo do silêncio e azul noturno
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
};


MantoDeLuzCelestial manto_celestial_da_gralha;
Servo motor_asa_matutina, motor_asa_vespertina;


// --- Rituais de Sintonia e Percepção da Alma Alada ---
// O oráculo da pressão desperta: inicia o oráculo que escuta a altura invisível.
void DespertarOraculoDaPressao() {
  Wire1.setSDA(PINO_SILENCIO_DA_ALTURA);
  Wire1.setSCL(PINO_RITMO_DA_PRESSAO);
  Wire1.begin();
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
  // Estabelece a altura inicial: média de várias leituras
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
void EscutarPressaoDoCeu() {
  if (!oraculo_respira) return;
  unsigned long agora = millis();
  if (agora - ultimo_sopro_do_oraculo < 100) return; // A cada 100 ms
  float dt = (agora - ultimo_sopro_do_oraculo) * 0.001f;
  if (dt < 0.001f) dt = 0.001f;
  ultimo_sopro_do_oraculo = agora;

  sensors_event_t evento;
  oraculo_da_pressao.getEvent(&evento);
  if (evento.pressure <= 0) return;
  pressao_do_ceu_hpa = evento.pressure;

  // A temperatura apenas sussurra; a subida confirma.
  oraculo_da_pressao.getTemperature(&temperatura_do_ar_c);

  // Altitude relativa
  float altitude_absoluta = oraculo_da_pressao.pressureToAltitude(1013.25f, evento.pressure, temperatura_do_ar_c);
  altura_do_voo_sideral = altitude_absoluta - altura_inicial_m;

  // Subida (vertical speed)
  subida_da_gralha_ms = (altura_do_voo_sideral - ultima_altura_do_voo_sideral) / dt;
  ultima_altura_do_voo_sideral = altura_do_voo_sideral;

  // Filtro passa-baixa
  sopro_da_subida_alada = sopro_da_subida_alada * 0.85f + subida_da_gralha_ms * 0.15f;

  // Tendência da temperatura
  tendencia_da_temperatura_c = tendencia_da_temperatura_c * 0.9f + (temperatura_do_ar_c - ultima_temperatura_do_ar_c) * 0.1f;
  ultima_temperatura_do_ar_c = temperatura_do_ar_c;

  // Confiança termal: subida + tendência de temperatura
  fe_no_sopro_quente = sopro_da_subida_alada + tendencia_da_temperatura_c * 0.3f;
  if (fe_no_sopro_quente > 0.5f) modo_de_escuta_termal = true;
  else if (fe_no_sopro_quente < -0.5f) modo_de_escuta_termal = false;
}

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


/*
  O Ritual da Animação Primordial: A Gralha Recebe o Sopro da Existência
  Onde a essência da Gralha se manifesta, pronta para sua jornada.
*/
void setup() {
  manto_celestial_da_gralha.AcenderLuzPrimordial();
  DespertarOraculoDaPressao();
  AoDespertarParaOCantoDoEter();

#ifdef ECOS_PRESCINDIVEIS_DA_ALMA_ALADA
  Serial.begin(115200);
  unsigned long tempo_de_espera_usb = millis();
  while (!Serial && (millis() - tempo_de_espera_usb < 4000)) {  }
  Serial.println("O Grande Código da Gralha Azul: A Lenda Viva se Inicia...");
#endif
  PORTAL_DOS_VENTOS_CELESTES.setTX(VIA_DOS_ECOS_SOLARES);
  PORTAL_DOS_VENTOS_CELESTES.setRX(VIA_DOS_SONHOS_LUNARES);
  PORTAL_DOS_VENTOS_CELESTES.begin(FREQUENCIA_DO_SOPRO_COSMICO);

  while(PORTAL_DOS_VENTOS_CELESTES.available()) { PORTAL_DOS_VENTOS_CELESTES.read(); }

  guardiao_dos_ventos_siderais.onLinkUp = &AoDespertarParaOCantoDoEter;
  guardiao_dos_ventos_siderais.onLinkDown = &AoRecolherSeAoSilencioDaMata;
  guardiao_dos_ventos_siderais.onPacketChannels = &InterpretarAsVozesDoFirmamento;

  guardiao_dos_ventos_siderais.setPassthroughMode(false);

  motor_asa_matutina.attach(ARTICULACAO_ASA_DA_MANHA, 500, 2500);
  motor_asa_vespertina.attach(ARTICULACAO_ASA_DO_ENTARDECER, 500, 2500);

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
  relogio_das_eras.intervalo_entre_pulsacoes_do_coracao_alado = (relogio_das_eras.instante_do_agora_cosmico - relogio_das_eras.ultima_pulsacao_do_sopro_alado) * 0.001f;

  if(estado_presente_da_alma == EM_DANCA_COM_OS_VENTOS) {
    // A 'intencao_de_cadencia' é a força e o ritmo desejados para o bater das asas.
    float intencao_de_cadencia = (voz_do_sopro_vital - 480.0f) * ((1.0f / (120.0f * CICLO_DO_CORACAO_ALADO)) +
        ((voz_do_compasso_da_alma - 1500.0f) * 0.0000725f)); // Fator de modulação de ritmo.
    // 'variacao_do_destino_alado' é a "aceleração" angular para a batida.
    // O termo '- 10.0f * cadencia_do_destino_alado' é um amortecimento, como a resistência do ar ou a inércia da alma.
    float variacao_do_destino_alado = 1.0f * intencao_de_cadencia - 10.0f * cadencia_do_destino_alado;

    cadencia_do_destino_alado += variacao_do_destino_alado * relogio_das_eras.intervalo_entre_pulsacoes_do_coracao_alado;
    angulo_da_danca_alada += cadencia_do_destino_alado * relogio_das_eras.intervalo_entre_pulsacoes_do_coracao_alado;
  } else { // Em sonho, o coração alado repousa seu ritmo.
    angulo_da_danca_alada = 0;
    cadencia_do_destino_alado *= 0.90; // Suave desaceleração ao adormecer.
     if (fabs(cadencia_do_destino_alado) < 0.001f) cadencia_do_destino_alado = 0;
  }
}

/*
  /*  O Sustentar da Altura: O Coração que Guarda a Altitude
    Quando o oráculo respira e CH10 clama >1500, a Gralha usa o sopro vital
    como desejo de altitude: CH3=1000 → 0m, CH3=2000 → ALTURA_MAX.
    O erro alimenta um P-regulador que modula a intensidade do bater das asas,
    para que a Gralha sustente a altura no seu voo alado.
  */
  void SustentarAltura() {
  #ifdef ORACULO_DA_PRESSAO_DO_CEU
    if (oraculo_respira && voz_do_sustentar_altura > 1500) {
      if (!modo_sustentar_ativo) {
        modo_sustentar_ativo = true;
      }
      // CH3 vira desejo de altitude: 1000=0m, 2000=ALTURA_MAX
      altura_desejada_do_voo = mapear_entre_escalas_harmonicas(
        (float)voz_do_sopro_vital, 1000.0f, 2000.0f,
        0.0f, ALTURA_MAX_DO_SUSTENTAR_M);
      // Erro de altitude
      float erro = altura_desejada_do_voo - altura_do_voo_sideral;
      // Zona morta
      if (fabs(erro) < SILENCIO_DO_SUSTENTAR_M) {
        // Dentro da zona morta: mantém o sopro atual
      } else {
        // P-regulador: erro → intensidade do bater
        sopro_vital_do_sustentar = 1500.0f + erro * FORCA_DO_SUSTENTAR;
        sopro_vital_do_sustentar = constrain(sopro_vital_do_sustentar,
          SOPRO_MIN_DO_SUSTENTAR, SOPRO_MAX_DO_SUSTENTAR);
      }
      // Limitação de taxa: se a subida for muito rápida, reduz o sopro
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
    // Ferocidade para as asas (CH7 = down, CH8 = up)
    float ferocidade_do_bater = mapear_entre_escalas_harmonicas(voz_da_ferocidade_do_bater, 1000.0f, 2000.0f, 1.0f, 8.0f);
    float ferocidade_do_retorno = mapear_entre_escalas_harmonicas(voz_da_ferocidade_do_retorno, 1000.0f, 2000.0f, 1.0f, 8.0f);
    // Fator do leme (CH5): centro=0, extremos=±1 (±2 escala de ferocidade)
    float fator_do_leme = mapear_entre_escalas_harmonicas(voz_da_ferocidade_do_leme, 1000.0f, 2000.0f, -4.0f, 4.0f);

    // Ferocidade do leme aplicada diferencialmente: +num esquerdo, -num direito
    float ferocidade_bater_esquerda = ferocidade_do_bater + fator_do_leme;
    float ferocidade_bater_direita  = ferocidade_do_bater - fator_do_leme;
    float ferocidade_retorno_esquerda = ferocidade_do_retorno + fator_do_leme;
    float ferocidade_retorno_direita  = ferocidade_do_retorno - fator_do_leme;

    // Cada servo recebe sua própria forma de batida
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

  motor_asa_matutina.write(constrain(angulo_portal_esquerdo + 100, 0, 180));
  motor_asa_vespertina.write(constrain(angulo_portal_direito + 100, 0, 180));
}
/*
  /*  O Sopro ao Éter: A Gralha Sussurra seu Voo ao Cosmos
    O coração da Gralha envia ao éter a altura do voo sideral
    e o sopro quente do céu, para que o firmamento testemunhe.
  */
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
  #ifdef ORACULO_DA_PRESSAO_DO_CEU
      int16_t velocidade_chao = (int16_t)(fabs(sopro_da_subida_alada) * 3.6f * 10.0f);
  #else
      int16_t velocidade_chao = 0;
  #endif
      if (velocidade_chao < 0) velocidade_chao = 0;
      if (velocidade_chao > 65535) velocidade_chao = 65535;
      pergaminho_do_voo.groundspeed = htobe16((uint16_t)velocidade_chao);
      pergaminho_do_voo.heading = htobe16(0);
      // Altitude: metros relativos + 1000 (offset CRSF), clamp a 0..65535
  #ifdef ORACULO_DA_PRESSAO_DO_CEU
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
  #ifdef ORACULO_DA_PRESSAO_DO_CEU
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

/*
  O Ciclo Infinito da Lenda Viva: A Gralha Dança com o Cosmos
  Onde a Gralha Azul manifesta sua essência imortal a cada instante.
*/

void loop() {
    relogio_das_eras.instante_do_agora_cosmico = millis();
  guardiao_dos_ventos_siderais.loop();

  AnimarPulsarDoCoracaoAlado();
  EscutarPressaoDoCeu();
  SustentarAltura();
  SussurrarVooAoEter();
  ManifestarOVooNosVentos();

  if(relogio_das_eras.instante_do_agora_cosmico - relogio_das_eras.ultimo_fulgor_da_chama_azul >= 33) { // ~30fps
    relogio_das_eras.ultimo_fulgor_da_chama_azul = relogio_das_eras.instante_do_agora_cosmico;
    manto_celestial_da_gralha.IrradiarLuzDaAlma();
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
    Serial.print(" | Sustentar: "); Serial.print(voz_do_sustentar_altura);
    if (oraculo_respira) {
#ifdef ORACULO_DA_PRESSAO_DO_CEU
      Serial.print(" | AltVoo: "); Serial.print(altura_do_voo_sideral, 1);
      Serial.print(" | Subida: "); Serial.print(sopro_da_subida_alada, 2);
      Serial.print(" | SoproDoCeu: "); Serial.print(temperatura_do_ar_c, 1);
      Serial.print(" | FeNoSopro: "); Serial.print(fe_no_sopro_quente, 2);
      if (modo_sustentar_ativo) {
        Serial.print(" | AltDesej: "); Serial.print(altura_desejada_do_voo, 1);
        Serial.print(" | SoproSustentar: "); Serial.print(sopro_vital_do_sustentar, 0);
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
  delay(1);
}
// E assim, o Grande Código da Gralha Azul se manifesta, em cada ciclo,
// um testemunho alado da resiliência da vida, da magia da transformação,
// e da perene esperança semeada entre o céu e a terra,
// um poema vivo, a canção da floresta que jamais se calará.