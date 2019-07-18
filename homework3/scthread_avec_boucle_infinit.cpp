/**
 * Author: Rayanne Souza
 * Last modification: 1 Jun 2016
 *
 */

#include<systemc.h>

SC_MODULE(foo)
{
   	sc_in<bool> a;
   	sc_in<int>  b;
   	sc_in<int>  c;
	sc_out<int> d;
	sc_out<int> e;

	SC_CTOR(foo)
   {
      // Le thread bar est sensible aux évènements sur a, b et c
      SC_THREAD(bar);
      sensitive << a << b ;
      sensitive << c ;
      // Le thread lab est sensible à l'évènement "front montant" de a
      SC_THREAD(lab);
      sensitive << a.pos();
   }

	void bar()
	{	
     		while( true ){
		    // attendre un évènement sur a, b ou c
		    wait();
		    // d est incrementé a chaque évènement sur a, b ou c	
		    d.write( d.read() + 1 );
		}
	}

	void lab()
	{
		while( true ) {	
		    // attendre un front montant de "a"
		    wait();
		    // e change a chaque front montant de a
		    e.write( b.read() + c.read() + e.read() );
		}		
	}
};

void sc_trace ( sc_trace_file* _f, const foo &_foo, const std::string &s )
{
        sc_trace(_f, _foo.a, "Foo_a");
        sc_trace(_f, _foo.b, "Foo_b");
        sc_trace(_f, _foo.c, "Foo_c");
	sc_trace(_f, _foo.d, "Foo_d");
	sc_trace(_f, _foo.e, "Foo_e");
}

int sc_main( int argc, char * argv[] )
{
    foo I_foo("I_foo");
    sc_signal<int> b, c, d, e;

    sc_trace_file *trace;

    trace = sc_create_vcd_trace_file ("Test_SC_THREAD");
    trace->set_time_unit(1,SC_NS);


    sc_clock clk( "clk", 10, SC_NS );

    c = 10;
    b = 20;

    // input 
    I_foo.a( clk );
    I_foo.b( b );
    I_foo.c( c );
  
    // Output
    I_foo.d( d );
    I_foo.e( e );

    sc_trace( trace, I_foo, "I_foo" );
    sc_trace( trace, clk, "CLOKS" );

    sc_start(800, SC_NS);   
 
    sc_close_vcd_trace_file(trace);

    cout << "Le fichier Test_SC_THREAD a été créer" << endl; 
	
    return 0;
}
