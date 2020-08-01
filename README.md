# Operating-System-Workshop

Теперь по-русски, потому что мне надоело писать по-английски, к тому же микрычам так будет проще. Здесь представлены разные практические и зачетные задачи от Сальникова А. Н. по дисциплине "Операционные системы" за прошлые годы. Порядок задач не имеет значения, тут все вперемешку. На лекциях я его не слушал, так что не знаю какой проходится теоретический курс, но по факту практические задачи представляют собой просто упражнение на умение работать с API Linux на языке Си. Сразу предупреждаю, что я выбрал стандарт C89, потому что я фарисей. Если есть где-то в решениях ошибка, пожалуйста, напишите мне куда-нибудь.

## Практические задачи

### Задача 0. "Распечатка битов".
Распечатать побитово число типа int, используя битовый сдиг.

### Задача 1. "Распачатка строк в обратном порядке"
На вход программе подаются строки. Программа должна их распечатать в обратном порядке. Нужно использовать динамическую память.

### Задача 2. "Диагональ матрицы"
Написать две программы. Одна пишет матрицу в файл, другая считывает из файла матрицу и считает сумму элементов на диагонали. Также нужно использовать Makefile для ускорения процесса компиляции и линковки всего этого.

### Задача 3. "Кольцо"
На вход программе подаются строки. Нужно создать закольцованный список, хранящий эти строки, затем найти наименьшую в лексикографическом смысле строку и напечатать список, начиная с элемента, содержащего эту строку.

## Зачетные задачи

### Задача 0.
Требуется написать 2 функции: упаковщик и распаковщик в 32 битное значение.
Прототипы функций следующие:
uint32_t pack(signed short x, signed short y, signed short z); и
void unpack(uint32_t packed_val, signed short *x, signed short *y, signed short *z);
предполагается, что x, y и z принимают значения в диапозоне от -512 до 511.
