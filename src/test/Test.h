#pragma once

namespace test{
    class Test{
    public:
        Test() {}
        virtual ~Test() {}

        virtual void OnRender() {}
        virtual void OnUpdate(float onDeltaTime) {}
        virtual void onImGuiRender() {}
    };
};