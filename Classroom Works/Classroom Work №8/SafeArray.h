#pragma once
template <class Type>

class SafeArray
{
private:
	Type* array = nullptr;
	int _size = 0;

public:
	SafeArray();
	SafeArray(int _size);
	int size();
	void push_back(Type object);
	auto operator[](int i) -> Type&;
	
};

template <class Type>
SafeArray<Type>::SafeArray() : _size(0)
{
	
}

template <class Type>
SafeArray<Type>::SafeArray(int size) : _size(size)
{
	array = new Type[size];
}

template <class Type>
int SafeArray<Type>::size()
{
	return _size;
}

template <class Type>
void SafeArray<Type>::push_back(Type object)
{
	Type* new_array = new Type[_size + 1];

	for (int i = 0; i < _size; ++i)
	{
		new_array[i] = array[i];
	}

	new_array[_size] = object;

	++_size;

	delete[] array;

	array = new_array;
}

template <class Type>
auto SafeArray<Type>::operator[](int i) -> Type&
{
	return array[i];
}

