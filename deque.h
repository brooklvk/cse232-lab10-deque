/***********************************************************************
 * Header:
 *    DEQUE
 * Summary:
 *    Our custom implementation of a deque
 *      __       ____       ____         __
 *     /  |    .'    '.   .'    '.   _  / /
 *     `| |   |  .--.  | |  .--.  | (_)/ /
 *      | |   | |    | | | |    | |   / / _
 *     _| |_  |  `--'  | |  `--'  |  / / (_)
 *    |_____|  '.____.'   '.____.'  /_/
 *
 *    This will contain the class definition of:
 *        deque                 : A class that represents a deque
 *        deque::iterator       : An iterator through a deque
 * Author
 *    Brooklyn and Josh 
 ************************************************************************/

#pragma once

// Debug stuff
#include <cassert>

class TestDeque;    // forward declaration for TestDeque unit test class

namespace custom
{

/******************************************************
 * DEQUE
 *         iaFront
 * ia =   0   1   2   3   4
 *      +---+---+---+---+---+
 *      |   | A | B | C |   |
 *      +---+---+---+---+---+
 * id =       0   1   2
 * iaFront = 1
 * numElements = 3
 * numCapacity = 5
 *****************************************************/
template <class T>
class deque
{
   friend class ::TestDeque; // give unit tests access to the privates
public:

   // 
   // Construct
   //
   deque() 
   { 
       iaFront = 0;
       numCapacity = 0;
       numElements = 0;
       data = (new T);
   }
   deque(int newCapacity);
   deque(const deque <T> & rhs);
   ~deque()
   { 
   }

   //
   // Assign
   //
   deque<T> & operator = (const deque <T> & rhs);

   //
   // Iterator
   //
   class iterator;
   iterator begin()
   {
      return iterator(this, 0);
   }
   iterator end()
   {
      return iterator(this, numElements);
   }

   //
   // Access
   //
   T& front();
   T& back();
   const T & front() const;
   const T & back()  const;
   const T & operator[](size_t index) const;
   T& operator[](size_t index);

   // 
   // Insert
   //
   void push_front(const T& t);
   void push_back(const T& t);

   //
   // Remove
   //
   void clear()
   { 
       numElements = 0;
       iaFront = 0;
   }
   void pop_front();
   void pop_back();

   // 
   // Status
   //
   size_t size() const 
   { 
      return numCapacity; 
   }
   bool empty() const 
   { 
      return numElements == 0; 
   }

   
private:
   
   // fetch array index from the deque index
   int iaFromID(int id) const
   {
      return (iaFront + id) % numCapacity;
   }
   void resize(int newCapacity = 0);

   // member variables
   T * data;           // dynamically allocated data for the deque
   size_t numCapacity; // the size of the data array
   size_t numElements; // number of elements in the deque
   int iaFront;        // the index of the first item in the array
};



/**********************************************************
 * DEQUE ITERATOR
 * Forward and reverse iterator through a deque, just call
 *********************************************************/
template <typename T>
class deque <T> ::iterator
{
   friend class ::TestDeque; // give unit tests access to the privates
public:
   //
   // Construct
   //
    iterator()
    {
        pDeque = nullptr;
        id = 0;
    }
    iterator(custom::deque<T>* pDeque, int id)
    {
        this->pDeque = pDeque;
        this->id = id;
    }
    iterator(const iterator& rhs)
    {
        pDeque = rhs.pDeque;
        id = rhs.id;
    }

   //
   // Assign
   //
   iterator& operator = (const iterator& rhs)
   {
       pDeque = rhs.pDeque;
       id = rhs.id;
       return *this;
   }

   //
   // Compare
   //
   bool operator == (const iterator& rhs) const { return pDeque == rhs.pDeque && id == rhs.id; }
   bool operator != (const iterator& rhs) const { return !(*this == rhs); }

   // 
   // Access
   //
   const T & operator * () const
   {
       int ia = pDeque->iaFromID(id);
       return pDeque->data[ia];
   }
   T& operator * () 
   {
       int ia = pDeque->iaFromID(id);
       return pDeque->data[ia];
   }

   // 
   // Arithmetic
   //
   int operator - (iterator it) const
   {
       return id - it.id;
   }
   iterator& operator += (int offset)
   {
       id += offset;
       return *this;
   }
   iterator& operator ++ ()
   {
       ++id;
       return *this;
   }
   iterator operator ++ (int postfix)
   {
       iterator temp = *this;
       ++id;
       return temp;
   }
   iterator& operator -- ()
   {
       --id;
       return *this;
   }
   iterator  operator -- (int postfix)
   {
       iterator temp = *this;
       --id;
       return temp;
   }

private:

   // Member variables
   int id;             // deque index
   deque<T> *pDeque;
};


/****************************************************
 * DEQUE : CONSTRUCTOR - non-default
 ***************************************************/
template <class T>
deque <T> :: deque(int newCapacity)
{
    numCapacity = newCapacity;
    numElements = 0;
    iaFront = 0;
    if (numCapacity > 0)
    {
        data = new T[numCapacity];
    }
    else
    {
        data = nullptr;
    }
}

/****************************************************
 * DEQUE : CONSTRUCTOR - copy
 ***************************************************/
template <class T>
deque <T> :: deque(const deque <T> & rhs)
{
    numElements = rhs.numElements;
    numCapacity = rhs.numCapacity;

    if (numCapacity > 0)
    {
        data = new T[numCapacity];
        // Copy the elements
        for (size_t i = 0; i < numElements; ++i)
        {
            data[i] = rhs.data[(rhs.iaFront + i) % rhs.numCapacity];
        }
        iaFront = 0;
    }
    else
    {
        data = nullptr;
        iaFront = 0;
    }
}


/****************************************************
 * DEQUE : ASSIGNMENT OPERATOR
 ***************************************************/
template <class T>
deque <T> & deque <T> :: operator = (const deque <T> & rhs)
{
    if (this != &rhs)
    {
        delete[] data;

        numElements = rhs.numElements;
        numCapacity = rhs.numCapacity;

        if (numCapacity > 0)
        {
            data = new T[numCapacity];
            // Copy the elements
            for (size_t i = 0; i < numElements; ++i)
            {
                data[i] = rhs.data[(rhs.iaFront + i) % rhs.numCapacity];
            }
            iaFront = 0;
        }
        else
        {
            data = nullptr;
            iaFront = 0;
        }
    }
    return *this;
}


/**************************************************
 * DEQUE :: FRONT
 * Fetch the item that is at the beginning of the deque
 *************************************************/
template <class T>
const T & deque <T> :: front() const 
{
    return data[iaFront];
}
template <class T>
T& deque <T> ::front()
{
    return data[iaFront];
}

/**************************************************
 * DEQUE :: BACK
 * Fetch the item that is at the end of the deque
 *************************************************/
template <class T>
const T & deque <T> :: back() const 
{
    int ia = iaFromID(numElements - 1);
    return data[ia];
}
template <class T>
T& deque <T> ::back()
{
    int ia = iaFromID(numElements - 1);
    return data[ia];
}

/**************************************************
 * DEQUE :: SUBSCRIPT
 * Fetch the item in the deque
 *************************************************/
template <class T>
const T& deque <T> ::operator[](size_t index) const
{
    int ia = iaFromID(index);
    return data[ia];
}
template <class T>
T& deque <T> ::operator[](size_t index)
{
    int ia = iaFromID(index);
    return data[ia];
}

/*****************************************************
 * DEQUE : POP_BACK
 *****************************************************/
template <class T>
void deque <T> :: pop_back()
{
    --numElements;
}

/*****************************************************
 * DEQUE : POP_FRONT
 *****************************************************/
template <class T>
void deque <T> :: pop_front()
{
    iaFront = (iaFront + 1) % numCapacity;
    --numElements;
}

/******************************************************
 * DEQUE : PUSH_BACK
 ******************************************************/
template <class T>
void deque <T> :: push_back(const T & t) 
{
    if (numElements == numCapacity)
        resize(numCapacity == 0 ? 1 : numCapacity * 2);

    int ia = iaFromID(numElements);
    data[ia] = t;
    ++numElements;
}

/******************************************************
 * DEQUE : PUSH_FRONT
 ******************************************************/
template <class T>
void deque <T> :: push_front(const T & t) 
{
    if (numElements == numCapacity)
        resize(numCapacity == 0 ? 1 : numCapacity * 2);

    iaFront = (iaFront - 1 + numCapacity) % numCapacity;
    data[iaFront] = t;
    ++numElements;
}

/****************************************************
 * DEQUE :: RESIZE
 * Resize the deque so the numCapacity matches the newCapacity
 ***************************************************/
template <class T>
void deque <T> :: resize(int newCapacity) 
{
    T* tempData = new T[newCapacity];

    for (size_t i = 0; i < numElements; ++i)
    {
        tempData[i] = data[iaFromID(i)];
    }

    delete[] data;
    data = tempData;
    numCapacity = newCapacity;
    iaFront = 0;
}

} // namespace custom
