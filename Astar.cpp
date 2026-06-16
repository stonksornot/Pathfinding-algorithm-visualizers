#include <iostream>
#include <vector>
#include <queue>
#define ll long long
#include <SFML/Graphics.hpp>

using namespace std;

const ll INF = LLONG_MAX/2;

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

struct node {
    int x, y;
    ll g, h;

    ll f() const {
        return g + h;
    }
    bool operator>(const node& other) const {
        return f() > other.f();
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "A* Visualization");

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
    vector<vector<ll>> d(maze.size(), vector<ll>(maze[0].size(), INF));
    d[0][0] = 0;

    priority_queue<node, vector<node>, greater<node>> pq;
    pq.push({0, 0, 0, 30 + 30});

    int count = 0;

    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::Black);

        sf::Font font;
        if(!font.loadFromFile("C:\\Users\\Rioca\\Documents\\Grid_visualizer\\DejaVuSans.ttf")) {
            cerr << "Error: Font file not found or could not be loaded.\n" ;
            return EXIT_FAILURE;
        }

        for(int i = 0; i < maze.size(); i++) {
            for(int j = 0; j < maze[i].size(); j++) {
                sf::RectangleShape cell(sf::Vector2f(20, 20));
                cell.setPosition(j * 20, i * 20);
                if(maze[i][j] == '#') {
                    cell.setFillColor(sf::Color::Red);
                } else if(maze[i][j] == 'v') {
                    cell.setFillColor(sf::Color::Green);
                } else {
                    cell.setFillColor(sf::Color::White);
                }
                window.draw(cell);
            }
        }

        sf::Text info_it;
        info_it.setFont(font);
        info_it.setString("Total explored: " + to_string(count));
        info_it.setCharacterSize(24);
        info_it.setFillColor(sf::Color::White);
        info_it.setPosition(10, maze.size() * 20 + 10);
        window.draw(info_it);

        sf::sleep(sf::milliseconds(50));

        window.display();

        if(!pq.empty()) {
            int x = pq.top().x;
            int y = pq.top().y;
            ll g = pq.top().g;
            ll h = pq.top().h;
            pq.pop();
            count++;
            maze[x][y] = 'v';
            if(d[x][y] < g) continue;
            for(int i = 0; i < 4; i++) {
                int nx = x + dx[i];
                int ny = y + dy[i];
                if(nx >= 0 && nx < maze.size() && ny >= 0 && ny < maze[0].size() && maze[nx][ny] != '#') {
                    ll ng = g + 1;
                    ll nh = (maze.size() - 1 - nx) + (maze[0].size() - 1 - ny);
                    if(ng < d[nx][ny]) {
                        d[nx][ny] = ng;
                        pq.push({nx, ny, ng, nh});
                    }
                }
            } 
            if(x == maze.size() - 1 && y == maze[0].size() - 1) {
                cout << "Reached the goal!\nTotal distance: " << d[x][y] << endl;
                while(!pq.empty()) pq.pop();
            }
        }
    }

    return 0;
}