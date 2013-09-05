// Copyright (C) 2013 Cristian Bidea
#include <android/JNIGameInterface.h>
#include <qui/log.h>
#include <qui/VirtualFS.h>
#include <qui/StandardGameEntry.h>
#include <qui/Timer.h>
#include <qui/InputInterface.h>
#include <qui/TouchInputEvent.h>
#include <string>

qui::Timer timer;

#ifdef __cplusplus
extern "C"
{
#endif

#define DBG_HALT()  ({ volatile int i=0; while (i == 0); }) // NOLINT
size_t dtime;

JNIEXPORT void JNICALL Java_ro_qui_apps_JNIGameInterface_init
  (JNIEnv *env, jclass cls, jstring apkPath)
{
    const char *nativeString = env->GetStringUTFChars(apkPath, 0);
    LOG(INFO) << "init( " << nativeString << " )";
    qui::VirtualFS fs;
    fs.addRelativePath(std::string(nativeString));
    env->ReleaseStringUTFChars(apkPath, nativeString);
    dtime = 0;
}

JNIEXPORT void JNICALL Java_ro_qui_apps_JNIGameInterface_onSurfaceCreated
  (JNIEnv *, jclass cls)
{
    LOG(INFO) << "onSurfaceCreated";
}

JNIEXPORT void JNICALL Java_ro_qui_apps_JNIGameInterface_onDrawFrame
  (JNIEnv *env, jclass cls)
{
    LOG(INFO) << "onDrawFrame";
    using qui::input::InputInterface;
    dtime += timer.getDeltaTime();
    if (dtime > 30)  // limit to ~30 fps
    {
        InputInterface ii;
        ii.fireUpdateListeners();
        qui::game->update(dtime);
        qui::game->paint();
        dtime = 0;
    }
}

JNIEXPORT void JNICALL Java_ro_qui_apps_JNIGameInterface_onSurfaceChanged
  (JNIEnv * env, jclass cls, jint width, jint height)
{
    LOG(INFO) << "onSurfaceChanged";
    LOG(INFO) << "Width: " << width << " Height: " << height;
    qui::game->getWindow().setSize(glm::vec2(width, height));
    qui::game->init();
}

JNIEXPORT void JNICALL Java_ro_qui_apps_JNIGameInterface_onTouchEvent
  (JNIEnv *env, jclass cls, jint pointerId, jint type, jint x, jint y)
{
    using qui::input::InputInterface;
    using qui::input::TouchInputEvent;
    LOG(INFO) << "Event: " << type << " x = " << x << " y = " << y;
    InputInterface ii;
    TouchInputEvent::TouchInputEventType et;
    switch (type)
    {
        case 1: et = TouchInputEvent::DOWN; break;
        case 2: et = TouchInputEvent::UP; break;
        case 3: et = TouchInputEvent::MOVE; break;
        default:
                LOG(LERROR) << "Unknown event type: " << type;
    }
    ii.addTouchEvent(new TouchInputEvent(et, pointerId, x, y));
}
#ifdef __cplusplus
}
#endif
