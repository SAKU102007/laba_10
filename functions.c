#include "functions.h"

void inputTour(ExcursionTour* tour) {
    while (1) {
        printf("Введите название тура (до 100 символов): ");
        char buffer[100];
        fgets(buffer, 100, stdin);
        
        if (strchr(buffer, '\n') == NULL && strlen(buffer) == 99) {
            printf("Ошибка: название слишком длинное (максимум 100 символов).\n");
            while (getchar() != '\n'); // Очистка буфера
            continue;
        }
        
        buffer[strcspn(buffer, "\n")] = '\0';

        if (strlen(buffer) == 0) {
            printf("Ошибка: название не может быть пустым.\n");
            continue;
        }
        
        tour->name = (char*)malloc(strlen(buffer) + 1);
        if (tour->name) {
            strcpy(tour->name, buffer);
        }
        break;
    }
    
    while (1) {
        printf("Введите стоимость тура: ");
        if (scanf("%f", &tour->price) != 1) {
            printf("Ошибка: введите числовое значение.\n");
            while (getchar() != '\n');
            continue;
        }
        
        if (tour->price < 0) {
            printf("Ошибка: стоимость не может быть отрицательной.\n");
            continue;
        }
        break;
    }
    
    while (1) {
        printf("Введите дату начала тура (DD.MM.YYYY): ");
        if (scanf("%10s", tour->start.date) != 1) {
            printf("Ошибка ввода даты.\n");
            while (getchar() != '\n');
            continue;
        }
        
        int day, month, year;
        if (sscanf(tour->start.date, "%d.%d.%d", &day, &month, &year) != 3) {
            printf("Ошибка: неверный формат даты. Используйте DD.MM.YYYY\n");
            continue;
        }
        
        if (day < 1 || day > 31 || month < 1 || month > 12 || year < 2025) {
            printf("Ошибка: неверные значения даты.\n");
            continue;
        }
        
        if (tour->start.date[2] != '.' || tour->start.date[5] != '.') {
            printf("Ошибка: используйте точки как разделители.\n");
            continue;
        }
        
        break;
    }
    
    while (1) {
        printf("Введите количество дней: ");
        if (scanf("%d", &tour->start.days) != 1) {
            printf("Ошибка: введите целое число.\n");
            while (getchar() != '\n');
            continue;
        }
        
        if (tour->start.days <= 0) {
            printf("Ошибка: количество дней должно быть положительным.\n");
            continue;
        }
        break;
    }

    printf("Тур успешно добавлен!\n");

    while(getchar() != '\n');
}

void printTour(const ExcursionTour* tour) {
    if (!tour || !tour->name) return;
    
    printf("Название: %s\n", tour->name);
    printf("Стоимость: %.2f\n", tour->price);
    printf("Дата начала: %s\n", tour->start.date);
    printf("Количество дней: %d\n", tour->start.days);
    printf("----------------------------\n");
}

void freeTour(ExcursionTour* tour) {
    if (tour && tour->name) {
        free(tour->name);
        tour->name = NULL;
    }
}

ExcursionTour* addTour(ExcursionTour* tours, int* count) {
    ExcursionTour* newTours = realloc(tours, (*count + 1) * sizeof(ExcursionTour));
    if (!newTours) {
        return NULL;
    }
    
    inputTour(&newTours[*count]);
    (*count)++;
    
    return newTours;
}

void findToursByPrice(const ExcursionTour* tours, int count, float maxPrice) {
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (tours[i].price < maxPrice) {
            printTour(&tours[i]);
            found = 1;
        }
    }
    if (!found) {
        printf("Туры дешевле %.2f не найдены.\n", maxPrice);
    }
}

int removeToursByName(ExcursionTour* tours, int* count, const char* nameToRemove) {
    int removed = 0;
    for (int i = 0; i < *count; ) {
        if (strcmp(tours[i].name, nameToRemove) == 0) {
            freeTour(&tours[i]);
            // Сдвигаем оставшиеся элементы
            for (int j = i; j < *count - 1; j++) {
                tours[j] = tours[j + 1];
            }
            (*count)--;
            removed++;
        } else {
            i++;
        }
    }
    return removed;
}

void printAllTours(const ExcursionTour* tours, int count) {
    if (count == 0) {
        printf("Нет доступных туров.\n");
        return;
    }
    
    printf("\nСписок всех туров:\n\n");
    printf("----------------------------\n");
    for (int i = 0; i < count; i++) {
        printTour(&tours[i]);
    }
}
