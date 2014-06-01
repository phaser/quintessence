#include "./mainwindow.h"
#include "./ui_mainwindow.h"
#include "OpenGLWidget.h"
#include <dlfcn.h>
#include <qui/log.h>

#define LIB_NAME "libSDLDemo.dylib"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QGLFormat format;
    format.setVersion(3, 1);
    format.setProfile(QGLFormat::CoreProfile);
    format.setSampleBuffers(true);

    glWidget = new OpenGLWidget(format);
    glWidget->setMinimumSize(960, 640);
    glWidget->setMaximumSize(960, 640);
    this->ui->scrollArea->setWidget(glWidget);
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
        exit(1);
    }

    typedef void (*game_function)();
    game_function gameInit = (game_function) dlsym(handle, "gameInit");
    const char* dlsym_error = dlerror();
    if (dlsym_error)
    {
        LOG(LERROR) << "Coud not load gameInit()!";
        dlclose(handle);
        exit(2);
    }
}
