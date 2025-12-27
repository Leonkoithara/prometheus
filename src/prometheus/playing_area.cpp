#include <SDL_rect.h>
#include <SDL_render.h>
#include <playing_area.h>
#include <tile.h>


void PlayingArea::render()
{
    if (is_active())
    {
        SDL_RenderClear(renderer);
        
        for (auto it : game_objects)
        {
            SDL_Rect src = it.second.second->get_src_render_rect();
            SDL_Rect dest = it.second.second->get_dest_render_rect();

            auto surfaces = it.second.second->get_surfaces();
            for (auto itr : surfaces)
            {
                SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, itr.second.second);
                SDL_RenderCopy(renderer, texture, &src, &dest);
                SDL_DestroyTexture(texture);
            }

            Tile *t = dynamic_cast<Tile*>(it.second.second);
            if (t != NULL)
			{
                t->update();
                if (t->is_highlighted())
                {
                    vec3D pos = t->get_position();
                    int x1, x2, x3, y1, y2, y3;
                    x1 = pos.x + 15;
                    x2 = pos.x - (ONE_BY_ROOT_TWO * 30) + 15;
                    x3 = pos.x + (ONE_BY_ROOT_TWO * 30) + 15;
                    y1 = pos.y;
                    y2 = pos.y + (ONE_BY_ROOT_TWO * 30);
                    y3 = pos.y + (ONE_BY_ROOT_TWO * 60);
                    SDL_Point points[5] = {
                        {x2, y2},
                        {x1, y1},
                        {x3, y2},
                        {x1, y3},
                        {x2, y2}
                    };
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                    SDL_RenderDrawLines(renderer, points, 5);
                    SDL_SetRenderDrawColor(renderer, 0, 125, 0, 255);
                }
            }
        }

        SDL_RenderFlush(renderer);
        SDL_RenderPresent(renderer);
    }
}
