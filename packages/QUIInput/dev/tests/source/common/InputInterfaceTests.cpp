// Copyright (C) 2013 Cristian Bidea
#include <gtest/gtest.h>
#include <qui/InputInterface.h>
#include <qui/TouchInputEvent.h>
#include <qui/ITouchInput.h>
#include <memory>
#include <list>

using qui::input::InputInterface;
using qui::input::TouchInputEvent;

class InputInterfaceTests : public testing::Test
{
};

class TestListener : public qui::input::ITouchInput
{
    public:
     bool cRU;
     int began;
     int move;
     int end;
     int canceled;

     TestListener()
     {
        cRU = true;
        began = move = end = canceled = 0;
     }

     void onTouchesBegan(std::list<TouchInputEvent*> touches)
     {
         began += touches.size();
     }

     void onTouchesMoved(std::list<TouchInputEvent*> touches)
     {
         move += touches.size();
     }

     void onTouchesEnd(std::list<TouchInputEvent*> touches)
     {
         end += touches.size();
     }

     void onTouchesCanceled(std::list<TouchInputEvent*> touches)
     {
         canceled += touches.size();
     }

     bool canReceiveUpdates()
     {
         return cRU;
     }
};

TEST_F(InputInterfaceTests, TestWholeEventLoop)  // NOLINT
{
    InputInterface store;
    TestListener listener;
    store.registerTouchInputListener(&listener);
    store.addTouchEvent(new TouchInputEvent(TouchInputEvent::DOWN, 0, 10, 10));
    store.addTouchEvent(new TouchInputEvent(TouchInputEvent::MOVE, 0, 10, 10));
    store.addTouchEvent(new TouchInputEvent(TouchInputEvent::UP, 0, 10, 10));
    store.addTouchEvent(new TouchInputEvent(TouchInputEvent::CANCELED, 0, 10, 10));

    listener.cRU = false;
    store.fireUpdateListeners();
    EXPECT_EQ(listener.began, 0);
    EXPECT_EQ(listener.move, 0);
    EXPECT_EQ(listener.end, 0);
    EXPECT_EQ(listener.canceled, 0);

    // No events to fire
    store.fireUpdateListeners();
    EXPECT_EQ(listener.began, 0);
    EXPECT_EQ(listener.move, 0);
    EXPECT_EQ(listener.end, 0);
    EXPECT_EQ(listener.canceled, 0);

    store.addTouchEvent(new TouchInputEvent(TouchInputEvent::DOWN, 0, 10, 10));
    store.addTouchEvent(new TouchInputEvent(TouchInputEvent::MOVE, 0, 10, 10));
    store.addTouchEvent(new TouchInputEvent(TouchInputEvent::UP, 0, 10, 10));
    store.addTouchEvent(new TouchInputEvent(TouchInputEvent::CANCELED, 0, 10, 10));
    store.unregisterTouchInputListener(&listener);
    store.fireUpdateListeners();  // no listener to fire to
    EXPECT_EQ(listener.began, 0);
    EXPECT_EQ(listener.move, 0);
    EXPECT_EQ(listener.end, 0);
    EXPECT_EQ(listener.canceled, 0);

    store.addTouchEvent(new TouchInputEvent(TouchInputEvent::DOWN, 0, 10, 10));
    store.addTouchEvent(new TouchInputEvent(TouchInputEvent::MOVE, 0, 10, 10));
    store.addTouchEvent(new TouchInputEvent(TouchInputEvent::UP, 0, 10, 10));
    store.addTouchEvent(new TouchInputEvent(TouchInputEvent::CANCELED, 0, 10, 10));
    store.registerTouchInputListener(&listener);
    listener.cRU = true;
    store.fireUpdateListeners();
    EXPECT_EQ(listener.began, 1);
    EXPECT_EQ(listener.move, 1);
    EXPECT_EQ(listener.end, 1);
    EXPECT_EQ(listener.canceled, 1);
}
