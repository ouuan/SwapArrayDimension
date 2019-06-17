/*

MIT License

Copyright (c) 2019 ouuan

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

string solve(const string & x, int y);

ifstream fin;
ofstream fout;
int dimension;
string sourceFile, arrayName;

vector<int> a, bracket;
stack<int> stk;

int main(int argc, char * argv[])
{
    if (argc <= 4)
    {
        cout << "main <sourceFile> <arrayName> <dimension> <a_1 a_2 a_3 ... a_{dimension}>" << endl;
        return 0;
    }

    sourceFile = argv[1];
    arrayName = argv[2];
    dimension = atoi(argv[3]);

    for (int i = 0; i < dimension; ++i) a.push_back(atoi(argv[i + 4]) - 1);

    fin.open(sourceFile);

    if (!fin.is_open())
    {
        cout << "Can't open source file." << endl;
        return 0;
    }

    string s, outputFile;

    int split = sourceFile.rfind('.');
    outputFile = sourceFile.substr(0, split) + "_swap" + sourceFile.substr(split);
    fout.open(outputFile);

    while (getline(fin, s))
    {
        bracket.resize(s.size());
        for (int i = 0; i < s.size(); ++i)
        {
            if (s[i] == '[') stk.push(i);
            else if (s[i] == ']')
            {
                bracket[i] = stk.top();
                bracket[stk.top()] = i;
                stk.pop();
            }
        }
        fout << solve(s, 0) << endl;
    }

    cout << "Succeeded." << endl;

    return 0;
}

string solve(const string & x, int y)
{
    int p = x.find(arrayName + "[");
    if (p == -1) return x;
    if (p) return x.substr(0, p) + solve(x.substr(p), y + p);
    string out = arrayName;
    vector<string> ans;
    ans.resize(dimension);
    int i, l, r;
    for (i = 0, l = p + arrayName.size(); i < dimension; ++i, l = r + 1)
    {
        r = bracket[l + y] - y;
        ans[a[i]] = "[" + solve(x.substr(l + 1, r - l - 1), y + l + 1) + "]";
    }
    for (i = 0; i < dimension; ++i) out += ans[i];
    out += solve(x.substr(l), y + l);
    return out;
}
