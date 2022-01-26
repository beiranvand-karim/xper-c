#include "maincanvas.h"
#include "iostream"
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <ellipseitem.h>
#include <lineitem.h>
#include <polygonitem.h>
#include <rectangleitem.h>
#include <textitem.h>

using namespace std;

MainCanvas::MainCanvas(QObject *parent)
    : QGraphicsScene(parent), currentItem(nullptr),
      state(CanvasState::State::DRAW), shape(CanvasState::Shapes::NONE),
      mousePressed(false) {
  this->setSceneRect(0, 0, 1000, 1000);
  this->setBackgroundBrush(QBrush(QColor(135, 130, 100, 100)));
}

MainCanvas::~MainCanvas() {
  delete currentItem;
  if (!this->items().empty()) {
    for (auto item : this->items()) {
      delete item;
    }
  }
}

void MainCanvas::setCanvasState(CanvasState::Shapes shape,
                                CanvasState::State state) {
  this->shape = shape;
  this->state = state;
  currentItem = nullptr;
  for (auto item : this->selectedItems()) {
    item->setSelected(false);
  }
}

void MainCanvas::setItemsMovable(bool isMovable) {
  for (auto item : this->items()) {
    item->setFlag(QGraphicsItem::ItemIsMovable, isMovable);
    item->setFlag(QGraphicsItem::ItemIsFocusable, isMovable);
  }
}

void MainCanvas::setItemsSelectable(bool isSelectable) {
  for (auto item : this->items()) {
    item->setFlag(QGraphicsItem::ItemIsSelectable, isSelectable);
  }
}

void MainCanvas::mousePressEvent(QGraphicsSceneMouseEvent *event) {
  this->mousePressed = true;
  if (this->state == CanvasState::State::SCALE) {
    setItemsSelectable(false);
    setItemsMovable(false);
    return;
  } else if (this->state == CanvasState::State::MOVE) {
    setItemsSelectable(true);
    setItemsMovable(true);
    return QGraphicsScene::mousePressEvent(event);
  } else if (this->state == CanvasState::State::DRAW) {
    currentItem = this->onDrawShape(event->scenePos());
    this->addItem(currentItem);
    this->update();
    return QGraphicsScene::mousePressEvent(event);
  }
}

void MainCanvas::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
  if (mousePressed && this->state == CanvasState::State::DRAW &&
      currentItem != nullptr) {
    currentItem->setBoundWidth(event->scenePos().x() -
                               currentItem->getItemPos().x());
    currentItem->setBoundHeight(event->scenePos().y() -
                                currentItem->getItemPos().y());
    currentItem->setSelected(true);
    this->update();
    QGraphicsScene::mouseMoveEvent(event);
  }
  this->update();
  return QGraphicsScene::mouseMoveEvent(event);
}

void MainCanvas::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
  this->mousePressed = false;
  if (state == CanvasState::State::SCALE)
    return;
  // delete empty shapes just for now
  if (currentItem && currentItem->getBoundWidth() == 0 &&
      currentItem->getBoundHeight() == 0) {
    this->removeItem(currentItem);
    delete currentItem;
    currentItem = nullptr;
  }
  this->update();
  QGraphicsScene::mouseReleaseEvent(event);
}

BaseShapeItem *MainCanvas::onDrawShape(QPointF itemPos) {
  setItemsMovable(false);
  setItemsSelectable(true);
  switch (this->shape) {
  case CanvasState::Shapes::RECTANGLE:
    return new RectangleItem(itemPos);
  case CanvasState::Shapes::ELLIPSE:
    return new EllipseItem(itemPos);
  case CanvasState::Shapes::POLYGON:
    return new PolygonItem(itemPos);
  case CanvasState::NONE:
  case CanvasState::LINE:
    return new LineItem(itemPos);
    break;
  case CanvasState::IMAGE:
    break;
  case CanvasState::TEXT:
    return new TextItem(itemPos);
    currentItem->setSelected(true);
    break;
  case CanvasState::PEN:
    break;
  case CanvasState::PENCIL:
    break;
  default:
    break;
  }
  return nullptr;
}
