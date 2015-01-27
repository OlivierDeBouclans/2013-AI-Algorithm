
/**----------------------------------------------------------------------
// @Class: Car related states (cpp file)
//
// @Autor: LE BAS DE BOUCLANS Olivier
// @Date: 13/10/13
//
// @Description: Implementation of each possible state for the entity Car.
// Each state follow the singleton design: Drive,OutofGas,Refuel,Repair,Broken
//----------------------------------------------------------------------**/

#include "StateCar.h"
#include "Points.h"

/**--------------------------------
// @State: Drive
// @Description: Normal state. Driving
// on the circuit.
//---------------------------------**/
//Initialisation of the singleton pointer
CarDrive* CarDrive::m_instance = 0;

void CarDrive::Execute(Car* car)
{
    int road=car->Getroad();
    int x=car->Getx();
    int y=car->Gety();

    //Usage of the car (fuel and state)
    car->Used();

    //Run out of gas
    if(car->Getfuel()==0)
        car->GetStateMachine()->ChangeState(CAR_OUTOFGAS);

    //Broken
    if(car->Getused()==0)
        car->GetStateMachine()->ChangeState(CAR_BROKEN);

    //Chance to get repaired or refueled
    if(x<X6+5 && x>X6-5)
    {
        //if fuel under the threshold go refuel
        if(y==tab_y[road][3] && (car->Getfuel()*100/car->GetfuelMax()) < PERCENT_FUEL)
            car->GetStateMachine()->ChangeState(CAR_REFUEL);

        //if state under the threshold go repair
        if(y==tab_y[road][6] && (car->Getused()*100/car->GetusedMax()) < PERCENT_REPAIR)
            car->GetStateMachine()->ChangeState(CAR_REPAIR);
    }

    //Driving depending on the corner
    if( x>=tab_x[road][0]  && y<tab_y[road][2])
        {
            car->Sety(y+car->Getspeed());
            car->Setx(tab_x[road][0]);
        }
    else if( x>tab_x[road][4]  && y>=tab_y[road][2])
        {
            car->Setx(x-car->Getspeed());
            car->Sety(tab_y[road][2]);
        }
    else if( x<=tab_x[road][4]  && y>tab_y[road][5])
        {
            car->Sety(y-car->Getspeed());
            car->Setx(tab_x[road][4]);
        }
    else if( x<tab_x[road][0]  && y<=tab_y[road][5])
        {
            car->Setx(x+car->Getspeed());
            car->Sety(tab_y[road][5]);
        }

    //If the car pass throught the startinf line, lap++
    int y2=car->Gety();
    if(y<=Y7 && y2>Y7)
        car->Lap();
};

/**--------------------------------
// @State: Refuel
// @Description: Car go itself for gas
//---------------------------------**/
//Initialisation of the singleton pointer
CarRefuel* CarRefuel::m_instance = 0;

void CarRefuel::Execute(Car* car)
{
    int road=car->Getroad();
    int x=car->Getx();
    int y=car->Gety();

    //Enter the refuel area
    if( y!=tab_y[road][7] && car->Getfuel()<car->GetfuelMax())
        {
            int sgn = tab_y[road][7]-y < 0 ? -1 : 1;
            car->Sety(y+sgn);
            car->Setx(tab_x[road][3]);
        }
    //Refuel
    else if(y==tab_y[road][7] && car->Getfuel()<car->GetfuelMax())
        {
            car->Refuel();
        }
    //Exit the refuel area
    else if(y!=tab_y[road][3] && car->Getfuel()==car->GetfuelMax())
        {
            int sgn = tab_y[road][3]-y < 0 ? -1 : 1;
            car->Sety(y+sgn);
        }
    //Return to driving after refueling
    else if(y==tab_y[road][3] && car->Getfuel()==car->GetfuelMax())
        {
            car->GetStateMachine()->ChangeState(CAR_DRIVE);
        }

};


/**--------------------------------
// @State: Repair
// @Description: Car go itself for repair
//---------------------------------**/
//Initialisation of the singleton pointer
CarRepair* CarRepair::m_instance = 0;

void CarRepair::Execute(Car* car)
{
    int road=car->Getroad();
    int x=car->Getx();
    int y=car->Gety();

    //Enter the reparation area
    if( y!=tab_y[road][8] && car->Getused()<car->GetusedMax())
        {
            int sgn = tab_y[road][8]-y < 0 ? -1 : 1;
            car->Sety(y+sgn);
            car->Setx(tab_x[road][6]);
        }
    //Reparation
    else if( y==tab_y[road][8] && car->Getused()<car->GetusedMax())
        {
            car->Repair();
        }
    //Exit the reparation area
    else if( y!=tab_y[road][6] && car->Getused()==car->GetusedMax())
        {
            int sgn = tab_y[road][6]-y < 0 ? -1 : 1;
            car->Sety(y+sgn);
        }
    //Return to driving after repairing
    else if( y==tab_y[road][6] && car->Getused()==car->GetusedMax())
        {
            car->GetStateMachine()->ChangeState(CAR_DRIVE);
        }
};

/**--------------------------------
// @State: Out of Gas
// @Description: Car run out of gas
// and wait for help (fuel)
//---------------------------------**/
//Initialisation of the singleton pointer
CarOutOfGas* CarOutOfGas::m_instance = 0;

void CarOutOfGas::Enter(Car* car)
{
    car->SwitchColor(COLOR_GRAY);
};

void CarOutOfGas::Exit(Car* car)
{
    car->SwitchColor();
};


/**--------------------------------
// @State: Broken
// @Description: Car is broken
// and wait for help (repairation)
//---------------------------------**/
//Initialisation of the singleton pointer
CarBroken* CarBroken::m_instance = 0;

void CarBroken::Enter(Car* car)
{
    car->SwitchColor(COLOR_GRAY);
};

void CarBroken::Exit(Car* car)
{
    car->SwitchColor();
};
