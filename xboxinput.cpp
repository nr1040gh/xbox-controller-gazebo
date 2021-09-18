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

    int count = 1, prev = 0;
    while (read(fd, &e, sizeof(e))){
        //if (e.type == EV_KEY){
            //std::cout << "type: KEY" << e.type << std::endl;
            
        //}
        code = e.code;
        input = mapping[code];

        //Apply dead zones for control sticks - If it's not outside deadzone, continue checking for buttons
        if (code <= 2 || (code >= 3 && code <= 4))
        {
            int deadzone = 6000; //calibrated based on testing my controller only - move this further out of the function
            switch (code)
            {
            case 0:
                if (std::abs(e.value) > deadzone)
                {
                    std::cout << "type: JS" << e.type << std::endl;
                    std::cout << "Input: " << input << std::endl;
                    std::cout << "value: " << e.value << std::endl;
                    std::cout << std::endl;
                }
                
            case 1:
                if (std::abs(e.value) > deadzone)
                {
                    std::cout << "type: JS" << e.type << std::endl;
                    std::cout << "Input: " << input << std::endl;
                    std::cout << "value: " << e.value << std::endl;
                    std::cout << std::endl;
                }
            case 3:
                if (std::abs(e.value) > deadzone)
                {
                    std::cout << "type: JS" << e.type << std::endl;
                    std::cout << "Input: " << input << std::endl;
                    std::cout << "value: " << e.value << std::endl;
                    std::cout << std::endl;
                }
            case 4:
                if (std::abs(e.value) > deadzone)
                {
                    std::cout << "type: JS" << e.type << std::endl;
                    std::cout << "Input: " << input << std::endl;
                    std::cout << "value: " << e.value << std::endl;
                    std::cout << std::endl;
                }
            }
        }

        //if ((e.type == EV_ABS) && (e.code == 0)){
        //   std::cout << "type: JS" << e.type << std::endl;
        //   std::cout << "code: " << e.code << std::endl;
        //   std::cout << "value: " << e.value << std::endl;
        //  std::cout << std::endl;
        //}
        if (prev == code){
            count ++;
        }

        else{
            count = 1;
        }

        prev = code;
        

        switch (code){
            /*
            case 0:
                std::cout << "type: JS" << e.type << std::endl;
                std::cout << "Input: " << input << std::endl;
                std::cout << "value: " << e.value << std::endl;
                std::cout << std::endl;
            case 1:
                std::cout << "type: JS" << e.type << std::endl;
                std::cout << "Input: " << input << std::endl;
                std::cout << "value: " << e.value << std::endl;
                std::cout << std::endl;
            */

            case 2:
                std::cout << "type: JS" << e.type << std::endl;
                std::cout << "Input: " << input << std::endl;
                std::cout << "value: " << e.value << std::endl;
                std::cout << std::endl;

            /*
            case 3:
                std::cout << "type: JS" << e.type << std::endl;
                std::cout << "Input: " << input << std::endl;
                std::cout << "value: " << e.value << std::endl;
                std::cout << std::endl;
            case 4:
                std::cout << "type: JS" << e.type << std::endl;
                std::cout << "Input: " << input << std::endl;
                std::cout << "value: " << e.value << std::endl;
                std::cout << std::endl;
            */
            case 5:
                std::cout << "type: JS" << e.type << std::endl;
                std::cout << "Input: " << input << std::endl;
                std::cout << "value: " << e.value << std::endl;
                std::cout << std::endl;
            
            case 16:
                std::cout << "type: JS" << e.type << std::endl;
                std::cout << "Input: " << input << std::endl;
                std::cout << "value: " << e.value << std::endl;
                std::cout<< "count: " << count << std::endl;  
                std::cout << std::endl;
            case 17:
                std::cout << "type: JS" << e.type << std::endl;
                std::cout << "Input: " << input << std::endl;
                std::cout << "value: " << e.value << std::endl;
                std::cout<< "count: " << count << std::endl;  
                std::cout << std::endl;
            case 304:
                std::cout << "type: JS" << e.type << std::endl;
                std::cout << "Input: " << input << std::endl;
                std::cout << "value: " << e.value << std::endl;
                std::cout<< "count: " << count << std::endl;  
                std::cout << std::endl;
            case 305:
                std::cout << "type: JS" << e.type << std::endl;
                std::cout << "Input: " << input << std::endl;
                std::cout << "value: " << e.value << std::endl;
                std::cout<< "count: " << count << std::endl;  
                std::cout << std::endl;
            case 307:
                std::cout << "type: JS" << e.type << std::endl;
                std::cout << "Input: " << input << std::endl;
                std::cout << "value: " << e.value << std::endl;
                std::cout<< "count: " << count << std::endl;  
                std::cout << std::endl;
            case 308:
                std::cout << "type: JS" << e.type << std::endl;
                std::cout << "Input: " << input << std::endl;
                std::cout << "value: " << e.value << std::endl;
                std::cout<< "count: " << count << std::endl;  
                std::cout << std::endl;
            case 314:
                std::cout << "type: JS" << e.type << std::endl;
                std::cout << "Input: " << input << std::endl;
                std::cout << "value: " << e.value << std::endl;
                std::cout<< "count: " << count << std::endl;  
                std::cout << std::endl;
            case 315:
                std::cout << "type: JS" << e.type << std::endl;
                std::cout << "Input: " << input << std::endl;
                std::cout << "value: " << e.value << std::endl;
                std::cout<< "count: " << count << std::endl;  
                std::cout << std::endl;
            case 310:
                std::cout << "type: JS" << e.type << std::endl;
                std::cout << "Input: " << input << std::endl;
                std::cout << "value: " << e.value << std::endl;
                std::cout<< "count: " << count << std::endl;  
                std::cout << std::endl;
            case 311:
                std::cout << "type: JS" << e.type << std::endl;
                std::cout << "Input: " << input << std::endl;
                std::cout << "value: " << e.value << std::endl;
                std::cout<< "count: " << count << std::endl;  
                std::cout << std::endl;
            case 316:
                std::cout << "type: JS" << e.type << std::endl;
                std::cout << "Input: " << input << std::endl;
                std::cout << "value: " << e.value << std::endl;
                std::cout<< "count: " << count << std::endl;  
                std::cout << std::endl;
            case 317:
                std::cout << "type: JS" << e.type << std::endl;
                std::cout << "Input: " << input << std::endl;
                std::cout << "value: " << e.value << std::endl;
                std::cout<< "count: " << count << std::endl;  
                std::cout << std::endl;
            case 318:
                std::cout << "type: JS" << e.type << std::endl;
                std::cout << "Input: " << input << std::endl;
                std::cout << "value: " << e.value << std::endl;
                std::cout<< "count: " << count << std::endl;  
                std::cout << std::endl;
    
        }

              

        

        

    }

    return 0;
}
