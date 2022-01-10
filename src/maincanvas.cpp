#include "maincanvas.h"
#include "iostream"
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <rectangleitem.h>

using namespace std;

MainCanvas::MainCanvas(QObject *parent)
    : QGraphicsScene(parent), currentItem(nullptr) {
  this->setSceneRect(0, 0, 1000, 1000);
}

MainCanvas::~MainCanvas() { delete currentItem; }

void MainCanvas::setCanvasState(CanvasState::Shapes shape,
                                CanvasState::State state) {
  this->shape = shape;
  this->state = state;
  currentItem = nullptr;
  for (auto item : this->selectedItems()) {
    item->setSelected(false);
  }
}

void MainCanvas::mousePressEvent(QGraphicsSceneMouseEvent *event) {
  if (this->state == CanvasState::State::DRAW) {
    switch (this->shape) {
    case CanvasState::Shapes::RECTANGLE:
      currentItem = new RectangleItem(this, event->scenePos().x(),
                                      event->scenePos().y(), 0, 0);
      this->addItem(currentItem);
      break;
    }
  }
  QGraphicsScene::mousePressEvent(event);
}

void MainCanvas::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
  if (this->state == CanvasState::State::DRAW && currentItem != nullptr) {
    currentItem->setBoundWidth(event->scenePos().x() - currentItem->getXPos());
    currentItem->setBoundHeight(event->scenePos().y() - currentItem->getYPos());
    currentItem->setSelected(true);
  }
  QGraphicsScene::mouseMoveEvent(event);
}

void MainCanvas::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
  this->shape = CanvasState::Shapes::NONE;
  this->state = CanvasState::State::MOVE;
  QGraphicsScene::mouseReleaseEvent(event);
}
