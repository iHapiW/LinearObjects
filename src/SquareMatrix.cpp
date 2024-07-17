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

