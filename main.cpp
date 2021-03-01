#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include<iostream>

using namespace std;

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
        -0.5f, -0.5f,
        0.0f, 0.5f,
        0.5f, -0.5f
    };
    unsigned int buffer;
    glGenBuffers(1,&buffer);
    glBindBuffer(GL_ARRAY_BUFFER,buffer);
    glBufferData(GL_ARRAY_BUFFER, 6*sizeof(float),position, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,sizeof(float)*2,0);

    string vertexShader =
        "#version 330 core\n"
        "\n"
        "layout(location=0) in vec4 position;\n"
        "\n"
        "void main()\n"
        "{\n"
        "   gl_Position = position;\n"
        "}\n";

    string fragmentShader =
        "#version 330 core\n"
        "\n"
        "layout(location=0) out vec4 color;\n"
        "\n"
        "void main()\n"
        "{\n"
        "   color = vec4(1.0,0.0,0.0,0.5)\n"
        "}\n";

    unsigned int shader = CreateShader(vertexShader,fragmentShader);
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

    glfwTerminate();
    return 0;
}