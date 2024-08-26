#ifndef MONTY_H
#define MONTY_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 */
typedef struct stack_s
{
    int n;
    struct stack_s *prev;
    struct stack_s *next;
} stack_t;

/**
 * struct instruction_s - opcode and its corresponding function
 * @opcode: the opcode string
 * @f: the function associated with the opcode
 *
 * Description: struct to associate opcodes with their functions
 */
typedef struct instruction_s
{
    char *opcode;
    void (*f)(stack_t **, unsigned int, char *);
} instruction_t;

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

#endif /* MONTY_H */
