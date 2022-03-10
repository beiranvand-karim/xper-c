#ifndef IMAGEITEM_H
#define IMAGEITEM_H

#include "baseshapeitem.h"

#include <QFileDialog>
#include <QList>

class ImageItem : public BaseShapeItem {
public:
  ImageItem(QPointF itemPos, QGraphicsScene *parent = nullptr);
  ~ImageItem();

  // QGraphicsItem interface
public:
  QRectF boundingRect() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;

  // BaseShapeItem interface
public:
  bool validateItemInsertion() override;

public:
  void setImagePath();

private:
  QList<QString> imagePath;
  QImage image;
  QFileDialog fileDialog;
  bool isImageSelected;
};
#endif // IMAGEITEM_H
