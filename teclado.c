#include "teclado.h"

unsigned char TAB_TEC[13] = {"\00""321654987E0A"}; 
unsigned char TAB_LIN[5] = {BIT4,BIT5,BIT6,BIT7,0X00};

void configura_teclado(void)
{ 
  COLUNAS_DIR &= ~BITS_COLUNA;
  LINHAS_DIR  |= BITS_LINHA;
}
unsigned char teclado(void) 
{ 
  unsigned char *APT_TEC = TAB_TEC; 
  unsigned char *APT_LIN = TAB_LIN;
  LINHAS |= BITS_LINHA; 
  if(COLUNAS & BITS_COLUNA)
  {
    __delay_cycles(45000);//tempo_repique(30000);
    LINHAS = *APT_LIN;
    while(((COLUNAS & (BITS_COLUNA))== 0X00) && (*APT_LIN != '\00'))
    {
      APT_TEC += 3;
      APT_LIN += 1;
      LINHAS = *APT_LIN;
    }
    if (*APT_LIN == '\00')
      APT_TEC = TAB_TEC;
    else if (COLUNAS & BIT0)
      APT_TEC += 1;
    else if (COLUNAS & BIT1)
      APT_TEC += 2;
    else if (COLUNAS & BIT2)
      APT_TEC += 3;
    else
      APT_TEC = TAB_TEC;
  }

  return (*APT_TEC); 

} 