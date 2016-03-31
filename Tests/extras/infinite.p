PROGRAM main(input);
VAR x : INTEGER;
PROCEDURE moo;
BEGIN
   x := 7
END;

FUNCTION foo : INTEGER;

   PROCEDURE goo;
   BEGIN
      moo;
      write(x)
   END;

   PROCEDURE loo;
   BEGIN
      x := 6;
      write(x)
   END;

BEGIN
   goo;
   write(x)
END;

BEGIN
   foo
END.
