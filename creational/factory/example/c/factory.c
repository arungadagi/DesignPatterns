/*
 * factory.c
 * Implementation of factory-created Shapes.
 */
#include "factory.h"
#include <stdlib.h>

static const double PI = 3.14159265358979323846;

typedef struct Circle {
    Shape base;
    double radius;
} Circle;

static double circle_area(const Shape *s) {
    const Circle *c = (const Circle*)s;
    return PI * c->radius * c->radius;
}

static void circle_destroy(Shape *s) {
    free((void*)s);
}

static const ShapeVTable circle_vtable = {
    .area = circle_area,
    .destroy = circle_destroy
};

Shape *create_circle(double radius) {
    Circle *c = (Circle*)malloc(sizeof(Circle));
    if (!c) return NULL;
    c->base.vtable = &circle_vtable;
    c->radius = radius;
    return (Shape*)c;
}

typedef struct Square {
    Shape base;
    double side;
} Square;

static double square_area(const Shape *s) {
    const Square *sq = (const Square*)s;
    return sq->side * sq->side;
}

static void square_destroy(Shape *s) {
    free((void*)s);
}

static const ShapeVTable square_vtable = {
    .area = square_area,
    .destroy = square_destroy
};

Shape *create_square(double side) {
    Square *sq = (Square*)malloc(sizeof(Square));
    if (!sq) return NULL;
    sq->base.vtable = &square_vtable;
    sq->side = side;
    return (Shape*)sq;
}

double shape_area(const Shape *s) {
    if (!s || !s->vtable || !s->vtable->area) return 0.0;
    return s->vtable->area(s);
}

void shape_destroy(Shape *s) {
    if (!s || !s->vtable || !s->vtable->destroy) return;
    s->vtable->destroy(s);
}
