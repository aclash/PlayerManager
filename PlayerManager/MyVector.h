template <typename T>
class MyVector
{
private:
	int theSize;
	int capacitytheSize;
	T* object;
public:
	static const int SPARE_CAPACITY = 16;
	explicit MyVector(int inittheSize = 0) :theSize{ inittheSize }, capacitytheSize{ inittheSize + SPARE_CAPACITY }
	{
		object = new T[capacitytheSize];
	}
	MyVector(const MyVector& rhs) :theSize{ rhs.theSize }, capacitytheSize{ rhs.capacitytheSize }, object{ nullptr } //deep copy
	{
		object = new T[capacitytheSize];
		for (int i = 0; i < theSize; ++i)
			object[i] = rhs.object[i];
	}
	MyVector& operator = (const MyVector& rhs)		//deep copy
	{
		/*	T* newp = new T[rhs.capacitytheSize];
		delete[] object;
		object = newp;
		theSize = rhs.theSize;
		capacitytheSize = rhs.capacitytheSize;
		return *this;*/

		MyVector temp = rhs;
		std::swap(*this, temp);
		return *this;
	}
	~MyVector()
	{
		delete[] object;
	}
	MyVector(MyVector&& rhs) :theSize{ rhs.theSize }, capacitytheSize{ rhs.capacitytheSize }, object{ rhs.object }				//shallow copy
	{
		rhs.object = nullptr;
		rhs.theSize = 0;
		rhs.capacitytheSize = 0;
	}
	MyVector& operator =(MyVector&& rhs)		//shallow copy
	{
		std::swap(theSize, rhs.theSize);
		std::swap(capacitytheSize, rhs.capacitytheSize);
		std::swap(object, rhs.object);
		return *this;
	}

	void reserve(int newCapacity)
	{
		if (newCapacity < theSize)
			return;

		T* newArray = new T[newCapacity];
		for (int i = 0; i < theSize; ++i)
			newArray[i] = std::move(object[i]);

		capacitytheSize = newCapacity;
		std::swap(object, newArray);
		delete[] newArray;
	}

	void resize(int newtheSize)
	{
		if (newtheSize > capacitytheSize)
			reserve(2 * newtheSize);
		theSize = newtheSize;
	}
	T& operator[](int index)
	{
		return object[index];
	}
	const T& operator[](int index) const
	{
		return object[index];
	}
	bool empty() const
	{
		return theSize == 0;
	}
	int size() const
	{
		return theSize;
	}
	int capacity() const
	{
		return capacitytheSize;
	}
	void push_back(const T& x)
	{
		resize(theSize + 1);
		object[theSize - 1] = x;
	}
	void push_back(T&& x)
	{
		resize(theSize + 1);
		object[theSize - 1] = std::move(x);
	}
	void pop_back()
	{
		--theSize;
	}

	const T& back() const
	{
		return object[theSize - 1];
	}

	typedef T* iterator;
	typedef const T* const_Iterator;

	iterator begin()
	{
		return &object[0];
	}
	const_Iterator begin() const
	{
		return &object[0];
	}
	iterator end()
	{
		return &object[size()];
	}
	const_Iterator end() const
	{
		return &object[size()];
	}
};