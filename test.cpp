#include <iostream>
#include <linux/input.h>
#include <fcntl.h> // for O_RDONLY
#include <unistd.h> //for read() and write()
#include <map>
#include <string>
#include <cmath>
#include <iomanip> //for setw function

//https://stackoverflow.com/questions/16695432/input-event-structure-description-from-linux-input-h


//BUTTON CODES:
/*
304:A
305:B
307:X
308:Y
315:START
314:SELECT
316:MIDDLE
311:RB
310:LB
317:LS
318:RS
*/

//ANALOG CODES?:
/*
0:LS X
1:LS Y
2:LT
3:RS X
4:RS Y
5:RT
16:DPAD X
17:DPAD Y
*/

//To do: create class for buttons, add deadzone method
    // Break into header and cpp files
// To do: create testing file/program


class Digital
{

    private:
        std::string input;
        int value;

        

    public:
        Digital(std::string input, int value)
        {
            this->input = input;
            this->value = value;
        }

        void setValue(int newValue)
        {
            value = newValue;
        }

        int getValue()
        {
            return value;
        }

        std::string getInput()
        {
            return input;
        }


};

std::ostream& operator << (std::ostream& os, Digital& digi)
{
    os << digi.getInput() << ": " << digi.getValue();
    return os;
}



class Analog : public Digital
{
    private:
        int deadzone; 
        int input;
        int value;
        int _width;

    public:
        bool isRegistered;

        //https://www.learncpp.com/cpp-tutorial/constructors-and-initialization-of-derived-classes/
        Analog(std::string input, int value, int deadzone, int width=0)
            : Digital{ input, value }
            , deadzone{ deadzone }
            , _width{ width }
        {      
            if (std::abs(value) >= deadzone)
                isRegistered = true;
            else
                isRegistered = false;
        }

        int getWidth()
        {
            return _width;
        }
        

};

std::ostream& operator << (std::ostream& os, Analog& ana)
{
    os << ana.getInput() << ": " << std::setw(ana.getWidth()) << ana.getValue();
    return os;
}


int main(){
    //https://www.kernel.org/doc/html/v5.3/input/joydev/joystick-api.html
    //event found using: cat /proc/bus/input/devices
    int fd = open("/dev/input/event11", O_RDONLY); 


    //https://www.kernel.org/doc/html/v5.3/input/input.html#event-interface
    //EV_KEY - buttons
    //EV_

    
    std::map<int, std::string> mapping {
        {0,"LS_X"},
        {1,"LS_Y"},
        {2,"LT"},
        {3,"RS_X"},
        {4,"RS_Y"},
        {5,"RT"},
        {16,"DPAD_X"},
        {17,"DPAD_Y"},
        {304,"A"},
        {305,"B"},
        {307,"X"},
        {308,"Y"},
        {315,"START"},
        {314,"SELECT"},
        {316,"MIDDLE"},
        {311,"RB"},
        {310,"LB"},
        {317,"LS"},
        {318,"RS"}
    };
    

    //input_event from linux.input.h
    struct input_event e; 
    int code;
    std::string input;
    int deadzone = 6000; //calibrated based on testing my controller only - move this further out of the function
    
    //Only used for std output purposes
    int stick_width = 6;
    int trigger_width = 3;


    //initialize buttons and sticks
    // Classes probably aren't the best here but it's for practice
    Analog ls_x = Analog("LS_X",0,deadzone,stick_width);
    Analog ls_y = Analog("LS_Y",0,deadzone,stick_width);
    Analog lt = Analog("LT",0,0,trigger_width);
    Analog rs_x = Analog("RS_X",0,deadzone,stick_width);
    Analog rs_y = Analog("RS_Y",0,deadzone,stick_width);
    Analog rt = Analog("RT",0,0,trigger_width);
    Digital a = Digital("A",0);
    Digital b = Digital("B",0);
    Digital x = Digital("X",0);
    Digital y = Digital("Y",0);
    Digital start = Digital("START",0);
    Digital selec = Digital("SELECT",0);
    Digital middle = Digital("MIDDLE",0);
    Digital rb = Digital("RB",0);
    Digital lb = Digital("LB",0);
    Digital rs = Digital("RS",0);
    Digital ls = Digital("LS",0);
    Digital dpad_x = Digital("DPAD_X",0);
    Digital dpad_y = Digital("DPAD_Y",0);


    while (read(fd, &e, sizeof(e))){
        //if (e.type == EV_KEY){
            //std::cout << "type: KEY" << e.type << std::endl;
            
        //}
        code = e.code;
        input = mapping[code];
        //std::cout << "\n" << code << std::endl;
        //Apply dead zones for control sticks - If it's not outside deadzone, continue checking for buttons
        if (code <= 1 || (code >= 3 && code <= 4))
        {
            
            switch (code)
            {

            case 0: 
                ls_x = Analog(input,e.value,deadzone,stick_width);
                if (!ls_x.isRegistered)
                {
                    ls_x.setValue(0);
                }
                break;

            case 1:
                ls_y = Analog(input,e.value,deadzone,stick_width);
                if (!ls_y.isRegistered)
                {
                    ls_y.setValue(0);
                }
                break;

            case 3:
                rs_x = Analog(input,e.value,deadzone,stick_width);
                if (!rs_x.isRegistered)
                {
                    rs_x.setValue(0);
                }
                break;

            case 4:
                rs_y = Analog(input,e.value,deadzone,stick_width);
                if (!rs_y.isRegistered)
                {
                    rs_y.setValue(0);
                }
            }
        }
        
        else
        {

            switch (code){
            
            case 2:
                lt.setValue(e.value); //lt = Analog(input,e.value,0);         

            case 5:
                rt.setValue(e.value); // = Analog(input,e.value,0);
                break;
            
            case 16:
                dpad_x.setValue(e.value);// = Digital(input,e.value);
                break;

            case 17:
                dpad_y.setValue(e.value);// = Digital(input,e.value);
                break;
                
            case 304:
                a.setValue(e.value);// = Digital(input,e.value);
                break;

            case 305:
                b.setValue(e.value);// = Digital(input,e.value);
                break;

            case 307:
                x.setValue(e.value);// = Digital(input,e.value);
                break;
                
            case 308:
                y.setValue(e.value);// = Digital(input,e.value);
                break;
                
            case 314:
                selec.setValue(e.value);// = Digital(input,e.value);
                break;
                
            case 315:
                start.setValue(e.value);// = Digital(input,e.value);
                break;
                
            case 310:
                lb.setValue(e.value);// = Digital(input,e.value);
                break;
                
            case 311:
                rb.setValue(e.value);// = Digital(input,e.value);
                break;
                
            case 316:
                middle.setValue(e.value);// = Digital(input,e.value);
                break;
                
            case 317:
                ls.setValue(e.value);// = Digital(input,e.value);
                break;
                
            case 318:
                rs.setValue(e.value);// = Digital(input,e.value);
                
            }
        }
        

        std::cout << ls_x << "  " << ls_y << "  " << rs_x << "  " << rs_y << "  " <<
        a << "  " << b << "  " << x  << "  " << y  << "  " << lt << "  " << rt << "  "
        << lb << "  " << rb << "  " << dpad_x << "  " << dpad_y << "  " << rs << "  "
        << ls << "  " << start << "  " << selec << "  " << middle << std::endl;

    }

    return 0;
}
