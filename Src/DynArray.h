#ifndef SYM_DYNAMIC_ARRAY
#define SYM_DYNAMIC_ARRAY

template <class T>
class DynArray
{
    int length;
    int capacity;
    T*  array;

public :
    DynArray(size_t _length)
    {
        length   = 0;
        capacity = _length;
        array    = (T*)calloc(length, sizeof(T));
    };

    int GetLength() { return length; };

    T& operator[](int index)
    { return array[index]; };

    void PushBack(T elem)
    {
        if (capacity <= length)
        {
            capacity = capacity * 2 + 1;
            array = (T*)realloc(array, capacity * sizeof(T));
        }

        array[length] = elem;
        length++;
    };

    void PopBack()
    {
        if (length > 0)
            length--;
    };
};

#endif  //SYM_DYNAMIC_ARRAY