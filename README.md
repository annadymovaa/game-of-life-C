## Rules
>- Any live cell with fewer than two live neighbours dies, as if by underpopulation.
>- Any live cell with two or three live neighbours lives on to the next generation.
>- Any live cell with more than three live neighbours dies, as if by overpopulation.
>- Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
>
>These rules, which compare the behavior of the automaton to real life, can be condensed into the following:
>
>- Any live cell with two or three live neighbours survives.
>- Any dead cell with three live neighbours becomes a live cell.
>- All other live cells die in the next generation. Similarly, all other dead cells stay dead.
>
>Conway chose his rules to meet these criteria:
>
>- There should be no explosive growth.
>- There should exist small initial patterns with chaotic, unpredictable outcomes.
>- There should be potential for von Neumann universal constructors.
>- The rules should be as simple as possible, whilst adhering to the above constraints.


На языке программирования С разработать программу `src/game_of_life.c`, представляющую собой визуализацию The Game of Life. Для отображения графики использовать только символьную (ASCII) графику (с выводом в терминал). Необходимо реализовать в игре The Game of Life интерактивный режим c настройкой скорости игры и возможностью окончания. Для упрощения обработки действий игроков и отображения символьной графики можно использовать библиотеку `ncurses`.

**Графика:**
- Поле — прямоугольник 80 на 25 клеток. Подразумевается, что поле «замкнуто само на себя», к примеру, у нижнего правого квадратика соседом справа является нижний левый квадратик, а соседом снизу — верхний правый.
- Предусмотреть начальную инициализацию состояния «игры» через stdin. Подготовить как минимум 5 файлов с начальным состоянием для быстрого запуска и инициализации через перенаправление ввода.

**Управление:**
- A/Z для увеличения/уменьшения скорости соответственно.
- Space Bar для завершения.


* Запрещено выполнять системные вызовы, используя функцию `system()` и другие аналогичные ей функции, которые могут обращаться напрямую к ядру системы.

> При разработке игры в полной мере руководствуйтесь принципами структурного программирования Э. Дейкстры. 
