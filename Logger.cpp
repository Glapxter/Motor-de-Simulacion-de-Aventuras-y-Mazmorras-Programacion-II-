#include "Logger.h"
#include <stdexcept>
using namespace std;

Logger::Logger(const string& logPath)
    : logPath(logPath), turn(1) {
    logFile.open(logPath);
    if (!logFile.is_open())
        throw runtime_error("Could not open log file: " + logPath);
    logFile << "=== Hyrule Adventure — Simulation Log ===" << endl;
    logFile << endl;
}

Logger::~Logger() {
    if (logFile.is_open()) logFile.close();
}

void Logger::log(const string& message) {
    entries.push_back(message);
    logFile << message << endl;
    logFile.flush();
}

void Logger::logTurn(const string& message) {
    string entry = "[Turn " + to_string(turn) + "] " + message;
    log(entry);
}

void Logger::nextTurn()
{
    ++turn;
}
int Logger::getTurn() const
{
    return turn;
}

Logger& Logger::operator<<(const string& message) {
    log(message);
    return *this;
}

void Logger::writeReport(const string& reportPath, const string& simulationSummary) const {
    ofstream report(reportPath);
    if (!report.is_open())
        throw runtime_error("Could not open report file: " + reportPath);

    report << " ========================== HYRULE ADVENTURE — FINAL REPORT ==========================" << endl;
    report << simulationSummary << endl;
    report << endl;
    report << "--- Event Log ---" << endl;
    for (const auto& entry : entries)
        report << entry << endl;
    report << endl;
    report << "========================================" << endl;
    report << "Total turns: " << turn << endl;
    report.close();
}

const vector<string>& Logger::getEntries() const { return entries; }