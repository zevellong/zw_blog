#include <iostream>
#include <string>
#include <unordered_map>

using std::cout;
using std::endl;
using std::string; 
using std::unordered_map;
/*! \class WebSite
*  \brief Brief class description
*
*  Detailed description
*/
class user
{
	public:
	user(string nm) : name(nm) {}
	string getName() const {return name;}
	private:
	string name;
};

class WebSite
{
public:
	virtual void use(const user& u) {}
	WebSite() = default;
	virtual ~WebSite() = 0;

protected:
};
WebSite::~WebSite()
{

}

class ConcreteWebsite : public WebSite
{
	public:
	ConcreteWebsite(string tp) : type(tp) {  }
	virtual void use(const user& u) override
	{
		cout << "WebSite type:" << type << " user:"  << u.getName() << endl;
	}
	private:
	string type;
};
class WebSiteFactory{
	public:
	size_t webCount() const
	{
		return webMap.size();
	}		
	void useWeb(string type, user u)
	{
		auto ed = webMap.end();
		if (webMap.find(type) == ed)
		{
			webMap[type] = new ConcreteWebsite(type);
		}
		webMap[type]->use(u);	
	}
	~WebSiteFactory()
	{
		unordered_map<string, WebSite*>::iterator mapIt = webMap.begin();
		cout << "~WebSiteFactory()" << endl;
		while (mapIt != webMap.end())
		{
			cout << "delete type:" << mapIt->first << endl;
			delete mapIt++->second;
			//++mapIt;
		}
	}
	private:
	unordered_map<string, WebSite*> webMap;
};

int main(int argc, char* argv[])
{
	WebSiteFactory wf;
	user u1("jack ma"), u2("BabaLa"), u3("GTR");
	wf.useWeb("weibo",  u1);
	wf.useWeb("zhihu", u2);
	wf.useWeb("tieba", u3);
	user u4("panda");
	wf.useWeb("zhihu", u4);
	cout << "wf.count=" <<wf.webCount()  << endl;
	return 0;
}
