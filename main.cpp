#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <vector>
#include "entity.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "projectile.hpp"

#define enemieCount 20
#define FPS 60
#define ScreenWidth 1200
#define ScreenHeight 800

int main() {
    Player player(ScreenWidth / 2.0 - 32 / 2.0, ScreenHeight / 2.0 - 32 / 2.0, 32, 32);

    ALLEGRO_DISPLAY* display = NULL;
    ALLEGRO_EVENT_QUEUE* event_queue = NULL;
    ALLEGRO_TIMER* timer = NULL;
    bool exitgame = false;
    bool redraw = false;

    std::vector<Projectile*> projectiles;

    std::vector<Enemy*> enemies;
    for (size_t i = 0; i < enemieCount; i++) {
        enemies.push_back(new Enemy(i * (ScreenWidth / enemieCount) + 45, 40, 30, 30, 4));
    }

    // Initialize Aleggro and keyboard
    if (!al_init())
        return -1;
    if (!al_init_image_addon())
        return -1;
    if (!al_install_keyboard())
        return -1;

    // Create timer
    timer = al_create_timer(1.0 / FPS);
    if (!timer)
        return -1;

    // Create display
    display = al_create_display(ScreenWidth, ScreenHeight);
    if (!display) {
        al_destroy_timer(timer);
        return -1;
    }

    // Create bitmap of player
    if (!player.create()) {
        al_destroy_display(display);
        al_destroy_timer(timer);
        return -1;
    }
    for (size_t i = 0; i < enemieCount; i++) {
        if (!enemies[i]->create(255, 0, 0)) {
            al_destroy_display(display);
            al_destroy_timer(timer);
            return -1;
        }
    }

    // Draw to Display
    al_set_target_bitmap(al_get_backbuffer(display));

    // Create Queue
    event_queue = al_create_event_queue();
    if (!event_queue) {
        player.destroy();
        al_destroy_display(display);
        al_destroy_timer(timer);
        return -1;
    }

    // Events from Timer, Display and Keyboard to be stored in event_queue
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    // Set current bitmap (display) to all black
    al_clear_to_color(al_map_rgb(0, 0, 0));

    al_flip_display();
    al_start_timer(timer);
 
    // Main game loop
    while (!exitgame) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        // Timer events
        if (ev.type == ALLEGRO_EVENT_TIMER) {
            player.move(ScreenWidth, ScreenHeight);
            for (size_t i = 0; i < projectiles.size(); i++) {
                if (!projectiles[i]->move(ScreenWidth, ScreenHeight)) {
                    projectiles.erase(projectiles.begin() + i);
                    break;
                }
                // Hitbox detection
                for (size_t j = 0; j < enemies.size(); j++) {
                    if (projectiles[i]->x >= enemies[j]->x && projectiles[i]->x <= enemies[j]->x + enemies[j]->sizeW && projectiles[i]->y >= enemies[j]->y && projectiles[i]->y <= enemies[j]->y + enemies[j]->sizeH) {
                        if (enemies[j]->hit(projectiles[i]->damage)) {
                            enemies[j]->destroy();
                            delete enemies[j];
                            enemies.erase(enemies.begin() + j);
                        }
                        projectiles[i]->destroy();
                        delete projectiles[i];
                        projectiles.erase(projectiles.begin() + i);
                        break;
                    }
                }
            }
            redraw = true;
        }
         if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (ev.keyboard.keycode) {
                case ALLEGRO_KEY_W:
                    player.dir[UP] = true;
                    break;

                case ALLEGRO_KEY_S:
                    player.dir[DOWN] = true;
                    break;

                case ALLEGRO_KEY_A:
                    player.dir[LEFT] = true;
                    break;

                case ALLEGRO_KEY_D:
                    player.dir[RIGHT] = true;
                    break;

                case ALLEGRO_KEY_SPACE:
                    projectiles.push_back(new Projectile(player.x + player.sizeW/2, player.y, 2, 4, 2));
                    if (!projectiles[projectiles.size() - 1]->create(255, 0, 0)) {
                    }
                    break;
            }
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
            switch (ev.keyboard.keycode) {
                case ALLEGRO_KEY_W:
                    player.dir[UP] = false;
                    break;

                case ALLEGRO_KEY_S:
                    player.dir[DOWN] = false;
                    break;

                case ALLEGRO_KEY_A:
                    player.dir[LEFT] = false;
                    break;

                case ALLEGRO_KEY_D:
                    player.dir[RIGHT] = false;
                    break;
            }
        }

        // Draw function
        if (redraw && al_is_event_queue_empty(event_queue)) {
            redraw = false;
            al_set_target_bitmap(al_get_backbuffer(display));

            al_clear_to_color(al_map_rgb(0, 0, 0));
            player.draw();
            for (size_t i = 0; i < enemies.size(); i++) {
                enemies[i]->draw();
            }
            for (size_t i = 0; i < projectiles.size(); i++) {
                projectiles[i]->draw();
            }
            al_flip_display();
        }
    }

    // Destroy when game exits
    for (auto& a : enemies) {
        a->destroy();
        delete a;
    }

    for (auto& a : projectiles) {
        a->destroy();
        delete a;
    }
    
    player.destroy();
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    return 0;
}
