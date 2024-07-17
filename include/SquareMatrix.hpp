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

    // Methods
    SquareMatrix& transpose() override;
    SquareMatrix& swapRows(std::size_t idx1, std::size_t idx2) override;
    SquareMatrix& swapColumns(std::size_t idx1, std::size_t idx2) override;

    // Setters
    SquareMatrix& setRow(std::size_t idx, const Vector& row) override;
    SquareMatrix& setColumn(std::size_t idx, const Vector& column) override;
    SquareMatrix& setSubRow(std::size_t idx, std::size_t columnStart, const Vector &subRow) override;
    SquareMatrix& setSubColumn(std::size_t idx, std::size_t rowStart, const Vector &subColumn) override;

    // Friend Operators
    friend SquareMatrix operator*(const SquareMatrix& lhs, const SquareMatrix& rhs);
    friend SquareMatrix operator^(const SquareMatrix& matrix, std::size_t power);
    friend SquareMatrix operator*(const SquareMatrix& lhs, double coeff);
    friend SquareMatrix operator*(double coeff, const SquareMatrix& lhs);
    friend SquareMatrix operator+(const SquareMatrix& lhs, const SquareMatrix& rhs);

    // Destructor
    ~SquareMatrix() override = default;
};

#endif //SQUAREMATRIX_HPP
