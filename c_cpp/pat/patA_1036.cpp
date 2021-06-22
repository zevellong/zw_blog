#include <iostream>
#include <vector>

using namespace std;

class Student{
    public:
        friend istream &operator>>(istream &is, Student &s);        
        void print()
        {
            cout << this->name << " " << this->ID << endl;
        }
    
        string name, ID;
        char gender;
        int grade;  
};
istream & operator>>(istream &is, Student &s)
{
    is >> s.name;
    is >> s.gender;
    is >> s.ID;
    is >> s.grade;

    return is;
}
int main()
{
    int i;
    Student tmp;
    vector<Student> vstd;
    cin >> i;
    for (;i>0; i--)
    {
        cin >> tmp;
        vstd.push_back(tmp);
    }
    int stuGrade[2] = {-1, 100};
    vector<Student>::iterator iter[2] = {vstd.end(), vstd.end()};
    for (auto it=vstd.begin(); it!=vstd.end(); it++)
    {
        if (it->gender == 'F')
        {
            if (it->grade > stuGrade[0])
            {
                stuGrade[0] = it->grade;
                iter[0] = it;
            }
        }
        else
        {   
            if (it->grade < stuGrade[1])
            {
                stuGrade[1] = it->grade;
                iter[1] = it;
            }
        }
    }
    bool flg = 0;
    for (auto itt : iter)
    {
        if (itt == vstd.end())
        {
            flg = 1;
            cout << "Absent" << endl;
        }           
        else
            itt->print();
    }
    if (flg)
    {
        cout << "NA" << endl;
    }
    else
    {
        cout << iter[0]->grade - iter[1]->grade << endl;
    }
    
    
    return 0;
}