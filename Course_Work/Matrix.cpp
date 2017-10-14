#include "Matrix.h"

Matrix::Matrix(PrimitiveTest<int>* _n, PrimitiveTest<int>* _m, std::function<Test*()> _generation_function, std::string _delimiter, std::string _line_breaker)
	: n_(_n)
	, m_(_m)
	, generation_function_(_generation_function)
	, example_(NULL)
	, delimiter_(_delimiter)
	, line_breaker_(_line_breaker)
	, print_size_(true)
	, print_size_as_square_(false)
{
}

Matrix::Matrix(PrimitiveTest<int>* _n, PrimitiveTest<int>* _m, Test * _example, std::string _delimiter, std::string _line_breaker)
	: n_(_n)
	, m_(_m)
	, generation_function_(NULL)
	, example_(_example)
	, delimiter_(_delimiter)
	, line_breaker_(_line_breaker)
	, print_size_(true)
	, print_size_as_square_(false)
{
}

Matrix::Matrix(PrimitiveTest<int>* _n, std::function<Test*()> _generation_function, std::string _delimiter, std::string _line_breaker)
	: n_(_n)
	, m_(_n)
	, generation_function_(_generation_function)
	, example_(NULL)
	, delimiter_(_delimiter)
	, line_breaker_(_line_breaker)
	, print_size_(true)
	, print_size_as_square_(true)
{
}

Matrix::Matrix(PrimitiveTest<int>* _n, Test * _example, std::string _delimiter, std::string _line_breaker)
	: n_(_n)
	, m_(_n)
	, generation_function_(NULL)
	, example_(_example)
	, delimiter_(_delimiter)
	, line_breaker_(_line_breaker)
	, print_size_(true)
	, print_size_as_square_(true)
{
}

void Matrix::Generate()
{
	test_generated_ = true;
	n_->Generate();
	m_->Generate();
	for (int i = 0; i < matrix_.size(); i++)
	{
		for (int j = 0; j < matrix_[i].size(); j++)
		{
			delete matrix_[i][j];
		}
	}
	int n = n_->Get();
	int m = m_->Get();
	if (n <= 0 && m <= 0)
	{
		throw std::runtime_error("Matrix size must be strongly positive");
	}
	matrix_.resize(n);
	for (int i = 0; i < matrix_.size(); i++)
	{
		matrix_[i].resize(m);
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (example_ != NULL)
			{
				matrix_[i][j] = example_->Clone();
			}
			if (generation_function_)
			{
				matrix_[i][j] = generation_function_();
			}
			if (matrix_[i][j] == NULL)
			{
				throw std::runtime_error("Array element is not assigned. In function Array::Generate()");
			}
			matrix_[i][j]->Generate();
		}
	}
}

void Matrix::Print(std::ostream & _out) const
{
	if (!test_generated_)
	{
		throw std::runtime_error("Print() must be called after Generate() in Array.");
	}
	int n = n_->Get();
	int m = m_->Get();
	if (print_size_)
	{
		_out << n;
		if (!print_size_as_square_)
		{
			_out << delimiter_ << m;
		}
		_out << line_breaker_;
	}
	for (unsigned int i = 0; i < matrix_.size(); i++)
	{
		for (unsigned int j = 0; j < matrix_[i].size(); j++)
		{
			matrix_[i][j]->Print(_out);
			if (j != matrix_[i].size() - 1)
				_out << delimiter_;
		}
		_out << line_breaker_;
	}
}

void Matrix::PrintSize(bool _print_size)
{
	print_size_ = _print_size;
}

std::pair<int, int> Matrix::Size()
{
	return std::make_pair(n_->Get(), m_->Get());
}

Matrix * Matrix::Clone() const
{
	Matrix* matrix;
	if (example_ == NULL)
	{
		if (m_)
		{
			matrix = new Matrix(n_, m_, generation_function_, delimiter_, line_breaker_);
		}
		else
		{
			matrix = new Matrix(n_, generation_function_, delimiter_, line_breaker_);
		}
	}
	else
	{
		if(m_)
		{
			matrix = new Matrix(n_, m_, example_, delimiter_, line_breaker_);
		}
		else
		{
			matrix = new Matrix(n_, example_, delimiter_, line_breaker_);
		}
	}
	matrix->print_size_ = print_size_;
	matrix->print_size_as_square_ = print_size_as_square_;
	return matrix;
}

Matrix::~Matrix()
{
	for (unsigned int i = 0; i < matrix_.size(); i++)
	{
		for (unsigned int j = 0; j < matrix_[i].size(); j++)
		{
			delete matrix_[i][j];
		}
	}
}

std::vector<Test*> Matrix::operator[](int i)
{
	return matrix_[i];
}
