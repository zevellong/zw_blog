#include <asm-generic/errno.h>
#include <iostream>
#include <string>
#include <vector>

using std::vector;
using std::cout;
using std::endl;
using std::string;

template<typename T>
class Iterator
{
public:
	Iterator<T>(T* p) : ptr(p) {  }
	virtual Iterator& operator++() = 0;
	virtual Iterator& operator--() = 0;
	virtual T& operator*() = 0;
	virtual Iterator& operator++(int) = 0;
	virtual Iterator& operator--(int) = 0;
	bool operator==(const Iterator<T>& rhs) const
	{
		return ptr == rhs.ptr;
	}
	 bool operator!=(const Iterator<T>& rhs) const
	{
		return !(*this == rhs);
	}	
protected:
	T* ptr;
};
class xx : public Iterator<int>
{
public:
	xx& operator++()
	{
		ptr++;
		return *this;
	}
};
class Department
{
public:
	Department() = default;
	Department(string nm, string ds) : name(nm),desc(ds) {  }
	void print()
	{
		cout << name << ": " << desc << endl;
	}
private:
	string name, desc;
};
class College
{
public:
	virtual Iterator<Department>* makeIter() = 0; 	
	virtual Iterator<Department>* begin() = 0;
	virtual Iterator<Department>* end() = 0;
	void print()
	{
		cout << name << ": " << desc << endl;
	}
protected:
	string name, desc;
};

class compCollege : public College
{
public:
	virtual Iterator<Department>* makeIter() override
	{
		return new Iter(dArray, 0);
	}
	compCollege()
	{
		name = "computer language";
		desc = "all 5 catalogy";
		setDepart(0, "C language", "fast and simple");
		setDepart(1, "Java language", "good");
		setDepart(2, "Python", "convienent");
		setDepart(3, "ruby", "good script");
		setDepart(4, "lua", "nice script");
	}
	void setDepart(int i, string name, string desc)
	{
		dArray[i] = Department(name, desc);

	}
	virtual Iterator<Department>* begin() override
	{
		return new Iter(dArray, 0);
	}
	virtual Iterator<Department>* end() override
	{
		return new Iter(dArray, 5);
	}
private:
Department dArray[6];

public:
class Iter : public Iterator<Department>
{
public:
	Iter(Department* p, int po) : Iterator(p + po), pos(po){}
	virtual Iter& operator++() override
	{
		check(pos, sta, cur - 1);
		Iterator<Department>::ptr++;
		pos++;
		return *this;
	}
	virtual Iter& operator--() override
	{
		check(pos, sta + 1, cur);
		Iterator<Department>::ptr--;
		pos--;
		return *this;
	}
	virtual Iter& operator++(int) override
	{
		auto ret = this;
		++*this;
		return *ret;
	}
	virtual Iter& operator--(int) override
	{
		auto ret = this;
		--*this;
		return *ret;
	}

	virtual Department& operator*() override
	{
		check(pos, sta, cur);
		return *Iterator<Department>::ptr;	
	}	
private:
	int pos=0, sta=0, cur=5;
	void check(int p, int s, int c)
	{
		if (p < s || p > c)
			throw std::out_of_range("compCollege::Iter: out_of_range");
	}
};
};
class output
{
public:
	void addCol(College* c)
	{
		col.push_back(c);
	}
	void print()
	{
		for (auto x : col)
		{
			x->print();
			for (auto y = x->begin(); *y!=*x->end();(*y)++)
			{
	//			(*y)++;
				(**y).print();	
			}
		}
	}
private:
vector<College*> col;
};
int main(int argc, char* argv[])
{
	compCollege cc;
	output o;
	o.addCol(&cc);
	o.print();		
	return 0;
}
