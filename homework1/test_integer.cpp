/**
 * Author: Rayanne Souza
 * Last modification: 20 May 2016 
 *
 */
#include<systemc.h>

int sc_main( int argc , char *argv[] )
{
	sc_int<8> byte, integer;
	sc_uint<8> u_byte;
	sc_lv<8> byte_logic = "00001111";
	sc_bv<4> b_vector = "1111";
	
	byte = byte_logic;
	u_byte = b_vector;
	integer = 15;
	
	cout<<" Initialisations"<<endl<<endl;

	cout<<" byte_logic = " << byte_logic << endl;
	cout<<" Variable entier sc_int<8> qui est initialisée par le byte_logic au-dessus:" <<endl;
	cout<<" byte = " << byte <<endl<<endl;  
	cout<<" Valeur d'un bool vector: b_vector = " << b_vector <<endl;
	cout<<" Variable entier sc_uint<8> qui est initialisée par le b_vector au-dessus:" <<endl;
	cout<<" u_byte = " << u_byte <<endl<<endl; 
	cout<<" Variable entier en 8 bits initialisée par un entier:" <<endl;
 	cout<<" integer = "<< integer <<endl<<endl;


	cout<<" Teste différents opérateurs arithmétiques et logiques"<<endl<<endl;
	// integer = 30
	integer = byte + u_byte;
	cout<< " Teste operateur '+', integer = "<< integer <<endl;

	// u_byte = 0
	u_byte = byte - u_byte;
	cout<<" Teste operateur '-', u_byte = "<< u_byte <<endl;

	// u_byte = 1
	u_byte ++;
	cout<<" Teste operateur d'incrementation '++', u_byte = "<< u_byte <<endl;

	// u_byte = 15
	u_byte = byte & b_vector; 
	cout<<" Teste operateur logique '&', u_byte = "<< u_byte <<endl;

	// u_byte = 0
	u_byte = byte ^ b_vector;
	cout<<" Teste operateur logique '^', u_byte = "<< u_byte <<endl;

	// integer = 0
	integer = u_byte * integer;
	cout<<" Teste operateur '*', integer = "<< integer <<endl<<endl;

	cout<<" Teste différents conversions"<<endl<<endl;
		

	sc_int<32> v_32 = byte_logic.to_uint();
	cout<<" variable byte_logic representée par 8 bits = " << byte_logic <<endl; 

	sc_lv<32> lv_32 = v_32;
	cout<< " Variable au-dessus representée par 32 bits lv_32 = "<< lv_32 <<endl;

	sc_lv<64> lv_64 = v_32.to_uint64();
	cout<< " Variable au-dessus representée par 64 bits lv_64 = "<< lv_64 <<endl;
	
	return 0;
}
