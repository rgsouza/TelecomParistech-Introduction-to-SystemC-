/**
 * Author: Rayanne Souza
 * Last modification: 22 May 2016
 */

#include <systemc.h>

int sc_main( int argc, char *argv[] )
{
	sc_lv < 8 > a_logic, b_logic;
	sc_bv < 8 > c_bool;
	sc_bv < 16 > d_bool;
	sc_lv < 4 > e_logic, g_logic;
	sc_bv < 4 > f_bool, h_bool;


	a_logic = false;

	// 170
	b_logic = "10101010";

	// Vecteur bool reçois la valeur du vecteur logique b
	c_bool = b_logic;
	
	// 170	
	d_bool = ( a_logic, c_bool );

	// valeur 13
	e_logic( 2,  0 ) = c_bool( 5, 3 );
	e_logic[ 3 ] = 1;

	// valeur 15
	f_bool = e_logic | d_bool( 3, 0 );

	// valeur 8
	g_logic = e_logic & d_bool( 3, 0 );

	// (0100) ^ (1111) = 11 
	h_bool = (g_logic >> 1) ^ f_bool;

	cout << " Teste differentes initialisations" << endl;
	cout << " Vecteur logic a_logic=" << a_logic << endl;
	cout << " Vecteur logic b_logic=" << b_logic.to_uint() << endl;
	cout << " Vecteur bool  c_bool=" << c_bool.to_uint() << endl;
	cout << " Vecteur bool d_bool=" << d_bool.to_int() << endl;
	cout << " Vecteur logic e_logic=" << e_logic.to_uint() << endl << endl;

	cout << " Teste differentes operations binaires" << endl; 
	cout << " Vecteur bool f_bool= e | b( 3, 0 ) =" << f_bool.to_uint() << endl;
	cout << " Vecteur logique g_logic =" << g_logic.to_uint() << endl;
	cout << " Vecteur logique h_logic =" << h_bool.to_uint() << endl << endl;
	
	// Differentes conversions
	cout << " Teste differentes conversions" << endl;

        cout << " Vecteur ( uint )  b_logic=" << b_logic.to_uint() << endl;
	cout << " Vecteur ( int  ) b_logic=" << b_logic.to_int() << endl;
	cout << " Vecteur ( long  ) b_logic=" << b_logic.to_long() << endl;
	cout << " Vecteur ( ulong  ) b_logic=" << b_logic.to_ulong() << endl;

	return 0;
}
