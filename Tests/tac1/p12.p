PROGRAM main( input ) ;

VAR x, y : INTEGER ;

FUNCTION gcd(a : INTEGER ; b : INTEGER ) : INTEGER ;

BEGIN

   IF ( b = 0 ) THEN gcd := a
      
   ELSE
      
      gcd := gcd( b, a MOD b ) 
   
END ; 

BEGIN

   x := 144 ;
   y := 72  
   
END.