/**
 * Author: Rayanne Souza
 * Last modification: 10 June 2016
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
	sc_uint< 8 >mpgcd, smaller, difference, value;


	SC_CTOR( PGCD )
	{
		SC_CTHREAD( get_GCD, clk.pos() );
	}

	void get_GCD()
	{
		while( true ){
			
			
			// Attend que les entrées soient pretes.
			while( !ready.read() ) wait();
			
			// Calcule du PGCD

			if( A.read() == 0 && B.read() == 0 )
				mpgcd = 1;
			 
			else if( A.read() == 0 && B.read() != 0 )
				mpgcd = B.read();
			
			else if( A.read() != 0 && B.read() == 0 )
                                mpgcd = A.read();
			
			else
			{
				value = smaller_number( A.read().to_int(), B.read().to_int() );
				difference = ( A.read() < B.read() ) ? B.read() - A.read() : A.read() - B.read();
				while( difference != 0 )
				{
					smaller = smaller_number( value, difference );			
					difference = ( difference < value ) ? value - difference : difference - value;
					value = smaller;
					wait(1);
				}

					
				mpgcd = smaller;
			}	
			
			// Attend au moin un cycle pour que le ready soit 0	
			wait( 1 );
		
			// Notifie que le resultat est prete
			valid.write( 1 );

			// Passe la valeur calculer à la sortie
			pgcd.write( mpgcd );

			// Attend un cycle
			wait( 1 );

			// Invalide le resultat
			valid.write( 0 );
			
			// Attends l'invalidation du resultat			
			wait(1);
		
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

	trace = sc_create_vcd_trace_file( "Trace_signal_pgcd_thread" );
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

	num_1.write( 0 );
	num_2.write( 0 );

	// Notifie que les entrées sont prete
	ready.write( 1 );
	sc_start( 10, SC_NS );

	// Finalise la durée d'un cycle d'horloge de valeur 1
	ready.write( 0 );

	int i = 0;
	while( i < 10 )
	{
		if( valid.read() ){
			if( pgcd.read().to_int() != compute_GCD(num_1.read().to_int(), num_2.read().to_int()) )
			{
				cout << "ERROR: PGCD should be "<<compute_GCD(num_1.read().to_int(), num_2.read().to_int())<<" but is "
				<< pgcd.read() << endl;
			}   		
			else{
				cout << "*************pgcd**************" << endl;
        			cout << "PGCD entre " << num_1 <<" et "<< num_2 <<" est " << pgcd << endl;
			}
			sc_start(10, SC_NS);
			
	
			num_1.write( (3 + i) * i );
			num_2.write( (1 + i ) + 20 );

			// Notifie que les entrées sont prete
			ready.write( 1 );
			sc_start( 10, SC_NS );

			// Finalise la durée d'un cycle d'horloge avec la valeur 1
			ready.write( 0 );

			i++;	
		}
		else
			sc_start( 10, SC_NS );
	}

	sc_close_vcd_trace_file( trace );

	cout << endl <<"Le fichier Trace_signal_pgcd_thread a été créé" << endl;
	
	return 0;
}
