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
    
public:
    Cli();
    ~Cli();                 
    void start();
};

#endif