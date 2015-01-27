/**----------------------------------------------------------------------
// @Class: Repair Car related states
//
// @Autor: LE BAS DE BOUCLANS Olivier
// @Date: 13/10/13
//
// @Description: Implementation of each possible state for the repair Car.
// Each state follow the singleton design: Wait,In,Out,Go,Back,Refuel
//----------------------------------------------------------------------**/

#ifndef STATEREPAIRCAR_H
#define STATEREPAIRCAR_H

#include "State.h"
#include "RepairCar.h"

//Instance for each state
#define REPAIRCAR_WAIT    RepairCarWait::Instance()
#define REPAIRCAR_REPAIR  RepairCarRepair::Instance()
#define REPAIRCAR_IN      RepairCarIn::Instance()
#define REPAIRCAR_OUT     RepairCarOut::Instance()
#define REPAIRCAR_GO      RepairCarGo::Instance()
#define REPAIRCAR_BACK    RepairCarBack::Instance()

/**--------------------------------
// @State: Wait
// @Description: Normal state. Waiting
// for the car to need help
//---------------------------------**/
class RepairCarWait : public State<RepairCar>
{

    private:
        //Constructor
        RepairCarWait(){}
        //Pointer to the singleton
        static RepairCarWait* m_instance;

    public:
        //Destructor
        virtual ~RepairCarWait() {}

        //singleton pointer
        static RepairCarWait* Instance()
        {
            if ( m_instance == 0 )
                m_instance = new RepairCarWait;
            return m_instance;
        }

        //Action on entering the state
        virtual void Enter(RepairCar*) {};
        //Action on exiting the state
        virtual void Exit(RepairCar*) {};
        //Action on updating
        virtual void Execute(RepairCar*);
        //Description of the state
        virtual char* ToString() { return "Waiting..."; }

    protected:

};


class RepairCarRepair : public State<RepairCar>
{

    private:
        //Constructor
        RepairCarRepair(){}
        //Pointer to the singleton
        static RepairCarRepair* m_instance;

    public:
        //Destructor
        virtual ~RepairCarRepair() {}

        //singleton pointer
        static RepairCarRepair* Instance()
        {
            if ( m_instance == 0 )
                m_instance = new RepairCarRepair;
            return m_instance;
        }

        //Action on entering the state
        virtual void Enter(RepairCar*) {};
        //Action on exiting the state
        virtual void Exit(RepairCar*) {};
        //Action on updating
        virtual void Execute(RepairCar*);
        //Description of the state
        virtual char* ToString() { return "Repairing...";}

    protected:

};


class RepairCarIn : public State<RepairCar>
{

    private:
        //Constructor
        RepairCarIn(){}
        //Pointer to the singleton
        static RepairCarIn* m_instance;

    public:
        //Destructor
        virtual ~RepairCarIn() {}

        //singleton pointer
        static RepairCarIn* Instance()
        {
            if ( m_instance == 0 )
                m_instance = new RepairCarIn;
            return m_instance;
        }

        //Action on entering the state
        virtual void Enter(RepairCar*) {};
        //Action on exiting the state
        virtual void Exit(RepairCar*) {};
        //Action on updating
        virtual void Execute(RepairCar*);
        //Description of the state
        virtual char* ToString() { return "IN"; }

    protected:

};


class RepairCarOut : public State<RepairCar>
{

    private:
        //Constructor
        RepairCarOut(){}
        //Pointer to the singleton
        static RepairCarOut* m_instance;

    public:
        //Destructor
        virtual ~RepairCarOut() {}

        //singleton pointer
        static RepairCarOut* Instance()
        {
            if ( m_instance == 0 )
                m_instance = new RepairCarOut;
            return m_instance;
        }

        //Action on entering the state
        virtual void Enter(RepairCar*) {};
        //Action on exiting the state
        virtual void Exit(RepairCar*) {};
        //Action on updating
        virtual void Execute(RepairCar*);
        //Description of the state
        virtual char* ToString() { return "OUT"; }

    protected:

};


class RepairCarGo : public State<RepairCar>
{

    private:
        //Constructor
        RepairCarGo(){}
        //Pointer to the singleton
        static RepairCarGo* m_instance;

    public:
        //Destructor
        virtual ~RepairCarGo() {}

        //singleton pointer
        static RepairCarGo* Instance()
        {
            if ( m_instance == 0 )
                m_instance = new RepairCarGo;
            return m_instance;
        }

        //Action on entering the state
        virtual void Enter(RepairCar*) {};
        //Action on exiting the state
        virtual void Exit(RepairCar*) {};
        //Action on updating
        virtual void Execute(RepairCar*);
        //Description of the state
        virtual char* ToString() {return "Go repairing";}

    protected:

};


class RepairCarBack : public State<RepairCar>
{

    private:
        //Constructor
        RepairCarBack(){}
        //Pointer to the singleton
        static RepairCarBack* m_instance;

    public:
        //Destructor
        virtual ~RepairCarBack() {}

        //singleton pointer
        static RepairCarBack* Instance()
        {
            if ( m_instance == 0 )
                m_instance = new RepairCarBack;
            return m_instance;
        }

        //Action on entering the state
        virtual void Enter(RepairCar*) {};
        //Action on exiting the state
        virtual void Exit(RepairCar*) {};
        //Action on updating
        virtual void Execute(RepairCar*);
        //Description of the state
        virtual char* ToString() {return "Going back";}

    protected:

};


#endif // STATEREPAIRCAR_H
