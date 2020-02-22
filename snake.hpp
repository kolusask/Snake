#ifndef SNAKE_H
#define SNAKE_H
#include <vector>

enum Directions { UP, DOWN, LEFT, RIGHT };

class Snake {
   public:
    Snake(const unsigned len, const int h, const int w);
    ~Snake();
    void move(const Directions dir);
    void grow();

   private:
    struct Section {
        Section(const int x, const int y);
        void setXY(const int x, const int y);
        void move(const Directions dir);
        int X;
        int Y;
        Directions direct;
    };
    void fit();
    Directions direct;
    Directions back_dir;
    std::vector<Section> sections;
    unsigned length;
    unsigned tail;
    const int width;
    const int height;
    friend class Field;
};

#endif
