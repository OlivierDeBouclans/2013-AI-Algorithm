
/**----------------------------------------------------------------------
// @Class: Car related states
//
// @Autor: LE BAS DE BOUCLANS Olivier
// @Date: 13/10/13
//
// @Description: Implementation of each possible state for the entity Car.
// Each state follow the singleton design: Drive,OutofGas,Refuel,Repair,Broken
//----------------------------------------------------------------------**/

#ifndef STATECAR_H
#define STATECAR_H

#include "Car.h"
#include "State.h"

//Instance for each state
#define CAR_DRIVE    CarDrive::Instance()
#define CAR_REFUEL   CarRefuel::Instance()
#define CAR_REPAIR   CarRepair::Instance()
#define CAR_OUTOFGAS CarOutOfGas::Instance()
#define CAR_BROKEN   CarBroken::Instance()

/**--------------------------------
// @State: Drive
// @Description: Normal state. Driving
// on the circuit.
//---------------------------------**/
class CarDrive : public State<Car>
{
    private:
        //Constructor
        CarDrive(){}
        //Pointer to the singleton
        static CarDrive* m_instance;

    public:
        //Destructor
        virtual ~CarDrive() {}

        //singleton pointer
        static CarDrive* Instance()
        {
            if ( m_instance == 0 )
                m_instance = new CarDrive;
            return m_instance;
        }

        //Action on entering the state
        virtual void Enter(Car*) {};
        //Action on exiting the state
        virtual void Exit(Car*) {};
        //Action on updating
        virtual void Execute(Car*);
        //Description of the state
        virtual char* ToString() { return "Driving";}

    protected:

};

/**--------------------------------
// @State: Refuel
// @Description: Car go itself for gas
//---------------------------------**/
class CarRefuel : public State<Car>
{

    private:
        //Constructor
        CarRefuel(){}
        //Pointer to the singletion
        static CarRefuel* m_instance;

    public:
        //Destructor
        virtual ~CarRefuel() {}

        //Pointer to the singleton
        static CarRefuel* Instance()
        {
            if ( m_instance == 0 )
                m_instance = new CarRefuel;
            return m_instance;
        }

        //Action on entering the state
        virtual void Enter(Car*) {};
        //Action on exiting the state
        virtual void Exit(Car*) {};
        //Action on updating
        virtual void Execute(Car*);
        //Description of the state
        virtual char* ToString() {return "Refueling...";}

    protected:

};

/**--------------------------------
// @State: Repair
// @Description: Car go itself for repair
//---------------------------------**/
class CarRepair : public State<Car>
{

    private:
        //Constructor
        CarRepair(){}
        //Pointer to the singletion
        static CarRepair* m_instance;

    public:
        //Destructor
        virtual ~CarRepair() {}

        //Pointer to the singleton
        static CarRepair* Instance()
        {
            if ( m_instance == 0 )
                m_instance = new CarRepair;
            return m_instance;
        }

        //Action on entering the state
        virtual void Enter(Car*) {};
        //Action on exiting the state
        virtual void Exit(Car*) {};
        //Action on updating
        virtual void Execute(Car*);
        //Description of the state
        virtual char* ToString() { return "Repairing...";}

    protected:

};

/**--------------------------------
// @State: Out of Gas
// @Description: Car run out of gas
// and wait for help (fuel)
//---------------------------------**/
class CarOutOfGas : public State<Car>
{

    private:
        //Constructor
        CarOutOfGas(){}
        //Pointer to the singletion
        static CarOutOfGas* m_instance;

    public:
        //Destructor
        virtual ~CarOutOfGas() {}

        //Pointer to the singleton
        static CarOutOfGas* Instance()
        {
            if ( m_instance == 0 )
                m_instance = new CarOutOfGas;
            return m_instance;
        }

        //Action on entering the state
        virtual void Enter(Car*);
        //Action on exiting the state
        virtual void Exit(Car*);
        //Action on updating
        virtual void Execute(Car*) {};
        //Description of the state
        virtual char* ToString() { return "Out of gas !";}

    protected:

};

/**--------------------------------
// @State: Broken
// @Description: Car is broken
// and wait for help (repairation)
//---------------------------------**/
class CarBroken : public State<Car>
{

    private:
        //Constructor
        CarBroken(){}
        //Pointer to the singletion
        static CarBroken* m_instance;

    public:
        //Destructor
        virtual ~CarBroken() {}

        //Pointer to the singleton
        static CarBroken* Instance()
        {
            if ( m_instance == 0 )
                m_instance = new CarBroken;
            return m_instance;
        }

        //Action on entering the state
        virtual void Enter(Car*);
        //Action on exiting the state
        virtual void Exit(Car*);
        //Action on updating
        virtual void Execute(Car*) {};
        //Description of the state
        virtual char* ToString() { return "Broken !"; }

    protected:

};

#endif // STATECAR_H
