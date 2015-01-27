
/**----------------------------------------------------------------------
// @Class: Repair Car (inherit Entity)
//
// @Autor: LE BAS DE BOUCLANS Olivier
// @Date: 13/10/13
//
// @Description: Implementation for repair car (repair the designed car)
//----------------------------------------------------------------------**/

#ifndef REPAIRCAR_H
#define REPAIRCAR_H

#include "allegro.h"
#include "Points.h"

#include "Entity.h"
#include "StateMachine.h"
#include "Car.h"

class RepairCar : public Entity
{
    public:
        //Constructor
        RepairCar(Car *car, State<RepairCar> *state):m_car(car)
        {
            m_x=tab_x[car->Getroad()][8];
            m_y=tab_y[car->Getroad()][8];
            m_color = COLOR_YELLOW;
            m_speed=1;
            m_road=car->Getroad();

            m_StateMachine = new StateMachine<RepairCar>(this,state);
        }
        //Destructor
        virtual ~RepairCar() {delete(m_StateMachine);}

        //Getter
        StateMachine<RepairCar>* GetStateMachine() { return m_StateMachine; }
        Car* GetCar() {return m_car;}

    protected:

    private:
        Car* m_car; //car assigned to refuel
        StateMachine<RepairCar> *m_StateMachine; //FSM

    public:

        //Display entity on screen
        void Draw(BITMAP* buffer)
        {
            circlefill(buffer, m_x, m_y, 5, m_color);

            if(m_car->Getroad()==0)
            {
                textprintf_ex(buffer, font,X11+5,Y1+160, COLOR_WHITE,-1,"RepairCar 1:   %s",m_StateMachine->GetCurrentState()->ToString());
                circlefill(buffer, X11+60+50, Y1+160+3, 5, m_color);
            }
            else
            {
                textprintf_ex(buffer, font,X11+5,Y1+180, COLOR_WHITE,-1,"RepairCar 2:   %s",m_StateMachine->GetCurrentState()->ToString());
                circlefill(buffer, X11+60+50, Y1+180+3, 5, m_color);
            }
        }

        //Update the FSM
        void Update() {m_StateMachine->Update();}
};

#endif // REPAIRCAR_H
