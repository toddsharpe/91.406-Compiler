PROGRAM main( input, output ) ;

  VAR x, y, z : INTEGER ;
   
  VAR A :  ARRAY [ 1..10 ] OF INTEGER ;

  PROCEDURE foo   ;

     VAR c : INTEGER ;
     
     BEGIN

        c := 100 + x 
      
     END ;

FUNCTION goo  : INTEGER ;
		
    VAR d : INTEGER ;
  
     BEGIN

        d := 300 ;

       goo := d * 10
     
      END ;
     
BEGIN

   A[3] := 6 ;
   y := 5 ;
   
   BEGIN

      foo  ;
      
      y := goo
      
   END
    
END.
