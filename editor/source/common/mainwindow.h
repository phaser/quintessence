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

private:
    Ui::MainWindow *ui;
    OpenGLWidget *glWidget;
};

#endif  // PACKAGES_QUI_QUIGAMEENTRY_DEV_SOURCE_QT5_MAINWINDOW_H_
