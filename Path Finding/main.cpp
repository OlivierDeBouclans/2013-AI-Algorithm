
//Include
#include "allegro.h"
#include <vector>
#include <iostream>

#include "Graph.h"
#include "GraphSearch.h"

#define MAP_SIZE_H 20
#define MAP_SIZE_W 20
#define MAP_SIZE_SQUARE 30
#define MAP_NB_OBSTACLE 80

void drawMap( int* map, BITMAP* buffer)
{
    rectfill(buffer,5-1,5-1,5+1+MAP_SIZE_W*MAP_SIZE_SQUARE+1,5+1+MAP_SIZE_H*MAP_SIZE_SQUARE, makecol(255,255,255));
    for(int k=0;k<MAP_SIZE_W*MAP_SIZE_H;k++)
    {
        int color=0;

        rect(buffer,5+(k % MAP_SIZE_W)*MAP_SIZE_SQUARE,5+(k / MAP_SIZE_W)*MAP_SIZE_SQUARE,5+(k % MAP_SIZE_W+1)*MAP_SIZE_SQUARE,5+(k / MAP_SIZE_W+1)*MAP_SIZE_SQUARE,makecol(120,120,120));

        if(map[k]==0)
            color=makecol(0,0,0);
        if(map[k]==1)
               color=makecol(255,255,255);
        if(map[k]==2)
            color=makecol(255,0,0);
        if(map[k]==3)
            color=makecol(0,255,0);

        rectfill(buffer,5+(k % MAP_SIZE_W)*MAP_SIZE_SQUARE+1,5+(k / MAP_SIZE_W)*MAP_SIZE_SQUARE+1,5+(k % MAP_SIZE_W+1)*MAP_SIZE_SQUARE-1,5+(k / MAP_SIZE_W+1)*MAP_SIZE_SQUARE-1,color);

    }

    textprintf(buffer,font,5+MAP_SIZE_W*MAP_SIZE_SQUARE+10,20,makecol(255,255,255),"Press Enter - Restart map");
    textprintf(buffer,font,5+MAP_SIZE_W*MAP_SIZE_SQUARE+10,40,makecol(255,255,255),"Press 1     - DFS");
    textprintf(buffer,font,5+MAP_SIZE_W*MAP_SIZE_SQUARE+10,60,makecol(255,255,255),"Press 2     - BFS");
    textprintf(buffer,font,5+MAP_SIZE_W*MAP_SIZE_SQUARE+10,80,makecol(255,255,255),"Press 3     - A*");

}

void drawGraph( GraphSearch *g, int From, int To, BITMAP* buffer)
{
    for(int k=0; k<MAP_SIZE_H*MAP_SIZE_W;k++)
    {
        if(g->Route().at(k) > -1)
            line(buffer,5+(k % MAP_SIZE_W)*MAP_SIZE_SQUARE+15,5+(k / MAP_SIZE_W)*MAP_SIZE_SQUARE+15,5+(g->Route().at(k) % MAP_SIZE_W)*MAP_SIZE_SQUARE+15,5+(g->Route().at(k) / MAP_SIZE_W)*MAP_SIZE_SQUARE+15,makecol(0,255,255));

    }

    double cost=0;
    int k,parent = g->Route().at(To);
    line(buffer,5+(To % MAP_SIZE_W)*MAP_SIZE_SQUARE+15,5+(To / MAP_SIZE_W)*MAP_SIZE_SQUARE+15,5+(parent % MAP_SIZE_W)*MAP_SIZE_SQUARE+15,5+(parent / MAP_SIZE_W)*MAP_SIZE_SQUARE+15,makecol(255,0,0));
    if(g->Found())
    while(parent!=From)
    {
        k=g->Route().at(parent);
        line(buffer,5+(k % MAP_SIZE_W)*MAP_SIZE_SQUARE+15,5+(k / MAP_SIZE_W)*MAP_SIZE_SQUARE+15,5+(parent % MAP_SIZE_W)*MAP_SIZE_SQUARE+15,5+(parent / MAP_SIZE_W)*MAP_SIZE_SQUARE+15,makecol(255,0,0));
        cost +=g->GetGraph()->GetEdge(k,parent)->Cost();
        parent = g->Route().at(parent);
    };

    textprintf(buffer,font,5+MAP_SIZE_W*MAP_SIZE_SQUARE+10,100,makecol(255,255,255),"Cost: %f",cost);
}

void InitMap(int*  map, int From, int To)
{
    for(int k=0;k<MAP_SIZE_W*MAP_SIZE_H;k++)
        map[k]=0;


    int k=MAP_NB_OBSTACLE;
    while(k>=0)
    {
        int i=rand() % (MAP_SIZE_W*MAP_SIZE_H);
        if(map[i]==0)
        {
            map[i]=1;
            k--;
        }
    }

    map[From]=2;
    map[To]=3;
}

SparseDirectedGraph* InitGraph(int* map)
{
    SparseDirectedGraph *graph = new SparseDirectedGraph();

    for(int k=0;k<MAP_SIZE_W*MAP_SIZE_H;k++)
        graph->AddNode(new GraphNode());


    for(int k=0;k<MAP_SIZE_W*MAP_SIZE_H;k++)
    {
        int i0=-1,j0=-1;
        int i1=1,j1=1;

        if( k/MAP_SIZE_W == 0)
            i0=0;
        if( k/MAP_SIZE_W == MAP_SIZE_H-1)
            i1=0;
        if( k%MAP_SIZE_W == 0 || k%MAP_SIZE_W == MAP_SIZE_W-1)
            j0=0;
        if( k%MAP_SIZE_W == MAP_SIZE_W-1)
            j1=0;

        for(int i=i0; i<=i1; i++)
            for(int j=j0; j<=j1; j++)
            {
                int idx = k + i*MAP_SIZE_W + j;
                double cost = (i!=0 && j!=0) ? 1.41 : 1;
                if( idx >= 0 && idx < MAP_SIZE_W*MAP_SIZE_H && idx!=k  && k/MAP_SIZE_W==(k+j)/MAP_SIZE_W )
                    if(map[idx]!=1)
                        graph->AddEdge(new GraphEdge(k,idx,cost));
            }
    }

    return graph;
}

/**--------------------------------
// @Function: Main
// @Description: Game's loop
//---------------------------------**/
int main(void)
{
    //init random
    srand(time(NULL));

    //initialize Allegro
    allegro_init();

    //init keyboard
    install_keyboard();

    // init graphics
    set_color_depth(32);

    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1280, 720, 0, 0))
    {
        allegro_message(allegro_error);
        return 1;
    }

    //Map initialisation


    //Graph creation
    int map[MAP_SIZE_W*MAP_SIZE_H];
    int From=rand() % (MAP_SIZE_W*MAP_SIZE_H);
    int To=From;
    while(To==From)
        To = rand() %(MAP_SIZE_W*MAP_SIZE_H);

    InitMap(map,From,To);
    SparseDirectedGraph *graph=InitGraph(map);

    GraphSearch * g0 = new GraphSearch(graph, From, To,0);
    GraphSearch * g1 = new GraphSearch(graph, From, To,1);
    GraphSearch * g2 = new GraphSearch(graph, From, To,2);

    //Game loop
    int time = clock();
    int Todraw=-1;
    bool pressed=false;
    BITMAP *buffer= create_bitmap(SCREEN_W, SCREEN_H);
    while(!key[KEY_ESC])
    {
        clear(buffer);

        if(key[KEY_1_PAD])
            Todraw=0;
        if(key[KEY_2_PAD])
            Todraw=1;
        if(key[KEY_3_PAD])
            Todraw=2;

        if(key[KEY_ENTER_PAD])
            pressed=true;
        if(!key[KEY_ENTER_PAD] && pressed)
        {
            pressed=false;

            From=rand() % (MAP_SIZE_W*MAP_SIZE_H);
            To=From;
            while(To==From)
                To = rand() %(MAP_SIZE_W*MAP_SIZE_H);

            InitMap(map,From,To);

            delete(graph);
            graph = InitGraph(map);

            delete(g0,g1,g2);
            g0 = new GraphSearch(graph, From, To,0);
            g1 = new GraphSearch(graph, From, To,1);
            g2 = new GraphSearch(graph, From, To,2);
        }

        //Map rendering
        drawMap(map,buffer);


        if(Todraw==0)
        {
            drawGraph(g0, From, To, buffer);
        }
        else if(Todraw==1)
        {
            drawGraph(g1, From, To, buffer);
        }
        else if(Todraw==2)
        {
            drawGraph(g2, From, To, buffer);
        }

        //Buffer's blitting on screen
        acquire_screen();
            blit (buffer, screen, 0, 0, 0, 0,SCREEN_W-1,SCREEN_H-1);
        release_screen();

        //temporisation
        rest(5);
    }

    //end program
    allegro_exit();

    return 0;
}
END_OF_MAIN()
