#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct vec_t {
    double x, y;
} vec_t;

vec_t vec_add(vec_t v, vec_t w) {
    vec_t result = {v.x + w.x, v.y + w.y};
    return result;
}

vec_t vec_scale(vec_t v, double a) {
    vec_t result = {v.x * a, v.y * a};
    return result;
}

typedef struct body_t {
    vec_t position;
    vec_t velocity;
    vec_t force;
    double mass;
} body_t;

void add_force(body_t *body, vec_t force) {
    body->force.x += force.x;
    body->force.y += force.y;
}

vec_t get_force(body_t *body1, body_t *body2) {
    double dx = body2->position.x - body1->position.x;
    double dy = body2->position.y - body1->position.y;
    double distance2 = fmax(dx * dx + dy * dy, 1.0);
    double force = 9.8 * body1->mass * body2->mass / distance2;
    double angle = atan2(dy, dx);
    vec_t result = {cos(angle) * force, sin(angle) * force};
    return result;
}

void update_forces(body_t *bodies, int n) {
    for (int i = 0; i < n; ++i) {
        bodies[i].force.x = 0;
        bodies[i].force.y = 0;
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;
            add_force(&bodies[i], get_force(&bodies[i], &bodies[j]));
        }
    }
}

void update_positions(body_t *bodies, int n, int dt) {
    for (int i = 0; i < n; ++i) {
        vec_t new_velocity = vec_scale(bodies[i].force, dt / bodies[i].mass);
        vec_t offset = vec_scale(vec_add(bodies[i].velocity, new_velocity), dt / 2.0);
        bodies[i].position = vec_add(bodies[i].position, offset);
        bodies[i].velocity = new_velocity;
    }
}

void simulate(body_t *bodies, int n, int steps, int dt) {
    for (int i = 0; i < steps; ++i) {
        update_forces(bodies, n);
        update_positions(bodies, n, dt);
    }
}

body_t rand_body() {
    body_t body;
    body.position.x = ((double)rand() / RAND_MAX) * 100;
    body.position.y = ((double)rand() / RAND_MAX) * 100;
    body.velocity.x = 0;
    body.velocity.y = 0;
    body.force.x = 0;
    body.force.y = 0;
    body.mass = 10 + ((double)rand() / RAND_MAX) * 90;
    return body;
}

void display(body_t *bodies, int n) {
    for (int i = 0; i < n; ++i) {
        printf("#%d { position=[%f, %f], velocity=[%f, %f], force=[%f, %f], mass=%f }\n", i, bodies[i].position.x,
               bodies[i].position.y, bodies[i].velocity.x, bodies[i].velocity.y, bodies[i].force.x, bodies[i].force.y,
               bodies[i].mass);
    }
}

int main(int argc, char const *argv[]) {
    body_t bodies[] = {rand_body(), rand_body()};

    printf("Start:\n");
    display(bodies, 2);

    simulate(bodies, 2, 20, 1);

    printf("End:\n");
    display(bodies, 2);

    return 0; 
}
