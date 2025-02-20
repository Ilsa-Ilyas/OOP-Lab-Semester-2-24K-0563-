#include <iostream>
using namespace std;

class Matrix
{
    double **matrix;
    int rows;
    int columns;

public:
    Matrix()
    {
        rows = 0;
        columns = 0;
        matrix = nullptr;
    }

    Matrix(int r, int c)
    {
        rows = r;
        columns = c;
        matrix = new double *[rows];
        for (int i = 0; i < rows; i++)
        {
            matrix[i] = new double[columns];
        }

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                matrix[i][j] = 0;
            }
        }
    }

    Matrix(const Matrix &mat)
    {
        rows = mat.rows;
        columns = mat.columns;
        matrix = new double *[rows];
        for (int i = 0; i < rows; i++)
        {
            matrix[i] = new double[columns];
        }

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                matrix[i][j] = mat.matrix[i][j];
            }
        }
    }

    Matrix(Matrix &&m)
    {
        columns = m.columns;
        rows = m.rows;
        matrix = m.matrix;
        m.matrix = nullptr;
    }

    ~Matrix()
    {
        if (matrix != nullptr)
        {
            for (int i = 0; i < rows; i++)
            {
                delete[] matrix[i];
            }
            delete[] matrix;
        }
    }

    int getcolumns()
    {
        return columns;
    }

    int getrows()
    {
        return rows;
    }

    double *at(int r, int c)
    {
        return &matrix[r][c];
    }

    void fill(double value)
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                matrix[i][j] = value;
            }
        }
    }

    Matrix transpose()
    {
        Matrix t(columns, rows);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                t.matrix[j][i] = matrix[i][j];
            }
        }
        return t;
    }

    void print()
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main()
{
    Matrix m(3, 2);

    m.fill(5);

    cout << "Original Matrix:" << endl;
    m.print();

    Matrix t = m.transpose();

    cout << "Transposed Matrix:" << endl;
    t.print();

    return 0;
}