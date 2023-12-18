#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
const int w = 1, wh = 3, size = 1000;
float shift_x = 0, shift_y = 0;
int size_p = 50;
bool Dark = false;
sf::RenderWindow wnd(sf::VideoMode(size + w * 2 + 1, size + w * 2 + 1), "SFML");

// рисование системы координат
void coordinate_system() {
    for (int i = w; i >= -w; --i) {
        sf::Vertex line[] = {sf::Vertex(sf::Vector2f(0, size / 2 + shift_x + i)),
                             sf::Vertex(sf::Vector2f(size + w * 2 + 1, size / 2 + shift_x + i))
        };
        if (!Dark) {
            line[0].color = sf::Color::Black;
            line[1].color = sf::Color::Black;
        } else {
            line[0].color = sf::Color::White;
            line[1].color = sf::Color::White;
        }
        wnd.draw(line, 2, sf::Lines);
    }
    for (int i = w; i >= -w; --i) {
        sf::Vertex line[] = {sf::Vertex(sf::Vector2f(size / 2 + shift_y + i, 0)),
                             sf::Vertex(sf::Vector2f(size / 2 + shift_y + i, size + w * 2 + 1))
        };
        if (!Dark) {
            line[0].color = sf::Color::Black;
            line[1].color = sf::Color::Black;
        } else {
            line[0].color = sf::Color::White;
            line[1].color = sf::Color::White;
        }
        wnd.draw(line, 2, sf::Lines);
    }
    sf::ConvexShape convex;
    convex.setPointCount(3);
    convex.setPoint(0, sf::Vector2f(size / 2 + shift_y, -1));
    convex.setPoint(1, sf::Vector2f(size / 2 - 10 + shift_y, 10));
    convex.setPoint(2, sf::Vector2f(size / 2 + 10 + shift_y, 10));
    if (!Dark) {
        convex.setFillColor(sf::Color::Black);
    } else {
        convex.setFillColor(sf::Color::White);
    }
    wnd.draw(convex);

    convex.setPointCount(3);
    convex.setPoint(0, sf::Vector2f(size + w * 2 + 1, size / 2 + shift_x));
    convex.setPoint(1, sf::Vector2f(size + w * 2 + 1 - 10, size / 2 - 10 + shift_x));
    convex.setPoint(2, sf::Vector2f(size + w * 2 + 1 -10, size / 2 + 10 + shift_x));
    if (!Dark) {
        convex.setFillColor(sf::Color::Black);
    } else {
        convex.setFillColor(sf::Color::White);
    }
    wnd.draw(convex);
}

void single_sigment() {
    for (int j = 1; j <= size / size_p; ++j) {
        sf::Vertex line[2];
        for (int i = 0; i < size + w * 2 + 1; ++i) {
            line[0] = sf::Vertex(sf::Vector2f((size / 2 + shift_y) + size_p * j, i));
            line[1] = sf::Vertex(sf::Vector2f((size / 2 + shift_y) + size_p * j, i + 5));
            if (!Dark) {
                line[0].color = sf::Color::Black;
                line[1].color = sf::Color::Black;
            } else {
                line[0].color = sf::Color::White;
                line[1].color = sf::Color::White;
            }
            wnd.draw(line, 2, sf::Lines);
            line[0] = sf::Vertex(sf::Vector2f((size / 2 + shift_y) - size_p * j, i));
            line[1] = sf::Vertex(sf::Vector2f((size / 2 + shift_y) - size_p * j, i + 5));
            if (!Dark) {
                line[0].color = sf::Color::Black;
                line[1].color = sf::Color::Black;
            } else {
                line[0].color = sf::Color::White;
                line[1].color = sf::Color::White;
            }
            wnd.draw(line, 2, sf::Lines);
            line[0] = sf::Vertex(sf::Vector2f(i, (size / 2 + shift_x) + size_p * j));
            line[1] = sf::Vertex(sf::Vector2f(i + 5, (size / 2 + shift_x) + size_p * j));
            if (!Dark) {
                line[0].color = sf::Color::Black;
                line[1].color = sf::Color::Black;
            } else {
                line[0].color = sf::Color::White;
                line[1].color = sf::Color::White;
            }
            wnd.draw(line, 2, sf::Lines);
            line[0] = sf::Vertex(sf::Vector2f(i, (size / 2 + shift_x) - size_p * j));
            line[1] = sf::Vertex(sf::Vector2f(i + 5, (size / 2 + shift_x) - size_p * j));
            if (!Dark) {
                line[0].color = sf::Color::Black;
                line[1].color = sf::Color::Black;
            } else {
                line[0].color = sf::Color::White;
                line[1].color = sf::Color::White;
            }
            wnd.draw(line, 2, sf::Lines);
            i += 6;
        }
    }
}

// перенос начала координат в точку 0, 0
double get_x(double x) {
    return x - (double(size) / 2 + double(shift_y));
}

double get_y(double y) {
    return (double(size) / 2 + double(shift_x)) - y;
}

double get_x_ind(double x) {
    return x + double(size) / 2 + double(shift_y);
}

double get_y_ind(double y) {
    return double(size) / 2.0 + double(shift_x) - y;
}

// закрашивание точки
void paint(double x, double y) {
    if ((x <= (size / 2) + shift_x - w || x >= (size / 2) + shift_x + w)
        && (y <= (size / 2) + shift_y - w || y >= (size / 2) + shift_y + w)) {
        sf::RectangleShape cube;
        if (!Dark) {
            cube.setFillColor(sf::Color::Blue);
        } else {
            cube.setFillColor(sf::Color::White);
        }
        cube.setSize(sf::Vector2f(wh, wh));
        cube.setPosition(y, x);
        wnd.draw(cube);
    }
}

// парабола по y (объект 2)
double parabola_y(int x) {
    x = get_x(x);
    double y = -12.0 / (12.5 * size_p) * (x * x) + 24.0 / 5.0 * x - 5 * size_p;
    return get_y_ind(y);
}

// парабола по x (объект 4)
double parabola_x(double y) {
    y = get_y(y);
    double x = -12.0 / (12.5 * size_p) * (y * y) + 24.0 / 5.0 * y - 4 * size_p;
    return get_x_ind(x);
}

double check_circle(double x) {
    x = get_x(x);
    double y = 2.25 * size_p * size_p - (x - 2 * size_p) * (x - 2 * size_p);
    return sqrt(y) - 2.5 * size_p;
}

double check_circle2(double x) {
    x = get_x(x);
    double y = 2.25 * size_p * size_p - (x - 2 * size_p) * (x - 2 * size_p);
    return -sqrt(y) - 2.5 * size_p;
}

double line1(double x) {
    x = get_x(x);
    double y = -1.0 / 3.0 * x - size_p / 3.0;
    return get_y_ind(y);
}

double line2(double x) {
    x = get_x(x);
    double y = 5.0 / 3.0 * x - (14 * size_p) / 3.0;
    return get_y_ind(y);
}

std::pair<double, double> rectangle_x(double x) {
    x = get_x(x);
    if (x >= -1.5 * size_p && x <= 2.5 * size_p) {
        return { 4.5 * size_p, 2.5 * size_p };
    }
}

std::pair<double, double> rectangle_y(double y) {
    y = get_y(y);
    if (y <= 4.5 * size_p && y >= 2.5 * size_p) {
        return { -1.5 * size_p, 2.5 * size_p };
    }
}

double rhombus_down(double x) {
    x = get_x(x);
    double y = 1.0 / 2.0 * x + (7.5 * size_p) / 2.0;
    if (x >= -3.5 * size_p && x <= -0.5 * size_p && y >= 2 * size_p && y <= 3.5 * size_p) {
        return y;
    }
    y = -1.0 / 2.0 * x + (0.5 * size_p) / 2.0;
    if (x >= -6.5 * size_p && x <= -3.5 * size_p && y >= 2 * size_p && y <= 3.5 * size_p) {
        return y;
    }
}

double rhombus_up(double x) {
    x = get_x(x);
    double y = 1.0 / 2.0 * x + (13.5 * size_p) / 2.0;
    if (x <= -3.5 * size_p && x >= -6.5 * size_p  && y <= 5 * size_p && y >= 3.5 * size_p) {
        return y;
    }
    y = -1.0 / 2.0 * x + (6.5 * size_p) / 2.0;
    if (x >= -3.5 * size_p && x <= -0.5 * size_p && y <= 5 * size_p && y >= 3.5 * size_p) {
        return y;
    }
}

void get() {
    for (double x = 0; x < size + w * 2 + 1; x += 1) {
        double y = line1(x);
        paint(y, x);
        y = line2(x);
        paint(y, x);

        double y1 = check_circle(x), y2 = check_circle(x + 1);
        y1 = get_y(y1);
        y2 = get_y(y2);
        for (double i = 0; i <= fabs(y1 - y2); i += 1) {
            paint(std::min(y1, y2) + i, x);
        }

        y1 = check_circle2(x), y2 = check_circle2(x + 1);
        y1 = get_y(y1);
        y2 = get_y(y2);
        for (double i = 0; i <= fabs(y1 - y2); i += 1) {
            paint(std::min(y1, y2) + i, x);
        }

        y = parabola_y(x), y2 = parabola_y(x + 1);
        for (double i = 0; i <= fabs(y - y2); i += 1) {
            paint(y + i, x);
        }
        std::pair<double, double> y3 = rectangle_x(x);
        paint(get_y_ind(y3.first), x);
        paint(get_y_ind(y3.second), x);

        y = rhombus_up(x);
        paint(get_y_ind(y), x);

        y = rhombus_down(x);
        paint(get_y_ind(y), x);
    }
    for (double y = 0; y < size + w * 2 + 1; y += 1) {
        double x = parabola_x(y), x2 = parabola_x(y + 1);
        for (double i = 0; i <= fabs(x - x2); i += 0.1) {
            paint(y, x + i);
        }

        std::pair<double, double> x1 = rectangle_y(y);
        paint(y, get_x_ind(x1.first));
        paint(y, get_x_ind(x1.second));
    }
}

// проверка принадлежнисти к области (по 2 функции на фигуру iside outside)
bool line1_down(double x, double y) {
    x = get_x(x);
    y = get_y(y);
    if (y <= -1.0 / 3.0 * x - size_p / 3.0) {
        return true;
    }
    return false;
}

bool line2_down(double x, double y) {
    x = get_x(x);
    y = get_y(y);
    if (y <= 5.0 / 3.0 * x - (14 * size_p) / 3.0) {
        return true;
    }
    return false;
}

bool parabola_x_in(double x, double y) {
    x = get_x(x);
    y = get_y(y);
    if (x <= -12.0 / (12.5 * size_p) * (y * y) + 24.0 / 5.0 * y - 4 * size_p) {
        return true;
    }
    return false;
}

bool parabola_y_in(double x, double y) {
    x = get_x(x);
    y = get_y(y);
    if (y <= -12.0 / (12.5 * size_p) * (x * x) + 24.0 / 5.0 * x - 5 * size_p) {
        return true;
    }
    return false;
}

bool circle_in(double x, double y) {
    x = get_x(x);
    y = get_y(y);
    if ((x - 2 * size_p) * (x - 2 * size_p) + (y + 2.5 * size_p) * (y + 2.5 * size_p) <= 2.25 * size_p * size_p) {
        return true;
    }
    return false;
}

bool rectangle_in(double x, double y) {
    x = get_x(x);
    y = get_y(y);
    if (x >= -1.5 * size_p && x <= 2.5 * size_p && y <= 4.5 * size_p && y >= 2.5 * size_p) {
        return true;
    }
    return false;
}

bool rhombus_in(double x, double y) {
    x = get_x(x);
    y = get_y(y);
    if (y <= 1.0 / 2.0 * x + (13.5 * size_p) / 2.0 &&
        y <= -1.0 / 2.0 * x + (6.5 * size_p) / 2.0 &&
        y >= 1.0 / 2.0 * x + (7.5 * size_p) / 2.0 &&
        y >= -1.0 / 2.0 * x + (0.5 * size_p) / 2.0) {
        return true;
    }
    return false;
}

bool axis_x_up(double x, double y) {
    x = get_x(x);
    y = get_y(y);
    if (y >= 0) {
        return true;
    }
    return false;
}

bool axis_y_right(double x, double y) {
    x = get_x(x);
    y = get_y(y);
    if (x >= 0) {
        return true;
    }
    return false;
}

void filling(std::vector<std::vector<bool>>& fills) {
    for (int x = 0; x < size + w * 2 + 1; ++x) {
        for (int y = 0; y < size + w * 2 + 1; ++y) {
            int x1 = x, y1 = y;
            if (x >= size / 2 + shift_y) {
                x1 -= 1;
            }
            if (y1 >= size / 2 + shift_x) {
                y1 -= 1;
            }
            if ((x + y) % 30 == 0 || abs(x - y) % 30 == 0) {
                // биг рофлс
                bool (*f[9])(double, double) = { line1_down, line2_down, parabola_x_in, parabola_y_in, circle_in, rectangle_in, rhombus_in, axis_x_up, axis_y_right };
                bool flag = false;
                for (int i = 0; i < fills.size(); ++i) {
                    flag = true;
                    for (int j = 0; j < 9; ++j) {
                        if (f[j](y1, x1) != fills[i][j]) {
                            flag = false;
                            break;
                        }
                    }
                    if (flag) {
                        break;
                    }
                }
                if (flag) {
                    sf::RectangleShape cube;
                    cube.setFillColor(sf::Color::Cyan);
                    cube.setSize(sf::Vector2f(wh - 1, wh - 1));
                    cube.setPosition(y, x);
                    wnd.draw(cube);
                }
            }
        }
    }
}

bool check(int x1, int y1, std::vector<std::vector<bool>>& fills) {
    bool (*f[9])(double, double) = { line1_down, line2_down, parabola_x_in, parabola_y_in, circle_in, rectangle_in, rhombus_in, axis_x_up, axis_y_right };
    bool flag = false;
    for (int i = 0; i < fills.size(); ++i) {
        flag = true;
        for (int j = 0; j < 9; ++j) {
            if (f[j](y1, x1) != fills[i][j]) {
                flag = false;
                break;
            }
        }
        if (flag) {
            break;
        }
    }
    return flag;
}

void update(std::vector<std::vector<bool>>& fills) {
    if (!Dark) {
        wnd.clear(sf::Color::White);
    } else {
        wnd.clear(sf::Color::Black);
    }
    filling(fills);
    get();
    coordinate_system();
    single_sigment();
    wnd.display();
}

int main() {
    std::vector<std::vector<bool>> fills;
    update(fills);

    sf::Clock clock;

    while (wnd.isOpen()) {
        sf::Vector2i position = sf::Mouse::getPosition(wnd);
        sf::Event event;

        float dt = clock.restart().asSeconds() * 10000;

        while (wnd.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                wnd.close();
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                update(fills);
                sf::Font font;
                font.loadFromFile("CyrilicOld.TTF");
                sf::Text text("", font, 50);
                if (!Dark) {
                    text.setFillColor(sf::Color::Black);
                } else {
                    text.setFillColor(sf::Color::White);
                }
                text.setStyle(sf::Text::Bold | sf::Text::Underlined);
                int x1 = position.x, y1 = position.y;
                if (x1 >= size / 2 + shift_y) {
                    x1 -= 1;
                }
                if (y1 >= size / 2 + shift_x) {
                    y1 -= 1;
                }
                if (check(y1, x1, fills)) {
                    text.setString("YES");
                } else {
                    text.setString("NO");
                }
                text.setPosition(0, 0);
                wnd.draw(text);
                wnd.display();
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                bool (*f[9])(double, double) = { line1_down, line2_down, parabola_x_in, parabola_y_in, circle_in, rectangle_in, rhombus_in, axis_x_up, axis_y_right };
                int x1 = position.x, y1 = position.y;
                if (x1 >= size / 2 + shift_y) {
                    x1 -= 1;
                }
                if (y1 >= size / 2 + shift_x) {
                    y1 -= 1;
                }
                std::vector<bool> a(9);
                for (int i = 0; i < 9; ++i) {
                    a[i] = f[i](x1, y1);
                }

                bool flag = true;
                int ind = 0;
                for (int i = 0; i < fills.size(); ++i) {
                    if (fills[i] == a) {
                        ind = i;
                        flag = false;
                    }
                }
                if (flag) {
                    fills.push_back(a);
                } else {
                    fills.erase(fills.begin() + ind);
                }
                update(fills);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                if (size_p <= 150) {
                    size_p += 10;
                    update(fills);
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
                if (size_p > 20) {
                    size_p -= 10;
                    update(fills);
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                if (shift_x < size / 2 - size_p) {
                    shift_x += 20 * dt;
                    update(fills);
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                if (shift_x > -(size / 2 - size_p)) {
                    shift_x -= 20 * dt;
                    update(fills);
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                if (shift_y > -(size / 2 - size_p)) {
                    shift_y -= 20 * dt;
                    update(fills);
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                if (shift_y < size / 2 - size_p) {
                    shift_y += 20 * dt;
                    update(fills);
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
                shift_y = 0;
                shift_x = 0;
                update(fills);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::N)) {
                size_p = 50;
                update(fills);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                Dark = !Dark;
                update(fills);
            }
        }
    }
    return 0;
}

