#include "CustomButton.h"

CustomButton::CustomButton(Shape shape, QWidget * parent)
    : QPushButton(parent)
{
    _normalColor = new QColor(130, 130, 130);
    _currentColor = _normalColor;
    _clicColor = new QColor(150, 150, 150);
    _textColor = new QColor(0, 0, 0);
    _borderColor = new QColor(0, 0, 0);
    _font = QFont();
    _shape = shape;
    _rX = 40.0;
    _rY = 40.0;
    _gradientActive = true;
    _pixmap = QPixmap(0, 0);
    _pixmapOpacity = 1.0;
    _opacity = 1.0;
    _transparencyEffect = false;
}

CustomButton::CustomButton(const QString & text, Shape shape, QWidget * parent)
    : QPushButton(text, parent)
{
    _normalColor = new QColor(130, 130, 130);
    _currentColor = _normalColor;
    _clicColor = new QColor(150, 150, 150);
    _textColor = new QColor(0, 0, 0);
    _borderColor = new QColor(0, 0, 0);
    _font = QFont();
    _shape = shape;
    _rX = 40.0;
    _rY = 40.0;
    _gradientActive = true;
    _pixmap = QPixmap(0, 0);
    _pixmapOpacity = 1.0;
    _opacity = 1.0;
    _transparencyEffect = false;

}
CustomButton::CustomButton(const QIcon & icon, const QString & text, Shape shape, QWidget * parent)
    : QPushButton(icon, text, parent)
{
    _normalColor = new QColor(130, 130, 130);
    _currentColor = _normalColor;
    _clicColor = new QColor(150, 150, 150);
    _textColor = new QColor(0, 0, 0);
    _borderColor = new QColor(0, 0, 0);
    _font = QFont();
    _shape = shape;
    _rX = 40.0;
    _rY = 40.0;
    _gradientActive = true;
    _pixmap = QPixmap(0, 0);
    _pixmapOpacity = 1.0;
    _opacity = 1.0;
    _transparencyEffect = false;
}

QColor const *CustomButton::getCurrentColor() const
{
    return (_currentColor);
}

void          CustomButton::setCurrentColor(QColor const &currentColor)
{
    _currentColor->setRed(currentColor.red());
    _currentColor->setGreen(currentColor.green());
    _currentColor->setBlue(currentColor.blue());

    _clicColor->setRed(_currentColor->red() + 20);
    _clicColor->setGreen(_currentColor->green() + 20);
    _clicColor->setBlue(_currentColor->blue() + 20);
}

QColor const *CustomButton::getClicColor() const
{
    return (_clicColor);
}

void          CustomButton::setClicColor(QColor const &clicColor)
{
    _clicColor->setRed(clicColor.red());
    _clicColor->setGreen(clicColor.green());
    _clicColor->setBlue(clicColor.blue());
}
qreal        CustomButton::getOpacity() const
{
    return (_opacity);
}
void         CustomButton::setOpacity(qreal opacity)
{
    _opacity = opacity;
}

CustomButton::Shape   CustomButton::getShape() const
{
    return (_shape);
}

void    CustomButton::setShape(Shape shape)
{
    _shape = shape;
}

void    CustomButton::setRadius(qreal rX, qreal rY)
{
    _rX = rX;
    _rY = rY;
}

void    CustomButton::setRadius(QPointF const &radius)
{
    _rX = radius.x();
    _rY = radius.y();
}

void                    CustomButton::setRadiusX(qreal rX)
{
    _rX = rX;
}

void                    CustomButton::setRadiusY(qreal rY)
{
    _rY = rY;
}

qreal   CustomButton::getRadiusX() const
{
    return (_rX);
}

qreal   CustomButton::getRadiusY() const
{
    return (_rY);
}

QPointF CustomButton::getRadius() const
{
    QPointF radius = QPointF(_rX, _rY);

    return (radius);
}

bool    CustomButton::gradientActive() const
{
    return (_gradientActive);
}

void    CustomButton::setGradientActive(bool activation)
{
    _gradientActive = activation;
}
QPixmap const & CustomButton::getPixmap() const
{
    return (_pixmap);
}

void    CustomButton::setPixmap(QPixmap const &pix)
{
    _pixmap = pix;
}

void    CustomButton::setTextColor(QColor const &color)
{
    _textColor->setRed(color.red());
    _textColor->setGreen(color.green());
    _textColor->setBlue(color.blue());
}

QColor  const *CustomButton::getTextColor() const
{
    return (_textColor);
}
void    CustomButton::setBorderColor(QColor const &color)
{
    _borderColor->setRed(color.red());
    _borderColor->setGreen(color.green());
    _borderColor->setBlue(color.blue());
}
QColor  const *CustomButton::getBorderColor() const
{
    return (_borderColor);
}

QFont   const &CustomButton::getFont() const
{
    return (_font);
}

void   CustomButton::setFont(QFont const &font)
{
    _font = font;
}

void    CustomButton::setTransparencyEffect(bool effect)
{
    _transparencyEffect = effect;
}

bool    CustomButton::transparencyEffect() const
{
    return (_transparencyEffect);
}

void    CustomButton::setBold(bool bold)
{
    _font.setBold(bold);
}
void CustomButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter p(this);
    QRect r = QRect(0, 0, geometry().width() - 1, geometry().height() - 1);
    QTextOption option(Qt::AlignCenter);

    option.setAlignment(Qt::AlignCenter);
    p.setPen(QPen(*_borderColor));
    p.setFont(_font);

    if (_gradientActive && _pixmap.isNull())
    {
        QLinearGradient gradient(0, 0, 0, r.height());

        gradient.setColorAt(0.0, QColor(255, 255, 255));
        if (_transparencyEffect)
        {
            gradient.setColorAt(0.3, Qt::transparent);
            gradient.setColorAt(0.6, Qt::transparent);
        }
        else
        {
            gradient.setColorAt(0.3, *_currentColor);
            gradient.setColorAt(0.8, *_currentColor);
            gradient.setColorAt(0.9, QColor(255, 255, 255));
        }

        gradient.setColorAt(1.0, QColor(255, 255, 255));
        gradient.setSpread(QGradient::PadSpread);

        QBrush brush(gradient);

        brush.setStyle(Qt::LinearGradientPattern);
        p.setBrush(brush);
        p.setOpacity(_opacity);
    }
    else if (!_gradientActive && _pixmap.isNull())
    {
        p.setOpacity(_opacity);
        p.setBrush(QBrush(*_currentColor));
    }
    else
    {
        QBrush brush(_pixmap);

        p.setBrush(brush);
        p.setOpacity(_pixmapOpacity);
    }

    if (_shape == ROUND)
        p.drawRoundedRect(r, _rX, _rY);
    if (_shape == RECT)
        p.drawRect(r);

    QPixmap ico = icon().pixmap(iconSize());

    if (!ico.isNull())
        p.drawPixmap(r.width() / 14, (r.height() / 2) - 10, 20, 20, ico);

    p.setPen(*_textColor);

    p.drawText(r, text(), option);
    p.end();
}

void CustomButton::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        _currentColor = _clicColor;
        if (!_pixmap.isNull())
            _pixmapOpacity -= 0.5;
        repaint();
        emit clicked();
    }
}

void CustomButton::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        _currentColor = _normalColor;
        if (!_pixmap.isNull())
            _pixmapOpacity = 1.0;
        repaint();
    }
}

CustomButton::~CustomButton()
{

}



