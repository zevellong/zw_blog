#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

class Stereo
{
public:
    static Stereo *getInstance()
    {
        static Stereo instance;
        return &instance;
    }
    void on()
    {
        cout << "Stereo: on" << endl;
    }
    void set(int disk)
    {
        cout << "Stereo: setDisk_" << disk << endl;
    }
    void off()
    {
        cout << "Stereo: off" << endl;
    }
    private:
    Stereo() {}
};

class Projecter
{
public:
    static Projecter *getInstance()
    {
        static Projecter instance;
        return &instance;
    }
    void play()
    {
        cout << "Projecter: playing" << endl;
    }
    void pause()
    {
        cout << "Projecter off" << endl;
    }
    void close()
    {
        cout << "Projecter: close" << endl;
    }
    void open()
    {
        cout << "Projecter: open" << endl;
    }
};
class Screen
{
public:
    static Screen *getInstance()
    {
        static Screen instance;
        return &instance;
    }
    void up()
    {
        cout << "Screen: up" << endl;
    }
    void down()
    {
        cout << "Screen down" << endl;
    }
    void close()
    {
        cout << "Screen: close" << endl;
    }
    void open()
    {
        cout << "Screen: open" << endl;
    }
};
class TheaterFacade
{
public:
    TheaterFacade() : pSte(Stereo::getInstance()),
                      pPro(Projecter::getInstance()),
                      pScr(Screen::getInstance())
    {
    }
    void ready()
    {
        cout << "-----ready--------- " << endl;
        pSte->on();
        pPro->open();
        pScr->open();
    }
    void play()
    {
        cout << "-----play--------- " << endl;
        pSte->set(1);
        pScr->down();
        pPro->play();
    }
    void close()
    {
        cout << "-----close--------- " << endl;
        pSte->off();
        pScr->up();
        pScr->close();
        pPro->close();
    }
    void pause()
    {
        cout << "-----pause--------- " << endl;
        pPro->pause();
    }
private:
    Stereo *pSte;
    Projecter *pPro;
    Screen *pScr;
};
int main(int argc, char const *argv[])
{
    TheaterFacade tf;
    tf.ready();
    tf.play();
    tf.pause();
    tf.close();
    return 0;
}
