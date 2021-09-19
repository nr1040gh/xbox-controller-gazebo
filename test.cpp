#include <iostream>
#include <linux/input.h>
#include <fcntl.h> // for O_RDONLY
#include <unistd.h> //for read() and write()
#include <map>
#include <string>
#include <cmath>

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

std::ostream& operator << (std::ostream& os, Digital digi)
{
    os << digi.getInput() << ": " << digi.getValue();
    return os;
}



class Analog : public Digital
{
    private:
        int deadzone; 

    public:
        //https://www.learncpp.com/cpp-tutorial/constructors-and-initialization-of-derived-classes/
        Analog(std::string input, int value, int deadzone)
            : Digital{ input, value }
            , deadzone{ deadzone }
        {      
            if (std::abs(value) >= deadzone)
                isRegistered = true;
            else
                isRegistered = false;
        }
        bool isRegistered;
};

std::ostream& operator << (std::ostream& os, Analog ana)
{
    os << ana.getInput() << ": " << ana.getValue();
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



    //initialize buttons and sticks
    // Classes probably aren't the best here but it's for practice
    Analog ls_x = Analog("LS_X",0,deadzone);
    Analog ls_y = Analog("LS_Y",0,deadzone);
    Analog lt = Analog("LT",0,0);
    Analog rs_x = Analog("RS_X",0,deadzone);
    Analog rs_y = Analog("RS_Y",0,deadzone);
    Analog rt = Analog("RT",0,0);
    Digital a = Digital("A",0);
    Digital b = Digital("B",0);
    Digital x = Digital("X",0);
    Digital y = Digital("Y",0);
    Digital start = Digital("START",0);
    Digital select = Digital("SELECT",0);
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

        //Apply dead zones for control sticks - If it's not outside deadzone, continue checking for buttons
        if (code <= 2 || (code >= 3 && code <= 4))
        {
            
            switch (code)
            {

            case 0: 
                ls_x = Analog(input,e.value,deadzone);
                if (!ls_x.isRegistered)
                {
                    ls_x.setValue(0);
                }

            case 1:
                ls_y = Analog(input,e.value,deadzone);
                if (!ls_y.isRegistered)
                {
                    ls_y.setValue(0);
                }
            case 3:
                rs_x = Analog(input,e.value,deadzone);
                if (!rs_x.isRegistered)
                {
                    rs_x.setValue(0);
                }
            case 4:
                rs_y = Analog(input,e.value,deadzone);
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
                lt = Analog(input,e.value,0);         

            case 5:
                rt = Analog(input,e.value,0);
            
            case 16:
                dpad_x = Digital(input,e.value);

            case 17:
                dpad_y = Digital(input,e.value);
                
            case 304:
                a = Digital(input,e.value);

            case 305:
                b = Digital(input,e.value);

            case 307:
                x = Digital(input,e.value);
                
            case 308:
                y = Digital(input,e.value);
                
            case 314:
                select = Digital(input,e.value);
                
            case 315:
                start = Digital(input,e.value);
                
            case 310:
                lb = Digital(input,e.value);
                
            case 311:
                rb = Digital(input,e.value);
                
            case 316:
                middle = Digital(input,e.value);
                
            case 317:
                ls = Digital(input,e.value);
                
            case 318:
                rs = Digital(input,e.value);
                
            }
        }
        

        std::cout << ls_x << "  " << ls_y << "  " << rs_x << "  " << rs_y << "  " <<
        a << "  " << b << "  " << x  << "  " << y  << "  " << lt << "  " << rt << "  "
        << lb << "  " << rb << "  " << dpad_x << "  " << dpad_y << "  " << rs << "  "
        << ls << "  " << start << "  " << select << "  " << middle << std::endl;

    }

    return 0;
}
