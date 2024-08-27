#ifndef MONTY_H
#define MONTY_H

#include <stdio.h>
#include <stdlib.h>

/* Data structure for stack */
typedef struct stack_s
{
    int n;
    struct stack_s *prev;
    struct stack_s *next;
} stack_t;

/* Structure to hold instruction and function pointer */
typedef struct instruction_s
{
    char *opcode;
    void (*f)(stack_t **stack, unsigned int line_number, char *arg);
} instruction_t;

/* Function prototypes */
void push(stack_t **stack, unsigned int line_number, char *arg);
void pall(stack_t **stack, unsigned int line_number, char *arg);
void pint(stack_t **stack, unsigned int line_number, char *arg);
void pop(stack_t **stack, unsigned int line_number, char *arg);
void swap(stack_t **stack, unsigned int line_number, char *arg);
void add(stack_t **stack, unsigned int line_number, char *arg);
void nop(stack_t **stack, unsigned int line_number, char *arg);
void sub(stack_t **stack, unsigned int line_number, char *arg);
void div_op(stack_t **stack, unsigned int line_number, char *arg);
void mul(stack_t **stack, unsigned int line_number, char *arg);
void mod(stack_t **stack, unsigned int line_number, char *arg);
void pchar(stack_t **stack, unsigned int line_number, char *arg);
void pstr(stack_t **stack, unsigned int line_number, char *arg);
void rotl(stack_t **stack, unsigned int line_number, char *arg);
void rotr(stack_t **stack, unsigned int line_number, char *arg); /* Declare rotr */

#endif /* MONTY_H */
