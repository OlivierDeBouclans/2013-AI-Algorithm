
/**----------------------------------------------------------------------
// @Projet: Finite State Machine
//
// @Autor: LE BAS DE BOUCLANS Olivier
// @Date: 13/10/13
//
// @Description: This projet is an implementation of finite state based
// agents. Two cars run on a circuit, using fuel and overall state, stoping
// for fuel or reparation if needed (inferior to a fixed percentage). The
// fuel consumption and overall damage are proportional to the car speed. If
// the car run out of gas or out of state in middle of a lap, an appropriate
// car (for repair or refuel) will come and help. Car and helpcar AI are
// implemented using a finite state machine.
//----------------------------------------------------------------------**/

//Include
#include "allegro.h"
#include "Points.h"

#include "Car.h"
#include "StateCar.h"
#include "RepairCar.h"
#include "StateRepairCar.h"
#include "RefuelCar.h"
#include "StateRefuelCar.h"

/**--------------------------------
// @Function: Draw
// @Description: Draw the circuit
//---------------------------------**/
void Draw(BITMAP *buffer)
{
    rectfill(buffer,X1,Y1,X11,Y13,COLOR_WHITE);
    rectfill(buffer,X1+5,Y1+5,X11-5,Y13-5,COLOR_BLACK);

    rectfill(buffer,X5,Y17,X7,Y1,COLOR_WHITE);
    rectfill(buffer,X5+5,Y17+5,X7-5,Y1+5,COLOR_BLACK);

    rectfill(buffer,X4,Y4,X8,Y10,COLOR_GRAY);

    rectfill(buffer,X5+5,Y4,X7-5,Y6-5,COLOR_BLACK);
    rectfill(buffer,X5+5,Y8+5,X7-5,Y10,COLOR_BLACK);

    rectfill(buffer,X5,Y13,X7,Y15,COLOR_WHITE);
    rectfill(buffer,X5+5,Y13-5,X7-5,Y15-5,COLOR_BLACK);

    rectfill(buffer,X8,Y7,X11,Y7+5,COLOR_WHITE);

    textprintf_ex(buffer, font,X4+2*STEP-5,Y1-10, COLOR_WHITE,-1,"Garage");
    textprintf_ex(buffer, font,X4+2*STEP-5,Y4+5, COLOR_WHITE,-1,"Garage");

    textprintf_ex(buffer, font,X7+5,Y13+10, COLOR_WHITE,-1,"Fuel Pump");
    textprintf_ex(buffer, font,X7+5,Y10-10, COLOR_WHITE,-1,"Fuel Pump");
}

/**--------------------------------
// @Function: Main
// @Description: Game's loop
//---------------------------------**/
int main(void)
{
    //initialize Allegro
    allegro_init();

    //initialize the keyboard
    install_keyboard();

    // init graphics
    set_color_depth(32);

    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0))
    {
        allegro_message(allegro_error);
        return 1;
    }

    //Entities initialisation
    Car Car1(10000,10000, CAR_DRIVE);
        Car1.SetColor(COLOR_GREEN);
        Car1.Setroad(0);
        Car1.Setx(X10);
        Car1.Sety(Y7);
        Car1.Setspeed(2);

    Car Car2(10000,10000,CAR_DRIVE);
        Car2.SetColor(COLOR_BLUE);
        Car2.Setroad(1);
        Car2.Setx(X9);
        Car2.Sety(Y7);
        Car2.Setspeed(3);

    RepairCar repaircar1(&Car1,REPAIRCAR_WAIT);
    RepairCar repaircar2(&Car2,REPAIRCAR_WAIT);

    RefuelCar refuelcar1(&Car1,REFUELCAR_WAIT);
    RefuelCar refuelcar2(&Car2,REFUELCAR_WAIT);

    //Game loop
    BITMAP *buffer= create_bitmap(SCREEN_W, SCREEN_H);
    while(!key[KEY_ESC])
    {
        clear(buffer);

        //Entities update
        repaircar1.Update();
        repaircar2.Update();
        refuelcar1.Update();
        refuelcar2.Update();
        Car1.Update();
        Car2.Update();

        //Entities display
        Draw(buffer);
        repaircar1.Draw(buffer);
        repaircar2.Draw(buffer);
        refuelcar1.Draw(buffer);
        refuelcar2.Draw(buffer);
        Car1.Draw(buffer);
        Car2.Draw(buffer);

        //Use of keyboard for cars' speed modification
        if(key[KEY_E] && Car1.Getspeed() < 10)
            Car1.Setspeed(Car1.Getspeed()+1);
        if(key[KEY_D] && Car1.Getspeed() > 1)
            Car1.Setspeed(Car1.Getspeed()-1);
        if(key[KEY_R] && Car2.Getspeed() < 10)
            Car2.Setspeed(Car2.Getspeed()+1);
        if(key[KEY_F] && Car2.Getspeed() > 1)
            Car2.Setspeed(Car2.Getspeed()-1);

        //Cars'speed display
        textprintf_ex(buffer, font,X11+5,Y1+280, COLOR_WHITE,-1,"Press E/D to change car 1 speed:    %d",Car1.Getspeed());
            circlefill(buffer, X11+60+215, Y1+280+3, 5, Car1.GetColor());
        textprintf_ex(buffer, font,X11+5,Y1+300, COLOR_WHITE,-1,"Press R/F to change car 2 speed:    %d",Car2.Getspeed());
            circlefill(buffer, X11+60+215, Y1+300+3, 5, Car2.GetColor());

        //Buffer's blitting on screen
        acquire_screen();
            blit (buffer, screen, 0, 0, 0, 0,SCREEN_W-1,SCREEN_H-1);
        release_screen();

        //temporisation
        rest(10);
    }

    //end program
    allegro_exit();

    return 0;
}
END_OF_MAIN()
