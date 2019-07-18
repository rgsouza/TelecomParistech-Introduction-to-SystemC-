/**
 * Author: Rayanne Souza
 * Last modification: 26 May 2016
 *
 */

#include <systemc.h>

int sc_main (int argc,char* argv[])
{

	if ( argc != 2 ){
	    	cout<< "Usage :"<< argv[0] << " <n_increment>"<< endl;
    		exit(1);
  	}
	if ( 0 > atoi(argv[1]) || atoi(argv[1]) > 255 )
	{	cout<< "La valeur de <n_increment> doit être entre 0 et 255 inclus"  << endl;	
		exit(1);
	}


	int count = 0;
	int N = atoi( argv[1] );
	
	// Un pointeur sur l’objet qui permet de gérer les traces
	sc_trace_file *trace_f;

	// Cette fonction crée l’objet
	// L’argument est le nom du fichier qui sera créer.
	// L’extension .vcd est ajoutée automatiquement
	trace_f = sc_create_vcd_trace_file ("my_simu_trace");

	// On peut aussi préciser l’unité de temps dans le fichier vcd
	trace_f->set_time_unit(1,SC_NS);


	sc_trace(trace_f, count, "count");

	for ( int i = 0; i <= N; i++ )
	{	sc_start(10,SC_NS);
		count++;
	}

	sc_close_vcd_trace_file(trace_f);

	
	return 0;

}
