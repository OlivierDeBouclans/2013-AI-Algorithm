
/**----------------------------------------------------------------------
// @Class: Repair Car related states (cpp file)
//
// @Autor: LE BAS DE BOUCLANS Olivier
// @Date: 13/10/13
//
// @Description: Implementation of each possible state for the repair Car.
// Each state follow the singleton design: Wait,In,Out,Go,Back,Refuel
//----------------------------------------------------------------------**/

#include "StateRepairCar.h"
#include "StateCar.h"

/**--------------------------------
// @State: Wait
// @Description: Normal state. Waiting
// for the car to need help
//---------------------------------**/
//Initialisation of the singleton pointer
RepairCarWait* RepairCarWait::m_instance = 0;

void RepairCarWait::Execute(RepairCar* car)
{
    //Check if the car need help
    if(car->GetCar()->Getused()==0)
        car->GetStateMachine()->ChangeState(REPAIRCAR_OUT);
};

/**--------------------------------
// @State: Repair
// @Description: Repair the car that
// need it
//---------------------------------**/
//Initialisation of the singleton pointer
RepairCarRepair* RepairCarRepair::m_instance = 0;

void RepairCarRepair::Execute(RepairCar* car)
{
    //Repare the car
    if( car->GetCar()->Getused()!=car->GetCar()->GetusedMax())
        {
            car->GetCar()->Repair();
        }
    //The car can go on and the fuel car can go back
    else
        {
            car->GetStateMachine()->ChangeState(REPAIRCAR_BACK);
            car->GetCar()->GetStateMachine()->ChangeState(CAR_DRIVE);
        }

};

/**--------------------------------
// @State: Back
// @Description: Go  back to the
// waiting zone
//---------------------------------**/
//Initialisation of the singleton pointer
RepairCarBack* RepairCarBack::m_instance = 0;

void RepairCarBack::Execute(RepairCar* car)
{
    int road=car->Getroad();
    int x=car->Getx();
    int y=car->Gety();

    //Chose the closest half of the circuit
    int speed = x-X6 < 0 ? -1 : 1;

    //Go in if close to the area
    if(x==tab_x[road][6] && y==tab_y[road][6])
        car->GetStateMachine()->ChangeState(REPAIRCAR_IN);

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
RepairCarOut* RepairCarOut::m_instance = 0;

void RepairCarOut::Execute(RepairCar* car)
{
    int road=car->Getroad();
    int x=car->Getx();
    int y=car->Gety();

    //Go out off the waiting zone
    if( y!=tab_y[road][6])
        {
            int sgn = tab_y[road][6]-y < 0 ? -1 : 1;
            car->Sety(y+sgn);
        }

    //then go to the helpless car
    else { car->GetStateMachine()->ChangeState(REPAIRCAR_GO);}
};

/**--------------------------------
// @State: In
// @Description: Enter in the waiting
// zone
//---------------------------------**/
//Initialisation of the singleton pointer
RepairCarIn* RepairCarIn::m_instance = 0;

void RepairCarIn::Execute(RepairCar* car)
{
    int road=car->Getroad();
    int x=car->Getx();
    int y=car->Gety();

    //Enter the waiting zone
    if( y!=tab_y[road][8])
        {
            int sgn = tab_y[road][8]-y < 0 ? -1 : 1;
            car->Sety(y+sgn);
        }

    //And wait
    else { car->GetStateMachine()->ChangeState(REPAIRCAR_WAIT);}


};

/**--------------------------------
// @State: Go
// @Description: Drive to the stoped
// car
//---------------------------------**/
//Initialisation of the singleton pointer
RepairCarGo* RepairCarGo::m_instance = 0;

void RepairCarGo::Execute(RepairCar* car)
{
    int road=car->Getroad();
    int x=car->Getx();
    int y=car->Gety();
    int x2=car->GetCar()->Getx();
    int y2=car->GetCar()->Gety();

    //Chose the closest half of the circuit
    int speed = X6-x2 < 0 ? 1 : -1;

    //Repair if the car is reached
    if(x==x2 && y==y2)
        car->GetStateMachine()->ChangeState(REPAIRCAR_REPAIR);

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
