#ifndef inv_INTERPRETER_H
#define inv_INTERPRETER_H

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>

#include "../Interpreter_NoThread/opcodes.h"
#include "../Roomba_Interpreter/UART/uart.h"
#include "file.h"

//std::chrono::milliseconds interval(500);

class Inv_interpreter{
private:
	UARTClass uart;
	std::array<uint16_t,58> sensorWaarden;
	Roomclass& room;

	uint8_t UartTemp;
	uint8_t HByte1;
	uint8_t LByte1;
	uint8_t HByte2;
	uint8_t LByte2;
	int iCurrentSpeed;
	int iCurrentRadius;

	void drive(void);
	void sendBumpAndWheel();
	void sendWall();
	void sendCliffL();
	void sendCliffFL();
	void sendCliffFR();
	void sendCliffR();
	void sendDistance();
	void sendAngle();
	void sendWallSignal();
	void sendCliffL_Signal();
	void sendCliffFL_Signal();
	void sendCliffFR_Signal();
	void sendCliffR_Signal();
	void sendLightBumper();
	void sendLightBumpL_Signal();
	void sendLightBumpFL_Signal();
	void sendLightBumpCL_Signal();
	void sendLightBumpCR_Signal();
	void sendLightBumpFR_Signal();
	void sendLightBumpR_Signal();

	void receivestart(void);
public:
	Inv_interpreter(Roomclass& room);
	~Inv_interpreter();

	void mainroutine(void);
};

#endif // inv_INTERPRETER_H
