#include "window.h"
#include "ADCreader.h"
#include <ctime>
#include <cmath>
#include <bcm2835.h>


Window::Window()
{
// set up the initial plot data                                                                                                                
        for( int index=0; index<plotDataSize; ++index )
        {
                xData[index]  = index;
                yData0[index] = 0;
                yData1[index] = 0;
                yData2[index] = 0;
        }
// Channel 0,1 and 2 plot                                                                                                                              
        curve0 = new QwtPlotCurve;
        curve1 = new QwtPlotCurve;
        curve2 = new QwtPlotCurve;

        plot0 = new QwtPlot;
        plot1 = new QwtPlot;
        plot2 = new QwtPlot;

        Label= new QLabel(this);

        curve0->setSamples(xData, yData0, plotDataSize);
        curve1->setSamples(xData, yData1, plotDataSize);
        curve2->setSamples(xData, yData2, plotDataSize);

        curve0->attach(plot0);
        curve1->attach(plot1);
        curve2->attach(plot2);

        plot0->setAxisTitle(QwtPlot::xBottom, "Time (x10ms)");
        plot0->setAxisTitle(QwtPlot::yLeft, "Temperature (°C)");
        plot1->setAxisTitle(QwtPlot::xBottom, "Time (x10ms)");
        plot1->setAxisTitle(QwtPlot::yLeft, "Voltage (mv)");
        plot2->setAxisTitle(QwtPlot::xBottom, "Time (x10ms)");
        plot2->setAxisTitle(QwtPlot::yLeft, "Moisture (units)");

        plot0->replot();
        plot1->replot();
        plot2->replot();

        plot0->show();
        plot1->show();
        plot2->show();


        vLayout = new QVBoxLayout;
        vLayout->addWidget(plot0);
        vLayout->addWidget(plot1);
        vLayout->addWidget(plot2);

        setLayout(vLayout);


adcreader = new ADCreader();
adcreader->start();
}
Window::~Window() {
        // tells the thread to no longer run its endless loop                                                                                  
        adcreader->quit();
        // wait until the run method has terminated                                                                                            
	adcreader->wait();
        delete adcreader;
}

void Window::timerEvent( QTimerEvent * )
{
  double inVal0 =  adcreader->Data0();
  double inVal1 =  adcreader->Data1();
 double inVal2 =  adcreader->Data2();

// add the new input to the plot                                                                                                               
        memmove( yData0, yData0+1, (plotDataSize-1) * sizeof(double) );
	yData0[plotDataSize-1] = inVal0;
        curve0->setSamples(xData, yData0, plotDataSize);
        plot0->setAxisTitle(QwtPlot::xBottom, "Temperature (°C)");
        plot0->setAxisTitle(QwtPlot::yLeft, "Time (x10ms)");
        plot0->replot();

memmove( yData1, yData1+1, (plotDataSize-1) * sizeof(double) );
        yData1[plotDataSize-1] = inVal1;
        curve1->setSamples(xData, yData1, plotDataSize);
        plot1->setAxisTitle(QwtPlot::xBottom, "Voltage (mv)");
        plot1->setAxisTitle(QwtPlot::yLeft, "Time (x10ms)");
        plot1->replot();

memmove( yData2, yData2+1, (plotDataSize-1) * sizeof(double) );
        yData2[plotDataSize-1] = inVal2;
        curve2->setSamples(xData, yData2, plotDataSize);
        plot2->setAxisTitle(QwtPlot::xBottom, "Moisture (units)");
        plot2->setAxisTitle(QwtPlot::yLeft, "Time (x10ms)");
        plot2->replot();

}

