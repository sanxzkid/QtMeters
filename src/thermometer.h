#ifndef THERMOMETER_H
#define THERMOMETER_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include "defines.h"

class Thermometer : public QWidget
{
	Q_OBJECT

public:
	explicit Thermometer(QWidget *parent = 0);
	~Thermometer();
	
	void setParameter(QString title, float percentage, float startScale, float endScale, QString unit);
	void setTitle(QString title);
	void setPercentage(float percentage);
	void setScale(float startScale, float endEscale);
	void setUnit(QString unit);
	void addRange(float startRange, float endRange, QColor(color));
	void setRangeStart(int index, float startRange);
	void setRangeEnd(int index, float endRange);
	void setRangeColor(int index, QColor color);
	
public slots:
	void setSize(float width, float height);
	
private:
	void paintEvent(QPaintEvent *event);
	
	ThermoMeasure dynamic;
	Parameter parameter;
	QList<Range> listRange;
	
	QPainter painter;	
	void calculateMeasure(float sizeWidth, float sizeHeight);
	void drawTitle();
	void drawUnit();
	void drawLabel();
	void drawDisplay();
	void drawScale();
	void drawMeter();
	void drawRange();
	void drawPointer();
};

#endif // THERMOMETER_H
