# HW4
# Чесноков Сергей 
## Компиляция
g++ main.cpp -o main.exe -fsanitize=thread -lpthread  

# На 4
## Ввод
n - число посетителей всего за день. 
Лучше в диапозоне 40-70, чтобы не ждать очень долго (для просмотра каждой картины выставленна небольшая задержка), но можно и другие положительные числа
## Описание используемой модели параллельных вычислений
В программе используется модель клиенты и серверы, так как главный поток постоянно запрашивает сервер (в данной задаче галерею), а сервер ожидает поток (посетителя) и затем релизует проход по картинам 

# На 5
## Коментарии
Добавлены необходимые коментарии в код
## Сценарий выполнения программы
Посетители заходят в галерею пока их в ней меньше 50, каждый посетитель идет от первой картины до пятой, на каждой картине может быть максимум 10 человек, как только 10й посетитель уходит от картины, на его место приходит новый, в случае если посетитель покидает галерею, то на его место также приходит новый, и так пока все посетители не пройдут все картины

# На 6
# Реализован ввод данных из командной строки
Формат ввода:  
./main.cpp n
# Обобщенный алгоритм
Имеется основной поток, который создает новые потоки (новых посетителей), каждый созданный поток выполняет 5 методов по просмотру картины, для синхронизации используются семофоры с количеством потоков равным 10 (чтобы на каждую картину смотрели максаимум 10 человек), так же основной поток следит за тем, чтобы посетителей(потоков) одновременно было не более 50.

# На 7
## Добавлена работа по вводу/выводу в файлы/из файлов 
Файл должен содержать корректные данные   
Формат ввода:  
./main input.txt output.txt
Так же при запуске программы с консоли/командной строки содержимое, помимо консоли дублируется в файл test/output.txt

# Приведены входные и выходные файлы с различными результатами выполнения программы
См. tests/input.txt, tests/output.txt 

# На 8
# Добавлен генератор случайных чисел для кол-ва посетитлей 
Генерация происходит в диапозоне 40-70, так как он является оптимальным для скорости и при этом демонстрации задачи  
Вывод данных с случайной генерации происходит в test/random.txt
# Ввод данных из командной строки расширен с учетом введенных изменени
Формат ввода:  
./main.cpp r
