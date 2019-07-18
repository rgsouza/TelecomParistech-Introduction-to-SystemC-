/**
 * Author: Rayanne Souza
 * Last modification: 5 June 2016
 *
 */

#include<systemc.h>
#include"fgcd.h"

SC_MODULE( PGCD )
{
	sc_in< bool > clk, ready;
	sc_in< sc_uint< 8 > > A, B;
	sc_out< bool > valid;
	sc_out< sc_uint< 8 > > pgcd; 
	sc_uint< 8 >mpgcd;


	SC_CTOR( PGCD )
	{
		SC_CTHREAD( get_GCD, clk.pos() );
	}

	void get_GCD()
	{
		while( true ){
			
			
			// Attend que les entrées soient pretes.
			while( !ready );
			
			// Attend un cycle
			wait( 1 );

			// Calcule du PGCD
			mpgcd = compute_GCD( A.read(), B.read() );			

			// Notifie que le resultat est prete
			valid.write( 1 );

			// Passe la valeur calculer à la sortie
			pgcd.write( mpgcd );

			// Attend un cycle
			wait( 1 );
	
			// Invalide le resultat
			valid.write( 0 );
		
		}
	}

};

void sc_trace ( sc_trace_file* _f, const PGCD &_pgcd, const std::string &s )
{
        sc_trace(_f, _pgcd.clk, "PCGD_clock");
        sc_trace(_f, _pgcd.ready, "PCGD_ready");
        sc_trace(_f, _pgcd.A, "PCGD_A");
	sc_trace(_f, _pgcd.B, "PCGD_B");
	sc_trace(_f, _pgcd.pgcd, "PCGD");
        sc_trace(_f, _pgcd.valid, "PCGD_valid");
}

int sc_main( int argc,char* argv[] )
{
	sc_clock clk("clock",10,SC_NS);
	sc_signal< sc_uint< 8 > > num_1, num_2, pgcd;
	sc_signal< bool > valid("valid"), ready("ready");

	sc_trace_file *trace;

	trace = sc_create_vcd_trace_file( "Trace_signal_pgcd" );
	trace-> set_time_unit( 1, SC_NS );

	PGCD I_PGCD("PGCD");
	

	I_PGCD.clk( clk );
	I_PGCD.A( num_1 );
	I_PGCD.B( num_2 );

	I_PGCD.ready( ready );
	I_PGCD.valid( valid );
	I_PGCD.pgcd( pgcd );

	sc_trace( trace, I_PGCD, "I_PGCD" );
	sc_trace( trace, num_1, "num_1" );
	sc_trace( trace, num_2, "num_2" );
	sc_trace( trace, valid, "valid" );
	sc_trace( trace, ready, "ready" );

	for( int i = 0; i < 10; i++ )
	{
		num_1.write( (3 + i) * i );
		num_2.write( (1 + i ) + 20 );
		
		// Notifie que les entrées sont prete
		ready.write( 1 );
		sc_start( 10, SC_NS );

		cout << "READY" << ready << endl;

		// Finalise la durée d'un cycle d'horloge avec la valeur 1
		ready.write( 0 );
		sc_start( 10, SC_NS );

		if( valid.read() ){
			if( pgcd.read() != compute_GCD(num_1.read(), num_2.read()) )
			{
				cout << "ERROR: PGCD should be "<<compute_GCD(num_1.read(), num_2.read())<<" but is "
				<< pgcd.read() << endl;
			}   		
			else{
				cout << "*************pgcd**************" << endl;
        			cout << "PGCD entre " << num_1 <<" et "<< num_2 <<" est " << pgcd << endl;
				cout << "READY" << I_PGCD.ready.read() << endl;
			}
		}
	}

	sc_close_vcd_trace_file( trace );

	cout << endl <<"Le fichier Trace_signal_pgcd a été créé" << endl;
	
	return 0;
}
