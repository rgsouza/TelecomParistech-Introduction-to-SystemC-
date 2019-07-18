/**
 * Author Rayanne Souza
 * Last modification: 3 jun 2016
 */

#include"modules_generateur_couleur.h"

SC_MODULE(M_SUM_PIXELS)
{
	sc_in< Pixel > pin_1;
	sc_in< Pixel > pin_2;
	sc_out< Pixel > pout; 


	SC_CTOR( M_SUM_PIXELS )
	{
		SC_METHOD( m_sum_pixel );
		sensitive << pin_1 << pin_2;

		dont_initialize();
	
	}

	void m_sum_pixel()
	{
		pout.write( pin_1.read() + pin_2.read() );
	}		
};

SC_MODULE(THREAD_SUM_PIXELS)
{
        sc_in< Pixel > pin_1;
        sc_in< Pixel > pin_2;
        sc_out< Pixel > pout;         


        SC_CTOR( THREAD_SUM_PIXELS )
        {
                SC_THREAD( sum_pixel );
                sensitive << pin_1 << pin_2;

        }

        void sum_pixel()
        {
		while( true ){
	
        	 	pout.write( pin_1.read() + pin_2.read() );
			wait();
  		}	
	}
};

int sc_main ( int argc, char *argv[] )
{
        sc_signal<Pixel> pin_1, pin_2, px1, px2, color_thread;
	sc_signal<Pixel> color_method, color_cthread;
	sc_signal<bool> rst;
	sc_clock clk("clock", 30, SC_NS);
 
	pin_1.write( Pixel(31, 20, 10) );
	pin_2.write( Pixel(30, 20, 21) ); 


	
	// Modules somme
	M_SUM_PIXELS I_m_sum_pixel( "Methode_sum" );
	THREAD_SUM_PIXELS I_thread_sum_pixel( "Thread_sum" );

	I_m_sum_pixel.pin_1( pin_1 );
	I_m_sum_pixel.pin_2( pin_2 );
	I_m_sum_pixel.pout( px1 );
	
	I_thread_sum_pixel.pin_1( pin_1 );
        I_thread_sum_pixel.pin_2( pin_2 );
        I_thread_sum_pixel.pout( px2 );

		

	// Modules calcule toutes les coleurs possibles
	ALL_COLOR_THREAD I_all_color_thread( "ALL_COLOR_THREAD" );
	ALL_COLOR_CTHREAD I_all_color_cthread( "ALL_COLOR_CTHREAD" );
	ALL_COLOR_METHOD I_all_color_method( "ALL_COLOR_CTHREAD" );


	I_all_color_thread.clk( clk );
	I_all_color_thread.color( color_thread );
	I_all_color_thread.rst( rst );

	I_all_color_cthread.clk( clk );
	I_all_color_cthread.color( color_cthread );
	I_all_color_cthread.rst( rst );

	I_all_color_method.clk( clk );
	I_all_color_method.color( color_method );
	I_all_color_method.rst( rst );


	sc_trace_file *trace_f;
	trace_f = sc_create_vcd_trace_file ("Trace_RGB_color");
	// Trace des signauw pixels à être sommés 
	sc_trace( trace_f, pin_1, "Pixel_1" );
	sc_trace( trace_f, pin_2, "Pixel_2" );

	// Trace resultat de la somme
	sc_trace( trace_f, px1, "Sortie_SUM_Method" );
	sc_trace( trace_f, px2, "Sortie_SUM_Thread" );

	// Trace des couleurs à être generer à chaque cycle d'horloge
	sc_trace( trace_f, color_thread, "Color_thread" );
	sc_trace( trace_f, color_cthread, "Color_cthread" );
	sc_trace( trace_f, color_method, "Color_method" );

	// Trace signal reset
	sc_trace( trace_f, rst, "RESET" );
	trace_f->set_time_unit(1,SC_NS);
	
	// Teste somme des pixels
	for( int i = 0; i < 10; i++ ){

             	cout <<"@ "<< sc_time_stamp() <<" PIXELS À SOMER" << endl;
		cout <<"@ "<< sc_time_stamp() << pin_1 << endl;
                cout <<"@ "<< sc_time_stamp() << pin_2 << endl;

		cout <<" METHODE " << endl;
		cout <<"@ "<< sc_time_stamp() << px1 << endl;

		cout <<" THREAD " << endl;
		cout <<"@ "<< sc_time_stamp() << px2 << endl;

		pin_1.write( Pixel(2 + i, 20 + i, i) );
		pin_2.write( Pixel(30, 20, 21) );

             	sc_start(1, SC_NS);
	}

	
	// Teste generation de toutes couleurs
	cout << endl << "Affichage de toutes les couleurs" << endl;
	for( int i = 0; i <= 65536; i++ )
	{
		cout<<"************************************" <<endl;
		cout<<" Color en utilisant sc_thread" << color_thread << endl;
		cout<<" Color en utilisant sc_cthread" << color_cthread << endl;
		cout<<" Color en utilisant sc_method" << color_method << endl;
		cout<<"************************************" <<endl;
		sc_start( 30, SC_NS ); 		

	}

	// Teste fonctionnement avec un signal reset
	rst.write( 1 );
	sc_start( 30, SC_NS );
	cout << "Reset activé" << endl;
	cout<<"************************************" <<endl;
	cout<<" Color en utilisant sc_thread" << color_thread << endl;
	cout<<" Color en utilisant sc_cthread" << color_cthread << endl;
	cout<<" Color en utilisant sc_method" << color_method << endl;
	cout<<"************************************" <<endl;
	rst.write( 0 );
	sc_start( 30, SC_NS );
	cout<<"************************************" <<endl;
        cout<<" Color en utilisant sc_thread" << color_thread << endl;
        cout<<" Color en utilisant sc_cthread" << color_cthread << endl;
        cout<<" Color en utilisant sc_method" << color_method << endl;
        cout<<"************************************" <<endl;
	
 
	sc_close_vcd_trace_file(trace_f);

        cout <<" Le fichier Trace_RGB_color.vcd a été créeé " << endl;

        return 0;
}

