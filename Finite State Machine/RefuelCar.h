
/**----------------------------------------------------------------------
// @Class: Refuel Car (inherit Entity)
//
// @Autor: LE BAS DE BOUCLANS Olivier
// @Date: 13/10/13
//
// @Description: Implementation for refuel car (refil the designed car with
// fuel)
//----------------------------------------------------------------------**/

#ifndef REFUELCAR_H
#define REFUELCAR_H

#include "allegro.h"
#include "Points.h"

#include "Entity.h"
#include "StateMachine.h"
#include "Car.h"

class RefuelCar : public Entity
{
    public:
        //Constructor
        RefuelCar(Car *car, State<RefuelCar> *state):m_car(car)
        {
            m_x=tab_x[car->Getroad()][7];
            m_y=tab_y[car->Getroad()][7];
            m_color = COLOR_ORANGE;
            m_speed=1;
            m_road=m_car->Getroad();

            m_StateMachine = new StateMachine<RefuelCar>(this,state);
        }
        //Destructor
        virtual ~RefuelCar() {delete(m_StateMachine);}

        //Getter
        StateMachine<RefuelCar>* GetStateMachine() { return m_StateMachine; }
        Car* GetCar() {return m_car;}

    protected:

    private:
        Car* m_car; //car assigned to refuel
        StateMachine<RefuelCar> *m_StateMachine; //FSM

    public:

        //Display entity on screen
        void Draw(BITMAP* buffer)
        {
            circlefill(buffer, m_x, m_y, 5, m_color);

            if(m_car->Getroad()==0)
            {
                textprintf_ex(buffer, font,X11+5,Y1+200, COLOR_WHITE,-1,"RefuelCar 1:   %s",m_StateMachine->GetCurrentState()->ToString());
                circlefill(buffer, X11+60+50, Y1+200+3, 5, m_color);
            }
            else
            {
                textprintf_ex(buffer, font,X11+5,Y1+220, COLOR_WHITE,-1,"RefuelCar 2:   %s",m_StateMachine->GetCurrentState()->ToString());
                circlefill(buffer, X11+60+50, Y1+220+3, 5, m_color);
            }

        }

        //Update the FSM
        void Update() {m_StateMachine->Update();}

};

#endif // REFUELCAR_H
