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
		assert(lhs.size() == rhs.size());
		int size = lhs.size();

		if (lhs.size() == 1) {
			auto ret = lhs.at(0, 0) * rhs.at(0, 0);
			Matrix m(1);
			m.at(0, 0) = ret;
			return m;
		}

		Matrix a11(&lhs, 0, 0, size/2);
		Matrix a12(&lhs, 0, size / 2, size/2);
		Matrix a21(&lhs, size / 2, 0, size/2);
		Matrix a22(&lhs, size / 2, size / 2, size/2);

		Matrix b11(&rhs, 0, 0, size/2);
		Matrix b12(&rhs, 0, size / 2, size/2);
		Matrix b21(&rhs, size / 2, 0, size/2);
		Matrix b22(&rhs, size / 2, size / 2, size/2);

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
	explicit Matrix(int size) {
		size_ = size;
		numbers_ = new int[size * size];
		self_ = true;
	}
	Matrix(const Matrix* m, int row, int col, int size) {
		self_ = false;
		parentMatrix_ = m;
		baseRow_ = row;
		baseCol_ = col;
		size_ = size;
	}
	Matrix(const Matrix& a11, const Matrix& a12, const Matrix& a21, const Matrix& a22) {
		assert(a11.self_ && a12.self_ && a21.self_ && a22.self_);
		size_ = a11.size() * 2;
		numbers_ = new int[size_ * size_];
		self_ = true;
		copy(a11, 0, 0);
		copy(a12, 0, a11.size());
		copy(a21, a11.size(), 0);
		copy(a22, a11.size(), a11.size());
	}
	void copy(const Matrix& subM, int baseRow, int baseCol) {
		for (int i = 0; i < subM.size(); ++i) {
			for (int j = 0; j < subM.size(); ++j) {
				at(i + baseRow, j + baseCol) = subM.at(i, j);
			}
		}
	}
	Matrix(const Matrix& m) {
		assert(m.self_);
		size_ = m.size_;
		numbers_ = new int[size_ * size_];
		memcpy(numbers_, m.numbers_, sizeof(int) * size_ * size_);
		self_ = true;
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
		if (self_)
			return numbers_[x * size_ + y];
		else {
			return parentMatrix_->at(baseRow_ + x, baseCol_ + y);
		}
	}
	int size() const {
		return size_;
	}
	void output() {
		for (int i = 0; i < size_; ++i) {
			for (int j = 0; j < size_; ++j) {
				std::cout << at(i, j)<< "\t";
			}
			std::cout << "\n";
		}
	}
private:
	const Matrix* parentMatrix_;
	int baseRow_;
	int baseCol_;
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
