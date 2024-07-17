#include "SquareMatrix.hpp"

// Constructors

SquareMatrix::SquareMatrix(std::size_t n): Matrix(n, n) {

}

SquareMatrix::SquareMatrix(std::initializer_list<std::initializer_list<double>> matrixRows) : Matrix(matrixRows) {
    if(m != n)
        throw std::invalid_argument("This is not Square Matrix!");
}

SquareMatrix::SquareMatrix(const std::vector<Vector> &matrixRows) : Matrix(matrixRows) {
    if(m != n)
        throw std::invalid_argument("This is not Square Matrix!");
}

SquareMatrix::SquareMatrix(const std::vector<std::vector<double>> &matrixRows) : Matrix(matrixRows) {
    if(m != n)
        throw std::invalid_argument("This is not Square Matrix!");
}

SquareMatrix::SquareMatrix(const SquareMatrix &matrix) : Matrix(matrix.rows) {
}

SquareMatrix::SquareMatrix(const SquareMatrix &&matrix) noexcept : Matrix(matrix.rows){

}

SquareMatrix::SquareMatrix(const Matrix& matrix) : Matrix(matrix) {
    if(n != m)
        throw std::invalid_argument("This is not Square Matrix!");
}

SquareMatrix &SquareMatrix::operator=(const SquareMatrix &matrix) {
    n = matrix.n;
    rows = matrix.rows;
    return *this;
}

SquareMatrix &SquareMatrix::operator=(SquareMatrix &&matrix) noexcept {
    n = matrix.n;
    rows = matrix.rows;
    return *this;
}

// Methods

SquareMatrix& SquareMatrix::transpose() {
    for(std::size_t i = 0; i < n; i++)
        for(std::size_t j = 0; j < m; j++)
            std::swap(rows[i][j], rows[j][i]);

    return *this;
}

SquareMatrix& SquareMatrix::swapRows(std::size_t idx1, std::size_t idx2) {
    Matrix::swapRows(idx1, idx2);
    return *this;
}

SquareMatrix& SquareMatrix::swapColumns(std::size_t idx1, std::size_t idx2) {
    Matrix::swapColumns(idx1, idx2);
    return *this;
}

// Setters

SquareMatrix& SquareMatrix::setRow(std::size_t idx, const Vector &row) {
    Matrix::setRow(idx, row);
    return *this;
}

SquareMatrix &SquareMatrix::setColumn(std::size_t idx, const Vector &column) {
    Matrix::setColumn(idx, column);
    return *this;
}

SquareMatrix &SquareMatrix::setSubRow(std::size_t idx, std::size_t columnStart, const Vector &subRow) {
    Matrix::setSubRow(idx, columnStart, subRow);
    return *this;
}

SquareMatrix &SquareMatrix::setSubColumn(std::size_t idx, std::size_t rowStart, const Vector &subColumn) {
    Matrix::setSubColumn(idx, rowStart, subColumn);
    return *this;
}

// Friend Operators

SquareMatrix operator*(const SquareMatrix &lhs, const SquareMatrix &rhs) {
    SquareMatrix result( static_cast<Matrix>(lhs) * static_cast<Matrix>(rhs) ); // Avoiding Recursion!
    return result;
}

SquareMatrix operator^(const SquareMatrix &matrix, std::size_t power) {
    if( power == 0 ) {
        SquareMatrix result(matrix.n);
        for(std::size_t i = 0; i < result.n; i++)
            result[i][i] = 1;
        return result;
    } else {
        SquareMatrix result(matrix);
        for(std::size_t i = 1; i < power; i++)
            result = result * matrix;
        return result;
    }

}

SquareMatrix operator*(const SquareMatrix &lhs, double coeff) {
    return SquareMatrix(coeff * static_cast<const Matrix&>(lhs));
}

SquareMatrix operator*(double coeff, const SquareMatrix &lhs) {
    return SquareMatrix(coeff * static_cast<const Matrix&>(lhs));
}

SquareMatrix operator+(const SquareMatrix &lhs, const SquareMatrix &rhs) {
    return SquareMatrix(static_cast<const Matrix&>(lhs) + static_cast<const Matrix&>(rhs));
}

