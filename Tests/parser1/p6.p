PROGRAM test6 ( input, output ) ;

   VAR x,y,z : INTEGER ;
   VAR a,b,c : REAL    ;
   VAR M :   ARRAY [1..10] OF INTEGER ;

   FUNCTION foo( a , b : INTEGER ; c : REAL ) : INTEGER ;

      VAR x, y, z : INTEGER ;
   
      BEGIN

	 a := 10 ;
	 b := a MOD 3 ;
	 bar( 1000 ) ;
	 foo := 42 
   
      END ;
   

   PROCEDURE bar(a	: INTEGER ) ;

      VAR x, y, z : REAL ; 
      VAR N :  ARRAY [1..100] OF REAL ;
   
      BEGIN

         IF ( NOT ((z + y) < x) ) THEN N[ 10 + 12 ] := 511 ELSE a := 44 
   
      END ;
	       

   BEGIN

      M[2] := 511 ;

      x := a + b ;

      WHILE ( ( a < +5 ) AND ( b > 10 )  OR ( c <> 3 ) ) DO

      BEGIN

	 c := foo( 3, 4, 5 ) ;
	 z := a DIV b ;
	 b := -c

      END 
      
   END.
