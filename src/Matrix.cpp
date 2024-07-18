#include "Matrix.hpp"

bool MatrixSize::validate() const {
    if( rowCount > 0 && columnCount > 0 )
        return true;
    return false;
}

// Constructors

Matrix::Matrix(std::size_t rowCount, std::size_t columnCount) {
    size.rowCount = rowCount;
    size.columnCount = columnCount;
    if(!size.validate())
        throw std::invalid_argument("Condition didn't match (rowCount, columnCount > 0)");
    for(std::size_t i = 0 ; i < rowCount; i++)
        data.emplace_back(columnCount);
}

Matrix::Matrix(MatrixSize matSize) {
    if(!matSize.validate())
        throw std::invalid_argument("Condition didn't match (rowCount, columnCount > 0)");
    size = matSize;
    for(std::size_t i = 0; i < size.rowCount; i++)
        data.emplace_back(size.columnCount);
}

Matrix::Matrix(std::initializer_list<std::initializer_list<double>> matrixRows) {

    size.rowCount = matrixRows.size();
    if( size.rowCount == 0 )
        throw std::invalid_argument("Condition didn't match (rowCount > 0)");
    bool first(true);
    for(auto row: matrixRows) {

        // Size Checking
        if (first) {
            size.columnCount = row.size();
            if(!size.columnCount)
                throw std::invalid_argument("Condition didn't match (columnCount > 0)");
            first = false;
        }
        else if (size.columnCount != row.size())
            throw std::invalid_argument("Every row should contain same amount of elements!");

        // Initialization
        Vector result(row);
        data.push_back(result);
    }

}

Matrix::Matrix(const std::vector<Vector>& matrixRows) {
    size.rowCount = matrixRows.size();
    if(size.rowCount == 0)
        throw std::invalid_argument("Condition didn't match (rowCount > 0)");

    size.columnCount = matrixRows[0].getDimension();
    if(size.columnCount == 0)
        throw std::invalid_argument("Condition didn't match (columnCount > 0)");

    for(const auto& i: matrixRows) {
        if(i.getDimension() != size.columnCount)
            throw std::invalid_argument("Every row should contain same amount of elements!");
        data.push_back(i);
    }
}

Matrix::Matrix(const std::vector<std::vector<double>>& matrixRows) {
    size.rowCount = matrixRows.size();
    if(size.rowCount == 0)
        throw std::invalid_argument("Condition didn't match (rowCount > 0)");

    size.columnCount = matrixRows[0].size();
    if(size.columnCount == 0)
        throw std::invalid_argument("Condition didn't match (columnCount > 0)");

    for(const auto& i: matrixRows) {
        if(i.size() != size.columnCount)
            throw std::invalid_argument("Every row should contain same amount of elements!");
        data.emplace_back(i);
    }
}

Matrix::Matrix(const Matrix& matrix) {
    size.rowCount = matrix.size.rowCount;
    size.columnCount = matrix.size.columnCount;
    data = matrix.data;
}

Matrix::Matrix(const Matrix&& matrix) noexcept {
    size.rowCount = matrix.size.rowCount;
    size.columnCount = matrix.size.columnCount;
    data = matrix.data;
}

Matrix& Matrix::operator=(const Matrix& matrix) {
    size = matrix.size;
    data = matrix.data;
    return *this;
}

Matrix& Matrix::operator=(Matrix &&matrix) noexcept {
    size = matrix.size;
    data = matrix.data;
    return *this;
}

// Methods

std::string Matrix::toString() const {
    std::ostringstream os;
    os << *this;
    return os.str();
}

Matrix& Matrix::transpose() {
    Matrix result(size.columnCount, size.rowCount);
    for(std::size_t i = 0; i < size.rowCount; i++) {
        for(std::size_t j = 0; j < size.columnCount; j++) {
            result[j][i] = data[i][j];
        }
    }
    *this = result;
    return *this;
}

Matrix& Matrix::swapRows(std::size_t idx1, std::size_t idx2) {
    if( idx1 >= size.rowCount || idx2 >= size.rowCount)
        throw std::invalid_argument("Condition didn't match ( idx1 < rowCount && idx2 < rowCount )");
    std::swap(data[idx1], data[idx2]);
    return *this;
}

Matrix& Matrix::swapColumns(std::size_t idx1, std::size_t idx2) {
    if(idx1 >= size.columnCount || idx2 >= size.columnCount)
        throw std::invalid_argument("Condition didn't match ( idx1 < columnCount && idx2 < columnCount");
    for(std::size_t i = 0; i < size.rowCount; i++)
        std::swap(data[i][idx1], data[i][idx2]);
    return *this;
}

// Getters

Matrix Matrix::getSubMatrix(std::size_t rowStart, std::size_t rowEnd,
                            std::size_t columnStart, std::size_t columnEnd) const {
    if(rowEnd < rowStart || rowEnd >= size.rowCount)
        throw std::invalid_argument("Condition didn't match (rowStart <= rowEnd < rowCount)");
    if(columnEnd < columnStart || columnEnd >= size.columnCount)
        throw std::invalid_argument("Condition didn't match (columnStart <= columnEnd < columnCount)");

    std::vector<Vector> newRows{};

    for(std::size_t i = rowStart, k = 0; i <= rowEnd; i++, k++)
        newRows.push_back(getSubRow(i, columnStart, columnEnd));

    return Matrix(newRows);
}

Vector Matrix::getRow(std::size_t idx) const {
    if( idx >= size.rowCount)
        throw std::invalid_argument("Index out of bound");
    return data[idx];
}

Vector Matrix::getColumn(std::size_t idx) const {
    if(idx >= size.columnCount)
        throw std::invalid_argument("Index out of bound");

    Vector result(size.rowCount);
    for(std::size_t i = 0; i < size.rowCount; i++)
        result[i] = data[i][idx];
    return result;
}

Vector Matrix::getSubRow(std::size_t idx, std::size_t columnStart, std::size_t columnEnd) const {
    if(columnStart > columnEnd || columnEnd >= size.columnCount)
        throw std::invalid_argument("Condition didn't match (columnStart <= columnEnd < columnCount)");
    if( idx >= size.rowCount)
        throw std::invalid_argument("Index out of bound");

    Vector subRow(columnEnd-columnStart+1);
    for(std::size_t i = columnStart, j=0; i <= columnEnd; i++, j++)
        subRow[j] = data[idx][i];
    return subRow;
}

Vector Matrix::getSubColumn(std::size_t idx, std::size_t rowStart, std::size_t rowEnd) const {
    if(rowStart > rowEnd || rowEnd >= size.rowCount)
        throw std::invalid_argument("Condition didn't match (rowStart <= rowEnd < rowCount)");
    if( idx >= size.columnCount)
        throw std::invalid_argument("Index out of bound");

    Vector subColumn(rowEnd-rowStart+1);
    for(std::size_t i = rowStart, j=0; i <= rowEnd; i++, j++)
        subColumn[j] = data[i][idx];
    return subColumn;
}

const MatrixSize& Matrix::getDimension() const {
    return size;
}

// Setters

Matrix& Matrix::setRow(std::size_t idx, const Vector& row) {
    if(row.getDimension() != size.columnCount)
        throw std::invalid_argument("Vector should contain " + std::to_string(size.columnCount) + " Elements");
    if(idx >= size.rowCount)
        throw std::invalid_argument("Index out of bound");

    data[idx] = row;
    return *this;
}

Matrix& Matrix::setColumn(std::size_t idx, const Vector& column) {
    if(column.getDimension() != size.rowCount)
        throw std::invalid_argument("Vector should contain " + std::to_string(size.rowCount) + " Elements");
    if(idx >= size.columnCount)
        throw std::invalid_argument("Index out of bound");

    for(std::size_t i = 0; i < size.rowCount; i++)
        data[i][idx] = column[i];

    return *this;
}

Matrix& Matrix::setSubRow(std::size_t idx, std::size_t columnStart, const Vector &subRow) {
    if(subRow.getDimension() > size.columnCount - columnStart)
        throw std::invalid_argument("Condition didn't match ( subRow.getDimension() <= columnCount - columnStart )");
    if(idx >= size.rowCount)
        throw std::invalid_argument("Index out of bound");

    for(std::size_t j = 0; j < subRow.getDimension(); j++)
        data[idx][j + columnStart] = subRow[j];

    return *this;
}

Matrix& Matrix::setSubColumn(std::size_t idx, std::size_t rowStart, const Vector &subColumn) {
    if(subColumn.getDimension() > size.rowCount - rowStart)
        throw std::invalid_argument("Condition didn't match ( subColumn.getDimension() <= rowCount - rowStart )");
    if(idx >= size.columnCount)
        throw std::invalid_argument("Index out of bound");

    for(std::size_t j = 0; j < subColumn.getDimension(); j++)
        data[j + rowStart][idx] = subColumn[j];

    return *this;
}

Matrix& Matrix::setSubMatrix(std::size_t rowStart, std::size_t columnStart, const Matrix &matrix) {
    if(matrix.size.rowCount > size.rowCount - rowStart)
        throw std::invalid_argument("Condition didn't match ( matrix.rowCount <= rowCount - rowStart )");
    if(matrix.size.columnCount > size.columnCount - columnStart)
        throw std::invalid_argument("Condition didn't match ( matrix.columnCount <= columnCount - columnStart )");

    for(std::size_t i = 0; i < matrix.size.rowCount; i++)
        setSubRow(i + rowStart, columnStart, matrix[i]);

    return *this;
}

// Friend Operators

std::ostream &operator<<(std::ostream& os, const Matrix& matrix) {
    for(std::size_t i = 0; i < matrix.size.rowCount; i++)
        os << matrix.data[i];
    return os;
}

Matrix operator*(const Matrix &lhs, const Matrix &rhs) {
    if(lhs.size.columnCount != rhs.size.rowCount)
        throw std::invalid_argument("Left matrix's column count should be equal to right matrix's row count!");

    Matrix result(lhs.size.rowCount, rhs.size.columnCount);
    for(std::size_t i = 0; i < lhs.size.rowCount; i++) {
        for(std::size_t j = 0; j < rhs.size.columnCount; j++) {
            result[i][j] = lhs.getRow(i) * rhs.getColumn(j);
        }
    }

    return result;
}

Matrix operator*(const Matrix &lhs, double coeff) {
    return coeff * lhs;
}

Matrix operator*(double coeff, const Matrix &lhs) {
    Matrix result(lhs);
    for(std::size_t i = 0; i < lhs.size.rowCount; i++)
        for(std::size_t j = 0; j < lhs.size.columnCount; j++)
            result[i][j] *= coeff;
    return result;
}

Matrix operator+(const Matrix &lhs, const Matrix &rhs) {
    if(lhs.size.rowCount != rhs.size.rowCount || lhs.size.columnCount != rhs.size.columnCount)
        throw std::invalid_argument("Addition of matrices with different sizes are not defined!");

    Matrix result(lhs);
    for(std::size_t i = 0; i < lhs.size.rowCount; i++)
        for(std::size_t j = 0; j < lhs.size.columnCount; j++)
            result[i][j] += rhs[i][j];

    return result;
}

// Class Operators

Vector& Matrix::operator[](std::size_t idx) {
    if(idx >= size.rowCount)
        throw std::invalid_argument("Index out of bound");
    return data[idx];
}

const Vector& Matrix::operator[](std::size_t idx) const {
    if(idx >= size.rowCount)
        throw std::invalid_argument("Index out of bound");
    return data[idx];
}
