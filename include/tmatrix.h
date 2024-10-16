// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - шаблонный вектор из динамической памяти
template<typename T>
class TDynamicVector
{
protected: 
	size_t sz;
	T* pMem;
public:
	TDynamicVector(size_t size = 1) : sz(size) // конструктор инициализатор + по умолчанию
	{
		if (sz == 0 || sz > MAX_VECTOR_SIZE)
			throw out_of_range("Vector size should be greater than zero and less than MAX_VECTOR_SIZE");
		pMem = new T[sz](); // {}; // У типа T должен быть конструктор по умолчанию
	}

	TDynamicVector(T* arr, size_t size) : sz(size) // конструктор преобразования типа
	{
		assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
		pMem = new T[sz];
		copy(arr, arr + sz, pMem);
	}

	TDynamicVector(const TDynamicVector& v) // конструктор копирования
	{
		sz = v.sz;
		pMem = new T[sz];
		copy(v.pMem, v.pMem + sz, pMem);
	}

	TDynamicVector(TDynamicVector&& v) noexcept // конструктор перемещения
	{
		sz = v.sz;
		pMem = v.pMem;
		v.sz = 0;
		v.pMem = nullptr;
	}

	~TDynamicVector() // деструктор
	{
		delete[] pMem;
	}

	TDynamicVector& operator=(const TDynamicVector& v)
	{
		if (this != &v)
		{
			delete[] pMem;
			sz = v.sz;
			pMem = new T[sz];
			copy(v.pMem, v.pMem + sz, pMem);
		}
		return *this;
	}

	TDynamicVector& operator=(TDynamicVector&& v) noexcept
	{
		if (this != &v)
		{
			sz = v.sz;
			pMem = v.pMem;
			v.sz = 0;
			v.pMem = nullptr;
		}
		return *this;
	}

	size_t size() const noexcept
	{
		return sz;
	}

	// индексация
	T& operator[](size_t ind) 
	{
		return pMem[ind];
	}

	const T& operator[](size_t ind) const 
	{
		return pMem[ind];
	}

	// индексация с контролем
	T& at(size_t ind) 
	{
		if (ind < 0 || ind >= sz)
			throw out_of_range("Invalid index");
		return pMem[ind];
	}

	const T& at(size_t ind) const 
	{
		if (ind < 0 || ind >= sz)
			throw out_of_range("Invalid index");
		return pMem[ind];
	}

	// сравнение
	bool operator==(const TDynamicVector& v) const noexcept
	{
		if (sz != v.sz)
			return false;
		else {
			for (size_t i = 0; i < sz; i++)
				if (pMem[i] != v.pMem[i])
					return false;
		}
		return true;
	}

	bool operator!=(const TDynamicVector& v) const noexcept
	{
		return !(*this == v);
	}

	// скалярные операции
	TDynamicVector operator+(T val)
	{
		TDynamicVector<T> result(sz);
		for (size_t i = 0; i < sz; i++)
			result.pMem[i] = pMem[i] + val;
		return result;
	}

	TDynamicVector operator-(T val)
	{
		TDynamicVector<T> result(sz);
		for (size_t i = 0; i < sz; i++)
			result.pMem[i] = pMem[i] - val;
		return result;
	}

	TDynamicVector operator*(T val)
	{
		TDynamicVector<T> result(sz);
		for (size_t i = 0; i < sz; i++)
			result.pMem[i] = pMem[i] * val;
		return result;
	}

	// векторные операции
	TDynamicVector operator+(const TDynamicVector& v)
	{
		if (sz != v.sz)
			throw length_error("Vector's sizes aren't equal");
		TDynamicVector<T> result(sz);
		for (size_t i = 0; i < sz; i++)
			result.pMem[i] = pMem[i] + v.pMem[i];
		return result;
	}

	TDynamicVector operator-(const TDynamicVector& v)
	{
		if (sz != v.sz)
			throw length_error("Vector's sizes aren't equal");
		TDynamicVector<T> result(sz);
		for (size_t i = 0; i < sz; i++)
			result.pMem[i] = pMem[i] - v.pMem[i];
		return result;
	}

	T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
	{
		if (sz != v.sz)
			throw length_error("Vector's sizes aren't equal");
		T result = 0;
		for (size_t i = 0; i < sz; i++)
			result += pMem[i] * v.pMem[i];
		return result;
	}

	friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
	{
		swap(lhs.sz, rhs.sz);
		swap(lhs.pMem, rhs.pMem);
	}

	// ввод/вывод
	friend istream& operator>>(istream& istr, TDynamicVector& v)
	{
		for (size_t i = 0; i < v.sz; i++)
			istr >> v.pMem[i]; // требуется оператор>> для типа T
		return istr;
	}

	friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
	{
		for (size_t i = 0; i < v.sz; i++)
			ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
		return ostr;
	}
};

// Динамическая матрица - шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
	using TDynamicVector<TDynamicVector<T>>::pMem;
	using TDynamicVector<TDynamicVector<T>>::sz;
public:
	TDynamicMatrix(size_t size = 1) : TDynamicVector<TDynamicVector<T>>(size) // конструктор инициализатор + по умолчанию
	{
		if (sz == 0 || sz > MAX_MATRIX_SIZE)
			throw out_of_range("Matrix size should be greater than zero and less than MAX_MATRIX_SIZE");
		for (size_t i = 0; i < sz; i++)
			pMem[i] = TDynamicVector<T>(sz);
	}

	TDynamicMatrix(const TDynamicMatrix& m) : TDynamicVector<TDynamicVector<T>>(m.sz) // конструктор копирования
	{
		for (size_t i = 0; i < sz; i++)
			pMem[i] = m.pMem[i];
	}

	TDynamicMatrix(TDynamicMatrix&& m) noexcept // конструктор перемешения
	{
		sz = m.sz;
		pMem = m.pMem;
		m.sz = 0;
		m.pMem = nullptr;
	}

	TDynamicMatrix& operator=(const TDynamicMatrix& m)
	{
		if (this != &m)
		{
			delete[] pMem;
			sz = m.sz;
			pMem = new TDynamicVector<T>[sz];
			for (size_t i = 0; i < sz; i++)
				pMem[i] = m.pMem[i];
		}
		return *this;
	}

	TDynamicMatrix& operator=(TDynamicMatrix&& m) noexcept
	{
		if (this != &m)
		{
			sz = m.sz;
			pMem = m.pMem;
			m.sz = 0;
			m.pMem = nullptr;
		}
		return *this;
	}

	using TDynamicVector<TDynamicVector<T>>::operator[];

	using TDynamicVector<TDynamicVector<T>>::size;

	using TDynamicVector<TDynamicVector<T>>::at;

	// сравнение 
	bool operator==(const TDynamicMatrix& m) const noexcept
	{
		if (sz != m.sz)
			return false;
		else {
			for (size_t i = 0; i < sz; i++)
				if (pMem[i] != m.pMem[i])
					return false;
		}
		return true;
	}

	bool operator!=(const TDynamicMatrix& m) const noexcept
	{
		return !(*this == m);
	}

	// матрично-скалярные операции
	TDynamicMatrix operator*(const T& val)
	{
		TDynamicMatrix result(sz);
		for (size_t i = 0; i < sz; i++)
			result[i] = pMem[i] * val;
		return result;
	}

	// матрично-векторные операции
	TDynamicVector operator*(const TDynamicVector<T>& v)
	{
		if (sz != v.size())
			throw invalid_argument("Matrix and vector sizes should be equal");
		TDynamicMatrix result(sz);
		for (size_t i = 0; i < sz; i++)
			result[i] = pMem[i] * v;
		return result;
	}

	// матрично-матричные операции
	TDynamicMatrix operator+(const TDynamicMatrix& m)
	{
		if (sz != m.sz)
			throw length_error("Matrix's sizes aren't equal");
		TDynamicMatrix result(sz);
		for (size_t i = 0; i < sz; i++)
			for (size_t j = 0; j < sz; j++)
				result[i][j] = pMem[i][j] + m.pMem[i][j];
		return result;
	}

	TDynamicMatrix operator-(const TDynamicMatrix& m)
	{
		if (sz != m.sz)
			throw length_error("Matrix's sizes aren't equal");
		TDynamicMatrix result(sz);
		for (size_t i = 0; i < sz; i++)
			for (size_t j = 0; j < sz; j++)
				result[i][j] = pMem[i][j] - m.pMem[i][j];
		return result;
	}

	TDynamicMatrix operator*(const TDynamicMatrix& m)
	{
		if (sz != m.sz)
			throw length_error("Matrix's sizez aren't equal");
		TDynamicMatrix result(sz);
		for (size_t i = 0; i < sz; i++)
			for (size_t j = 0; j < sz; j++)
				for (size_t k = 0; k < sz; k++)
					result[i][j] += pMem[i][k] * m.pMem[k][j];
		return result;
	}

	// ввод/вывод
	friend istream& operator>>(istream& istr, TDynamicMatrix& m)
	{
		for (size_t i = 0; i < m.sz; i++)
			istr >> m.pMem[i]; // требуется оператор>> для типа T
		return istr;
	}

	friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& m)
	{
		for (size_t i = 0; i < m.sz; i++)
			ostr << m.pMem[i] << ' '; // требуется оператор<< для типа T
		return ostr;
	}
};

#endif


