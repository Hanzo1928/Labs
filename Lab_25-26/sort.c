#include "sort.h"

void udtSwap(Udt *udt1, Udt *udt2)                                  // Функция, меняющая очереди местами
{
    Udt tmp;                                                        // tmp = структура САМОЙ очереди

    tmp = *udt1;                                                    // Указатель на структуру очереди 1
    *udt1 = *udt2;                                                  // Указатель на структуру очереди 2
    *udt2 = tmp;                                                    // Указатель равен структуре
}

void udtSort(Udt *udt)                                              // Функция сортировки
{
    const int cap = udtCapacity(udt);                               // Функция определения формального размера очереди
    UDT_TYPE max;                                                   // Структура элемента очереди
    Udt second;
    Udt third;
    Udt tmp;

    if (cap < 2)                                                    // Если формальный размер меньше 2, то ничего
        return;

    udtCreate(&second, cap);                               // Создание структуры того же размера, что и у основной очереди
    udtCreate(&third, cap);                                // Создание структуры того же размера, что и у основной очереди
    udtCreate(&tmp, cap);                                  // Создание структуры того же размера, что и у основной очереди

    max = udtFront(udt);                                            // Первый элемент исходной очереди

    udtPop(udt);                                                    // Извлекаем из исходной очереди первый (самый старый) элемент
    udtPush(&second, max);                                // Добавляем первый элемент во вторую очередь

    while (!udtEmpty(udt))                                          // Пока очередь не пуста
    {
        if (udtFront(udt)._key > max._key)                          // Если первый элемент текущей очереди больше 1-го элемента предыдущей
        {
            max = udtFront(udt);                                    // запоминаем первый элемент измененной очереди

            udtPop(udt);                                            // Извлекаем из очереди первый (самый старый) элемент
            udtPush(&second, max);                        // Добавляем еще один первый элемент измен. очереди во вторую очередь
        }
        else
        {
            while (udtFront(&second)._key < udtFront(udt)._key) // Пока первый элемент 2 очереди < первого элемента исходно-измененной
            {
                udtPush(&third, udtFront(&second));   // Добавляем в 3 очередь первый элемент второй очереди
                udtPop(&second);                                // Извлекаем из 2 очереди первый (самый старый) элемент
            }

            udtPush(&third, udtFront(udt));               // Добавляем в 3 очередь первый элемент исходной очереди
            udtPop(udt);                                            // Извлекаем из исходной очереди первый элемент

            while (!udtEmpty(&second))                          // Пока вторая очередь не пуста
            {
                udtPush(&third, udtFront(&second));   // Добавляем в 3 очередь первый элемент второй очереди
                udtPop(&second);                                // Извлекаем из 2 очереди первый (самый старый) элемент
            }

            udtSwap(&third, &second);                     // Меняем очереди местами (первая становится второй, а вторая первой)
        }
    }

    udtSwap(&second, udt);                                  // Меняем местами вторую и исходную очереди

    udtDestroy(&second);                    // ПОЛНОЕ удаление очереди
    udtDestroy(&third);                     // ПОЛНОЕ удаление очереди
    udtDestroy(&tmp);                       // ПОЛНОЕ удаление очереди
}
