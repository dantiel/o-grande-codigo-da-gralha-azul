/*
  O Grande Código da Gralha Azul — Valores Padrão Internos
*/

#ifndef GRALHA_AZUL_PADRAOS_H
#define GRALHA_AZUL_PADRAOS_H

/* — Articulações das Asas — */
#define ARTICULACAO_ASA_DA_MANHA_PADRAO        8
#define ARTICULACAO_ASA_DO_ENTARDECER_PADRAO   7

/* — O Guardião e o Mensageiro dos Ventos — */
// MENSAGEIRO_DOS_CANTOS_COSMICOS: definir PORTAL_DOS_CANTOS_COSMICOS e NUMERO_DE_CANTOS no sketch
// GUARDIAO_DOS_VENTOS_SIDERAIS: definir VIA_DOS_SONHOS_LUNARES, VIA_DOS_ECOS_SOLARES, FREQUENCIA_DO_SOPRO_COSMICO

/* — A Via do Sopro Cósmico — */
#define VIA_DO_SOPRO_COSMICO_PADRAO                    Serial1
#define VIA_DOS_SONHOS_LUNARES_PADRAO          1    /* entrada dos sonhos */
#define VIA_DOS_ECOS_SOLARES_PADRAO            0    /* saída dos ecos */
#define FREQUENCIA_DO_SOPRO_COSMICO_PADRAO     420000

/* — O Núcleo da Chama Azul — */
#define NUCLEO_DA_CHAMA_AZUL_PADRAO            16
#define QUANTIDADE_DE_CENTELHAS_PADRAO         1

/* — Geometria do Voo — */
#define CICLO_DO_CORACAO_ALADO_PADRAO          0.070f
#define LIMIAR_DO_VOO_ATIVO_PADRAO             1040
#define ANGULO_DO_PLANAR_SERENO_PADRAO         -4

/* — Escalas de Movimento — */
#define ESCALA_ANGULAR_DA_ARTICULACAO_PADRAO   0.04f
#define ESCALA_ANGULAR_DO_PROFUNDOR_PADRAO     0.06f
#define MAGNITUDE_ESCALA_DA_FEROCIDADE_PADRAO  0.06f
#define MULTIPLICADOR_FINAL_ANGULAR_PADRAO     2.0f
#define OFFSET_ANGULAR_NEUTRO_PADRAO           100

/* — Ferocidade — */
#define FEROCIDADE_MINIMA_PADRAO               1.0f
#define FEROCIDADE_MAXIMA_PADRAO               8.0f

/* — Diferencial do Leme — */
#define DIFERENCIAL_LEME_MIN_PADRAO            -4.0f
#define DIFERENCIAL_LEME_MAX_PADRAO            4.0f

/* — Compasso e Cadência — */
#define MODULACAO_DO_COMPASSO_PADRAO           0.0003f
#define ACELERACAO_DO_COMPASSO_PADRAO          8.0f
#define DECAIMENTO_DA_CADENCIA_SONOLENTA_PADRAO 0.90f
#define EPSILON_CADENCIA_ZERO_PADRAO           0.001f

/* — Altitude Hold — */
#define FORCA_BASE_DO_SUSTENTAR_PADRAO         30
#define AMORTECIMENTO_DO_ERRO_SUSTENTAR_PADRAO 0.1f
#define SILENCIO_DO_SUSTENTAR_M_PADRAO         0.5f
#define SOPRO_MIN_DO_SUSTENTAR_PADRAO          1000
#define SOPRO_MAX_DO_SUSTENTAR_PADRAO          2000
#define TAXA_DE_SUBIDA_PROGRESSIVA_PADRAO      50.0f
#define LIMITE_DA_SUBIDA_SUSTENTADA_PADRAO     5.0f
#define CORRECAO_DA_TAXA_LIMITE_SUSTENTAR_PADRAO  10.0f
#define LIMITE_DA_DESCIDA_SUSTENTADA_PADRAO    -5.0f
#define GANHO_LIMIAR_SUSTENTAR_PADRAO          0.1f
#define ALTURA_MAX_DO_SUSTENTAR_M_PADRAO       20

/* — A Origem das Asas — */
#define ORIGEM_ASA_MATUTINA_PADRAO             0
#define ORIGEM_ASA_VESPERTINA_PADRAO           0

/* — Os Limites dos Tendões Alados — */
#define PULSO_MINIMO_SERVO_PADRAO              500
#define PULSO_MAXIMO_SERVO_PADRAO              2500

/* — Frequência / Animação — */
#define DT_MAXIMO_DO_SONHO_PADRAO              0.1f
#define MULTIPLICADOR_MINIMO_FREQUENCIA_PADRAO 0.5f
#define PESO_DO_SOPRO_NA_FREQUENCIA_PADRAO     0.5f
#define PESO_DO_COMPASSO_NA_FREQUENCIA_PADRAO  0.3f
#define LIMITE_ANGULAR_DO_GIRO_PADRAO          6.283185307f

/* — O Oráculo da Pressão — */
#define SILENCIO_DA_ALTURA_PADRAO              4
#define RITMO_DA_PRESSAO_PADRAO                5
#define AMOSTRAS_DE_CALIBRACAO_PADRAO          10
#define REFERENCIA_DA_PRESSAO_PADRAO           1013.25f
#define ATRASO_DE_CALIBRACAO_PADRAO            50
#define INTERVALO_DE_LEITURA_PADRAO            20
#define SALTOS_DO_CICLO_TERMICO_PADRAO         10
#define SUAVIZACAO_TERMICA_PADRAO              0.5f
#define FILTRO_DE_TENDENCIA_PADRAO             0.9f
#define PESO_DA_TENDENCIA_PADRAO               0.1f
#define EXPONENTE_DA_FORMULA_PADRAO            0.190284f
#define CONSTANTE_DA_FORMULA_PADRAO            44330.0f
#define PESO_DA_SUBIDA_ATUAL_PADRAO            0.7f
#define PESO_DA_SUBIDA_PASSADA_PADRAO          0.3f
#define PESO_DA_CONFIANCA_TERMICA_PADRAO       0.5f
#define LIMIAR_DE_CONFIANCA_PADRAO             0.5f

/* — Intervalos de Sopro — */
#define INTERVALO_DO_GUARDIAO_LUMINAR_PADRAO     1000
#define INTERVALO_DO_ORACULO_TERMICO_PADRAO      1000
#define INTERVALO_DA_CHAMA_AZUL_PADRAO           50
#define INTERVALO_DOS_ECOS_PADRAO              1000

/* — Cadência da Comunicação — */
#define RITMO_DA_COMUNICACAO_PADRAO            115200

/* — Constantes matemáticas — */
#define EPSILON_FORMA_BATER_PADRAO             0.000001f
#define LIMITE_FORMA_BATER_PADRAO              1.0f
#define MINIMO_DT_SEGUNDOS_PADRAO              0.000001f

#endif /* GRALHA_AZUL_PADRAOS_H */