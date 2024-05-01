#pragma once

#include "Core.h"

#include "Window.h"
#include "NotVoxel/Core/LayerStack.h"

#include "NotVoxel/ImGui/ImGuiLayer.h"

#include "NotVoxel/Core/TimeStep.h"

namespace VoxelForge
{
    class WindowCloseEvent;
    class WindowResizeEvent; 
    
    struct AppCommandLineArgs
    {
        int Count = 0;
        char** Args = nullptr;

        const char* operator[](int index) const
        {
            CORE_ASSERT(index < Count, "Overflow!");
            return Args[index];
        }
    };

    struct ApplicationSpecification
    {
        std::string Name = "NotRed Application";
        std::string WorkingDirectory;
        AppCommandLineArgs CommandLineArgs;
    };

    class Application
    {
    public:
        Application(const ApplicationSpecification& specification);
        virtual ~Application();

        void Run();

        void OnEvent(Event& e);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);

        inline Window& GetWindow() { return *mWindow; }
        inline static Application& Get() { return *sInstance; }

        const ApplicationSpecification& GetSpecification() const { return mSpecification; }

        void SubmitToMainThread(const std::function<void()>& function);

        ImGuiLayer* GetImGuiLayer() { return mImGuiLayer; }

        inline void Close() { mRunning = false; }

    private:
        bool OnWindowClose(WindowCloseEvent& e);
        bool OnWindowResize(WindowResizeEvent& e);

        void ExecuteQueuedFunctions();

    private:
        static Application* sInstance;

        ApplicationSpecification mSpecification;

        std::vector<std::function<void()>> mQueuedFunctions;
        std::mutex mMainThreadQueueMutex;

        bool mRunning = true;
        bool mMinimized = false;

        Scope<Window> mWindow;
        
        LayerStack mLayerStack;
        ImGuiLayer* mImGuiLayer;

        TimeStep mTimeStep;
    };

    Application* CreateApplication(AppCommandLineArgs args);
}