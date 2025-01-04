#include <iostream>
#include <algorithm>
using namespace std;

int arr[1000005]{};

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> arr[i];
    sort(arr, arr + n);
    int t = n;
    int mid = n / 2 + 1;
    int r = mid;
    for (int l = 0; r < n; r++)
    {
        if (arr[l] * 2 <= arr[r] && l < mid)
        {
            t--;
            l++;
        }
    }
    cout << t << endl;
    return 0;
}
