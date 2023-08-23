#include "main.h"

void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - Printf function
 * @format: format.
 * Return: Printed chars.
 */
int _printf(const char *format, ...)
{
    int i, printed = 0, printed_chars = 0;
    int buff_ind = 0;
    va_list list;
    char buffer[BUFF_SIZE];

    if (format == NULL)
        return (-1);

    va_start(list, format);

    for (i = 0; format && format[i] != '\0'; i++)
    {
        if (format[i] != '%')
        {
            buffer[buff_ind++] = format[i];
            if (buff_ind == BUFF_SIZE)
                print_buffer(buffer, &buff_ind);
            printed_chars++;
        }
        else
        {
            print_buffer(buffer, &buff_ind);
            ++i;
            printed = handle_print(format, &i, list, buffer);
            if (printed == -1)
                return (-1);
            printed_chars += printed;
        }
    }

    print_buffer(buffer, &buff_ind);

    va_end(list);

    return (printed_chars);
}

/**
 * print_buffer - Prints the contents of the buffer if it exists
 * @buffer: Array of chars
 * @buff_ind: Index at which to add next char, represents the length.
 */
void print_buffer(char buffer[], int *buff_ind)
{
    if (*buff_ind > 0)
        write(1, &buffer[0], *buff_ind);

    *buff_ind = 0;
}

/**
 * handle_print - Handles format specifiers and prints accordingly
 * @format: The format string
 * @i: Pointer to the current position in the format string
 * @list: The variable argument list
 * @buffer: Buffer to store characters
 * Return: Number of characters printed
 */
int handle_print(const char *format, int *i, va_list list, char buffer[])
{
    // Implementation for handling %d and %i format specifiers
    if (format[*i] == 'd' || format[*i] == 'i')
    {
        int num = va_arg(list, int);
        char num_str[12]; // Assuming maximum integer length is 11 digits
        snprintf(num_str, sizeof(num_str), "%d", num);
        int len = 0;
        while (num_str[len] != '\0')
        {
            buffer[*i] = num_str[len++];
            (*i)++;
        }
        return len;
    }
    else
    {
        // Handle other format specifiers (e.g., %c, %s, %%, etc.) as before
    }
}
