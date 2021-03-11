#pragma once
#include<string>
#include<unordered_map>
using namespace std;

class Shader {
    private:
        std::string m_FilePath;
        unsigned int m_RendererID;
        std::unordered_map<std::string,int> m_LocationCache;
        int GetUniformLocation(const std::string& name);
        unsigned int CompileShader(unsigned int type, const string &source);
        unsigned int CreateShader(const string &verterShader, const string &fragmentShader);
    public : 
        Shader(const std::string &filepath);
        ~Shader();

        void Bind() const;
        void Unbind() const;
        void SetUniform1f(const std::string &name, float value);
        void SetUniform1i(const std::string &name, int value);
        void SetUniform4f(const std::string &name, float v0, float v1, float f1, float f3);
};