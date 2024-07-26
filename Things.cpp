

#include "Things.h"

static int random(int min, int max)  // range : [min, max]
{
    static bool first = true;
    if (first) {
        srand(time(NULL));  // seeding for the first time only!
        first = false;
    }
    return min + rand() % ((max + 1) - min);
}

static bool collisionCir2Cir(struct Point o1, int r1, struct Point o2, int r2) {
    float distX = o1.x - o2.x;
    float distY = o1.y - o2.y;
    float distance = sqrt((distX * distX) + (distY * distY));

    return distance <= r1 + r2;
}

Things::Things(Render& render) : render(render) {
    int heigth = render.getHeigth();
    
    count = 0;

    min = heigth / 2 - 50 - THING_RADIUS;
    max = heigth / 2 + 50 + THING_RADIUS;
    
    array.push_back({BAD, {-THING_RADIUS, random(min, max)}});
};

enum ThingType Things::act(float dt, const Pinwheel& pw) {
    enum ThingType res = NOTHING;

    static float refresh_time = 0.;

    refresh_time += dt;

    if (refresh_time >= REFRESH_TIME) {

        refresh_time = 0.;

        mutex.lock();

        for (auto it = array.begin(); it != array.end(); it++) {
            if (++it->position.x > render.getWidth() + THING_RADIUS)
                it = array.erase(it);
        }

        if (array.size() == 1 && array[0].position.x > 3 * render.getWidth() / 4) {
            count = (count + 1) % COUNT_MAX;
            array.push_back({count == GOOD? GOOD : BAD, {-THING_RADIUS, random(min, max)}});
        }

        for (auto it = array.begin(); it != array.end(); it++) {
            if (it->type == GOOD) {
                if (collisionCir2Cir(pw.pt1, THING_RADIUS, it->position, THING_RADIUS)
                 || collisionCir2Cir(pw.pt2, THING_RADIUS, it->position, THING_RADIUS)) {
                    it = array.erase(it);
                    count = (count + 1) % COUNT_MAX;
                    array.push_back({count == GOOD ? GOOD : BAD, {-THING_RADIUS, random(min, max)}});
                    res = GOOD;
                    break;
                }
            } else if (it->type == BAD) {
                if (collisionCir2Cir(pw.pt1, THING_RADIUS, it->position, THING_RADIUS) ||
                    collisionCir2Cir(pw.pt2, THING_RADIUS, it->position, THING_RADIUS)) {
                    // it = array.erase(it);
                    count = (count + 1) % COUNT_MAX;
                    array.push_back({count == GOOD ? GOOD : BAD, {-THING_RADIUS, random(min, max)}});
                    res = BAD;
                    break;
                }
            }
        }

        mutex.unlock();
    }

    return res;
}

void Things::draw() {
    
    mutex.lock();

    for (auto it = array.cbegin(); it != array.cend(); it++) {
        if (it->type == BAD) {
            int x = it->position.x;
            int y = it->position.y;
            render.fillRectangle({x - THING_RADIUS, y - THING_RADIUS, 2*THING_RADIUS, 2*THING_RADIUS}, BAD_COLOR);
        } else {
            render.fillCircle(THING_RADIUS, it->position, GOOD_COLOR);
        }
            
    }   

    mutex.unlock();
}

