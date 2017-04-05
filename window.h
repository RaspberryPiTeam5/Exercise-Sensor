#ifndef WINDOW_H
#define WINDOW_H

#include <qwt/qwt_thermo.h>
#include <qwt/qwt_knob.h>
#include <qwt/qwt_plot.h>
#include <qwt/qwt_plot_curve.h>
#include <QBoxLayout>
#include <QLabel>
#include "adcreader.h"



// class definition 'Window'
class Window : public QWidget
{
	// must include the Q_OBJECT macro for for the Qt signals/slots framework to work with this class
	Q_OBJECT

public:
	Window(); // default constructor - called when a Window is declared without arguments

	~Window();

	void timerEvent( QTimerEvent * );


// internal variables for the window class
private:

	QwtPlot      *plot0;
        QwtPlot      *plot1;
        QwtPlot      *plot2;
	QwtPlotCurve *curve0;
        QwtPlotCurve *curve1;
        QwtPlotCurve *curve2;
      

	// layout elements from Qt itself http://qt-project.org/doc/qt-4.8/classes.html
	QVBoxLayout  *vLayout0;  // vertical layout
        QVBoxLayout  *vLayout2;  // vertical layout
        QVBoxLayout  *vLayout3;  // vertical layout
	QHBoxLayout  *hLayout;  // horizontal layout

	static const int plotDataSize = 100;

	// data arrays for the plot
	double xData[plotDataSize];
	double y0Data[plotDataSize];
        //double x1Data[plotDataSize];
	double y1Data[plotDataSize];
       // double x2Data[plotDataSize];
	double y2Data[plotDataSize];
	
	


};

#endif // WINDOW_H
