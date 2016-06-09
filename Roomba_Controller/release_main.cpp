#include <iostream>


#include "Pipehandler/check_class.h"

using namespace std;

int main(void){
	interpreter inter;
	inter.startRoomba();
	Roombacontroller room(room);
	check_class checker(room,inter);
	checker.pipe_checker();
	cout << "Oh thanks you master for letting me exit gracefully." << endl;
	cout << "I hereby present you this parting gift" << endl;
	sleep(1);
	cout << ".";
	sleep(1);
	cout << ".";
	sleep(1);
	cout << ".";
	sleep(1);
	cout << endl;
	cout << u8"😘 kisssss" << endl;
	cout << "you may now once more take controll of this machine and go forth with you oh so important duties." << endl;
	
}
