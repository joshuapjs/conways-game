#ifndef CLI
#define CLI
#include <memory>

class World;

class Cli {
private:
    bool printOn;
    int delayTime;           //delay in milliseconds
    bool stabilityCheck;     
    std::unique_ptr<World> world; 
    void save(std::string& input);
    void load(std::string& input);
    void create(std::string& input);
    
public:
    Cli();
    ~Cli();
    void start();
    void addBeacon(std::string& input);
    void addToad(std::string& input);
    void addGlider(std::string& input);
    void getOneD(std::string& input);
    void getTwoD(std::string& input);
    void setOneD(std::string& input);
    void setTwoD(std::string& input);
    void getOneD(std::string& input);
    void setOneD(std::string& input);
    void setTwoD(std::string& input);
    void run(std::string& input);
    void stability(std::string& input);
    void delay(std::string& input);
    void print(std::string& input);
    void help(std::string& input);
};

#endif