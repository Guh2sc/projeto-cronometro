/*******************************************************************************
  * File Name          : lcd.h
  * Processador        : MSP430F149
  * Autores            : Gustavo Santos and Emanuel Rocha
  ******************************************************************************
  * Descrição          : 
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _LCD_H
#define _LCD_H //previne dupla inclusao da biblioteca

/* Includes ------------------------------------------------------------------*/
#include "io430.h"

/* Private defines -----------------------------------------------------------*/
 #define LCM_DADO_DIR    P5DIR
 #define LCM_DADO_OUT    P5OUT
 #define LCM_CTL_DIR     P3DIR
 #define LCM_CTL_OUT     P3OUT
 #define TEMPO_CONFIG    20000
 #define TEMPO           120000

//Definição dos bits e da máscara de envio para o LCD
#define RS      BIT7
#define EN      BIT6

/* Prototypes ----------------------------------------------------------------*/
void configura_LCM(void);
void envia_comando(char);
void envia_dado(char);
void envia_string(const char *);
char tamanho_string(const char *);
void rotaciona_string( const char *);
void programa_LCM(void);
#endif

