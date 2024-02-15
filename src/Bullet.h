//
// Created by mateu on 15.02.2024.
//

#ifndef ENGINE_PROJECT_BULLET_H
#define ENGINE_PROJECT_BULLET_H

//
// Created by mateu on 12/02/2024.
//


class Bullet {
public:
    Bullet();

    Bullet(float start_x, float start_y, float start_z);

    ~Bullet();

    void activate();

    void live(float tt);

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
};

//-lglu32




#endif //ENGINE_PROJECT_BULLET_H
