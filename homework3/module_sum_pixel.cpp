/**
 * Author: Rayanne Souza
 * Last modification: 3 Jun 2016
 *
 */
#include"pixels.h"

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
	
			wait(SC_ZERO_TIME);
        	 	pout.write( pin_1.read() + pin_2.read() );
  		}	
	}
};

SC_MODULE( ALL_COLOR )
{
	sc_in< bool > clk;
        //sc_in< Pixel > rst;
        sc_out< Pixel > color;


        SC_CTOR( COMPUTE_COLOR )
	{
		SC_THREAD( compute_color );
		sensitive << clk.pos();		
	}


	void compue_color()
	{


	}
}
int sc_main ( int argc, char *argv[] )
{
        sc_signal<Pixel> pin_1, pin_2, px1, px2;

	pin_1.write( Pixel(31, 20, 10) );
	pin_2.write( Pixel(30, 20, 21) ); 

	M_SUM_PIXELS I_m_sum_pixel( "Methode_sum" );
	THREAD_SUM_PIXELS I_thread_sum_pixel( "Thread_sum" );

	I_m_sum_pixel.pin_1( pin_1 );
	I_m_sum_pixel.pin_2( pin_2 );
	I_m_sum_pixel.pout( px1 );
	
	I_thread_sum_pixel.pin_1( pin_1 );
        I_thread_sum_pixel.pin_2( pin_2 );
        I_thread_sum_pixel.pout( px2 );

		

 /*       sc_trace_file *trace_f;
        trace_f = sc_create_vcd_trace_file ("Trace_RGB_color");
        sc_trace( trace_f, p, "Pixel" );
        trace_f->set_time_unit(1,SC_NS);
*/

        for( int i = 0; i < 31; i++ ){

                //px = pixel + pixel_2;

               // p.write( pixel );

                cout <<"@ "<< sc_time_stamp() << pin_1 << endl;
                cout <<"@ "<< sc_time_stamp() << pin_2 << endl;

		cout <<" METHODE " << endl;
                cout <<"@ "<< sc_time_stamp() << px1 << endl;

		cout <<" THREAD " << endl;
		cout <<"@ "<< sc_time_stamp() << px2 << endl;

                sc_start(1, SC_NS);

                //cout << endl <<"-------------APRES 1ns------------" << endl << endl;
               // cout <<"@ "<< sc_time_stamp() << pixel << endl;
                //cout <<"@ " << sc_time_stamp() << " Signal rgb" << p << endl;
        }


 //       sc_close_vcd_trace_file(trace_f);

        cout <<" Le fichier Trace_RGB_color.vcd a été créeé " << endl;

        return 0;
}

