#ifndef SRC_S21_MATRIX_OOP_H_
#define SRC_S21_MATRIX_OOP_H_

#define MARIX_EPS 1e-7

class S21Matrix {
 private:
  int rows_, cols_;
  double** matrix_;

  enum operation_t { SUM_OP, SUB_OP };

  void Cleanup() noexcept;
  void CalcMatrix(const S21Matrix& b, operation_t op);

 public:
  // Construction, Distruction
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept;
  ~S21Matrix();

  // Getters, Setters
  int GetRows() const noexcept;
  int GetCols() const noexcept;

  void SetRows(int newRows);
  void SetCols(int newCols);

  // Logic
  bool EqMatrix(const S21Matrix& other) const noexcept;

  // Arithmetic
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num) noexcept;
  void MulMatrix(const S21Matrix& other);

  // Other
  S21Matrix Transpose() noexcept;
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

  // Operators
  double& operator()(int i, int j);
  const double& operator()(int i, int j) const;
  bool operator==(const S21Matrix& other) const noexcept;

  S21Matrix& operator=(S21Matrix&& other);
  S21Matrix& operator=(const S21Matrix& other);

  S21Matrix operator+(const S21Matrix& other) const;
  S21Matrix operator+=(const S21Matrix& other);

  S21Matrix operator-(const S21Matrix& other) const;
  S21Matrix operator-=(const S21Matrix& other);

  S21Matrix operator*(const double num) const;
  S21Matrix operator*(const S21Matrix& other) const;
  S21Matrix operator*=(const double num);
  S21Matrix operator*=(const S21Matrix& other);
  friend S21Matrix operator*(const double& num, const S21Matrix& matrix);

  // Utils
  static void CopyVals(const S21Matrix& from, S21Matrix& to);
  static void CopyValsSkip(const S21Matrix& from, S21Matrix& to, int skipRow,
                           int skipCol);
  static void Swap(S21Matrix& one, S21Matrix& second);
};

#endif  // !SRC_S21_MATRIX_OOP_H_