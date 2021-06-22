#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

class cmd
{
public:
	virtual void exec() = 0;
	virtual void undo() = 0;
private:
};
void cmd::exec() {}
void cmd::undo() {}
class LightRcv
{
public:
	void on()
	{
		cout << "LightRcv::on()" <<endl;
	}
	void off()
	{
		cout << "LightRcv::off()" <<endl;
	}
private:
};
class LightOn : public cmd
{
public:
	LightOn(LightRcv* p) : plr(p) {}
	virtual void exec() override
	{
		cout << "cmd::LightON::exec()\t";
		plr->on();
	}	
	virtual void undo() override
	{
		cout << "cmd::lightOn::undo\t";
		plr->off();
	}
private:
	LightRcv* plr;
};
class LightOff : public cmd
{
public:
	LightOff(LightRcv* p) : plr(p) {}
	virtual void exec() override
	{
		cout << "cmd::LightOff::exec()\t";
		plr->off();
	}	
	virtual void undo() override
	{
		cout << "cmd::lightOff::undo\t";
		plr->on();
	}
private:
	LightRcv* plr;
};
class NoCmd : public cmd
{
public:
	virtual void exec() override {cout<<"NoCmd::exec"<<endl;}
	virtual void undo() override {cout<<"NoCmd::undo"<<endl;}
private:
	
};
class RmtCtrl
{
public:
	RmtCtrl()
	{
		//auto nocmd = new NoCmd;
		for (int i = 0; i < 5; i++)
		{
			onVec[i] = nocmd;
			offVec[i] = nocmd;
		}
		preCmd = nocmd;
	}
	void setCmd(int no, cmd* oncmd, cmd* offcmd)
	{
		onVec[no] = oncmd;
		offVec[no] = offcmd;
	}
	void pressOnCmd(int no)
	{
		cout << "RmtCtrl::PressOn() -->";
		onVec[no]->exec();
		preCmd = onVec[no];
	}
	void pressOffCmd(int no)
	{
		cout << "RmtCtrl::PressOff() -->";
		offVec[no]->exec();
		preCmd = offVec[no];
	}
	void pressUndo()
	{
		cout << "RmtCtrl::undo() -->";
		preCmd->undo();
		preCmd = nocmd;
	}
	~RmtCtrl()
	{
		delete nocmd;
	}
private:
	cmd *onVec[5],*offVec[5];
	cmd* preCmd;
	NoCmd* nocmd = new NoCmd;
};

int main(int argc, char const *argv[])
{
	RmtCtrl ykq;
	LightRcv lr;
	LightOn lo(&lr);
	LightOff loff(&lr);
	ykq.setCmd(0, &lo, &loff);
	ykq.pressOnCmd(0);
	ykq.pressOffCmd(0);
	ykq.pressUndo();
	ykq.pressUndo();
	

	return 0;
}
