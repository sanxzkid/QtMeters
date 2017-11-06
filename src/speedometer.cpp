#include "speedometer.h"

Speedometer::Speedometer(QWidget *parent)
    : QWidget(parent)
{
    int size = 1000;
    calculateMeasure(size);
}

Speedometer::~Speedometer()
{
    return;
}

void Speedometer::paintEvent(QPaintEvent *)
{
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);

    drawTitle();
    drawLabel();
    drawDisplay();
    drawMeter();
    drawRange();
    drawScale();
    drawPointer();

    painter.end();
}

void Speedometer::drawTitle()
{
    painter.save();
    painter.setBrush(QColor("white"));

    QFont consolasFontDisplay("Consolas");
    consolasFontDisplay.setPixelSize(dynamic.displayFontSize);
    painter.setFont(consolasFontDisplay);

    QRect baseUnit(dynamic.meterInPos, dynamic.sizeOut * 0.04, dynamic.sizeOut - 2 * dynamic.meterInPos, dynamic.displayHeight);
    painter.drawText(baseUnit, Qt::AlignCenter, parameter.title);

    painter.restore();
}

void Speedometer::drawLabel()
{
    painter.save();
    QFont consolasFont("Consolas");
    consolasFont.setPixelSize(dynamic.labelFontSize);
    painter.setFont(consolasFont);

    float start = parameter.scale.start;
    float pass = (parameter.scale.end - parameter.scale.start) / 10;

    QString step[11];

    for (int x = 0; x < 11; x++)
    {
        if (start < 999.99)
        {
            step[x].sprintf("%.1f", start);
        }
        else
        {
            step[x].sprintf("%.0f", start);
        }
        start += pass;
    }

    painter.drawText(QRect(dynamic.labelP1, dynamic.labelP12, dynamic.labelWidth, dynamic.labelHeight), Qt::AlignCenter, step[0]);
    painter.drawText(QRect(dynamic.labelP2, dynamic.labelP13, dynamic.labelWidth, dynamic.labelHeight), Qt::AlignCenter, step[1]);
    painter.drawText(QRect(dynamic.labelP3, dynamic.labelP7, dynamic.labelWidth, dynamic.labelHeight), Qt::AlignCenter, step[2]);
    painter.drawText(QRect(dynamic.labelP2, dynamic.labelP5, dynamic.labelWidth, dynamic.labelHeight), Qt::AlignCenter, step[3]);
    painter.drawText(QRect(dynamic.labelP1, dynamic.labelP4, dynamic.labelWidth, dynamic.labelHeight), Qt::AlignCenter, step[4]);
    painter.drawText(QRect(dynamic.labelP8, dynamic.labelP6, dynamic.labelWidth, dynamic.labelHeight), Qt::AlignCenter, step[5]);
    painter.drawText(QRect(dynamic.labelP9, dynamic.labelP4, dynamic.labelWidth, dynamic.labelHeight), Qt::AlignCenter, step[6]);
    painter.drawText(QRect(dynamic.labelP10, dynamic.labelP5, dynamic.labelWidth, dynamic.labelHeight), Qt::AlignCenter, step[7]);
    painter.drawText(QRect(dynamic.labelP11, dynamic.labelP7, dynamic.labelWidth, dynamic.labelHeight), Qt::AlignCenter, step[8]);
    painter.drawText(QRect(dynamic.labelP10, dynamic.labelP13, dynamic.labelWidth, dynamic.labelHeight), Qt::AlignCenter, step[9]);
    painter.drawText(QRect(dynamic.labelP9, dynamic.labelP12, dynamic.labelWidth, dynamic.labelHeight), Qt::AlignCenter, step[10]);

    painter.restore();
}

void Speedometer::drawDisplay()
{
    painter.save();
    painter.setBrush(QColor("white"));

    QFont consolasFontDisplay("Consolas");
    consolasFontDisplay.setPixelSize(dynamic.displayFontSize);
    painter.setFont(consolasFontDisplay);

    QRect baseValue(dynamic.displayP1, dynamic.displayP2, dynamic.displayWidth, dynamic.displayHeight);
    painter.drawRect(baseValue);
    QString value;
    value.sprintf("%.1f", parameter.scale.start + (parameter.percentage * (parameter.scale.end - parameter.scale.start) / 100));
    painter.drawText(baseValue, Qt::AlignCenter, value);

    QRect baseUnit(dynamic.displayP1, dynamic.displayP2 + dynamic.displayHeight, dynamic.displayWidth, dynamic.displayHeight);
    painter.drawText(baseUnit, Qt::AlignCenter, parameter.unit);

    painter.restore();
}

void Speedometer::drawMeter()
{
    painter.save();
    painter.setBrush(QColor(255, 255, 255));

    QPainterPath meterPath;
    QRectF qRect(dynamic.meterOutPos, dynamic.meterOutPos, dynamic.meterOutDia, dynamic.meterOutDia);
    meterPath.arcMoveTo(qRect, 240);
    meterPath.arcTo(qRect, 240, -300);
    meterPath.arcTo(dynamic.meterInPos, dynamic.meterInPos, dynamic.meterInDia, dynamic.meterInDia, -60, 300);
    meterPath.closeSubpath();
    painter.translate(dynamic.deslocation);
    painter.drawPath(meterPath);
    painter.restore();
}

void Speedometer::drawRange()
{
    for (int i = 0; i < listRange.length(); i++)
    {
        Range tmpRange = listRange.value(i);
        painter.setBrush(tmpRange.color);

        int startAngle = 240 - (3 * tmpRange.start);
        int endAngle = 240 - (3 * tmpRange.end);
        int difAngle = endAngle - startAngle;

        painter.save();
        QPainterPath meterPath;
        QRectF qRect(dynamic.meterOutPos, dynamic.meterOutPos, dynamic.meterOutDia, dynamic.meterOutDia); //+1 and -2 to make 3D appearence
        meterPath.arcMoveTo(qRect, startAngle);
        meterPath.arcTo(qRect, startAngle, difAngle);
        meterPath.arcTo(dynamic.meterInPos, dynamic.meterInPos, dynamic.meterInDia, dynamic.meterInDia, endAngle, -difAngle); //+1 and -2 to make 3D appearence
        meterPath.closeSubpath();
        painter.translate(dynamic.deslocation);
        painter.drawPath(meterPath);
        painter.restore();
    }
}

void Speedometer::drawScale()
{
    painter.save();
    painter.translate(dynamic.center + dynamic.deslocation);
    painter.rotate(120.0);
    for (int i = 0; i <= 100; ++i)
    {
        if (i % 10 == 0)
        {
            painter.drawLine(dynamic.scalePos, 0, dynamic.scaleSLenght, 0);
        }
        else if (i % 5 == 0)
        {
            painter.drawLine(dynamic.scalePos, 0, dynamic.scaleMLenght, 0);
        }
        else
        {
            painter.drawLine(dynamic.scalePos, 0, dynamic.scaleHLenght, 0);
        }
        painter.rotate(3.0);
    }
    painter.restore();
}

void Speedometer::drawPointer()
{
    painter.save();
    painter.translate(dynamic.center + dynamic.deslocation);

    float rad = dynamic.pointerRadius;
    painter.setBrush(QColor(0, 0, 0));
    painter.drawEllipse(-rad / 2, -rad / 2, rad, rad);

    static const QPoint pointer[4] = {
        QPoint(rad * 0.1, rad * 0.7),
        QPoint(-rad * 0.1, rad * 0.7),
        QPoint(-rad * 0.1, -dynamic.pointerSize),
        QPoint(rad * 0.1, -dynamic.pointerSize)};

    painter.setBrush(QColor(255, 0, 0));
    painter.rotate(-150.0 + 3 * parameter.percentage);
    painter.drawConvexPolygon(pointer, 4);
    painter.restore();
}

void Speedometer::calculateMeasure(int size)
{
    dynamic.sizeOut = size;
    dynamic.sizeIn = dynamic.sizeOut / 1.4;

    dynamic.center = QPointF(dynamic.sizeOut * 0.5, dynamic.sizeOut * 0.5);
    dynamic.deslocation = QPointF(dynamic.sizeOut * 0.00, dynamic.sizeOut * 0.05);

    dynamic.meterOutPos = dynamic.sizeOut * 0.10;
    dynamic.meterOutDia = dynamic.sizeOut * 0.80;
    dynamic.meterInPos = dynamic.sizeOut * 0.14;
    dynamic.meterInDia = dynamic.sizeOut * 0.72;

    double cscale = 0.35;
    dynamic.scalePos = dynamic.sizeOut * cscale;
    dynamic.scaleSLenght = dynamic.sizeOut * (cscale - 0.05);
    dynamic.scaleMLenght = dynamic.sizeOut * (cscale - 0.03);
    dynamic.scaleHLenght = dynamic.sizeOut * (cscale - 0.01);

    dynamic.pointerSize = dynamic.sizeOut * 0.42;
    dynamic.pointerRadius = dynamic.sizeOut * 0.07;

    dynamic.labelFontSize = dynamic.sizeOut * 0.032;
    dynamic.labelWidth = dynamic.sizeOut * 0.1;
    dynamic.labelHeight = dynamic.sizeOut * 0.04;

    dynamic.labelP1 = dynamic.sizeOut * 0.33;
    dynamic.labelP2 = dynamic.sizeOut * 0.23;
    dynamic.labelP3 = dynamic.sizeOut * 0.20;
    dynamic.labelP4 = dynamic.sizeOut * 0.32 - dynamic.labelHeight / 2;
    dynamic.labelP5 = dynamic.sizeOut * 0.42 - dynamic.labelHeight / 2;
    dynamic.labelP6 = dynamic.sizeOut * 0.28 - dynamic.labelHeight / 2;
    dynamic.labelP7 = 0.55 * (dynamic.sizeOut - dynamic.labelHeight);
    dynamic.labelP8 = 0.5 * (dynamic.sizeOut - dynamic.labelWidth);
    dynamic.labelP9 = dynamic.sizeOut - dynamic.labelWidth - dynamic.labelP1;
    dynamic.labelP10 = dynamic.sizeOut - dynamic.labelWidth - dynamic.labelP2;
    dynamic.labelP11 = dynamic.sizeOut - dynamic.labelWidth - dynamic.labelP3;
    dynamic.labelP12 = dynamic.sizeOut - dynamic.sizeOut * 0.21 - dynamic.labelHeight / 2;
    dynamic.labelP13 = dynamic.sizeOut - dynamic.sizeOut * 0.32 - dynamic.labelHeight / 2;

    dynamic.displayFontSize = dynamic.sizeOut * 0.06;
    dynamic.displayWidth = dynamic.sizeOut * 0.2;
    dynamic.displayHeight = dynamic.sizeOut * 0.06;
    dynamic.displayP1 = 0.5 * (dynamic.sizeOut - dynamic.displayWidth);
    dynamic.displayP2 = dynamic.sizeOut * 0.86;

    setFixedSize(dynamic.sizeOut, dynamic.sizeOut);
}

void Speedometer::setParameter(QString title, float percentage, float startScale, float endScale, QString unit)
{
    setTitle(title);
    setPercentage(percentage);
    setScale(startScale, endScale);
    setUnit(unit);
}

void Speedometer::setTitle(QString title)
{
    parameter.title = title;
}

void Speedometer::setPercentage(float percentage)
{
    parameter.percentage = percentage;
}

void Speedometer::setScale(float startScale, float endScale)
{
    parameter.scale.start = startScale;
    parameter.scale.end = endScale;
}

void Speedometer::setUnit(QString unit)
{
    parameter.unit = unit;
}

void Speedometer::addRange(float startRange, float endRange, QColor color)
{
    Range range = {startRange, endRange, color};
    listRange.append(range);
}

void Speedometer::setRangeStart(int index, float startRange)
{
    listRange[index].start = startRange;
}

void Speedometer::setRangeEnd(int index, float endRange)
{
    listRange[index].end = endRange;
}

void Speedometer::setRangeColor(int index, QColor color)
{
    listRange[index].color = color;
}

void Speedometer::setSize(int size)
{
    calculateMeasure(size);
}
