#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

const int INF = 1e9; // Assuming INF represents infinity

class floydGraphProcessor
{
public:
    void processInput(const string &line, ifstream &infile, ofstream &outfile)
    {
        // Extract problem number and matrix size
        size_t problem_position = line.find("Problem");
        if (problem_position == string::npos)
        {
            cerr << "Error extracting parameters. \n";
            return;
        }

        int problemNumber, n;
        sscanf(line.c_str() + problem_position, "Problem%d", &problemNumber);

        // Extracting n from the line
        size_t n_position = line.find("n = ");
        if (n_position == string::npos)
        {
            cerr << "Error: 'n =' not found.\n";
            return;
        }

        sscanf(line.c_str() + n_position, "n = %d", &n);

        // Resize output matrix to n x n
        vector<vector<int>> matrix(n, vector<int>(n));

        // Read n x n matrix values
        for (int i = 0; i < n; i++)
        {
            string r;
            getline(infile, r);
            istringstream iss(r);
            for (int j = 0; j < n; j++)
            {
                iss >> matrix[i][j];
            }
        }

        // Output to file
        outfile << "Problem " << problemNumber << ": n = " << n << endl;
        vector<vector<int>> dist = matrix;
        vector<vector<int>> P(n, vector<int>(n, 0));

        // Floyd-Warshall algorithm
        for (int k = 0; k < n; k++)
        {
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    if (k != i && k != j && (dist[i][j] >= dist[i][k] + dist[k][j]))
                    {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        P[i][j] = k + 1;
                    }
                }
            }
        }
        outfile << "Pmatrix:" << endl;
        printPath(P, n, outfile);
        outfile << endl;

        // shortest paths and length to file
        for (int i = 0; i < n; i++)
        {
            outfile << "V" << i + 1 << "-Vj: shortest path and length" << endl;
            for (int j = 0; j < n; j++)
            {
                outfile << "V" << i + 1 << " ";
                if (i != j)
                {
                    outfile << "V" << j + 1 << " ";
                    int v = j;
                    while (P[i][v] != 0)
                    {
                        outfile << "V" << P[i][v] << " ";
                        v = P[i][v] - 1;
                    }
                }
                outfile << ": " << dist[i][j] << endl;
            }
        }
    }

private:
    // pmatrix output
    void printPath(const vector<vector<int>> &P, int n, ofstream &outfile)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                outfile << P[i][j] << " ";
            }
            outfile << endl;
        }
    }
};

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cerr << "Usage: " << argv[0] << " <input_file_path>" << endl;
        return 1;
    }

    ifstream infile(argv[1]);
    if (!infile.is_open())
    {
        cerr << "Error!. Wrong usage of the file, error opening the file. " << endl;
        cout << "Correct usage : " << argv[0] << " <input_file_path>" << endl;
        return 1;
    }

    ofstream outfile("output.txt");
    if (!outfile.is_open())
    {
        cerr << "Error opening output file." << endl;
        return 1;
    }

    string line;
    floydGraphProcessor processor;
    while (getline(infile, line))
    {
        size_t found = line.find("Problem");
        if (found != string::npos)
        {
            processor.processInput(line, infile, outfile);
        }
    }

    infile.close();
    outfile.close();
    return 0;
}
