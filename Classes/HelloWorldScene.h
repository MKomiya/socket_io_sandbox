#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <SocketIO.h>
#include <ui/cocosGUI.h>

using namespace cocos2d::network;
using namespace cocos2d::ui;

class HelloWorld : public cocos2d::Layer, public SocketIO::SIODelegate
{
private:
    int index;
    SIOClient* client;
    TextField* edit_box;

public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    void onReceiveEvent(SIOClient* client, const std::string& data);
    void onReceiveRooms(SIOClient* client, const std::string& data);
    void joinRoomEvent(const std::string& room_name);

    virtual void onConnect(SIOClient* client);
    virtual void onMessage(SIOClient* client, const std::string& data);
    virtual void onClose(SIOClient* client);
    virtual void onError(SIOClient* client, const std::string& data);

    void textFieldEvent(Ref *pSender, TextField::EventType type);
    std::string HelloWorld::getValue(const std::string& data, const std::string key);
    void addTalkPlayer(const std::string& str);
    void addTalkOther(const std::string& str);

    virtual bool init();
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
