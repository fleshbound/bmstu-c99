# Функциональные тесты для Л/Р №04 (04-01)

## Входные данные

Строка с некоторым количеством пробельных символов в начале и конце.

## Выходные данные

Слово "YES", если в строке находится валидное вещественное число, слово "NO" - в ином случае.

## Позитивные тесты

### "YES"

- 01 - одна цифра;
- 02 - плюс, одна цифра;
- 03 - минус, одна цифра;
- 04 - несколько цифр;
- 05 - плюс, несколько цифр;
- 06 - минус, несколько цифр;
- 07 - цифра, точка;
- 08 - плюс, цифра, точка;
- 09 - минус, цифра, точка;
- 10 - точка, цифра;
- 11 - плюс, точка, цифра;
- 12 - минус, точка, цифра;
- 13 - цифра, точка, цифра (= "обычн. вещ.ч.");
- 14 - плюс, цифра, точка, цифра;
- 15 - минус, цифра, точка, цифра; 
- 16 - обычн. вещ. ч., e, беззнаковая степень;
- 17 - плюс, обычн.вещ.ч., e, беззнаковая степень;
- 18 - минус, обычн.вещ.ч., e, беззнаковая степень;
- 19 - обычн. вещ. ч., e, '+' степень;
- 20 - плюс, обычн.вещ.ч., e, '+' степень;
- 21 - минус, обычн.вещ.ч., e, '+' степень;
- 22 - обычн. вещ. ч., e, '-' степень;
- 23 - плюс, обычн.вещ.ч., e, '-' степень;
- 24 - минус, обычн.вещ.ч., e, '-' степень;
- 25 - одна цифра, e, беззнаковая степень;
- 26 - плюс, одна цифра, e, беззнаковая степень;      
- 27 - минус, одна цифра, e, беззнаковая степень;
- 28 - несколько цифр, e, беззнаковая степень;
- 29 - плюс, несколько цифр, e, беззнаковая степень;
- 30 - минус, несколько цифр, e, беззнаковая степень;
- 31 - цифра, точка, e, беззнаковая степень;
- 32 - плюс, цифра, точка, e, беззнаковая степень;
- 33 - минус, цифра, точка, e, беззнаковая степень;
- 34 - точка, цифра, e, беззнаковая степень;
- 35 - плюс, точка, цифра, e, беззнаковая степень;
- 36 - минус, точка, цифра, e, беззнаковая степень;
- 37 - пробелы !! плюс, обычн.вещ.ч., E, '-' степень;

### "NO"

- 38 - нецелая степень у e;
- 39 - отсуствует степень у e;
- 40 - некорректные символы для представления числа;
- 41 - отсутсвует основание числа;
- 42 - только пробелы;
- 43 - знак основания без численного значения;
- 44 - знак степени без численного значения;
- 45 - знак плюс;

## Негативные тесты

- 01 - длина строки больше 256 символов;
- 02 - введена пустая строка;
- 03 - кодировка не ascii;