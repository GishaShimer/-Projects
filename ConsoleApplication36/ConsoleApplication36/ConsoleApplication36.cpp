#include <iostream>
using namespace std;


class Singleton
{
private:
	static Singleton* _instance;
	int d;
protected:

	Singleton()
	{
		d = 0;
	}
public:
	static Singleton* Instance()
	{
		if (_instance == nullptr)
		{
			_instance = new Singleton();
			return _instance;
		}
		else
		{
			return nullptr;
		}
	}
	int Get() { return d; }
	void Set(int _d) { d = _d; }

	void Print()
	{
		cout << "d = " << d << "\n";
	}
	~Singleton()
	{
		if (_instance)
			delete _instance;
	}
};

Singleton* Singleton::_instance = nullptr;
int main()
{
  	Singleton* obj1 = Singleton::Instance();

	if (obj1 != nullptr)
	{
		obj1->Set(250);
		obj1->Print();
	}

	Singleton* obj2 = Singleton::Instance();

	if (obj2 != nullptr)
	{
		obj2->Set(300);
		obj2->Print();
	}
	else
	{
		cout << "obj2 == nullptr\n";
	}
}
