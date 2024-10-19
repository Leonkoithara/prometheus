#include <iostream>

#include <button.h>
#include <scene.h>
#include <world_gen.h>


terrain get_terrain(int *probablity_row)
{
    int rand_num = rand()%101;
    int sum = 0;
    for (int i=plains; i<TERRAIN_TYPES; i++)
	{
        if (rand_num < sum+*(probablity_row+i))
            return static_cast<terrain>(i);
        sum += *(probablity_row+i);
    }
    return plains;
}

WorldGen::WorldGen(int size, std::string nm)
{
    name = nm;
    world_size = size;
    seed = 0;
    terrain_matrix = new terrain*[world_size];
    for(int i=0; i<world_size; i++)
        terrain_matrix[i] = new terrain[world_size];
    submap_generated_flag = new bool*[world_size];
    for(int i=0; i<world_size; i++)
    {
        submap_generated_flag[i] = new bool[world_size];
        for(int j=0; j<world_size; j++)
            submap_generated_flag[i][j] = false;
    }
    submap_data_matrix = new submap_data*[world_size];
    for(int i=0; i<world_size; i++)
    {
        submap_data_matrix[i] = new submap_data[world_size];
        for(int j=0; j<world_size; j++)
            submap_data_matrix[i][j] = submap_data(world_size);
    }

    // currently always 0, todo add optional seed input
    if (seed == 0)
        srand(time(NULL));
    else
        srand(seed);
    int p = 100/TERRAIN_TYPES, rem = 100%TERRAIN_TYPES;
    probablity_matrix = new int**[size];
    for(int i=0; i<size; i++)
    {
        probablity_matrix[i] = new int*[size];
        for(int j=0; j<size; j++)
        {
            probablity_matrix[i][j] = new int[TERRAIN_TYPES];
            for(int k=0; k<TERRAIN_TYPES; k++)
                probablity_matrix[i][j][k] = p;
            probablity_matrix[i][j][rand()%TERRAIN_TYPES] += rem;
        }
    }
}

void WorldGen::modify_probablities(int x, int y, int p_delta, terrain t)
{
    int changed = 0;
    int temp = probablity_matrix[x][y][t] + p_delta;

    if (temp < 0)
    {
        p_delta = -1 * probablity_matrix[x][y][t];
        probablity_matrix[x][y][t] = 0;
    }
    else if (temp > 100)
    {
        p_delta = 100 - probablity_matrix[x][y][t];
        probablity_matrix[x][y][t] = 100;
    }
    else
        probablity_matrix[x][y][t] += p_delta;

    // what remains to be split amoung the rest
    int remains = p_delta;

    while (std::abs(changed) < std::abs(p_delta))
    {
        int change_each = remains/(TERRAIN_TYPES-1);
        // if what remains is less than terrain_types-1 then they just need to be increase/decreased by 1
        if (change_each == 0)
            change_each = remains/std::abs(remains);
        int old_changed = changed;

        for (int i=plains; i<TERRAIN_TYPES; i++)
        {
            int change = 0;
            if (i != t && std::abs(changed) < std::abs(p_delta))
            {
                temp = probablity_matrix[x][y][i] - change_each;
                if (temp < 0)
				{
                    change = probablity_matrix[x][y][i];
                    probablity_matrix[x][y][i] = 0;
                }
                else if (temp > 100)
                {
                    change = probablity_matrix[x][y][i] - 100;
                    probablity_matrix[x][y][i] = 100;
                }
                else
                {
                    change = change_each;
                    probablity_matrix[x][y][i] -= change_each;
                }
            }
            changed -= change;
            remains -= change;
        }

        if (changed == old_changed)
		{
            std::cout << probablity_matrix[x][y][0] << " " << probablity_matrix[x][y][1] << " " << probablity_matrix[x][y][2] << " " << probablity_matrix[x][y][3] << " " << probablity_matrix[x][y][4] << " " << probablity_matrix[x][y][5] << " " << std::endl;
            std::cout << "Cannot change " << probablity_matrix[x][y][t] << " by " << p_delta << std::endl;
            break;
        }
    }
}

void WorldGen::set_terrain_matrix()
{
    for (int i=0; i<world_size; i++)
    {
        for (int j=0; j<world_size; j++)
        {
            terrain t = get_terrain(probablity_matrix[i][j]);
            terrain_matrix[i][j] = t;
            int rad = 3;
            switch (t)
			{
                case plains:
                case forests:
                    if (i+1 < world_size)
                        modify_probablities(i+1, j, (TERRAIN_TYPES-1)*5.5, t);
                    if (j+1 < world_size)
                        modify_probablities(i, j+1, (TERRAIN_TYPES-1)*5.5, t);
                    if (i+1 < world_size && j+1 < world_size)
                        modify_probablities(i+1, j+1, (TERRAIN_TYPES-1)*5.5, t);
                    if (i-1 > 0 && j+1 < world_size)
                        modify_probablities(i-1, j+1, (TERRAIN_TYPES-1)*5.5, t);
                    break;
                case mountains:
                    if (i+1 < world_size)
                        modify_probablities(i+1, j, (TERRAIN_TYPES-1)*7, t);
                    if (j+1 < world_size)
                        modify_probablities(i, j+1, (TERRAIN_TYPES-1)*7, t);
                    break;
                case water:
                    if (i+1 < world_size)
                        modify_probablities(i+1, j, (TERRAIN_TYPES-1)*8, t);
                    if (j+1 < world_size)
                        modify_probablities(i, j+1, (TERRAIN_TYPES-1)*8, t);
                    break;
                case human_civ:
                case civ_ruins:
                    for (int xr=-1*rad; xr<=rad; xr++)
                    {
                        for (int yr=-1*rad; yr<=rad; yr++)
                        {
                            if (i+xr < world_size && j+yr < world_size && i+xr >= 0 && j+yr >=0 && xr != 0 && yr != 0)
                            {
                                modify_probablities(i+xr, j+yr, -15, human_civ);
                                modify_probablities(i+xr, j+yr, -15, civ_ruins);
                            }
                        }
                    }
                    break;
                default:
                    std::cout << "Unknown terrain" << std::endl;
            }
        }
    }
}

void WorldGen::populate_objects(Scene *prometheus)
{
    int terrain_count[6] = {0, 0, 0, 0, 0};                                                   // Count in map for each terrain
    std::string texturefile_map[6] = {
        "plains", "hill", "tree", "water", "human_civ", "civ_ruins"
    };
    const char* terrain_name[6] = {
        "plains", "hills", "trees", "water", "human_civ", "civ_ruins"
    };
    for (int i=0; i<world_size; i++)
	{
        for (int j=0; j<world_size; j++)
        {
            char go_name[15];
            terrain_count[terrain_matrix[i][j]]++;
            snprintf(go_name, 15, "%s_%d", terrain_name[terrain_matrix[i][j]], terrain_count[terrain_matrix[i][j]]);
            Button *new_symbol = new Button(std::string(go_name));
            new_symbol->add_tag("terrain", texturefile_map[terrain_matrix[i][j]].c_str());
            new_symbol->add_tag("xpos", i);
            new_symbol->add_tag("ypos", j);
            new_symbol->set_onclickevent(create_submap);
            new_symbol->set_position({(float)25*i, (float)25*j});
            new_symbol->add_texturefile("res/textures/" + texturefile_map[terrain_matrix[i][j]] + ".png", 0);
            prometheus->add_game_object(new_symbol);
        }
    }
}

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

void create_submap(int x, GameObject *icon)
{
    std::cout << "Clicked: " << icon->get_tag("terrain")->strval << ", at: " << icon->get_tag("xpos")->longval << "," << icon->get_tag("ypos")->longval << std::endl;
    world->set_terrain_elevation(icon->get_tag("xpos")->longval, icon->get_tag("ypos")->longval);
}
