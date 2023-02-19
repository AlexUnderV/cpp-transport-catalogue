# cpp-transport-catalogue
Программная реализация транспортного справочника, для добавления, обработки и хранения информации об остановках и маршрутах. Его работа состоит из двух стадий: первый отвечает за наполнение базы дынных информацией, второй же производит вывод статистики по добавленной информации.

## Использование:
0. Установка всех требуемых компонентов в среде разработки.
1. Вариант использования показан в main.cpp.
2. В main.cpp есть два варианта ввода данных: `RunFile()` для считывания информации из файла и `RunCin()` для считывания ввода с командной строки.

## Системные требования:
1. С++20 (STL)
2. GCC (MinGW-w64) 8.1.0

## Планы по доработке:
1. Добавить работу с JSON запросами.
2. Добавить графический вывод.

## Стек технологий:
1. CMake 3.23.0
