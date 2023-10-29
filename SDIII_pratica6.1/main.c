#include "io430.h"
#include "teclado.h"
#include "lcd.h"
#define DESLOCAMENTO    4 // Define o valor de deslocamento para o cursor no display LCD
#define TEMPORIZACAO    1 // Define o valor de temporização para algum propósito específico

unsigned char us='0', ds='0', um='0', dm='0', uh='0', dh='0'; 
/*
us: unidade de segundo
ds: dezena de segundo
um: unidade de minuto
dm: dezena de minuto
uh: unidade de hora
dh: dezena de hora
*/

void cronometro(unsigned char PI, unsigned char reset)
{ 
  envia_comando((PI + 7));
  
  // Reseta todos os contadores se a tecla de reset estiver ativada
  if(reset == 1)
  {
    us = '0';
    ds = '0';
    um = '0';    
    dm = '0';     
    uh = '0';     
    dh = '0';
  }
  
  // Verifica o valor máximo de tempo
  if(dh == '2' && (uh == '3') && (dm == '5') && (um == '9') && (ds == '5') && (us == '9'))
  {
  }
  else
  {
    if(us >= '9')
    {
      // Trabalha com a unidade de segundos
      if(ds == '5' && us == '9')
      {
        // Pula o incremento da unidade de segundos
      }
      else
      {
        us = '0';
        envia_dado(us);
        envia_comando(PI + 6);
      }
      
      // Trabalha com a dezena de segundos
      if((ds >= '5') || (ds == '5' && us == '9'))
      {    
        us = '0';
        envia_dado(us);
        envia_comando(PI + 6);
        ds = '0';
        envia_dado(ds);
        envia_comando(PI + 4);

        // Trabalha com a unidade de minutos
        if(um >= '9')
        {
          um = '0';
          envia_dado(um);
          envia_comando(PI + 3);

          // Trabalha com a dezena de minutos
          if((dm >= '5') || (dm == '5' && um == '9'))
          {
            dm = '0';
            envia_dado(dm);
            envia_comando(PI + 1);

            // Trabalha com a unidade de horas
            if((dh == '2') && (uh == '3'))
            {
              // Pula o incremento da hora
            }
            else
            {
              // Trabalha com a unidade de horas
              if(uh >= '9')
              {
                uh = '0';
                envia_dado(uh);
                envia_comando(PI);
                if(dh < '2')
                {
                  __delay_cycles(TEMPORIZACAO);
                  dh++;
                  envia_dado(dh);
                  envia_comando(PI);
                }
                else
                {
                  //Pula o incremento da hora
                }
              }
              else
              {
                __delay_cycles(TEMPORIZACAO);
                uh++;
                envia_dado(uh);
              }
            }
          }
          else
          {
            __delay_cycles(TEMPORIZACAO);
            dm++;
            envia_comando(PI + 3);
            envia_dado(dm);
          }
        }
        else
        {
          if(dm == '5' && um == '9')
          {
            // Pula o incremento do minuto
          }
          else
          {
            __delay_cycles(TEMPORIZACAO);
            um++;
            envia_comando(PI + 4);
            envia_dado(um);                 
          }
        }
      }
      else
      {
        __delay_cycles(TEMPORIZACAO);
        ds++;
        envia_dado(ds);
      }
    }
    else
    {
      if(ds == '5' && us == '9')
      {
       //Pula o incremento do segundo
      }
      else
      {
        __delay_cycles(TEMPORIZACAO);
        us++;
        envia_dado(us);
      }
    }
  }
 
  PI = (0xC0 + DESLOCAMENTO); // Atualiza o indicador de posição e exibe
  envia_comando(PI);
}

void zera_cronometro(unsigned char PI)
{
  unsigned char limite = 8; // Define o limite de dígitos que são (horas, minutos e segundos)
  while(limite != 0) // Loop para preencher os dígitos do cronômetro com zeros
  {  
    if((limite == 3) || (limite == 6)) // Verifica se o limite atual corresponde a um dos pontos de separação (':')
      envia_dado(':'); // Envia o caractere ':' para separar as unidades 
    else
      envia_dado('0'); // Envia o caractere '0' para preencher as unidades de tempo com zeros
    limite--; // subtraí o limite para mover para o próximo dígito
    PI++; // Incrementa a posição 
    envia_comando(PI); // Atualiza a posição do cursor     
  } 
  PI = (0xC0 + DESLOCAMENTO); // Reposiciona o cursor 
  envia_comando(PI);
}

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD; // Desativa o Watchdog Timer
  configura_LCM(); // Configura o display LCD   
  programa_LCM(); // Inicializa o programa no display LCD
  configura_teclado(); // Configura o teclado
  envia_comando(0x80 + 3); // Posiciona o cursor do display na terceira linha   
  envia_string("Cronometro$"); // Envia a palavra "Cronometro" para o display LCD
  
  // Define a posição inicial do cursor no display LCD e zera o cronômetro
  unsigned char posicao_inicial = (0xC0 + DESLOCAMENTO), ativo = 0, tecla;
  unsigned char reset = 1;
  
  envia_comando(posicao_inicial); // Posiciona o cursor na posição inicial
  zera_cronometro(posicao_inicial); // Zera o cronômetro na posição inicial
   
  while(1)
  {
    tecla = teclado(); // Verifica qual tecla do teclado foi pressionada
    if(tecla == '0') // Caso a tecla '0' seja pressionada
    {
      zera_cronometro(posicao_inicial);  // Zera o cronômetro, desativa o modo ativo e prepara para o próximo cronômetro
      ativo = 0;
      reset = 1;
    }
    else if(tecla == '1') // Caso a tecla '1' seja pressionada
      ativo = 1; // Ativa o cronômetro
    else if(tecla == '2') // Caso a tecla '2' seja pressionada
    {
      while(tecla != '3') // Aguarda até que a tecla '3' seja pressionada para sair do loop
      {
        tecla = teclado();
      }
    }
    
    if(ativo == 1) // Caso o modo ativo esteja ativado
    {
      cronometro(posicao_inicial, reset); // Executa o cronômetro e desativa a reinicialização
      reset = 0;
    }
  }
}
