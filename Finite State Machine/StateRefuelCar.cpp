
/**----------------------------------------------------------------------
// @Class: Refuel Car related states (cpp file)
//
// @Autor: LE BAS DE BOUCLANS Olivier
// @Date: 13/10/13
//
// @Description: Implementation of each possible state for the refuel Car.
// Each state follow the singleton design: Wait,In,Out,Go,Back,Refuel
//----------------------------------------------------------------------**/

#include "StateRefuelCar.h"
#include "StateCar.h"

/**--------------------------------
// @State: Wait
// @Description: Normal state. Waiting
// for the car to need help
//---------------------------------**/
//Initialisation of the singleton pointer
RefuelCarWait* RefuelCarWait::m_instance = 0;

void RefuelCarWait::Execute(RefuelCar* car)
{
    //Check if the car need help
    if(car->GetCar()->Getfuel()==0)
        car->GetStateMachine()->ChangeState(REFUELCAR_OUT);
};

/**--------------------------------
// @State: Refuel
// @Description: Refuel the car that
// need it
//---------------------------------**/
//Initialisation of the singleton pointer
RefuelCarRefuel* RefuelCarRefuel::m_instance = 0;

void RefuelCarRefuel::Execute(RefuelCar* car)
{
    //Refuel the car
    if( car->GetCar()->Getfuel()!=car->GetCar()->GetfuelMax())
        {
            car->GetCar()->Refuel();
        }
    //The car can go on and the fuel car can go back
    else
        {
            car->GetStateMachine()->ChangeState(REFUELCAR_BACK);
            car->GetCar()->GetStateMachine()->ChangeState(CAR_DRIVE);
        }

};


/**--------------------------------
// @State: Back
// @Description: Go  back to the
// waiting zone
//---------------------------------**/
//Initialisation of the singleton pointer
RefuelCarBack* RefuelCarBack::m_instance = 0;

void RefuelCarBack::Execute(RefuelCar* car)
{
    int road=car->Getroad();
    int x=car->Getx();
    int y=car->Gety();

    //Chose the closest half of the circuit
    int speed = X6-x < 0 ? 1 : -1;

    //Go in if close to the area
    if(x==tab_x[road][3] && y==tab_y[road][3])
        car->GetStateMachine()->ChangeState(REFUELCAR_IN);

    //Driving depending of the corner
    if( x==tab_x[road][0]  && speed*y<speed*tab_y[road][1+speed])
        {
            car->Sety(y+speed);
            car->Setx(tab_x[road][0]);
        }
    else if( speed*x>speed*tab_x[road][3+speed]  && y==tab_y[road][2])
        {
            car->Setx(x-speed);
            car->Sety(tab_y[road][2]);
        }
    else if( x==tab_x[road][4]  && speed*y>speed*tab_y[road][4+speed])
        {
            car->Sety(y-speed);
            car->Setx(tab_x[road][4]);
        }
    else if(speed*x<speed*tab_x[road][(6+speed) % 7]  &&  y==tab_y[road][5])
        {
            car->Setx(x+speed);
            car->Sety(tab_y[road][5]);
        }
};

/**--------------------------------
// @State: Out
// @Description: Exit in the waiting
// zone
//---------------------------------**/
//Initialisation of the singleton pointer
RefuelCarOut* RefuelCarOut::m_instance = 0;

void RefuelCarOut::Execute(RefuelCar* car)
{
    int road=car->Getroad();
    int x=car->Getx();
    int y=car->Gety();

    //Go out off the waiting zone
    if( y!=tab_y[road][3])
        {
            int sgn = tab_y[road][3]-y < 0 ? -1 : 1;
            car->Sety(y+sgn);
        }
    //then go to the helpless car
    else { car->GetStateMachine()->ChangeState(REFUELCAR_GO);}
};

/**--------------------------------
// @State: In
// @Description: Enter in the waiting
// zone
//---------------------------------**/
//Initialisation of the singleton pointer
RefuelCarIn* RefuelCarIn::m_instance = 0;

void RefuelCarIn::Execute(RefuelCar* car)
{
    int road=car->Getroad();
    int x=car->Getx();
    int y=car->Gety();

    //Enter the waiting zone
    if( y!=tab_y[road][7])
        {
            int sgn = tab_y[road][7]-y < 0 ? -1 : 1;
            car->Sety(y+sgn);
        }
    //and then wait
    else { car->GetStateMachine()->ChangeState(REFUELCAR_WAIT);}


};

/**--------------------------------
// @State: Go
// @Description: Drive to the stoped
// car
//---------------------------------**/
//Initialisation of the singleton pointer
RefuelCarGo* RefuelCarGo::m_instance = 0;

void RefuelCarGo::Execute(RefuelCar* car)
{
    int road=car->Getroad();
    int x=car->Getx();
    int y=car->Gety();
    int x2=car->GetCar()->Getx();
    int y2=car->GetCar()->Gety();

    //Chose the closest half of the circuit
    int speed = X6-x2 < 0 ? -1 : 1;

    //Refuel if the car is reached
    if(x==x2 && y==y2)
        car->GetStateMachine()->ChangeState(REFUELCAR_REFUEL);

    //Drive depending on the corner
    if( x==tab_x[road][0]  && speed*y<speed*tab_y[road][1+speed])
        {
            car->Sety(y+speed);
            car->Setx(tab_x[road][0]);
        }
    else if( speed*x>speed*tab_x[road][3+speed]  && y==tab_y[road][2])
        {
            car->Setx(x-speed);
            car->Sety(tab_y[road][2]);
        }
    else if( x==tab_x[road][4]  && speed*y>speed*tab_y[road][4+speed])
        {
            car->Sety(y-speed);
            car->Setx(tab_x[road][4]);
        }
    else if(speed*x<speed*tab_x[road][(6+speed) % 7]  &&  y==tab_y[road][5])
        {
            car->Setx(x+speed);
            car->Sety(tab_y[road][5]);
        }
};
