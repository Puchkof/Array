#ifndef ARRAY_H
#define ARRAY_H

#include "memory.h"
#include <iostream>
using namespace std;



template <class T>
void Swap_T(T *pThis, const T &R) // template swap function for assignment operator
{
    char sBuff[sizeof(T)];//buffer for current condition of object to destroy object in future
    T Temp(R); //temporary object, copied from R. It`s on stack to call destructor of present object after function ending
    memcpy(sBuff, pThis, sizeof(T));
    memcpy(pThis, &Temp, sizeof(T));
    memcpy(&Temp, sBuff, sizeof(T));
}

template <class T>
class Array
{
        int m_nSize;//size of allocated memory
        int m_iCurInd;//number of values
        T * m_pAr;//pointer to the memory

        void add_memory()//allocates new memory if array needs it. It`s in private to save programm from overstacking
        {
            if (m_nSize == 0)
                m_nSize = 1;
            T* pBuf = new T[m_nSize*2];
            memcpy(pBuf, m_pAr, sizeof(T)*m_iCurInd);
            delete []m_pAr;
            m_nSize *= 2;
            m_pAr = pBuf;
        }
    public:
         Array():m_nSize(0), m_iCurInd(0), m_pAr(0)//creates empty array with size 0
         {
             cout << "Array() " << this << ' ' << m_nSize << endl;//some diagnostics
         }

         Array(int nSize):m_nSize(nSize),m_iCurInd(0), m_pAr(0)//creates array with 0`s with size equal to nSize
         {
             if (nSize <= 0)
                 m_nSize = 0;
             else
             {
                 m_pAr = new T[m_nSize];
                 for (int i = 0; i < m_nSize; ++i)
                     m_pAr[i] = 0;
                 m_iCurInd = m_nSize;
             }

             cout << "Array(int) " << this << ' ' << m_nSize << endl;
         }

         Array(T *pAr, int nSize):m_nSize(nSize), m_iCurInd(0), m_pAr(0)//creates array, getting nSize values from pAr
         {
             if (nSize <= 0)
                 m_nSize = 0;
             else
             {
                 m_pAr = new T[m_nSize];
                 if (pAr != NULL)
                 {
                     memcpy(m_pAr, pAr, sizeof(T) * m_nSize);
                     m_iCurInd = m_nSize;
                 }
             }

             cout << "Array(*, int) " << this << ' ' << m_nSize << endl;
         }

         Array(const Array& R):m_nSize(R.m_nSize), m_iCurInd(R.m_iCurInd), m_pAr(0)//copy constructor
         {
             if (R.m_pAr != NULL && R.m_nSize > 0)
             {
                 m_pAr = new T[m_nSize];
                 memcpy(m_pAr, R.m_pAr, sizeof(T) * m_iCurInd);
             }

             cout << "Array copy " << this << " from " << &R << ' ' << m_nSize << endl;
         }

         Array(Array &&R):m_nSize(R.m_nSize), m_iCurInd(R.m_iCurInd), m_pAr(R.m_pAr) //moving constructor
         {
             R.m_pAr = 0;
             cout << "Array move " << &R << " to " << this << endl;
         }

        ~Array()//destructor
         {
             if (m_pAr != 0)
                 delete []m_pAr;

             cout << "~Array() " << this << ' ' << m_nSize << endl;
         }

         Array operator +(const Array& R)//operator + returns array with two joined parts
         {
             Array Temp(*this);
             for (int i = 0; i < R.m_iCurInd; ++i)
             {
                 Temp.push_back(R.m_pAr[i]);
             }
             return Temp;
         }

         Array operator +(T nValue)//operator + return array, where all the values are summed with n
         {
             Array Temp(*this);
             for (int i = 0; i < m_iCurInd; ++i)
                 Temp.m_pAr[i] += nValue;
             return Temp;
         }

         Array& operator =(const Array& R)//assignment operator
         {
             if (this != &R)
             {
                 Swap_T(this, R);
             }
             return *this;
         }



         void Show()//shows array in console
         {
             if (m_pAr != 0)
             {
                 cout << "Number of values: " << m_iCurInd << endl;
                 cout << "Size of your array: " << m_nSize << endl;
                 for (int i = 0; i < m_iCurInd; ++i)
                 {
                     cout << m_pAr[i] << ' ';
                 }
                 cout << endl;
             }
         }

         void push_back(T nValue)//add the nValue to the end of the array
         {
             if (m_iCurInd >= m_nSize)
             {
                 add_memory();
             }
             m_pAr[m_iCurInd] = nValue;
             ++m_iCurInd;
         }

};

#endif // ARRAY_H
