#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "raylib.h"


#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

typedef struct 
{
    Vector2 velocity;
    Vector2 position;
    float mass;
    float radius;
    float invMass;
    float bounciness;
}Body;


int collision(Body A, Body B, float *dx, float *dy)
{
     *dx = A.position.x - B.position.x;
     *dy = A.position.y - B.position.y;

    float distanceSquared = (*dx) * (*dx) + (*dy) * (*dy);
    float radiusSumSquared = (A.radius + B.radius) * (A.radius + B.radius);

    return(distanceSquared <= radiusSumSquared);
}

void resolveCollision(Body *A, Body *B, float dx, float dy)
{
    float distance = sqrt(dx * dx + dy * dy);

    float overlap = (A->radius + B->radius) - distance;

    Vector2 normal;

    if(distance == 0.0f)
    {
        normal.x = 1.0f;
        normal.y = 0.0f;
        distance = 0.0001f;
    }
    else
    {
        normal.x = dx/distance;
        normal.y = dy/distance;
    }
    
    if(A->mass != 0.0f)
        A->invMass = 1.0f / A->mass;
    else A->invMass = 0.0f;


    if(B->mass != 0.0f)
        B->invMass = 1.0f / B->mass;
    else B->invMass = 0.0f;
    
    float invMTotal = A->invMass + B->invMass;

    if(invMTotal == 0)
    return;

    
    float RatioA = A->invMass / invMTotal;
    float RatioB = B->invMass / invMTotal;


    A->position.x += normal.x * (RatioA * overlap);
    A->position.y += normal.y * (RatioA * overlap);

    B->position.x -= normal.x * (RatioB * overlap);
    B->position.y -= normal.y * (RatioB * overlap);

    float relativeVelocityX = A->velocity.x - B->velocity.x;
    float relativeVelocityY = A->velocity.y - B->velocity.y;

    float normalVelocity = relativeVelocityX * normal.x + relativeVelocityY * normal.y;

    if(normalVelocity < 0)
    {
        float e = fmin(A->bounciness, B->bounciness);
        float j = (-(1 + e) * normalVelocity) / invMTotal;

        Vector2 impulse;
        impulse.x = j * normal.x;
        impulse.y = j * normal.y;

        A->velocity.x += (impulse.x * A->invMass);
        A->velocity.y += (impulse.y * A->invMass);

        B->velocity.x -= (impulse.x * B->invMass);
        B->velocity.y -= (impulse.y * B->invMass);
    }
    else return;
}

void resolveWalls(Body *A)
{
    if(A->position.x - A->radius < 0)
    {
        A->position.x = A->radius;
        A->velocity.x *= -A->bounciness;
    }

    if(A->position.x + A->radius > SCREEN_WIDTH)
    {
        A->position.x = SCREEN_WIDTH - A->radius;
        A->velocity.x *= -A->bounciness;
    }

    if(A->position.y - A->radius < 0)
    {
        A->position.y = A->radius;
        A->velocity.y *= -A->bounciness;
    }

    if(A->position.y + A->radius > SCREEN_HEIGHT)
    {
        A->position.y = SCREEN_HEIGHT - A->radius;
        A->velocity.y *= -A->bounciness;
    }
}

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Collision Simulator");
    SetTargetFPS(60);

    Body A;
    A.position.x = 150.0f;
    A.position.y = 300.0f;

    A.velocity.x = 250.0f;
    A.velocity.y = 0.0f;

    A.radius = 25.0f;
    A.mass = 2.0f;
    A.bounciness = 0.99f;


    Body B;
    B.position.x = 650.0f;
    B.position.y = 300.0f;

    B.velocity.x = -250.0f;
    B.velocity.y = 0.0f;

    B.radius = 25.0f;
    B.mass = 2.0f;
    B.bounciness = 0.9f;


    while((!WindowShouldClose()))
    {
        float dt = GetFrameTime();

        A.position.x += A.velocity.x * dt;
        A.position.y += A.velocity.y * dt;

        B.position.x += B.velocity.x * dt;
        B.position.y += B.velocity.y * dt;

        resolveWalls(&A);
        resolveWalls(&B);

        float dx, dy;

        if(collision(A, B, &dx, &dy))
        {
            resolveCollision(&A, &B, dx, dy);
        }
        BeginDrawing();
        ClearBackground(BLACK);

        DrawCircle((int)A.position.x, (int)A.position.y, A.radius, RED);
        DrawCircle((int)B.position.x, (int)B.position.y, B.radius, BLUE);
        EndDrawing();
    }


    CloseWindow();
    return 0;
}