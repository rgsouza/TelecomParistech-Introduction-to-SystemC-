/**
 * Author: Rayanne Souza
 * Last modification: 5 Jun 2016
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

	// Surchage d'operateur "+" pour faire la somme saturante
	Pixel operator + ( const Pixel &p_1 ) const
	{
		Pixel p;

		if( p_1.R + this->R > 31 )
			p.R = 31;
		else
			p.R = p_1.R + this->R;

		if( p_1.G + this->G > 63 )
                        p.G = 63;
                else
                        p.G = p_1.G + this->G;

		if( p_1.B + this->B > 31 )
                        p.B = 31;
                else
                        p.B = p_1.B + this->B;

		return p;
	}   
};


                
void sc_trace ( sc_trace_file* _f, const Pixel &_p, const std::string &s )
{
	sc_trace( _f, _p.R, s + "R" );
	sc_trace( _f, _p.G, s + "G" );
	sc_trace( _f, _p.B, s + "B" );
}

