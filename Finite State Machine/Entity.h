
/**----------------------------------------------------------------------
// @Class: Entity
//
// @Autor: LE BAS DE BOUCLANS Olivier
// @Date: 13/10/13
//
// @Description: Description for base entity of the game
//----------------------------------------------------------------------**/

#ifndef ENTITY_H
#define ENTITY_H

class Entity
{
    public:
        //Constructor
        Entity() {}
        //Destructor
        ~Entity() {};

        //Getter
        int GetColor() { return m_color;}
        int Getx()     { return m_x; }
        int Gety()     { return m_y; }
        int Getspeed() { return m_speed; }
        int Getroad()  { return m_road; }

        //Setter
        void SetColor(int val) { m_color = val;}
        void Setx(int val) { m_x = val; }
        void Sety(int val) { m_y = val; }
        void Setspeed(int val) { m_speed = val; }
        void Setroad(int val) { m_road = val; }

    protected:
        //coordinate
        int m_x;
        int m_y;

        //speed
        int m_speed;

        //road
        int m_road; //1: interior road, 0: exterior road

        //color
        int m_color;

    private:

};

#endif // ENTITY_H
