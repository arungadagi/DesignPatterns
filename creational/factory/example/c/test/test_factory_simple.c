#include <stdio.h>
#include <math.h>
#include <assert.h>

#include "../factory.h"

int main(void) {
    const double PI = 3.14159265358979323846;

    Shape *s = create_circle(1.0);
    assert(s != NULL);
    double a = shape_area(s);
    assert(fabs(a - PI * 1.0 * 1.0) < 1e-6);
    shape_destroy(s);

    s = create_square(2.0);
    assert(s != NULL);
    a = shape_area(s);
    assert(fabs(a - 4.0) < 1e-6);
    shape_destroy(s);

    printf("C simple tests passed\n");
    return 0;
}
