#ifndef ADCREADER
#define ADCREADER
#include "mcp3008Spi.h"
#include <QThread>

class ADCreader : public QThread

{
public:
        ADCreader() {running = 0;};
        void quit();
        void run();
        int Data0();
        int Data1();
        int Data2();

private:

        bool running;
        int output0;
        int output1;
        int output2;

};

#endif

