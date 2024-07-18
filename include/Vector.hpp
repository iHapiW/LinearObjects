#ifndef LINEAROBJECTS_HPP
#define LINEAROBJECTS_HPP

#include <ostream>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <string>
#include <numeric>
#include <initializer_list>
#include <vector>

class Matrix;

// Note: All Objects Are Zero-Origin Based !
enum class VectorType {
    RowMatrix,
    ColumnMatrix
};

class Vector {
private:
        std::vector<double> comps{};
        std::size_t n{};
public:

    // Constructors
    Vector(std::initializer_list<double> components);
    explicit Vector(std::size_t size);
    explicit Vector(const std::vector<double>& components);


    // (Move & Copy) (Constructor & Assignment)
    Vector(const Vector& vec);
    Vector(const Vector&& vec) noexcept;
    Vector& operator=(const Vector& rhs);
    Vector& operator=(Vector&& rhs) noexcept;

    // Methods
    [[nodiscard]] std::string toString() const;
    [[nodiscard]] double magnitude() const;
    [[nodiscard]] std::size_t getDimension() const;
    [[nodiscard]] double angle(const Vector& rhs) const; // In Radians
    [[nodiscard]] Matrix getMatrix(VectorType vType) const;

    // Operators
    friend std::ostream& operator<<(std::ostream& os, const Vector& vec);    // Printing vec.toString()
    friend double operator*(const Vector& lhs, const Vector& rhs);  // Dot Product
    friend Vector operator^(const Vector& lhs, const Vector& rhs); // Cross Product
    friend Vector operator*(const Vector& vec, double coeff);   // Vector with Coefficient
    friend Vector operator*(double coeff, const Vector& vec);   // Vector with Coefficient (vec * coeff)
    friend Vector operator+(const Vector& lhs, const Vector& rhs); // Vector Addition

    // Class Operators
    Vector operator-() const;    // Vector negation ( -1 * (*this) )
    double& operator[](std::size_t n);
    const double& operator[](std::size_t n) const;

    // Destructor
    ~Vector() = default;
};

#endif // LINEAROBJECTS_HPP
