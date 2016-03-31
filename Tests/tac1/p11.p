PROGRAM main( input ) ;

VAR A : ARRAY[ -10 .. 10 ] OF INTEGER ;

FUNCTION foo( x : INTEGER  ) : INTEGER ;

BEGIN

   foo := x * 1000
   
END;


PROCEDURE goo(  a : INTEGER ; b : INTEGER ; c : INTEGER ) ;

BEGIN

   a :=  foo( b ) + foo( c ) 
   
END; 

PROCEDURE moo ;

BEGIN

   goo( 10, 20, 30 ) 
   
END; 


BEGIN

   A[-3] := 100 ;
   moo 
   
END.