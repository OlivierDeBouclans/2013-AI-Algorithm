
/**----------------------------------------------------------------------
// @Class: State (template)
//
// @Autor: LE BAS DE BOUCLANS Olivier
// @Date: 13/10/13
//
// @Description: Implementation for a AI state (template for each kind of
// entity: Car, RepairCar, RefuelCar)
//----------------------------------------------------------------------**/

#ifndef STATE_H
#define STATE_H

template <class Entity_type>
class State
{
    public:
        //Constructor
        State() {};
        //Destructor
        virtual ~State(){};

        //Action on entering the state
        virtual void Enter(Entity_type*) =0;
        //Action on exiting the state
        virtual void Exit(Entity_type*) =0;
        //Action on updating
        virtual void Execute(Entity_type*) =0;
        //Description of the state
        virtual char* ToString() =0;

    protected:

    private:
};

#endif // STATE_H
