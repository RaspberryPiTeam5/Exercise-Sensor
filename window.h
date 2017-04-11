#ifndef WINDOW_H
#define WINDOW_H

#include <qwt/qwt_thermo.h>
#include <qwt/qwt_knob.h>
#include <qwt/qwt_plot.h>
#include <qwt/qwt_plot_curve.h>
#include <QBoxLayout>
#include <QLabel>
#include "ADCreader.h"
#include <QPushButton>
#include <QPen>


// class definition 'Window'                                                                                                                   
class Window : public QWidget
{
        // must include the Q_OBJECT macro for for the Qt signals/slots framework to work with this class                                      
        Q_OBJECT

public:
        Window(); // default constructor - called when a Window is declared without arguments                                                  

        ~Window();

        void timerEvent( QTimerEvent * );
                        public slots:

          int tempnorm();
          int temp0();
          int sweaty();
          int dry();
          void setGain(double gain);



// internal variables for the window class                                                                                                     
private:
        QwtKnob *knob;

        QwtPlot      *plot0,*plot1,*plot2;

        QwtPlotCurve *curve0,*curve00,*curve1,*curve2,*curve22;

        QPushButton*button0,*button00,*button2,*button22;

        QLabel*Label;

        // layout elements from Qt itself http://qt-project.org/doc/qt-4.8/classes.html                                                        
          QVBoxLayout  *vLayout;  // vertical layout                          
        QVBoxLayout*vLayout1;// vertical layout                             
        QHBoxLayout*hLayout;// horizontal layout

  static const int plotDataSize = 100;

        // data arrays for the plot                                                                                                            
         double xData[plotDataSize];
        double yData0[plotDataSize];
        double yData00[plotDataSize];                                      \

        double yData1[plotDataSize];                                       \
                                                                           \
        double yData2[plotDataSize];
        double yData22[plotDataSize];
        
        double gain;
        int normtemp;
        int moistlev;
        ADCreader *adcreader;




};

#endif // WINDOW_H     


