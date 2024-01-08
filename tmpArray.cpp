#include "tmparray.h"
//-----------------------------------------------------------------------
template <class T>
tmpArray<T>::tmpArray()
{
   pArray = NULL;
   Reset(128, 32);
}
//-----------------------------------------------------------------------
template <class T>
tmpArray<T>::~tmpArray()
{
   RemoveAll();
}
//-----------------------------------------------------------------------
template <class T>
bool tmpArray<T>::Reset(int size, int delta)
{
	RemoveAll();

	if(size != 0)
	{
		pArray = new pT[size];
		if(!pArray) return false;
		memset(pArray, 0, sizeof(T*)*size);
	}
	curDelta = delta;
	sizeUsed = 0;
	sizeFull = size;
	return true;
}
//-----------------------------------------------------------------------
template <class T>
bool tmpArray<T>::Expand(void)
{
	if(sizeFull == sizeUsed)
	{
		int newSize = sizeFull + curDelta + 1;
		T** p = new pT[newSize];
		if(!p) return false;
		memset(p, 0, sizeof(T*)*newSize);
		memcpy(p, pArray, sizeof(T*)*sizeUsed);
		delete pArray;
		pArray = p;
		sizeFull = newSize;
	}
   return true;
}
//-----------------------------------------------------------------------
template <class T>
bool tmpArray<T>::Add(void)
{
   if(!Expand()) return false;

   pArray[sizeUsed++] = new T;
	return true;
}
//-----------------------------------------------------------------------
template <class T>
bool tmpArray<T>::Add(T* pointer)
{
   if(!Add()) return false;
   memcpy(&pArray[sizeUsed-1], pointer, sizeof(T));
	return true;
}
//-----------------------------------------------------------------------
template <class T>
T* tmpArray<T>::GetAt(int pos)
{
   if(pos < 0 || sizeUsed <= pos) return 0;
   return pArray[pos];
}
//-----------------------------------------------------------------------
template <class T>
bool tmpArray<T>::InsertAt(int pos, T *pointer)
{
   int i;
   if(pos < sizeUsed)
   {
      if(!Expand()) return false;

      for(i = sizeUsed; i > pos; i--)
		  memcpy((pArray+i), (pArray+i-1), sizeof(T*));

      memcpy(&pArray[pos], pointer, sizeof(T));
      sizeUsed++;
   }
   else
   if(pos == sizeUsed)
   {
      return Add(pointer);
   }
   else return false;

   return true;
}
//-----------------------------------------------------------------------
template <class T>
bool tmpArray<T>::RemoveAt(int pos)
{
   if(pos < 0 || sizeUsed <= pos) return false;

   delete pArray[pos];
   pArray[pos] = NULL;

   for(int i = pos; i < (sizeUsed-1); i++)
   memcpy((pArray+i), (pArray+i+1), sizeof(T*));

   sizeUsed--;
   return true;
}
//-----------------------------------------------------------------------
template <class T>
void tmpArray<T>::RemoveAll()
{
   if(pArray) delete pArray;
   pArray = NULL;
   sizeFull = 0;
   sizeUsed = 0;
}
//-----------------------------------------------------------------------
template <class T>
T& tmpArray<T>::operator[](int pos)
{
   assert(pos < sizeUsed);
   return *pArray[pos];
}
//-----------------------------------------------------------------------
template <class T>
T* tmpArray<T>::operator[](int pos) const
{
   assert(pos < sizeUsed);
   return pArray[pos];
}
//-----------------------------------------------------------------------
template <class T>
int tmpArray<T>::Find(T* pointer, int first)
{
	for(int i = first; i < sizeUsed; i++)
	{
		if(memcmp(*pArray[i], *pointer, sizeof(T)) == 0) return i;
	}
	return -1;
}
//-----------------------------------------------------------------------
template <class T>
bool tmpArray<T>::save(FILE* xf)
{
	return true;
//   xf->xwrite(&curDelta,sizeof(curDelta)) &&
//		xf->xwrite(&sizeUsed,sizeof(sizeUsed)) &&
//		xf->xwrite(&sizeFull,sizeof(sizeFull)) &&
//		xf->xwrite(pArray,sizeof(T) * sizeUsed)
//		;
}
//-----------------------------------------------------------------------
template <class T>
bool tmpArray<T>::load(FILE* xf)
{
//	int curDelta1, sizeUsed1, sizeFull1;
//	bool head=false;

//	if( xf->xread(&curDelta1,sizeof(curDelta)) &&
//		xf->xread(&sizeUsed1,sizeof(sizeUsed)) &&
//		xf->xread(&sizeFull1,sizeof(sizeFull)) )
//	{
		//RemoveAll();
//		head=SetSize( sizeFull1, curDelta1);
//		sizeUsed=sizeUsed1;
//		head=head && xf->xread(pArray,sizeof(T) * sizeUsed);
//	}

//	return head;
	return true;
}
//-----------------------------------------------------------------------
// сохранение только описания массива, без содержимого
//-----------------------------------------------------------------------
template <class T>
bool	tmpArray<T>::saveDesc(FILE* xf)
{
//	return xf->xwrite(&curDelta,sizeof(curDelta)) &&
//		xf->xwrite(&sizeUsed,sizeof(sizeUsed)) &&
//		xf->xwrite(&sizeFull,sizeof(sizeFull));
   return true;
}
//-----------------------------------------------------------------------
// создание массива по сохраненному описанию
//-----------------------------------------------------------------------
template <class T>
bool	tmpArray<T>::loadDesc(FILE* xf)
{
//	int curDelta1, sizeUsed1, sizeFull1;
//	bool head=false;

//	if( xf->xread(&curDelta1,sizeof(curDelta)) &&
//		xf->xread(&sizeUsed1,sizeof(sizeUsed)) &&
//		xf->xread(&sizeFull1,sizeof(sizeFull)) )
//	{
// 	//RemoveAll();
//		head=SetSize( sizeFull1, curDelta1);
//		sizeUsed=sizeUsed1;
//	}

//	return head;
   return true;
}
