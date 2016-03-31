PROGRAM main( input, output ) ;

  VAR x : INTEGER       ;  
  VAR y : INTEGER       ;
  VAR A :  ARRAY [ 1..10 ] OF INTEGER ;
   
BEGIN

   A[3] := 6 ;
   y := 5 ;
   
   WHILE ( 6 > 1 ) AND ( y < 10 )  DO
      
   BEGIN
      
      x := 2 ;
      
      A[ x + 1 ] := 511 ;
      
      IF ( y > 100 ) THEN A[1] := 50  ELSE A[1] := 100 
      
   END
   
END.
