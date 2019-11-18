// ce programme est pour faire un plot en html5 de la fonction du quantificateur
/*
gcc -Wall -o plot.exe plot_wsub2.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* fonction de quantification generique */
double quantif( double x, double q )
{
double qx; int ix;
if  ( q == 0.0 ) return( x );

if   ( x >= 0.0 )
     {
     qx = ( x / q ) + 0.5;
     ix = (int) qx;
     qx = q * ix;
     return ( qx );
     }	     
else {
     qx = ( -x / q ) + 0.5;
     ix = (int) qx;
     qx = q * ix;
     return ( -qx );
     }
}

int main( int argc, char ** argv )
{
FILE * fil;
double x;

fil = fopen("plot_a42.js", "w" );

if	( fil == NULL )
	return 1;

fprintf( fil, "var plot1 = [\n");
for	( x = -1.0; x <= 1.0; x += 0.002 )
	{
	fprintf( fil, "[%.3f,%.3f],", x, quantif( x, 0.02 ) );
	}
fprintf( fil, "];\nvar plot2 = [\n");
for	( x = -1.0; x <= 1.0; x += 0.002 )
	{
	fprintf( fil, "[%.3f,%.3f],", x, quantif( x, 0.1 ) );
	}
fprintf( fil, "];\nvar plot3 = [\n");
for	( x = -1.0; x <= 1.0; x += 0.002 )
	{
	fprintf( fil, "[%.3f,%.3f],", x, quantif( x, 0.4 ) );
	}
fprintf( fil, "];\n");
fclose( fil );

return 0;
}
