
/**----------------------------------------------------------------------
// @Class: Car (inherit Entity)
//
// @Autor: LE BAS DE BOUCLANS Olivier
// @Date: 13/10/13
//
// @Description: Implementation for running car (with fuel,state,lap)
//----------------------------------------------------------------------**/

#ifndef CAR_H
#define CAR_H

#include "Points.h"
#include "allegro.h"

#include "Entity.h"
#include "StateMachine.h"

class Car : public Entity
{
    public:
        //Constructor
        Car(int a, int b, State<Car> *state):m_fuel(a), m_fuelMax(a), m_used(b), m_usedMax(b),m_lap(0)
            {m_StateMachine = new StateMachine<Car>(this,state);}
        //Destructor
        ~Car() {delete(m_StateMachine);}

        //Getter
        int Getfuel()    { return m_fuel; }
        int GetfuelMax() { return m_fuelMax; }
        int GetusedMax() { return m_usedMax; }
        int Getused()    { return m_used; }
        int Getlap()     { return m_lap; }
        StateMachine<Car>* GetStateMachine() { return m_StateMachine; }

        //Setter
        void Setfuel(int val)    { m_fuel = val; }
        void SetfuelMax(int val) { m_fuelMax = val; }
        void SetusedMax(int val) { m_usedMax = val; }
        void Setused(int val)    { m_used = val; }

    protected:

    private:
        int m_fuel;    //remaining fuel
        int m_fuelMax; //maximum fuel
        int m_used;    //current state
        int m_usedMax; //maximum resistance
        int m_lap;     //lap's number
        int m_previouscolor; //previous color
        StateMachine<Car> *m_StateMachine; //FSM

    public:

        //Display car on screen
        void Draw(BITMAP* buffer)
        {
            circlefill(buffer, m_x, m_y, 5, m_color);

            if(m_road==0)
            {
                textprintf_ex(buffer, font,X11+5,Y1, COLOR_WHITE,-1,"Car 1:");
                circlefill(buffer, X11+60, Y1+3, 5, m_color);

                textprintf_ex(buffer, font,X11+5,Y1+17, COLOR_WHITE,-1,"Fuel:");
                rectfill(buffer,X11+5+50,Y1+16,X11+50+BARW,Y1+6+BARH,COLOR_WHITE);
                rectfill(buffer,X11+6+50,Y1+17,X11+6+50+(BARW-7)*m_fuel/m_fuelMax,Y1+5+BARH,COLOR_RED);

                textprintf_ex(buffer, font,X11+5,Y1+37, COLOR_WHITE,-1,"State:");
                rectfill(buffer,X11+5+50,Y1+36,X11+50+BARW,Y1+26+BARH,COLOR_WHITE);
                rectfill(buffer,X11+6+50,Y1+37,X11+6+50+(BARW-7)*m_used/m_usedMax,Y1+25+BARH,COLOR_RED);

                textprintf_ex(buffer, font,X11+50+BARW+10,Y1+16, COLOR_WHITE,-1,"Lap: %d", m_lap);
                textprintf_ex(buffer, font,X11+50+BARW+10,Y1+36, COLOR_WHITE,-1,"Status: %s", m_StateMachine->GetCurrentState()->ToString());
            }
            else
            {
                textprintf_ex(buffer, font,X11+5,Y1+80, COLOR_WHITE,-1,"Car 2:");
                circlefill(buffer, X11+60, Y1+3+80, 5, m_color);

                textprintf_ex(buffer, font,X11+5,Y1+80+17, COLOR_WHITE,-1,"Fuel:");
                rectfill(buffer,X11+5+50,Y1+80+16,X11+50+BARW,Y1+80+6+BARH,COLOR_WHITE);
                rectfill(buffer,X11+6+50,Y1+80+17,X11+6+50+(BARW-7)*m_fuel/m_fuelMax,Y1+80+5+BARH,COLOR_RED);

                textprintf_ex(buffer, font,X11+5,Y1+80+37, COLOR_WHITE,-1,"State:");
                rectfill(buffer,X11+5+50,Y1+80+36,X11+50+BARW,Y1+80+26+BARH,COLOR_WHITE);
                rectfill(buffer,X11+6+50,Y1+80+37,X11+6+50+(BARW-7)*m_used/m_usedMax,Y1+80+25+BARH,COLOR_RED);

                textprintf_ex(buffer, font,X11+50+BARW+10,Y1+80+16, COLOR_WHITE,-1,"Lap: %d", m_lap);
                textprintf_ex(buffer, font,X11+50+BARW+10,Y1+80+36, COLOR_WHITE,-1,"Status: %s", m_StateMachine->GetCurrentState()->ToString());
            }
        }

        //Update the FSM
        void Update() {m_StateMachine->Update();}

        //Use of the car (fuel and state)
        void Used()
        {
            if(m_fuel>0)
                m_fuel-=m_speed*3;
            if(m_fuel<0)
                m_fuel=0;

            if(m_used>0)
                m_used-=m_speed+8;
            if(m_used<0)
                m_used=0;
        }

        //Refuel the car
        void Refuel()
        {
            if(m_fuel < m_fuelMax)
                m_fuel+=80;

            if (m_fuel>m_fuelMax)
                m_fuel=m_fuelMax;
        }

        //Repair the car
        void Repair()
        {
            if(m_used< m_usedMax)
                m_used+=80;

            if(m_used> m_usedMax)
                m_used=m_usedMax;
        }

        //New lap
        void Lap()  { m_lap++; }

        //Change the car color (or switch back)
        void SwitchColor(int color) { m_previouscolor = m_color; m_color=color;}
        void SwitchColor() { m_color = m_previouscolor; }
};

#endif // CAR_H
