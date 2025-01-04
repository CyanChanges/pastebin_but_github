#include <iostream>
using namespace std;

#define int unsigned long long

int a[100005]{};
int b[100005]{};
int n, t;

bool try_mod(int* arr, int& i)
{
    if (i >= n)
        return true;

    if (t < arr[i]) return true;
    // cout << "pick " << (arr == a ? 'a' : 'b') << '[' << i << ']' << endl;
    t -= arr[i++];
    return false;
}

bool pick(int& i, int& j)
{
    if (i > n || j > n) return true;
    if (a[i] == b[j])
    {
        if (a[i + 1] <= b[j + 1])
        {
            if (try_mod(a, i)) return true;
        }
        else if (try_mod(b, j)) return true;
    }
    else if (a[i] <= b[j])
    {
        if (try_mod(a, i)) return true;
    }
    else
        if (try_mod(b, j)) return true;
    if (t <= 0) return true;

    return false;
}

signed main()
{
    cin >> n >> t;
    for (int idx = 0; idx < n; ++idx)
        cin >> a[idx];
    for (int idx = 0; idx < n; ++idx)
        cin >> b[idx];
    int i = 0, j = 0;
    while (true)
        if (pick(i, j)) break;
    if (t > 0)
    {
        if (i < n)
            while (!try_mod(a, i))
            {
            }
        if (j < n)
            while (!try_mod(b, j))
            {
            }
    }
    cout << i + j << endl;
    return 0;
}
