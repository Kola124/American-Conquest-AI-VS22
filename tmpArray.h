#ifndef _TMPPTRARRAY_H
#define _TMPPTRARRAY_H

#include <stdio.h>

template <class T>
class tmpArray
{
  protected:
  int curDelta;	// ���������� ��������� <class T> � ������
				      // ���������� ������� �������
  public:
  typedef T* pT;
  T** pArray;
  int sizeUsed;	// ������������ ���������
  int sizeFull;   // ����� ���������

  tmpArray();
  ~tmpArray();

  T* operator [] ( int pos) const;
  T& operator [] ( int pos);

  bool  Reset(int size, int delta = 0);   // - ������� ������� � ��������������
  bool  Expand(void);
  bool  Add(void);
  bool  Add(T*);
  T* GetAt(int pos);
  bool  InsertAt(int pos, T *pointer);
  bool  RemoveAt(int pos);
  void  RemoveAll();
  int	Find(T *pointer, int first = 0);

  //--- saving|loading
  bool	save(FILE*); //��������� ����� ������� ������ � �������� ������� �� sizeUsed
  bool	load(FILE*); //��������� ����� ������� ������ (������ ������ ������) � �������� ������� �� sizeUsed
  bool	saveDesc(FILE*); //���������� ������ �������� �������, ��� �����������
  bool	loadDesc(FILE*); //�������� ������� �� ������������ ��������
};
#endif
