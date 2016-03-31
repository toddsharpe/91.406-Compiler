PROGRAM main( input, output ) ;

  VAR x, y, z : INTEGER ;
   
  VAR A,B,C :  ARRAY [ 1..5 ] OF INTEGER ;

 PROCEDURE foo( y : INTEGER )  ;

  VAR f : INTEGER ;
     
  BEGIN

     f := y + x 
      
  END ;
     
BEGIN

   x := 10 ;
   
   B[1] := 2 ;
   
   C[3] := 1 ;
   
   A[ B[ C[3] ] ] := 6 ;
   
   foo ( 10 ) 
    
END.
