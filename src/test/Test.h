#pragma once
#include <functional>
#include <iostream>
#include <vector>
#include <string>


namespace test{
    class Test{
    public:
        Test() {}
        virtual ~Test() {}

        virtual void OnRender() {}
        virtual void OnUpdate(float onDeltaTime) {}
        virtual void onImGuiRender() {}
    };

    class TestMenu : public Test 
    {
    public:
        TestMenu(Test*& currentTestPointer);
        void onImGuiRender() override;

        template<typename T>
        void RegisterTest(const std::string& name)
        {   
            std::cout<<"Regitering tests"<<name<<std::endl;
            m_Tests.push_back(std::make_pair(name,[](){ return new T();}));
        }

    private:
        Test*& m_CurrentTest;
        std::vector<std::pair<std::string, std::function<Test*()>>> m_Tests;
    };
};