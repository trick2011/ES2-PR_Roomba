#ifndef MACROS
#define MACROS

namespace site_opcodes{
	//volitail functions
	static const char	MoveForward 	= 'a';
	static const char	MoveRight		= 'b';
	static const char	MoveLeft		= 'c';
	static const char	MoveBackword 	= 'd';	//corrected

	//static fucntions
	static const char	AutoClean	 	= 'e';
	static const char	SpotClean		= 'g';
	static const char	WallTrace		= 'h';
	static const char	Dock			= 'k';
	static const char	StopRoomba		= 'j';

	//roomba controll
	static const char	Start			= 's';
	static const char	Stop			= 'o';
	static const char	BrushOn			= 'f';
	static const char	BrushOff		= 'i';
	
	
	//controller controll
	static const char	StopController	= 'S';
	static const char	easter			= 'E';
	
	//Roomba side
	static const char	BumpRight		= 'v';
	static const char	BumpLeft		= 'w';
	static const char	Drop			= 'x';
	static const char	TrashbinFull 	= 'y';
	static const char	BatteryLow  	= 'z';
	static const char	Nothing			= ' ';
}
#endif 
