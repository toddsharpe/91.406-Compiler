PROGRAM main(input);

VAR x, y, z : INTEGER;

FUNCTION gcd(a : INTEGER; b:INTEGER) : INTEGER;

BEGIN
   IF (b = 0) THEN gcd := a
   ELSE
      gcd := gcd(b, a MOD b)
END; { gcd }

BEGIN
   x := 66;
   y := 72;
   z := gcd(x, y);
   PRINT z

END.
