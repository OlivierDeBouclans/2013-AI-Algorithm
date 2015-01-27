/**----------------------------------------------------------------------
// @Class: Refuel Car related states
//
// @Autor: LE BAS DE BOUCLANS Olivier
// @Date: 13/10/13
//
// @Description: Implementation of each possible state for the refuel Car.
// Each state follow the singleton design: Wait,In,Out,Go,Back,Refuel
//----------------------------------------------------------------------**/

#ifndef STATEREFULCAR_H
#define STATEREFULCAR_H

#include "State.h"
#include "RefuelCar.h"

//Instance for each state
#define REFUELCAR_WAIT    RefuelCarWait::Instance()
#define REFUELCAR_REFUEL  RefuelCarRefuel::Instance()
#define REFUELCAR_IN      RefuelCarIn::Instance()
#define REFUELCAR_OUT     RefuelCarOut::Instance()
#define REFUELCAR_GO      RefuelCarGo::Instance()
#define REFUELCAR_BACK    RefuelCarBack::Instance()

/**--------------------------------
// @State: Wait
// @Description: Normal state. Waiting
// for the car to need help
//---------------------------------**/
class RefuelCarWait : public State<RefuelCar>
{
    private:
        //Constructor
        RefuelCarWait(){}
        //Pointer to the singleton
        static RefuelCarWait* m_instance;

    public:
        //Destructor
        virtual ~RefuelCarWait() {}

        //singleton pointer
        static RefuelCarWait* Instance()
        {
            if ( m_instance == 0 )
                m_instance = new RefuelCarWait;
            return m_instance;
        }

        //Action on entering the state
        virtual void Enter(RefuelCar*) {};
        //Action on exiting the state
        virtual void Exit(RefuelCar*) {};
        //Action on updating
        virtual void Execute(RefuelCar*);
        //Description of the state
        virtual char* ToString() { return "Waiting...";}

    protected:

};

/**--------------------------------
// @State: Refuel
// @Description: Refuel the car that
// need it
//---------------------------------**/
class RefuelCarRefuel : public State<RefuelCar>
{

    private:
        //Constructor
        RefuelCarRefuel(){}
        //Pointer to the singleton
        static RefuelCarRefuel* m_instance;

    public:
        //Destructor
        virtual ~RefuelCarRefuel() {}

        //singleton pointer
        static RefuelCarRefuel* Instance()
        {
            if ( m_instance == 0 )
                m_instance = new RefuelCarRefuel;
            return m_instance;
        }

        //Action on entering the state
        virtual void Enter(RefuelCar*) {};
        //Action on exiting the state
        virtual void Exit(RefuelCar*) {};
        //Action on updating
        virtual void Execute(RefuelCar*);
        //Description of the state
        virtual char* ToString() { return "Refueling...";}

    protected:

};

/**--------------------------------
// @State: In
// @Description: Enter in the waiting
// zone
//---------------------------------**/
class RefuelCarIn : public State<RefuelCar>
{

    private:
        //Constructor
        RefuelCarIn(){}
        //Pointer to the singleton
        static RefuelCarIn* m_instance;

    public:
        //Destructor
        virtual ~RefuelCarIn() {}

        //singleton pointer
        static RefuelCarIn* Instance()
        {
            if ( m_instance == 0 )
                m_instance = new RefuelCarIn;
            return m_instance;
        }

        //Action on entering the state
        virtual void Enter(RefuelCar*) {};
        //Action on exiting the state
        virtual void Exit(RefuelCar*) {};
        //Action on updating
        virtual void Execute(RefuelCar*);
        //Description of the state
        virtual char* ToString() {return "IN";}

    protected:

};

/**--------------------------------
// @State: Out
// @Description: Exit in the waiting
// zone
//---------------------------------**/
class RefuelCarOut : public State<RefuelCar>
{

    private:
        //Constructor
        RefuelCarOut(){}
        //Pointer to the singleton
        static RefuelCarOut* m_instance;

    public:
        //Destructor
        virtual ~RefuelCarOut() {}

        //singleton pointer
        static RefuelCarOut* Instance()
        {
            if ( m_instance == 0 )
                m_instance = new RefuelCarOut;
            return m_instance;
        }

        //Action on entering the state
        virtual void Enter(RefuelCar*) {};
        //Action on exiting the state
        virtual void Exit(RefuelCar*) {};
        //Action on updating
        virtual void Execute(RefuelCar*);
        //Description of the state
        virtual char* ToString() { return "OUT";}

    protected:

};

/**--------------------------------
// @State: Back
// @Description: Go  back to the
// waiting zone
//---------------------------------**/
class RefuelCarBack : public State<RefuelCar>
{

    private:
        //Constructor
        RefuelCarBack(){}
        //Pointer to the singleton
        static RefuelCarBack* m_instance;

    public:
        //Destructor
        virtual ~RefuelCarBack() {}

        //singleton pointer
        static RefuelCarBack* Instance()
        {
            if ( m_instance == 0 )
                m_instance = new RefuelCarBack;
            return m_instance;
        }

        //Action on entering the state
        virtual void Enter(RefuelCar*) {};
        //Action on exiting the state
        virtual void Exit(RefuelCar*) {};
        //Action on updating
        virtual void Execute(RefuelCar*);
        //Description of the state
        virtual char* ToString() {return "Going back";}

    protected:

};

/**--------------------------------
// @State: Go
// @Description: Drive to the stoped
// car
//---------------------------------**/
class RefuelCarGo : public State<RefuelCar>
{

    private:
        //Constructor
        RefuelCarGo(){}
        //Pointer to the singleton
        static RefuelCarGo* m_instance;

    public:
        //Destructor
        virtual ~RefuelCarGo() {}

        //singleton pointer
        static RefuelCarGo* Instance()
        {
            if ( m_instance == 0 )
                m_instance = new RefuelCarGo;
            return m_instance;
        }

        //Action on entering the state
        virtual void Enter(RefuelCar*) {};
        //Action on exiting the state
        virtual void Exit(RefuelCar*) {};
        //Action on updating
        virtual void Execute(RefuelCar*);
        //Description of the state
        virtual char* ToString() { return "Go refueling";}

    protected:

};

#endif // STATEREFULCAR_H
