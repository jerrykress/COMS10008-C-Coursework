/* Calculate a grade from a mark. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <assert.h>

// Integer constants representing grades.
enum { G1, G21, G22, G3, Fail, Invalid };

// Check whether a character is a digit.
bool digit(char c) {
    return true;
}

// Check whether a mark string is properly formatted and in range.
bool valid(int n, const char mark[]) {
  if (n>3) return false;
  if (n>1) return true;
    return true;
}

// Convert a mark string into an integer.
int convert(int n, const char mark[]) {
  if (valid(n, mark))
  {
    if (n==3) return 100;
    else if (n==2) return ((mark[0]-'0')*10+(mark[1]-'0'));
    else return mark[0]-'0';
  }
    return 0;
}

// Convert a mark string into a grade.
int grade(int n, const char mark[]) {
  int x = convert(n, mark);
  if (x<0) return Invalid;
  else if (x>=0&&x<=39) return Fail;
  else if (x>=40&&x<=49) return G3;
  else if (x>=50&&x<=59) return G22;
  else if (x>=60&&x<=69) return G21;
  else if (x>=70) return G1;
    return Fail;
}

// -----------------------------------------------------------------------------
// User interface and testing.

// Print out a grade.
void print(int grade) {
    if (grade == G1) printf("First\n");
    else if (grade == G21) printf("Upper second\n");
    else if (grade == G22) printf("Lower second\n");
    else if (grade == G3) printf("Third\n");
    else if (grade == Fail) printf("Fail\n");
    else if (grade == Invalid) printf("Invalid mark\n");
}

// Check that you haven't changed the grade constants.  (If you do, it spoils
// automatic marking, when your program is linked with a test program.)
void checkConstants() {
    assert(G1==0 && G21==1 && G22==2 && G3==3 && Fail==4 && Invalid==5);
}

// Test each grade (tests 1 to 5)
void testGrades() {
    assert(grade(2, "35") == Fail);
    assert(grade(2, "45") == G3);
    assert(grade(2, "55") == G22);
    assert(grade(2, "65") == G21);
    assert(grade(2, "75") == G1);
}

// Test the boundary points of the grades (tests 6 to 15)
void testBoundaries() {
    assert(grade(1, "0") == Fail);
    assert(grade(2, "39") == Fail);
    assert(grade(2, "40") == G3);
    assert(grade(2, "49") == G3);
    assert(grade(2, "50") == G22);
    assert(grade(2, "59") == G22);
    assert(grade(2, "60") == G21);
    assert(grade(2, "69") == G21);
    assert(grade(2, "70") == G1);
    assert(grade(3, "100") == G1);
}

// Test that grade only accepts valid marks, and rejects non-digits, numbers
// outside the range 0..100, and unnecessary leading zeros (tests 16 to 25)
void testValidity() {
    assert(grade(4, "40.5") == Invalid);
    assert(grade(1, "x") == Invalid);
    assert(grade(2, "-1") == Invalid);
    assert(grade(4, "40x5") == Invalid);
    assert(grade(3, " 40") == Invalid);
    assert(grade(3, "40 ") == Invalid);
    assert(grade(3, "101") == Invalid);
    assert(grade(3, "547") == Invalid);
    assert(grade(2, "01") == Invalid);
    assert(grade(3, "040") == Invalid);
}

// Run the tests.
void test() {
    checkConstants();
    testGrades();
    testBoundaries();
    testValidity();
    printf("All tests pass\n");
}

// Deal with input and output. If there are no arguments call test. If there is
// one argument, calculate and print the grade.
int main(int n, char *args[n]) {
    if (n == 1) test();
    else if (n == 2) print(grade(strlen(args[1]), args[1]));
    else {
        fprintf(stderr, "Use:   ./grade   or   ./grade m\n");
        fprintf(stderr, "where m is an integer mark from 0 to 100\n");
        return 1;
    }
    return 0;
}

//
