#include <iostream>
using namespace std;


class Logger {
public:
    enum class Level{
        DEFAULT,
        INFO,
        FATAL
    };
    static Logger& getLoggerInstance() {
        call_once(flag, [](){
            // make_unique(args) 是外部，call Logger 裡面的 constructor.
            // 這裏是 private constructor 所以不行
            logger.reset(new Logger());
        });
        return *logger; // logger.get();  // 回傳 Logger*
    }
    void log(const string &message, Level level)
    {
        switch (level) {
            case Level::DEFAULT:
                cout << "[DEFAULT]: ";
                break;
            case Level::INFO:
                cout << "[INFO]: ";
                break;
            case Level::FATAL:
                cout << "[FATAL] ";
                break;
        }
        cout << message << endl;
    }

    // copy
    Logger(const Logger& copy) = delete;
    // assignment
    Logger& operator=(const Logger& assign) = delete;

    // move
    Logger(Logger&& copy) = delete;
    // move assignment
    Logger& operator=(Logger&& assign) = delete;

private:
    Logger() = default;
    static unique_ptr<Logger> logger;
    static once_flag flag;
};

unique_ptr<Logger> Logger::logger = nullptr;
once_flag Logger::flag;

int main()
{
    Logger& logger = Logger::getLoggerInstance();
    logger.log("Hello world", Logger::Level::INFO);
}
