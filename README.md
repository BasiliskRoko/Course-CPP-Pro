Утилита для обнаружения файлов-дубликатов.

Параметры:

Директории для сканирования (может быть несколько)
 --input значение по умолчанию "./"
 Например:
    --input=test,./test2

Директории для исключения из сканирования (может быть несколько)
--ignore значение по умолчанию ""
Например:
    --ignore=test/dir2

Уровень сканирования (один на все директории, 0 - только указанная директория без вложенных)
--scan или --s значение по умолчанию 0
Например:
    --scan=1

Минимальный размер файла
--min значение по умолчанию 1
Например:
    --min=3

Маски имен файлов разрешенных для сравнения (не зависят от регистра)
--mask начение по умолчанию "*"
Например:
    --mask='H*.txt'

Размер блока, которым производится чтения файлов
--block или --b" значение по умолчанию 1
Например:
    --block=5

Один из имеющихся алгоритмов хэширования crc32, md5
--hash" значение по умолчанию "md5"
Например:
    --hash=crc32

Результатом работы утилиты должен быть список полных путей файлов с идентичным содержимым, выводимый на стандартный вывод. На одной строке один файл. Идентичные файлы должны подряд, одной группой.

Разные группы разделяются пустой строкой.

Свойство утилиты - бережное обращение с дисковым вводом выводом. Каждый файл представлен в виде списка блоков. Если размер файла не кратен блоку, он дополняется бинарными нулями.
Блок каждого файла читается с диска не более одного раза
Блок каждого файла читается только в случае необходимости

Файлы считаются идентичными при полном совпадении последовательности хешей блоков.