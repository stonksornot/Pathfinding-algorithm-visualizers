#include <iostream>
#include <vector>
#include <queue>
#include <SFML/Graphics.hpp>

using namespace std;

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "BFS Visualization");

    std::vector<std::string> maze = {
        ".....#....#....................",
        "#.#..#....#....................",
        "#.#.###.#.#########.#########..",
        "#.#...#.#...........#...#......",
        "#.#####.#############.###.####.",
        "#...#...#.........#...#...#....",
        "###.#.###.#######.#.#.#.###.##.",
        "#...#...#.#.....#.#.#.#...#....",
        "#.#####.#.#####.#.#.###.###..##",
        "#.....#.#.#.....#...#...#.#....",
        "#####.#.#.#.###.#####.#.#.#.#..",
        "#.#...#.#.#...#.....#.#.#.#.#..",
        "#.#.###.#.#####.###.#.#.#.#.#..",
        "#...#...#.#.....#...#.#.#...#..",
        "#.###.#.#.#.#####.#.#.#######..",
        "#.#...#.#.#.#.#...#.#..........",
        "#.###.#.#.#.#.###.##########..#",
        "#...#.#.#...#.#.............#..",
        "###.###.#####.#############.#..",
        "#.#.#...#.........#.#...#...#..",
        "#.#.#.###.#.#####.#.#.#.#.###..",
        "#.#.#.#...#.#...#...#.#...#....",
        "#.#.#.#####.#.#####.#.#####.#..",
        "#.#.#...#...#.......#.#...#.#..",
        "#.#.#.#.#.#####.#####.#.#.#.#..",
        "#.#.#.#.#.....#...#.#.#.#...#..",
        "#.#.###.#####.###.#.#.#######..",
        "#.#.#...#.....#.....#...#......",
        "#.#.#.###.#############.#.###..",
        "#.....#...................#....",
        "##############################."
    };

    queue<pair<int, int>> q;
    q.push({0, 0});

    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        for(int i = 0; i < maze.size(); i++) {
            for(int j = 0; j < maze[i].size(); j++) {
                sf::RectangleShape cell(sf::Vector2f(20, 20));
                cell.setPosition(j * 20, i * 20);
                if(maze[i][j] == '#') {
                    cell.setFillColor(sf::Color::Red);
                } else if(maze[i][j] == '.') {
                    cell.setFillColor(sf::Color::White);
                } else {
                    cell.setFillColor(sf::Color::Green);
                }
                window.draw(cell);
            }
        }

        sf::sleep(sf::milliseconds(10));

        window.display();

        if(!q.empty()) {
            int x = q.front().first;
            int y = q.front().second;
            q.pop();
            maze[x][y] = 'v';
            for(int i = 0; i < 4; i++) {
                int nx = x + dx[i];
                int ny = y + dy[i];
                if(nx >= 0 && nx < maze.size() && ny >= 0 && ny < maze[0].size() && maze[nx][ny] == '.') {
                    q.push({nx, ny});
                }
            }
        }
    }

    return 0;
}