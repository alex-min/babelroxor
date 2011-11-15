#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H

#include <QPushButton>
#include <QtGui/QPainter>
#include <QtGui/QMouseEvent>
#include <QtGui/QBitmap>
#include <QtGui/QGraphicsOpacityEffect>
#include <QtGui/QFont>


class CustomButton : public QPushButton
{
    Q_OBJECT

public:
    enum Shape {ROUND, RECT};

    CustomButton(Shape shape = RECT, QWidget * parent = 0);
    CustomButton(const QString & text, Shape shape = RECT, QWidget * parent = 0);
    CustomButton(const QIcon & icon, const QString & text, Shape shape = RECT, QWidget * parent = 0);
    QColor const *getCurrentColor() const;
    void          setCurrentColor(QColor const &currentColor);
    QColor const *getClicColor() const;
    void          setClicColor(QColor const &clicColor);
    CustomButton::Shape   getShape() const;
    void                    setShape(Shape shape);
    void                    setRadius(qreal rX, qreal rY);
    void                    setRadius(QPointF const &radius);
    void                    setRadiusX(qreal rX);
    void                    setRadiusY(qreal rY);
    qreal                   getRadiusX() const;
    qreal                   getRadiusY() const;
    QPointF                 getRadius() const;
    bool                    gradientActive() const;
    void                    setGradientActive(bool activation);
    QPixmap const &         getPixmap() const;
    void                    setPixmap(QPixmap const &pix);
    QColor  const *         getTextColor() const;
    void                    setTextColor(QColor const &color);
    QColor  const *         getBorderColor() const;
    void                    setBorderColor(QColor const &color);
    QFont   const &         getFont() const;
    void                    setFont(QFont const &font);
    qreal                   getOpacity() const;
    void                    setOpacity(qreal opacity);
    void                    setTransparencyEffect(bool effect);
    bool                    transparencyEffect() const;
    void                    setBold(bool bold);
    ~CustomButton();

protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void mousePressEvent(QMouseEvent *e);
    virtual void mouseReleaseEvent(QMouseEvent *e);
private:
    QColor  *_currentColor;
    QColor  *_clicColor;
    QColor  *_normalColor;
    QColor  *_textColor;
    QColor  *_borderColor;
    QFont   _font;
    Shape   _shape;
    qreal   _rX;
    qreal   _rY;
    bool    _gradientActive;
    QPixmap _pixmap;
    qreal   _pixmapOpacity;
    qreal   _opacity;
    bool    _transparencyEffect;
};

#endif // CUSTOMBUTTON_H
