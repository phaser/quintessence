// Copyright (C) 2013 Cristian Bidea
#include <gtest/gtest.h>
#include <qui/TouchInputEvent.h>
#include <memory>

class TouchInputEventTest : public testing::Test
{
};

TEST_F(TouchInputEventTest, TestConstructor)  // NOLINT
{
    using qui::input::TouchInputEvent;
    std::auto_ptr<TouchInputEvent> event(
            new TouchInputEvent(TouchInputEvent::DOWN, 0, 10, 10));
    EXPECT_EQ(event->getType(), TouchInputEvent::DOWN);
    EXPECT_EQ(event->getPointerId(), 0);
    EXPECT_EQ(event->getX(), 10);
    EXPECT_EQ(event->getY(), 10);
}

TEST_F(TouchInputEventTest, TestDefaultCopyConstructor)  // NOLINT
{
    using qui::input::TouchInputEvent;
    TouchInputEvent event(TouchInputEvent::CANCELED, 1, 12, 11);
    TouchInputEvent event2 = event;

    EXPECT_EQ(event2.getType(), TouchInputEvent::CANCELED);
    EXPECT_EQ(event2.getPointerId(), 1);
    EXPECT_EQ(event2.getX(), 12);
    EXPECT_EQ(event2.getY(), 11);
}
