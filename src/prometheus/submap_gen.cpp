#include <world_gen.h>


void WorldGen::set_terrain_elevation(long x, long y)
{
    // set elevation to 0 and terrain to plains
    submap_generated_flag[x][y] = true;
    for( int i=0; i<world_size; i++)
    {
        for( int j=0; j<world_size; j++)
        {
            submap_data_matrix[x][y].elevation_matrix[i][j] = 0;
            submap_data_matrix[x][y].terrain_matrix[i][j] = plains;
        }
    }
}
