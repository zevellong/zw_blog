    #include <iostream>
    #include <algorithm>
    #include <vector>
    #include <string>
    #include <sstream>

    using namespace std;
    bool strSmaller(const string &s1, const string &s2)
    {
        bool rtn = true;
        size_t sz1 = s1.size(), sz2 = s2.size();
        size_t size = sz1 > sz2 ? sz1 : sz2;

        for (int i = 0; size>0; i++)
        {
            if (s1[i % sz1] > s2[i % sz2])
            {
                rtn = false;
                break;
            }
            else if (s1[i % sz1] < s2[i % sz2])
            {
                rtn = true;
                break;
            }
        }
        return rtn;
    }

  bool cmp1(string &s1, string &s2)
  {
      return s1 + s2 < s2 + s1;
  }

    int main(int argc, char* argv[])
    {
        string buf;
        vector<string> vbuf;
        int ct;
        cin >> ct;
        for (int i = ct; i > 0; i--)
        {
            cin >> buf;
            vbuf.push_back(buf);
        }
        sort(vbuf.begin(), vbuf.end(), cmp1);
        
        string val;
        int i;
        for (auto s : vbuf)
            val += s;
        for (i = 0; i < val.size(); i++)
            if (val[i] != '0')
                break;
        if (i==val.size())
            cout << 0;
        else
            cout << string(val, i, val.size());
        cout << endl;
        return 0;
    }