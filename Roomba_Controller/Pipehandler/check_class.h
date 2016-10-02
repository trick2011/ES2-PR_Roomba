#ifndef check_class_h
#define check_class_h

//#include <iostream>
//#include <string>
//#include <sys/stat.h>
//#include <unistd.h>
//#include <fcntl.h>
//#include <sys/types.h>
//#include <sys/stat.h>
//#include <string.h>
//#include <linux/stat.h>
//#include "macros.h"

#include "../roombacontroller.h"
#include "../../Roomba_Interpreter/interpreter.h"
#include "macros.h"

//#include "com_class.h"
//#include "pipe_filler.h"

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

using namespace std;


typedef websocketpp::server<websocketpp::config::asio> server;

//#define DRY_DEBUG // define DRY_DEBUG when not debugging with the roomba
#define VERBOSE

class check_class{// : public com_class{
private:
//	bool Auto_clean_Flag;
//	bool Man_clean_Flag;
//	bool Dock_roomba_Flag;
	
	server print_server;
	static server* print_serverptr;
	
	static Basicclean* Cleaningprogramc;
	static interpreter* inter;
	static Roombacontroller* roomref;
	static void on_message(websocketpp::connection_hdl hdl, server::message_ptr msg);
public:
	//check_class();
	check_class(Roombacontroller* roomref,interpreter* inter,int port = 25565);


	void operator()();

	//void pipe_checker();
	static void easter(void);
	
};
#endif
