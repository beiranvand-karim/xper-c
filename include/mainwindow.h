#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <canvasview.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:

  void on_ellipseAction_triggered();
  void on_moveAction_triggered();
  void on_frameAction_triggered();
  void on_rectAction_triggered();
  void on_penAction_triggered();
  void on_pencilAction_triggered();
  void on_lineAction_triggered();
  void on_polygonAction_triggered();
  void on_imageAction_triggered();
  void on_textAction_triggered();
  void on_scaleAction_triggered();

private:
  Ui::MainWindow *ui;
  CanvasView *canvasView;
};
#endif // MAINWINDOW_H
