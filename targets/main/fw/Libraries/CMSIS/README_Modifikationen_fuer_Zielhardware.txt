----------------------------------------------------------------------------------------------------
Datum:    29.02.2012 (DHA)
Hardware: LED20kMain Rev. 2.3
Software: STM32F2xx_StdPeriph_Lib_V1.0.0 (18.04.2011)
          Sourcery CodeBench Lite 2011.09-69 for ARM EABI

N�tige �nderungen:
In der Datei "core_cm3.c" m�ssen die beiden Funktionen "__STREXB" und "__STREXH" ge�ndert werden um Fehler beim Kompilieren zu verhindern.
Alt:
uint32_t __STREXB(uint8_t value, uint8_t *addr)
{
   uint32_t result=0;
  
   __ASM volatile ("strexb %0, %2, [%1]" : "=r" (result) : "r" (addr), "r" (value) );
   return(result);
}

uint32_t __STREXH(uint16_t value, uint16_t *addr)
{
   uint32_t result=0;
  
   __ASM volatile ("strexh %0, %2, [%1]" : "=r" (result) : "r" (addr), "r" (value) );
   return(result);
}

Neu:
uint32_t __STREXB(uint8_t value, uint8_t *addr)
{
    register uint32_t result asm ("r2");
   __ASM volatile ("strexb %0, %2, [%1]" : "=&r" (result) : "r" (addr), "r" (value) );
   return(result);
}

uint32_t __STREXH(uint16_t value, uint16_t *addr)
{
    register uint32_t result asm ("r2");
   __ASM volatile ("strexh %0, %2, [%1]" : "=&r" (result) : "r" (addr), "r" (value) );
   return(result);
}

Quelle/weitere Informationen:
http://old.nabble.com/-Bug-gas-13215--New%3A-ARM-Cortex-M3-strexh-strexb-instructions-with-same-registers-generates-error-td32516436.html
----------------------------------------------------------------------------------------------------

F�r die Zielhardware sind einige Anpassungen an den Dateien in diesem Ordner passiert.
Die Dateien wurden von der ST CMSIS Sammlung zusammengestellt und sind wie im Folgend angegeben ver�ndert.

----------------------------------------------------------------------------------------------------
Datum:    10.07.2010 (CBA)
Hardware: LED20kMain Rev. 2.0
Software: STM32F10x_StdPeriph_Lib_V3.3.0 (16.04.2010)

N�tige �nderungen:
High Speed External Clock (HSE) ist ein 16MHz Quartz. PLL Eingangsteiler (PLLXTPRE) auf 2 ge�ndert.

Beil�ufige �nderungen:
Alles, was nichts mit der HD MCU und 72MHz zu tun hat, gel�scht. 

----------------------------------------------------------------------------------------------------

