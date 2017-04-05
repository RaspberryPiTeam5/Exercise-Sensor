#include "window.h"
#include "adcreader.h"
#include <ctime>
#include <cmath>

// set up the initial plot data
	for( int index=0; index<plotDataSize; ++index )
	{
		xData[index] = index;
		yData0[index] = 0;
                yData1[index] = 0;
                yData2[index] = 0;
	}
// Channel 0 plot.
	curve0 = new QwtPlotCurve("Temperature");
	plot0 = new QwtPlot;
	curve0->setSamples(xData, yData0, plotDataSize);
	curve0->attach(plot0);
        plot0->setAxisTitle(QwtPlot::xBottom, "Temperature (°C)");
        plot0->setAxisTitle(QwtPlot::yLeft, "Time (x10ms)");
	plot0->replot();
	plot0->show();
// Channel 1 plot.
	curve1 = new QwtPlotCurve("Pulse");
	plot1 = new QwtPlot;
	curve1->setSamples(xData, yData1, plotDataSize);
	curve1->attach(plot1);
        plot1->setAxisTitle(QwtPlot::xBottom, "Voltage (mv)");
        plot1->setAxisTitle(QwtPlot::yLeft, "Time (x10ms)");
	plot1->replot();
	plot1->show();

// Channel 2 plot.
	curve2 = new QwtPlotCurve("Moisture");
	plot2 = new QwtPlot;
	curve2->setSamples(xData, yData2, plotDataSize);
	curve2->attach(plot2);
        plot2->setAxisTitle(QwtPlot::xBottom, "Moisture (units)");
        plot2->setAxisTitle(QwtPlot::yLeft, "Time (x10ms)");
	plot2->replot();
	plot2->show();

vLayout1 = new QVBoxLayout;
	vLayout2->addWidget(plot0);
        vLayout2->addWidget(plot1);
        vLayout2->addWidget(plot2);


adcreader = new ADCreader();
adcreader->start();

Window::~Window() {
	// tells the thread to no longer run its endless loop
	adcreader->quit();
	// wait until the run method has terminated
	adcreader->wait();
	delete adcreader;
}

void Window::timerEvent( QTimerEvent * )
{


// add the new input to the plot
	memmove( yData0, yData0+1, (plotDataSize-1) * sizeof(double) );
	yData[plotDataSize-1] = inVal0;
	curveo.setSamples(xData, yData0, plotDataSize);
        plot0->setAxisTitle(QwtPlot::xBottom, "Temperature (°C)");
        plot0->setAxisTitle(QwtPlot::yLeft, "Time (x10ms)");
	plot0->replot();

memmove( yData1, yData1+1, (plotDataSize-1) * sizeof(double) );
	yData[plotDataSize-1] = inVal1;
	curve1.setSamples(xData, yData1, plotDataSize);
        plot1->setAxisTitle(QwtPlot::xBottom, "Voltage (mv)");
        plot1->setAxisTitle(QwtPlot::yLeft, "Time (x10ms)");
	plot1->replot();

memmove( yData2, yData2+1, (plotDataSize-1) * sizeof(double) );
	yData[plotDataSize-1] = inVal2;
	curve2.setSamples(xData, yData2, plotDataSize);
        plot2->setAxisTitle(QwtPlot::xBottom, "Moisture (units)");
        plot2->setAxisTitle(QwtPlot::yLeft, "Time (x10ms)");
	plot2->replot();



