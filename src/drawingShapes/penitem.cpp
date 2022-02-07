#include "penitem.h"
#include "iostream"

#include <QEvent>
#include <QGraphicsSceneHoverEvent>
using namespace std;

PenItem::PenItem(QPointF itemPos, QGraphicsScene *parent)
    : BaseShapeItem(parent), isDoubleClicked(false),
      shouldDrawControlLine(false), shouldDrawTempPath(false),
      isReleaseBtn(false), isPathClosed(false) {
  this->setAcceptTouchEvents(true);
  this->firstPoint = itemPos;
  this->lastPoint = firstPoint;
  this->ctrlLine.setP1(itemPos);
  pointList << this->firstPoint;
}

PenItem::~PenItem() {
  delete this->pen;
  delete this->brush;
}
QRectF PenItem::boundingRect() const {
  if (path.isEmpty())
    return QRectF(this->firstPoint, this->lastPoint).normalized();
  else {
    return path.boundingRect();
  }
}

void PenItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                    QWidget *widget) {
  Q_UNUSED(option)
  Q_UNUSED(widget)
  QPainterPath cubicTemporaryPath;
  painter->save();
  painter->setRenderHint(QPainter::Antialiasing);
  if (shouldDrawControlLine) {
    painter->setPen(QPen(Qt::magenta, 1));
    painter->drawLine(this->ctrlLine);
  }
  painter->restore();
  painter->save();
  painter->setRenderHint(QPainter::Antialiasing);
  painter->setPen(*this->pen);
  if (shouldDrawTempPath) {
    cubicTemporaryPath.moveTo(this->firstPoint);
    cubicTemporaryPath.cubicTo(this->firstPoint, this->lastPoint, endPoint);
    painter->drawPath(cubicTemporaryPath);
  }
  painter->drawPath(path);
  painter->restore();

  if (this->isSelected() && (isDoubleClicked || isPathClosed)) {
    this->shouldDrawTempPath = false;
    this->shouldDrawControlLine = false;
    BaseShapeItem::drawBorders(this->boundingRect(), painter);
  } else if (this->isEnterEvent) {
    BaseShapeItem::drawShapeOnHover(path, painter);
  }
}

bool PenItem::validateItemInsertion() {
  this->isReleaseBtn = true;
  if (this->lastPoint.isNull())
    return false;
  this->update();
  return true;
}

/* draw control line on mouse press && mouse move and
 *  draw temporary path on mouse move to end point and be ready to draw new
 * point before drawLineToNewPoint() func called
 */
void PenItem::setLastPoint(QPointF newLastPoint) {
  if (!isPathClosed) {
    if (!this->isReleaseBtn) {
      BaseShapeItem::setLastPoint(newLastPoint);
      ctrlLine.setP2(this->lastPoint);
      this->shouldDrawControlLine = true;
      this->update();
    } else {
      this->shouldDrawTempPath = true;
      this->endPoint = newLastPoint;
      this->update();
    }
  }
}

void PenItem::checkIsPathClosed(QPointF &newPoint) {
  for (auto point : pointList) {
    if (qAbs(newPoint.x() - point.x()) <= 4 &&
        qAbs(newPoint.y() - point.y()) <= 4) {
      newPoint = point;
      onPathClosed();
      this->update();
      return;
    }
  }
}

void PenItem::onPathClosed() {
  this->isPathClosed = true;
  this->shouldDrawControlLine = false;
  this->shouldDrawTempPath = false;
  this->setSelected(true);
  this->update();
}

bool PenItem::getIsControlLineDrawn() const {
  if (this->ctrlLine.isNull())
    return false;
  return true;
}

// draw cubic to new point with mouse press in scene
void PenItem::drawLineToNewPoint(QPointF p2) {
  if (!isPathClosed) {
    path.moveTo(this->firstPoint);
    checkIsPathClosed(endPoint);
    path.cubicTo(this->firstPoint, this->lastPoint, this->endPoint);
    this->update();
    pointList << this->endPoint;
    this->firstPoint = endPoint;
    this->lastPoint = p2;
    this->endPoint = p2;
  }
}

void PenItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
  isDoubleClicked = true;
  setSelected(true);
  this->update();
  QGraphicsItem::mouseDoubleClickEvent(event);
}
