#include  <cstdio>

 punto de 
estructura { 
    flotante x ; 
    flotador y ; 
} ;

// interpolaci�n lineal simple entre dos puntos
 void  lerp ( point & dest ,  const point & a ,  const point & b ,  const  float t ) 
{ 
    dest . x = a . x +  ( b . x - a . x ) * t ; 
    dest . y = a . y +  ( b .y - a . y ) * t ; 
}

// eval�a un punto en una curva bezier. t va de 0 a 1.0
 vac�o  bezier ( punto  , t ); // punto entre ayb (verde) y dest ,  punto const & a ,  punto const & b ,  punto const & c ,  punto const & d ,  const  float t ) 
{ 
    punto ab , bc , cd , abbc , bccd ; 
    lerp ( ab , a , b           
     lerp ( bc , b , c , t );            // punto entre byc (verde) 
    lerp ( cd , c , d , t );            // punto entre c y d (verde) 
    lerp ( abbc , ab , bc , t );        // punto entre ab y bc (azul) 
    lerp ( bccd , bc , cd , t );       // punto entre bc y cd (azul) 
    lerp ( dest , abbc , bccd , t );    // punto en la curva de bezier (negro)
 }

// peque�o programa de prueba ... solo imprime los puntos
 int  main () 
{ 
    // 4 puntos definen la curva bezier. Estos son los puntos utilizados 
    // para las im�genes de ejemplo en esta p�gina. 
    punto a =  {  40 ,  100  } ; 
    punto b =  {  80 ,  20   } ; 
    punto c =  {  150 ,  180  } ; 
    punto d =  {  260 ,  100  } ;

    para  ( int i = 0 ; i < 1000 ;  ++ i ) 
    {
	 punto p ; 
	float t =  static_cast < float > ( i ) / 999.0 ; 
	bezier ( p , a , b , c , d , t ); 
	printf ( "% f% f \ n " , p . x , p . y );
    }

    devuelve  0 ; 
}
