// Для целого числа (int) вывести содержимое каждого байта (в десятичной
// системе счисления).

// Сакута

// 20.04.2025

#include <stdio.h>

typedef struct {
    unsigned first_byte : 8;
    unsigned second_byte : 8;
    unsigned third_byte : 8;
    unsigned fourth_byte : 8;
} int_per_byte;

int main()
{
    long int num;


    while (1)
    {
        printf("Введите целое число (Введите '0' для завершения работы программы): ");
        if (scanf("%ld", &num) != 1)
        {
            printf("Ошибка ввода. Пожалуйста, введите целое число.\n");
            while (getchar() != '\n');
        }

        else {
            if (num == 0)
            return 0;

            if (!(num < -2147483648 || num > 2147483647))
            {
                int_per_byte num_per_byte;
                char *bytes = (char *)&num_per_byte;

                for (int i = 0; i < 4; i++)
                {
                    bytes[i] = num % 256;
                    num /= 256;
                }

                printf("Первый байт = %d\n"
                       "Второй байт = %d\n"
                       "Третий байт = %d\n"
                       "Четвёртый байт = %d\n",
                       num_per_byte.first_byte, num_per_byte.second_byte, num_per_byte.third_byte, num_per_byte.fourth_byte);

                // // альтернативный способ вывода
                //     for (int i = 0; i < 4; i++)
                //         printf("%d байт = %d\n", i + 1, bytes[i]);
            }

            else printf("Число выходит за пределы допустимого диапазона.\n");
        }


        

    }

    return 0;
}
