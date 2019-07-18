/**
 * Author: Rayanne Souza
 * Last modification: 5 June 2016
 *
 */

#include"fgcd.h"

int main( int argc, char** argv )
{
	if( argc != 3 )
	{
		cout <<" Usage:"<<argv[0] << "<number_1> <number_2>" << endl;
		exit(1);
	}	

	cout <<" The greatest common divisor between "<< atoi( argv[1] )
	<< " and "<< atoi( argv[2] ) <<" is " << compute_GCD( atoi( argv[1] ), 
	atoi( argv[2] ) ) << endl; 

	return 0;
}
