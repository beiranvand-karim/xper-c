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
    : BaseShapeItem(parent), customTextGraphics(nullptr) {
  this->firstPoint = itemPos;
  this->lastPoint = itemPos;
  customTextGraphics = new CustomTextGraphics(itemPos, this, parent);
  this->setSelected(true);
}

QRectF TextItemWrapper::boundingRect() const {
  int boundWidth = lastPoint.x() - firstPoint.x();
  int boundHeight = lastPoint.y() - firstPoint.y();
  int maxWitdth =
      max(customTextGraphics->boundingRect().width(), double(boundWidth));
  int maxHeight =
      max(customTextGraphics->boundingRect().height(), double(boundHeight));
  return QRectF(customTextGraphics->x(), customTextGraphics->y(), maxWitdth,
                maxHeight);
}

void TextItemWrapper::paint(QPainter *painter,
                            const QStyleOptionGraphicsItem *option,
                            QWidget *widget) {
  Q_UNUSED(option)
  Q_UNUSED(widget)
  QPainterPath path;
  path.addRect(this->boundingRect());
  if (this->isSelected()) {
    this->customTextGraphics->setFocus();
    BaseShapeItem::drawBorders(this->boundingRect(), painter);
  } else if (this->isEnterEvent) {
    BaseShapeItem::drawShapeOnHover(path, painter);
  }
}

bool TextItemWrapper::validateItemInsertion() {
  if (!BaseShapeItem::validateItemInsertion())
    return false;
  return true;
}
