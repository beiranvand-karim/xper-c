#include "rectangleitem.h"
#include <maincanvas.h>

#include <QColor>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <qwidget.h>

#include "iostream"
using namespace std;

RectangleItem::~RectangleItem() {
  delete this->pen;
  delete this->brush;
}
RectangleItem::RectangleItem(MainCanvas *canvas, int x, int y, int width,
                             int height)
    : radiusX(0), radiusY(0) {
  this->setFlag(ItemIsSelectable, true);
  this->setFlag(ItemIsMovable, true);
  this->xPos = x;
  this->yPos = y;
  // critical bug in next line
  //  this->setPos(x, y);
  this->canvas = canvas;
  this->boundWidth = width;
  this->boundHeight = height;
  this->brush = new QBrush(Qt::gray);
  this->pen = new QPen(Qt::gray);
  this->show();
}

QRectF RectangleItem::boundingRect() const {
  return QRectF(this->xPos, this->yPos, this->boundWidth, this->boundHeight);
}

void RectangleItem::paint(QPainter *painter,
                          const QStyleOptionGraphicsItem *option,
                          QWidget *widget) {
  if (this->isSelected()) {
    painter->save();
    QPen pen(Qt::blue);
    pen.setStyle(Qt::DotLine);
    pen.setWidth(3);
    painter->setPen(pen);
    painter->drawRoundedRect(this->boundingRect(), this->radiusX,
                             this->radiusY);
    painter->restore();
  }
  painter->save();
  painter->setBrush(*this->brush);
  painter->setPen(*this->pen);
  painter->drawRoundedRect(this->boundingRect(), this->radiusX, this->radiusY);
  painter->restore();
}

void RectangleItem::setBrushColor(QColor color) {
  this->brush->setColor(color);
  this->updateItem();
}

void RectangleItem::setPenColor(const QColor newPenColor) {
  this->pen->setColor(newPenColor);
  this->updateItem();
}

void RectangleItem::setIsFill(bool isFill) {
  this->isFill = isFill;
  this->updateItem();
}

void RectangleItem::setBorderWidth(int borderWidth) {
  this->borderWidth = borderWidth;
  this->updateItem();
  this->canvas->update();
}

void RectangleItem::setBoundWidth(int boundWidth) {
  this->boundWidth = boundWidth;
  this->updateItem();
}

void RectangleItem::setBoundHeight(int boundHeight) {
  this->boundHeight = boundHeight;
  this->updateItem();
}

void RectangleItem::setPenWidth(int penWidth) {
  this->penWidth = penWidth;
  this->updateItem();
  this->canvas->update();
}

void RectangleItem::setCanvas(MainCanvas *canvas) {
  this->canvas = canvas;
  this->updateItem();
}

int RectangleItem::getXPos() { return this->xPos; }

void RectangleItem::setXPos(int newXPos) {
  this->xPos = newXPos;
  this->updateItem();
}

int RectangleItem::getYPos() { return this->yPos; }

void RectangleItem::setYPos(int newYPos) {
  this->yPos = newYPos;
  this->updateItem();
}

void RectangleItem::updateItem() {
  this->update();
  this->canvas->update();
}
