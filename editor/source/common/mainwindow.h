#ifndef PACKAGES_QUI_QUIGAMEENTRY_DEV_SOURCE_QT5_MAINWINDOW_H_
#define PACKAGES_QUI_QUIGAMEENTRY_DEV_SOURCE_QT5_MAINWINDOW_H_

#include <QMainWindow>

namespace Ui
{
    class MainWindow;
}  // namespace Ui

class OpenGLWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT
 public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void on_pushButton_clicked();

    void on_actionOpen_Game_triggered();

private:
    Ui::MainWindow *ui;
    OpenGLWidget *glWidget;

    template <typename T>
    T getFunctionPointer(void* handle, const char* functionName);
    void openGame(const char* gamePath);
};

#endif  // PACKAGES_QUI_QUIGAMEENTRY_DEV_SOURCE_QT5_MAINWINDOW_H_
