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
	int getData();
private:
	bool running;
	int output;
};

#endif
