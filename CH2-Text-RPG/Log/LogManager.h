#pragma once

#include <string>
#include <vector>

class LogManager
{
public:
    LogManager();
    ~LogManager();

    void AddLog(const std::string& message);
    void PrintLog() const;
    const std::vector<std::string>& GetLogs() const;

protected:
private:
    std::vector<std::string> Logs;
};
