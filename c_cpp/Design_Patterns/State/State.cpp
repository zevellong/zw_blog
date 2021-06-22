#include "State.h"

StateBase::StateBase(Activity* spa) : sa(spa) {}

noRaffle::noRaffle(Activity* spa) : StateBase(spa) {}
void noRaffle::deduceMoney()
{
    cout << "现在扣除50积分，然后您可以抽奖" << endl;
    sa->setState(sa->s2);
}
bool noRaffle::ruffle()
{
    cout << "不能抽奖，请先支付50积分" << endl;
    return false;
}
void noRaffle::dispensePrize()
{
    cout << "没有奖品，请先抽奖，支付50积分" << endl;
}

canRaffle::canRaffle(Activity* spa) : StateBase(spa) {}
void canRaffle::deduceMoney()
{
    cout << "已经扣除50积分了，可以抽奖" << endl;
}
bool canRaffle::ruffle()
{
    cout << "正在抽奖，请先稍等~~~" << endl;
    static std::default_random_engine e(time(NULL));
    static std::uniform_real_distribution<double> u(0, 1);
    auto x = u(e);
    cout << "u(e)=" << x <<endl; 
    if (x <= 0.1)
    {
        cout << "恭喜中奖，请去领取奖品" << endl;
        sa->setState(sa->s3);
        return true;
    }
    else
    {
        cout << "没有中奖，祝您下次好运" << endl;
        sa->setState(sa->s1);
        return false;
    }
}
void canRaffle::dispensePrize()
{
    cout << "没有奖品，请先抽奖，支付50积分" << endl;
}

dispenseState::dispenseState(Activity* spa) : StateBase(spa) {}
void dispenseState::deduceMoney()
{
    cout << "已经中奖，请去领取奖品" << endl;
}
bool dispenseState::ruffle()
{
    cout << "已经中奖，请去领取奖品" << endl;
    return false;
}
void dispenseState::dispensePrize()
{
    cout << "奖品领取成功" << endl;
    sa->setState(sa->s4);
}

outState::outState(Activity* spa) : StateBase(spa) {}
void outState::deduceMoney()
{
    cout << "已经中奖，欢迎下次再来" << endl;
}
bool outState::ruffle()
{
    cout << "已经中奖，欢迎下次再来" << endl;
    return false;
}

void outState::dispensePrize()
{
    cout << "已经中奖，欢迎下次再来" << endl;
}