#ifndef type_h
#define type_h

//Doesn't work for multidimensional arrays...not yet
typedef struct type
{
  int code;

  //For arrays
  int is_array;

  //Constant array offset
  int c;

  struct interval *intervals;  
} Type;

typedef struct interval
{
  int start;
  int end;

  struct interval *next;
} Interval;

//Prototypes
Type *make_type(int code);
Interval *make_interval(int start, int end);

#endif
