#include "thermometer.h"

Thermometer::Thermometer(QWidget *parent)
    : QWidget(parent) 
{
	calculateMeasure(550, 100);	
}

Thermometer::~Thermometer()
{    
    return;
}

void Thermometer::paintEvent(QPaintEvent *)
{
	painter.begin(this);

	drawTitle();
	drawUnit();
	drawLabel();
	drawDisplay();
	drawScale();
	drawMeter();
	drawRange();
	drawPointer();

	painter.end();
}

void Thermometer::drawTitle()
{
	painter.translate(10,10);
    painter.save(); 
	QFont consolasFont("Consolas");
	consolasFont.setPixelSize(20);
	painter.setFont(consolasFont);
	painter.drawText(QRect(0, 0, 125, 20), Qt::AlignCenter, parameter.title);
    painter.restore();	
}

void Thermometer::drawUnit()
{
	painter.translate(0,20);
    painter.save(); 
	QFont consolasFont("Consolas");
	consolasFont.setPixelSize(15);
	painter.setFont(consolasFont);
	painter.drawText(QRect(0, 0, 125, 15), Qt::AlignRight, parameter.unit);
    painter.restore();	
}

void Thermometer::drawLabel()
{
	painter.translate(0,10);
    painter.save();
	
	QFont consolasFont("Consolas");
	consolasFont.setPixelSize(15);
	painter.setFont(consolasFont);

	float start = parameter.scale.start;
	float pass = (parameter.scale.end - parameter.scale.start) / 10;

	QString step;
	for (int x = 0; x <= 10; x++) {
		if (start < 999.99) {
			step.sprintf("%.1f", start);
		}
		else {
			step.sprintf("%.0f", start);
		}
		painter.drawText(QRect(0, 500 - (x * 50), 50, 20),Qt::AlignRight, step);

		start += pass;
	}

    painter.restore();	
}

void Thermometer::drawScale()
{
	painter.translate(10+50+5+5,10);
    painter.save();

	QPainterPath scalePath;
	float posX = 0;
	float posY = 0;

	for (int i = 0; i <= 100; i++) {
		scalePath.moveTo(posX, posY);	
		if (i % 10 == 0) {
			scalePath.lineTo(posX - 15, posY);
		}
		else if (i % 5 == 0) {
			scalePath.lineTo(posX - 10, posY);
		}
		else {
			scalePath.lineTo(posX - 5, posY);
		}
		posY += 5;
	}
	painter.drawPath(scalePath);
    painter.restore();
}

void Thermometer::drawDisplay()
{
    painter.save();
	painter.translate(0,525);
	painter.setBrush(QColor("white"));

	QFont consolasFont("Consolas");
	consolasFont.setPixelSize(25);
	painter.setFont(consolasFont);

	QString value;
	value.sprintf("%.1f", parameter.scale.start + (parameter.percentage * (parameter.scale.end - parameter.scale.start) / 100));
	painter.drawRect(QRect(0, 0, 125, 25));
	painter.drawText(QRect(0, 0, 125, 25), Qt::AlignCenter, value);
    painter.restore();	
}

void Thermometer::drawMeter()
{
	painter.translate(5,0);

    painter.save();
	painter.setBrush(QColor("white"));

	QRectF meterRectangle(0, 0, 50, 500);
	QPainterPath meterPath;
	meterPath.addRect(meterRectangle);

	painter.drawPath(meterPath);
    painter.restore();	
}

void Thermometer::drawRange()
{
	for (int i = 0; i < listRange.length() ; i++)
	{		
		Range tmpRange = listRange.value(i);
		painter.setBrush(tmpRange.color);
		
		int startPos = 500 - (5 * tmpRange.start);
		int endPos = 500 - (5 * tmpRange.end);
		int difPos = endPos - startPos;
		
		painter.save();

		QRectF rangeRectangle(0, startPos, 50, difPos);
		QPainterPath rangePath;
		rangePath.addRect(rangeRectangle);

		painter.drawPath(rangePath);
		painter.restore();
	}
}

void Thermometer::drawPointer()
{	
    painter.save();
	painter.setBrush(QColor("red"));
	
	QPainterPath pointerPath;

	QRectF pointerRectangle(0 - 10, 0 - 1, 50 + 12, 3);
	pointerPath.addRect(pointerRectangle);

	painter.translate(0, 500 - 5 * parameter.percentage);
	painter.drawPath(pointerPath);
    painter.restore();
}

void Thermometer::calculateMeasure(float width, float height)
{
	width = 150; height = 600;
	dynamic.width = width;
	dynamic.height = height;
	dynamic.borderSize = dynamic.width * 0.1;

	dynamic.labelStartPos = 0;
	dynamic.labelFontSize;
	dynamic.labelWidth = dynamic.width / 2.4;
    dynamic.labelHeight = dynamic.height * 0.04;

	setFixedSize(dynamic.width, dynamic.height);
}

void Thermometer::setParameter(QString title, float percentage, float startScale, float endScale, QString unit)
{
	setTitle(title);
	setPercentage(percentage);
	setScale(startScale, endScale);
	setUnit(unit);
}

void Thermometer::setTitle(QString title)
{
	parameter.title = title;
}

void Thermometer::setPercentage(float percentage)
{
	parameter.percentage = percentage;
}

void Thermometer::setScale(float startScale, float endScale)
{	
	parameter.scale.start = startScale;
	parameter.scale.end = endScale;
}

void Thermometer::setUnit(QString unit)
{	
	parameter.unit = unit;
}

void Thermometer::setRangeStart(int index, float startRange)
{
    listRange[index].start = startRange;
}

void Thermometer::setRangeEnd(int index, float endRange)
{
    listRange[index].end = endRange;
}

void Thermometer::setRangeColor(int index, QColor color)
{
    listRange[index].color = color;
}

void Thermometer::addRange(float startRange, float endRange, QColor color)
{
	Range range = {startRange, endRange, color};
	listRange.append(range);
}

void Thermometer::setSize(float sizeWidth, float sizeHeight)
{
	calculateMeasure(sizeWidth, sizeHeight);
}
