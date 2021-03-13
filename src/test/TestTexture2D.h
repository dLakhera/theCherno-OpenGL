#pragma once

#include <memory>

#include "Test.h"

#include "../Texture.h"
#include "../VertexArray.h"
#include "../VertexBuffer.h"
#include "../VertexBufferLayout.h"
#include "../vendor/glm/glm.hpp"
#include "../vendor/glm/gtc/matrix_transform.hpp"
#include "../Shader.h"

namespace test
{
    class TestTexture2D : public Test
    {
    public:
        TestTexture2D();
        ~TestTexture2D();

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void onImGuiRender() override;

    private:
        glm::vec3 m_TranslationA, m_TranslationB;
        std::unique_ptr<VertexArray> m_VAO;
        std::unique_ptr<VertexBuffer> m_VertexBuffer;
        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<IndexBuffer> m_IndexBuffer;
        std::unique_ptr<Texture> m_Texture;

        glm::mat4 m_Proj, m_View;
    };
}