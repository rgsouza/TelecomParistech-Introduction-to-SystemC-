/**
 * Author: Rayanne Souza
 * Last modification: 29 May 2016
 *
 */

#include<systemc.h>

struct Pixel{

	sc_uint< 5 > R;
	sc_uint< 6 > G;
	sc_uint< 5 > B;

	// Constructeur avec les valeurs (0,0,0 ) par default 
	Pixel( sc_uint< 5 > _r = 0, sc_uint< 6 > _g = 0, sc_uint< 5 > _b = 0  ){
		R = _r;
		G = _g;
		B = _b;	
	}

	friend ostream& operator << ( ostream &o, const Pixel & p )
	{
		o << "--- RGB---" << "(" << p.R << ", "<< p.G
		<<", "<< p.B << ")"<< endl;

		return o;
	}

	// Test d'égalité
	bool operator == ( const Pixel &p )
	{
		if ( R == p.R && G == p.G && B == p.B )
			return true;
		
		return  false;
	}

};

void sc_trace ( sc_trace_file* _f, const Pixel &_p, const std::string &s )
{
	sc_trace( _f, _p.R, s + "R" );
	sc_trace( _f, _p.G, s + "G" );
	sc_trace( _f, _p.B, s + "B" );
}

int sc_main ( int argc, char *argv[] )
{
	sc_signal<Pixel> p;
	Pixel pixel;
	sc_uint< 5 > param = 1;

	sc_trace_file *trace_f;
	trace_f = sc_create_vcd_trace_file ("Trace_RGB_color");
	sc_trace( trace_f, p, "Pixel" );
	trace_f->set_time_unit(1,SC_NS);


	pixel = p.read();

	for( int i = 0; i < 31; i++ ){

		pixel.R = pixel.R + param ;
		pixel.G = pixel.G+ param;
		pixel.B = pixel.B + param;

		p.write( pixel );

		cout <<"@ "<< sc_time_stamp() << pixel << endl;	
		cout <<"@ " << sc_time_stamp() << " Signal rgb" << p << endl;
		
		sc_start(1, SC_NS);

		cout << endl <<"-------------APRES 1ns------------" << endl << endl;
		cout <<"@ "<< sc_time_stamp() << pixel << endl;
		cout <<"@ " << sc_time_stamp() << " Signal rgb" << p << endl;
	}
	
	sc_close_vcd_trace_file(trace_f);

	cout <<" Le fichier Trace_RGB_color.vcd a été créeé " << endl;
		
	return 0;
}
