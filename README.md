# s21_string+

## Содержание

1. [О проекте](#о-проекте)
2. [Навыки, полученные в ходе разработки](#навыки-полученные-закрепленные-в-ходе-разработки)
3. [Инструкция по сборке и запуску тестов](#инструкция-по-сборке-и-запуску-тестов)
4. [Команда разработчиков](#команда-разработчиков)

## О проекте

В данном проекте была разработана собственная реализация библиотеки `string.h` на языке программирования Си с некоторыми дополнениями (с собственной реализацией функций `sprintf` и `sscanf`, а так же некоторых функций из `C#`). Полное покрытие unit-тестами, разработка в соответсвии с TDD-подходом.

## Навыки, полученные (закрепленные) в ходе разработки
- Работа со строками на языке Си
- Работа с переменным числом аргументов в функциях
- Создание и связывание статических библиотек, сборка проекта с помощью Makefile
- Тестирование с помощью библиотеки Check

<br>

## Инструкция по сборке и запуску тестов
## Список всех команд

| Действие                       | Команда                                         |
| ------------------------------ | ----------------------------------------------- |
| Сборка и запуск всех тестов    | `make`                                          |
| Сборка библиотеки              | `make s21_string.a (linux:libs21_string.a)`     |
| Запуск базовых тестов          | `make test;./test`                              |
| Запуск случайных тестов        | `make random_test;./random_test`                |
| Запуск дополнительных тестов   | `make extended_test`                            |
| Формирование отчета о покрытии | `make gcov_report`                              |
| Стилевой тест                  | `make style`                                    |
| Запуск отчистки                | `make clean`                                    |

<br>

---

### Сборка и запуск всех тестов

```bash
make
```

---

### Сборка библиотеки

MacOS:

```bash
make s21_string.a
```

*__Linux:__*

```bash
make libs21_string.a
```

---

### Запуск базовых тестов

```bash
make test;./test
```

---

### Запуск случайных тестов

*__Все тесты:__*

```bash
make random_test;./random_test
```

*__Тесты базовых функций библиотеки:__*

```bash
make random_test;./random_test string
```

*__Тесты функции s21_sprintf:__*

```bash
make random_test;./random_test sprintf
```

*__Тесты функции s21_sscanf:__*

```bash
make random_test;./random_test sscanf
```

---

### Запуск дополнительных тестов

```bash
make extended_test
```

---

### Формирование отчета о покрытии

```bash
make gcov_report
```

---

### Стилевые тесты

```bash
make style
```

---

### Запуск отчистки

```bash
make clean
```

<br>

## Команда разработчиков

<table>
    <tbody>
        <tr>
            <td align="center" valign="middle">
                <a href="https://github.com/cheremshin" title="cheremshin">
                    <img valign="middle" width="64px" height="64px" src="https://avatars.githubusercontent.com/u/91583699?v=4">
                </a>
            </td>
            <td align="center" valign="middle">
                <a href="https://github.com/sanddony" title="sanddony">
                    <img valign="middle" width="64px" height="64px" src="https://avatars.githubusercontent.com/u/42729400?v=4">
                </a>
            </td>
            <td align="center" valign="middle">
                <a href="https://github.com/kaylebee" title="kaylebee">
                    <img valign="middle" width="64px" height="64px" src="https://avatars.githubusercontent.com/u/111429825?v=4">
                </a>
            </td>
            <td align="center" valign="middle">
                <a href="https://github.com/Txnsky" title="Txnsky">
                    <img valign="middle" width="64px" height="64px" src="https://avatars.githubusercontent.com/u/126697890?v=4">
                </a>
            </td>
        </tr>
        <tr>
            <td align="center" valign="middle">
                <a href="https://github.com/cheremshin" title="cheremshin">cheremshin</a>
            </td>
            <td align="center" valign="middle">
                <a href="https://github.com/sanddony" title="sanddony">sanddony</a>
            </td>
            <td align="center" valign="middle">
                <a href="https://github.com/kaylebee" title="kaylebee">kaylebee</a>
            </td>
            <td align="center" valign="middle">
                <a href="https://github.com/Txnsky" title="Txnsky">Txnsky</a>
            </td>
        </tr>
    </tbody>
</table>