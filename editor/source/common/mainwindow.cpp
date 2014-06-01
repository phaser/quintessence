#include "./mainwindow.h"
#include "./ui_mainwindow.h"
#include "./GameInterface.h"
#include "OpenGLWidget.h"
#include <dlfcn.h>
#include <qui/log.h>

#define LIB_NAME "/Users/cristi/projects/quintessence/projects/SDLDemo/Debug/libSDLDemo.dylib"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete glWidget;
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    void* handle = dlopen(LIB_NAME, RTLD_LAZY);
    if (!handle)
    {
        LOG(FATAL) << "Could not open " LIB_NAME "!";
        return;
    }

    GameInterface gi;
    gi.gameInit = getFunctionPointer<gameInit_t>(handle, GAME_INIT);
    if (gi.gameInit == nullptr)
    {
        return;
    }
    gi.gameUpdate = getFunctionPointer<gameUpdate_t>(handle, GAME_UPDATE);
    if (gi.gameUpdate == nullptr)
    {
        return;
    }
    gi.gamePaint = getFunctionPointer<gamePaint_t>(handle, GAME_PAINT);
    if (gi.gamePaint == nullptr)
    {
        return;
    }
    gi.gameExit = getFunctionPointer<gameExit_t>(handle, GAME_EXIT);
    if (gi.gameExit == nullptr)
    {
        return;
    }
    gi.gameSetWindowSize = getFunctionPointer<gameSetWindowSize_t>(handle, GAME_SET_WINDOW_SIZE);
    if (gi.gameSetWindowSize == nullptr)
    {
        return;
    }
    
    QGLFormat format;
    format.setVersion(3, 1);
    format.setProfile(QGLFormat::CoreProfile);
    format.setSampleBuffers(true);
    
    glWidget = new OpenGLWidget(format, gi);
    glWidget->setMinimumSize(960, 640);
    glWidget->setMaximumSize(960, 640);
    this->ui->scrollArea->setWidget(glWidget);
}

template <typename T>
T MainWindow::getFunctionPointer(void* handle, const char* functionName)
{
    T func = (T) dlsym(handle, functionName);
    const char* dlsym_error = dlerror();
    if (dlsym_error)
    {
        LOG(LERROR) << "Could not get function pointer for " << functionName << "!";
        dlclose(handle);
        return nullptr;
    }
    return func;
}
