#include <iostream>
#include <iterator>
using namespace std;
template <typename Type>
void destroy(Type* p) {
	p->~Type();
}
template <typename Type>
class my_vector
{
public:
	class my_iterator;
	class const_my_iterator;
	class my_rev_iterator;
	class const_my_rev_iterator;
private:
	Type* my_data;
	size_t size_of_data;
	size_t reserv;
	my_iterator begining;
	my_iterator ending;
public:
	my_vector()
	{
		my_data = NULL;
		size_of_data = 0;
		reserv = 0;
		begining = my_iterator(this, 0);
		ending = my_iterator(this, size_of_data - 1);
	}
	/*my_vector(const my_vector& other)
	{
		size_of_data = other.size_of_data;
		reserv = other.reserv;
		my_data = new Type[reserv];
		memcpy(my_data, other.my_data, size_of_data * (sizeof(Type)));
	}*/
	my_vector(size_t size)
	{
		my_data = new Type[size];
		size_of_data = size;
		reserv = size;
		memset(my_data, 0, sizeof(my_data) * size);
		begining = my_iterator(this, 0);
		ending = my_iterator(this, size_of_data - 1);
	}
	my_vector(size_t size, const Type& value)
	{
		my_data = new Type[size];
		for (int i = 0; i < size; i++) my_data[i] = value;
		size_of_data = size;
		reserv = size;
		begining = my_iterator(this, 0);
		ending = my_iterator(this, size_of_data - 1);
	}
	my_vector(const initializer_list<Type> _list)
	{
		reserv = 0;
		for (auto& element : _list) { reserv++; }
		int count = 0;
		my_data = new Type[reserv];
		for (auto& element : _list)
		{
			my_data[count] = element;
			++count;
		}
		size_of_data = count;
		begining = my_iterator(this, 0);
		ending = my_iterator(this, size_of_data - 1);
	}
	my_vector& operator=(const initializer_list<Type> _list)
	{
		reserv = 0;
		for (auto& element : _list) { reserv++; }
		int count = 0;
		my_data = new Type[reserv];
		for (auto& element : _list)
		{
			my_data[count] = element;
			++count;
		}
		size_of_data = count;
		begining = my_iterator(this, 0);
		ending = my_iterator(this, size_of_data - 1);
		return *this;
	}
	my_vector& operator=(const my_vector& other)
	{
		//clear();
		delete[]my_data;
		size_of_data = other.size_of_data;
		reserv = other.reserv;
		my_data = new Type[reserv];
		if (other.my_data != NULL)
		{
			for (int i = 0; i < size_of_data; i++)
			{
				my_data[i] = other.my_data[i];
			}
		}
		begining = other.begining;
		ending = other.ending;
		return *this;
	}
	my_vector& operator[](size_t index)
	{
		return &my_data[index];
	}
	~my_vector()
	{
		while (size_of_data != 0)
		{
			destroy(my_data + size_of_data - 1);
			size_of_data--;
		}
		size_of_data = 0;
		reserv = 0;
	}
	size_t size()const noexcept
	{
		return size_of_data;
	}
	const Type* data()const noexcept
	{
		if (size() == 0 || my_data == nullptr) { cout << "Data NULL!" << endl; return NULL; }
		else { return my_data; }
	}
	Type* data()noexcept
	{
		if (size() == 0 || my_data == nullptr) { cout << "Data NULL!" << endl; return NULL; }
		else { return my_data; }
	}
	Type& operator[](int i)
	{
		return (this->my_data[i]);
	}
	const Type& operator[](int i)const
	{
		return (this->my_data[i]);
	}
	Type at(size_t index)
	{
		if (index<0 || index>size_of_data) { cout << "Error!" << endl; return NULL; }
		return my_data[index];
	}
	const Type at(size_t index)const
	{
		if (index<0 || index>size_of_data) { cout << "Error!" << endl; return NULL; }
		return my_data[index];
	}
	Type back()
	{
		if (empty()) { cout << "Error!" << endl; return NULL; }
		return *ending;
	}
	const Type back()const
	{
		if (empty()) { cout << "Error!" << endl; return NULL; }
		return *ending;
	}
	void reserve(size_t size)
	{
		if (reserv >= size) { cout << "Error capacity!" << endl; return; }
		Type* tmp = new Type[size_of_data];
		for (int i = 0; i < size_of_data; i++)
		{
			tmp[i] = my_data[i];
		}
		delete[]my_data;
		my_data = new Type[size];
		for (int i = 0; i < size_of_data; i++)
		{
			my_data[i] = tmp[i];
		}
		delete[]tmp;
		reserv = size;
	}
	void resize(size_t n)
	{
		size_t size = n;
		size_t prev_res = reserv;
		if (n > size_of_data)size = size_of_data;
		Type* tmp = new Type[size];
		for (int i = 0; i < size; i++)
		{
			tmp[i] = my_data[i];
		}
		//clear();
		delete[]my_data;
		size_of_data = n;
		if (n > prev_res)reserv = n;
		else { reserv = prev_res; }
		my_data = new Type[reserv];
		for (int i = 0; i < size; i++)
		{
			my_data[i] = tmp[i];
		}
		delete[]tmp;
		if (size < size_of_data)
		{
			memset(my_data + size, 0, (sizeof(Type)) * (size_of_data - size));
		}
		begining = my_iterator(this, 0);
		ending = my_iterator(this, size_of_data - 1);
	}
	void resize(size_t n, const Type& value)
	{
		size_t size = n;
		size_t prev_res = reserv;
		if (n > size_of_data)size = size_of_data;
		Type* tmp = new Type[size];
		for (int i = 0; i < size; i++)
		{
			tmp[i] = my_data[i];
		}
		//clear();
		delete[]my_data;
		size_of_data = n;
		if (n > prev_res)reserv = n;
		else { reserv = prev_res; }
		my_data = new Type[reserv];
		for (int i = 0; i < size; i++)
		{
			my_data[i] = tmp[i];
		}
		delete[]tmp;
		if (size < size_of_data)
		{

			while (size != size_of_data)
			{
				my_data[size] = value;
				size++;
			}
		}
		begining = my_iterator(this, 0);
		ending = my_iterator(this, size_of_data - 1);
	}
	size_t capacity()const noexcept
	{
		return reserv;
	}
	void clear() noexcept
	{
		while (size_of_data > 0) pop_back();
		size_of_data = 0;
	}
	bool empty() const noexcept
	{
		if (my_data == nullptr || size_of_data == 0) {
			return true;
		}
		return false;
	}
	Type front()
	{
		if (empty()) {
			cout << "my_vector is empty!" << endl;
			return;
		}
		return *begining;
	}
	const Type front()const
	{
		if (empty()) {
			cout << "my_vector is empty!" << endl;
			return NULL;
		}
		return *begining;
	}
	void pop_back()
	{
		if (empty()) {
			cout << "my_vector is empty!" << endl;
			return;
		}
		destroy(my_data + size_of_data - 1);
		size_of_data--;
		ending = my_iterator(this, size_of_data - 1);
	}
	void push_back(const Type& value)
	{
		if (size_of_data < reserv)
		{
			size_of_data++;
			my_data[size_of_data - 1] = value;
			ending = my_iterator(this, size_of_data - 1);
			return;
		}
		resize(size_of_data + 1, value);
		ending = my_iterator(this, size_of_data - 1);
	}
	void shrink_to_fit()
	{
		if (reserv > size_of_data) {
			size_t tmp_size = size_of_data;
			Type* tmp = new Type[tmp_size];
			for (int i = 0; i < size_of_data; i++)
			{
				tmp[i] = my_data[i];
			}
			//clear();
			delete[]my_data;
			size_of_data = tmp_size;
			reserv = tmp_size;
			my_data = new Type[size_of_data];
			for (int i = 0; i < size_of_data; i++)
			{
				my_data[i] = tmp[i];
			}
			delete[]tmp;
			begining = my_iterator(this, 0);
			ending = my_iterator(this, size_of_data - 1);
		}
	}
	void swap(my_vector& other)
	{
		my_vector<Type>tmp_vec;
		tmp_vec = *this;
		*this = other;
		other = tmp_vec;
	}
	size_t max_size() const noexcept
	{
		return (pow(2, 32) - 1) / sizeof(Type);
	}
	class my_iterator : public std::iterator<std::random_access_iterator_tag, Type>
	{
	private:
		const my_vector<Type>* p;
		int index;
	public:
		friend class my_vector;
		my_iterator() : p(0), index(0) {}
		my_iterator(const my_vector* p, int index) : p(p), index(index) { }
		my_iterator(const my_iterator& it) : p(it.p), index(it.index) { }
		//my_iterator(const const_my_iterator& it) : p(it.p), index(it.index) { }
		~my_iterator() {}
		my_iterator& operator=(const my_iterator& it)
		{
			p = it.p;
			index = it.index;
			return *this;
		}
		my_iterator& operator++()
		{
			index++;
			return *this;
		}
		my_iterator operator++(int)
		{
			my_iterator copy(*this);
			operator++();
			return copy;
		}
		my_iterator& operator--()
		{
			index--;
			return *this;
		}
		my_iterator operator--(int)
		{
			my_iterator copy(*this);
			operator--();
			return copy;
		}
		my_iterator operator+(const int& i)const
		{
			return my_iterator(p, index + i);
		}
		my_iterator operator+=(const int& i)
		{
			index += i;
			return *this;
		}
		my_iterator operator-(const int& i)const
		{
			return my_iterator(p, index - i);
		}
		my_iterator operator-=(const int& i)
		{
			index -= i;
			return *this;
		}
		size_t operator-(const my_iterator& it)
		{
			if (p != it.p) cout << "Iterators are in different vectors." << endl;
			return index - it.index;
		}
		typename my_iterator::reference operator[](int i) const { /*auto tmp = *p; tmp += n; return *tmp;*/return (p->my_data[i]); }
		typename my_iterator::reference operator*() const { return (p->my_data[index]); }
		/*Type* operator->()
		{
			return &p->my_data[index];
		}*/
		bool operator==(my_iterator const& it) const
		{
			return p == it.p && index == it.index;
		}
		bool operator!=(my_iterator const& it) const
		{
			return !(*this == it);
		}
		bool operator<(my_iterator const& it)const
		{
			if (p != it.p) cout << "Iterators are in different vectors." << endl;
			return index < it.index;
		}
		bool operator>(my_iterator const& it)const
		{
			if (p != it.p) cout << "Iterators are in different vectors." << endl;
			return index > it.index;
		}
		bool operator<=(my_iterator const& it)const
		{
			if (p != it.p) cout << "Iterators are in different vectors." << endl;
			return index <= it.index;
		}
		bool operator>=(my_iterator const& it)const
		{
			if (p != it.p) cout << "Iterators are in different vectors." << endl;
			return index >= it.index;
		}
	};
	class const_my_iterator : public std::iterator<std::random_access_iterator_tag, const Type>
	{
	private:
		const my_vector<Type>* p;
		int index;
	public:
		friend class my_vector;
		const_my_iterator() : p(0), index(0) {}
		const_my_iterator(const my_vector* p, int index) : p(p), index(index) { }
		const_my_iterator(const const_my_iterator& it) : p(it.p), index(it.index) { }
		const_my_iterator(const my_iterator& it) : p(it.p), index(it.index) { }
		const_my_iterator& operator=(const const_my_iterator& it)
		{
			p = it.p;
			index = it.index;
			return *this;
		}
		~const_my_iterator() {}
		const typename const_my_iterator::reference operator[](int i) const { return (p->my_data[i]); }
		const typename const_my_iterator::reference operator*() const { return (p->my_data[index]); }
		const_my_iterator& operator++()
		{
			index++;
			return *this;
		}
		const_my_iterator operator++(int)
		{
			const_my_iterator copy(*this);
			operator++();
			return copy;
		}
		const_my_iterator& operator--()
		{
			index--;
			return *this;
		}
		const_my_iterator operator--(int)
		{
			const_my_iterator copy(*this);
			operator--();
			return copy;
		}
		const_my_iterator operator+(const size_t& i)const
		{
			return const_my_iterator(p, index + i);
		}
		const_my_iterator operator+=(const size_t& i)
		{
			index += i;
			return *this;
		}
		const_my_iterator operator-(const size_t& i)const
		{
			return const_my_iterator(p, index - i);
		}
		const_my_iterator operator-=(const size_t& i)
		{
			index -= i;
			return *this;
		}
		size_t operator-(const const_my_iterator& it)
		{
			if (p != it.p) cout << "Iterators are in different vectors." << endl;
			return index - it.index;
		}
		bool operator==(const_my_iterator const& it) const
		{
			return p == it.p && index == it.index;
		}
		bool operator!=(const_my_iterator const& it) const
		{
			return !(*this == it);
		}
		bool operator<(const_my_iterator const& it)const
		{
			if (p != it.p) cout << "Iterators are in different vectors." << endl;
			return index < it.index;
		}
		bool operator>(const_my_iterator const& it)const
		{
			if (p != it.p) cout << "Iterators are in different vectors." << endl;
			return index > it.index;
		}
		bool operator<=(const_my_iterator const& it)const
		{
			if (p != it.p) cout << "Iterators are in different vectors." << endl;
			return index <= it.index;
		}
		bool operator>=(const_my_iterator const& it)const
		{
			if (p != it.p) cout << "Iterators are in different vectors." << endl;
			return index >= it.index;
		}
	};
	class my_rev_iterator : public std::iterator<std::random_access_iterator_tag, Type>
	{
	private:
		const my_vector<Type>* p;
		int index;
	public:
		friend class my_vector;
		my_rev_iterator() : p(0), index(0) {}
		my_rev_iterator(const my_vector* p, int index) : p(p), index(index) { }
		my_rev_iterator(const my_rev_iterator& it) : p(it.p), index(it.index) { }
		~my_rev_iterator() {}
		my_rev_iterator& operator=(const my_rev_iterator& it)
		{
			p = it.p;
			index = it.index;
			return *this;
		}
		my_rev_iterator& operator++()
		{
			index--;
			return *this;
		}
		my_rev_iterator operator++(int)
		{
			my_rev_iterator copy(*this);
			operator++();
			return copy;
		}
		my_rev_iterator& operator--()
		{
			index++;
			return *this;
		}
		my_rev_iterator operator--(int)
		{
			my_rev_iterator copy(*this);
			operator--();
			return copy;
		}
		my_rev_iterator operator+(const int& i)const
		{
			return my_rev_iterator(p, index - i);
		}
		my_rev_iterator operator+=(const int& i)
		{
			index -= i;
			return *this;
		}
		my_rev_iterator operator-(const int& i)const
		{
			return my_rev_iterator(p, index + i);
		}
		my_rev_iterator operator-=(const int& i)
		{
			index += i;
			return *this;
		}
		size_t operator-(const my_rev_iterator& it)
		{
			if (p != it.p) cout << "Iterators are in different vectors." << endl;
			return index + it.index;
		}
		typename my_rev_iterator::reference operator[](int i) const { /*auto tmp = *p; tmp += n; return *tmp;*/return (p->my_data[i]); }
		typename my_rev_iterator::reference operator*() const { return (p->my_data[index]); }
		/*Type* operator->()
		{
			return &p->my_data[index];
		}*/
		bool operator==(my_rev_iterator const& it) const
		{
			return p == it.p && index == it.index;
		}
		bool operator!=(my_rev_iterator const& it) const
		{
			return !(*this == it);
		}
		bool operator<(my_rev_iterator const& it)const
		{
			if (p != it.p) cout << "Iterators are in different vectors." << endl;
			return index > it.index;
		}
		bool operator>(my_rev_iterator const& it)const
		{
			if (p != it.p) cout << "Iterators are in different vectors." << endl;
			return index < it.index;
		}
		bool operator<=(my_rev_iterator const& it)const
		{
			if (p != it.p) cout << "Iterators are in different vectors." << endl;
			return index >= it.index;
		}
		bool operator>=(my_rev_iterator const& it)const
		{
			if (p != it.p) cout << "Iterators are in different vectors." << endl;
			return index <= it.index;
		}
	};
	class const_my_rev_iterator : public std::iterator<std::random_access_iterator_tag, const Type>
	{
	private:
		const my_vector<Type>* p;
		int index;
	public:
		friend class my_vector;
		const_my_rev_iterator() : p(0), index(0) {}
		const_my_rev_iterator(const my_vector* p, int index) : p(p), index(index) { }
		const_my_rev_iterator(const const_my_rev_iterator& it) : p(it.p), index(it.index) { }
		const_my_rev_iterator(const my_rev_iterator& it) : p(it.p), index(it.index) { }
		~const_my_rev_iterator() {}
		const_my_rev_iterator& operator=(const const_my_rev_iterator& it)
		{
			p = it.p;
			index = it.index;
			return *this;
		}
		const_my_rev_iterator& operator++()
		{
			index--;
			return *this;
		}
		const_my_rev_iterator operator++(int)
		{
			const_my_rev_iterator copy(*this);
			operator++();
			return copy;
		}
		const_my_rev_iterator& operator--()
		{
			index++;
			return *this;
		}
		const_my_rev_iterator operator--(int)
		{
			const_my_rev_iterator copy(*this);
			operator--();
			return copy;
		}
		const_my_rev_iterator operator+(const int& i)const
		{
			return const_my_rev_iterator(p, index - i);
		}
		const_my_rev_iterator operator+=(const int& i)
		{
			index -= i;
			return *this;
		}
		const_my_rev_iterator operator-(const int& i)const
		{
			return const_my_rev_iterator(p, index + i);
		}
		const_my_rev_iterator operator-=(const int& i)
		{
			index += i;
			return *this;
		}
		size_t operator-(const const_my_rev_iterator& it)
		{
			if (p != it.p) cout << "Iterators are in different vectors." << endl;
			return index + it.index;
		}
		const typename const_my_rev_iterator::reference operator[](int i) const { return (p->my_data[i]); }
		const typename const_my_rev_iterator::reference operator*() const { return (p->my_data[index]); }
		/*Type* operator->()
		{
			return &p->my_data[index];
		}*/
		bool operator==(const_my_rev_iterator const& it) const
		{
			return p == it.p && index == it.index;
		}
		bool operator!=(const_my_rev_iterator const& it) const
		{
			return !(*this == it);
		}
		bool operator<(const_my_rev_iterator const& it)const
		{
			if (p != it.p) cout << "Iterators are in different vectors." << endl;
			return index > it.index;
		}
		bool operator>(const_my_rev_iterator const& it)const
		{
			if (p != it.p) cout << "Iterators are in different vectors." << endl;
			return index < it.index;
		}
		bool operator<=(const_my_rev_iterator const& it)const
		{
			if (p != it.p) cout << "Iterators are in different vectors." << endl;
			return index >= it.index;
		}
		bool operator>=(const_my_rev_iterator const& it)const
		{
			if (p != it.p) cout << "Iterators are in different vectors." << endl;
			return index <= it.index;
		}
	};

public:
	my_iterator begin() const { return begining; }
	my_iterator end() const { return  ending; }

	const_my_iterator cbegin() const { return const_my_iterator(this, 0); }
	const_my_iterator cend() const { return  const_my_iterator(this, size_of_data - 1); }

	my_rev_iterator rbegin() const { return my_rev_iterator(this, size_of_data - 1); }
	my_rev_iterator rend() const { return my_rev_iterator(this, 0); }

	const_my_rev_iterator crbegin() const { return const_my_rev_iterator(this, size_of_data - 1); }
	const_my_rev_iterator crend() const { return  const_my_rev_iterator(this, 0); }

	template<class my_iterator>
	void assign(my_iterator first, my_iterator last)
	{
		int len = last - first;
		Type* tmp = new Type[len + 1];
		int count = 0;
		for (my_iterator it = first; it <= last; it++)
		{
			tmp[count] = *it;
			count++;
		}
		//memset(my_data, 0, size_of_data * (sizeof(Type)));
		delete[]my_data;
		my_data = new Type[reserv];
		for (int i = 0; i < len + 1; i++)
		{
			my_data[i] = tmp[i];
		}
		//memcpy(my_data, tmp, sizeof(Type) * (len + 1));
		size_of_data = len + 1;
		delete[]tmp;
		begining = my_iterator(this, 0);
		ending = my_iterator(this, size_of_data - 1);
	}
	void assign(const size_t size, const Type& value)
	{
		if (reserv < size) reserv = size;
		size_t tmp_reserv = reserv;
		//clear();
		delete[]my_data;
		reserv = tmp_reserv;
		size_of_data = size;
		my_data = new Type[reserv];
		size_of_data = size;
		for (int i = 0; i < size_of_data; i++)
		{
			my_data[i] = value;
		}
		begining = my_iterator(this, 0);
		ending = my_iterator(this, size_of_data - 1);
	}
	void assign(initializer_list<Type> _list)
	{
		int count = 0;
		for (auto& element : _list) { count++; }
		if (reserv < count) reserv = count;
		size_t tmp_reserv = reserv;
		//clear();
		delete[]my_data;
		reserv = tmp_reserv;
		my_data = new Type[reserv];
		count = 0;
		for (auto& element : _list)
		{
			my_data[count] = element;
			++count;
		}
		size_of_data = count;
		begining = my_iterator(this, 0);
		ending = my_iterator(this, size_of_data - 1);
	}
	my_iterator erase(my_iterator position)
	{
		Type* tmp = new Type[size_of_data - 1];
		int count = 0;
		for (my_iterator it = begining; it <= ending; it++)
		{
			if (it != position)
			{
				tmp[count] = *it;
				count++;
			}
		}
		delete[]my_data;
		my_data = new Type[reserv];
		for (int i = 0; i < size_of_data - 1; i++)
		{
			my_data[i] = tmp[i];
		}
		//memcpy(my_data, tmp, sizeof(Type) * (size_of_data - 1));
		size_of_data--;
		delete[]tmp;
		begining = my_iterator(this, 0);
		ending = my_iterator(this, size_of_data - 1);
		my_iterator pos = ++position;
		return pos;
	}
	my_iterator erase(my_iterator first, my_iterator last)
	{
		int len = last - first;
		Type* tmp = new Type[size_of_data - len];
		int count = 0;
		for (my_iterator it = begining; it <= ending; it++)
		{
			if (it < first || it >= last)
			{
				tmp[count] = *it;
				count++;
			}
		}
		delete[]my_data;
		my_data = new Type[reserv];
		for (int i = 0; i < size_of_data - len; i++)
		{
			my_data[i] = tmp[i];
		}
		//memcpy(my_data, tmp, sizeof(Type) * (size_of_data-len));
		size_of_data -= len;
		delete[]tmp;
		begining = my_iterator(this, 0);
		ending = my_iterator(this, size_of_data - 1);
		my_iterator pos = ++last;
		return pos;
	}
	my_iterator emplase(const my_iterator position, Type args)
	{
		return insert(position, args);
	}
	my_iterator emplase_back(Type args)
	{
		return insert(ending, args);
	}
	my_iterator insert(const my_iterator position, const Type& value)
	{
		Type* tmp = new Type[size_of_data + 1];
		int count = 0;
		for (my_iterator it = begining; it <= position; it++)
		{
			tmp[count] = *it;
			count++;
		}
		tmp[count] = value;
		count++;
		for (my_iterator it = position + 1; it <= ending; it++)
		{
			tmp[count] = *it;
			count++;
		}
		if (reserv < count) { reserv = count; }
		size_t tmp_size = size_of_data + 1;
		size_t tmp_reserv = reserv;
		//clear();
		delete[]my_data;
		reserv = tmp_reserv;
		size_of_data = tmp_size;
		my_data = new Type[reserv];
		for (int i = 0; i < size_of_data; i++)
		{
			my_data[i] = tmp[i];
		}
		delete[]tmp;
		begining = my_iterator(this, 0);
		ending = my_iterator(this, size_of_data - 1);
		my_iterator pos = position + 1;
		return pos;
	}
	my_iterator insert(const my_iterator position, size_t n, const Type& value)
	{
		my_iterator it = position;
		while (n != 0)
		{
			it = insert(it, value);
			n--;
		}
		return it;
	}
	my_iterator insert(const my_iterator position, initializer_list<Type> _list)
	{
		my_iterator it = position;
		for (auto& element : _list)
		{
			it = insert(it, element);
		}
		return it;
	}
};
