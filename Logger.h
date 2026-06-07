#ifndef BARRIOS_MARCHAN_ANTHONY__PROYECTO_2__LOGGER_H
#define BARRIOS_MARCHAN_ANTHONY__PROYECTO_2__LOGGER_H

#include <string>
#include <vector>
#include <fstream>

// Records every significant event during the simulation.
// Writes a log file in real time and a final report at the end.
class Logger {
private:
    std::vector<std::string> entries;
    std::ofstream logFile;
    std::string logPath;
    int turn;

public:
    explicit Logger(const std::string& logPath);
    ~Logger();

    void log(const std::string& message);
    void logTurn(const std::string& message);

    void nextTurn();
    int  getTurn() const;

    void writeReport(const std::string& reportPath, const std::string& simulationSummary) const;

    // Overloaded << for convenient logging
    Logger& operator<<(const std::string& message);

    const std::vector<std::string>& getEntries() const;
};

#endif //BARRIOS_MARCHAN_ANTHONY__PROYECTO_2__LOGGER_H