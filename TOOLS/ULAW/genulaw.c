/* generation data ulaw pour plot

gcc -o genulaw genulaw.c -lm
*/

#include <stdio.h>
#include <math.h>

/*
fonction normalisee : f = ln( 1 + U*x ) / ln ( 1 + U )
derivee f' = 1 / ln(1+U) * U / 1 + U*x
	min(f') = f'(1) = ( U / 1 + U ) / ln(1+U) 
	max(f') = f'(0) =   U           / ln(1+U)
rapport de variation des derivees :
	max(f')/min(f') = 1 + U
exemple : U = 100
	min(f') = f'(1) = ( 100/101 ) / 4.61512 = 0.2145
	max(f') = f'(0) =   100       / 4.61512 = 21.67
exemple : U = 255
	min(f') = f'(1) = ( 255/256 ) / 5.545 = 0.179
	max(f') = f'(0) =   255       / 5.545 = 45.98
	*/

double ulaw( double x )  /* -1 < x < 1 */
{
double retval, ax, u;
ax = ( x >= 0.0 )?( x ):( -x );
u = 100.0;  /* pourquoi 100 ? sais pas, c'est magic */
retval = log( 1.0 + u * ax ) / log( 1.0 + u );
return(  ( x >= 0.0 )?( retval ):( -retval ) );
}

void main()
{

double x; int i;
for ( i = 0; i <= 200; i++ )
    {
    x = i - 100;
    x = x / 100;
    printf("%g\n", 100.0 * ulaw( x ) );
    }

}
/*
------------------------------------------------------------------
U-LAW and A-LAW definitions
---------------------------

[Adapted from information provided by duggan@cc.gatech.edu (Rick
Duggan) and davep@zenobia.phys.unsw.EDU.AU (David Perry)]

u-LAW (really mu-LAW) is

          sgn(m)   (     |m |)       |m |
   y=    ------- ln( 1+ u|--|)       |--| =< 1
         ln(1+u)   (     |mp|)       |mp|

A-LAW is

     |     A    (m )                 |m |    1
     |  ------- (--)                 |--| =< -
     |  1+ln A  (mp)                 |mp|    A
   y=|
     | sgn(m) (        |m |)    1    |m |
     | ------ ( 1+ ln A|--|)    - =< |--| =< 1
     | 1+ln A (        |mp|)    A    |mp|

Values of u=100 and 255, A=87.6, mp is the Peak message value, m is
the current quantised message value.  (The formulae get simpler if you
substitute x for m/mp and sgn(x) for sgn(m); then -1 <= x <= 1.)

Converting from u-LAW to A-LAW is in a sense "lossy" since there are
quantizing errors introduced in the conversion.

"..the u-LAW used in North America and Japan, and the
A-LAW used in Europe and the rest of the world and
international routes.."
*/
