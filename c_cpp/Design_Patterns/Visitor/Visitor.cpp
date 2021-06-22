#include <iostream>
#include <string>
#include <system_error>
using std::cout;
using std::endl;
using std::string;

class Action;
class Person
{
public:
	virtual void accpet(Action* pact) = 0;
private:
	
};
class Man : public Person
{
public:
	virtual void accpet(Action *pact) override;
private:
	
};
class Woman : public Person
{
public:
	virtual void accpet(Action *pact) override;
private:
	
};


class Action
{
public:
	virtual void getManAcion(Man* p) {}
	virtual void getWomanAction(Woman* p) {}
private:
	
};
class Success : public Action
{
public:
	virtual void getManAcion(Man* p)
	{
		cout << "Man give Success" <<endl;
	}	
	virtual void getWomanAction(Woman* p)
	{
		cout << "Woman give Success" <<endl;
	}	
};
class Fail : public Action
{
public:
	virtual void getManAcion(Man* p)
	{
		cout << "Man give Fail" <<endl;
	}	
	virtual void getWomanAction(Woman* p)
	{
		cout << "Woman give Fail" <<endl;
	}	
};

void Man::accpet(Action *pact)
{
	pact->getManAcion(this);
}
void Woman::accpet(Action *pact)
{
	pact->getWomanAction(this);
}
const int MAX_PER_NM = 10;
class ObjStructure
{
public:
	void addPerson(Person *p)
	{
		if (perNm < 10)
		{
			persons[perNm++] = p;	
		}
	}
	void display(Action* pact)
	{
		for (int i = 0; i < perNm; i++)
		{
			persons[i]->accpet(pact);
		}
	}
	void distplay(std::initializer_list<Action*> lst)
	{
		int i = 0;
		for (auto x=lst.begin(); i<perNm && x!=lst.end();x++, i++)
			persons[i]->accpet(*x);
	}
private:
	Person *persons[MAX_PER_NM];
	int perNm = 0;
};

int main(int argc, char* argv[])
{
	Man p1;
	Woman p2;
	ObjStructure objs;
	objs.addPerson(&p1);
	objs.addPerson(&p2);
	Success su;
	Fail fa;

	objs.display(&su);

	objs.display(&fa);	

	cout << "----use list-----"<<endl;
	objs.distplay({&su, &fa, &fa});
	return 0;
}
