#include <iostream>
#include <string>

using namespace std;

class Matrix
{
private:
    int row;
    int col;
    int **mat;

public:
    Matrix(int row, int col){
        this->row = row;
        this->col = col;
        mat = new int*[row];
        for (int i = 0; i < row; i++)
        {
            mat[i] = new int[col];
        }
    }
    int getRow(){
        return row;
    }
    int getCol(){
        return col;
    }
    void setElement(int i, int j, int value){
        if ((i >= 0) && (i < row) && (j >= 0) && (j < col)) {
            mat[i][j] = value;
        }
    }
    
    Matrix addMatrix(Matrix& m) {
        if (m.getRow() != row || m.getCol() != col) {
            cerr << "Matrices cannot be added: Dimensions don''t match." << endl;
            exit(1);
        }
        Matrix result(row, col);
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                result.mat[i][j] = mat[i][j] + m.mat[i][j];
            }
        }
        return result;
    }

    Matrix mulMatrix(Matrix& m) {
        if (col != m.getRow()) {
            cerr << "Matrices cannot be multiplied: Invalid." << endl;
            exit(1);
        }
        Matrix result(row, m.getCol());
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < m.getCol(); j++) {
                result.mat[i][j] = 0;
                for (int k = 0; k < col; k++) {
                    result.mat[i][j] += mat[i][k] * m.mat[k][j];
                }
            }
        }
        return result;
    }
    
    void display(){
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                cout << mat[i][j] << " ";
            }
            cout << endl;
        }
    }

    ~Matrix(){
        for (int i = 0; i < row; i++) {
            delete[] mat[i];
        }
        delete[] mat;
    }
};

int main(int argc, char* argv[]) {
    if (argc < 5) {
        cerr << "Insufficient arguments" << endl;
        return 1;
    }

    int rows1 = stoi(argv[1]);
    int cols1 = stoi(argv[2]);
    int rows2 = stoi(argv[3]);
    int cols2 = stoi(argv[4]);

    int totalElements1 = rows1 * cols1;
    int totalElements2 = rows2 * cols2;
    if (argc < 5 + totalElements1 + totalElements2) {
        cerr << "Insufficient arguments: Not enough elements provided for the matrices." << endl;
        return 1;
    }

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

    cout << "Matrix 1:\n";
    m1.display();

    cout << "Matrix 2:\n";
    m2.display();

    cout << "Matrix 1 + Matrix 2:\n";
    Matrix sum = m1.addMatrix(m2);
    sum.display();

    cout << "Matrix 1 * Matrix 2:\n";
    Matrix product = m1.mulMatrix(m2);
    product.display();

    return 0;
}