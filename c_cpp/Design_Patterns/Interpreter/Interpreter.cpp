#include <iostream>
#include <string>
#include <memory>

using std::cout;
using std::endl;
using std::string;

class Expression
{
private:
    /* data */
public:
    virtual bool interpret(const string context) const = 0;
};
class TermExpression : public Expression
{
private:
    string data;
public:
    TermExpression(string str) : data(str) {}
    ~TermExpression() {}
    virtual bool interpret(const string context) const override
    {
        auto x = context.find(data);
        if (x == string::npos)
            return false;
        else
            return true;
    }
};
class OrExpression : public Expression
{
private:
    std::shared_ptr<Expression> expr1, expr2;
public:
    OrExpression(std::shared_ptr<Expression> lhs, std::shared_ptr<Expression> rhs) 
        : expr1(lhs), expr2(rhs) {}
    virtual bool interpret(const string context) const override
    {
        return expr1->interpret(context) || expr2->interpret(context);
    }
};
class AndExpression : public Expression
{
private:
    std::shared_ptr<Expression> expr1, expr2;
public:
    AndExpression(std::shared_ptr<Expression> lhs, std::shared_ptr<Expression> rhs) 
        : expr1(lhs), expr2(rhs) {}
    virtual bool interpret(const string context) const override
    {
        return expr1->interpret(context) && expr2->interpret(context);
    }
};
std::shared_ptr<Expression> getIsMale()
{
    std::shared_ptr<Expression> expr1 =  std::make_shared<TermExpression>("Jack");
    std::shared_ptr<Expression> expr2 =  std::make_shared<TermExpression>("Bob");
    return std::make_shared<OrExpression>(expr1, expr2);
}
std::shared_ptr<Expression> getIsMarriedFamale()
{
    std::shared_ptr<Expression> expr1 =  std::make_shared<TermExpression>("Julia");
    std::shared_ptr<Expression> expr2 =  std::make_shared<TermExpression>("Married");
    return std::make_shared<AndExpression>(expr1, expr2);
}
int main(int argc, char const *argv[])
{
    auto isMale = getIsMale();
    auto isMarriedFamale = getIsMarriedFamale();
    cout << "Jack is male?\t" << isMale->interpret("Jack") << endl;
    cout << "Jack is Mairred female?\t" << isMarriedFamale->interpret("Jack") <<endl;
    cout << "Julia is Mairred female?\t" 
         << isMarriedFamale->interpret("Married Julia") <<endl;
    return 0;
}
