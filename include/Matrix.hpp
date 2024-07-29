#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <sstream>
#include <string>
#include <vector>
#include <ostream>

#include "Vector.hpp"

// Note: All Objects Are Zero-Origin Based !

class MatrixSize {
public:
    std::size_t rowCount{};
    std::size_t columnCount{};

    MatrixSize() = default;
    [[nodiscard]] bool validate() const;
    ~MatrixSize() = default;
};

class Matrix {
protected:
    std::vector<Vector> data{};
    MatrixSize size{};

public:
    // Constructors
    Matrix(std::size_t rowCount, std::size_t columnCount);
    explicit Matrix(MatrixSize matSize);
    Matrix(std::initializer_list<std::initializer_list<double>> matrixRows);
    explicit Matrix(const std::vector<Vector>& matrixRows);
    explicit Matrix(const std::vector<std::vector<double>>& matrixRows);

    // (Move & Copy) (Constructor & Assignment)
    Matrix(const Matrix& matrix);
    Matrix(const Matrix&& matrix) noexcept;
    Matrix& operator=(const Matrix& matrix);
    Matrix& operator=(Matrix&& matrix) noexcept;

    // Methods
    [[nodiscard]] std::string toString() const;
    virtual Matrix& transpose();
    virtual Matrix& swapRows(std::size_t idx1, std::size_t idx2);
    virtual Matrix& swapColumns(std::size_t idx1, std::size_t idx2);
    Matrix& rotate();

    // Getters
    [[nodiscard]] Vector getRow(std::size_t idx) const;
    [[nodiscard]] Vector getColumn(std::size_t idx) const;
    [[nodiscard]] Vector getSubRow(std::size_t idx, std::size_t columnStart, std::size_t columnEnd) const;
    [[nodiscard]] Vector getSubColumn(std::size_t idx, std::size_t rowStart, std::size_t rowEnd) const;
    [[nodiscard]] Matrix getSubMatrix(std::size_t rowStart, std::size_t rowEnd,
                                      std::size_t columnStart, std::size_t columnEnd) const;
    [[nodiscard]] const MatrixSize& getDimension() const;

    // Setters
    virtual Matrix& setRow(std::size_t idx, const Vector& row);
    virtual Matrix& setColumn(std::size_t idx, const Vector& column);
    virtual Matrix& setSubRow(std::size_t idx, std::size_t columnStart, const Vector &subRow);
    virtual Matrix& setSubColumn(std::size_t idx, std::size_t rowStart, const Vector &subColumn);
    Matrix& setSubMatrix(std::size_t rowStart, std::size_t columnStart, const Matrix& matrix);

    // Friend Operators
    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
    friend Matrix operator*(const Matrix& lhs, const Matrix& rhs);
    friend Matrix operator*(const Matrix& lhs, double coeff);
    friend Matrix operator*(double coeff, const Matrix& lhs);
    friend Matrix operator+(const Matrix& lhs, const Matrix& rhs);

    // Class Operators
    Vector& operator[]( std::size_t idx );
    const Vector& operator[]( std::size_t idx) const;

    // Destructor
    virtual ~Matrix() = default;
};

#endif //MATRIX_HPP
