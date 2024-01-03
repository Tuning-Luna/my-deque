#include <iostream>
#include <cassert>
using namespace std;
#define MAX 100//deque最大长度

template <typename T>
class Deque
{
private:
	//deque属性
	T _val[MAX];             //内部数组
	int _size;              //元素个数

public:
	Deque()
	{
		_size = 0;
	}
	//迭代器类
	class iterator
	{
	private:
		T* _ptr;
	public:
		iterator(T* ptr) : _ptr(ptr) {} //有参构造函数，但是初始值只有调用时才知道值
		iterator& operator++() { _ptr++; return *this; }
		iterator operator++(int) { iterator temp = *this; ++(*this); return temp; }
		iterator& operator--() { _ptr--; return *this; }
		iterator operator--(int) { iterator temp = *this; --(*this); return temp; }
		T& operator*() const { return *_ptr; }
		T* operator->() const { return _ptr; }
		bool operator==(const iterator& other) const { return _ptr == other._ptr; }
		bool operator!=(const iterator& other) const { return !(*this == other); }
	};
	class const_iterator
	{
	private:
		const T* _ptr;
	public:
		const_iterator(const T* ptr) : _ptr(ptr) {}//有参构造函数，但是初始值只有调用时才知道值
		const_iterator& operator++() { _ptr++; return *this; }
		const_iterator operator++(int) { const_iterator temp = *this; ++(*this); return temp; }
		const_iterator& operator--() { _ptr--; return *this; }
		const_iterator operator--(int) { const_iterator temp = *this; --(*this); return temp; }
		const T& operator*() const { return *_ptr; }
		const T* operator->() const { return _ptr; }
		bool operator==(const const_iterator& other) const { return _ptr == other._ptr; }
		bool operator!=(const const_iterator& other) const { return !(*this == other); }
	};

	//重载
	bool operator==(const Deque& other); // ==运算符重载
	bool operator!=(const Deque& other); // !=运算符重载
	bool operator<(const Deque& other);  // <运算符重载
	bool operator<=(const Deque& other); // <=运算符重载
	bool operator>(const Deque& other);  // >运算符重载
	bool operator>=(const Deque& other); // >=运算符重载
	T& operator[](int index);            // 下标运算符重载

	//deque容器功能
	T& front();                          // 返回首元素
	T& back();                           // 返回尾元素
	void push_front(const T& value);     // 在队列前端插入元素
	void push_back(const T& value);      // 在队列后端插入元素
	void pop_front();                    // 删除首元素
	void pop_back();                     // 删除尾元素
	void assign(int n, const T& value);  // 赋值
	void insert(int pos, const T& value);// 插入元素（下标）
	void insert(Deque<T>::iterator it, const T& value);
	//插入元素（迭代器）
	void resize(int num);                //改变容器大小
	void erase(int pos);                 // 删除元素（下标）
	void erase(Deque<T>::iterator it);   // 删除元素（迭代器）
	void clear();                        // 清空容器
	bool empty() const;                  // 判断容器是否为空
	int size() const;                    // 获取容器的元素个数
	void swap(Deque& other);             // 交换两个容器

	//迭代器相关功能
	iterator begin() { return iterator(&_val[0]); }
	iterator end() { return iterator(&_val[_size]); }
	iterator rbegin() { return iterator(&_val[_size - 1]); }
	iterator rend() { return iterator(&_val[0] - 1); }
	const_iterator begin() const { return const_iterator(&_val[0]); }
	const_iterator end() const { return const_iterator(&_val[_size]); }
	const_iterator rbegin() const { return const_iterator(&_val[_size - 1]); }
	const_iterator rend()const { return const_iterator(&_val[0] - 1); }
};

//重载==
template <typename T>
bool Deque<T>::operator==(const Deque& temp)
{
	//先判断大小，大小不相等直接false
	if (_size != temp._size)
	{
		return false;
	}

	//依次遍历
	//只要找到一个不一样就返回false
	for (int i = 0; i < _size; i++)
	{
		if (_val[i] != temp._val[i])
		{
			return false;
		}
	}
	return true;
}

//重载!= (利用重载==）
template <typename T>
bool Deque<T>::operator!=(const Deque& temp)
{
	return !(*this == temp);//利用重载的 == 重载 !=
}

//重载< 
template <typename T>
bool Deque<T>::operator<(const Deque& temp)
{
	if (this->_size != temp._size)return this->_size < temp._size;
	for (int i = 0; i < this->_size; i++)
	{
		if (this->_val[i] >= temp._val[i])return false;
	}
	return true;
}

//重载<=（利用重载<）
template <typename T>
bool Deque<T>::operator<=(const Deque& temp)
{
	return ((*this < temp) || (*this == temp));
}

//重载>(利用重载<=)
template <typename T>
bool Deque<T>::operator>(const Deque& temp)
{
	return !(*this <= temp);
}

//重载>=(利用重载<）
template <typename T>
bool Deque<T>::operator>=(const Deque& temp)
{
	return !(*this < temp);
}

//重载[]
template <typename T>
T& Deque<T>::operator[](int _idx)
{
	assert(_idx < this->_size);
	return _val[_idx];
}

//front()返回头元素
template <typename T>
T& Deque<T>::front()
{
	assert(this->_size > 0);
	return _val[0];
}

//back()返回尾元素
template <typename T>
T& Deque<T>::back()
{
	assert(this->_size > 0);
	return _val[this->_size - 1];
}

//assign()赋值
template <typename T>
void Deque<T>::assign(int n, const T& value)
{
	assert(n <= this->_size);

	this->_size = n;
	for (int i = 0; i < this->_size; i++)
	{
		this->_val[i] = value;
	}
}

//insert(pos value) 插入
template <typename T>
void Deque<T>::insert(int pos, const T& value)
{
	assert(this->_size < MAX);
	assert(pos < MAX);
	for (int i = _size; i > pos; i--)
	{
		_val[i] = _val[i - 1];
	}
	_val[pos] = value;
	_size++;
}

//insert(iterator , value) 插入--重载
template <typename T>
void Deque<T>::insert(Deque<T>::iterator it, const T& value)
{
	assert(this->_size < MAX);

	int _count = 0;
	while (it != this->begin())//得到位置
	{
		_count++;
		it--;
	}

	for (int i = this->_size; i > _count; i--)
	{
		this->_val[i] = this->_val[i - 1];
	}
	this->_val[_count] = value;
	this->_size++;
}

//push_front() 头插
template <typename T>
void Deque<T>::push_front(const T& value)
{
	assert(this->_size < MAX);

	//元素依次向后移动，空出第一位
	for (int i = this->_size; i > 0; i--)
	{
		this->_val[i] = this->_val[i - 1];
	}
	this->_val[0] = value;
	this->_size++;
}

//push_back() 尾插
template <typename T>
void Deque<T>::push_back(const T& value)
{
	assert(this->_size < MAX);
	_val[this->_size] = value;
	++this->_size;
}

//pop_front() 头删
template <typename T>
void Deque<T>::pop_front()
{
	assert(this->_size != 0);
	for (int i = 0; i < this->_size - 1; i++)
	{
		this->_val[i] = this->_val[i + 1];
	}
	this->_size--;
}

//pop_back() 尾删
template <typename T>
void Deque<T>::pop_back()
{
	assert(this->_size != 0);
	this->_size--;
}

//erase(iterator) 删除
template <typename T>
void Deque<T>::erase(Deque<T>::iterator it)
{
	assert(this->_size != 0);
	int _count = 0;
	while (it != this->begin())//得到位置
	{
		_count++;
		it--;
	}
	for (int i = _count; i < this->_size; i++)
	{
		this->_val[i] = this->_val[i + 1];
	}
	this->_size--;
}

//erase(pos) 删除--重载版本
template <typename T>
void Deque<T>::erase(int pos)
{
	assert(this->_size != 0);
	for (int i = pos; i < this->_size; i++)
	{
		this->_val[i] = this->_val[i + 1];
	}
	this->_size--;
}

//clear() 清空容器
template <typename T>
void Deque<T>::clear()
{
	this->_size = 0;
}

//empty()判断是否为空
template <typename T>
bool Deque<T>::empty() const
{
	return _size == 0;
}

//size()得到容器大小
template <typename T>
int Deque<T>::size() const
{
	return _size;
}

//swap() 交换容器
template <typename T>
void Deque<T>::swap(Deque& target)
{
	//创建一个T数组和size
	T _temp_val[MAX] = { 0 };
	int _temp_size;

	// 保存当前容器的元素和元素个数
	for (int i = 0; i < this->_size; i++)
	{
		_temp_val[i] = this->_val[i];
	}
	_temp_size = this->_size;

	// 将当前容器替换为 temp 容器的元素和元素个数
	for (int i = 0; i < target._size; i++)
	{
		this->_val[i] = target._val[i];
	}
	_size = target._size;

	// 将 temp 容器替换为之前保存的当前容器的元素和元素个数
	for (int i = 0; i < _temp_size; i++)
	{
		target._val[i] = _temp_val[i];
	}
	target._size = _temp_size;
}

//resize() 改变大小
template<typename T>
void Deque<T>::resize(int num)
{
	assert(num >= 0 && num <= 100);
	if (this->_size < num)
	{
		for (int i = this->_size; i != num; ++i)
		{
			this->_val[i] = 0;
		}
	}
	this->_size = num;
}

