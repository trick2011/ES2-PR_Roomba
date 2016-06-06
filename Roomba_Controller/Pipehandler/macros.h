#ifndef MACROS
#define MACROS

namespace site_opcodes{
	//volitail functions
	static const char	MoveForward 	= 'a';
	static const char	MoveRight		= 'b';
	static const char	MoveLeft		= 'c';
	static const char	MoveBackword 	= 'd';	//corrected

	//Roomba side
	static const char	BumpRight		= 'v';
	static const char	BumpLeft		= 'w';
	static const char	Drop			= 'x';
	static const char	TrashbinFull 	= 'y';
	static const char	BatteryLow  	= 'z';
	static const char	Nothing			= ' ';

	//static fucntions
	static const char	AutClean	 	= 'e';
	static const char	SpotClean		= 'g';
	static const char	WallTrace		= 'h';
	static const char	Dock			= 'k';
	static const char	StopRoomba		= 'j';
}
#endif 
