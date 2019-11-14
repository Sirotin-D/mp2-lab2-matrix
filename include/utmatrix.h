// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// utmatrix.h - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (21.04.2015)
//
// Верхнетреугольная матрица - реализация на основе шаблона вектора

#ifndef __TMATRIX_H__
#define __TMATRIX_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Шаблон вектора
template <class ValType>
class TVector
{
protected:
	ValType *pVector;
	int Size;       // размер вектора
	int StartIndex; // индекс первого элемента вектора
public:
	TVector(int s = 10, int si = 0);
	TVector(const TVector &v);                // конструктор копирования
	~TVector();
	int GetSize() { return Size; } // размер вектора
	int GetStartIndex() { return StartIndex; } // индекс первого элемента
	ValType& operator[](int pos);             // доступ
	bool operator==(const TVector &v) const;  // сравнение
	bool operator!=(const TVector &v) const;  // сравнение
	TVector& operator=(const TVector &v);     // присваивание

	// скалярные операции
	TVector  operator+(const ValType &val);   // прибавить скаляр
	TVector  operator-(const ValType &val);   // вычесть скаляр
	TVector  operator*(const ValType &val);   // умножить на скаляр

	// векторные операции
	TVector  operator+(const TVector &v);     // сложение
	TVector  operator-(const TVector &v);     // вычитание
	ValType  operator*(const TVector &v);     // скалярное произведение

	// ввод-вывод
	friend istream& operator>>(istream &istr, TVector &v)
	{
		for (int i = 0; i < v.Size; i++)
			istr >> v.pVector[i];
		return istr;
	}
	friend ostream& operator<<(ostream &ostr, const TVector &v)
	{
		for (int i = 0; i < v.StartIndex; i++) {
			ostr << "0 ";
		}
		for (int i = v.StartIndex; i < v.Size; i++) {

			ostr << v.pVector[i - v.StartIndex] << ' ';
		}

		return ostr;
	} 
};

template <class ValType>
TVector<ValType>::TVector(int s, int si)
{
	if (s > MAX_VECTOR_SIZE) { throw - 1; }
	if ((s == 0) && (si == 0)) {
		pVector = new ValType[1];
		pVector[1] = 0;
	}
	else {
		if ((s > -1) && (si > -1) && (s > si)) {
			Size = s;
			StartIndex = si;
			pVector = new ValType[Size - StartIndex];

		}
		else {
			if (s == si) {

				Size = s;
				StartIndex = 0;
				pVector = new ValType[Size - StartIndex];

			}
			else {
				cout << "Size is  " << s << " si " << si << "\n";
				throw "Сannot create vector";
			}

		}
	}
} /*-------------------------------------------------------------------------*/

template <class ValType> //конструктор копирования
TVector<ValType>::TVector(const TVector<ValType> &v)
{
	Size = v.Size;
	StartIndex = v.StartIndex;
	pVector = new ValType[Size - StartIndex];
	for (int i = 0; i < Size; i++)
	{
		pVector[i] = v.pVector[i];
	}
} /*-------------------------------------------------------------------------*/

template <class ValType>
TVector<ValType>::~TVector()
{
	delete[] pVector;
} /*-------------------------------------------------------------------------*/

template <class ValType> // доступ
ValType& TVector<ValType>::operator[](int pos)
{
	if ((pos - StartIndex) < 0) { throw - 1; }
	if ((pos) >= Size) { throw - 2; }
	return pVector[pos - StartIndex];
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator==(const TVector &v) const
{
	bool temp = false;
	if ((Size == v.Size) && (StartIndex == v.StartIndex)) {
		for (int i = 0; i < (Size - StartIndex); i++) {
			if (pVector[i] != v.pVector[i]) { return temp; }
		}
		temp = true;
	}
	return temp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator!=(const TVector &v) const
{	
	bool temp = true;
	if ((Size == v.Size) && (StartIndex == v.StartIndex)) {
		for (int i = 0; i < (Size - StartIndex); i++) {
			if (pVector[i] != v.pVector[i]) { return temp; }
		}
		temp = false;
	}
	return temp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TVector<ValType> & TVector<ValType>::operator=(const TVector &v)
{
	if (this != &v) { return *this; }
	else {
		delete[]pVector;
		Size = v.Size;
		StartIndex = v.StartIndex;
		pVector = new ValType[Size - StartIndex];
		for (int i = 0; i < Size - StartIndex; i++) {
			pVector[i] = v.pVector[i];
		}
		return *this;
	}
} /*-------------------------------------------------------------------------*/

template <class ValType> // прибавить скаляр
TVector<ValType> TVector<ValType>::operator+(const ValType &val)
{
	TVector<ValType> temp(*this);

	for (int i = 0; i < Size; i++) {
		temp.pVector[i] += val;
	}
	return temp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычесть скаляр
TVector<ValType> TVector<ValType>::operator-(const ValType &val)
{
	TVector temp(*this);
	for (int i = 0; i < Size; i++) {
		temp.pVector[i] -= val;
	}
	return temp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // умножить на скаляр
TVector<ValType> TVector<ValType>::operator*(const ValType &val)
{
	TVector temp(*this);
	for (int i = 0; i < Size; i++) {
		temp.pVector[i] *= val;
	}
	return temp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType> &v)
{
	TVector temp(Size, StartIndex);
	if (Size != v.Size) { throw "Size != v.size (operator +)"; }
	for (int i = 0; i < Size - StartIndex; i++) {
		temp.pVector[i] = pVector[i] + v.pVector[i];

	}
	return temp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType> &v)
{
	TVector temp(Size, StartIndex);
	if (Size != v.Size) { throw "Size != v.size (operator -)"; }
	for (int i = 0; i < Size - StartIndex; i++) {
		temp.pVector[i] = pVector[i] - v.pVector[i];

	}
	return temp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // скалярное произведение
ValType TVector<ValType>::operator*(const TVector<ValType> &v)
{
	ValType res = 0;
	TVector temp(Size, StartIndex);
	if (Size != v.Size) { throw "size != v.size (operator *)"; }
	for (int i = 0; i < Size; i++) {
		temp[i] = pVector[i] * v.pVector[i];
		res += temp[i];
	}
	return res;
} /*-------------------------------------------------------------------------*/


// Верхнетреугольная матрица
template <class ValType>
class TMatrix : public TVector<TVector<ValType> >
{
public:
  TMatrix(int s = 10);                           
  TMatrix(const TMatrix &mt);                    // копирование
  TMatrix(const TVector<TVector<ValType> > &mt); // преобразование типа
  bool operator==(const TMatrix &mt) const;      // сравнение
  bool operator!=(const TMatrix &mt) const;      // сравнение
  TMatrix& operator= (const TMatrix &mt);        // присваивание
  TMatrix  operator+ (const TMatrix &mt);        // сложение
  TMatrix  operator- (const TMatrix &mt);        // вычитание

  // ввод / вывод
  friend istream& operator>>(istream &istr, TMatrix &mt)
  {
	  for (int i = 0; i < mt.Size; i++)
		  istr >> mt.pVector[i];
	  return istr;
  }
  friend ostream & operator<<( ostream &ostr, const TMatrix &mt)
  {
	  for (int i = 0; i < mt.Size; i++)
		  ostr << mt.pVector[i] << endl;
	  return ostr;
  }
};

template <class ValType>
TMatrix<ValType>::TMatrix(int s): TVector<TVector<ValType> >(s)
{
	if (s > MAX_MATRIX_SIZE) { throw - 1; }
	for (int i = 0; i < s; i++) 
	{
		pVector[i] = TVector<ValType>(s,i);
	}
} /*-------------------------------------------------------------------------*/

template <class ValType> // конструктор копирования
TMatrix<ValType>::TMatrix(const TMatrix<ValType> &mt):
  TVector<TVector<ValType> >(mt) {}

template <class ValType> // конструктор преобразования типа
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> > &mt):
  TVector<TVector<ValType> >(mt) {}

template <class ValType> // сравнение
bool TMatrix<ValType>::operator==(const TMatrix<ValType> &mt) const
{
	bool temp = true;
	if (Size != mt.Size) { temp = false;  return temp; }
	for (int i = 0; i < Size - StartIndex; i++) {
		if (pVector[i] != mt.pVector[i]) { temp = false; return temp; }
	}
	return temp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TMatrix<ValType>::operator!=(const TMatrix<ValType> &mt) const
{
	bool temp = true;
	if (Size == mt.Size) {

		for (int i = 0; i < Size - StartIndex; i++) {
			if (pVector[i] == mt.pVector[i]) { temp = false; return temp; }
		}
	}
	return temp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType> &mt)
{
	if (this != &mt) {
		if (Size != mt.Size) {
			delete[]pVector;
			pVector = new TVector<ValType>[mt.Size - StartIndex];
		}
		Size = mt.Size; StartIndex = mt.StartIndex;
		for (int i = 0; i < Size - StartIndex; i++) {
			pVector[i] = mt.pVector[i];
		}
		return *this;
	}
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType> &mt)
{
	TMatrix res(mt);
	if (Size != mt.Size) { throw - 1; }

	for (int i = 0; i < Size - StartIndex; i++) {
		res.pVector[Size - i - 1] = pVector[Size - i - 1] + mt.pVector[Size - i - 1];
	}
	return res;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType> &mt)
{
	TMatrix res(mt);
	if (Size != mt.Size) { throw - 1; }

	for (int i = 0; i < Size - StartIndex; i++) {
		res.pVector[Size - i - 1] = pVector[Size - i - 1] - mt.pVector[Size - i - 1];
	}
	return res;
} /*-------------------------------------------------------------------------*/

// TVector О3 Л2 П4 С6
// TMatrix О2 Л2 П3 С3
#endif
