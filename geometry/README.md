# Geometry

### Vector

Класс `Vector` для вектора на плоскости с необходимыми арифметическими операциями (унарные и бинарные 
`+`/`-`, умножение/деление на скаляр, присваивающие версии операций, сравнение на равенство).

### Shape

Набор классов-фигур, которые наследуются от абстрактного базового класса `IShape` для работы с двумерными
геометрическими примитивами:
* `Point` (точка);
* `Segment` (отрезок);
* `Line` (линия);
* `Ray` (луч);
* `Polygon` (простой многоугольник - часть плоскости, ограниченная замкнутой ломаной без самопересечений);
* `Circle` (окружность).

В базовом классе `IShape` предусмотреть чисто виртуальные методы:
* Move(const Vector&) - сдвиг на заданный вектор
* ContainsPoint(const Point&) - проверка (`true`/`false`) содержит ли фигура (внутренность фигуры) точку;
* CrossesSegment(const Segment&) проверка (`true`/`false`) пересекается ли фигура (граница фигуры) с отрезком;
* Clone() - копирование объекта
* ToString() - строковое представление фигуры

Разность двух точек возвращает вектор перемещения одной точки в
другую.