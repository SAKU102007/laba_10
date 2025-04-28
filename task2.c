// Структура содержит информацию об экскурсионных турах: стоимость
// (число), название (указатель), вложенную структуру – дату начала (строка
// фиксированной длины) и количество дней. Найти туры со стоимостью
// меньше заданной. Удалить туры с заданным названием.

// Сакута

// 26.04.2025

#include "functions.h"


int main() {
    ExcursionTour* tours = NULL;
    int tourCount = 0;
    int choice;
    
    do {

        printf("\nМеню:\n");
        printf("1. Добавить тур\n");
        printf("2. Показать все туры\n");
        printf("3. Найти туры дешевле заданной цены\n");
        printf("4. Удалить туры с заданным названием\n");
        printf("0. Выход\n");
        printf("Выберите действие: ");
        scanf("%d", &choice);
        printf("\n");
        
        while(getchar() != '\n');
        
        switch(choice) {
            case 1: {
                tours = addTour(tours, &tourCount);
                if (!tours) {
                    printf("Ошибка выделения памяти!\n");
                    return 1;
                }
                break;
            }
            case 2: {
                printAllTours(tours, tourCount);
                break;
            }
            case 3: {
                float maxPrice;
                printf("Введите максимальную цену: ");
                scanf("%f", &maxPrice);
                findToursByPrice(tours, tourCount, maxPrice);
                break;
            }
            case 4: {
                char nameToRemove[100];
                printf("Введите название тура для удаления: ");
                fgets(nameToRemove, 100, stdin);
                nameToRemove[strcspn(nameToRemove, "\n")] = '\0';
                
                int removed = removeToursByName(tours, &tourCount, nameToRemove);
                printf("Все туры с названием '%s' (в количестве %d) успешно удалены!\n", nameToRemove, removed);
                break;
            }
            case 0: {
                printf("Выход из программы\n");
                break;
            }
            default: {
                printf("Введено неверное число. Попробуйте снова.\n");
                break;
            }
        }

    } while(choice != 0);
    
    for (int i = 0; i < tourCount; i++) {
        freeTour(&tours[i]);
    }
    free(tours);

    return 0;
}
