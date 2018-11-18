# Задача 1
## Цели

- Познакомиться со стратегией запрета копирования при управлении рессурсами
- Получить базовые знания о конструкторах и деструкторах
- Освоить принцип *const as much as possible*
- Научиться перегружать операторы `= * -> type`

## Условие

Необходимо написать свой простой класс умного указателя - `SmartPtr`.

**Класс должен удовлетворять слующим требованиям:**

- Класс должен единолично владеть указателем.
- Копирование и перемещение запрещено
- Должен иметься конструктор по умолчанию
- Должен иметься конструктор, принимающий указатель
- Деструктор должен автоматически очищать память
- Должны иметься операторы `* и ->` для доступа к данным в указателе
- Есть метод `Empty()`, проверяющий валидность указателя
- Есть метод `Reset(pointer)`, позволяющий заменить указатель на новый, удалив старый. `Reset()` без параметров должен мгновенно очистить и сбросить указатель.  
- Есть возможность сделать cast умного указателя к обычному указателю
- Класс необходимо *шаблонизировать\**, чтобы он мог хранить указатель любого типа. 

### \*При чем тут шаблоны
Не пугайтесь шаблонизации. Технологии нужно изучать в связке, иначе примеры будут бесполезными. В данном случае затраты на шаблонность минимальны, а польза огромна.

Можете сначала написать класс указателя на тип `TreeNode` (из файла `three.h`). Затем заменить `TreeNode` на `T`, соответствующей припиской `template <typename T>` перед `class SmartPtr`.

При написании шаблонного кода, все реализации методов должны быть описаны в `*.h` файле.

## Требования к решению

В папке с условием есть файлы `main.cpp, tree.h, tree.cpp`. Файл `tree.h` подключает отстутвующий файл `smart_ptr.h`. Ваша задача написать `smart_ptr.h` так, чтобы программа скомпилировалась и корректно завершилась с сообщением `The happy end!`. При этом должны быть выполнены условия в комментариях к коду.в `main.cpp`

Вообще, присмотритесь повнимательнее к файлам `tree.h tree.cpp`. Это очень упрощенный класс map, реализованный с помощью дерева. Он ловко использует умный указатель для слежения за ресурсами. Он может послужить вам примером для последующих работ. 

Особое внимание обратите на то, как используются **namespace**, **const**-квалификаторы, как разбит функционал между `*.h и *.cpp`, где происходят `#include`, как производится защита хэдеров...
