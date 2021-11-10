#include "types.h"
#include "user.h"

// Prevent this function from being optimized, which might give it closed form
#pragma GCC push_options
#pragma GCC optimize ("O0")
static int
recurse(int n)
{
  if(n == 0)
    return 0;
  return n + recurse(n - 1);
}
#pragma GCC pop_options

int
main(int argc, char *argv[])
{
  int v, n, m;

  if (argc == 1) {
    v = argc;
    printf(1, "Lab 3 (part 1) - Address at first location: %p\n", &v);
    exit(0);
  }
  else if (argc == 2) {
    n = atoi(argv[1]);
    printf(1, "Lab 3 (part 2) - Recursing %d levels\n", n);
    m = recurse(n);
    printf(1, "Lab 3 (part 2) - Yielded a value of %d\n", m);
    exit(0);
  }
  else {
    printf(1, "Test Part 1 - Usage: $ %s\n", argv[0]);
    printf(1, "Test Part 2 - Usage: $ %s <levels>\n", argv[0]);
    exit(0);
  }
}
