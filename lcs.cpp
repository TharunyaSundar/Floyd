#include <iostream>
#include <string>
using namespace std;

pair<int **, char **> lcs_length(const string &X, const string &Y)
{
    int m = X.length();
    int n = Y.length();

    // Initialize dynamic programming tables
    int **c = new int *[m + 1];
    char **b = new char *[m + 1];

    for (int i = 0; i <= m; i++)
    {
        c[i] = new int[n + 1];
        b[i] = new char[n + 1];
    }

    // Initialize the first row and column of the dynamic programming table
    for (int i = 0; i <= m; i++)
    {
        c[i][0] = 0;
    }
    for (int j = 0; j <= n; j++)
    {
        c[0][j] = 0;
    }

    // Compute lengths of LCS and populate direction matrix
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (X[i - 1] == Y[j - 1])
            {
                c[i][j] = c[i - 1][j - 1] + 1;
                b[i][j] = 'D';
            }
            else
            {
                if (c[i - 1][j] >= c[i][j - 1])
                {
                    c[i][j] = c[i - 1][j];
                    b[i][j] = 'U';
                }
                else
                {
                    c[i][j] = c[i][j - 1];
                    b[i][j] = 'L';
                }
            }
        }
    }
    return {c, b};
}

string lcs_backtrack(char **b, const string &X, int i, int j)
{
    if (i == 0 || j == 0)
        return "";
    if (b[i][j] == 'D')
    {
        return lcs_backtrack(b, X, i - 1, j - 1) + X[i - 1];
    }
    else if (b[i][j] == 'U')
    {
        return lcs_backtrack(b, X, i - 1, j);
    }
    else
    {
        return lcs_backtrack(b, X, i, j - 1);
    }
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        cout << "Usage: " << argv[0] << " <string1> <string2>" << endl;
        return 1;
    }
    string X = argv[1];
    string Y = argv[2];

    auto result = lcs_length(X, Y);
    int **c = result.first;
    char **b = result.second;

    cout << "Length of LCS: " << c[X.length()][Y.length()] << endl;

    string lcs = lcs_backtrack(b, X, X.length(), Y.length());
    cout << "LCS: " << lcs << endl;

    // Clean up memory
    int m = X.length();
    for (int i = 0; i <= m; ++i)
    {
        delete[] c[i];
        delete[] b[i];
    }
    delete[] c;
    delete[] b;

    return 0;
}
