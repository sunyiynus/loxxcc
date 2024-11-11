#include <iostream>
using namespace std;

static const char *const HEADER = "\nLoxxcc © 2024 Sun Yi.\n\n";


#include <iostream>
#include <unordered_map>
#include <functional>
#include <sstream>
#include <vector>
#include "interpreter.h"

class REPL {
public:
    REPL() {
        // 注册命令
        commands["help"] = [this](const std::vector<std::string>& args) { help(args); };
        commands["exit"] = [this](const std::vector<std::string>& args) { exit(args); };
    }

    void run() {
        std::cout << "欢迎使用loxxjj！输入 'help' 查看命令列表，输入 'exit' 退出。" << std::endl;
        std::string line;
        while (running) {
            std::cout << ">>> ";
            if (!std::getline(std::cin, line)) break;
            evaluate(line);
        }
    }

private:
    
private:
    std::unordered_map<std::string, std::function<void(const std::vector<std::string>&)>> commands;
    bool running = true;

    void evaluate(const std::string& commandLine) {
        std::istringstream iss(commandLine);
        std::string commandName;
        iss >> commandName;

        std::vector<std::string> args;
        std::string arg;
        while (iss >> arg) {
            args.push_back(arg);
        }

        auto command = commands.find(commandName);
        if (command != commands.end()) {
            command->second(args);
        } else {
            std::cout << "未知命令: " << commandName << std::endl;
        }
    }

    void help(const std::vector<std::string>& args) {
        std::cout << "可用命令:" << std::endl;
        for (const auto& command : commands) {
            std::cout << "  " << command.first << std::endl;
        }
    }

    void exit(const std::vector<std::string>& args) {
        std::cout << "退出Loxxjj..." << std::endl;
        running = false;
    }
};


int main(int argc, const char *argv[]) {
  cout << HEADER;
    REPL repl;
    repl.run();
  return 0;
}
