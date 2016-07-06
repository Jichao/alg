//implmentation of matrix multiplication
#include <iostream>
#include <vector>
#include <assert.h>

class Matrix {
	friend Matrix operator+(const Matrix& lhs, const Matrix& rhs) 
	{
		Matrix result(lhs.size());
		for (int i = 0; i < lhs.size(); ++i) {
			for (int j = 0; j < lhs.size(); ++j) {
				result.at(i, j) = lhs.at(i, j) + rhs.at(i, j);
			}
		}
		return result;
	}

	friend Matrix operator-(const Matrix& lhs, const Matrix& rhs) 
	{
		Matrix result(lhs.size());
		for (int i = 0; i < lhs.size(); ++i) {
			for (int j = 0; j < lhs.size(); ++j) {
				result.at(i, j) = lhs.at(i, j) - rhs.at(i, j);
			}
		}
		return result;
	}

	friend Matrix operator*(const Matrix& lhs, const Matrix& rhs)
	{
		Matrix a11(lhs, 0, 0, lhs.size());
		Matrix a12(lhs, 0, lhs.size() / 2, lhs.size());
		Matrix a21(lhs, lhs.size() / 2, 0, lhs.size());
		Matrix a22(lhs, lhs.size() / 2, lhs.size() / 2, lhs.size());

		Matrix b11(rhs, 0, 0, lhs.size());
		Matrix b12(rhs, 0, rhs.size() / 2, lhs.size());
		Matrix b21(rhs, rhs.size() / 2, 0, lhs.size());
		Matrix b22(rhs, rhs.size() / 2, rhs.size() / 2, lhs.size());

		Matrix s1 = b12 - b22;
		Matrix s2 = a11 + a12;
		Matrix s3 = a21 + a22;
		Matrix s4 = b21 - b11;
		Matrix s5 = a11 + a22;
		Matrix s6 = b11 + b22;
		Matrix s7 = a12 - a22;
		Matrix s8 = b21 + b22;
		Matrix s9 = a11 - a21;
		Matrix s10 = b11 + b12;

		auto p1 = a11 * s1;
		auto p2 = s2 * b22;
		auto p3 = s3 * b11;
		auto p4 = a22 * s4;
		auto p5 = s5 * s6;
		auto p6 = s7 * s8;
		auto p7 = s9 * s10;

		auto c11 = p5 + p4 - p2 + p6;
		auto c12 = p1 + p2;
		auto c21 = p3 + p4;
		auto c22 = p5 + p1 - p3 - p7;
		return Matrix(c11, c12, c21, c22);
	}

	public:
	Matrix(int size) {
		size_ = size;
		numbers_ = new int[size * size];
		self_ = true;
	}
	Matrix(Matrix& m, int row, int col, int size) {
		self_ = false;
		numbers_ = m.numbers_ + row * m.size_ + col;
		size_ = size;
	}
	Matrix(const Matrix& a11, const Matrix& a12, const Matrix& a21, const Matrix& a22) {
		size_ = a11.size() * 2;
		numbers_ = new int[size_ * size_];
		self_ = true;
		auto msize = (a11.size_ * a11.size_);
		memcpy(numbers_, a11.numbers_, msize * sizeof(int));
		memcpy(numbers_ + msize, a12.numbers_, msize * sizeof(int));
		memcpy(numbers_ + msize * 2, a21.numbers_, msize * sizeof(int));
		memcpy(numbers_ + msize * 3, a22.numbers_, msize * sizeof(int));
	}
	Matrix() {
		size_ = 0;
		numbers_ = nullptr;
		self_ = true;
	}
	void get(int size) {
		size_ = size;
		numbers_ = new int[size * size];
		self_ = true;
		for (int i = 0; i < size * size; ++i) {
			std::cin >> numbers_[i];
		}
	}
	~Matrix() {
		if (self_) {
			delete[] numbers_;
		}
	}
	int& at(int x, int y) const {
		return numbers_[x * size_ + y];
	}
	int size() const {
		return size_;
	}
	void output() {
		for (int i = 0; i < size_ * size_; ++i) {
			std::cout << numbers_[i] << "\t";
			if (i % size_ == size_ - 1) {
				std::cout << "\n";
			}
		}
	}
	private:
	int* numbers_;
	int size_;
	bool self_;
};

int main()
{
	int size;
	std::cin >> size;
	Matrix a;
	Matrix b;
	a.get(size);
	b.get(size);
	Matrix c = a * b;
	c.output();
	return 0;
}


