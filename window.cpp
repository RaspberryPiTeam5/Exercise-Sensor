#include "window.h"
#include "ADCreader.h"
#include <ctime>
#include <cmath>
#include <bcm2835.h>


Window::Window():normtemp(0), gain(5), moistlev(0)

{
	 knob = new QwtKnob;
  // set up the gain knob                                                                                                                      
  knob->setValue(gain);

    // use the Qt signals/slots framework to update the gain -                                                                                 
    // every time the knob is moved, the setGain function will be called                                                                       
    connect( knob, SIGNAL(valueChanged(double)), SLOT(setGain(double)) );

// set up the initial plot data                                                                                                                
        for( int index=0; index<plotDataSize; ++index )
        {
                 xData[index]  = index;
                yData0[index] = 0;
                yData00[index]=normtemp;
                yData1[index] =gain* 0;
                yData2[index] = 0;
                yData22[index]=moistlev;

        }
// Channel 0,1 and 2 curves                                                                                                                            
        curve0 = new QwtPlotCurve;
        curve0->setPen(QPen(Qt::green,2));
        curve00 = new QwtPlotCurve;
        curve00->setPen(QPen(Qt::blue,2));
        curve1 = new QwtPlotCurve;
        curve2 = new QwtPlotCurve;
        curve2->setPen(QPen(Qt::green,2));
        curve22= new QwtPlotCurve;
        curve22->setPen(QPen(Qt::blue,2));

// Channel 0,1 and 2 plots
        plot0 = new QwtPlot;
        plot1 = new QwtPlot;
        plot2 = new QwtPlot;
	
	// buttons for plots
	button0=new QPushButton("skin temp");
        button00=new QPushButton("zero temp");
        button2=new QPushButton("Very Sweaty");
        button22=new QPushButton("Very Dry");


        Label= new QLabel(this);
	 //connecting buttons to intended purpose
	connect( button0, SIGNAL(clicked()), SLOT(tempnorm()) );
        connect( button00, SIGNAL(clicked()), SLOT(temp0()) );
        connect( button2, SIGNAL(clicked()), SLOT(sweaty()) );
        connect( button22, SIGNAL(clicked()), SLOT(dry()) );


        curve0->setSamples(xData, yData0, plotDataSize);
        curve00->setSamples(xData, yData00, plotDataSize);
        curve1->setSamples(xData, yData1, plotDataSize);
        curve2->setSamples(xData, yData2, plotDataSize);
        curve22->setSamples(xData, yData22, plotDataSize);

        curve0->attach(plot0);
        curve00->attach(plot0);
        curve1->attach(plot1);
        curve2->attach(plot2);
        curve22->attach(plot2);


        plot0->setAxisTitle(QwtPlot::yLeft, "Temperature (degrees)");
      
        plot1->setAxisTitle(QwtPlot::yLeft, "Voltage (mv)");
      ;
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
        vLayout1= new QVBoxLayout;
        vLayout1->addWidget(button0);
        vLayout1->addWidget(button00);
        vLayout1->addWidget(knob);
        vLayout1->addWidget(button2);
        vLayout1->addWidget(button22);
        hLayout=new QHBoxLayout;
        //      hLayout->addWidget(button0);                                                                                                   
        hLayout->addLayout(vLayout1);
        hLayout->addLayout(vLayout);
        setLayout(hLayout);



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
	//reading data from the ADC
   double inVal0 =  adcreader->Data0();
  double inVal00= normtemp;
  double inVal1 =  gain*(adcreader->Data1());
 double inVal2 =  adcreader->Data2();
 double inVal22=moistlev;


// add the new input to the plot                                                                                                               
        memmove( yData0, yData0+1, (plotDataSize-1) * sizeof(double) );
	yData0[plotDataSize-1] = inVal0;
        curve0->setSamples(xData, yData0, plotDataSize);
	
	memmove( yData00, yData00+1, (plotDataSize-1) * sizeof(double) );
        yData00[plotDataSize-1] = inVal00;
        curve00->setSamples(xData, yData00, plotDataSize);

        
        plot0->setAxisTitle(QwtPlot::yLeft, "Temperature (degrees)");
        plot0->replot();

memmove( yData1, yData1+1, (plotDataSize-1) * sizeof(double) );
        yData1[plotDataSize-1] = inVal1;
        curve1->setSamples(xData, yData1, plotDataSize);
        
        plot1->setAxisTitle(QwtPlot::yLeft, "Voltage (mv)");
        plot1->replot();

memmove( yData2, yData2+1, (plotDataSize-1) * sizeof(double) );
        yData2[plotDataSize-1] = inVal2;
        curve2->setSamples(xData, yData2, plotDataSize);
	
memmove( yData22, yData22+1, (plotDataSize-1) * sizeof(double) );
        yData22[plotDataSize-1] = inVal22;
        curve22->setSamples(xData, yData22, plotDataSize);

       
        plot2->setAxisTitle(QwtPlot::yLeft, "Moisture (% change)");
        plot2->replot();

}
int Window::tempnorm()
{
  normtemp=34;
  return normtemp;
}

int Window::temp0()
{
  normtemp=0;
  return normtemp;
}

int Window::sweaty()
{
  moistlev=100;
  return moistlev;
}

int Window::dry()
{
  moistlev=0;
  return moistlev;
}



// this function can be used to change the gain of the A/D internal amplifier                                                                  
void Window::setGain(double gain)
{
  // for example purposes just change the amplitude of the generated input                                                                     
  this->gain = gain;
}
