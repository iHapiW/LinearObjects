#ifndef SQUAREMATRIX_HPP
#define SQUAREMATRIX_HPP

#include <initializer_list>
#include <vector>

#include "Matrix.hpp"

class SquareMatrix: public Matrix {
public:
    // Constructors
    explicit SquareMatrix(std::size_t n);
    SquareMatrix(std::initializer_list<std::initializer_list<double>> matrixRows);
    explicit SquareMatrix(const std::vector<Vector>& matrixRows);
    explicit SquareMatrix(const std::vector<std::vector<double>>& matrixRows);
    explicit SquareMatrix(const Matrix& matrix);

    // (Move & Copy) (Constructor & Assignment)
    SquareMatrix(const SquareMatrix& matrix);
    SquareMatrix(const SquareMatrix&& matrix) noexcept;
    SquareMatrix& operator=(const SquareMatrix& matrix);
    SquareMatrix& operator=(SquareMatrix&& matrix) noexcept;

    // Friend Operators
    friend SquareMatrix operator*(const SquareMatrix& lhs, const SquareMatrix& rhs);
    friend SquareMatrix operator^(const SquareMatrix& matrix, std::size_t power);
};

#endif //SQUAREMATRIX_HPP
