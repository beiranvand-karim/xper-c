#include "maincanvas.h"
#include "iostream"
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <ellipseitem.h>
#include <imageitem.h>
#include <lineitem.h>
#include <pencilitem.h>
#include <pentool.h>
#include <polygonitem.h>
#include <rectangleitem.h>
#include <textitemwrapper.h>

using namespace std;

MainCanvas::MainCanvas(QGraphicsView *view)
    : QGraphicsScene(view), view(view), currentItem(nullptr),
      currentPenTool(nullptr), state(CanvasState::State::DRAW),
      currentShapeType(CanvasState::Shapes::NONE), mousePressed(false) {
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
  if (state == CanvasState::State::DRAW)
    view->setCursor(QCursor(Qt::CrossCursor));
  this->currentShapeType = shape;
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
  if (this->state == CanvasState::State::DRAW) {
    auto newItem = this->onDrawShape(event->scenePos());
    if (currentItem != newItem) {
      currentItem = newItem;
      this->addItem(currentItem);
    }
  }
  this->update();
  return QGraphicsScene::mousePressEvent(event);
}

void MainCanvas::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
  if (this->currentShapeType == CanvasState::Shapes::PEN && currentPenTool)
    currentPenTool->setPenState(event->scenePos(), mousePressed);
  else if (mousePressed && this->state == CanvasState::State::DRAW) {
    if (currentItem) {
      currentItem->setSecondPoint(event->scenePos());
      currentItem->setSelected(true);
    }
  }
  this->update();
  return QGraphicsScene::mouseMoveEvent(event);
}

void MainCanvas::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
  this->mousePressed = false;
  this->lastShapeType = this->currentShapeType;
  if (currentItem && !currentItem->validateItemInsertion())
    deleteCurrentItem();
  this->update();
  QGraphicsScene::mouseReleaseEvent(event);
}
BaseShapeItem *MainCanvas::onDrawShape(QPointF itemPos) {
  setItemsMovable(false);
  setItemsSelectable(true);
  switch (this->currentShapeType) {
  case CanvasState::Shapes::RECTANGLE:
    return new RectangleItem(itemPos, this);
  case CanvasState::Shapes::ELLIPSE:
    return new EllipseItem(itemPos, this);
  case CanvasState::Shapes::POLYGON:
    return new PolygonItem(itemPos, this);
  case CanvasState::NONE:
  case CanvasState::LINE:
    return new LineItem(itemPos, this);
  case CanvasState::IMAGE:
    return new ImageItem(itemPos, this);
  case CanvasState::TEXT:
    return new TextItemWrapper(itemPos, this);
  case CanvasState::PEN: {
    if (currentItem && lastShapeType == CanvasState::Shapes::PEN) {
      currentPenTool->draw(itemPos);
      return currentItem;
    }
    currentPenTool = nullptr;
    currentItem = nullptr;
    currentPenTool = new PenTool(itemPos, this);
    return currentPenTool;
  }
  case CanvasState::PENCIL:
    return new PencilItem(itemPos, this);
  case CanvasState::FRAME:
    break;
  default:
    break;
  }
  return nullptr;
}

void MainCanvas::deleteCurrentItem() {
  this->removeItem(currentItem);
  delete currentItem;
  currentItem = nullptr;
}
