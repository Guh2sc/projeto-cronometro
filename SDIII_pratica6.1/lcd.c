#include "lcd.h"

/*------------------------------------------------------------------------------
Nome:      Configura_LCM
Descrição:  Configuração das portas conectadas ao LCM
Entrada:         -
Saída:           -
------------------------------------------------------------------------------*/
void configura_LCM(void)
{
 //Configuração das portas
 LCM_DADO_DIR = 0XFF;   // Todos os bits da porta de dados como saída
 LCM_DADO_OUT  = 0X00;   // Limpa a saída
 LCM_CTL_DIR |= RS+EN;  // Bits da porta de controle como saída
 LCM_CTL_OUT &= ~(RS+EN); // Limpa pinos
}

/*------------------------------------------------------------------------------
Nome:      Envia_comando
Descrição: Envia os comando para o display para que ele possa ser utilizado
Entrada:      char comando
Saída:            -
------------------------------------------------------------------------------*/

void envia_comando(char comando)
{
 // Envio dos comandos
 LCM_DADO_OUT = comando;    // Passa o comando para os pinos do LCM
 LCM_CTL_OUT &= ~(RS+EN);   // joga nivel lógico baixo no E e RS
 __delay_cycles(TEMPO_CONFIG);
 LCM_CTL_OUT |= EN;         // Joga nivel lógico alto no E
 __delay_cycles(TEMPO_CONFIG);
 LCM_CTL_OUT &= ~(EN);      // joga nível lógico baixo no E
}

/*------------------------------------------------------------------------------
Nome:      Envia_dado
Descrição: Envia os dados para o display para que ele possa ser utilizado
Entrada:       char dados
Saída:            -
------------------------------------------------------------------------------*/
void envia_dado(char dados)
{
 // Envio dos dados
 LCM_DADO_OUT = dados;      // Passa o dado para os pinos do LCM
 LCM_CTL_OUT |= RS;         // joga nível lógico alto no RS
 LCM_CTL_OUT &= ~(EN);      // joga nível lógico baixo no E
 __delay_cycles(TEMPO_CONFIG);
 LCM_CTL_OUT |= EN;         // Joga nivel lógico alto no E
 __delay_cycles(TEMPO_CONFIG);
 LCM_CTL_OUT &= ~(EN);      // joga nível lógico baixo no E
}

/*------------------------------------------------------------------------------
Nome:      Envia_string
Descrição: Envia uma menssagem para o display LCM (letra-a-letra).
Entrada:     const char *apt 
Saída:            -
------------------------------------------------------------------------------*/
void envia_string(const char *apt)
{
 // Envio dos string
 unsigned char letra = *apt;    // Carrega o caracter na varivel letra
 while(letra != '$')            // Pergunta se a letra é igual a '$'
 {
   envia_dado(letra);           // envia a letra para o display
   apt += 1;                    // incrementa o apontador de memoria
   letra = *apt;                // carrega o novo caracter em 'letra'
 }
}
/*------------------------------------------------------------------------------
Nome:      Tamanho_string
Descrição: Essa função varre a menssagem interira até o caracter de que inidca o final
e retorna o tamanho da menssagem.
Entrada:    const char * apt ------- o apontador de menssagem
Saída:        char tamanho   ------- o tamanho da menssagem
------------------------------------------------------------------------------*/
char tamanho_string(const char * apt)
{
 char letra = *apt;     //Carrega a letra inicial da menssagem
 char tamanho = 0;      //Cria e inicia a varivel que quatifica o tamanho da string.
 while (letra != '$')   //Pergunta se a variavel letra é igual a '$'
   {
     apt++;             //Incrementa o indice da letra
     letra = *apt;      //Carrega a nova letra na variavel lista.
     tamanho++;         //incrementa o tamanho da lista
   } 
 return(tamanho);       // Retorna o tamanho da lista
}
/*------------------------------------------------------------------------------
Nome:     Rotaciona_string
Descrição:Essa função atrávez do tamanho da string consegue rotacionar a menssagem
até retornar a menssagem inicial.
Entrada:   const char *apt ------- o apontador de menssagem
Saída:             -
------------------------------------------------------------------------------*/
/*
void rotaciona_string( const char *apt)
{
  char final = tamanho_string(menssagem1);  // Carrega o tamannho da string na variavel final
  const char *inicio;           // Cria a variavel inicio
  inicio = apt;                 // Carrega o apontador de menssagem navariavel inicio
  char contador,letra;          // Cria a vriavel contador e letra
  char rotacao = 0;             // Cria a variavel que ira contar quantas rotações a palavra fez.
  while(rotacao != (final+1))   // Pergunta se a menssagem já fez todas as rotações necessárias para completar a menssagem inteira.
  {
    envia_comando(0x01);        // Apaga o que está escrito no display.
    contador =0;                // Carrega zero no contador.
    apt = inicio;               // Carrega a varivel que está com o inidice inicial no apontador de messagem
    apt += rotacao;             // Soma o apontador de menssagem com o número de roações
    letra = *apt;               // Carrega o novo caracter na variavel letra        
    while(contador != final)    // Pergunta se o contador é igual ao tamanho da lista para verificar se a menssagem inteira já fi enviada.
    {
      if(letra == '$')          // Pergunta se a letra é igual ao caracter que inica o final da menssagem
      {
        apt = inicio;           // Carrega a varivel que está com o inidice inicial no apontador de messagem
        letra = *apt;           // Carrega o novo caracter na variavel letra 
      }
      else
      {
        envia_dado(letra);     // Chama a função que carrega as letras no display
        __delay_cycles(TEMPO); // Chama a função de tempo para que não fique muito rapido.
        apt++;                 // Incrementa o apontador de menssagem
        letra = *apt;          // Carrega o novo caracter na variavel letra
        contador++;            // Incrementa o apontador de messagem
      }  
    }
    rotacao++;                 // Incrementa o número de rotações que a palavra fez
    __delay_cycles(TEMPO);     // Chama a função de tempo para que não fique muito rapido.
  }
}*/
/*------------------------------------------------------------------------------
Nome:      Programa_LCM
Descrição: Deixa o LCM preparado para receber informações 
Entrada:         -
Saída:           -
------------------------------------------------------------------------------*/
void programa_LCM(void)
{
 envia_comando(0x38);
 envia_comando(0x0E);
 envia_comando(0x06);
 envia_comando(0x01);
}
