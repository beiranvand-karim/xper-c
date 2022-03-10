#include "pentool.h"
#include "iostream"
#include <QEvent>
#include <QGraphicsScene>
#include <QGraphicsSceneHoverEvent>
#include <basepoint.h>

using namespace std;

PenTool::PenTool(QPointF itemPos, QGraphicsScene *parent)
    : BaseShapeItem(parent), penState(PenToolState::StraightLine),
      isDoubleClicked(false), stopDrawing(false) {
  this->setAcceptTouchEvents(true);
  this->firstPoint = itemPos;
  cubicList << new Cubic(this->firstPoint, this, this->mainCanvas);
  cubicList.last()->setFirstPoint(this->firstPoint);
}

PenTool::~PenTool() {
  delete this->pen;
  delete this->brush;
}

void PenTool::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                    QWidget *widget) {
  Q_UNUSED(option)
  Q_UNUSED(widget)
  if (!this->stopDrawing) {
    QPainterPath path;
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(*this->pen);
    path.moveTo(this->firstPoint);
    if (penState == PenToolState::CubicBezier) {
      painter->drawLine(this->firstPoint, this->ctrlPoint1);
      if (!this->secondPoint.isNull())
        path.cubicTo(this->ctrlPoint1, this->ctrlPoint2, this->secondPoint);
    } else if (penState == PenToolState::StraightLine)
      if (!this->secondPoint.isNull()) {
        path.lineTo(secondPoint);
      }
    painter->drawPath(path);
    painter->restore();
  }
  if (this->isSelected() && isDoubleClicked) {
    BaseShapeItem::drawBorders(this->boundingRect(), painter);
  } else if (this->isEnterEvent) {
    QPainterPath path = this->shape();
    BaseShapeItem::drawShapeOnHover(path, painter);
  }
}

QRectF PenTool::boundingRect() const { return this->shape().boundingRect(); }

QPainterPath PenTool::shape() const {
  QPainterPath path;
  for (auto cubic : cubicList) {
    path.addPath(cubic->shape());
  }
  return path;
}

void PenTool::setPenState(QPointF mousePos, bool mousePressed) {
  if (mousePressed) {
    this->penState = PenToolState::CubicBezier;
    this->ctrlPoint1 = mousePos;
    if (cubicList.length() > 1)
      this->symmetryOfCtrlPoint_1 = (2 * this->firstPoint) - this->ctrlPoint1;
    this->update();
  } else {
    this->ctrlPoint2 = mousePos;
    BaseShapeItem::setSecondPoint(mousePos);
  }
}

void PenTool::draw(QPointF p2) {
  // p2 == this->secondPoint = true
  if (penState == PenToolState::CubicBezier)
    drawCubic(p2);
  else if (penState == PenToolState::StraightLine)
    drawStraightLine(p2);
}

void PenTool::drawStraightLine(QPointF p2) {
  cubicList.last()->setSecondPoint(p2);
  prepareToDraw();
  // <= end draw line and create a new one
  Cubic *line = new Cubic(this->firstPoint, this, this->mainCanvas);
  line->setFirstPointHandler(cubicList.last()->getSecondPointHandler());
  cubicList << line;
  this->update();
}

void PenTool::drawCubic(QPointF p2) {
  cubicList.last()->setCtrlPoint2(this->ctrlPoint2);
  this->cubicList.last()->setSecondPoint(p2);
  prepareToDraw();
  // <= end draw cubic and create a new one
  Cubic *cubic = new Cubic(this->firstPoint, this, this->mainCanvas);
  cubic->setFirstPointHandler(cubicList.last()->getSecondPointHandler());
  cubicList << cubic;
}

void PenTool::prepareToDraw() {
  this->firstPoint = this->secondPoint;
  this->secondPoint = QPointF();
  this->ctrlPoint1 = QPointF();
  this->ctrlPoint2 = QPointF();
  this->penState = PenToolState::StraightLine;
  this->update();
}

bool PenTool::validateItemInsertion() {
  initControlPoints();
  this->update();
  return BaseShapeItem::validateItemInsertion();
}

void PenTool::initControlPoints() {
  if (penState == PenToolState::CubicBezier) {
    if (!this->ctrlPoint1.isNull())
      cubicList.last()->setCtrlPoint1(this->ctrlPoint1);
    if (!this->symmetryOfCtrlPoint_1.isNull() && this->cubicList.length() > 1) {
      // hide control point of cubic that is in two cubic before last
      if (this->cubicList.length() > 3) {
        cubicList[cubicList.length() - 3]->setShowCtrlPoint1(false);
        cubicList[cubicList.length() - 4]->setShowCtrlPoint2(false);
      }
      // show the second control point of cubic that is in one cubic before last
      Cubic *penultimateCubic = cubicList[cubicList.length() - 2];
      if (penultimateCubic->getCtrlPointHandler1()) {
        penultimateCubic->setCtrlPoint2(this->symmetryOfCtrlPoint_1);
        // integrate first control point of current cubic with second control
        // point of penultimate cubic
        setPointInSymmetry(penultimateCubic->getCtrlPointHandler2(),
                           cubicList.last()->getCtrlPointHandler1());
      }
    }
  }
}

void PenTool::setPointInSymmetry(ControlPoint *firstPoint,
                                 ControlPoint *secondPoint) {
  firstPoint->setSymmetryPoint(secondPoint);
  firstPoint->update();
  secondPoint->setSymmetryPoint(firstPoint);
  secondPoint->update();
}

void PenTool::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
  this->isDoubleClicked = true;
  this->setSelected(true);
  this->update();
  BaseShapeItem::mouseDoubleClickEvent(event);
}
