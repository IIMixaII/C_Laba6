#include <iostream>
#include <vector>
#include <climits>
#include <random>
using namespace std;
int multiplicationCounter = 0;
random_device rd;
// Функция для генерации и вывода матриц
vector<vector<vector<int>>> GenerateAndPrintMatrix(const vector<int>& p) {
    vector<vector<vector<int>>> matrices;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 3); 

    for (int i = 0; i < p.size() - 1; i++) {
        int rows = p[i];
        int columns = p[i + 1];
        vector<vector<int>> matrix(rows, vector<int>(columns, 0));

        for (int j = 0; j < rows; j++) {
            for (int k = 0; k < columns; k++) {
                matrix[j][k] = dis(gen); 
            }
        }

        matrices.push_back(matrix);
    
    cout << "Matrix " << i + 1 << ":" << endl;
    for (const auto& row : matrix) {
        for (int element : row) {
            cout << element << ' ';
        }
        cout << endl;
    }
    cout << endl; 
}
    return matrices;
}


int matrixChainOrder(const vector<int>& p, vector<vector<int>>& m, vector<vector<int>>& s) {
    int n = p.size();
    for (int i = 1; i < n; i++)
        m[i][i] = 0;

    for (int L = 2; L < n; L++) {
        for (int i = 1; i < n - L + 1; i++) {
            int j = i + L - 1;
            m[i][j] = INT_MAX;
            for (int k = i; k <= j - 1; k++) {
                int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
    return m[1][n - 1];
}
//vector<vector<int>> multiplyMatrices(const vector<vector<int>>& A, const vector<vector<int>>& B) {
//    int rowsA = A.size();
//    int colsA = A[0].size();
//    int rowsB = B.size();
//    int colsB = B[0].size();
//
//    if (colsA != rowsB) {
//        throw invalid_argument("Number of columns in A must be equal to number of rows in B");
//    }
//
//    vector<vector<int>> result(rowsA, vector<int>(colsB, 0));
//
//    for (int i = 0; i < rowsA; ++i) {
//        for (int j = 0; j < colsB; ++j) {
//            for (int k = 0; k < colsA; ++k) {
//                // Increment the counter for each multiplication
//                multiplicationCounter++;
//                long long temp = static_cast<long long>(A[i][k]) * B[k][j];
//                if (temp > INT_MAX || temp < INT_MIN) {
//                    result[i][j] = (temp > INT_MAX) ? INT_MAX : INT_MIN;
//                }
//                else {
//                    result[i][j] = static_cast<int>(temp);
//                }
//            }
//        }
//    }
//
//    return result;
//}
vector<vector<int>> multiplyMatrices(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int rowsA = A.size();
    int colsA = A[0].size();
    int rowsB = B.size();
    int colsB = B[0].size();

    if (colsA != rowsB) {
        throw invalid_argument("Количество столбцов в A должно быть равно количеству строк в B");
    }

    vector<vector<int>>  result(rowsA, vector<int>(colsB, 0));

    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < colsB; ++j) {
            for (int k = 0; k < colsA; ++k) {
                result[i][j] += A[i][k] * B[k][j];
                multiplicationCounter++;
            }
        }
    }

    return result;
}
//int matrixChainMultiplication(vector<int> const& p, int i, int j, vector<vector<int>>& lookup)
//{
//    
//    if (j <= i + 1) {
//        return 0;
//    }
//    int min = INT_MAX; // определяем Количество умножений
//
//    if (lookup[i][j] == 0)
//    {
//       
//
//        for (int k = i + 1; k <= j - 1; k++)
//        {
//            int cost = matrixChainMultiplication(p, i, k, lookup);
//
//            
//            cost += matrixChainMultiplication(p, k, j, lookup);
//
//            
//            cost += p[i] * p[k] * p[j];
//
//            if (cost < min) {
//                min = cost;
//            }
//        }
//
//        lookup[i][j] = min;
//    }
//
//   
//    return lookup[i][j];
//}


void printOptimalParenthesis(const vector<vector<int>>& s, int i, int j) {
    if (i == j) {
        cout << "A" << i;
    }
    else {
        cout << "(";
        printOptimalParenthesis(s, i, s[i][j]);
        printOptimalParenthesis(s, s[i][j] + 1, j);
        cout << ")";
    }
}
vector<vector<int>> multiplyMatrixChain(const vector<vector<vector<int>> > &matrices, const vector<vector<int>>  & s, int i, int j) {
   
    if (i == j) {
        return matrices[i-1];
    }

    vector<vector<int>>  X = multiplyMatrixChain(matrices, s, i, s[i][j]);
    vector<vector<int>>  Y = multiplyMatrixChain(matrices, s, s[i][j] + 1, j);
        
    
    return multiplyMatrices(X, Y);
}
void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int element : row) {
            cout << element << ' ';
        }
        cout << endl;
    }
}

int main() {
    vector<int> p = { 33, 33, 13, 53, 13, 23, 23 };
    int n = p.size();
    vector<vector<int>> m(n, vector<int>(n, 0));
    vector<vector<int>> s(n, vector<int>(n, 0));
    setlocale(LC_ALL, "Rus");
    vector<vector<vector<int>>> matrices = GenerateAndPrintMatrix(p);
    matrixChainOrder(p, m, s);
    cout << "Минимальное количество умножений: " << m[1][n - 1] << endl;
    cout << "Оптимально раставленные скобик: ";
    printOptimalParenthesis(s, 1, n - 1);
    cout <<  endl;
    vector<vector<int>> lookup(n + 1, vector<int>(n + 1));
    //cout << "Минимальное количество умножений " << matrixChainMultiplication(p, 0, n - 1, lookup) << endl;
    vector<vector<int>>  result = multiplyMatrixChain(matrices, s, 1, n - 1);
    printMatrix(result);
    cout << "Количество умножений: " << multiplicationCounter << endl;
    return 0;
}
