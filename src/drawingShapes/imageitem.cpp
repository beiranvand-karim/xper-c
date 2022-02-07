#include "imageitem.h"

#include <QFileDialog>
#include <QGraphicsScene>
#include <QObject>
#include <iostream>
using namespace std;

ImageItem::ImageItem(QPointF itemPos, QGraphicsScene *parent)
    : BaseShapeItem(parent) {
  this->firstPoint = itemPos;
  this->lastPoint = itemPos;
}

ImageItem::~ImageItem() {
  delete this->pen;
  delete this->brush;
}

QRectF ImageItem::boundingRect() const {
  return QRectF(firstPoint, lastPoint).normalized();
}

void ImageItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                      QWidget *widget) {
  Q_UNUSED(option)
  Q_UNUSED(widget)
  QPainterPath path;
  path.addRect(this->boundingRect());
  painter->save();
  painter->setRenderHint(QPainter::Antialiasing);
  if (!image.isNull())
    painter->drawImage(this->boundingRect(), image);
  painter->restore();
  if (this->isSelected())
    BaseShapeItem::drawBorders(this->boundingRect(), painter);
  else if (this->isEnterEvent)
    BaseShapeItem::drawShapeOnHover(path, painter);
}

bool ImageItem::validateItemInsertion() {
  if (isImageInserted())
    return true;
  return false;
}

bool ImageItem::isImageInserted() {
  if (!BaseShapeItem::validateItemInsertion())
    return false;
  fileDialog.setFileMode(QFileDialog::FileMode::ExistingFiles);
  fileDialog.setNameFilter("Images (*.png *.xpm *.jpg *.jpeg *.svg)");
  if (fileDialog.exec())
    imagePath = fileDialog.selectedFiles();
  if (imagePath.isEmpty())
    return false;
  image.load(imagePath.first());
  return true;
}
