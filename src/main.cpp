#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include<iostream>
#include<fstream>
#include<bits/stdc++.h>

using namespace std;

struct ShaderProgramSource {
    string VertexSource;
    string FragmentSource;
};

static ShaderProgramSource ParseShader(const std::string& filepath){
    fstream stream(filepath);
    string line;

    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    ShaderType type = ShaderType::NONE;

    stringstream ss[2];
    while(getline(stream, line)){
        if(line.find("#shader") != string::npos){
            if(line.find("vertex") != string::npos){
                // set mode to vertex
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != string::npos){
                type = ShaderType::FRAGMENT;
            }
        } else {
            ss[(int)type] << line <<"\n";
        }
    }

    return {ss[0].str(), ss[1].str()};
}

static unsigned int CompileShader(unsigned int type, const string &source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id,1, &src,nullptr);
    glCompileShader(id);
    
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    if(result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)(alloca(length*sizeof(char)));
        glGetShaderInfoLog(id,length,&length,message);
        cout<<"Error from "<<(type == GL_VERTEX_SHADER ? "VERTEX":"FRAGMENT")<< " shader file";
        cout<<message<<endl;
        glDeleteShader(id);
    }
    return id;
}

static unsigned int CreateShader(const string& verterShader, const string& fragmentShader){
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

int main(void)
{
    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    cout<<glGetString(GL_VERSION)<<endl;
    glewInit();

    float position[6] = { 
        0.0f, 0.0f,
        0.0f, 0.5f,
        0.5f, 0.0f
    };
    unsigned int buffer;
    glGenBuffers(1,&buffer);
    glBindBuffer(GL_ARRAY_BUFFER,buffer);
    glBufferData(GL_ARRAY_BUFFER, 6*sizeof(float),position, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,sizeof(float)*2,0);

    ShaderProgramSource source = ParseShader("../res/shader/basic.shader");
    // cout<<"VERTEX"<<endl;
    // cout << source.VertexSource << endl;
    // cout << "Fragment" << endl;
    // cout << source.FragmentSource << endl;

    unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
    glUseProgram(shader);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES,0,3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window); 

        /* Poll for and process events */
        glfwPollEvents();
    }
    glDeleteProgram(shader);
    glfwTerminate();
    return 0;
}