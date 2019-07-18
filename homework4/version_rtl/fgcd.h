/**
 * Author: Rayanne Souza
 * Last modification: 10 June 2016
 *
 */

#ifndef FGCD
#define FGCD

#include<cstdlib>
#include<systemc.h>


int smaller_number( int num_1, int num_2 )
{
        return ( num_1 > num_2 )? num_2 : num_1;
}

int compute_GCD( int num_1, int num_2 )
{
	if( num_1 == 0 && num_2 == 0 )
		return 1;

        if( abs( num_1 - num_2 ) == 0 )
                return num_1;

        if( num_1 == 0 && num_2 != 0 )
                return num_2;

        if( num_2 == 0 && num_1 != 0 )
                return num_1;

        return compute_GCD( abs( num_1 - num_2 ), smaller_number( num_1, num_2 ) );

}


#endif
