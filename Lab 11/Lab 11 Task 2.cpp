#include <iostream>
#include <vector>

class DimensionMismatchException {
public:
    const char* what() const noexcept {
        return "DimensionMismatchException: Matrix dimensions are incompatible.";
    }
};

class IndexOutOfBoundsException {
public:
    const char* what() const noexcept {
        return "IndexOutOfBoundsException: Matrix index is out of bounds.";
    }
};

template<typename T>
class Matrix {
private:
    std::vector<std::vector<T>> data;
    int rows, cols;

public:
    Matrix(int r, int c) : rows(r), cols(c) {
        data.resize(r, std::vector<T>(c));
    }

    int getRows() const { return rows; }
    int getCols() const { return cols; }

    T& at(int i, int j) {
        if (i < 0 || i >= rows || j < 0 || j >= cols)
            throw IndexOutOfBoundsException();
        return data[i][j];
    }

    const T& at(int i, int j) const {
        if (i < 0 || i >= rows || j < 0 || j >= cols)
            throw IndexOutOfBoundsException();
        return data[i][j];
    }

    Matrix<T> operator+(const Matrix<T>& other) const {
        if (rows != other.rows || cols != other.cols)
            throw DimensionMismatchException();

        Matrix<T> result(rows, cols);
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                result.data[i][j] = data[i][j] + other.data[i][j];
        return result;
    }

    Matrix<T> operator*(const Matrix<T>& other) const {
        if (cols != other.rows)
            throw DimensionMismatchException();

        Matrix<T> result(rows, other.cols);
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < other.cols; ++j)
                for (int k = 0; k < cols; ++k)
                    result.data[i][j] += data[i][k] * other.data[k][j];
        return result;
    }

    void print() const {
        for (const auto& row : data) {
            for (const auto& val : row)
                std::cout << val << " ";
            std::cout << "\n";
        }
    }
};
