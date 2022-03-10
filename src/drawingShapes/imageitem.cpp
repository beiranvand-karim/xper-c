#include "imageitem.h"

#include <QFileDialog>
#include <QGraphicsScene>
#include <QObject>
#include <iostream>
using namespace std;

ImageItem::ImageItem(QPointF itemPos, QGraphicsScene *parent)
    : BaseShapeItem(parent), isImageSelected(false) {
  this->firstPoint = itemPos;
  this->secondPoint = itemPos;
}

ImageItem::~ImageItem() {
  delete this->pen;
  delete this->brush;
}

QRectF ImageItem::boundingRect() const {
  return QRectF(firstPoint, secondPoint).normalized();
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
  if (BaseShapeItem::validateItemInsertion()) {
    setImagePath();
    return this->isImageSelected;
  }
  return false;
}

void ImageItem::setImagePath() {
  fileDialog.setFileMode(QFileDialog::FileMode::ExistingFiles);
  fileDialog.setNameFilter("Images (*.png *.xpm *.jpg *.jpeg *.svg)");
  if (fileDialog.exec())
    imagePath = fileDialog.selectedFiles();
  if (!imagePath.isEmpty())
    this->isImageSelected = true;
  image.load(imagePath.first());
}
