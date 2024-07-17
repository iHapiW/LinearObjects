#include "Matrix.hpp"

// Constructors

Matrix::Matrix(std::size_t rowCount, std::size_t columnCount) {
    n = rowCount;
    m = columnCount;
    for(std::size_t i = 0 ; i < rowCount; i++)
        rows.emplace_back(columnCount);
}

Matrix::Matrix(std::initializer_list<std::initializer_list<double>> matrixRows) {

    n = matrixRows.size();
    bool first(true);
    for(auto row: matrixRows) {

        // Size Checking
        if (first) {
            m = row.size();
            first = false;
        }
        else if (m != row.size())
            throw std::invalid_argument("Every row should contain same amount of elements!");

        // Initialization
        Vector result(row);
        rows.push_back(result);
    }

}

Matrix::Matrix(const std::vector<Vector>& matrixRows) {
    n = matrixRows.size();
    m = matrixRows[0].getDimension();
    for(const auto& i: matrixRows) {
        if(i.getDimension() != m)
            throw std::invalid_argument("Every row should contain same amount of elements!");
        rows.push_back(i);
    }
}

Matrix::Matrix(const std::vector<std::vector<double>>& matrixRows) {
    n = matrixRows.size();
    m = matrixRows[0].size();
    for(const auto& i: matrixRows) {
        if(i.size() != m)
            throw std::invalid_argument("Every row should contain same amount of elements!");
        rows.emplace_back(i);
    }
}

Matrix::Matrix(const Matrix &matrix) {
    n = matrix.n;
    m = matrix.m;
    rows = matrix.rows;
}

Matrix::Matrix(const Matrix &&matrix) noexcept {
    n = matrix.n;
    m = matrix.m;
    rows = matrix.rows;
}

Matrix& Matrix::operator=(const Matrix &matrix) {
    n = matrix.n;
    m = matrix.m;
    rows = matrix.rows;
    return *this;
}

Matrix& Matrix::operator=(Matrix &&matrix) noexcept {
    n = matrix.n;
    m = matrix.m;
    rows = matrix.rows;
    return *this;
}

// Methods

std::string Matrix::toString() const {
    std::ostringstream os;
    os << *this;
    return os.str();
}

Matrix Matrix::transpose() const {
    Matrix result(m, n);
    for(std::size_t i = 0; i < n; i++) {
        for(std::size_t j = 0; j < m; j++) {
            result[j][i] = rows[i][j];
        }
    }
    return result;
}

// Getters

Matrix Matrix::getSubMatrix(std::size_t rowStart, std::size_t rowEnd,
                            std::size_t columnStart, std::size_t columnEnd) const {
    if(rowEnd < rowStart || rowEnd >= n)
        throw std::invalid_argument("Condition didn't match (rowStart <= rowEnd < rowCount)");
    if(columnEnd < columnStart || columnEnd >= m)
        throw std::invalid_argument("Condition didn't match (columnStart <= columnEnd < columnCount)");

    std::vector<Vector> newRows{};

    for(std::size_t i = rowStart, k = 0; i <= rowEnd; i++, k++)
        newRows.push_back(getSubRow(i, columnStart, columnEnd));

    return Matrix(newRows);
}

Vector Matrix::getRow(std::size_t idx) const {
    if( idx >= n)
        throw std::invalid_argument("Index out of bound");
    return rows[idx];
}

Vector Matrix::getColumn(std::size_t idx) const {
    if(idx >= m)
        throw std::invalid_argument("Index out of bound");

    Vector result(n);
    for(std::size_t i = 0; i < n; i++)
        result[i] = rows[i][idx];
    return result;
}

Vector Matrix::getSubRow(std::size_t idx, std::size_t columnStart, std::size_t columnEnd) const {
    if(columnStart > columnEnd || columnEnd >= m)
        throw std::invalid_argument("Condition didn't match (columnStart <= columnEnd < columnCount)");
    if( idx >= n)
        throw std::invalid_argument("Index out of bound");

    Vector subRow(columnEnd-columnStart+1);
    for(std::size_t i = columnStart, j=0; i <= columnEnd; i++, j++)
        subRow[j] = rows[idx][i];
    return subRow;
}

Vector Matrix::getSubColumn(std::size_t idx, std::size_t rowStart, std::size_t rowEnd) const {
    if(rowStart > rowEnd || rowEnd >= n)
        throw std::invalid_argument("Condition didn't match (rowStart <= rowEnd < rowCount)");
    if( idx >= m)
        throw std::invalid_argument("Index out of bound");

    Vector subColumn(rowEnd-rowStart+1);
    for(std::size_t i = rowStart, j=0; i <= rowEnd; i++, j++)
        subColumn[j] = rows[i][idx];
    return subColumn;
}

// Setters

void Matrix::setRow(std::size_t idx, const Vector& row) {
    if(row.getDimension() != m)
        throw std::invalid_argument("Row should contain " + std::to_string(m) + " Columns");
    if(idx >= n)
        throw std::invalid_argument("Index out of bound");

    rows[idx] = row;
}

void Matrix::setColumn(std::size_t idx, const Vector& column) {
    if(column.getDimension() != m)
        throw std::invalid_argument("Column should contain " + std::to_string(n) + " Columns");
    if(idx >= m)
        throw std::invalid_argument("Index out of bound");

    for(std::size_t i = 0; i < n; i++)
        rows[i][idx] = column[i];
}

void Matrix::setSubRow(std::size_t idx, std::size_t columnStart, const Vector &subRow) {
    if(subRow.getDimension() > m - columnStart)
        throw std::invalid_argument("Condition didn't match ( subRow.getDimension() <= columnCount - columnStart )");
    if(idx >= n)
        throw std::invalid_argument("Index out of bound");

    for(std::size_t j = 0; j < subRow.getDimension(); j++)
        rows[idx][j+columnStart] = subRow[j];
}

void Matrix::setSubColumn(std::size_t idx, std::size_t rowStart, const Vector &subColumn) {
    if(subColumn.getDimension() > n - rowStart)
        throw std::invalid_argument("Condition didn't match ( subColumn.getDimension() <= rowCount - rowStart )");
    if(idx >= m)
        throw std::invalid_argument("Index out of bound");

    for(std::size_t j = 0; j < subColumn.getDimension(); j++)
        rows[j+rowStart][idx] = subColumn[j];
}

void Matrix::setSubMatrix(std::size_t rowStart, std::size_t columnStart, const Matrix &matrix) {
    if(matrix.m > n - rowStart)
        throw std::invalid_argument("Condition didn't match ( matrix.columnCount <= rowCount - rowStart )");
    if(matrix.n > m - columnStart)
        throw std::invalid_argument("Condition didn't match ( matrix.rowCount <= columnCount - columnStart )");

    for(std::size_t i = 0; i < matrix.n; i++)
        setSubRow(i + rowStart, columnStart, matrix[i]);
}

// Friend Operators

std::ostream &operator<<(std::ostream& os, const Matrix& matrix) {
    for(std::size_t i = 0; i < matrix.n; i++)
        os << matrix.rows[i] << '\n';
    return os;
}

Matrix operator*(const Matrix &lhs, const Matrix &rhs) {
    if(lhs.m != rhs.n)
        throw std::invalid_argument("Left matrix's column count should be equal to right matrix's row count!");

    Matrix result(lhs.n, rhs.m);
    for(std::size_t i = 0; i < lhs.n; i++) {
        for(std::size_t j = 0; j < rhs.m; j++) {
            result[i][j] = lhs.getRow(i) * rhs.getColumn(j);
        }
    }

    return result;
}

// Class Operators

Vector& Matrix::operator[](std::size_t idx) {
    if(idx >= n)
        throw std::invalid_argument("Index out of bound");
    return rows[idx];
}

const Vector& Matrix::operator[](std::size_t idx) const {
    if(idx >= n)
        throw std::invalid_argument("Index out of bound");
    return rows[idx];
}