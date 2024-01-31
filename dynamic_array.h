#pragma once
#include <limits>
#include <initializer_list>
#include <iostream>
#include <string>
#include <cmath>
#include <exception>
#include "bad_range.h"

template <typename T = std::string>
class DynamicArray {
 public:
    DynamicArray();
    DynamicArray(size_t length);
    DynamicArray(const DynamicArray& other);
    DynamicArray(const std::initializer_list<T>& l);
    
    ~DynamicArray();
    
    void erase();
    
    T& operator[](size_t index);
    
    // оператор присваивания, который присваивает один объект DynamicArray другому возвращает ссылку на самого себя
    DynamicArray& operator=(const DynamicArray<T>& other);

    size_t getLength() const;
    
    // reallocate resizes the array.  Any existing elements will be destroyed.  This function operates quickly.
    void reallocate(size_t newLenght);
    void resize(size_t newLength);
    
    T& insertBefore(const T& value, size_t index);
    T& PushFront(const T& value);
    T& PushBack(const T& value);
    
    void Remove(size_t index);
    
    bool Find(const T& value, size_t index_result);

    void Show() const;
    
 private:
    size_t _length;
    T* _data;
};



template<typename T>
DynamicArray<T>::DynamicArray() {
    //std::cout << "DynamicArray Default Constructor - "<< this << std::endl;
}

template<typename T>
DynamicArray<T>::DynamicArray(size_t length) 
    : _length(length){
        
        if(length > std::numeric_limits<size_t>::max()) {
            throw BadLength();
        }
        
        try{
            _data = new T[length]{};
        }
        catch(const std::exception& ex) {
            std::cerr << "Не смогли выделить памать " << ex.what() << std::endl;
            throw;
        }
        
        //std::cout << "DynamicArray Constructor on size - " << this << std::endl;
}

template<typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& other){
    // Set the size of the new array appropriately
    // Сначала уничтожаем полностью существующий контейнер, реаллоцируем новый нулевой, с нужной длиной и далее совершаем глубокое копирование.
    reallocate(other.getLength());
    
    // Then copy the elements, здесь _length уже новая
    for (size_t i = 0; i < _length; ++ i){
        _data[i] = other._data[i];
    } 
    //std::cout << "Copy DynamicArray Constructor - " << this << std::endl;
}

template<typename T>
DynamicArray<T>::DynamicArray(const std::initializer_list<T>& l){
    _length = l.size();
    
    try{
        _data = new T[_length]{};
    }
    catch(const std::exception& ex) {
            std::cerr << "Не смогли выделить памать " << ex.what() << std::endl;
            throw;
    }
    
    size_t i = 0;
    for(const T* ptr = l.begin(); ptr != l.end() && i < _length; ++ptr, ++i){
        _data[i] = *ptr;
    }
    
   std::cout << "DynamicArray initializer_list Constructor - " << this << std::endl;
 }

template<typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T>& other){
    //Проверка не ссылается ли другой объект на этот же, т.е. на самоприсваивание
    if(&other == this) return *this;
    
    //Уничтожаем старый контейнер и делаем глубокое копирование
    reallocate(other.getLength());
    
    // здесь _length уже имеет новую длину другого объекта назначенную в функции reallocate
    for(size_t i = 0; i < _length; ++i){
        _data[i] = other._data[i];
    }
    
    return *this;
}


template<typename T>
DynamicArray<T>::~DynamicArray(){
    delete[] _data;
     // we don't need to set m_data to null or m_length to 0 here, since the object will be destroyed immediately after this function anyway
    std::cout << "DynamicArray DeStructor - " << this << std::endl<<std::endl; 
}

template<typename T>
void DynamicArray<T>::erase(){
    delete[] _data;
    
    // We need to make sure we set m_data to nullptr here, otherwise it will
    // be left pointing at deallocated memory!
    _data = nullptr;
    _length = 0;
}

template<typename T>
T& DynamicArray<T>::operator[](size_t index){
    if(index < 0 || index > _length) throw BadRange();
    return _data[index];
}

template<typename T>
size_t DynamicArray<T>::getLength() const {
    return _length;
}

// reallocate resizes the array.  Any existing elements will be destroyed.  This function operates quickly.
template<typename T>
void DynamicArray<T>::reallocate(size_t newLength){
    // First we delete any existing elements
    erase(); 
    
    // If our array is going to be empty now, return here
    if(newLength <= 0 || newLength > std::numeric_limits<size_t>::max()) {
        throw BadLength();
    }
        
    try{
        _data = new T[newLength]{};
    }catch(const std::exception& ex) {
        std::cerr << "Не смогли выделить памать " << ex.what() << std::endl;
        throw;
    }
    
    _length = newLength;
}     

// resize resizes the array.  Any existing elements will be kept.  This function operates slowly.
template<typename T>
void DynamicArray<T>::resize(size_t newLength){
    // if the array is already the right length, we're done
    if (newLength == _length)
        return;
    
    // If we are resizing to an empty array, do that and return 
    if(newLength < 0 || newLength > std::numeric_limits<size_t>::max()) {
        throw BadLength();
    }
    if(newLength == 0){
        erase();
        return;
    }
    
    // Now we can assume newLength is at least 1 element.  This algorithm
    // works as follows: First we are going to allocate a new array.  Then we
    // are going to copy elements from the existing array to the new array.
    // Once that is done, we can destroy the old array, and make m_data
    // point to the new array.
    
    // First we have to allocate a new array
    try{
    T* newdata = new T[newLength]{};  // int* data{ new int[newLength] }; - universal initialisation  
    
    // Then we have to figure out how many elements to copy from the existing
    // array to the new array.  We want to copy as many elements as there are
    // in the smaller of the two arrays.
    
    if(_length > 0){
        
        size_t countNewElems = (newLength > _length) ? _length : newLength;
        
        // Now copy the elements one by one
        for(size_t i = 0; i < countNewElems; ++i){
            newdata[i] = _data[i];
        }
    }
    
    // Now we can delete the old array because we don't need it any more
    delete[] _data;
    
    // And use the new array instead!  Note that this simply makes m_data point
    // to the same address as the new array we dynamically allocated.  Because
    // data was dynamically allocated, it won't be destroyed when it goes out of scope.
    
    _data = newdata;
    _length = newLength;
    
    }
    catch(const std::exception& ex) {
        std::cerr << "Не смогли выделить памать " << ex.what() << std::endl;
        throw;
    }
}

template<typename T>
T& DynamicArray<T>::insertBefore(const T& value, size_t index){
    //Проверка на допустимость индекса
    if(index < 0 || index > _length) throw BadRange();
    
    // First create a new array one element larger than the old array
    
    
    try{
        T* newdata = new T[_length + 1]{};
        
        // Copy all of the elements up to the index
        for (size_t i = 0; i < index; ++ i){
            newdata[i] = _data[i];
        }
        
        // Insert our new element into the new array
        newdata[index] = value;
        
        // Copy all of the values after the inserted element
        for(size_t i = index; i < _length; ++i){
            
            newdata[i+1] = _data[i];
        }
        
        //Finally, delete the old array, and use the new array instead
        
        delete[] _data;
        _data = newdata;
        ++_length;
        
        return _data[index];
        
    }
    catch(const std::exception& ex) {
        std::cerr << "Не смогли выделить памать " << ex.what() << std::endl;
        throw;
    }   
        
}

template<typename T>
T& DynamicArray<T>::PushFront(const T& value){
    return insertBefore(value, 0);
}

template<typename T>
T& DynamicArray<T>::PushBack(const T& value){
    return insertBefore(value, _length);
}

//Удаляет элемент из массива
template<typename T>
void DynamicArray<T>::Remove(size_t index){
    // Проверяем входил ли индекс в имеющиеся
    if(index > _length) throw BadRange();
    
    // If this is the last remaining element in the array, set the array to empty and bail out
    if(_length == 1){
        erase();
        return;
    }
    
    try{
        // First create a new array one element smaller than the old array
        T* newdata = new T[_length - 1]{};
        
        // Copy all of the elements up to the index
        for (size_t i = 0; i < index; ++i){
            newdata[i] = _data[i];
        }
        
        // Copy all of the values after the removed element
        for(size_t i = index+1; i < _length; ++ i){
            newdata[i - 1] = _data[i];
        }
        
        // Finally, delete the old array, and use the new array instead
        delete[] _data;
        _data = newdata;
        --_length;
        
    }    
    catch(const std::exception& ex) {
        std::cerr << "Не смогли выделить памать " << ex.what() << std::endl;
        throw;
    }      
}
template<typename T>
void DynamicArray<T>::Show() const {
    for(size_t i = 0; i < _length; ++i){
        std::cout << _data[i];
        
        if(i != _length-1) std::cout << ", ";
    }
    
    std::cout << std::endl;
}

template<>
void DynamicArray<double>::Show() const {
    for(size_t i = 0; i < _length; ++i){
        std::cout <<std::scientific<< _data[i];
        
        if(i != _length-1) std::cout << ", ";
    }
    
    std::cout << std::endl;
}

template<typename T>
bool DynamicArray<T>::Find(const T& value, size_t index_result){
    for(size_t i = 0; i < _length; ++i){
        if(_data[i] == value){
            index_result = i;
            return true;
        }    
        
    }
    return false;
}
