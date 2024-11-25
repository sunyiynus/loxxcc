#ifndef TESTSCAFFOLD_H
#define TESTSCAFFOLD_H

#include <string>
#include <random>
#include <gtest/gtest.h>
#include "Utility.h"
#include "types.h"
#include "config.h"
#include "scanner.h"
#include "parser.h"
#include "interpreter.h"
#include "printer.h"

class ParserTestScaffold : public ::testing::Test {
protected:
    Tokens tokens;
    Parser parser;
    std::vector<AbsStmt::ptr> stmts;
    Printer astprinter;
    Interpreter interpreter;
    std::ostringstream oss;
    std::ostringstream ossExec;
    std::string runtimeDir;

    std::string loxFilePath;

    void SetUp() override {
        // Initialize tokens or other necessary setup before each test case
        interpreter.setOutput(std::reference_wrapper<std::ostream>(oss));
        runtimeDir = Utility::PathJoin({g_loxSourceDir, "bin"});
        setOstreamToBuffer();

    }

    Token createToken(TokenType type, std::string lexeme) {
        return Token(lexeme, lexeme, 0, type);
    }

    void setOstreamToBuffer() {
        astprinter.setOstream(oss);
        interpreter.setOutput(ossExec);
    }

    void loadLoxCodeFromFile(const std::string path) {
        loxFilePath = path;
        auto filePath = Utility::PathJoin({g_loxSourceDir, path});
        std::string srcCode = Utility::ReadFile(filePath);
        Scanner lexer(srcCode);
        tokens = lexer.scanTokens();
        parser = Parser(tokens);
        stmts = parser.parse();
    }

    std::string generateRandomDotFileName() {
        const int nameLength = 6;  // 文件名长度
        const std::string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

        // 随机数生成器
        std::random_device rd;
        std::mt19937 generator(rd());
        std::uniform_int_distribution<> distribution(0, chars.size() - 1);

        std::string fileName;
        for (int i = 0; i < nameLength; ++i) {
            fileName += chars[distribution(generator)];
        }

        // 添加 .dot 后缀
        fileName += ".dot";
        return fileName;
    }

    std::string generateDot(const std::string file = "") {
        std::ostringstream tmposs;
        tmposs << "digraph AST {\n";
        tmposs << "label=\"" << file <<"\";\n";
        tmposs << "  node [shape=records];\n";
        tmposs << oss.str();
        tmposs << "}\n";
        return tmposs.str();
    }

    bool writeToDotFile() {

        auto content = generateDot(loxFilePath);
        // 打开文件输出流
        std::string filePath = runtimeDir + "/dot/" + generateRandomDotFileName();
        std::ofstream outFile(filePath);
        // 检查文件是否打开成功
        if (!outFile.is_open()) {
            std::cerr << "Error: Could not open file " << filePath << " for writing." << std::endl;
            return false;
        }
        // 写入内容到文件
        outFile << content;
        // 关闭文件
        outFile.close();
        
        // 检查文件流状态
        if (outFile.fail()) {
            std::cerr << "Error: Failed to write to file " << filePath << "." << std::endl;
            return false;
        }
        
        return true;
    }
};



#endif // TESTSCAFFOLD_H