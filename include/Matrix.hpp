#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <sstream>
#include <string>
#include <vector>
#include <ostream>

#include "Vector.hpp"

class Matrix {
protected:
    std::vector<Vector> rows{};
    std::size_t n{};
    std::size_t m{};

public:
    // Constructors
    Matrix(std::size_t rowCount, std::size_t columnCount);
    Matrix(std::initializer_list<std::initializer_list<double>> matrixRows);
    explicit Matrix(const std::vector<Vector>& matrixRows);
    explicit Matrix(const std::vector<std::vector<double>>& matrixRows);

    // Methods
    [[nodiscard]] std::string toString() const;

    // Getters
    [[nodiscard]] Vector getRow(std::size_t idx) const;
    [[nodiscard]] Vector getColumn(std::size_t idx) const;
    [[nodiscard]] Vector getSubRow(std::size_t idx, std::size_t columnStart, std::size_t columnEnd) const;
    [[nodiscard]] Vector getSubColumn(std::size_t idx, std::size_t rowStart, std::size_t rowEnd) const;
    [[nodiscard]] Matrix getSubMatrix(std::size_t rowStart, std::size_t rowEnd,
                                      std::size_t columnStart, std::size_t columnEnd) const;

    // Setters
    void setRow(std::size_t idx, const Vector& row);
    void setColumn(std::size_t idx, const Vector& column);
    void setSubRow(std::size_t idx, std::size_t columnStart, const Vector &subRow);
    void setSubColumn(std::size_t idx, std::size_t rowStart, const Vector &subColumn);
    void setSubMatrix(std::size_t rowStart, std::size_t columnStart, const Matrix& matrix);

    // Friend Operators
    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);

    // Class Operators
    Vector& operator[]( std::size_t idx );
    const Vector& operator[]( std::size_t idx) const;
};

#endif //MATRIX_HPP
