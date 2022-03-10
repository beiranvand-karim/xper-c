#include "cubic.h"

#include "basepoint.h"
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <controlpoint.h>

Cubic::Cubic(QPointF startPoint, QGraphicsItem *parent, QGraphicsScene *canvas)
    : BaseShapeItem(canvas), firstPointHandler(nullptr),
      lastPointHandler(nullptr), ctrlPointHandler1(nullptr),
      ctrlPointHandler2(nullptr), showPoints(true) {
  this->firstPoint = startPoint;
  this->setParentItem(parent);
}

Cubic::~Cubic() {}

QRectF Cubic::boundingRect() const { return this->shape().boundingRect(); }

void Cubic::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                  QWidget *widget) {
  Q_UNUSED(option)
  Q_UNUSED(widget)
  painter->save();
  painter->setRenderHint(QPainter::Antialiasing);
  painter->setPen(QPen(Qt::darkGray, 2));
  if (!this->shape().isEmpty()) {
    painter->drawPath(this->shape());
    if (this->isEnterEvent) {
      QPainterPath path = this->shape();
      BaseShapeItem::drawShapeOnHover(path, painter);
    }
  }
  painter->restore();
  painter->save();
  painter->setRenderHint(QPainter::Antialiasing);
  painter->setPen(QPen(Qt::darkYellow, 1));
  if (this->showPoints && !this->ctrlPoint1.isNull() &&
      !this->ctrlPoint2.isNull()) {
    if (this->ctrlPointHandler1->isVisible()) {
      painter->drawLine(this->firstPointHandler->getPos(),
                        this->ctrlPointHandler1->getPos());
    }
    if (this->ctrlPointHandler2->isVisible()) {
      painter->drawLine(this->lastPointHandler->getPos(),
                        this->ctrlPointHandler2->getPos());
    }
  }
  painter->restore();
}

QPainterPath Cubic::shape() const {
  QPainterPath path;
  if (firstPointHandler && lastPointHandler) {
    path.moveTo(firstPointHandler->getPos());
    if (ctrlPointHandler1 && ctrlPointHandler2)
      path.cubicTo(this->ctrlPointHandler1->getPos(),
                   this->ctrlPointHandler2->getPos(),
                   this->lastPointHandler->getPos());
    else
      path.lineTo(lastPointHandler->getPos());
  }
  return path;
}

void Cubic::setShowPointsHandlers(bool showPoints) {
  this->showPoints = showPoints;
  if (this->showPoints) {
    this->firstPointHandler->show();
    this->ctrlPointHandler1->show();
    this->ctrlPointHandler2->show();
  } else {
    this->firstPointHandler->hide();
    if (this->ctrlPointHandler1)
      this->ctrlPointHandler1->hide();
    if (this->ctrlPointHandler2)
      this->ctrlPointHandler2->hide();
  }
  this->update();
}

QPointF Cubic::getCtrlPoint1() const { return ctrlPoint1; }

QPointF Cubic::getCtrlPoint2() const { return ctrlPoint2; }

void Cubic::setFirstPoint(QPointF newItemPos) {
  BaseShapeItem::setFirstPoint(newItemPos);
  this->setFirstPointHandler(
      new BasePoint(newItemPos, this->parentItem(), this->mainCanvas));
}

void Cubic::setFirstPointHandler(BasePoint *newFirstPointHandler) {
  if (this->firstPointHandler) {
    delete this->firstPointHandler;
    this->firstPointHandler = nullptr;
  }
  firstPointHandler = newFirstPointHandler;
  this->update();
}

void Cubic::setShowCtrlPoint1(bool showCtrl1) {
  if (this->ctrlPointHandler1) {
    if (showCtrl1)
      this->ctrlPointHandler1->show();
    else
      this->ctrlPointHandler1->hide();
  }
  this->update();
}

void Cubic::setShowCtrlPoint2(bool showCtrl2) {
  if (this->ctrlPointHandler2) {
    if (showCtrl2)
      this->ctrlPointHandler2->show();
    else
      this->ctrlPointHandler2->hide();
  }
  this->update();
}

void Cubic::setCtrlPoint1(QPointF newCtrlPoint1) {
  ctrlPoint1 = newCtrlPoint1;
  this->setCtrlPointHandler1(
      new ControlPoint(this->ctrlPoint1, this->parentItem(), this->mainCanvas));
}

void Cubic::setCtrlPointHandler1(ControlPoint *newCtrlPointHandler1) {
  if (this->ctrlPointHandler1) {
    delete this->ctrlPointHandler1;
    this->ctrlPointHandler1 = nullptr;
  }
  ctrlPointHandler1 = newCtrlPointHandler1;
  this->update();
}

void Cubic::setCtrlPoint2(QPointF newCtrlPoint2) {
  ctrlPoint2 = newCtrlPoint2;
  this->setCtrlPointHandler2(
      new ControlPoint(ctrlPoint2, this->parentItem(), this->mainCanvas));
}

void Cubic::setCtrlPointHandler2(ControlPoint *newCtrlPointHandler2) {
  if (this->ctrlPointHandler2) {
    delete this->ctrlPointHandler2;
    this->ctrlPointHandler2 = nullptr;
  }
  ctrlPointHandler2 = newCtrlPointHandler2;
  this->update();
}

void Cubic::setSecondPoint(QPointF newLastPoint) {
  BaseShapeItem::setSecondPoint(newLastPoint);
  this->setSecondPointHandler(
      new BasePoint(newLastPoint, this->parentItem(), this->mainCanvas));
}

void Cubic::setSecondPointHandler(BasePoint *newLastPointHandler) {
  lastPointHandler = newLastPointHandler;
  this->update();
}

BasePoint *Cubic::getFirstPointHandler() const { return firstPointHandler; }
ControlPoint *Cubic::getCtrlPointHandler1() const { return ctrlPointHandler1; }
ControlPoint *Cubic::getCtrlPointHandler2() const { return ctrlPointHandler2; }
BasePoint *Cubic::getSecondPointHandler() const { return lastPointHandler; }
