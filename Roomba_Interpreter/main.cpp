#include <iostream>
#include <opcodes.h>

using namespace std;

int main(int argc, char *argv[])
{
    cout << "Hello World!" << endl;
    opcodes Opcodes;
    //Opcodes.receiveUart();
    Opcodes.print();
    cout<<endl;
    int d = (int) Opcodes.getWheelOvercurrents();
    int l = (int) Opcodes.getLeftWheelOvercurrent();
    int r = (int) Opcodes.getRightWheelOvercurrent();
    int m = (int) Opcodes.getMainBrushOvercurrent();
    int s = (int) Opcodes.getSideBrushOvercurrent();
    cout<<" overcurrent =      "<<d<<endl;
    cout<<"left overcurrent =  "<<l<<endl;
    cout<<"right overcurrent = "<<r<<endl;
    cout<<"main overcurrent =  "<<m<<endl;
    cout<<"side overcurrent =  "<<s<<endl;
    return 0;
}
