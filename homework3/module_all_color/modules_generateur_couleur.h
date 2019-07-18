/**
 * Author: Rayanne Souza
 * Last modification: 6 Jun 2016
 */

#ifndef  MODULES_GENERATEUR_COULEUR_H
#define MODULES_GENERATEUR_COULEUR_H

#include<systemc.h>
#include"pixels.h"

SC_MODULE( ALL_COLOR_THREAD )
{
        sc_in_clk clk;
	sc_in<bool> rst;
        sc_out< Pixel > color;
	sc_uint< 16 > current_color_thread;

        SC_CTOR( ALL_COLOR_THREAD )
        {
		current_color_thread = 0;
		SC_THREAD( compute_color );
		sensitive << clk.pos() << rst.pos();        
        }
        
	void compute_color( ){
	
		while( true ){	

			// Attend un evenement de front montant d'horloge
			wait();		

			if( rst )
				current_color_thread = 0;
			else{

				if( current_color_thread < 65535 )	
					current_color_thread++;
				else
					current_color_thread = 0;
			}
				color.write( Pixel( current_color_thread(4, 0), current_color_thread(10, 5),
								current_color_thread(15, 11)) );
	
		
		}
	}
};

SC_MODULE( ALL_COLOR_CTHREAD )
{
	sc_in_clk clk;
	sc_in< bool > rst;
	sc_out< Pixel > color;
	sc_uint< 16 > current_color_cthread;

	SC_CTOR( ALL_COLOR_CTHREAD )
	{
		current_color_cthread = 0;
		SC_CTHREAD( compute_color, clk.pos() );
		async_reset_signal_is( rst, true );               
	}
        
	void compute_color( ){
		 while( true ){

			if( rst )
				current_color_cthread = 0;
			else{
				if( current_color_cthread < 65535 ) 
					current_color_cthread++;
				else
					current_color_cthread = 0;

			}
			
			color.write( Pixel( current_color_cthread(4, 0), current_color_cthread(10, 5),
									current_color_cthread(15, 11)) );
			
			// Attend un evenement
                        wait();
		}      
	}

};

SC_MODULE( ALL_COLOR_METHOD )
{
	sc_in< bool > clk, rst;
 	sc_out< Pixel > color;
	sc_uint< 16 > current_color;

	SC_CTOR( ALL_COLOR_METHOD )
	{
		current_color = 0;
		SC_METHOD( compute_color );
		sensitive << clk.pos();
		async_reset_signal_is( rst, true );
		dont_initialize();        
	}

	void compute_color( ){

		if( rst )
			current_color = 0;
		else{
			if( current_color < 65535 )
				current_color++;
			else
				current_color = 0;
		}
			color.write( Pixel( current_color(4, 0), current_color(10, 5),
								current_color(15, 11)) );
        }
};

#endif
