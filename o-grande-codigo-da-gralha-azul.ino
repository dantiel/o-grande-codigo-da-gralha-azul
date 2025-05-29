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
#define ECOS_PRESCINDIVEIS_DA_ALMA_ALADA // Se definido, a Gralha partilha seus estados (Debug).
#define FREQUENCIA_DO_SOPRO_COSMICO 115200 // O ritmo da comunicação com o éter.
#define PORTAL_DOS_VENTOS_CELESTES Serial1  // O limiar por onde as influências astrais tocam a Gralha.

#include <CrsfSerial.h> 
// O Guardião dos Ventos Siderais, intérprete dos desígnios para a Gralha.
CrsfSerial guardiao_dos_ventos_siderais(PORTAL_DOS_VENTOS_CELESTES, FREQUENCIA_DO_SOPRO_COSMICO);

#include <Servo.h> // A arte ancestral de animar os tendões de luz.
#include <Adafruit_NeoPixel.h> // O encanto para acender a chama da alma.

/* As Relíquias da Gralha: Vínculos de Poder e Essência
  Os pontos de contato com o mundo, ecos da sua jornada.
*/
#define ARTICULACAO_ASA_MATUTINA 7    // Asa que se ergue com a aurora.
#define ARTICULACAO_ASA_VESPERTINA 5 // Asa que se recolhe com o crepúsculo.
#define VIA_DOS_SONHOS_LUNARES 1    // Canal dos sussurros da noite (CRSF RX).
#define VIA_DOS_ECOS_SOLARES 0  // Canal da canção ao dia (CRSF TX).
#define NUCLEO_DA_CHAMA_AZUL 16    // Onde a alma da Gralha brilha, sua essência anil.
#define QUANTIDADE_DE_CENTELHAS_NA_CHAMA 1 // Uma única, mas intensa, luz interior.

/*
  Os Mistérios do Voo Sagrado: Leis Imutáveis da Natureza Alada
  Verdades primordiais, a essência do voo e da missão da Gralha.
*/
#define CICLO_DO_CORACAO_ALADO 0.052f // A pulsação rítmica do voo, como a respiração da mata.
#define LIMIAR_DO_VOO_ATIVO 1040      // O ímpeto para o bater das asas, a dança da vida.
#define ANGULO_DO_PLANAR_SERENO -11   // Postura de escuta, em comunhão com os ventos.
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

/*
  Os Estados da Alma Alada: Fases da Consciência da Gralha
  A Gralha responde ao cosmos, seu ser uma manifestação da lenda.
*/
enum EstadoDaAlmaAlada { 
  EM_DANCA_COM_OS_VENTOS, // A Gralha ativa, respondendo aos chamados, cumprindo sua missão.
  EM_SONHO_NA_QUIETUDE_DA_FLORESTA   // A conexão se abranda, a Gralha medita em seu ninho de estrelas.
};

enum ModoDoEspiritoAlado { 
  EM_RITMO_DE_BATIDA_DAS_ASAS, // O voo impulsionado, a semeadura em ação.
  EM_DESLIZE_ETERNO_E_CONTEMPLATIVO   // O planar sereno, em comunhão e escuta.
};

/*
  O Coração do Mistério Alado: Variáveis que Guardam o Ser da Gralha
*/
volatile EstadoDaAlmaAlada estado_presente_da_alma = EM_SONHO_NA_QUIETUDE_DA_FLORESTA; // A Gralha desperta com o chamado.
ModoDoEspiritoAlado modo_presente_do_espirito = EM_DESLIZE_ETERNO_E_CONTEMPLATIVO; // Inicia em serenidade.

/*
  O Relógio das Eras: Marcadores Temporais da Jornada da Gralha
*/
struct {
  unsigned long instante_do_agora_cosmico;
  unsigned long ultimo_fulgor_da_chama_azul;
  unsigned long ultima_pulsacao_do_sopro_alado;
  float intervalo_entre_pulsacoes_do_coracao_alado;
} relogio_das_eras;

/*
  As Vozes do Céu: Inspirações que Moldam o Destino da Gralha
*/
volatile int voz_do_aletao = VIBRACAO_NEUTRA_DO_ALETAO;
volatile int voz_do_profundor = VIBRACAO_NEUTRA_DO_PROFUNDOR;
volatile int voz_do_sopro_vital = VIBRACAO_MINIMA_DO_SOPRO_VITAL;
volatile int voz_do_leme_estelar = VIBRACAO_NEUTRA_DO_LEME_ESTELAR;
volatile int voz_do_compasso_da_alma = VIBRACAO_NEUTRA_DO_COMPASSO_DA_ALMA;

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
float mapear_entre_escalas_harmonicas(float valor, float min_origem, float max_origem, float min_destino, float max_destino) {
  return (valor - min_origem) * (max_destino - minimo_destino) / (max_origem - minimo_origem) + minimo_destino;
}

/*
  O Manto de Luz Celestial: A Irradiação da Chama Azul da Alma
  Um espelho do estado e da missão da Gralha.
*/
class MantoDeLuzCelestial {
private:
  Adafruit_NeoPixel chama_azul_pixel;
  uint16_t tonalidade_do_sonho_florestal;

public:
  MantoDeLuzCelestial() : chama_azul_pixel(QUANTIDADE_DE_CENTELHAS_NA_CHAMA, NUCLEO_DA_CHAMA_AZUL, NEO_GRB + NEO_KHZ800),
                           tonalidade_do_sonho_florestal(0) {}

  void AcenderLuzPrimordial() { 
    chama_azul_pixel.begin(); 
    chama_azul_pixel.setBrightness(70); // Um brilho sereno, mas presente.
    chama_azul_pixel.show();
  }

  // A Chama Azul reflete o estado da alma da Gralha.
  void IrradiarLuzDaAlma() {
    float posicao_das_asas_no_ciclo = (sin(angulo_da_danca_alada) + 1.0f) * 0.5f; // [0-1]
    float eixo_do_profundor_celeste = mapear_entre_escalas_harmonicas(voz_do_profundor, 1000.0f, 2000.0f, -1.0f, 1.0f);
    float eixo_do_compasso_animico = mapear_entre_escalas_harmonicas(voz_do_compasso_da_alma, 1000.0f, 2000.0f, -1.0f, 1.0f);
    float eixo_do_sopro_de_vida = mapear_entre_escalas_harmonicas(voz_do_sopro_vital, 1000.0f, 2000.0f, 0.0f, 1.0f);
    byte r=0, g=0, b=0;

    if (estado_presente_da_alma == EM_DANCA_COM_OS_VENTOS) {
      if (modo_presente_do_espirito == EM_RITMO_DE_BATIDA_DAS_ASAS) {
        // Azul da Gralha, com toques de verde (esperança/floresta) e um brilho solar (força).
        // A intensidade e matiz variam com o sopro vital e o compasso da alma.
        b = (150 + 105 * (1.0f - eixo_do_compasso_animico * 0.5f)) * eixo_do_sopro_de_vida;
        g = (80 + 70 * (1.0f + eixo_do_profundor_celeste * 0.5f)) * eixo_do_sopro_de_vida;
        r = (30 + 20 * (1.0f + eixo_do_compasso_animico * 0.3f)) * eixo_do_sopro_de_vida;
        
        // O pulsar das asas modula o brilho.
        float modulador_de_brilho = posicao_das_asas_no_ciclo * 0.8f + 0.2f; // Evita apagar totalmente.
        r *= modulador_de_brilho;
        g *= modulador_de_brilho;
        b *= modulador_de_brilho;
      } else { // EM_DESLIZE_ETERNO_E_CONTEMPLATIVO
        // Azul mais suave e sereno, com toques de verde, como o céu refletido na mata.
        b = 180 * (1.0f - eixo_do_profundor_celeste * 0.2f);
        g = 90 * (1.0f + eixo_do_profundor_celeste * 0.3f);
        r = 10; // Um leve toque quente.
      }
    } else { // EM_SONHO_NA_QUIETUDE_DA_FLORESTA
      // Um ciclo suave de cores da floresta adormecida, verdes e azuis noturnos.
      tonalidade_do_sonho_florestal = (tonalidade_do_sonho_florestal + 250) % 65536; // Ciclo suave.
      uint16_t matiz_base = (sin(tonalidade_do_sonho_florestal * 0.0001f) > 0) ? 20000 : 42000; // Alterna verdes e azuis.
      chama_azul_pixel.setPixelColor(0, chama_azul_pixel.gamma32(chama_azul_pixel.ColorHSV(matiz_base + (int)(sin(millis()*0.0003f)*1800.0f) , 210, 90)));
      chama_azul_pixel.show(); // Mostra cor HSV e retorna.
      return;
    }

    chama_azul_pixel.setPixelColor(0, constrain(r,0,255), constrain(g,0,255), constrain(b,0,255));
    chama_azul_pixel.show();
  }
};

MantoDeLuzCelestial manto_celestial_da_gralha;
Servo motor_asa_matutina, motor_asa_vespertina;

// --- Rituais de Sintonia e Percepção da Alma Alada ---
void AoDespertarParaOCantoDoEter() { 
  estado_presente_da_alma = EM_DANCA_COM_OS_VENTOS;
#ifdef ECOS_PRESCINDIVEIS_DA_ALMA_ALADA
  Serial.println("A Gralha desperta, atenta aos ventos cósmicos!");
#endif
}

void AoRecolherSeAoSilencioDaMata() { 
  estado_presente_da_alma = EM_SONHO_NA_QUIETUDE_DA_FLORESTA;
  modo_presente_do_espirito = EM_DESLIZE_ETERNO_E_CONTEMPLATIVO; // Em sonho, sempre serena.
#ifdef ECOS_PRESCINDIVEIS_DA_ALMA_ALADA
  Serial.println("O éter silencia. A Gralha retorna ao seu sonho na floresta.");
#endif
}

void InterpretarAsVozesDoFirmamento() { 
  voz_do_aletao = mensageiro_dos_ventos_cosmicos.getChannel(1);
  voz_do_profundor = mensageiro_dos_ventos_cosmicos.getChannel(2);
  voz_do_sopro_vital = mensageiro_dos_ventos_cosmicos.getChannel(3);
  voz_do_leme_estelar = mensageiro_dos_ventos_cosmicos.getChannel(4);
  voz_do_compasso_da_alma = mensageiro_dos_ventos_cosmicos.getChannel(6); 
}

/*
  O Ritual da Animação Primordial: A Gralha Recebe o Sopro da Existência
  Onde a essência da Gralha se manifesta, pronta para sua jornada.
*/
void setup() {
  manto_celestial_da_gralha.AcenderLuzPrimordial(); 
  
  mensageiro_dos_ventos_cosmicos.onLinkUp = &AoDespertarParaOCantoDoEter;
  mensageiro_dos_ventos_cosmicos.onLinkDown = &AoRecolherSeAoSilencioDaMata;
  mensageiro_dos_ventos_cosmicos.onPacketChannels = &InterpretarAsVozesDoFirmamento;
  
  Serial1.setRX(VIA_DOS_SONHOS_LUNARES);
  Serial1.setTX(VIA_DOS_ECOS_SOLARES);
  PORTAL_DOS_VENTOS_CELESTES.begin(FREQUENCIA_DO_SOPRO_COSMICO);
  mensageiro_dos_ventos_cosmicos.setPassthroughMode(false);

#ifdef ECOS_PRESCINDIVEIS_DA_ALMA_ALADA
  Serial.begin(115200); 
  Serial.println("O Grande Código da Gralha Azul: A Lenda Viva se Inicia...");
#endif

  motor_asa_matutina.attach(ARTICULACAO_ASA_DA_MANHA);
  motor_asa_vespertina.attach(ARTICULACAO_ASA_DO_ENTARDECER);
  
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
     if (abs(cadencia_do_destino_alado) < 0.001) cadencia_do_destino_alado = 0;
  }
}

/*
  O Movimento dos Portais Alados: Manifestando o Voo da Gralha
  Traduz a dinâmica interna e as inspirações celestes em movimento físico.
  Este é o 'MoverPortais' da essência da Gralha.
*/
void ManifestarOVooNosVentos() {
  float comando_aletao = (voz_do_aletao - 1500.0f) * 0.04f;
  float comando_profundor = (voz_do_profundor - 1500.0f) * 0.04f;
  float fator_leme_sutil = ((1500.0f / voz_do_leme_estelar) - 1.0f) * 2.0f + 1.0f; 
  
  int angulo_portal_esquerdo, angulo_portal_direito;
  
  if(modo_presente_do_espirito == EM_RITMO_DE_BATIDA_DAS_ASAS) {
    // A 'magnitude_da_batida' é a força com que a Gralha impulsiona o ar.
    float magnitude_da_batida = ((voz_do_sopro_vital - LIMIAR_DO_VOO_ATIVO) * 0.06f) * (1.0f - (voz_do_compasso_da_alma - 1500.0f) * 0.0003f);
    // O 'pulso_do_sopro_vital' é o coração senoidal do movimento.
    pulso_do_sopro_vital = sin(angulo_da_danca_alada);

    float graus_do_movimento_alado = magnitude_da_batida * pulso_do_sopro_vital;
    
    angulo_portal_esquerdo = (int)((comando_aletao - (graus_do_movimento_alado * fator_leme_sutil) + ORIGEM_ASA_MATUTINA - comando_profundor) * 2.0f);
    angulo_portal_direito  = (int)((comando_aletao + (graus_do_movimento_alado / fator_leme_sutil) + ORIGEM_ASA_VESPERTINA + comando_profundor) * 2.0f);
  } else { // EM_DESLIZE_ETERNO_E_CONTEMPLATIVO
    angulo_portal_esquerdo = (int)((comando_aletao - ANGULO_DO_PLANAR_EM_ESCUTA + ORIGEM_ASA_MATUTINA - comando_profundor) * 2.0f);
    angulo_portal_direito  = (int)((comando_aletao + ANGULO_DO_PLANAR_EM_ESCUTA + ORIGEM_ASA_VESPERTINA + comando_profundor) * 2.0f);
  }

  motor_asa_matutina.write(constrain(angulo_portal_esquerdo + 100, 0, 180));
  motor_asa_vespertina.write(constrain(angulo_portal_direito + 100, 0, 180));
}

/*
  O Ciclo Infinito da Lenda Viva: A Gralha Dança com o Cosmos
  Onde a Gralha Azul manifesta sua essência imortal a cada instante.
*/
void loop() {
  relogio_das_eras.instante_do_agora_cosmico = millis();
  mensageiro_dos_ventos_cosmicos.loop(); 
  
  if(estado_presente_da_alma == EM_DANCA_COM_OS_VENTOS) {
    // A Gralha bate as asas se o sopro vital (acelerador) for forte o suficiente.
    modo_presente_do_espirito = (voz_do_sopro_vital > LIMIAR_DO_VOO_ATIVO) ? EM_RITMO_DE_BATIDA_DAS_ASAS : EM_DESLIZE_ETERNO_E_CONTEMPLATIVO;
  } else {
    modo_presente_do_espirito = EM_DESLIZE_ETERNO_E_CONTEMPLATIVO; // Em sonho, sempre serena.
  }

  AnimarPulsarDoCoracaoAlado(); 
  ManifestarOVooNosVentos(); 
  
  if(relogio_das_eras.instante_do_agora_cosmico - relogio_das_eras.ultimo_fulgor_da_chama_azul >= 33) { // ~30fps
    relogio_das_eras.ultimo_fulgor_da_chama_azul = relogio_das_eras.instante_do_agora_cosmico;
    manto_celestial_da_gralha.IrradiarLuzDaAlma(); 
  }

#ifdef ECOS_PRESCINDIVEIS_DA_ALMA_ALADA
    Serial.print(estado_presente_da_alma == EM_DANCA_COM_OS_VENTOS ? "VOANDO" : "SONHANDO");
    Serial.print(" | Modo: ");
    Serial.print(modo_presente_do_espirito == EM_RITMO_DE_BATIDA_DAS_ASAS ? "RITMADO" : "PLANANDO");
    Serial.print(" | SoproV: "); Serial.print(voz_do_sopro_vital);
    // Serial.print(" | Alet: "); Serial.print(voz_do_aletao);
    // Serial.print(" | Prof: "); Serial.print(voz_do_profundor);
    // Serial.print(" | Leme: "); Serial.print(voz_do_leme_estelar);
    Serial.print(" | Compasso: "); Serial.print(voz_do_compasso_da_alma);
    Serial.print(" | FaseDanca: "); Serial.print(angulo_da_danca_alada, 2);
    // Serial.print(" | Cadencia: "); Serial.print(cadencia_do_destino_alado, 2);
    Serial.println();
#endif
  relogio_das_eras.ultima_pulsacao_do_sopro_alado = relogio_das_eras.instante_do_agora_cosmico;
}
// E assim, o Grande Código da Gralha Azul se manifesta, em cada ciclo,
// um testemunho alado da resiliência da vida, da magia da transformação,
// e da perene esperança semeada entre o céu e a terra,
// um poema vivo, a canção da floresta que jamais se calará.
