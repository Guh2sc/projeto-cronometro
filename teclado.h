/*******************************************************************************
  * File Name          : teclado.h
  * Processador        : MSP430F149
  * Autores            : Gustavo Santos and Emanuel Rocha
  ******************************************************************************
  * Descrição          : 
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _TECLADO_H
#define _TECLADO_H //previne dupla inclusao da biblioteca

/* Includes ------------------------------------------------------------------*/
#include "io430.h"

/* Private defines -----------------------------------------------------------*/
 #define COLUNAS_DIR   P2DIR
 #define COLUNAS       P2IN
 #define LINHAS_DIR    P6DIR
 #define LINHAS        P6OUT 
 #define BITS_LINHA    BIT4+BIT5+BIT6+BIT7
 #define BITS_COLUNA   BIT0+BIT1+BIT2

/* Prototypes ----------------------------------------------------------------*/
void configura_teclado(void);
unsigned char teclado(void);
#endif
