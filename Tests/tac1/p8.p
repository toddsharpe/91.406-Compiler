PROGRAM main( input, output ) ;

  VAR x, y, z : INTEGER ;
   
  VAR A :  ARRAY [ 1..10 ] OF INTEGER ;

 PROCEDURE foo( x : INTEGER )  ;

  VAR c : INTEGER ;
     
  BEGIN

     c := 100 + x 
      
  END ;

FUNCTION goo( b : INTEGER ) : INTEGER ;
		
  VAR d : INTEGER ;
  
  BEGIN

     d := 300 ;
     
     b := 500 ;

     goo := d * b
     
  END ;
     
BEGIN

   A[3] := 511  ;
   
   BEGIN

      foo( 100 ) ;
      
      y := goo( 2 ) 
      
   END
    
END.
