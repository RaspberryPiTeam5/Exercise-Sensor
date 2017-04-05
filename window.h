#ifndef WINDOW_H
#define WINDOW_H

#include <qwt/qwt_thermo.h>
#include <qwt/qwt_knob.h>
#include <qwt/qwt_plot.h>
#include <qwt/qwt_plot_curve.h>
#include <QBoxLayout>
#include <QLabel>
#include "ADCreader.h"

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

        QwtPlot      *plot0,*plot1,*plot2;

        QwtPlotCurve *curve0,*curve1,*curve2;

        QLabel*Label;

        // layout elements from Qt itself http://qt-project.org/doc/qt-4.8/classes.html                                                        
        QVBoxLayout  *vLayout;  // vertical layout  

  static const int plotDataSize = 100;

        // data arrays for the plot                                                                                                            
        double xData[plotDataSize];
        double yData0[plotDataSize];
        //double x1Data[plotDataSize];                                                                                                         
        double yData1[plotDataSize];
       // double x2Data[plotDataSize];                                                                                                         
        double yData2[plotDataSize];

        ADCreader *adcreader;


};

#endif // WINDOW_H     


