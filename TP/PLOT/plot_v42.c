// ce programme est pour faire un plot en html5 de la fonction du quantificateur
/*
gcc -Wall -c plotquant.c
gcc -s -o plot.exe plot_v42.o quant.o
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

extern int dequant[4][256];
extern unsigned char quant[4][512];

// initialisation des quantifieurs (appeler 1 fois)
void init_quant0();


int main( int argc, char ** argv )
{
int iquant = 0;
FILE * fil;
double x;

init_quant0();
fil = fopen("plot_v42.js", "w" );

if	( fil == NULL )
	return 1;

fprintf( fil, "var plot1 = [\n");
for	( x = 0.0; x <= 511.0; x += 0.1 )
	{
	fprintf( fil, "[%.1f,%d],", x, quant[iquant][(int)round(x)] );
	}
fprintf( fil, "];\nvar plot2 = [\n");
for	( x = 0.0; x <= 511.0; x += 0.1 )
	{
	fprintf( fil, "[%.1f,%d],", x, dequant[iquant][quant[iquant][(int)round(x)]] );
	}
fprintf( fil, "];\n");
fclose( fil );

return 0;
}
