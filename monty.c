#include "monty.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
void rotr(stack_t **stack, unsigned int line_number, char *arg); /* Function prototype for rotr */

/* Function implementations */

void push(stack_t **stack, unsigned int line_number, char *arg)
{
    int num;
    stack_t *new_node;

    if (arg == NULL || ((num = atoi(arg)) == 0 && strcmp(arg, "0") != 0))
    {
        fprintf(stderr, "L%u: usage: push integer\n", line_number);
        exit(EXIT_FAILURE);
    }

    new_node = malloc(sizeof(stack_t));
    if (new_node == NULL)
    {
        fprintf(stderr, "Error: malloc failed\n");
        exit(EXIT_FAILURE);
    }

    new_node->n = num;
    new_node->prev = NULL;
    new_node->next = *stack;

    if (*stack != NULL)
        (*stack)->prev = new_node;

    *stack = new_node;
}

void pall(stack_t **stack, unsigned int line_number, char *arg)
{
    stack_t *current;

    (void)line_number; /* Avoid unused parameter warning */
    (void)arg;        /* Avoid unused parameter warning */

    current = *stack;

    while (current != NULL)
    {
        printf("%d\n", current->n);
        current = current->next;
    }
}

void pint(stack_t **stack, unsigned int line_number, char *arg)
{
    (void)arg; /* Avoid unused parameter warning */

    if (*stack == NULL)
    {
        fprintf(stderr, "L%u: can't pint, stack empty\n", line_number);
        exit(EXIT_FAILURE);
    }

    printf("%d\n", (*stack)->n);
}

void pop(stack_t **stack, unsigned int line_number, char *arg)
{
    stack_t *temp;

    (void)arg; /* Avoid unused parameter warning */

    if (*stack == NULL)
    {
        fprintf(stderr, "L%u: can't pop an empty stack\n", line_number);
        exit(EXIT_FAILURE);
    }

    temp = *stack;
    *stack = (*stack)->next;

    if (*stack != NULL)
        (*stack)->prev = NULL;

    free(temp);
}

void swap(stack_t **stack, unsigned int line_number, char *arg)
{
    stack_t *first, *second;

    (void)arg; /* Avoid unused parameter warning */

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

void add(stack_t **stack, unsigned int line_number, char *arg)
{
    stack_t *first, *second;
    int sum;

    (void)arg; /* Avoid unused parameter warning */

    if (*stack == NULL || (*stack)->next == NULL)
    {
        fprintf(stderr, "L%u: can't add, stack too short\n", line_number);
        exit(EXIT_FAILURE);
    }

    first = *stack;
    second = (*stack)->next;

    sum = first->n + second->n;
    second->n = sum;

    *stack = second;
    free(first);
}

void sub(stack_t **stack, unsigned int line_number, char *arg)
{
    stack_t *first, *second;
    int difference;

    (void)arg; /* Avoid unused parameter warning */

    if (*stack == NULL || (*stack)->next == NULL)
    {
        fprintf(stderr, "L%u: can't sub, stack too short\n", line_number);
        exit(EXIT_FAILURE);
    }

    first = *stack;
    second = (*stack)->next;

    difference = second->n - first->n;
    second->n = difference;

    *stack = second;
    free(first);
}

void div_op(stack_t **stack, unsigned int line_number, char *arg)
{
    stack_t *first, *second;
    int result;

    (void)arg; /* Avoid unused parameter warning */

    if (*stack == NULL || (*stack)->next == NULL)
    {
        fprintf(stderr, "L%u: can't div, stack too short\n", line_number);
        exit(EXIT_FAILURE);
    }

    first = *stack;
    second = (*stack)->next;

    if (first->n == 0)
    {
        fprintf(stderr, "L%u: division by zero\n", line_number);
        exit(EXIT_FAILURE);
    }

    result = second->n / first->n;
    second->n = result;

    *stack = second;
    free(first);
}

void mul(stack_t **stack, unsigned int line_number, char *arg)
{
    stack_t *first, *second;
    int result;

    (void)arg; /* Avoid unused parameter warning */

    if (*stack == NULL || (*stack)->next == NULL)
    {
        fprintf(stderr, "L%u: can't mul, stack too short\n", line_number);
        exit(EXIT_FAILURE);
    }

    first = *stack;
    second = (*stack)->next;

    result = second->n * first->n;
    second->n = result;

    *stack = second;
    free(first);
}

void mod(stack_t **stack, unsigned int line_number, char *arg)
{
    stack_t *first, *second;
    int result;

    (void)arg; /* Avoid unused parameter warning */

    if (*stack == NULL || (*stack)->next == NULL)
    {
        fprintf(stderr, "L%u: can't mod, stack too short\n", line_number);
        exit(EXIT_FAILURE);
    }

    first = *stack;
    second = (*stack)->next;

    if (first->n == 0)
    {
        fprintf(stderr, "L%u: division by zero\n", line_number);
        exit(EXIT_FAILURE);
    }

    result = second->n % first->n;
    second->n = result;

    *stack = second;
    free(first);
}

void pchar(stack_t **stack, unsigned int line_number, char *arg)
{
    (void)arg; /* Avoid unused parameter warning */

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

void pstr(stack_t **stack, unsigned int line_number, char *arg)
{
    stack_t *current;

    (void)line_number; /* Avoid unused parameter warning */
    (void)arg;        /* Avoid unused parameter warning */

    current = *stack;

    while (current != NULL && current->n != 0 && current->n >= 0 && current->n <= 127)
    {
        printf("%c", current->n);
        current = current->next;
    }

    printf("\n");
}

void rotl(stack_t **stack, unsigned int line_number, char *arg)
{
    stack_t *top, *bottom;

    (void)line_number; /* Avoid unused parameter warning */
    (void)arg;        /* Avoid unused parameter warning */

    if (*stack == NULL || (*stack)->next == NULL)
        return; /* No need to rotate if the stack is empty or has only one element */

    top = *stack;
    bottom = *stack;

    /* Find the bottom node */
    while (bottom->next != NULL)
    {
        bottom = bottom->next;
    }

    /* Rotate the stack */
    *stack = top->next;
    (*stack)->prev = NULL;

    top->next = NULL;
    top->prev = bottom;
    bottom->next = top;
}

void rotr(stack_t **stack, unsigned int line_number, char *arg)
{
    stack_t *top, *bottom;

    (void)line_number; /* Avoid unused parameter warning */
    (void)arg;        /* Avoid unused parameter warning */

    if (*stack == NULL || (*stack)->next == NULL)
        return; /* No need to rotate if the stack is empty or has only one element */

    bottom = *stack;

    /* Find the bottom node */
    while (bottom->next != NULL)
    {
        bottom = bottom->next;
    }

    /* If the stack has more than one element */
    if (bottom != *stack)
    {
        top = *stack;

        /* Remove the bottom node from the stack */
        bottom->prev->next = NULL;
        bottom->prev = NULL;

        /* Move the bottom node to the top of the stack */
        bottom->next = top;
        top->prev = bottom;
        *stack = bottom;
    }
}

void nop(stack_t **stack, unsigned int line_number, char *arg)
{
    (void)stack; /* Avoid unused parameter warning */
    (void)line_number; /* Avoid unused parameter warning */
    (void)arg; /* Avoid unused parameter warning */
}

/* main function */
int main(int argc, char *argv[])
{
    FILE *file;
    char line[1024];
    char *opcode, *arg;
    unsigned int line_number;
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
        {"pstr", pstr},
        {"rotl", rotl},
        {"rotr", rotr}, /* Add rotr to the instructions array */
        {NULL, NULL}
    };
    instruction_t *instr;
    stack_t *stack = NULL; /* Initialize stack */

    if (argc != 2)
    {
        fprintf(stderr, "Usage: monty file\n");
        return (EXIT_FAILURE);
    }

    file = fopen(argv[1], "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
        return (EXIT_FAILURE);
    }

    line_number = 1;
    while (fgets(line, sizeof(line), file) != NULL)
    {
        opcode = strtok(line, " \n");
        arg = strtok(NULL, " \n");
        instr = instructions;

        if (opcode == NULL || line[0] == '#')
            continue;

        while (instr->opcode != NULL)
        {
            if (strcmp(opcode, instr->opcode) == 0)
            {
                instr->f(&stack, line_number, arg);
                break;
            }
            instr++;
        }

        if (instr->opcode == NULL)
        {
            fprintf(stderr, "L%u: unknown instruction %s\n", line_number, opcode);
            fclose(file);
            return (EXIT_FAILURE);
        }

        line_number++;
    }

    fclose(file);
    return (EXIT_SUCCESS);
}
