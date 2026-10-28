#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

static bool s_isGreen = true;
static cocos2d::CCDrawNode* s_indicator = nullptr;

void updateIndicatorColor() {
    if (!s_indicator) return;
    s_indicator->clear();
    cocos2d::ccColor4F color = s_isGreen ? cocos2d::ccColor4F{0.f, 1.f, 0.f, 1.f} : cocos2d::ccColor4F{1.f, 0.f, 0.f, 1.f};
    s_indicator->drawDot(cocos2d::CCPointZero, 4.0f, color);
}

class $modify(PlayLayer) {
    bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
        if (!PlayLayer::init(level, useReplay, dontCreateObjects)) return false;

        auto winSize = cocos2d::CCDirector::sharedDirector()->getWinSize();
        auto node = cocos2d::CCDrawNode::create();
        node->setPosition({winSize.width - 15.f, winSize.height - 15.f});
        node->setZOrder(999);
        this->addChild(node);
        s_indicator = node;

        updateIndicatorColor();
        return true;
    }

    void onQuit() {
        s_indicator = nullptr;
        PlayLayer::onQuit();
    }
};

$execute {
    // Регистрация горячей клавиши (по умолчанию K)
    geode::listenForSettingChanges("toggle-key", +[](std::string val) {});

    geode::Modifier::get()->addHook(
        "+[CCKeyboardDispatcher dispatchKeyboardMSG:isKeyDown:isKeyRepeat:]",
        +[](void* self, enumKeyCodes key, bool down, bool repeat) {
            if (down && !repeat && key == enumKeyCodes::KEY_K) {
                s_isGreen = !s_isGreen;
                updateIndicatorColor();
            }
        }
    );
}
