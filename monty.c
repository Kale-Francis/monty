#include "monty.h"

#define BUFFER_SIZE 1024

/**
 * push - Pushes an element to the stack.
 * @stack: Double pointer to the top of the stack.
 * @line_number: Line number where the instruction appears.
 * @arg: The argument to be pushed onto the stack.
 */
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

/**
 * pall - Prints all the values on the stack, starting from the top.
 * @stack: Double pointer to the top of the stack.
 * @line_number: Line number where the instruction appears (unused).
 */
void pall(stack_t **stack, unsigned int line_number)
{
    stack_t *current = *stack;

    (void)line_number; /* Avoid unused parameter warning */

    while (current != NULL)
    {
        printf("%d\n", current->n);
        current = current->next;
    }
}

/**
 * pint - Prints the value at the top of the stack.
 * @stack: Double pointer to the top of the stack.
 * @line_number: Line number where the instruction appears.
 */
void pint(stack_t **stack, unsigned int line_number)
{
    if (*stack == NULL)
    {
        fprintf(stderr, "L%u: can't pint, stack empty\n", line_number);
        exit(EXIT_FAILURE);
    }

    printf("%d\n", (*stack)->n);
}

/**
 * pop - Removes the top element of the stack.
 * @stack: Double pointer to the top of the stack.
 * @line_number: Line number where the instruction appears.
 */
void pop(stack_t **stack, unsigned int line_number)
{
    stack_t *temp;

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

/**
 * swap - Swaps the top two elements of the stack.
 * @stack: Double pointer to the top of the stack.
 * @line_number: Line number where the instruction appears.
 */
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

/**
 * add - Adds the top two elements of the stack.
 * @stack: Double pointer to the top of the stack.
 * @line_number: Line number where the instruction appears.
 */
void add(stack_t **stack, unsigned int line_number)
{
    stack_t *first, *second;
    int sum;

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

/**
 * sub - Subtracts the top element of the stack from the second top element.
 * @stack: Double pointer to the top of the stack.
 * @line_number: Line number where the instruction appears.
 */
void sub(stack_t **stack, unsigned int line_number)
{
    stack_t *first, *second;
    int difference;

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

/**
 * div_op - Divides the second top element of the stack by the top element.
 * @stack: Double pointer to the top of the stack.
 * @line_number: Line number where the instruction appears.
 */
void div_op(stack_t **stack, unsigned int line_number)
{
    stack_t *first, *second;
    int result;

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

/**
 * nop - Does nothing.
 * @stack: Double pointer to the top of the stack (unused).
 * @line_number: Line number where the instruction appears (unused).
 */
void nop(stack_t **stack, unsigned int line_number)
{
    (void)stack;      /* Avoid unused parameter warning */
    (void)line_number; /* Avoid unused parameter warning */
}

/**
 * main - Entry point for the Monty bytecode interpreter.
 * @argc: Argument count.
 * @argv: Argument vector.
 *
 * Return: EXIT_SUCCESS on success, or EXIT_FAILURE on failure.
 */
int main(int argc, char *argv[])
{
    FILE *file;
    char line[BUFFER_SIZE];
    unsigned int line_number = 0;
    stack_t *stack = NULL;
    char *opcode;
    char *arg;

    if (argc != 2)
    {
        fprintf(stderr, "USAGE: monty file\n");
        return (EXIT_FAILURE);
    }

    file = fopen(argv[1], "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
        return (EXIT_FAILURE);
    }

    while (fgets(line, BUFFER_SIZE, file) != NULL)
    {
        line_number++;
        opcode = strtok(line, " \n");
        arg = strtok(NULL, " \n");

        if (opcode == NULL || opcode[0] == '#')
            continue;

        if (strcmp(opcode, "push") == 0)
            push(&stack, line_number, arg);
        else if (strcmp(opcode, "pall") == 0)
            pall(&stack, line_number);
        else if (strcmp(opcode, "pint") == 0)
            pint(&stack, line_number);
        else if (strcmp(opcode, "pop") == 0)
            pop(&stack, line_number);
        else if (strcmp(opcode, "swap") == 0)
            swap(&stack, line_number);
        else if (strcmp(opcode, "add") == 0)
            add(&stack, line_number);
        else if (strcmp(opcode, "nop") == 0)
            nop(&stack, line_number);
        else if (strcmp(opcode, "sub") == 0)
            sub(&stack, line_number);
        else if (strcmp(opcode, "div") == 0)
            div_op(&stack, line_number);
        else
        {
            fprintf(stderr, "L%u: unknown instruction %s\n", line_number, opcode);
            fclose(file);
            return (EXIT_FAILURE);
        }
    }

    fclose(file);
    return (EXIT_SUCCESS);
}
