#include <iostream>
#include <cstdlib>
using namespace std;

class Matrix {
private:
    int rows, cols;
    int **mat;

public:
    Matrix(int rows, int cols) {
        this->rows = rows;
        this->cols = cols;
        mat = new int *[rows];
        for (int i = 0; i < rows; i++) {
            mat[i] = new int[cols](); 
        }
    }

    int getRows() const {
        return rows;
    }

    int getCols() const {
        return cols;
    }

    void setElement(int i, int j, int value) {
        if (i >= 0 && i < rows && j >= 0 && j < cols) {
            mat[i][j] = value;
        }
    }

    void display() const {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << mat[i][j] << " ";
            }
            cout << endl;
        }
    }

    Matrix add(const Matrix &other) const {
        if (rows != other.getRows() || cols != other.getCols()) {
            cout << "Matrices cannot be added due to different dimensions." << endl;
            return Matrix(0, 0);
        }

        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.setElement(i, j, mat[i][j] + other.mat[i][j]);
            }
        }
        return result;
    }

    Matrix multiply(const Matrix &other) const {
        if (cols != other.getRows()) {
            cout << "Matrices cannot be multiplied due to incompatible dimensions." << endl;
            return Matrix(0, 0); 
        }

        Matrix result(rows, other.getCols());
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < other.getCols(); j++) {
                int sum = 0;
                for (int k = 0; k < cols; k++) {
                    sum += mat[i][k] * other.mat[k][j];
                }
                result.setElement(i, j, sum);
            }
        }
        return result;
    }

    ~Matrix() {
        for (int i = 0; i < rows; i++) {
            delete[] mat[i];
        }
        delete[] mat;
    }
};

bool validateArguments(int argc, char *argv[]) {
    if (argc < 5) {
        cout << "Usage: program <rows1> <cols1> <rows2> <cols2> <matrix1_elements> <matrix2_elements>" << endl;
        return false;
    }
    return true;
}

int main(int argc, char *argv[]) {
    if (!validateArguments(argc, argv)) {
        return 1; 
    }

    int rows1 = stoi(argv[1]);
    int cols1 = stoi(argv[2]);
    int rows2 = stoi(argv[3]);
    int cols2 = stoi(argv[4]);

    Matrix m1(rows1, cols1);
    Matrix m2(rows2, cols2);

    int index = 5;
    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols1; j++) {
            m1.setElement(i, j, stoi(argv[index++]));
        }
    }

    for (int i = 0; i < rows2; i++) {
        for (int j = 0; j < cols2; j++) {
            m2.setElement(i, j, stoi(argv[index++]));
        }
    }

    cout << "Matrix 1 (" << rows1 << "x" << cols1 << "):\n";
    m1.display();

    cout << "Matrix 2 (" << rows2 << "x" << cols2 << "):\n";
    m2.display();

    cout << "\nMatrix 1 + Matrix 2:\n";
    Matrix resultAdd = m1.add(m2);
    if (resultAdd.getRows() > 0 && resultAdd.getCols() > 0) {
        resultAdd.display();
    }

    cout << "\nMatrix 1 * Matrix 2:\n";
    Matrix resultMul = m1.multiply(m2);
    if (resultMul.getRows() > 0 && resultMul.getCols() > 0) {
        resultMul.display();
    }

    return 0;
}
