#include <iostream>
#include <vector>

using namespace std;
class value{
    public:
	void print()
	{
		for (auto s : vs)
		{
			cout << s << endl;
		}
	}
        void add(const string s){
		vs.push_back(s);
        }
    private:
	vector<string> vs;
};
value fun(int *arr, int size, int cost)
{
    string cut;
    int minCost = cost;
    value v;
    v.add("123");
    v.add("bsd");
    
    cout << "add suc\n";
    return v;
}
int arr[1024];
int main(int argc, char* argv[])
{
    int size, cost;
    cin >> size >> cost;
    for (int i = 0; i < size; i++)
        cin >> arr[i];
    cout << "read data succusee\n";

    value v = fun(arr, size, cost);
    v.print();
       
    return 0;
}
