#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "monty.h"

/* Push function implementation */
void push(stack_t **stack, unsigned int line_number)
{
    char *arg = strtok(NULL, " \n");
    int value;
    stack_t *new_node;

    if (arg == NULL || (atoi(arg) == 0 && strcmp(arg, "0") != 0))
    {
        fprintf(stderr, "L%u: usage: push integer\n", line_number);
        exit(EXIT_FAILURE);
    }

    value = atoi(arg);

    new_node = malloc(sizeof(stack_t));
    if (new_node == NULL)
    {
        fprintf(stderr, "Error: malloc failed\n");
        exit(EXIT_FAILURE);
    }

    new_node->n = value;
    new_node->next = *stack;
    new_node->prev = NULL;

    if (*stack != NULL)
        (*stack)->prev = new_node;

    *stack = new_node;
}

/* Pall function implementation */
void pall(stack_t **stack, unsigned int line_number)
{
    stack_t *current;

    (void)line_number; /* Unused parameter */

    current = *stack;
    while (current != NULL)
    {
        printf("%d\n", current->n);
        current = current->next;
    }
}

/* Pint function implementation */
void pint(stack_t **stack, unsigned int line_number)
{
    if (*stack == NULL)
    {
        fprintf(stderr, "L%u: can't pint, stack empty\n", line_number);
        exit(EXIT_FAILURE);
    }

    printf("%d\n", (*stack)->n);
}

/* Pop function implementation */
void pop(stack_t **stack, unsigned int line_number)
{
    stack_t *top;

    if (*stack == NULL)
    {
        fprintf(stderr, "L%u: can't pop an empty stack\n", line_number);
        exit(EXIT_FAILURE);
    }

    top = *stack;
    *stack = (*stack)->next;

    if (*stack != NULL)
        (*stack)->prev = NULL;

    free(top);
}

/* Swap function implementation */
void swap(stack_t **stack, unsigned int line_number)
{
    stack_t *first, *second;

    if (*stack == NULL || (*stack)->next == NULL)
    {
        fprintf(stderr, "L%u: can't swap, stack too short\n", line_number);
        exit(EXIT_FAILURE);
    }

    first = *stack;
    second = (*stack)->next;

    first->next = second->next;
    if (second->next != NULL)
        second->next->prev = first;

    second->prev = NULL;
    second->next = first;
    first->prev = second;

    *stack = second;
}

/* Add function implementation */
void add(stack_t **stack, unsigned int line_number)
{
    stack_t *top;
    int sum;

    if (*stack == NULL || (*stack)->next == NULL)
    {
        fprintf(stderr, "L%u: can't add, stack too short\n", line_number);
        exit(EXIT_FAILURE);
    }

    top = *stack;
    sum = top->n + top->next->n;

    pop(stack, line_number);
    (*stack)->n = sum;
}

/* Nop function implementation */
void nop(stack_t **stack, unsigned int line_number)
{
    (void)stack; /* Unused parameter */
    (void)line_number; /* Unused parameter */
}

/* Sub function implementation */
void sub(stack_t **stack, unsigned int line_number)
{
    stack_t *top;
    int diff;

    if (*stack == NULL || (*stack)->next == NULL)
    {
        fprintf(stderr, "L%u: can't sub, stack too short\n", line_number);
        exit(EXIT_FAILURE);
    }

    top = *stack;
    diff = top->next->n - top->n;

    pop(stack, line_number);
    (*stack)->n = diff;
}

/* Div function implementation */
void div_op(stack_t **stack, unsigned int line_number)
{
    stack_t *top;
    int divisor;

    if (*stack == NULL || (*stack)->next == NULL)
    {
        fprintf(stderr, "L%u: can't div, stack too short\n", line_number);
        exit(EXIT_FAILURE);
    }

    if ((*stack)->n == 0)
    {
        fprintf(stderr, "L%u: division by zero\n", line_number);
        exit(EXIT_FAILURE);
    }

    top = *stack;
    divisor = top->next->n / top->n;

    pop(stack, line_number);
    (*stack)->n = divisor;
}

/* Mul function implementation */
void mul(stack_t **stack, unsigned int line_number)
{
    stack_t *top;
    int product;

    if (*stack == NULL || (*stack)->next == NULL)
    {
        fprintf(stderr, "L%u: can't mul, stack too short\n", line_number);
        exit(EXIT_FAILURE);
    }

    top = *stack;
    product = top->n * top->next->n;

    pop(stack, line_number);
    (*stack)->n = product;
}

/* Mod function implementation */
void mod(stack_t **stack, unsigned int line_number)
{
    stack_t *top;
    int remainder;

    if (*stack == NULL || (*stack)->next == NULL)
    {
        fprintf(stderr, "L%u: can't mod, stack too short\n", line_number);
        exit(EXIT_FAILURE);
    }

    if ((*stack)->n == 0)
    {
        fprintf(stderr, "L%u: division by zero\n", line_number);
        exit(EXIT_FAILURE);
    }

    top = *stack;
    remainder = top->next->n % top->n;

    pop(stack, line_number);
    (*stack)->n = remainder;
}

/* Pchar function implementation */
void pchar(stack_t **stack, unsigned int line_number)
{
    if (*stack == NULL)
    {
        fprintf(stderr, "L%u: can't pchar, stack empty\n", line_number);
        exit(EXIT_FAILURE);
    }

    if ((*stack)->n < 0 || (*stack)->n > 127)
    {
        fprintf(stderr, "L%u: can't pchar, value out of range\n", line_number);
        exit(EXIT_FAILURE);
    }

    printf("%c\n", (*stack)->n);
}

/* Main function implementation */
int main(int argc, char *argv[])
{
    FILE *file;
    char *line = NULL;
    size_t len = 0;
    int line_number = 1;
    stack_t *stack = NULL;
    char *opcode;
    int i;
    instruction_t instructions[] = {
        {"push", push},
        {"pall", pall},
        {"pint", pint},
        {"pop", pop},
        {"swap", swap},
        {"add", add},
        {"nop", nop},
        {"sub", sub},
        {"div", div_op},
        {"mul", mul},
        {"mod", mod},
        {"pchar", pchar},
        {NULL, NULL}
    };

    if (argc != 2)
    {
        fprintf(stderr, "USAGE: monty file\n");
        exit(EXIT_FAILURE);
    }

    file = fopen(argv[1], "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        if (getline(&line, &len, file) == -1)
        {
            if (feof(file))
                break;

            fprintf(stderr, "Error: getline failed\n");
            exit(EXIT_FAILURE);
        }

        if (line[0] == '#' || line[0] == '\n')
            continue;

        opcode = strtok(line, " \n");

        if (opcode == NULL)
            continue;

        for (i = 0; instructions[i].opcode != NULL; i++)
        {
            if (strcmp(opcode, instructions[i].opcode) == 0)
            {
                instructions[i].f(&stack, line_number);
                break;
            }
        }

        if (instructions[i].opcode == NULL)
        {
            fprintf(stderr, "L%u: unknown instruction %s\n", line_number, opcode);
            fclose(file);
            exit(EXIT_FAILURE);
        }

        line_number++;
    }

    free(line);
    fclose(file);
    return (EXIT_SUCCESS);
}
