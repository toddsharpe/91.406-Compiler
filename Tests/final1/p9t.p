PROGRAM main(input, output);

VAR x, y, z, a:INTEGER;
VAR t0, t1, t2, t3, t4, t5, t6, t7, t8 :  INTEGER;

BEGIN
   x := 1;
   y := 10;
   z := 3;
   a := 5;

   t0 := x < 10;
   t1 := y > 20;
   t2 := t0 AND t1;
   t3 := z > 5;
   t4 := NOT t3;
   t5 := t2 OR t4;

   write(t0);
   write(t1);
   write(t2);
   write(t3);
   write(t4);
   write(t5);

   
   
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
