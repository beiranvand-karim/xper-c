#include "textitemwrapper.h"
#include <QBrush>
#include <QCursor>
#include <QGraphicsScene>
#include <QPainter>
#include <QPen>
#include <QTextDocument>
#include <iostream>

using namespace std;

TextItemWrapper::~TextItemWrapper() {
  delete this->pen;
  delete this->brush;
  delete this->customTextGraphics;
}

TextItemWrapper::TextItemWrapper(QPointF itemPos, QGraphicsScene *parent)
    : BaseShapeItem(parent), parentScene(parent), customTextGraphics(nullptr) {
  this->firstPoint = itemPos;
  this->secondPoint = this->firstPoint;
  this->setSelected(true);
}

QRectF TextItemWrapper::boundingRect() const {
  if (customTextGraphics) {
    int boundWidth = secondPoint.x() - firstPoint.x();
    int boundHeight = secondPoint.y() - firstPoint.y();
    int maxWitdth =
        max(customTextGraphics->boundingRect().width(), double(boundWidth));
    int maxHeight =
        max(customTextGraphics->boundingRect().height(), double(boundHeight));
    return QRectF(customTextGraphics->x(), customTextGraphics->y(), maxWitdth,
                  maxHeight);
  }
  return QRectF(this->firstPoint, this->secondPoint).normalized();
}

void TextItemWrapper::paint(QPainter *painter,
                            const QStyleOptionGraphicsItem *option,
                            QWidget *widget) {
  Q_UNUSED(option)
  Q_UNUSED(widget)
  QPainterPath path;
  path.addRect(this->boundingRect());
  if (this->isSelected()) {
    if (customTextGraphics)
      this->customTextGraphics->setFocus();
    BaseShapeItem::drawBorders(this->boundingRect(), painter);
  } else if (this->isEnterEvent) {
    BaseShapeItem::drawShapeOnHover(path, painter);
  }
}

bool TextItemWrapper::validateItemInsertion() {
  if (BaseShapeItem::validateItemInsertion()) {
    customTextGraphics =
        new CustomTextGraphics(this->firstPoint, this, parentScene);
    return true;
  }
  return false;
}
