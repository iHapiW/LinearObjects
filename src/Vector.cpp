#include "Vector.hpp"

// Constructors

Vector::Vector(std::size_t size) {
    n = size;
    comps.resize(n);
}

Vector::Vector(std::initializer_list<double> components) {
    n = components.size();
    for(auto i: components)
        comps.push_back(i);
}

Vector::Vector(const std::vector<double>& components) {
    n = components.size();
    for(auto i: components)
        comps.push_back(i);
}

Vector::Vector(const Vector& vec) {
    n = vec.n;
    comps = vec.comps;
}

Vector::Vector(const Vector&& vec)  noexcept {
    n = vec.n;
    comps = vec.comps;
}

Vector& Vector::operator=(const Vector& rhs) {
    n = rhs.n;
    comps = rhs.comps;
    return *this;
}

Vector& Vector::operator=(Vector&& rhs) noexcept {
    n = rhs.n;
    comps = rhs.comps;
    return *this;
}

// Methods

std::string Vector::toString() const {
    std::ostringstream result{};
    result << *this;
    return result.str();
}

double Vector::magnitude() const {
    return sqrt((*this) * (*this));
}

std::size_t Vector::getDimension() const {
    return n;
}

double Vector::angle(const Vector &rhs) const{
    double dotProduct = (*this) * rhs;
    double magnitudes = this->magnitude() * rhs.magnitude();
    return acos(dotProduct/magnitudes);
}

// Operators

std::ostream& operator<<(std::ostream& os, const Vector& vec) {
    os << "( ";
    for(std::size_t i = 0; i < vec.n; i++) {
        os << vec.comps.at(i);
        if(i != vec.n-1)
            os << ", ";
    }
    os << " )";
    return os;
}

// Dot Product
double operator*(const Vector& lhs, const Vector& rhs) {
    if(lhs.n != rhs.n)
        throw std::invalid_argument("Dot product is defined only for two same dimensional vectors!");

    return std::inner_product(lhs.comps.begin(), lhs.comps.end(), rhs.comps.begin(), 0.0);
}

// Cross Product
Vector operator^(const Vector& lhs, const Vector& rhs) {
    if( lhs.n != 3 || rhs.n != 3)
        throw std::invalid_argument("Cross Product is only defined for two 3 dimensional vectors!");

    Vector result = {
            lhs.comps.at(1) * rhs.comps.at(2) - rhs.comps.at(1) * lhs.comps.at(2),
            rhs.comps.at(0) * lhs.comps.at(2) - lhs.comps.at(0) * rhs.comps.at(2),
            lhs.comps.at(0) * rhs.comps.at(1) - rhs.comps.at(0) * lhs.comps.at(1)
    };
    return result;
}

Vector operator*(const Vector& vec, double coeff) {
    return coeff*vec;
}

Vector operator*(double coeff, const Vector& vec) {
    Vector result(vec.n);
    std::transform(vec.comps.begin(), vec.comps.end(), result.comps.begin(),
                   [coeff](double comp){ return comp * coeff;});
    return result;
}

Vector operator+(const Vector &lhs, const Vector &rhs) {
    if(lhs.n != rhs.n)
        throw std::invalid_argument("Vector addition is defined only for two same dimensional vectors!");
    Vector result(lhs);

    for(std::size_t i = 0; i < lhs.n; i++)
        result[i] += rhs[i];

    return result;
}

Vector Vector::operator-() const {
    return (*this) * (-1);
}

Vector operator-(const Vector &lhs, const Vector &rhs){
    return lhs + ( -rhs );
}

double& Vector::operator[](std::size_t i) {
    if( i >= n )
        throw std::invalid_argument("Index out of bound");
    return comps.at(i);
}

const double& Vector::operator[](std::size_t i) const {
    if( i >= n )
        throw std::invalid_argument("Index out of bound");
    return comps.at(i);
}
