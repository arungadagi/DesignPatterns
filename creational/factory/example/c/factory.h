/*
 * factory.h
 * Minimal Factory pattern example in C (TDD-driven)
 */
#ifndef CREATIONAL_FACTORY_EXAMPLE_C_FACTORY_H
#define CREATIONAL_FACTORY_EXAMPLE_C_FACTORY_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

typedef struct Shape Shape;

typedef struct ShapeVTable {
    double (*area)(const Shape *self);
    void (*destroy)(Shape *self);
} ShapeVTable;

struct Shape {
    const ShapeVTable *vtable;
};

double shape_area(const Shape *s);
void shape_destroy(Shape *s);

/* Factory creators */
Shape *create_circle(double radius);
Shape *create_square(double side);

#ifdef __cplusplus
}
#endif

#endif /* CREATIONAL_FACTORY_EXAMPLE_C_FACTORY_H */
