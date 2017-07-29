#include "TestLibrary.h"


class BinaryTree: public CompositeTest
{
	int depth_;
	int current_depth_;
public:
	BinaryTree(int _depth) : depth_(_depth), current_depth_(_depth) { this->Generate(); }
	void E()
	{
		ConstPrimitiveTest<char>* left_bracket = new ConstPrimitiveTest<char>('(');
		ConstPrimitiveTest<char>* right_bracket = new ConstPrimitiveTest<char>(')');
		if (current_depth_ == 0)
		{
			this->Add(left_bracket);
			this->Add(right_bracket);
			return;
		}
		current_depth_--;
		int rng = rand() % 4;
		ConstPrimitiveTest<char>* semicolon = new ConstPrimitiveTest<char>(';');
		
		this->Add(left_bracket);
		this->Add(CreateNumber(1, 100));
		this->Add(semicolon);
		if (rng & 2)
		{
			E();
		}
		else
		{
			this->Add(left_bracket);
			this->Add(right_bracket);
		}
		this->Add(semicolon);
		if (rng & 1)
		{
			E();
		}
		else
		{
			this->Add(left_bracket);
			this->Add(right_bracket);
		}
		this->Add(right_bracket);
	}
	void Generate()
	{
		current_depth_ = depth_;
		this->Clear();
		E();
	}

};

void main(){
	try
	{
		Grammar* grammar = new Grammar("({1 , 2 , 3}, {a,b,c}, P, 1)", "${ 1 }->${2}${ 3 }\n${ 2 }->a${2}\n${ 2 }->${3}\n${ 3 }->${3}b\n${ 3 }->e" );
		
		while (1)
		{
			system("cls");
			grammar->Generate();
			grammar->Print();
			std::cout << std::endl;
			system("pause");
		}
		/*BinaryTree* bt = new BinaryTree(1000);
		int n = 10000;
		while (n--)
		{
			system("cls");
			bt->Generate();
			bt->Print();
			std::cout << std::endl;
			system("pause");
		}*/

		
	}
	catch ( std::runtime_error _err )
	{
		std::cout << _err.what() << std::endl;
	}
}