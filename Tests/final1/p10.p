PROGRAM main(input);

VAR A:ARRAY[-10..10] OF INTEGER;

FUNCTION foo(x : INTEGER) : INTEGER;

BEGIN
   write(x);
   foo := x * 1000
END; { foo }

PROCEDURE goo (a : INTEGER; b:INTEGER; c:INTEGER);

BEGIN

   write(400);
   a:=foo(b)+foo(c);
   write(a)

END; { goo }

PROCEDURE moo;
BEGIN
   write(300);
   goo(10, 20, 30)
END; { moo }

BEGIN

   A[-3] := 100;
   A[2 + 3 * 1] := 200;
   moo;
   write(1000)

END.
