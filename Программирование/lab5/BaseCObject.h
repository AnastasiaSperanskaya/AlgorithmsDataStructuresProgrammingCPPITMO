#ifndef LAB5_BASECOBJECT_H
#define LAB5_BASECOBJECT_H

class BaseCObject {
public:
// Имя класса (типа данных).
    virtual const char* classname() = 0;
// Размер занимаемой памяти.
    virtual unsigned int size() = 0;
};

#endif //LAB5_BASECOBJECT_H
