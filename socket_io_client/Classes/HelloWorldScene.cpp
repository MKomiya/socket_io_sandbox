#include "HelloWorldScene.h"
#include "json/rapidjson.h"
#include "json/document.h"

USING_NS_CC;

const static int PLAYER_TEXT_X = 900;
const static int OTHER_TEXT_X = 50;
const static int TEXT_H = 60;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    index = 0;
    
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    edit_box = TextField::create("please input text" , "Meiryo" , 40);
    edit_box->setContentSize(Size(visibleSize.width , 50));
    edit_box->setPosition(Point(visibleSize.width / 2 , 30));
    edit_box->addEventListener(CC_CALLBACK_2(HelloWorld::textFieldEvent, this));
    this->addChild(edit_box);
    
    // ここでsocket.io connection開始。clientを持っておく
    client = SocketIO::connect("http://ec2-52-11-116-58.us-west-2.compute.amazonaws.com:3000", *this);
    client->on("hello", CC_CALLBACK_2(HelloWorld::onReceiveEvent, this));
    
    // TCPサーバー立てる
    auto console = Director::getInstance()->getConsole();
    
    // helloと繋ぐ
    auto name = "hello";
    auto help = "send message to socket server";
    auto callback = [=] (int fd, const std::string& args) {
        Director::getInstance()->getScheduler()->performFunctionInCocosThread([args,this]() {
            CCLOG("%s", args.c_str());
            
            auto sendText = "[{\"value\":\"" + args + "\"}]";
            client->emit("hello", sendText);
        });
    };
    console->addCommand({name, help, callback});
    console->listenOnTCP(6010);
    
    return true;
}

void HelloWorld::onConnect(SIOClient* client){
    // SocketIO::connect success
}

void HelloWorld::onMessage(SIOClient* client, const std::string& data){
    // SocketIO::send receive
}
void HelloWorld::onClose(SIOClient* client){
    // SocketIO::disconnect success
}
void HelloWorld::onError(SIOClient* client, const std::string& data){
    // SocketIO::failed
}

void HelloWorld::onReceiveEvent(SIOClient* client , const std::string& data)
{
    rapidjson::Document doc;
    doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
    rapidjson::Value &val = doc["args"];
    std::string value = val[rapidjson::SizeType(0)]["value"].GetString();
    
    addTalkOther(value);
};

void HelloWorld::textFieldEvent(Ref *pSender, TextField::EventType type)
{
    TextField* text;
    std::string sendText;
    switch (type)
    {
            // IMEが閉じた時
        case TextField::EventType::DETACH_WITH_IME:
            text = (TextField*)pSender;
            
            sendText = "[{\"value\":\"" + text->getString() + "\"}]";
            client->emit("hello", sendText);
            addTalkPlayer(text->getString());
            break;
        default:
            break;
    }
}

/**
 * プレイヤーUI
 */
void HelloWorld::addTalkPlayer(const std::string& str){
    Size size = Director::getInstance()->getVisibleSize();
    
    DrawNode* draw = DrawNode::create();
    
    int originalX = PLAYER_TEXT_X;
    int originalY = size.height - (TEXT_H * (index + 1));
    
    int x = originalX - 290;
    int y = originalY - 60;
    int w = 300;
    int h = 60;
    
    Vec2 points[] = {
        Vec2(x , y),
        Vec2(x + w , y),
        Vec2(x + w , y + h),
        Vec2(x , y + h),
    };
    
    this->addChild(draw);
    draw->drawPolygon(points, 4, Color4F(0 , 0.5, 0, 1), 1, Color4F(0,0,1,1));
    
    auto text = Text::create(str, "Meiryo", 40);
    text->setTextHorizontalAlignment(TextHAlignment::RIGHT);
    text->setAnchorPoint(Point(1.0 , 1.0));
    text->setPosition(Point(originalX , originalY));
    
    this->addChild(text);
    index++;
}

/**
 * その他UI
 */
void HelloWorld::addTalkOther(const std::string& str){
    Size size = Director::getInstance()->getVisibleSize();
    
    DrawNode* draw = DrawNode::create();
    
    int originalX = OTHER_TEXT_X;
    int originalY = size.height - (TEXT_H * (index + 1));
    
    int x = originalX - 10;
    int y = originalY - 60;
    int w = 300;
    int h = 60;
    
    Vec2 points[] = {
        Vec2(x , y),
        Vec2(x + w , y),
        Vec2(x + w , y + h),
        Vec2(x , y + h),
    };
    
    this->addChild(draw);
    draw->drawPolygon(points, 4, Color4F(0.5, 0, 0, 1), 1, Color4F(1,0,0,1));
    
    auto text = Text::create(str, "Meiryo", 40);
    text->setTextHorizontalAlignment(TextHAlignment::LEFT);
    text->setAnchorPoint(Point(0.0 , 1.0));
    text->setPosition(Point(originalX , originalY));
    text->setColor(Color3B(255, 255, 0));
    this->addChild(text);
    index++;
}
