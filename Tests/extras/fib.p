PROGRAM main(input);
VAR x : ARRAY [1 .. 30] OF INTEGER;
VAR c : INTEGER;

BEGIN
   x[1] := 1;
   x[2] := 1;

   c := 3;

   {generate}
   WHILE (c <= 30) DO
   BEGIN
      x[c] := x[c-1] + x[c-2];
      c := c + 1
   END;

   {display}
   c := 1;
   WHILE (c <= 30) DO
   BEGIN
      write(x[c]);
      c := c + 1
   END
   
END.
