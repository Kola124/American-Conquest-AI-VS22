#ifndef _TMPPTRARRAY_H
#define _TMPPTRARRAY_H

#include <stdio.h>

template <class T>
class tmpArray
{
  protected:
  int curDelta;	// приращение элементов <class T> в случае
				      // превышени€ размера массива
  public:
  typedef T* pT;
  T** pArray;
  int sizeUsed;	// использовано элементов
  int sizeFull;   // всего элементов

  tmpArray();
  ~tmpArray();

  T* operator [] ( int pos) const;
  T& operator [] ( int pos);

  bool  Reset(int size, int delta = 0);   // - очистка массива с инициализацией
  bool  Expand(void);
  bool  Add(void);
  bool  Add(T*);
  T* GetAt(int pos);
  bool  InsertAt(int pos, T *pointer);
  bool  RemoveAt(int pos);
  void  RemoveAll();
  int	Find(T *pointer, int first = 0);

  //--- saving|loading
  bool	save(FILE*); //сохран€ет шапку объекта класса и элементы массива до sizeUsed
  bool	load(FILE*); //загружает шапку объекта класса (удал€€ старый массив) и элементы массива до sizeUsed
  bool	saveDesc(FILE*); //сохранение только описани€ массива, без содержимого
  bool	loadDesc(FILE*); //создание массива по сохраненному описанию
};
#endif
