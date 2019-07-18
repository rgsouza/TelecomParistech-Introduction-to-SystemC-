/**
 * Author: Rayanne Souza 
 * Last modification: 22 May 2016
 */

#include<systemc.h>

void test_initialisation( )
{
	sc_logic a, b, c, d, e, f;

        cout << "Test initialisation" <<endl;

        a = 0;
        b = 1;
        c = 2;
        d = 3;

        // Affiche 0
        cout <<" a:"<<a<<endl;
        // Affiche 1
        cout <<" b:"<<b<<endl;
        // Affiche Z
        cout <<" c:"<<c<<endl;
        // Affiche X
        cout <<" d:"<<d<<endl;

        a = 'z';
        b = '1';
        c = 'x';
        d = '0';
        e = 'Z';
        f = 'X';


        // Affiche Z
        cout <<" a:"<<a<<endl;
        // Affiche 1
        cout <<" b:"<<b<<endl;
        // Affiche X
        cout <<" c:"<<c<<endl;
        // Affiche 0
        cout <<" d:"<<d<<endl;
        // Affiche Z
        cout <<" e:"<<e<<endl;
        // Affiche X
        cout <<" f:"<<f<<endl;

	a = 'a';
        b = 'b';
        c = 'c';
        d = 'd';


        // Affiche X
        cout <<" a:"<<a<<endl;
        // Affiche X
        cout <<" b:"<<b<<endl;
        // Affiche X
        cout <<" c:"<<c<<endl;
        // Affiche X
        cout <<" d:"<<d<<endl;

        a = false;
        b = true;

        // Affiche 0
        cout <<" a:"<<a<<endl;
        // Affiche 1
        cout <<" b:"<<b<<endl;


}

void test_operateurs_egalite( )
{
	sc_logic a, b;

	a = false;
	b = true;
	
	cout <<"test operateurs égalité"<< endl;

        if( a == '0' )
       		cout <<" a est egal à 0"<<endl;
        if( b != 0 )
                cout <<" b  est different de 0"<<endl;
}

void test_operateurs_logiques( )
{
	sc_logic a, b, c, d, e,f;

	cout <<"Test operateur binaire"<<endl;	
	a = 1;
	b = 0;
	c = 3;
	
	if ( (a == '0') | (c =='x') )
		cout <<"Test operateur binaire '|' a :"<<a<<"c:"<<c<<endl;
	 

	if( (b == 0)  & (a == 1) )
		cout << "Test operateur binaire '&' a :"<<a<<" b:"<<b<<endl;		
	// d = 1
	d = a | b;
	// e = x
	e = a & c;
	// f = 1
	f = a ^ b;
	
	a = ~a;
	
	cout << "d doit etre 1 et d: "<< d << endl;
	cout << "e doit etre x et e: "<< e << endl;
	cout << "f doit etre 1 et f: "<< f << endl;
	cout << "a doit etre 0 et a: "<< a << endl;	

}

void test_operateurs_binaires( )
{
	sc_logic a, b, f, g, h;
	bool d, e;

	cout << "Test operateurs binaires entre sc_logic et bool" << endl;
	a = 1;
	b = 0;

	d = a.to_bool();
	g = false;
	f = d & a;
	e = f.to_bool();
	h = b ^ e;

	cout << "a :" << a << endl;
	cout << "b :" << b << endl;
	cout << "d doit etre egal à 'a' donc 1 et d =" << d <<endl;
 	cout << "e doit etre égal à 1 et e =" << e << endl;
	cout << "f doit etre égal à 1 et f=" << f << endl;
	cout << "g doit etre égal à 0 et g=" << g << endl;
	cout << "h doit etre égal à 1 et h=" << h << endl;
}

int sc_main( int argc, char *argv[] )
{
	test_initialisation( );
	test_operateurs_egalite( );
	test_operateurs_logiques( );	
	test_operateurs_binaires( );

	return 0;
}
