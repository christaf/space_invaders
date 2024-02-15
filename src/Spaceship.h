//
// Created by mateu on 15.02.2024.
//

#ifndef ENGINE_PROJECT_SPACESHIP_H
#define ENGINE_PROJECT_SPACESHIP_H


class Spaceship {
public:
    Spaceship();

    Spaceship(float start_x, float start_y, float start_z);

    ~Spaceship();

    void activate();

    void live(float tt);

    void draw() const;

    void Render() const;

    bool active;
    float life{}, fade{};
    float size;
    float r, g, b;

    float posX{};
    float posY{};
    float posZ{};

    float movX{};
    float movY{};
    float movZ{};

    float gravX{};
    float gravY{};
    float gravZ{};

    void setPos(float x, float y, float z);

    void move(float x, float y, float z);
};


#endif //ENGINE_PROJECT_SPACESHIP_H
