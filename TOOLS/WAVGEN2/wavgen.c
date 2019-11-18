/* ce prog genere un son arbitraire
gcc -o wavgen.exe -Wall wav_head.c wavgen.c -lm

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>

#include "wav_head.h"

// generation signal sinus frequence fixe
void gen_fix_f( wavpars *d, double f, int duree )
{
// parametres de generation
double amplitude = 0.5;

// variables temporaires
short frame[2];		// left et right...
int writcnt, i;
double phi, v;

d->wavsize = d->freq * duree;	// nombre de frames
WAVwriteHeader( d );

amplitude *= 32767.0;
phi = 0.0; 
for	( i = 0; i < d->wavsize; ++i )
	{
	v = amplitude * sin( phi );
	frame[0] = (short int)round(v);
	frame[1] = frame[0];
	phi += ( ( f * 2.0 * M_PI ) / (double)d->freq );
	writcnt = write( d->hand, frame, d->chan * sizeof(short) );
	if	( writcnt != ( d->chan * sizeof(short) ) )
		gasp("erreur ecriture disque (plein?)");
	}
}

// generation signal triangle frequence fixe
void gen_tri_f( wavpars *d, double f, int duree )
{
// parametres de generation
double amplitude = 0.5;

// variables temporaires
short frame[2];		// left et right...
int writcnt, i;
double phi, v;

d->wavsize = d->freq * duree;	// nombre de frames
WAVwriteHeader( d );

amplitude *= ( 2.0 * 32767.0 );
phi = 0.0; 
for	( i = 0; i < d->wavsize; ++i )
	{
	if	( phi > 2.0 )
		phi -= 2.0;
	v = ( phi > 1 )?( 2.0 - phi ):( phi );
	v -= 0.5;
	v *= amplitude;
	frame[0] = (short int)round(v);
	frame[1] = frame[0];
	phi += ( ( f * 2.0 ) / (double)d->freq );
	writcnt = write( d->hand, frame, d->chan * sizeof(short) );
	if	( writcnt != ( d->chan * sizeof(short) ) )
		gasp("erreur ecriture disque (plein?)");
	}
}

// generation signal sinus balayage lineaire en frequence
void bal_f_lin( wavpars *d, int duree )
{
// parametres de generation
double f0 = 20.0;
double f1 = 15000;
double finc = (f1-f0)/(double)(d->freq*duree);
double amplitude = 0.7;

// variables temporaires
short frame[2];		// left et right...
int writcnt, i;
double phi, v, f;

d->wavsize = d->freq * duree;	// nombre de frames
WAVwriteHeader( d );

f = f0;
phi = 0.0; 
for	( i = 0; i < d->wavsize; ++i )
	{
	f += finc;
	v = amplitude * 32767.0 * sin( phi );
	frame[0] = (short int)round(v);
	frame[1] = frame[0];
	phi += ( ( f * 2.0 * M_PI ) / (double)d->freq );
	writcnt = write( d->hand, frame, d->chan * sizeof(short) );
	if	( writcnt != ( d->chan * sizeof(short) ) )
		gasp("erreur ecriture disque (plein?)");
	}
}

// generation signal sinus balayage "log" en frequence
void bal_f_log( wavpars *d, int duree )
{
// parametres de generation
double f0 = 20.0;
double f1 = 15000;
double loginc = log( f1 / f0 ) / (double)(d->freq*duree);
double amplitude = 0.7;

// variables temporaires
short frame[2];		// left et right...
int writcnt, i;
double phi, v, flog, f;

d->wavsize = d->freq * duree;	// nombre de frames
WAVwriteHeader( d );

flog = log( f0 );
phi = 0.0; 
for	( i = 0; i < d->wavsize; ++i )
	{
	flog += loginc;
	f = exp( flog );
	v = amplitude * 32767.0 * sin( phi );
	frame[0] = (short int)round(v);
	frame[1] = frame[0];
	phi += ( ( f * 2.0 * M_PI ) / (double)d->freq );
	writcnt = write( d->hand, frame, d->chan * sizeof(short) );
	if	( writcnt != ( d->chan * sizeof(short) ) )
		gasp("erreur ecriture disque (plein?)");
	}
}


int main( int argc, char **argv )
{
if	( argc < 4 )
	{
	printf(	"usage :\n"
		"  bal. log : wavgen L <fichier_dest> <duree>\n"
		"  bal. lin : wavgen i <fichier_dest> <duree>\n"
		"  sin. fix : wavgen f <fichier_dest> <frequ>\n"
		"  tri. fix : wavgen t <fichier_dest> <frequ>\n"
		);
	return 1;
	}

wavpars d;

d.type = 1;
d.resol = 16;
d.freq = 44100;
d.chan = 2;

d.hand = open( argv[2], O_RDWR | O_BINARY | O_CREAT | O_TRUNC, 0666 );
if	( d.hand == -1 )
	gasp("echec ouverture ecriture %s", argv[1] );

switch	( argv[1][0] )
	{
	case 'L' : bal_f_log( &d, (int)strtod( argv[3], NULL ) );
		break;
	case 'i' : bal_f_lin( &d, (int)strtod( argv[3], NULL ) );
		break;
	case 'f' : gen_fix_f( &d, strtod( argv[3], NULL ), 20 );
		break;
	case 't' : gen_tri_f( &d, strtod( argv[3], NULL ), 20 );
		break;
	}

close( d.hand );
return 0;
}

