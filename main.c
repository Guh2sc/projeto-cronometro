#include "io430.h"
#include "teclado.h"
#include "lcd.h"
#define DESLOCAMENTO    4                                      // Define o valor de deslocamento para o cursor no display LCD.
#define TEMPORIZACAO    1                                      // Define o valor de temporização para algum propósito específico.

unsigned char us='0', ds='0', um='0', dm='0', uh='0', dh='0';  // Cria as variveis utilizadas pelo cronômetro.
/*
us: unidade de segundo
ds: dezena de segundo
um: unidade de minuto
dm: dezena de minuto
uh: unidade de hora
dh: dezena de hora
*/
/*------------------------------------------------------------------------------
Nome: Cronômetro
Descrição: Essa função simula a contagem um cronômetro real, onde apresenta a posibilidade de continuar a contagem de onde parou ou reiniciar a contagem.
Entradas:   unsigned char PI - Posição inicial do cursor.
            unsigned char reset - reset, que vai indicar como vai realizar a contagem.
Saídas:                      -
------------------------------------------------------------------------------*/
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
  
  // Verifica se o valor máximo de tempo foi atingido.
  if(dh == '2' && (uh == '3') && (dm == '5') && (um == '9') && (ds == '5') && (us == '9'))
  {}// Não realiza a contagem.
  
  //Contagem do cronômetro.
  else
  {
    // Trabalha com a unidade de segundos.
    if(us >= '9')                                       // Verifica se a varivel us atingiu o valor de 9.
    {
      
      if(ds == '5' && us == '9')                        // Verifica se ds e us atingiram o limite desejado para os segundos.
      {}                                                // Pula o incremento das unidades de segundos.
      else
      {
        us = '0';                                       // Zera a variavel da unidade dos segundos.
        envia_dado(us);                                 // Atualiza a varivel no cronômetro.
        envia_comando(PI + 6);                          // Atualiza o cursor.
      }
      
      // Trabalha com a dezena de segundos.
      if((ds >= '5') || (ds == '5' && us == '9'))       // Verifica se ds atingiu o valor de 5 ou se ds e us atingiram o limite desejado para os segundos.
      {    
        us = '0';                                       // Zera a variavel da unidade dos segundos.
        envia_dado(us);                                 // Atualiza a varivel no cronômetro.
        envia_comando(PI + 6);                          // Atualiza o cursor.
        ds = '0';                                       // Zera a variavel da dezena dos segundos.
        envia_dado(ds);                                 // Atualiza a varivel no cronômetro.
        envia_comando(PI + 4);                          // Atualiza o cursor.

        // Trabalha com a unidade de minutos.
        if(um >= '9')                                   // Verifica se a varivel um atingiu o valor de 9.
        {
          um = '0';                                     // Zera a variavel da unidade dos minutos.
          envia_dado(um);                               // Atualiza a varivel no cronômetro.
          envia_comando(PI + 3);                        // Atualiza o cursor.

          // Trabalha com a dezena de minutos.
          if((dm >= '5') || (dm == '5' && um == '9'))   // Verifica se dm atingiu o valor de 5 ou se dm e um atingiram o limite desejado para os minutos.
          {
            dm = '0';                                   // Zera a variavel da dezena dos minutos.
            envia_dado(dm);                             // Atualiza a varivel no cronômetro.
            envia_comando(PI + 1);                      // Atualiza o cursor.

            // Trabalha com as horas.
            if((dh == '2') && (uh == '3'))
            {}                                          // Pula caso o limite permitido das horas tenha sido atingido.
            else
            {
              // Trabalha com a unidade de horas.
              if(uh >= '9')                             // Verifica se a varivel uh atingiu o valor de 9.
              {
                uh = '0';                               // Zera a variavel da unidade das horas.
                envia_dado(uh);                         // Atualiza a varivel no cronômetro.
                envia_comando(PI);                      // Atualiza o cursor.
                if(dh < '2')                            // Verifica se variavel dh pode ser incrementada.
                {
                  __delay_cycles(TEMPORIZACAO);         // Passagem de tempo.
                  dh++;                                 //Incrementa a dezena das horas.
                  envia_dado(dh);                       // Atualiza a varivel no cronômetro.
                  envia_comando(PI);                    // Atualiza o cursor.
                }
                else
                {}                                      //Pula o incremento da hora.
              }
              else
              {
                __delay_cycles(TEMPORIZACAO);           // Passagem de tempo.
                uh++;                                   //Incrementa a unidade das horas.
                envia_dado(uh);                         // Atualiza a varivel no cronômetro.
              }
            }
          }
          else
          {
            __delay_cycles(TEMPORIZACAO);               // Passagem de tempo.
            dm++;                                       //Incrementa a dezena dos minutos.
            envia_comando(PI + 3);                      // Atualiza o cursor.
            envia_dado(dm);                             // Atualiza a varivel no cronômetro.
          }
        }
        else
        {
          if(dm == '5' && um == '9')
          {}                                            // Pula o incremento do minuto.
          else
          {
            __delay_cycles(TEMPORIZACAO);               // Passagem de tempo.
            um++;                                       //Incrementa a unidade dos minutos.
            envia_comando(PI + 4);                      // Atualiza o cursor.
            envia_dado(um);                             // Atualiza a varivel no cronômetro.                
          }
        }
      }
      else
      {
        __delay_cycles(TEMPORIZACAO);                   // Passagem de tempo.
        ds++;                                           //Incrementa a dezena dos segundos.
        envia_dado(ds);                                 // Atualiza a varivel no cronômetro.
      }
    }
    else
    {
      if(ds == '5' && us == '9')
      {}                                                //Pula o incremento do segundo.
      else
      {
        __delay_cycles(TEMPORIZACAO);                   // Passagem de tempo.
        us++;                                           //Incrementa a unidade dos segundos.
        envia_dado(us);                                 // Atualiza a varivel no cronômetro.
      }
    }
  }
 
  PI = (0xC0 + DESLOCAMENTO);                           // Atualiza o indicador de posição e exibe
  envia_comando(PI);                                    // Atualiza o cursor.
}
/*------------------------------------------------------------------------------
Nome: Zera_cronômetro
Descrição: Essa função cria a formatação de cronômetro(00:00:00),a partir da posição desejada, que é definiada pelo cursor.
Entradas:       unsigned char PI - Posição inicial do cursor.
Saídas:                 -
--------------------------------------------------------------------------------*/
void zera_cronometro(unsigned char PI)
{
  unsigned char limite = 8;             // Define o limite de dígitos.
  while(limite != 0)                    // Loop para preencher os dígitos do cronômetro.
  {  
    if((limite == 3) || (limite == 6))  // Verifica se o limite atual corresponde a um dos pontos de separação (':').
      envia_dado(':');                  // Envia o caractere ':' para separar as unidades. 
    else
      envia_dado('0');                  // Envia o caractere '0' para preencher as unidades de tempo com zeros.
    limite--;                           // subtraí o limite para mover para o próximo dígito.
    PI++;                               // Incrementa a posição.
    envia_comando(PI);                  // Atualiza a posição do cursor.     
  } 
  PI = (0xC0 + DESLOCAMENTO);            // Reposiciona o cursor.
  envia_comando(PI);
}

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;   
  configura_LCM();                      // Configura o display LCD.
  programa_LCM();                       // Inicializa o programa no display LCD.
  configura_teclado();                  // Configura o teclado.
  envia_comando(0x80 + 3);              // Posiciona o cursor do display na terceira linha .  
  envia_string("Cronometro$");          // Envia a palavra "Cronometro" para o display LCD.
  
  // Define a posição inicial do cursor no display LCD e zera o cronômetro.
  unsigned char posicao_inicial = (0xC0 + DESLOCAMENTO), ativo = 0, tecla; // Cria as variaveis que irão indicar a posição inicial no cronômetro, cria a variavel tecla e ativo.
  unsigned char reset = 1;              //Cria a variavel reset, que serve para conferir se o cronômetro foi zerado.
  
  envia_comando(posicao_inicial);       // Posiciona o cursor na posição inicial que ele irá se escrito.
  zera_cronometro(posicao_inicial);     // Chama a função zera cronômetro para criar-lo.
   
  while(1)
  {
    tecla = teclado();                  // Verifica qual tecla do teclado foi pressionada.
    if(tecla == '0')                    // Caso a tecla '0' seja pressionada.
    {
      zera_cronometro(posicao_inicial); // Zera o cronômetro, desativa o modo ativo e prepara para o próximo cronômetro.
      ativo = 0;                        // Desativa o cronômetro.
      reset = 1;                        // Habilita que o cronômetro comece a contar do zero novamente.
    }
    else if(tecla == '1')               // Caso a tecla '1' seja pressionada.
      ativo = 1;                        // Ativa o cronômetro.
    else if(tecla == '2')               // Caso a tecla '2' seja pressionada.
    {
      while(tecla != '3')               // Aguarda até que a tecla '3' seja pressionada para sair do loop.
      {
        tecla = teclado();              // Verifica qual tecla do teclado foi pressionada.
      }
    }
    
    if(ativo == 1)                      // Pergunta se o cronômetro está ativo.
    {
      cronometro(posicao_inicial, reset); // Executa o cronômetro e desativa a reinicialização
      reset = 0;
    }
  }
}
