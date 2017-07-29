#include "TestLibrary.h"


class BinaryTree : public CompositeTest
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

void main() {
	try
	{
		/*	Grammar* grammar = new Grammar("({1,2}, {a,b,c}, P, 1)", "${1} -> a${1}a\n${1} -> b${1}b\n${1} -> c${1}c\n${1} -> e\n" );

			while (1)
			{
				system("cls");
				grammar->Generate();
				grammar->Print();
				std::cout << std::endl;
				system("pause");
			}*/

		BinaryTree* bt = new BinaryTree(1000);
		int n = 10000;
		while (n--)
		{
			system("cls");
			bt->Generate();
			bt->Print();
			std::cout << std::endl;
			system("pause");
		}


	}
	catch (std::runtime_error _err)
	{
		std::cout << _err.what() << std::endl;
	}
}