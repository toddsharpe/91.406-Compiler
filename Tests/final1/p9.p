PROGRAM main(input, output);

VAR x, y, z, a:INTEGER;

BEGIN
   x := 1;
   y := 10;
   z := 3;
   a := 5;

   IF ((x < 10) AND (y > 10)) OR (NOT (z > 5)) THEN
   BEGIN
      write(z);
      IF (a + 10 > 2) THEN x := 1000 ELSE x := 2000
   END

   ELSE

   BEGIN
      write(z * 10);
      y := 5000
   END;

   write(x);
   write(-1);
   write(y)

END.
