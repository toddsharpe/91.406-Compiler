PROGRAM main(input, ouput);

VAR x, y, z : INTEGER;
VAR A : ARRAY[1..10] OF INTEGER;

PROCEDURE foo;
VAR c : INTEGER;

BEGIN
   c := 100+x;
   write(x);
   write(c)
END; { foo }

FUNCTION goo : INTEGER;
VAR d : INTEGER;

BEGIN
   write(z);
   write(y);
   d:=300;
   y := y * 10;
   write(y);
   goo := d * 10;
   write(z);
   write(y)
END; { goo }

BEGIN
   A[3] := 6;
   y := 5;
   x := 100;
   z := 5 * (y + x) * 10;
   write(z);

BEGIN
   foo;
   y := goo;
   write(y)
END

END.
