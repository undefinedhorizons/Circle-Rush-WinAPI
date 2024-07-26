#include "Pinwheel.h"

Pinwheel::Pinwheel(Render& render) : render(render){
    center = render.getCenter();

    pt1 = {center.x - (int)(CIRCLE_DISTANCE * cosf(angle)), center.y + (int)(CIRCLE_DISTANCE * sinf(angle))};
    pt2 = {center.x + (int)(CIRCLE_DISTANCE * cosf(angle)), center.y - (int)(CIRCLE_DISTANCE * sinf(angle))};
};

void Pinwheel::act(float dt) {
    static float refresh_time = 0.;
    static float refresh_time_mark = 0.;

    refresh_time += dt;

    if (refresh_time >= REFRESH_TIME) {

        refresh_time = 0.;

        angle += da;

        if (angle > M_PI)
            angle = -M_PI;
        else if (angle < -M_PI)
            angle = M_PI;

        pt1 = {center.x - (int)(CIRCLE_DISTANCE * cosf(angle)), center.y + (int)(CIRCLE_DISTANCE * sinf(angle))};
        pt2 = {center.x + (int)(CIRCLE_DISTANCE * cosf(angle)), center.y - (int)(CIRCLE_DISTANCE * sinf(angle))};
    }

    refresh_time_mark += dt;

    if (refresh_time_mark >= MARK_TIME) {

        refresh_time_mark = 0.;

        mutex.lock();

        for (auto it = marks.begin(); it != marks.end(); it++) {
            if (--it->radius <= 0)
                it = marks.erase(it);
        }

        marks.push_back({MARK_RADIUS, pt1});
        marks.push_back({MARK_RADIUS, pt2});

        mutex.unlock();
    }

    if (is_key_pressed(VK_LEFT))
        da = -ANGLE_DELTA;

    if (is_key_pressed(VK_RIGHT))
        da = ANGLE_DELTA;
}

void Pinwheel::draw() {
    render.fillCircle(CIRCLE_RADIUS, pt1, CIRCLE_COLOR);
    render.fillCircle(CIRCLE_RADIUS, pt2, CIRCLE_COLOR);

    mutex.lock();

    for (auto it = marks.cbegin(); it != marks.cend(); it++) {
        render.fillCircle(it->radius, it->point, CIRCLE_COLOR);
    }

    mutex.unlock();
}