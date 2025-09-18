#include "expr.h"
#include "stdlib.h"
#include "stdio.h"


struct Expr *mk_plus(struct Expr *e1, struct Expr *e2) {
    struct Expr *ret = malloc(sizeof(struct Expr));
    ret->type = PLUS;
    ret->subexprs.e1 = e1;
    ret->subexprs.e2 = e2;

    return ret;
}

struct Expr *mk_minus(struct Expr *e1, struct Expr *e2) {
    struct Expr *ret = malloc(sizeof(struct Expr));
    ret->type = MINUS;
    ret->subexprs.e1 = e1;
    ret->subexprs.e2 = e2;

    return ret;
}

struct Expr *mk_times(struct Expr *e1, struct Expr *e2) {
    struct Expr *ret =  malloc(sizeof(struct Expr));
    ret->type = TIMES;
    ret->subexprs.e1 = e1;
    ret->subexprs.e2 = e2;

    return ret;
}

struct Expr *mk_div(struct Expr *e1, struct Expr *e2) {
    struct Expr *ret = malloc(sizeof(struct Expr));
    ret->type = DIV;
    ret->subexprs.e1 = e1;
    ret->subexprs.e2 = e2;

    return ret;
}

struct Expr *mk_float(float f) {
    struct Expr *ret = malloc(sizeof(struct Expr));
    ret->type = FLOAT;
    ret->literal = f;

    return ret;
}

/* This function should create the expr (2 + (5 * 3))
 * using the above constructors.
 */
struct Expr *mk_expr1() {
    /* TODO: Your code here */
    return mk_plus(mk_float(2.0), mk_times(mk_float(5.0), mk_float(3.0)));
}

/* This function should create the expr (3 + (1 / 8))
 * using the above constructors.
 */
struct Expr *mk_expr2() {
    /* TODO: Your code here */
     return mk_plus(mk_float(3.0), mk_div(mk_float(1.0), mk_float(8.0)));
}

/* This function should create the expr ((4 / 3) - (4 / (2 + 3)))
 * using the above constructors.
 */
struct Expr *mk_expr3() {
    /* TODO: Your code here */
     return mk_minus(
        mk_div(mk_float(4.0), mk_float(3.0)),
        mk_div(mk_float(4.0), mk_plus(mk_float(2.0), mk_float(3.0)))
    );
}


/*
 * This function should free all memory associated 
 * with the given AST.
*/
void free_expr(struct Expr* e) {
    /* TODO: Your code here */
    if (e == NULL) {
        return;
    }
    
    // If it's not a leaf node (FLOAT), free the children first
    if (e->type != FLOAT) {
        free_expr(e->subexprs.e1);
        free_expr(e->subexprs.e2);
    }
    
    // Free the current node
    free(e);
}

/*
 * This function should evaluate the given AST and
 * return the floating-point result.
*/
float eval(struct Expr* e) {
    /* TODO: Your code here */
     if (e == NULL) {
        return 0.0;
    }
    
    switch (e->type) {
        case FLOAT:
            return e->literal;
        case PLUS:
            return eval(e->subexprs.e1) + eval(e->subexprs.e2);
        case MINUS:
            return eval(e->subexprs.e1) - eval(e->subexprs.e2);
        case TIMES:
            return eval(e->subexprs.e1) * eval(e->subexprs.e2);
        case DIV:
            return eval(e->subexprs.e1) / eval(e->subexprs.e2);
        default:
            return 0.0; // Should never reach here since it is exhaustive,
    }
}




