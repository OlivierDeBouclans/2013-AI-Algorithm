
/**----------------------------------------------------------------------
// @Class: StateMachine (template)
//
// @Autor: LE BAS DE BOUCLANS Olivier
// @Date: 13/10/13
//
// @Description: Implementation of the Finite State Machine for AI (one for
// each entity: car, RefuelCar, RepaintCar)
//----------------------------------------------------------------------**/

#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "State.h"

template <class Entity_type>
class StateMachine
{
    public:
        //Constructor
        StateMachine<Entity_type>(Entity_type *owner, State<Entity_type> *state)
            {
                m_owner = owner;
                m_currentState = state;
            }
        //Destructor
        ~StateMachine() {};

        //Getter
        State<Entity_type>* GetCurrentState() { return m_currentState;}

        //Change state
        void ChangeState(State<Entity_type> *state)
            {
                m_currentState->Exit(m_owner); //state action on exiting
                m_currentState = state;
                m_currentState->Enter(m_owner);//state action on entering
            }

        //Update: executing the action of the current state
        void Update()
            {
                m_currentState->Execute(m_owner);
            }

    protected:

    private:
        //Current state
        State<Entity_type> *m_currentState;
        //Pointer to the owner
        Entity_type *m_owner;

};

#endif // STATEMACHINE_H
