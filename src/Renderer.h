#pragma once

#include <GL/glew.h>
#include <cassert>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"



#define GLCall(x)   \
    GLClearError(); \
    x;              \
    assert(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char *function, const char *file, int line);

class Renderer {
private:

public:
    void Clear() const;
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};