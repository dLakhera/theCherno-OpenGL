#include "Shader.h"
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include "Renderer.h"

using namespace std;

struct ShaderProgramSource
{
    string VertexSource;
    string FragmentSource;
};

static ShaderProgramSource ParseShader(const std::string &filepath)
{
    fstream stream(filepath);
    string line;

    enum class ShaderType
    {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };

    ShaderType type = ShaderType::NONE;

    stringstream ss[2];
    while (getline(stream, line))
    {
        if (line.find("#shader") != string::npos)
        {
            if (line.find("vertex") != string::npos)
            {
                // set mode to vertex
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != string::npos)
            {
                type = ShaderType::FRAGMENT;
            }
        }
        else
        {
            ss[(int)type] << line << "\n";
        }
    }

    return {ss[0].str(), ss[1].str()};
}

Shader::Shader(const std::string& filepath) 
    :m_FilePath(filepath), m_RendererID(0)
{
    ShaderProgramSource source = ParseShader(filepath);
    m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader() 
{
    GLCall(glDeleteProgram(m_RendererID));
}


void Shader::SetUniform4f(const std::string& name, float v0, float v1, float f1, float f3) 
{
    GLCall(glUniform4f(GetUniformLocation(name),v0,v1,f1,f3));
}

void Shader::Bind() const
{
    GLCall(glUseProgram(m_RendererID));
}

void Shader::Unbind() const
{
    GLCall(glUseProgram(0));
}

void Shader::SetUniform1f(const std::string &name, float value) 
{
    GLCall(glUniform1f(GetUniformLocation(name),value));
}

void Shader::SetUniform1i(const std::string &name, int value) 
{
    GLCall(glUniform1i(GetUniformLocation(name), value));
}

unsigned int Shader::CompileShader(unsigned int type, const string &source)
{
    unsigned int id = glCreateShader(type);
    const char *src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char *message = (char *)(alloca(length * sizeof(char)));
        glGetShaderInfoLog(id, length, &length, message);
        cout << "Error from " << (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT") << " shader file";
        cout << message << endl;
        glDeleteShader(id);
    }
    return id;
}

unsigned int Shader::CreateShader(const string &verterShader, const string &fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, verterShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);

    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
};


int Shader::GetUniformLocation(const std::string& name) 
{

    if(m_LocationCache.find(name) != m_LocationCache.end()){
        return m_LocationCache[name];
    }

    GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
    if(location == -1)
        std::cout << "Warning: UNiform " << name << " doesnt exist?" <<std::endl;
    else {
        m_LocationCache[name] = location;
    }
    return location;
}
